#ifndef COMMON_TCP_H
#define COMMON_TCP_H
#include <assert.h>

#include "baseDef.h"
#include "baseThread.h"

/*
class Socket : private Noncopyable
{
	public:
		bool  m_bUseIocp;
		DWORD m_SendSize;
		DWORD m_LastSend;
		DWORD m_LastSended;
		static const int T_RD_MSEC = 2100;
		static const int T_WR_MSEC = 2100;
		static const DWORD PH__LEN = sizeof(DWORD);
		static const DWORD PACKET_ZIP_MIN = 32;
		static const DWORD PACKET_ZIP = 0X40000000;
		static const DWORD INCOMPLETE_READ = 0X00000000;
		static const DWORD INCOMPLETE_WRITE = 0X00000002;
		static const DWORD PACKET_MASK = trunkSize - 1;
		static const DWORD MAX_DATABUFFERSIZE = PACKET_MASK;
		static const DWORD MAX_DATASIZE = MAX_DATABUFFERSIZE - PH__LEN - PACKHEADLASTSIZE;
		static const DWORD MAX_USERDATASIZE = MAX_DATASIZE - 128;
		static const char* getIPByIfName(const char *ifName);
		Socket(const SOCKET sock,const struct sockaddr_in *addr = NULL,const bool compress = false,const bool useIocp = false,TcpTask *tcpTask = NULL);
		~Socket();
		int recvToCmd(void *pstrCmd,const int cmdLen,const bool wait);
		bool sendCmd(const void *pstrCmd,const int cmdLen,const bool buffer = false);
		int Send(const SOCKET _sock,const void *pBuffer,const int nLen,int flags);
		bool sync();
		void force_sync();
		int checkIOForRead();
		int checkIOForWrite();
		int recvToBuf_NoPoll();
		int recvToCmd_NoPoll(void *pstrCmd,const int nCmdLen);
		inline const char* getIP() const
		{
			return inet_ntoa(addr.sin_addr);
		}
		inline const DWORD getAddr() const
		{
			return addr.sin_addr.s_addr;
		}
		inline const WORD getPort() const
		{
			return ntohs(addr.sin_port);
		}
		inline const char* getLocalIP() const
		{
			return inet_ntoa(local_addr.sin_addr);
		}
		inline const WORD getLocalPort() const
		{
			return ntohs(local_addr.sin_port);
		}
		inline void setReadTimeOut(const int msec)
		{
			rd_msec = msec;
		}
		inline void setWriteTimeOut(const int msec)
		{
			wr_msec = msec;
		}
		inline void fillPollFd(struct pollfd& pfd,short events)
		{
			pfd.fd = sock;
			pfd.events = events;
			pfd.revents = 0;
			pfd.pSock = this;
		}
		void disConnect()
		{
			shutdown(sock,0x02);
		}
		Lock m_lock;
		bool m_bIocpDeleted;
		bool m_bTaskDeleted;
		bool m_bDeleted;

	private:
		SOCKET sock;
		struct sockaddr_in addr;
		struct sockaddr_in local_addr;
		int rd_msec;
		int wr_msec;
		Lock m_recvLock;
		t_BufferCmdQueue  m_RecvBuffer;
		t_BufferCmdQueue  tQueue;

};

*/

/*
class TcpTask : public Processor,private Noncopyable
{
	public:
		enum TerminateMethod
		{
			terminate_no,
			terminate_active,
			terminate_passive
		};
		enum TcpTask_State
		{
			notuse = 0,  //连接关闭状态
			verify = 1,  //连接验证状态
			sync   = 2,  //等待来自其他服务器的同步验证状态
			okay   = 3,  //连接处理状态
			recycle= 4,  //连接回收状态
		};


		TcpTask(TcpTaskPool *pool,const SOCKET _socket,const struct sockaddr_in *addr = NULL,const bool compress = false,const bool checkSignal = true,const bool useIocp = false):pool(pool),lifeTime(),_checkSignal(checkSignal),_ten_min(600),tick(false)
		{
		}
	

	private:
	 	TcpTaskPool *pool;
	   	TerminateMethod terminate;
	    bool terminate_wait;
		RTime lifetime;
		bool uniqueVerified;
		const bool _checkSignal;
		Timer _ten_min;
		bool tick;
		bool fdsradd;
	 protected:
	  	bool buffered;
	    Socket *mSocket;
		TcpTask_State state;
};
*/

#endif
