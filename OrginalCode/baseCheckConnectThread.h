#ifndef BASE_CHECK_CONNECT_THREAD_H
#define BASE_CHECK_CONNECT_THREAD_H

class CheckConnectThread : public Thread,public TaskQueue<TcpClientTaskBase>
{
	public:
		CheckConnectThread():Thread( "连接检查线程" )
		{
			
		}
		void _add( TcpClientTaskBase *task );
		int taskSize() const;
		int maxTaskSize() const;
		void initParam( void *param );
		virtual void run();
	private:
		TcpClientTaskBaseContainer tasks;
		TcpClientTaskPool *pool;
		static const int maxConns = 4096;
};

#endif
