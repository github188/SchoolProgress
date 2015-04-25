void CheckWaitThread::_add( TcpClientTaskBase *task )
{
	task->addEpoll( kdpfd,EPOLLIN | EPOLLERR | EPOLLPRI,(void*)task );
	tasks.push_back( task );
	_size = tasks.size();
	task_count = tasks.size();
	if( _size > epfds.size() )
	{
		epfds.resize( _size + 16 );
	}
}

void CheckWaitThread::remove( TcpClientTaskBase *task)
{
	task->delEpoll( kdpfd,EPOLLIN | EPOLLPRI | EPOLLERR );
	tasks.remove( task );
	_size = tasks.size();
	task_count = tasks.size();
}
void CheckWaitThread::remove( TcpClientTaskBase_IT &it )
{
	(*it)->delEpoll( kdpfd,EPOLLIN | EPOLLPRI | EPOLLERR );
	tasks.erase( it );
	_size = tasks.size();
	task_count = tasks.size();
}
CheckWaitThread::CheckWaitThread():Thread( "验证线程" )
{
	task_count = 0;
	kdpfd = epoll_create( 256 );
	assert( -1 != kdpfd );
	epfds.resize( 256 );
}
int CheckWaitThread::taskSize() const
{
	return task_count + _size;
}
int CheckWaitThread::maxTaskSize() const
{
	return maxConns;
}
void CheckWaitThread::initParam( void *param )
{
	pool = (TcpClientTaskPool*)param;
}
void CheckWaitThread::run()
{
	TcpClientTaskBase_IT it,next;
	while( !isFinal() )
	{
		this->setRunning();
		Thread::sleep( 1 );
		check_queue();
		if( !tasks.empty() )
		{
			int retcode = epoll_wait( kdpfd,&epfds[0],task_count,0 );
			if( retcode > 0 )
			{
				for( int i = 0;i < retcode;++i )
				{
					TcpClientTaskBase *task = (TcpClientTaskBase*)epfds[i],data,ptr;
					if( epfds[i].events & (EPOLLERR | EPOLLPRI ) )
					{
						remove( task );
						task->resetState();
					}
					else if(epfds[i].events & EPOLLIN )
					{
						switch( task->checkRebound() )
						{
							case 1:
								{
									remove( task );
									if( !pool->addMain( task ) )
									{
										task->resetState();
									}
									break;
								}
							case 0:
								break;
							case -1:
								{
									remove( task );
									task->resetState();
									break;
								}
						}
					}
				}
			}
		}
		Time ct;
		for( it = tasks.begin();next = it,next++;it != tasks.end();it = next,next++ )
		{
			TcpClientTaskBase *task = *it;
			if( task->checkStateTimeout( TcpClientTaskBase::sync,ct,4 ) )
			{
				remove( it );
				task->resetState();
			}
		}
		Thread::msleep( 50 );
	}
	for( it = tasks.begin(),next = it,next++;it != tasks.end();it = next,next++ )
	{
		TcpClientTaskBase *task = *it;
		remove( it );
		task->resetState();
	}
}



		
