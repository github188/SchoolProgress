#ifndef BASE_SOCKET_H
#define BASE_SOCKET_H
#include <sys/epoll.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <poll.h>
#include <errno.h>
#include "baseDef.h"
#include "baseClass.h"
#include "baseMsgContainer.h"
#include "baseTest.h"
class Socket : private Noncopyable
{
	public:
		static DWORD uncompress_size;
		static DWORD nocompress_size;
		static DWORD compress_size;
	public:
		static const SWORD T_RD_MSEC = 2100;
		static const SWORD T_WR_MSEC = 5100;
		static const DWORD PH_LEN = sizeof(DWORD);
		static const DWORD PACKET_ZIP_MIN = 32;
		static const DWORD PACKET_ZIP = 0x40000000;
		static const DWORD INCOMPLETE_READ = 0X00000001;
		static const DWORD INCOMPLETE_WRITE = 0X00000002;
		static const DWORD PACKET_MASK = trunkSize - 1;
		static const DWORD MAX_DATABUFFERSIZE = PACKET_MASK;
		static const DWORD MAX_DATASIZE = MAX_DATABUFFERSIZE - PH_LEN - PACKHEADLASTSIZE;
		static const DWORD MAX_USERDATASIZE = MAX_DATASIZE - 128;
		static const char* getIPByIfName(const char *ifName);
		bool checkChangeSocket();
		DWORD getMaxDataSize() const;
		bool setChangeSocket(const SWORD sock);
		bool changeSocket(const SWORD sock);
		bool checkMaxSendSize(const SWORD size);
		void success_unpack();
		const SWORD getSocket()
		{
			return sock;
		}
		Socket(const SWORD sock,const struct sockaddr_in *addr = NULL,const bool compress = false);
		~Socket();
		SWORD recvToCmd(void *pstrCmd,const SWORD cmdLen,const bool wait);
		bool sendCmd1(const void *pstrCmd,const SWORD cmdLen,const bool buffer = false);
		bool sendCmd(const void *pstrCmd,const SWORD nLen,const bool buffer = false);
		bool sendCmdNoPack(const void *pstrCmd,const SWORD CmdLen,const bool bufer)
		bool sync();
		void force_sync();
	 	//-1：操作失败 0：操作超时 1：套接子有数据	
		SWORD checkIOForRead();
		SWORD checkIOForWrite();
		SWORD recvToBuf_NoPoll();
		SWORD recvToCmd_NoPoll(void *pstrCmd,const DWORD cmdLen);
		void success_recv_and_dec(SWORD retcode);
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
		inline void setReadTimeOut(const SWORD msec)
		{
			rd_msec = msec;
		}
		inline void setWriteTimeOut(const SWORD msec)
		{
			wr_msec = msec;
		}
		inline void addEpoll(SWORD kdpfd,__uint_t events,void *ptr)
		{
			mutex.lock();
			_kdpfd = kdpfd;
			_ev.events = events;
			_ev.data.ptr = ptr;
			if(epoll_ctl(kdpfd,EPOLL_CTL_ADD,sock,&_ev) == -1)
			{
				char _buf[100];
				bzero(_buf,sizeof(_buf));
				strerror_r(errno,_uf,sizeof(_buf));
				Test::logger->fatal("addEpoll: %s,",_buf);
			}
			mutex.unlock();
		}
		inline void delEpoll(SWORD kdpfd,__uint32_t events)
		{
			mutex.lock();
			_ev.events = events;
			if(epoll_ctl(kdpfd,EPOLL_CTL_DEL,sock,&_ev) == -1)
			{
				char _buf[100];
				bzero(_buf,sizeof(_buf));
				strerror_r(errno,_buf,,sizeof(_buf));
				Test::logger->fatal("delEpoll error :%s",_buf);
			}
			mutex.unlock();
		}
		inline void fillPollFd(struct pollfd& pfd,WORD events)
		{
			pfd.fd = sock;
			pfd.events = events;
			pfd.revents = 0;
			pfd.pSock = this;
		}
		inline void setEncMethod(Encrpt::encMethod m)
		{
			enc.setEncMethod(m);
		}

