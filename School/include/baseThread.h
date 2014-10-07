#ifndef BASE_THREAD_H
#define BASE_THREAD_H

#include <signal.h>
#include <bits/atomicity.h>
#include "baseLock.h"
#include "baseEntry.h"

class Thread : public Entry
{
	private:
		static void *threadProc(void *arg);
		virtual void run() = 0;
	public:
		virtual void initParam(void *arg)
		{
		}
		Thread(const char *name,bool joinable = true);
		virtual ~Thread();
		const char* getClassName()
		{
			return "线程";
		}
		void mysqlInit();
		void mysqlDestroy();
		bool start();
		bool checkRunning();
		inline void setRuning()
		{
			_running = true;
		}
		pthread_t getThreadID();
		void join();
		const bool isJoinable() const;
		void final();
		const bool isAlive() const;
		const bool isFinal() const;
		static void sleep(const long sec);
		static void msleep(long millis);
		static void usleep(const long usec);
		static pthread_t getCurrentThreadId();
		static long atomicAdd(volatile long *val,long x);
		static long atomicInc(volatile long *val);
		static long atomicDec(volatile long *val);
	private:
		Mutex mlock;
		Condition cond;
		bool _joinable;
		pthread_t _thread;
		volatile bool _alive;
		volatile bool _complete;
		volatile bool _running;
		static long _tempid;
};

class ThreadManager : public EntryManager<EntryID,EntryNone<2>,EntryNone<3>,true>,public SingletonBase<ThreadManager>
{
	private:
		friend class SingletonBase<ThreadManager>;
		ThreadManager();
		~ThreadManager();
	public:
		bool addThread(Thread *entry);
		void removeThread(Thread *entry);
		template<class YourEntry>
		bool execEveryThread(EntryCallBack<YourEntry> &exec)
		{
			bool ret = false;
			rwlock.rdlock();
			ret = execEveryEntry<>(exec);
			rwlock.unlock();
			return ret;
		}
	private:
		RWLock rwlock;
};



#endif
