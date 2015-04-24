#ifndef SUPER_TASK_MANAGER_H
#define SUPER_TASK_MANAGER_H

#include "base/baseTaskManager.h"
#include "base/baseClass.h"

class SuperTask;
class SuperTaskManager : public TaskQueueManager,public SingletonBase<SuperTaskManager>
{
	private:
		friend class SingletonBase<SuperTaskManager>;
		SuperTaskManager() {};
		~SuperTaskManager() {};
	public:
		const DWORD caculateOnlineNum();
		const bool checkDependence(const WORD serverType);
};
#endif