		inline void set_key_rc5(const BYTE *data,SWORD len,SWORD rounds = RC5_8_ROUNDS)
		{
			enc.set_key_rc5(data,len,rounds);
		}
		inline void set_key_des(const_DES_cblock *key)
		{
			enc.set_key_des(key);
		}
		inline void set_key_des_ipp(Ipp8u *key)
		{
			enc.set_key_des_ipp(key);
		}
		inline DWORD snd_queue_size() const
		{
			return _snd_queue.rd_size() + _enc_queue.size();
		}
		inline DWORD rcv_raw_size() const
		{
			return _rcv_raw_size;
		}
	private:
		SWORD sock;
		SWORD sock_change;
		SWORD _kdpfd;
		struct epoll_event _ev;
		struct sockaddr_in addr;
		struct sockaddr_in local_addr;
		SWORD rd_msec;
		SWORD wr_msec;
		t_BufferCmdQueue _rcv_queue;
		DWORD _rcv_raw_size;
		t_BufferCmdQueue _zip_queue;
		t_BufferCmdQueue _snd_queue;
		t_BufferCmdQueue _enc_queue;
		DWORD _current_cmd;
		Mutex mutex;
		DWORD bitmask;
		CEncrypt enc;
		inline void set_flag(DWORD _f)
		{
			bitmask |= _f;
		}
		inline bool isset_flag(DWORD _f) const
		{
			return bitmask & _f;
		}
		inline void clear_flag(DWORD _f)
		{
			bitmask &= ~_f;
		}
		inline bool need_enc() const
		{
			return CEncrypt::ENCDEC_NONE != enc.getEncMethod();
		}
		inline DWORD packetMinSize() const
		{
			return PH_LEN;
		}
		inline DWORD packetSize(const BYTE *in) const
		{
			return PH_LEN + (*(DWORD*)in) & PACKET_MASK;
		}
		inline SWORD sendRawData(const void *pBuffer,const SWORD size);
		inline bool sendRawDataIM(const void *pBuffer,const SWORD size);
		inline SWORD sendRawData_NoPoll(const void *pBuffer,const int size);
		inline bool setNonblock();
		inline SWORD waitForRead();
		inline SWORD waitForWrite();
		inline SWORD recvToBuf();
		inline DWORD packetUnpack(BYTE *in,const DWORD packerLen);
		template<typename buffer_type>
		DWORD packetAppend(const void *pData,const DWORD len,buffer_type &cmd_queue);
		template<typename buffer_type>
		DWORD packetAppendNoEnc(const void *pData,const DWORD len,buffer_type &cmd_queue);
		template<typename buffer_type>
		DWORD packetPackEnc(buffer_type &cmd_queue,const DWORD current_cmd,const DWORD offset = 0);
		template<typename buffer_type>
		DWORD packetPackNoZip(const void *pData,const DWORD len,buffer_type &cmd_queue);
		template<typename buffer_type>
		DWORD packetPackZip(const void *pData,const DWORD len,buffer_type &cmd_queue,const bool _compress);
};

template<typename buffer_type>
DWORD Socket::packetAppendNoEnc(const void *pData,const DWORD len,buffer_type &cmd_queue)
{
	return packetPackZip<buffer_type>(pData,len,cmd_queue,PACKET_ZIP == (bitmask & PACKET_ZIP));
}
template<typename buffer_type>
DWORD Socket::packetAppend(const void *pData,const DWORD len,buffer_type &cmd_queue)
{
	DWORD size = packetPackZip(pData,len,cmd_queue,PACKET_ZIP == (bitmask & PACKET_ZIP));
	if(need_enc())
	{
		size = packetPackEnc(cmd_queue,cmd_queue.rd_size());
	}
	return size;
}
template<typename buffer_type>
DWORD Socket::packetPackEnc(buffer_type &cmd_queue,const DWORD current_cmd,const DWORD offset)
{
	DWORD mod = (cmd_queue.rd_size() - offset) % 8;
	if(mod)
	{
		mod = 8 - mod;
		(*(DWORD*)(&(cmd_queue.rd_buf()[cmd_queue.rd_size() - current_cmd])));
		cmd_queue.wr_reserve(mod);
		cmd_queue.wr_flip(mod);
	}
	enc.encdec(&cmd_queue.rd_buf()[offset],cmd_queue.rd_size() - offset,true);
	return cmd_queue.rd_size();
}
template<typename buffer_type>
DWORD Socket::packetPackNoZip(const void *pData,const DWORD len,buffer_type &cmd_queue)
{
	DWORD size = len > getMaxDataSize() ? getMaxDataSize() : len;
	DWORD mask = 0;
	cmd_queue.wr_reserve(size + PH_LEN);
	bcopy(pData,&(cmd_queue.wr_buf()[PH_LEN]),size);
	cmd_queue.wr_flip(size + PH_LEN);
	return size + PH_LEN;
}
template<typename buffer_type>
DWORD Socket::packetPackZip(const void *pData,const DWORD len,buffer_type &cmd_queue,const bool _compress)
{
	DWORD size = len > getMaxDataSize() ? getMaxDataSize() : len;
	DWORD mask = 0;
	if(size >= PACKET_ZIP_MIN && _compress)
	{
	/*
		uncompress_size += size;
		DWORD zipLen = unzip_size(size);
		cmd_queue.wr_reserver(zipLen + PH_LEN);
		SWORD retcode = Test::lib_compress(&(cmd_queue.wr_buff()[PH_LEN]);
		switch(retcode)
		{
			case Z_OK:
				break;
			case Z_MEM_ERROR:
				break;
			case Z_BUF_ERROR:
				break;
		}
		size = zipLen;
		compress_size += size;
		mask |= PACKET_ZIP;
	*/
	}
	else
	{
		compress_size += size;
		cmd_queue.wr_reserve(size + PH_LEN);
		bcopy(pData,&(cmd_queue.wr_buf()[PH_LEN]),size);
	}
	(*(DWORD*)cmd_queue.wr_buf()) = (size | mask);
	cmd_queue.wr_flip(size + PH_LEN);
	return size + PH_LEN;
};
	

#endif
