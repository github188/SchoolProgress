#include "scenesServer.h"
#include "base/baseProperty.h"
#include "base/testAutoPtr.h"

bool ScenesServer::s_reloadConfig = false;
bool ScenesServer::s_initOK = false;
bool ScenesServer::s_waitFinal = false;
bool ScenesServer::s_checkMove = true;
bool ScenesServer::s_openElemEffect = true;

WORD ScenesServer::s_serverSequence = 0;
WORD ScenesServer::s_serverCount = 0;

ScenesServer::ScenesServer() : SubNetService( "Scene",SCENESSERVER ),m_antiaddiceCheck( false )
{
}

ScenesServer::~ScenesServer()
{
}

bool ScenesServer::init()
{
	Time time;
	time.now();
	switchAnalysis( ( std::string )Global::config["cmdswitch"] == "true");
	m_antiaddiceCheck = ( std::string )Global::config["antiaddict"] == "true";

	m_taskPool = new TcpTaskPool( ( DWORD )Global::config["threadPoolSize"],5000 );
	if( !m_taskPool || !m_taskPool->init() )
	{
		return false;
	}
	if( !SubNetService::init() )
	{
		return false;
	}
# if 0
	const ServerEntry *serverEntry = NULL;
	serverEntry = getServerEntryByType(RECORDSERVER);
	if( !serverEntry )
	{
		return false;
	}
	recordClient = new RecordClient("档案服务器",serverEntry->exip,serverEntry);
	if(!recordClient)
	{
		return false;
	}

	if(!recordClient->connectToRecordServer())
	{
		return false;
	}

	if(recordClient->start())
	{
		Global::logger->info("初始化Record服务器模块( %s:%u )成功",serverEntry->pstrExpIP,serverEntry->Export);
	}

	serverEntry = getServerEntryByType( SESSIONSERVER );
	if( !serverEntry )
	{
		return false;
	}

	sessionClient = new SessionClient( "Session服务器",serverEntry->pstrExtIP,serverEntry->extport);
	if( !sessionClient )
	{
		return false;
	}
	if( !sessionClient->connectToSessionServer() )
	{
		return false;
	}
	if( sessionClient->start() )
	{
		Global::logger->info("初始化session服务器模块( %s:%u ) 成功",serverEntry->outNetIP,serverEntry->outNetPort);
	}

	if( !initConfig() )
	{
		return false;
	}

	if( SceneTimeTick::getInstance().start() )
	{
		Global::logger->info("初始化TimeTick服务器模块成功");
	}
	else
	{
		return false;
	}

	if( MonitorThread::getInstance().start() )
	{
		Global::logger->info("初始化监控服务器模成功");
	}
	else
	{
		return false;
	}
	startUpOK();
	
	srand( SceneTimeTick::currentTime.sec() );

	s_initOK = true;
#endif
	return true;
}

void ScenesServer::startUpOver()
{
#if 0
	Cmd::Session::stRequestInitGameSceneSessionCmd request;
	sessionClient->sendCmd( &request,sizeof( request ) );
	SubNetService::startUpOver();
#endif
}

void ScenesServer::newTcpTask( const int sock,const struct sockaddr_in *addr )
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

bool ScenesServer::msgParse_InfoServer( const Cmd::NullCmd *nullCmd,const DWORD cmdLen)
{
#if 0
	if( !SceneAdminToolMgr::getInstance().msgParse( nullCmd,cmdLen ) )
	{
		return SubNetService::msgParse_InfoServer( nullCmd,cmdLen );
	}
#endif
	return true;
}

bool ScenesServer::msgParse_SuperService( const Cmd::NullCmd *nullCmd,const DWORD cmdLen )
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

