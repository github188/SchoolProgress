#ifndef BASE_TCP_TASK_H
#define BASE_TCP_TASK_H
class TcpTask : public Entry,public MessageQueue<false>
{
	public:
		enum TerminateMethod
		{
			terminate_no,
			terminate_active,
			terminate_passive,
		};
		TcpTask(const SWORD sock,const struct sockaddr_in *addr = NULL,const bool compress = false);
		virtual ~TcpTask()
		{
		}
		void addEpoll(SWORD kdpfd,__uint32_t events,void *ptr)
		{
			mSocket.addEpoll(kdpfd,events,ptr);
		}
		void delEpoll(SWORD kdpfd,__uint32_t events)
		{
			mSocket.delEpoll(kdpfd,events);
		}
		bool checkVerifyTimeout(const Time &ct,const QWORD interval = 4000L) const
		{
			if(!_check_timeout)
			{
				return false;
			}
			return lifeTime.elapse(ct) > interval;
		}
		bool isFdsrAdd() const
		{
			return fdsradd;
		}
		bool fdsrAdd()
		{
			fdsradd = true;
			return fdsradd;
		}
		bool verifyLogin(const Cmd::Server::stLoginStartServerCmd *ptCmd);
		virtual SWORD verifyConn();
		virtual SWORD waitSync()
		{
			return 1;
		}

		virtual SWORD recycleConn()
		{
			return 1;
		}
		virtual void addToContainer()
		{
		}
		virtual void removeFromContainer()
		{
		}
		virtual bool uniqueAdd()
		{
			return true;
		}
		virtual bool uniqueRemove()
		{
			return true;
		}
		void setUnique()
		{
			uniqueVerified = true;
		}
		bool isUnique() const
		{
			return uniqueVerified;
		}
		bool isVerminateWait()
		{
			return terminate_wait;
		}
		void terminaterWait()
		{
			terminate_wait = true;
		}
		bool isTerminate() const
		{
			return terminate_no != terminate;
		}
		virtual void Terminate(const TerminateMethod method = terminate_passive)
		{
			terminate = method;
		}
		virtual bool TerminateError()
		{
			return true;
		}
		virtual bool parse(const Cmd::t_NullCmd *ptNullCmd,const DWORD cmdLen) = 0;
		virtual bool sendCmd(const void *pstrCmd,SWORD cmdLen);
		bool sendCmdNoPack(const void *pstrCmd,SWORD cmdLen);
		virtual bool listeningRecv(bool needRecv);
		virtual bool listeningSend();
		enum TCPTASK_State
		{
			notuse = 0,
			verify = 1,
			sync = 2,
			okey = 3,
			recycle = 4
		};
		const TCPTASK_State getState() const
		{
			return state;
		}
		void setState(const TCPTASK_State state)
		{
			this->state = state;
		}
		void getNextState();
		void resetState();
		const char* getStateString(const TCPTASK_State state) const
		{
			const char *retval = NULL;
			switch(state)
			{
				case notuse:
					retval = "notuse";
					break;
				case verify:
					retval = "verify";
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
				default:
					retval = "none";
					break;
			}
			return retval;
		}
		const WORD getPort() const
		{
			return mSocket.getPort();
		}
		const char* getIP() const
		{
			return mSocket.getIP();
		}
		const DWORD getAddr() const
		{
			return mSocket.getAddr();
		}
		const bool ifCheckSignal() const
		{
			return _checkSignal;
		}
		bool checkInterval(const Time &ct)
		{
			return _tick_timer(ct);
		}
		bool checkTick() const
		{
			return tick;
		}
		void clearTick()
		{
			tick = false;
		}
		const DWORD getID() const
		{
			return id;
		}
		const DWORD getType() const
		{
			return taskType;
		}
		void setTick()
		{
			tick = true;
		}
		void checkSignal(const Time &ct);
		bool checkVerifyOK()
		{
			return _verify_state == 1;
		}
		void setCheckTimeout(bool check)
		{
			_check_timeout = check;
		}
	public:
		DWORD taskType;
		bool buffered;
		Socket mSocket;
		TCPTASK_State state;
	private:
		TerminateMethod terminate;
		bool terminate_wait;
		bool fdsradd;
		Tim lifeTime;
		bool uniqueVerfied;
		const bool _checkSignal;
		Timer _tick_timer;
		bool tick;
		SWORD _verify_state;
		bool _check_timeout;
	protected:
		virtual void analysisSendingCmd(BYTE cmd,BYTE param,DWORD size)
		{
		}
		virtual void analysisRecvingCmd(BYTE cmd,BYTE param,DWORD size)
		{
		}
};

#endif
