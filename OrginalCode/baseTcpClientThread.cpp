#include "baseTcpTaskThread.h"

class TcpClientTaskPool;
typedef std::list<TcpClientTaskBase*,__gnu_cxx::__pool_alloc<TcpClientTaskBase*> >TcpClientTaskBaseContainer;

typedef std::queue<TcpClientTaskBase*,std::deque<TcpClientTaskBase*,__gnu_cxx::__pool_alloc<TcpClientTaskBase*> >TcpClientTaskBaseQueue;

typedef TcpClientTaskBaseContainer::iterator TcpClientTaskBase_IT;

typedef std::vector<struct epoll_event> epollfdContainer;


TcpClientTaskThread::TcpClientTaskThread() : Thread( "工作线程" )
{
	m_TaskCnt = 0;
	m_kdpfd = epoll_create( m_maxConCnt );
	assert( -1 != m_kdpfd );
	m_epfds.resize( m_maxConCnt );
}

void TcpClientTaskThread::setMaxSize( DWORD perThreadSize )
{
	m_maxConCnt = perThreadSize;
}

int TcpClientTaskThread::getMaxSize()
{
	return m_maxConCnt;
}
int TcpClientTaskThread::taskSize() const
{
	return task_count + _size;
}
int TcpClientTaskThread::maxTaskSize() const
{
	return maxConns;
}
void TcpClientTaskThread::initParam( void *param )
{
	pool = (TcpClientTaskPool*)param;
}
void TcpClientTaskThread::_add( TcpClientTaskBase *task )
{
	task->addEpoll( m_kdpfd,EPOLLIN | EPOLLERR | EPOLLPRI,(void*)task );
	m_task.push_back( task );
	if( task_count  > m_epfds.size() )
	{
		m_epfds.resize( task_count + 16 );
	}
}
void TcpClientTaskThread::remove( TcpClientTaskBase_IT &it )
{
	(*it)->delEpoll( m_kdpfd,EPOLLIN | EPOLLOUT | EPOLLERR | EPOLLPRI );
	tasks.erase( it );
	task_count = tasks.size();
}
void TcpClientTaskThread::run()
{
	TcpClientTaskBase_IT it,next;
	Time currentTime;
	Time _write_time;
	
	int kdpfd_r;
	epollfdContainer epfds_r;
	kdpfd_r = epoll_create(256);
	assert( -1 != kdpfd_r );
	epfds_r.resize( 256 );
	DWORD fds_count_r = 0;
	bool check = false;
	while( !isFinal() )
	{
		cyrrentTime.now();
		this->setRunning();
		if( check )
		{
			check_queue();
			if( !tasks.empty() )
			{
				for( it = tasks.begin(),next = it,next++;it != tasks.end();it = next,next++ )
				{
					TcpClientTaskBase *task = *it;
					if( task->isTerminate() )
					{
						if( task->isFdsrAdd() )
						{
							task->delEpoll( kdpfd_r,EPOLLIN | EPOLLPRI );
							fds_count_r -= 1;
							task->fdsrAdd( false );
						}
						remove( it );
						task->getNextState();
					}
					else
					{
						if( task->checkFirstMainLoop() )
						{
							task->ListeningRecv( false );
						}
						if( !task->isFdsrAdd() )
						{
							task->addEpoll(kdpfd_r,EPOLL | EPOLLERR | EPOLLPRI,(void*)task);
							task->fdsrAdd(true);
							fds_count_r += 1;
							if(fds_count_r > epfds_r.size() )
							{
								epfds_r.resize(fds_count_r + 16 );
							}
						}
					}
				}
			}
			check = false;
		}
		Thread::msleep(2);
		if(fds_count_r)
		{
			int retcode = epoll_wait(kdpfd_r,&epfds_r[0],fds_count_r,0);
			if(retcode > 0 )
			{
				for(int i = 0;i < retcode;++i)
				{
					TcpClientTaskBase *task = (TcpClientTaskBase*)epfds_r[i].data.ptr;
					if(epfds_r[i].events & (EPOLLERR | EPOLLPRI ) )
					{
						task->Terminate(TcpClientTaskBase::TM_sock_error );
						check = true;
					}
					else
					{
						if(epfds_r[i].events & EPOLLIN )
						{
							if( !task->ListeningRecv(true) )
							{
								task->Terminate( TcpClientTaskBase::TM_sock_error );
								check = true;
							}
						}
					}
					epfds_r[i].events = 0;
				}
			}
		}
		if( check )
		{
			continue;
		}
		if( currentTime.msec() - _write_time.msec() >= (unsigned long)(pool->s_usleepTime/1000) )
		{
			_write_time = currentTime;
			if(!tasks.empty() )
			{
				int retcode = epoll_wait(kdpfd,&epfds[0],task_count,0);
				if(retcode)
				{
					for(int i=0;i < retcode;i++ )
					{
						TcpClientTaskBase *task = (TcpClientBase*)epfds[i].data.ptr;
						if(epfds[i].events & (EPOLLERR | EPOLLPRI ) )
						{
							task->Terminate(TcpClientTaskBase::TM_sock_error);
						}
						else
						{
							if(epfds[i].events & EPOLLIN )
							{
								if(!task->ListeningRecv(true))
								{
									task->Terminate(TcpClientTaskBase::TM_sock_error );
								}
							}
							if(epfds[i].events & EPOLLOUT)
							{
								if(!task->ListeningSend())
								{
									task->Terminate(TcpClientTaskBase::TM_sock_error );
								}
							}
						}
						epfds[i].events = 0;
					}
				}
			}
			check = true;
		}
	}
	for(it = tasks.begin(),next = it,next++;it != tasks.end();it = next,next++)
	{
		TcpClientTaskBase *task = *it;
		remove(it);
		task->getNextState();
	}
}


