#include <ext/pool_allocator.h>

int TcpClientTaskThread::maxConns = 20;
void CheckConnectThread::_add( TcpClientTaskBase *task )
{
	tasks.push_back( task );
}

int CheckConnectThread::taskSize() const
{
	return tasks.size();
}
int CheckConnectThread::maxTaskSize() const
{
	return maxConns;
}
void CheckConnectThread::initParam( void *param )
{
	pool = (TcpClientTaskPool *)param;
}
void CheckConnectThread::run()
{
	while( !isFinal() )
	{
		this->setRunning();
		Thread::sleep( 1 );
		Time ct;
		check_queue();
		for( TcpClientTaskBase_IT it = tasks.begin();it != tasks.end(); )
		{
			TcpClientTaskBase *task = *it;
			if( !task->checkStateTimeout( TcpClientTaskBase::close,ct,4 ) )
			{
				if( task->connect() )
				{
					pool->addCheckWait( task );
				}
				else if( !task->needReConn() )
				{
					TcpClientTaskBase_IT temp = it;
					++it;
					tasks.erase( temp );
					task->resetState();
					SAFE_DELETE( task );
					continue;
				}
			}
			break;
		case TcpClientTaskBase::sync:
			break;
		case TcpClientTaskBase::recycle:
			if( task->checkStateTimeout( TcpClientTaskBase::recycle,ct,4 ) )
			{
				task->getNextState();
				if( !task->needReConn() )
				{
					TcpClientTaskBase_IT temp = it;
					++it;
					tasks.erase( temp );
					SAFE_DELETE( task );
					continue;
				}
			}
			break;
		}
		++it;
	}
}
