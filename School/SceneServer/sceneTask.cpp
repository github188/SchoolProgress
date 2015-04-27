#include "sceneTask.h"
#include "base/baseConstruct.h"
#include "base/baseSqlHandle.h"
#include "sceneTimeTick.h"
#include "SceneServer.h"
#include "sceneTaskManager.h"


SceneTask::SceneTask(const SDWORD sock,const struct sockaddr_in *addr) : TcpTaskQueue(sock,addr),m_sequenceTimer(2*1000L)
{
	m_recycleTime = 200;
	m_recycleState = RS_First;
	m_verify = false;
}

bool SceneTask::checkRecycle()
{
	CheckConditonReturn( m_recycleState!=RS_First,false );
	if(m_recycleState == RS_Second)
	{
		m_recycleState = RS_Third;
	}
	return true;
}

SDWORD SceneTask::verifyConnect()
{
	SDWORD ret = m_mSocket.recvToBufNoPoll();
	CheckConditonReturn(ret>0,ret);

	BYTE cmd[Socket::s_maxDataSize];
	LogErrorCheckCondition(m_mSocket.recvToCmdNoPoll(cmd),0,"场景服务器连接验证接收数据失败");
	
	using namespace Cmd::Server;
	LoginStartServerCmd*ptCmd = (LoginStartServerCmd*)cmd;
	if(ptCmd->byCmd == START_SERVERCMD && ptCmd->byParam == LOGIN_START_SERVERCMD_PARA)
	{
		if(verifyLogin(ptCmd))
		{
			m_verify = true;
			Global::logger->info("场景服务器客户端连接通过验证%u,%u",id,m_taskType);
			return 1;
		}
	}
	Global::logger->error("场景服务器客户端连接验证失败"); 
	return -1;
}

SDWORD SceneTask::waitSync()
{
	return 1;
}

SDWORD SceneTask::recycleConnect()
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

bool SceneTask::uniqueAdd()
{
	return SceneTaskManager::getInstance().addTask(this);
}

bool SceneTask::uniqueRemove()
{
	return SceneTaskManager::getInstance().uniqueRemove(this);
}

bool SceneTask::msgParseStart(const Cmd::NullCmd *cmd,const DWORD cmdLen)
{
	return true;
}

bool SceneTask::msgParseForward(const Cmd::NullCmd *cmd,const DWORD cmdLen)
{
	return false;
}

bool SceneTask::msgParse(const Cmd::NullCmd *cmd,const DWORD cmdLen)
{
	return true;
}


