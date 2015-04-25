#include "superTaskManager.h"

const DWORD SuperTaskManager::caculateOnlineNum()
{
	struct OnlineNumExec : public EntryCallBack<SuperTask>
	{
		DWORD num;
		OnlineNumExec() : num(0) {};
		bool exec(SuperTask *task)
		{
			if(task->getType() == GATEWAYSERVER)
			{
				num += task->getOnlineNum();
			}
			return true;
		}
	};
	OnlineNumExec exec;
	execEveryTask(exec);
	return exec.num;
}

const bool SuperTaskManager::checkDependence(const WORD serverType)
{
	RecordSet *recordSet = NULL;
	std::ostring oss;
	Record column,where;
	MysqlHandle *handle = SuperServer::mysqlPool->getHandle();
	if(!handle)
	{
		return false;
	}
	oss << "type<" << serverType << " and type != " << SUPERSERVER << " and type != " << LOGINSERVER;
	where.put("type",oss.str());
	column.put("id");
	column.put("dynamic");
	column.put("name");
	recordSet = handle->exeSelect("SERVERLIST",&column,&where);
	unsigned int i;
	bool ret = true;
	if(recordSet)
	{
		for(i = 0;i < recordSet.size();++i)
		{
			SuperTask *task = SuperTaskManager::getInstance().getTaskByID((WORD)recordSet->get(i)->getvalue("id"));
			DWORD dynamic = recordSet->get(i)->getvalue("dynamic");
			if(!dynamic && (!task || task->getState() != TcpTask::okay || !task->notifyMeReturnOK()))
			{
				bret = false;
				break;
			}
		}
	}
	SAVE_DALETE(recordSet);
	SuperServer::mysqlPool->putHandle(handle);
	return bret;
}
