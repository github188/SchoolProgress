#ifndef SUPER_TASK_H
#define SUPER_TASK_H

#include "base/baseTcpTaskQueue.h"
#include "base/baseLock.h"
#include "base/baseTime.h"

class SuperTask : public TcpTaskQueue
{
	public:
		enum Recycle_State
		{
			RS_First,
			RS_Second,
			RS_Third,
		};

		SuperTask(const SDWORD sock,const struct sockaddr_in *addr=NULL);
		~SuperTask() {};
		const char* getClassName() const
		{
			return "SuperTask";
		}
		bool notifyReturnOK()
		{
			return m_serverSize == m_serverReturnSize;
		}
		bool notifyMeReturnOK()
		{
			return m_hasNotifyMeReturn;
		}
		void notifyReturn()
		{
			++m_serverReturnSize;
		}
		bool checkRecycle();
		SDWORD verifyConnect();
		SDWORD  waitSync();
		SDWORD recycleConnect();
		bool uniqueAdd();
		bool uniqueRemove();
		bool msgParseStart(const Cmd::NullCmd *cmd,const DWORD cmdLen);
		bool msgParseForward(const Cmd::NullCmd *cmd,const DWORD cmdLen);
		bool msgParse(const Cmd::NullCmd *cmd,const DWORD cmdLen);
	public:
		DWORD m_protocol;
		DWORD m_buildTime;
		DWORD m_svnVersion;
		static RWLock s_lock;
	private:
		Recycle_State m_recycleState;
		bool m_verify;
		DWORD m_recycleTime;
		Timer m_sequenceTimer;
		bool m_hasNotifyOther;
		bool m_hasNotifyMe;
		bool m_hasNotifyMeReturn;
		DWORD m_serverSize;
		DWORD m_serverReturnSize;
		char m_ip[MAX_IP_LENGTH];
		WORD m_port;
		char m_outIP[MAX_IP_LENGTH];
		WORD m_outPort;
	private:
		bool verify(const DWORD serverType,const char *ip);
		bool notifyOther();
		bool notifyMe();
};
#endif