void ScenesServer::finalSave()
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
void ScenesServer::final()
{
	s_waitFinal = true;
	while( s_initOK && s_waitFinal && !SceneTimeTick::getInstance().isFinal() )
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

#if 0
static struct argp_option scenes_options[] =
{
	{"daemon",'d',0,0,"Run service as daemon",0},
	{"log",'1',"level",0,"Log level",0},
	{"logfilename",'f',"filename",0,"Log file name",0},
	{"mysql",'y',"mysql",0,"MySQL[mysql://user:passwd@host:port/dbName]",0},
	{"ifname",'i',"ifname",0,"Local network device",0},
	{"server",'s',"ip",0,"Super server ip address",0},
	{"port",'p',"port",0,"Super server port number",0},
	{"info",'n',0,0,"show info",0},
	{0,0,0,0,0,0}
};
#endif
static error_t scenes_parse_opt( int key,char *arg,struct argp_state *state )
{
#if 0
	switch( key )
	{
		case 'd':
			{
				Navy::global["daemon"] = "true";
			}
			break;
		case 'p':
			{
				Navy::global["port"] = arg;
			}
			break;
		case 's':
			{
				Navy::global["server"] = arg;
			}
			break;
		case 'l':
			{
				Navy::global["logfilename"] = arg;
			}
			break;
		case 'f':
			{
				Navy::global["logfilename"] = arg;
			}
			break;
		case 'y':
			{
				Navy::global["mysql"] = arg;
			}
			break;
		case 'i':
			{
				Navy::global["ifname"] = arg;
			}
			break;
		case 'n':
			{
				std::cout<<"编译选项:\t"<<"DEBUG_STRING"<<'\n';
				std::cout<<"GM模式开关:\t"<<( const char * )Navy::global["gm_mode"]<<'\n';
				if( !strcmp( "_ALL_SUPER_GM","DEBUG_STRING" ) && Navy::global["gm_mode"] )
				{
					std::cout<<"现在所有人都是\tdebug_mode\n";
				}
				else
				{
					std::cout<<"现在是\t\t正常模式\n";
				}
				exit( 0 );
			}
			break;
		default:
			return ARGP_ERR_UNKNOWN;
	}
#endif
	return 0;
}
#if 0
static char scenes_doc[] = "\nScenesServer\n" "\t场景服务器.";

const char *arpg_program_version = "Program version :\t" "VERSION_STRING" "\Bulid version :\t" "_S( BUILD STRING )" "\Build time :\t" __DATE__","__TIME__;
#endif
void ScenesServer::reloadConfig()
{
	s_reloadConfig = true;
}

void ScenesServer::checkAndReloadConfig()
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
	TestAutoPtr *ptr = new TestAutoPtr( 1,2 );
	SafePtr autoPtr = ptr->getWeakPtr();
	if( !autoPtr.expired() )
	{
		TestAutoPtr *hui = (TestAutoPtr*)autoPtr.lock().get();
		cout<< "testA:" << hui->getA() << "testB:" << hui->getB() << endl;
	}
	delete ptr;
	ptr = NULL;
	if( !autoPtr.expired() )
	{
		TestAutoPtr *hui = (TestAutoPtr*)autoPtr.lock().get();
		cout<< "testAa:" << hui->getA() << "testBb:" << hui->getB() << endl;
	}

	struct timespec ts;
	clock_gettime( CLOCK_REALTIME,&ts );
	DWORD begin_time = ts.tv_sec * 1000 + ts.tv_nsec / 1000000;
	Global::logger = new Logger( "SC" );
	Global::config["cmdswitch"] = "true";

	Global::logger->setLevel( (const char* )Global::config["LoggerLevel"] );
	if( strlen( Global::config["logfilename"] ) )
	{
		Global::logger->setFile( ( const char* )Global::config["logfilename"] );
	}
	if( strcmp( "true",Global::config["daemon"] ) )
	{
		Global::logger->info( "Program will be run as a daemon" );
		Global::logger->removeConsole();
		daemon( 1,1 );
	}
	ScenesServer::newInstance<ScenesServer>();
	ScenesServer::getInstance().loop();

	return EXIT_SUCCESS;
}

void ScenesServer::switchAnalysis( bool switchFlg )
{
#if 0
	SessionClient::switchCmdAnalysis( switchFlg );
	RecordClient::switchCmdAnalysis( switchFlg );
	SceneTask::switchCmdAnalysis( switchFlg );
#endif
}


		



