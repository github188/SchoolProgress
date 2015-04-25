#ifndef BASE_TCP_TASK_QUEUE_H
#define BASE_TCP_TASK_QUEUE_H

class TcpTaskQueue : public TcpTask
{
	public:
		TcpTaskQueue(const int sock,const struct sockaddr_in *addr = NULL,const bool compress = false,const bool checkSignal = true) : TcpTask(sock,addr,compress,checkSignal)
	{
	}
		virtual ~TcpTaskQueue() {};
		virtual bool checkRecycle() = 0;
	private:
		bool parse(const Cmd::NullCmd *cmd,const unsigned int cmdLen);
};

#endif
