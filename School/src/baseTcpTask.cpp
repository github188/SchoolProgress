#include "baseTcpTask.h"
bool TcpTask::listeningSend()
{
	return mSocket.sync();
}
void TcpTask::getNextState()
{
	TCPTask_State old_state = getState();
	switch(old_state)
	{
		case notuse:
			setState(verify);
			break;
		case verify:
			setState(sync);
			break;
		case sync:
			buffered = true;
			addToContainer();
			setState(okey);
			break;
		case okay:
			removeFromContainer();
			setState(recycle);
			break;
		case recycle:
			setState(notuse);
			break;
	}
}
void TcpTask::resetState()
{
	TCPTask_State old_state = getState();
	switch(old_state)
	{
		case notuse:
		case recycle:
			break;
		case verify:
		case sync:
		case okay:
			break;
	}
	setState(recycle);
}
void TcpTask::checkSignal(const Time &ct)
{
	if(ifCheckSignal() && checkInterval(ct))
	{
		if(checkTick())
		{
			terminate(TCPTask::terminate_active);
		}
		else
		{
			Cmd::t_NullCmd tNullCmd;
			if(sendCmd(&tNullCmd,sizeof(tNullCmd)))
			{
				setTick();
			}
		}
	}
}
TcpTask::TcpTask(const SWORD sock,const struct sockaddr_in *addr,const bool compress,const):taskType(0),
buffered(false),mSocket(sock,addr,compress),state(notuse),terminate(terminate_no),terminate_wait(false),fdsradd(false),lifeTime(),uniqueVerified(false),_checkSignal(checkSignal),_tick_timer(3600 *1000L),tick(false),_check_timeout(true)
{
	_verify_state = 0;
}
bool TcpTask::sendCmd(const void *pstrCmd,SWORD cmdLen)
{
	Cmd::t_NullCmd *ptNullCmd = (Cmd::t_NullCmd*)pstrCmd;
	analysisSendingCmd(ptNullCmd->byCmd,ptNullCmd->byParam,cmdLen);
	return mSocket.sendCmd(pstrCmd,cmdLen,buffered);
}
bool TcpTask::sendCmdNoPack(const void *pstrCmd,SWORD cmdLen)
{
	return mSocket.sendCmdNoPack(pstrCmd,cmdLen,buffered);
}
SWORD TcpTask::verifyConn()
{
	SWORD ret = mSocket.recvToBuf_NoPoll();
	if(ret > 0)
	{
		return ret;
	}
	BYTE pstrCmd[Socket::MAX_DATASIZE];
	SWORD cmdLen = mSocket.recvToCmd_NoPoll(pstrCmd,sizeof(pstrCmd));
	if(cmdLen <= 0)
	{
		return 0;
	}
	msgParseStart((Cmd::t_NullCmd*)pstrCmd,cmdLen);
	return _verify_state;
}
bool TcpTask::verifyLogin(const Cmd::Server::stLoginStartServerCmd *ptCmd)
{
	const ServerEntry *entry = SubNetService::getInstance().getServerEntry(ptCmd->ServerType);
	_verify_state = -1;
	if(!entry)
	{
		return false;
	}
	char strIP[32];
	strcpy(strIP,getIP());
	if(ptCmd->ServerType != entry->ServerType)
	{
		return false;
	}
	if(strcmp(strIP,entry->pstrIP))
	{
		return false;
	}
	id = ptCmd->ServerID;
	taskType = ptCmd->ServerType;
	strncpy(name,getServerTypeString((ServerType)ptCmd->ServerType),sizeof(name));
	_verify_state = 1;
	return true;
}
bool TcpTask::listeningRecv(bool needRecv)
{
	SWORD ret = 0;
	if(needRecv)
	{
		ret = mSocket.recvToBuf_NoPoll();
	}
	if(ret == -1)
	{
		return false;
	}
	else
	{
		do
		{
			BYTE pstrCmd[Socket::MAX_DATASIZE];
			SWORD cmdLen = mSocket.recvToCmd_NoPoll(pstrCmd,sizeof(pstrCmd));
			if(cmdLen <= 0)
			{
				break;
			}
			else
			{
				Cmd::t_NullCmd *ptNullCmd = (Cmd::t_NullCmd*)pstrCmd;
				if(Cmd::CMD_NULL == ptNullCmd->byCmd)
				{
					if(Cmd::SERVER_PARA_NULL == ptNullCmd->byParam)
					{
						clearTick();
					}
					else if(Cmd::CLIENT_PARA_NULL == ptNull->byParam)
					{
						sendCmd(ptNullCmd,cmdLen);
					}
				}
				else
				{
					parse(ptNullCmd,cmdLen);
					analysisRecvingCmd(ptNullCmd->byCmd,ptNullCmd->byParam,);
				}
			}
		}while(true);
	}
	return true;
}
bool TcpTaskNoQueue::parse(const Cmd::t_NullCmd *ptNullCmd,const DWORD cmdLen)
{
	switch(ptNullCmd->byCmd)
	{
		case Cmd::Server::START_SERVERCMD:
			{
				return msgParseStart(ptNull,cmdLen);
			}
			break;
		case Cmd::Server::FORWARD_SERVERCMD:
			{
				return msgParseForward(ptNull.cmdLen);
			}
			break;
		default:
			{
				return msgParse(ptNull,cmdLen);
			}
			break;
	}
	rturn true;
}

bool TcpTaskQueue::parse(const Cmd::t_NullCmd *ptNullCmd, const DWORD cmdLen)
{
	return cmdMsgParse(ptNullCmd,cmdLen);
}
bool TcpTask::listeningSend()
{
	return mSocket.sync();
}
