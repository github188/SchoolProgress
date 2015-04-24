#ifndef BASE_THREAD_MANAGER_H
#define BASE_THREAD_MANAGER_H
#include "baseEntry.h"
#include "baseLock.h"
#include "baseThread.h"
template<typename T>
class TaskThreadManager : public EntryManager<EntryID,EntryNone<2>,EntryNone<3>,true>
{
	private:
		int max_count;
		int min_count;
		RWLock rwlock;
		int getMaxCount()
		{
			return max_count;
		}
		int getMinCount()
		{
			return min_count;
		}
		void setMaxCount(int count)
		{
			max_count = count;
		}
		void setMinCount(int count)
		{
			min_count = count;
		}
	public:
		TaskThreadManager()
		{
			min_count = 0;
			max_count = 0;
		}
		~TaskThreadManager()
		{
		}
		bool init(const int min = 1,const int max = 1,const std::string name = "thread",void *param = NULL)
		{
			setMinCount(min);
			setMaxCount(max);
			bool bret = true;
			rwlock.wrlock();
			for(int index = 0;index < getMaxCount();++index)
			{
				T *thread = new T;
				if(thread)
				{
					thread->initParam(param);
					if(index < getMinCount() && !thread->start())
					{
						DELETE(thread);
						bret = false;
						break;
					}
					if(!addEntry(thread))
					{
						DELETE(thread);
						bret = false;
						break;
					}
				}
				else
				{
					bret = false;
					break;
				}
			}
			rwlock.unlock();
			return bret;
		}
		T* getAverageOne()
		{
			struct GetBest : public EntryCallBack<T>
			{
				T *_thread;
				bool _findFlg;
				GetBest():_thread(NULL),_findFlg(false){}
				bool exec(T *thread)
				{
					if(!thread->isAlive())
					{
						if(!thread->start())
						{
							return false;
						}
						_findFlg = true;
						_thread = thread;
					}
					if(!_thread || (thread->taskSize() < _thread->maxTaskSize()))
					{
						_thread = thread;
					}
					return true;
				}
			};
			GetBest exec;
			rwlock.rdlock();
			execEveryEntry<T>(exec);
			rwlock.unlock();
			return exec._thred;
		}
		T *getOne()
		{
			struct GetBest : public EntryCallBack<T>
			{
				T *_thread;
				GetBest():_thread(NULL){}
				bool exec(T *thread)
				{
					if(!thread->isAlive())
					{
						if(!thread->start())
						{
							return false;
						}	
					}
					if(thread->taskSize() < thread->maxTaskSize())
					{
						_thread = thread;
						return false;
					}
					return true;
				}
			};
			GetBest exec;
			rwlock.rdlock();
			execEveryEntry<T>(exec);
			rwlock.unlock();
			return exec._thread;
		}
		int taskCount()
		{
			struct GetBest : public EntryCallBack<T>
			{
				int _size;
				GetBest():_size(0){}
				bool exec(T *thread)
				{
					_size += thread->taskSize();
					return true;
				}
			};
			GetBest exec;
			rwlock.rdlock();
			execEveryEntry<T>(exec);
			rwlock.unlock();
			return exec._size;
		}
		void final()
		{
	#if 0
			struct RemoveAll:public removeEntry_Pred<T>
			{
				bool isIt(T *entry)
				{
					if(entry)
					{
						entry->final();
						entry->join();
					}
					return true;
				}
			};
			rwlock.wrlock();
			RemoveAll exec;
			removeEntry_if<T>(exec);
			rwlock.unlock();
	#endif
		}
	
		template<class YourEntry>
		bool execEvery(EntryCallBack<YourEntry> &exec)
		{
			rwlock.rdlock();
			bool ret = execEveryEntry<>(exec);
			rwlock.unlock();
			return ret;
		}
		bool addThread(Thread *entry)
		{
			bool bret = false;
			rwlock.wrlock();
			bret = addEntry(entry);
			return bret;
		}
		void removeThread(Thread *entry)
		{
			rwlock.wrlock();
			removeEntry(entry);
			rwlock.unlock();
		}
		T* getThreadByID(const WORD id)
		{
			T *ret = NULL;
			rwlock.rdlock();
			ret = (T*)getEntryByID(id);
			return ret;
		}
};

#endif
		

