#include "SuperServer.h"
#include "base/baseFunc.h"
#include "base/baseSqlHandle.h"
#include "base/baseSqlPool.h"
#include "base/baseSqlHandle.h"
#include "base/baseThread.h"
#include "superTimeTick.h"

MysqlPool*  SuperServer::s_mySqlPool = NULL;
SuperServer::SuperServer() : NetService( "服务器管理器" )
{
	m_serverID = 0;
	m_serverType = SUPERSERVER;
	bzero( m_ip,sizeof( m_ip ) );
	m_port = 0;
	bzero( m_outIP,sizeof( m_outIP ) );
	bzero( m_gameZoneStr,sizeof( m_gameZoneStr ) );
	bzero( m_zoneInfoBuff,sizeof( m_zoneInfoBuff ) );
	m_outPort = 0;
	m_clientPool = NULL;
}

SuperServer::~SuperServer()
{
}

bool SuperServer::getServerInfo()
{
	MysqlHandle *handle = s_mySqlPool->getHandle();
	CheckConditonReturn( handle,false );
	
	bool ret = true;
	std::ostringstream temp;
	temp << "TYPE=" << SUPERSERVER;
	Record where;
	where.put( "type",temp.str() );
	RecordSet *recordSet = handle->exeSelect( "SERVERLIST",NULL,&where );
	if( recordSet && recordSet->size() == 1 )
	{
		strncpy( m_ip,recordSet->get( 0 )->getValue( "ip" ),strlen( m_ip ) );
		m_serverID = recordSet->get( 0 )->getValue( "id" );
		strncpy( name,recordSet->get( 0 )->getValue( "name" ),sizeof( name ) );
		m_port = recordSet->get( 0 )->getValue( "port" );
		m_outPort = recordSet->get( 0 )->getValue( "outPort" );
	}
	else
	{
		ret = false;
	}
	DELETE( recordSet );
	s_mySqlPool->putHandle( handle );
	return ret;
}

void SuperServer::setZoneID( const GameZone &gameZone )
{
	char home[256];
	strncpy( home,getenv( "HOME" ),256 );
	std::ostringstream oss;
	char buf[128];
	oss << home << "/.zoneid";
	SDWORD fd = 0;
	if( ( fd = open( oss.str().c_str(),O_CREAT|O_TRUNC|O_WRONLY,0644 ) ) >= 0 )
	{
		snprintf( buf,sizeof( buf ),"-%4d",gameZone.zone );
		write( fd,buf,strlen( buf ) );
	}
	close( fd );
	this->m_gameZone = gameZone;
}

bool SuperServer::init()
{
	s_mySqlPool = new MysqlPool();
	const char *mysql = (const char*)Global::config["mysql"];
	LogErrorCheckCondition( s_mySqlPool && s_mySqlPool->putUrl(0,mysql),false,"管理服务器连接数据库失败%s",mysql ); 
	
	strncpy(m_ip,Socket::getIPByIfName(Global::config["ifname"]),MAX_IP_LENGTH);

	LogErrorCheckCondition( getServerInfo(),false,"管理服务器设置IP和端口错误" );

	m_taskPool = new TcpTaskPool( Global::config["threadPoolCapacity"] );
	LogErrorCheckCondition( m_taskPool && m_taskPool->init(),false,"管理服务器初始化任务池失败" );

	m_clientPool = new TcpClientTaskPool( 50,50000 );
	LogErrorCheckCondition( m_clientPool && m_clientPool->init(),false,"管理服务器初始化客户端连接池失败" );
#if 0
	if( !FLClient::init( m_clientPool ) )
	{
		return false;
	}
	
	if( !MonitorClient::init( m_clientPool ) )
	{
		return false;
	}

	if( !DuDuAppLoaderClient::init( m_clientPool ) )
	{
		return false;
	}

	if( !UserClient::init( m_clientPool ) )
	{
		return false;
	}
	if( !InfoClient::init( m_clientPool ) )
	{
		return false;
	}
	if( !NameClient::init( m_clientPool ) )
	{
		return false;
	}
	if( !PayClient::init( m_clientPool ) )
	{
		return false;
	}
	if( !ZoneClient::init( m_clientPool ) )
	{
		return false;
	}
#endif
	LogErrorCheckCondition( SuperTimeTick::getInstance().start(),false,"管理服务器时间线程启动失败" );
	LogErrorCheckCondition( NetService::init(m_port),false,"管理服务器邦定端口失败%d",m_port );
	return true;
}

void SuperServer::newTcpTask(const SDWORD sock,const struct sockaddr_in *addr)
{
	SuperTask *tcpTask = new SuperTask( sock,addr );
	if(!tcpTask)
	{
		TEMP_FAILURE_RETRY(::close(sock));
	}
	else if(!m_taskPool->addVerify(tcpTask))
	{
		DELETE( tcpTask );
	}
}

void SuperServer::final()
{
#if 0
	Cmd::Server::stShutdownStartServerCmd send;
	SuperTaskManager::getInstance().broadcast( &send,sizeof( send ) );
	while( !SuperUserManager::getInstance().isEmpty() )
	{
		Thread::msleep( 10 );
	}
#endif
#if 0
	SuperTimeTick::getInstance().final();
	SuperTimeTick::getInstance().join();
	SuperTimeTick;:delInstance();
#endif
	if( m_taskPool )
	{
		m_taskPool->final();
		DELETE( m_taskPool );
	}

	if( m_clientPool )
	{
		m_clientPool->final();
		DELETE( m_clientPool );
	}
}

bool SuperServer::sendUserCmdToMonitor( const void *pstrCmd,const DWORD cmdLen )
{
	return true;
#if 0
	_BUFFER_DATACMD( Cmd::Monitor::stUserCmdToAllMonitorForwardMonitorUserCmd,sendCmd )
	sendCmd->num = cmdLen;
	bcopy( pstrCmd,sendCmd->data,cmdLen );
	return MonitorClientManager::getInstance().broadcast( sendCmd,sendCmd->size() );
#endif
}

void SuperServer::reloadConfig()
{
#if 0
	Navy::logger->debug( "%s",__PRETRY_FUNCTION__ );
	ConfigFile conf( "config.xml" );
	conf.parse( "SuperServer" );
	ConfigFile vconf( Navy::global["varconfig"] );
	vconf.parseNodeEx( "SuperServer" );
	switchAnalysis( std;:string ) Navy::global["cmdswitch"] == "true" );
	ChatClient::reload( clientPool );
	FLClient::reload( clientPool );
	GMClient::reload( clientPool );
	GuildClient::reload( clientPool );
	InfoClient::reload( clientPool );
	MonitorClient::reload( clientPool );
	NameClient::reload( clientPool );
	UserClient::reload( clientPool );
	DuDuAppLoaderClient::reload( clientPool );
#endif
}



