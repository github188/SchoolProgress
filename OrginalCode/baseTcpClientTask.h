#ifndef BASE_TCP_CLIENT_TASK_H
#define BASE_TCP_CLIENT_TASK_H

#include "baseTcpTask.h"

class TcpClientTaskBase : public Entry
{
	public:
		enum TerminateMethod
		{
			TM_no,
			TM_sock_error,
			TM_server_close
		};
		enum ConnState
		{
			close = 0,
			sync = 1,
			okay = 2,
			recycle = 3,
		};
		TcpClientTaskBase( const std::string &ip,const DWORD port,const bool compress = false,const reConn = true,const DWORD reConnTimer = 60*1000L );
		virtual ~TcpClientTaskBase()
		{
			final();
		}
		void final()
		{
			DELETE (pSocket );
			terminate = TM_no;
			mainloop = false;
		}
		bool isTerminate() const
		{
			return TM_no != terminate;
		}
		void Terminate(const TerminateMethod method )
		{
			terminate = method;
		}
		bool checkFirstMainLoop()
		{
			if(mainloop)
			{
				return false;
			}
			mainloop = true;
			return true;
		}
		const ConnState getState() const
		{
			return state;
		}
		void setState(const ConnState state)
		{
			this->state = state;
		}
		bool isOkay() const
		{
			return getState() == okay;
		}
		const DWORD getID() const
		{
			return id;
		}
		const DWORD getType() const
		{
			return taskType;
		}
		const char* getStateString(const ConnState state)
		{
			const char *retval = NULL;
			switch(state)
			{
				case close:
					retval = "close";
					break;
				case sync:
					retval = "sync";
					break;
				case okay:
					retval = "okay";
					break;
				case recycle:
					retval = "recycle";
					break;
			}
			return retval;
		}
		voidaddEpoll(int kdpfd,__uint32_t events,void *ptr)
		{
			if(pSocket)
			{
				pSocket->addEpoll(kdpfd,events,ptr);
			}
		}
		void delEpoll(int kdpfd,__uint32_t events)
		{
			if(pSocket)
			{
				pSocket->delEpoll(kdpfd,events);
			}
		}
		bool checkStateTimeOut(const ConnState state,const Time &ct,const DWORD timeout)
		{
			if(state == this->state)
			{
				if(lifeTime.elape(ct) >= timeout*1000L)
				{
					lifeTime = ct;
					return true;
				}
			}
			return false;
		}
		virtual int checkRebound()
		{
			return 1;
		}
		virtual void recycleConn()
		{
		}
		virtual void addToContainer()
		{
		}
		virtual void removeFromContainer()
		{
		}
		virtual bool connect();
		void checkConn();
		bool sendCmd(const void *cmd,const int cmdLen);
		virtual bool sendLoginCmd();
		bool ListeningRecv(bool needRecv);
		bool ListeningSend();
		void getNextState();
		void resetState();
		bool needReConn()
		{
			return reConn;
		}
		const WORD getPort() const
		{
			return pSocket->getPort();
		}
		const char* getIP() const
		{
			return pSocket->getIP();
		}
		const DWORD getAddr() const
		{
			return pSocket->getAddr();
		}
		bool isFdsrAdd()
		{
			return fdsradd;
		}
		bool fdsrAdd(bool set=true)
		{
			fdsradd = set;
			return fdsradd;
		}
		virtual bool parse(const Cmd::t_NullCmd *ptNukkCmd,const DWORD cmdLen) = 0;
		virtual void onReconnect();
	protected:
		DWORD taskType;
		Socket *pSocket;
		volatile ConnState state;
		bool checkTick() const
		{
			return tick;
		}
		void clearTick()
		{
			tick = false;
		}
		void setTick()
		{
			tick = true;
		}
		void resetTickTimer(DWORD howLong);
	private:
		bool fdsradd;
		const bool compress;
		const bool reConn;
		const std::string ip;
		const DWORD port;
		Time lifeTime;
		TerminateMethod terminate;
		volatile bool mainloop;
		Timer _tick_timer;
		bool tick;
	private:
		virtual void analysisSendingCmd(BYTE cmd,BYTE param,DWORD size) {};
		virtual void analysisRecvingCmd(BYTE cmd,BYTE param,DWORD size) {};

};

#endif

