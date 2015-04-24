#include "superTask.h"

RWLock SuperTask::s_lock;

SuperTask::SuperTask(const SDWORD sock,const struct sockaddr_in *addr) : TcpTaskQueue(sock,addr),m_sequenceTimer(2*1000L)
{
	bzero(m_ip,sizeof(m_ip));
	m_port = 0;
	bzero(m_outIP,sizeof(m_outIP));
	m_outPort = 0;
	m_serverSize = 0;
	m_serverReturnSize = 0;
	m_hasNotifyOther = false;
	m_hasNotifyMe = false;
	m_hasNotifyMeReturn = false;
	m_recycleTime = 200;

	m_recycleState = RS_First;
	m_verify = false;
}
bool SuperTask::checkRecycle()
{
	CheckConditonReturn( m_recycleState!=RS_First,false );
	if(m_recycleState == RS_Second)
	{
		m_recycleState = RS_Third;
	}
	return true;
}

bool SuperTask::verify(const DWORD serverType,const char *ip)
{
	RWLock_scope_wrlock tempLock(s_lock);
	MysqlHandle *handle = SuperServer::s_mySqlPool->getHandle();
	LogErrorCheckCondition(handle,false,"数据库句柄为空");
	
	std::ostringstream oss;
	Record where;
	strncpy(m_ip,ip,sizeof(m_ip));
	oss << "type=" << serverType;
	where.put("type",oss.str());
	oss.str("");
	std::string escapeIP;
	oss << "ip=" << handle->escapeString(ip,escapeIP) << "";
	where.put("ip",oss.str());
	RecordSet *recordSet = handle->exeSelect("SERVERLIST",NULL,&where);
	
	SuperServer::s_mySqlPool->putHandle(handle);	
	if(!recordSet || recordSet.empty())
	{
		SAFE_DELETE(recordSet);
		return false;
	}
	for(size_t index = 0;index < recordSet.size();++index)
	{
		if(SuperTaskManager::getInstance().uniqueVerify(recordSet->get(index)->getValue("id")))
		{
			id = recordSet->get(index)->getvalue("id");
			taskType = recordSet->get(index)->getValue("type");
			strncpy(name,recordSet->get(index)->getValue("name"),sizeof(name));
			m_port = recordSet->get(index)->getValue("port");
			strncpy(m_outIP,recordSet->get(index)->getValue("outip"),sizeof(m_outIP));
			m_outPort = recordSet->get(index)->getValue("outport");
			break;
		}
	}
	if(recordSet->size() == index)
	{
		DELETE(recordSet);
		return false;
	}
	DELETE(recordSet);

	using namespace Cmd::Server;
	ResponseStartServerCmd cmd;
	cmd.serverID = id;
	cmd.port = m_port;
	bcopy(m_outIP,cmd.outIp,sizeof(m_outIP));
	LogErrorCheckCondition(sendCmd(&cmd,sizeof(cmd)),false,"管理服务器连接验证发送消息失败");
	return true;
}

SDWORD SuperTask::verifyConnect()
{
	SDWORD ret = m_mSocket.recvToBuf_NoPoll();
	CheckConditonReturn(ret,ret);

	BYTE cmd[Socket::s_maxDataSize];
	LogErrorCheckCondition(m_mSocket.recvToCmd_NoPoll(cmd,sizeof(cmd)) > 0,0,"管理服务器连接验证接收数据失败");
	using namespace Cmd::Server;
	RequestStartServerCmd *ptCmd = (RequestStartServerCmd*)cmd;
	if(ptCmd->byCmd == START_SERVERCMD && ptCmd->byParam == REQUEST_START_SERVERCMD_PARA)
	{
		if(verify(ptCmd->serverType,ptCmd->ip))
		{
			m_protocol = ptCmd->protocol;
			m_buildTime = ptCmd->buildTime;
			m_svnVersion = ptCmd->svnVersion;
			m_verify = true;
			Global::logger->info("客户端连接通过验证%s,%u",m_ip,m_port);
			return 1;
		}
	}
	Global::logger->error("客户端连接验证失败");
	return -1;
}

SDWORD SuperTask::waitSync()
{
	SDWORD retcode = m_mSocket.checkIOForRead();
	CheckConditonReturn(retcode != -1,retcode);
	if(retcode > 0)
	{
		retcode = m_mSocket.recvToBuf_NoPoll();
		CheckConditonReturn(retcode != -1,retcode);
	}
	BYTE cmd[Socket::s_maxDataSize];
	SDWORD cmdLen = m_m_mSoket.recvToCmd_NoPoll(cmd,sizeof(cmd));
	if(cmdLen > 0)
	{
		using namespace Cmd::Server;
		OkStartServerCmd *ptCmd = (OkStartServerCmd*)cmd;
		if(cmd->byCmd == START_SERVERCMD && cmd->byParam == OK_START_SERVERCMD_PARA && id == cmd->serverID)
		{
			sendCmd(ptCmd,sizeof(OkStartServerCmd));
			Global::logger->info("服务器连接同步成功");
			return 1;
		}
		return 0;
	}
	
	RWLock_scope_wrlock tempLock(s_lock);
	if(!m_hasNotifyOther && m_sequenceTimer(SuperTimeTick::s_currentTime) && SuperTaskManager::getInstance().checkDependence(getType()))
	{
		if(notifyOther())
		{
			m_hasNotifyOther = true;
		}
	}
	if(!m_hasNotifyMe && m_hasNotifyOther && notifyReturnOK())
	{
		m_hasNotifyMe = true;
		notifyMe();
	}
	return 0;
}

