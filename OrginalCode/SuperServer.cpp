#include "SuperServer.h"
#include "base/baseFunc.h"
#include "base/baseSqlHandle.h"
#include "base/baseSqlPool.h"
#include "base/baseSqlHandle.h"
#include "base/baseThread.h"

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
	if( !handle )
	{
		return false;
	}
	std::ostringstream streamInst;
	streamInst << "TYPE=" << SUPERSERVER;
	Record column,where;
	where.put( "type",streamInst.str() );
	RecordSet *recordSet = handle->exeSelect( "SERVERLIST",NULL,&where );
	if( recordSet && recordSet->size() == 1 )
	{
		strncpy( m_ip,( const char* )recordSet->get( 0 )->getValue( "ip" ),strlen( m_ip ) );
		m_serverID = recordSet->get( 0 )->getValue( "id" );
		strncpy( name,( const char* )recordSet->get( 0 )->getValue( "name" ),sizeof( name ) );
		m_port = ( WORD )recordSet->get( 0 )->getValue( "port" );
		m_outPort = ( WORD )recordSet->get( 0 )->getValue( "outPort" );
	}
	else if( !recordSet || recordSet->empty() )
	{
		m_outPort = Global::config["port"];
		column.put( "id",m_serverID );
		column.put( "name",this->name );
		column.put( "ip",m_ip );
		column.put( "port",m_port );
		column.put( "type",m_serverType );
		column.put( "outIP",m_outIP );
		column.put( "outPort",m_outPort );
		if( ( unsigned int ) -1 == handle->exeInsert( "SERVERLIST",&column ) )
		{
			DELETE( recordSet );
			s_mySqlPool->putHandle( handle );
			return false;
		}
	}
	else
	{
		DELETE( recordSet );
		s_mySqlPool->putHandle( handle );
		return false;
	}
	DELETE( recordSet );
	s_mySqlPool->putHandle( handle );
	return true;
}

void SuperServer::setZoneID( const GameZone &gameZone )
{
	char home[256];
	strncpy( home,getenv( "HOME" ),256 );
	std::ostringstream oss;
	char buf[128];
	oss << home << "/.zoneid";
	int fd = 0;
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
	switchAnalysis( ( std::string )Global::config["cmdswitch"] == "true" );
	s_mySqlPool = new MysqlPool();
	if( !s_mySqlPool || !s_mySqlPool->putUrl( 0,Global::config["mysql"] ) )
	{
		Global::logger->debug( "管理服务器连接数据库失败:%s",(const char*)Global::config["mysql"] ); 
		return false;
	}
#if 0
	strncpy( m_ip,Socket::getIPByIfName( Global::config["ifname"] ),MAX_IP_LENGTH - 1 );
#endif
	if( !getServerInfo() )
	{
		return false;
	}
	m_taskPool = new TcpTaskPool( Global::config["threadPoolCapacity"] );
	if( !m_taskPool || !m_taskPool->init() )
	{
		return false;
	}
	m_clientPool = new TcpClientTaskPool( 50,50000 );
	if( !m_clientPool || !m_clientPool->init() )
	{
		return false;
	}
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
#if 0
	if( !SuperTimerTick::getInstance().start() )
	{
		return false;
	}
#endif
#if 0
	SuperChangeYuanbaoManager::getInstance().init( mysqlPool );
#endif
	if( NetService::init( m_port ) )
	{
		return false;
	}
	return true;
}

void SuperServer::newTcpTask( const int sock,const struct sockaddr_in *addr )
{
#if 0
	SuperTask *tcpTask = new SuperTask( sock,addr );
	if( !tcpTask )
	{
		TEMP_FAILURE_RETRY( ::close( sock ) );
	}
	else if( !m_taskPool->addVerity( tcpTask ) )

	{
		DELETE( tcpTask );
	}
#endif
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



