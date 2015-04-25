#ifndef BASE_CHECK_WAIT_THREAD_H
#define BASE_CHECK_WAIT_THREAD_H

class CheckWaitThread : public Thread,public TaskQueue<TcpClientTaskBase>
{
	public:
		CheckWaitThread();
		~CheckWaitThread()
		{
			TEMP_FAILURE_RETRY( ::close( kdpfd ) );
		}
		int taskSize() const;
		int maxTaskSize() const;
		void initParam( void *param );
		virtual void run();
	private:
		static const int maxConns = 4096;
		TcpClientTaskPool *pool;
		TcpClientTaskBaseContainer::size_type task_count;
		int kdpfd;
		epollfdContainer epfds;
		void _add( TcpClientTaskBase *task );
		void remove( TcpClientTaskBase *task );
		void remove( TcpClientTaskBase_IT &it );
};

#endif