SDWORD SuperTask::recycleConnect()
{
	SDWORD ret = 1;
	CheckConditonReturn( m_verify,ret );
	switch(m_recycleState)
	{
		case RS_First:
			{
				m_recycleState = RS_First;
				ret = 0;
			}
			break;
		case RS_Second:
			{
				ret = 0;
			}
			break;
		case RS_Third:
			break;
	}
	return ret;
}
bool SuperTask::uniqueAdd()
{
	return true;
}
bool SuperTask::uniqueRemove()
{
	return true;
}
bool SuperTask::msgParseStart(const Cmd::NullCmd *cmd,const DWORD cmdLen)
{
	return false;
}
bool SuperTask::msgParseForward(const Cmd::NullCmd *cmd,const DWORD cmdLen)
{
	return false;
}
bool SuperTask::msgParse(const Cmd::NullCmd *cmd,const DWORD cmdLen)
{
	return true;
}
bool SuperTask::notifyOther()
{
	using namespace Cmd::Server;
	NotifyOtherServer cmd;
	bzero(&cmd.entry,sizeof(cmd.entry));
	cmd.entry.serverID = id;
	cmd.entry.serverType = getType();
	strncpy(cmd.entry.name,name,sizeof(name));
	strncpy(cmd.entry.ip,m_ip,sizeof(m_ip));
	cmd.entry.port = m_port;
	strncpy(cmd.entry.outNetIP,m_outIP,sizeof(m_outIP));
	cmd.entry.outNetPort = m_outPort;
	cmd.entry.state = m_state;
	
	struct CheckNotifyOtherExec : public EntryCallBack<SuperTask>
	{
		WORD type;
		CheckNotifyOtherExec(const WORD _type) : type(_type)
		{
		}
		bool exec(SuperTask *task)
		{
			if(task->getType() < type)
			{
				if(task->getState() != TcpTask::TTS_OKAY)
				{
					return false;
				}
			}
			return true;
		}
	};
	CheckNotifyOtherExec exec(getType());
	CheckConditonReturn(SuperTaskManager::getInstance().execEveryTask(exec),false);
	
	struct NotifyOtherExec : public EntryCallBack<SuperTask>
	{
		NotifyOtherServer* send;
		WORD type;
		DWORD count;
		NotifyOtherExec(const NotifyOtherServer *_send,const WORD type) : send(_send),type(_type)
		{
			count = 0;
		}
		bool exec(SuperTask *task)
		{
			if(task->getType() < type)
			{
				if(task->getState() != TcpTask::TTS_OKAY)
				{
					return false;
				}
				++count;
				task->sendCmd(send,sizeof(NotifyOtherServer));
			}
			else if(task->getType() != type && task->getState() == TcpTask::TTS_OKAY)
			{
				task->sendCmd(send,sizeof(NotifyOtherServer));
			}
			return true;
		}
	};
	NotifyOtherExec notifyExec(&cmd,getType());
	SuperTaskManager::getInstance().execEveryTask(notifyExec);
	m_serverSize = exec.count;
	return true;
}

bool SuperTask::notifyMe()
{
	return true;
#if 0
	using namespace Cmd::Server;
	BYTE pBuffer[Socket::MAX_DATASIZE];
	stServerEntryNotifyMeStartServerCmd *ptCmd = (stServerEntryNotifyMeStartServerCmd*)pBuffer;
	constructInPlace(ptCmd);
	ptCmd->size = 0;
	struct NotifyMeExec : public Callback<SuperTask>
	{
		stServerEntryNotifyMeStartServerCmd *_send;
		WORD _id;
		NotifyMeExec(stServerEntryNotifyMeStartServerCmd *send,WORD id) : _send(send)._id(id)
		{
		}
		bool exec(SuperTask *task)
		{
			if(task->getID() != _id)
			{
				bzero(&_send->entry[_send->size],sizeof(_send->entry[_send->size]));
				_send->entry[_send->size].serverID = task->getID();
				_send->entry[_send->size].serverType = task->getType();
				strncpy(_send->entry[_send->size].pstrName,task->name,sizeof(task->name));
				strncpy(_send->entry[_send->size].pstrIP,task->pstrIP,sizeof(task->pstrIP));
				_send->entry[_send->size].wdPort = task->wdPort;
				strncpy(_send->entry[_send->size].pstrExtip,task->extip,sizeof(task->extip));
				_send->entry[_send->size].state = task->state;
				_send->size += 1;
			}
			return true;
		}
	};
	NotifyMeExec exec(ptCmd,getID());
	SuperTaskManager::getInstance().execEveryTask(exec);
	return sendCmd(ptCmd,sizeof(stServerEntryNotifyMeStartServerCmd) + ptCmd->size * sizeof(ServerEntry));
	#endif
}

