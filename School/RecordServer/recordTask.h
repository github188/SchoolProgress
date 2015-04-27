#ifndef RECORD_TASK_H
#define RECORD_TASK_H

#include "base/baseTcpTaskQueue.h"
#include "base/baseLock.h"
#include "base/baseTime.h"

class RecordTask : public TcpTaskQueue
{
	public:
		enum Recycle_State
		{
			RS_First,
			RS_Second,
			RS_Third,
		};

		RecordTask(const SDWORD sock,const struct sockaddr_in *addr=NULL);
		~RecordTask() {};
		const char* getClassName() const
		{
			return "RecordTask";
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
	private:
		Recycle_State m_recycleState;
		bool m_verify;
		DWORD m_recycleTime;
		Timer m_sequenceTimer;
};

#endif
