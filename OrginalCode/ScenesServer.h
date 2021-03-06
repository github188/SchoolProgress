#ifndef SCENES_SERVER_H
#define SCENES_SERVER_H

class ScenesServer : public SubNetService
{
	private:
		friend class SingletonBase<Service,false>;
		ScenesServer();
		~ScenesServer();
	public:
		static ScenesServer &getInstance()
		{
			return Service::getInstance<ScenesServer>();
		}
		void reloadConfig();
		bool init();
		void final();
		void startUpOver();
		void finalSave();
		void newTcpTask(const int sock,const struct sockaddr_in *addr);
		bool msgParse_SuperService(const Cmd::NullCmd *nullCmd,const DWORD cmdLen);
		bool msgParse_ZoneService(const Cmd::NullCmd *nullCmd,const DWORD cmdLen);
		bool msgParse_FLServer(const Cmd::NullCmd *nullCmd,const DWORD cmdLen);
		bool msgParse_ChatServer(const Cmd::NullCmd *nullCmd,const DWORD cmdLen);
		bool msgParse_NameServer(const Cmd::NullCmd *nullCmd,const DWORD cmdLen);
		bool msgParse_GMServer(const Cmd::NullCmd *nullCmd,const DWORD cmdLen);
		bool msgParse_UserServer(const Cmd::NullCmd *nullCmd,const DWORD cmdLen);
		bool msgParse_InfoServer(const Cmd::NullCmd *nullCmd,const DWORD cmdLen);
	public:
		static WORD s_serverSequence;
		static WORD s_serverCount;
	private:
		static bool s_reloadConfig;
	public:
		void checkAndReloadConfig();
		static void globalInit();
		static DWORD s_online;
		static bool s_waitFinal;
		static bool s_initOK;
		static bool s_checkMove;
		static bool s_openElemEffect;
		bool m_antiaddiceCheck;
	private:
		void switchAnalysis(const bool switchFlg);
		bool initConfig();
	public:
		typedef SceneTimeTick TimeTick;
};

#endif
		

