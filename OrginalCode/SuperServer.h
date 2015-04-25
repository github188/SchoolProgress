#ifndef SUPER_SERVER_H
#define SUPER_SERVER_H

#include "base/baseNetService.h"
#include "base/baseSubService.h"
#include "base/baseTcpClientTaskPool.h"
#include "base/baseSqlRecord.h"

class SuperServer : public NetService
{
	private:
		friend class SingletonBase<Service,false>;
		SuperServer();
		~SuperServer();
	public:
		static SuperServer &getInstance()
		{
			return Service::getInstance<SuperServer>();
		}
		void reloadConfig();
		const GameZone& getZoneID() const
		{
			return gameZone;
		}
		void setZoneID( const GameZone &gameZone );
		const std::string& getZoneName()
		{
			return m_zoneName;
		}
		void setZoneName( const char *zoneName )
		{
			m_zoneName = zoneName;
		}
		const WORD getID() const
		{
			return m_serverID;
		}
		const WORD getType() const
		{
			return m_serverType;
		}
		const char* getIP() const
		{
			return m_ip;
		}
		const WORD getPort() const
		{
			return m_port;
		}
		TcpClientTaskPool* getClientPool()
		{
			return m_clientPool;
		}
		static MysqlPool *s_mySqlPool;
		char m_zoneInfoBuff[Socket::MAX_DATASIZE];
		Cmd::Chat::stZoneInfoListLoginChatCmd *m_zoneInfoCmd;
		char m_gameZoneStr[16];
		DWORD m_serialNum;
		BYTE startDuduMark;
		GameZone m_duduGameZone;
		std::map<DWORD,std::string> m_accountInfo;
	private:
		TcpClientTaskPool *m_clientPool;
		GameZone m_gameZone;
		std::string m_zoneName;
		WORD m_serverID;
		WORD m_serverType;
		char m_ip[MAX_IP_LENGTH];
		WORD m_port;
		char m_outIP[MAX_IP_LENGTH];
		WORD m_outPort;
	private:
		bool init();
		void newTcpTask( const int sock,const struct sockaddr_in *addr );
		void final();
		bool getServerInfo();
	public:
		bool sendUserCmdToMonitor( const void *strCmd,const DWORD cmdLen );
};

#endif

		
