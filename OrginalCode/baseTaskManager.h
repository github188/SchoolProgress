#ifndef BASE_TASK_MANAGER_H
#define BASE_TASK_MANAGER_H

template<typename T>
class TaskManager : public EntryManager<IndexID>
{
	public:
		TaskManager() {};
		~TaskManager() {};
		bool addTask(T *task)
		{
			rwlock.wrlock();
			bool bret = addEntry(task);
			rwlock.unlock();
			return bret;
		}
		void removeTask(T *task)
		{
			rwlock.wrlock();
			removeEntry(task);
			rwlock.unlock();
		}
		DWORD getSize()
		{
			return size();
		}
		T *getTaskByID(const DWORD id)
		{
			rwlock.rdlock();
			T *ret = (T*)getEntryByID(id);
			rwlock.unlock();
			return ret;
		}
		DWORD getTaskSizeByType(const DWORD taskType)
		{
			struct GetTaskCountExec : Callback<T>
			{
				const DWORD _task_type;
				BYTE _size;
				GetTaskCountExec(const DWORD taskType) : _task_type(taskType),_size(0)
				{
				}
				bool exec(T *entry)
				{
					if(entry->getType() == _task_type)
					{
						++_size;
					}
					return true;
				}
			}exec(taskType);

			execEveryTask(exec);
			return exec._size;
		}
		bool uniqueVerify(const DWORD id)
		{
			return NULL == getTaskByID(id);
		}
		bool uniqueAdd(T *task)
		{
			return addEntry(task);
		}
		bool uniqueRemove(T *task)
		{
			removeTask(task);
			return true;
		}
		bool broadcast(const void *pstrcmd,const int cmdLen)
		{
			struct BroadCast : public Callback<T>
			{
				const void *_pstrcmd;
				const int _cmdLen;
				BroadCast(const void *pstrcmd,const int cmdLen) : _pstrcmd(pstrcmd),_cmdLen(cmdLen)
				{
				}
				bool exec(T *task)
				{
					task->sendCmd(_pstrcmd,_cmdLen);
					return true;
				}
			};
			BroadCast exec(pstrcmd,cmdLen);
			execEveryTask(exec);
			return true;
		}
		bool brocastToID(const DWORD serverID,const void *pstrcmd,const int cmdLen)
		{
			bool ret = false;
			rwlock.rdlock();
			T *task = (T*)getEntryByID(serverID);
			if(task)
			{
				ret = task->sendCmd(pstrcmd,cmdLen);
			}
			rwlock.unlock();
			return ret;
		}
		bool broadcastToTypeExceptOne(const DWORD type,const DWORD except,const void *pstrcmd,const int cmdLen)
		{
			struct BroadCast : public Callback<T>
			{
				const void *_pstrcmd;
				const int _cmdLen;
				const DWORD _type;
				const DWORD _except;
				BroadCast(const void *pstrcmd,const int cmdLen,const DWORD type,const DWORD except) : _pstrcmd(pstrcmd),_cmdLen(cmdLen),_type(type),_except(except)
				{
				}
				bool exec(T *task)
				{
					if(task->getType() == _type && task->id != _except)
					{
						task->sendCmd(_pstrcmd,_cmdLen);
					}
					return true;
				}
			};
			BroadCast exec(pstrcmd,cmdLen,type,except);
			execEveryTask(exec);
			return true;
		}
		template<typename YourEntry>
		bool execEveryTask(Callback<YourEntry> &callback)
		{
			rwlock.rdlock();
			bool ret = execEveryEntry<>(callback);
			rwlock.unlock();
			return bret;
		}
	protected:
		RWLock rwlock;
};

#endif
