#ifndef BASE_TCP_CLIENT_TASK_THREAD_H
#define BASE_TCP_CLIENT_TASK_THREAD_H

class TcpClientTaskThread : public Thread, public TaskQueue<TcpClientTaskBase>
{
	public:
		TcpClientTaskThread();
		~TcpClientTaskThread()
		{
			TEMP_FAILURE_RETRY( ::close( kdpfd ) );
		}
		static int getMaxSize();
		static void setMaxSize( DWORD perThreadSize );
		int taskSize() const;
		int maxTaskSize() const;
		void initParam( void *param );
		virtual void run();
	private:
		static int s_maxConCnt;
		TcpClientTaskPool *m_pool;
		TcpClientTaskBaseContainer m_tasks;
		TcpClientTaskBaseContainer::size_type task_count;
		int m_kdpfd;
		epollfdContainer m_epfds;
		void _add( TcpClientTaskBase *task );
		void remove( TcpClientTaskBase_IT &it );
};
#endif
