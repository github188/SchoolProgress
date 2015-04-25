#include "RecordServer.h"
#include "base/baseProperty.h"
#include "recordTimeTick.h"

bool RecordServer::s_reloadConfig = false;
bool RecordServer::s_initOK = false;
bool RecordServer::s_waitFinal = false;
bool RecordServer::s_checkMove = true;
bool RecordServer::s_openElemEffect = true;

WORD RecordServer::s_serverSequence = 0;
WORD RecordServer::s_serverCount = 0;

RecordServer::RecordServer() : SubNetService("RecordServer",RECORDSERVER),m_antiaddiceCheck(false)
{
}

RecordServer::~RecordServer()
{
}

bool RecordServer::init()
{
	Time time;
	time.now();
	switchAnalysis( (std::string)Global::config["cmdswitch"] == "true");

	m_taskPool = new TcpTaskPool((DWORD)Global::config["threadPoolSize"],5000 );
	LogErrorCheckCondition(m_taskPool && m_taskPool->init(),false,"档案服务器初始化任务池失败");
	
	LogErrorCheckCondition(SubNetService::init(),false,"档案服务器服务器初始化失败");

	LogErrorCheckCondition(RecordTimeTick::getInstance().start(),false,"档案服务器时间线程启动失败");
	
	startUpOK();
	s_initOK = true;
	return true;
}

void RecordServer::startUpOver()
{
	SubNetService::startUpOver();
}

void RecordServer::newTcpTask( const int sock,const struct sockaddr_in *addr )
{
#if 0
	SceneTask *tcpTask = new SceneTask( sock,addr );
	if( !tcpTask )
	{
		TEMP_FAILURE_RETRY( ::close( sock ) );
	}
	else if( !taskPool->addVerify( tcpTask ) )
	{
		DELETE(tcpTask);
	}
#endif
}

bool RecordServer::msgParse_InfoServer( const Cmd::NullCmd *nullCmd,const DWORD cmdLen)
{
#if 0
	if( !SceneAdminToolMgr::getInstance().msgParse( nullCmd,cmdLen ) )
	{
		return SubNetService::msgParse_InfoServer( nullCmd,cmdLen );
	}
#endif
	return true;
}

bool RecordServer::msgParse_SuperService( const Cmd::NullCmd *nullCmd,const DWORD cmdLen )
{
#if 0
	using namespace Cmd::Server;
	switch( nullCmd->byCmd )
	{
		case FORWARD_SERVERCMD:
			{
				switch( nullCmd->byParam )
				{
					case SEND_USERCMD_TO_SERVERUSER_FORWARD_SERVERCMD:
						{
							stSendUserCmdToServerUserForwardServerCmd *rev = (stSendUserCmdToServerUserForwardServerCmd*)nullCmd;
							SceneUser *pUser = SceneUserManager::getInstance().getUserByID( rev->id );
							if( pUser )
							{
								pUser->userMsgParse( ( Cmd::stNullUserCmd* )rev->data,rev->dataSize );
							}
							return true;
						}
						break;
					}
				}
				break;
			case Cmd::Zone::CMD_ZONE:
				{
					return msgParse_ZoneService( nullCmd,cmdLen );
				}
				break;
	}
#endif
	return false;
}

void RecordServer::finalSave()
{
#if 0
	Global::logger->debug(" 停机保存数据" );
	SceneUserManager::getInstance().removeSceneUserAll();
	SceneNpcManager::getInstance().saveAllNpc();
#endif
}
#if 0
void ScenesServer::checkFinal()
{
	if( !s_waitFinal )
	{
		return;
	}
	finalSave();
	s_waitFinal = true;
}
#endif
void RecordServer::final()
{
	s_waitFinal = true;
	while( s_initOK && s_waitFinal && !RecordTimeTick::getInstance().isFinal() )
	{
		Thread::msleep( 10 );
	}
#if 0
	SceneTimeTick::getInstance().final();
	SceneTimeTick::getInstance().join();
	SceneTimeTick::delInstance();
#endif

#if 0
	MonitorThread::getInstance().final();
	MonitorThread::getInstance().join();
	MonitorThread::delInstance();
#endif
	if( m_taskPool )
	{
		m_taskPool->final();
		DELETE( m_taskPool );
	}
#if 0
	if( sessionClient )
	{
		sessionClient->final();
		sessionClient->join();
		DELETE( sessionClient );
	}
#endif
#if 0
	if( recordClinet )
	{
		recordClient->final();
		recordClient->join();
		DELETE( recordClient );
	}
#endif

	SubNetService::final();
}


void RecordServer::reloadConfig()
{
	s_reloadConfig = true;
}

void RecordServer::checkAndReloadConfig()
{
	if( !s_reloadConfig )
	{
		return;
	}
	s_reloadConfig = false;
	switchAnalysis( (std::string)Global::config["cmdswitch"] == "true" );
}

int main( int argc,char **argv )
{
	struct timespec timeVal;
	clock_gettime( CLOCK_REALTIME,&timeVal);
	DWORD begin_time = timeVal.tv_sec*1000 + timeVal.tv_nsec/1000000;
	
	Global::logger = new Logger( "RE" );
	Global::config["cmdswitch"] = "true";
	Global::config["logfilename"] = "/home/flyer/flyer/School/log/recordserver.log";
	Global::config["LoggerLevel"] = "debug";
	Global::config["daemon"] = "true";
	Global::config["port"] = 5000;
	Global::config["serverIP"] = "127.0.0.1";
	Global::config["ifname"] = "eth0";

	Global::logger->setLevel((const char*)Global::config["LoggerLevel"]);
	if(strlen(Global::config["logfilename"]))
	{
		Global::logger->setFile((const char*)Global::config["logfilename"]);
	}
	if(!strcmp("true",Global::config["daemon"]))
	{
		Global::logger->info("RecordServer will be run as a daemon");
		Global::logger->removeConsole();
		daemon(1,1);
	}
	RecordServer::newInstance<RecordServer>();
	RecordServer::getInstance().loop();

	return EXIT_SUCCESS;
}

void RecordServer::switchAnalysis( bool switchFlg )
{
#if 0
	SessionClient::switchCmdAnalysis( switchFlg );
	RecordClient::switchCmdAnalysis( switchFlg );
	SceneTask::switchCmdAnalysis( switchFlg );
#endif
}


		



