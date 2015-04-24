#ifndef BASE_TASK_QUEUE_MANAGER_H
#define BASE_TASK_QUEUE_MANAGER_H

template<typename T>
class TaskQueueManager : public TaskManager<T>
{
	public:
		TaskQueueManager() {};
		virtual ~TaskQueueManager() {};
		void doCmd()
		{
			struct DoCmdExec : public EntryCallBack<T>
			{
				struct DoCmdExec() {}
				bool exec(T *task)
				{
					if(!task->checkRecycle())
					{
						task->doCmd();
					}
					return true;
				}
			};
			DoCmdExec exec;
			execEveryTask(exec);
		}
};

#endif
		}

