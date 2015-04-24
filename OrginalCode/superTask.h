#ifndef SUPER_TASK_H
#define SUPER_TASK_H

#include "base/baseTcpTaskQueue.h"

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
		static RWLock lock;
	private:
		Recycle_State m_recycleState;
		bool m_verify;
		int recycle_time;
		Timer _sequence_timer;
		bool hasNotifyOther;
		bool hasNotifyMe;
		bool hasNotifyMeReturn;
		DWORD serversize;
		DWORD serverReturnSize;
		char psterIP[MAX_IP_LENGTH];
		WORD wdPort;
		char pstrExtIP[MAX_IP_LENGTH];
		WORD wdExtPort;
		bool notifyReturnOK()
		{
			return serversize == serverReturnSize;
		}

};
#endif
