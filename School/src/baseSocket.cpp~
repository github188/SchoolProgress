#include "baseSocket.h"
DWORD Socket::uncompress_size = 0;
DWORD Socket::nocompress_size = 0;
DWORD Socket::compress_size = 0;
//DWORD Socket::PACKET_ZIP_MIN = 64;
Socket::Socket(const SWORD sock,const struct sockaddr_in *addr,const bool compress)
{
	bitmask = 0;
	assert(sock != -1);
	this->sock = sock;
	sock_change = 0;
	_kdpfd = 0;
	bzero(&this->addr,sizeof(struct sockaddr_in));
	if(!addr)
	{
		socklen_t len = sizeof(struct sockaddr);
		getpeername(this->sock,(struct sockaddr*)&this->addr,&len);
	}
	else
	{
		bcopy(addr,&this->addr,sizeof(struct sockaddr_in));
	}
	bzero(&local_addr,sizeof(struct sockaddr_in));
	socklen_t len = sizeof(struct sockaddr_in);
	getsockname(this->sock,(struct sockaddr *)&local_addr,&len);
	fcntl(this->sock,F_SETFD,fcntl(this->sock,F_GETFD,0) | FD_CLOEXEC);
	setNonblock();
	rd_msec = T_RD_MSEC;
	wr_msec = T_WR_MSEC;
	_rcv_raw_size = 0;
	_current_cmd = 0;
	set_flag(INCOMPLATE_READ | INCOMPLATE_WRITE);
	if(compress)
	{
		bitmask |= PACKET_ZIP;
	}
}
bool Socket::setChangeSocket(const SWORD socket)
{
	sock_change = socket;
	return true;
}
bool Socket::changeSocket(const SWORD socket)
{
	sock = sock_change;
	sock_change = 0;
	return true;
}
bool Socket::checkChangeSocket()
{
	return sock_change;
}
Socket::~Socket()
{
	Test::logger->debug("Socket::~SocketSocket 关闭套接口连接");
	shutdown(sock,SHUT_RDWR);
	TEMP_FAILURE_RETRY(close(sock));
	sock = -1;
}
void Socket::success_unpack()
{
	if(_rcv_raw_size >= packetMinSize())
	{
		DWORD recordLen = packetSize(_rcv_queue.rd_buf());
		if(_rcv_raw_size >= recordLen)
		{
			SWORD retval = packetUnpack(_rcv_queue.rd_buf(),recordLen,(BYTE*)_rcv_queue.rd_flip(recordLen));
			_rcv_raw_size -= recordLen;
			//return retval;
		}
	}
}
SWORD Socket::recvToCmd(void *pstrCmd,const SWORD cmdLen,const bool wait)
{
	success_unpack();
	do
	{
		SWORD retval = recvToBuf();
		if(retval == -1 || (!retval && !wait))
		{
			return retval;
		}
		success_unpack();
	}while(true);
	return 0;
}
bool Socket::checkMaxSendSize(const SWORD size)
{
	if(size > (SWORD)MAX_USERDATASIZE)
	{
		Test::logger->error("Socket::checkMaxSendSizeerror 发送数据大小大于发送缓存,写缓存溢出:%d",size);
		assert(false);
		return false;
	}
	return true;
}
SWORD Socket::sendRawData(const void *pBuffer,const SWORD size)
{
	SWORD retcode = -1;
	if(isset_flag(INCOMPLATE_WRITE))
	{
		clear_flag(INCOMPLATE_WRITE);
		goto do_select;
	}
	retcode = TEMP_FAILURE_RETRY(send(sock,pBuffer,size,MSG_NOSIGNAL));
	if(retcode == -1 && (errno == EAGAIN || errno == EWOULDBLOCK))
	{
		do_select:
			retcode = waitForWrite();
			if(retcode == 1)
			{
				retcode = TEMP_FAILURE_RETRY(send(sock,pBuffer,size,MSG_NOSIGNAL));
			}
			else
			{
				return retcode;
			}
	}
	if(retcode > 0 && retcode < size)
	{
		set_flag(INCOMPLATE_WRITE);
		return retcode;
	}
}
bool Socket::sendRawDataIM(const void *pBuffer,const SWORD size)
{
	if(!pBuffer || size <= 0)
	{
		return false;
	}
	int offset = 0;
	do
	{
		SWORD retcode = sendRawData(&((char*)pBuffer)[offset],size - offset);
		if(retcode == -1)
		{
			return false;
		}
		offset += retcode;
	}while(offset < size);
	return offset == size;
}
bool Socket::sendCmd(const void *pstrCmd,const SWORD cmdLen,const bool buffer)
{
	if(!pstrCmd || cmdLen <= 1)
	{
		return false;
	}
	bool retval = true;
	if(buffer)
	{
		t_StackCmdQueue _raw_queue;
		packetAppendNoEnc(pstrCmd,cmdLen,_raw_queue);
		mutex.lock();
		_snd_queue.put(_raw_queue.rd_buf(),_raw_queue.rd_size());
		_current_cmd = _raw_queue.rd_size();
		mutex.unlock();
	}
	else
	{
		t_StackCmdQueue _raw_queue;
		packetAppend(pstrCmd,cmdLen,_raw_queue);
		mutex.lock();
		retval = sendRawDataIM(_raw_queue.rd_buf(),_raw_queue.rd_size());
		_current_cmd = _raw_queue.rd_size();
		mutex.unlock();
	}
	return retval;
}
bool Socket::sendCmd1(const void *pstrCmd,const SWORD cmdLen,const bool buffer)
{
	if(!pstrCmd || cmdLen <= 1)
	{
		return false;
	}
	bool retval = true;
	if(buffer)
	{
		t_StackCmdQueue _raw_queue;
		packetPackNoZip<t_StackCmdQueue>(pstrCmd,cmdLen,_raw_queue);
		bool bsend = true;
		mutex.lock();
		if(_zip_queue.rd_size() + _raw_queue.rd_size() >= Socket::MAX_USERDATASIZE)
		{
			if(!_zip_queue.rd_size())
			{
				Test::logger->debug("Socket::sendCmd1压缩缓冲消息长度:%u,%u",_zip_queue.rd_size(),_raw_queue.rd_size());
			}
			else if(*(DWORD*)_zip_queue.rd_buf() + sizeof(PH_LEN) < _zip_queue.rd_size())
			{
				if(_zip_queue.rd_size() < Socket::MAX_DATASIZE - sizeof(PH_LEN) < _zip_queue.rd_size())
				{
				/*
					BUFFER_CMD(Cmd::t_ZipCmdPackNullCmd,send,Socket::MAX_DATA_SIZE + 4);
					bcopy(_zip_queue.rd_buf(),send->data,_zip_queue.rd_size());
					send->dwSize = _zip_queue.rd_size();
					_zip_queue.reset();
					mutex.unlock();
					t_StackCmdQueue _raw_queue1;
					packetAppendNoEnc(send,send->allsize(),_raw_queue1);
					mutex.lock();
				
					_snd_queue.put(_raw_queue.rd_buf(),_raw_queue1.rd_size());
					_current_cmd = _raw_queue1.rd_size();
				*/
				}
				else
				{
					Test::logger->debug("SOcket::sendCmd1 error 压缩缓冲消息过大 :%u",_zip_queue.rd_size());
				}
			}
			else
			{
			/*
				BUFFER_CMD(Cmd::t_ZipCmdPackNullCmd,send,Socket::MAX_DATASIZE + 4);
				bcopy(_zip_queue.rd_buf(),send->data,_zip_queue.rd_size());
				_zip_queue.reset();
				mutex.unlock();
				t_StackCmdQueue _raw_queue1;
				packetAppendNoEnc(send->data,send->datasize(),_raw_queue1);
				mutex.lock();
				_snd_queue.put(raw_queue1.rd_buf(),_raw_queue1.rd_size());
			*/
			}
			if(_raw_queue.rd_size() >= Socket::MAX_USERDATASIZE)
			{
				mutex.unlock();
				t_StackCmdQueue _raw_queue1;
				packetAppendNoEnc(_raw_queue.rd_buf(),_raw_queue.rd_size(),_raw_queue1);
				mutex.lock();
				_snd_queue.put(_raw_queue1.rd_buf(),_raw_queue1.rd_size());
				_current_cmd = _raw_queue1.rd_size();
				bsend = false;
			}
		}
		if(bsend)
		{
			if(_zip_queue.rd_size() + _raw_queue.rd_size() < Socket::MAX_USERDATASIZE)
			{
				_zip_queue.put(_raw_queue.rd_buf(),_raw_queue.rd_size());
			}
			else
			{
				mutex.unlock();
				t_StackCmdQueue _raw_queue1;
				packetAppendNoEnc(_raw_queue.rd_buf(),_raw_queue.rd_size(),_raw_queue1);
				mutex.lock();
				_snd_queue.put(_raw_queue1.rd_buf(),_raw_queue1.rd_size());
				_current_cmd = _raw_queue1.rd_size();
			}
		}
		mutex.unlock();
	}
	else
	{
		t_StackCmdQueue _raw_queue;
		packetAppend(pstrCmd,cmdLen,_raw_queue);
		mutex.lock();
		retval = sendRawDataIM(_raw_queue.rd_buf(),_raw_queue.rd_size());
		mutex.unlock();
	}
	return retval;
}
bool Socket::sendCmdNoPack(const void *pstrCmd,const SWORD cmdLen,const bool buffer)
{
	if(!pstrCmd || cmdLen <= 0)
	{
		return false;
	}
	bool retval = false;
	if(buffer)
	{
		mutex.lock();
		_snd_queue.put((BYTE*)pstrCmd,cmdLen);
		_current_cmd = cmdLen;
		mutex.unlock();
	}
	else
	{
		if(need_enc())
		{
			t_StackCmdQueue _raw_queue;
			_raw_queue.put((BYTE*)pstrCmd,cmdLen);
			_current_cmd = cmdLen;
			mutex.unlock();
		}
		else
		{
			mutex.lock();
			retval = sendRawDataIM(pstrCmd,cmdLen);
			mutex.unlock();
		}
	}
	return retval;
}
bool Socket::sync()
{
	return true;
/*
	if(need_enc())
	{
		DWORD size = 0,curren_cmd = 0,offset = 0;
		mutex.lock();
		if(_zip_queue.rd_read())
		{
			BUFFER_CMD(Cmd::t_ZipCmdPackNullCmd,send,Socket::MAX_DATASIZE + 4);
			bcopy(_zip_queue.rd_buf(),send->data,_zip_queue.rd_size());
			send->dwSize = _zip_queue.rd_size();
			_zip_queue.reset();
			t_StackCmdQueue _raw_queue;
			mutex.unlock();
			if(*(SWORD)send->data + (SWORD)sizeof(PH_LEN) < send->datasize())
			{
				packetAppendNoEnc(send,send->allsize(),_raw_queue);
				mutex.lock();
				_snd_queue.put(_raw_queue.rd_buf(),_raw_queue.rd_size());
				_current_cmd = _raw_queue.rd_size();
			}
			else
			{
				mutex.lock();
				_snd_queue.put((const BYTE)send->data,send->datasize());
				_current_cmd = send->datasize();
			}
			if(_snd_queue.rd_ready())
			{
				size = _snd_queue.rd_size();
				current_cmd = _current_cmd;
				offset = _enc_queue.rd_size();
				_enc_queue.put(_snd_queue.rd_buf(),size);
				_snd_queue.rd_flip(size);
				_current_cmd = 0;
			}
			mutex.unlock();
			if(size)
			{
				packetPackEnc(_enc_queue,current_cmd,offset);
			}
			if(_enc_queue.rd_ready())
			{
				SWORD retcode = sendRawData_NoPoll(_enc_queue.rd_buf(),_enc_queue.rd_size());
				if(retcode > 0)
				{
					_enc_queue.rd_flip(retcode);
				}
				else if(retcode == -1)
				{
					return false;
				}
			}
		}
		else
		{
			mutex.lock();
			if(_zip_queue.rd_ready())
			{
			//	BUFFER_CMD(Cmd::t_ZipCmdPackNullCmd,send,Socket::MAX_DATASIZE + 4);
			//	bcopy(_zip_queue.rd_buf(),send->data,_zip_queue.rd_size());
				_zip_queue.reset();
				t_StackCmdQueue _raw_queue;
				if(*(SWORD*)send->data + (SWORD)sizeof(PH_LEN) < send->datasize())
				{
					packetAppendNoEnc(send,send->allsize(),_raw_queue);
					mutex.lock();
					_snd_queue.put(_raw_queue.rd_buf(),_raw_queue.rd_size());
					_current_cmd = _raw_queue.rd_size();
				}
				else
				{
					mutex.lock();
					_snd_queue.put((const BYTE*)send->data,send->datasize());
					_current_cmd = send->datasize();
				}
			}
			if(_snd_queue.rd_ready())
			{
				_enc_queue.put(_snd_queue.rd_buf(),_snd_queue.rd_size());
				_snd_queue.rd_flip(_snd_queue.rd_size());
				_current_cmd = 0;
			}
			mutex.unlock();
			if(_enc_queue.rd_ready())
			{
				SWORD retcode = sendRawData_NoPoll(_enc_queue.rd_buf(),_enc_queue.rd_size());
				if(retcode > 0)
				{
					_enc_queue.rd_flip(retcode);
				}
				else if(retconde == -1)
				{
					return false;
				}
			}
		}
	}
	return true;
*/
}
void Socket::force_sync()
{
/*
	if(need_enc())
	{
		DWORD size = 0,current_cmd = 0,offset = 0;
		mutex.lock();
		if(_zip_queue.rd_ready())
		{
			BUFFER_CMD(Cmd::t_ZipCmdPackNullCmd,send,Socket::MAX_DATASIZE + 4);
			bcopy(_zip_queue.rd_buf(),send->data,_zip_queue.rd_size());
			send->dwSize = _zip_queue.rd_size();
			_zip_queue.reset();
			mutex.unlock();
			t_StackCmdQueue _raw_queue;
			if(*(SWORD*)send->data + (SWORD)sizeof(PH_LEN) < send->datasize())
			{
				packetAppendNoEnc(send,send->allsize(),_raw_queue);
				mutex.lock();
				_snd_queue.put(_raw_queue.rd_buf(),_raw_queue.rd_size());
				_current_cmd = _raw_queue.rd_size();
			}
			else
			{
				mutex.lock();
				_snd_queue.put((const BYTE*)send->data,send->datasize());
				_current_cmd = send->datasize();
				offset = _enc_queue.rd_size();
				_enc_queue.put(_snd_queue.rd_buf(),size);
				_snd_queue.rd_flip(size);
				_current_cmd = 0;
			}
			mutex.unlock();
			if(size)
			{
				packetPackEnc(_enc_queue,current_cmd,offset);
			}
			if(_enc_queue.rd_ready())
			{
				sendRawDataIM(_enc_queue.rd_buf(),_enc_queue.rd_size());
				_enc_queue.reset();
			}
		}
		else
		{
			mutex.lock();
			if(_zip_queue.rd_ready())
			{
				BUFFER_CMD(Cmd::t_ZipCmdPackNullCmd,send,Socket::MAX_DATASIZE + 4);
				bcopy(_zip_queue.rd_buf(),send->data,_zip_queue.rd_size());
				send->dwSize = _zip_queue.rd_size();
				_zip_queue.reset();
				mutex.unlock();
				t_StackCmdQueue _raw_queue;
				if(*(SWORD*)send->data + (SWORD)sizeof(PH_LEN) < send->datasize())
				{
					packetAppendNoEnc(send,send->allsize(),_raw_queue);
					mutex.lock();
					_snd_queue.put(_raw_queue.rd_buf(),_raw_queue.rd_size());
					_current_cmd = _raw_queue.rd_size();
				}
				else
				{
					mutex.lock();
					_snd_queue.put((const BYTE*)send->data,send->datasize());
					_current_cmd = send->datasize();
				}
			}
			if(_snd_queue.rd_ready())
			{
				_enc_queue.put(_snd_queue.rd_buf(),_snd_queue.rd_size());
				_snd_queue.rd_flip(_snd_queue.rd_size());
				_current_cmd = 0;
			}
			mutex.unlock();
			if(_enc_queue.rd_ready())
			{
				sendRawDataIM(_enc_queue.rd_buf(),_enc_queue.rd_size());
				_enc_queue.reset();
			}
		}
	}
*/
}
SWORD Socket::checkIOForRead()
{
	struct pollfd pfd;
	pfd.fd = sock;
	pfd.events = POLLIN | POLLERR | POLLPRI;
	pfd.revents = 0;
	SWORD retcode = TEMP_FAILURE_RETRY(poll(&pfd,1,0));
	if(retcode > 0 && !(pfd.revents & POLLIN))
	{
		retcode = -1;
	}
	return retcode;
}
SWORD Socket::checkIOForWrite()
{
	struct pollfd pfd;
	pfd.fd = sock;
	pfd.events = POLLOUT | POLLERR | POLLPRI;
	pfd.revents = 0;
	SWORD retcode = TEMP_FAILURE_RETRY(poll(&pfd,1,0));
	if(retcode > 0 && !(pfd.revents & POLLOUT))
	{
		retcode = -1;
	}
	return retcode;
}
const char* Socket::getIPByIfName(const char *ifName)
{
	SWORD s;
	struct ifreq ifr;
	static const char *none_ip = "0.0.0.0";
	if(!ifName)
	{
		return none_ip;
	}
	s = socket(AF_INET,SOCK_DGRAM,0);
	if(s == -1)
	{
		return none_ip;
	}
	bzero(ifr.ifr_name,sizeof(ifr.ifr_name));
	strncpy(ifr.ifr_name,ifName,sizeof(ifr.ifr_name) - 1);
	if(ioctl(s,SIOCGIFADDR,&ifr) == -1)
	{
		TEMP_FAILURE_RETRY(close(s));
		return none_ip;
	}
	TEMP_FAILURE_RETRY(close(s));
	return inet_ntoa(((struct sockaddr_in*)&ifr.ifr_addr)->sin_addr);
}
void success_recv_and_dec(SWORD retcode)
{
	if((DWORD)retcode < _rcv_queue.wr_size())
	{
		set_flag(INCOMPLATE_READ);
	}
	_rcv_queue.wr_flip(retcode);
	DWORD size = _rcv_queue.rd_size();
	if(size)
	{
		enc.encdec(&_rcv_queue.rd_buf(){_rcv_raw_size],size,false);
		_rcv_raw_size += size;
	}
}
void Socket::success_recv()
{
	if((DWORD)retcode < _rcv_queue.wr_size())
	{
		set_flag(INCOMPLETE_READ);
	}
	_rcv_queue.wr_flip(retcode);
	_rcv_raw_size += retcode;
}
SWORD Socket::recvToBuf_NoPoll()
{
	SWORD retcode = 0;
	if(need_enc())
	{
		_rcv_queue.wr_reserve(MAX_DATABUFFERSIZE);
		retcode = TEMP_FAILURE_RETRY(recv(sock,_rcv_queue.wr_buf(),_rcv_queue.wr_size(),MSG_NOSIGNAL));
		if(retcode == -1 && (errno == EAGAIN || errno == EWOULDBLOCK))
		{
			return 0;
		}
		if(retcode > 0)
		{
			success_recv_and_dec(retcode);
		}
	}
	else
	{
		_rcv_queue.wr_reserve(MAX_DATABUFFERSIZE);
		retcode = TEMP_FAILURE_RETRY(recv(sock,_rcv_buf(),_rcv_queue.wr_size(),MSG_NOSIGNAL));
		if(retcode == -1 && (errno == EAGAIN || errno == EWOULDBLOCK))
		{
			return 0;
		}
		if(retcode > 0)
		{
			success_recv();
		}
	}
	if(!retcode)
	{
		return -1;
	}
	return retcode;
}
SWORD Socket::recvToCmd_NoPoll(void *pstrCmd,const SWORD cmdLen)
{
	success_uppack();
	return 0;
}
SWORD Socket::sendRawData_NoPoll(const void *pBuffer,const SWORD size)
{
	SWORD retcode = TEMP_FAILURE_RETRY(send(sock,pBuffer,size,MSG_NOSIGNAL);
	if(retcode == -1 && (errno == EAGAIN || errno == EWOULDBLOCK))
	{
		return 0;
	}
	if(recode > 0 && retcode < size)
	{
		set_flag(INCOMPLATE_WRITE);
	}
	return retcode;
}
bool Socket::setNonblock()
{
	SWORD fd_flags,nodelay = 1;
	if(setsockopt(sock,IPPROTO_TCP,TCP_NODELAY,(void*)&nodelay,sizeof(nodelay)))
	{
		return false;
	}
	fd_flags = fcntl(sock,F_GETFL,0);
	#if defined(O_NONBLOCK)
		fd_flags |= O_NONBLOCK;
	#elif defined(O_NDELAY)
		fd_flags |= O_NDELAY;
	#elif defined(FNDELAY)
		fd_flags |= O_FNDELAY;
	#else
		return false;
	#endif
	if(fcntl(sock,F_SETFL,fd_flags) == -1)
	{
		return false;
	}
	return true;
}
SWORD Socket::waitForRead()
{
	struct pollfd pfd;
	pfd.fd = sock;
	pfd.events = POLLIN | POLLERR | POLLPRI;
	pfd.revents = 0;
	SWORD retcode = TEMP_FAILURE_RETRY(poll(&pfd,1,rd_msec));
	if(retcode > 0 && 0 == (pfd.revents & POLLIN)
	{
		retcode = -1;
	}
	return retcode;
}
SWORD Socket::waitForWrite()
{
	struct pollfd pfd;
	pfd.fd = sock;
	pfd.events = POLLOUT | POLLERR | POLLPRI;
	pfd.revents = 0;
	SWORD retcode = TEMP_FAILURE_RETRY(poll(&pfd,1,wr_msec));
	if(retcode > 0 && 0 == (pfd.revents & POLLOUT))
	{
		retcode = -1;
	}
	return retcode;
}
SWORD Socket::recvToBuf()
{
	SWORD retcode = 0;
	if(need_enc())
	{
		if(isset_flag(INCOMPLATE_READ))
		{
			clear_flag(INCOMPLATE_READ);
			goto do_select_enc;
		}
		_rcv_queue.wr_reserve(MAX_DATABUFFERSIZE);
		retcode = TEMP_FAILURE_RETRY(recv(sock,_rcv_queue.wr_buf(),_rcv_queue.wr_size(),MSG_NOSIGNAL));
		if(retcode == -1 && (errno == EAGAIN || errno == EWOULDBLOCK))
		{
			do_select_enc:
				retcode = waitForRead();
				if(retcode == 1)
				{
					retcode = TEMP_FAILURE_RETRY(recv(sock,_rcv_queue.wr_buf(),_rcv_queue.wr_size(),MSG_NOSIGNAL));
				}
				else
				{
					return retcode;
				}
		}
		if(retcode > 0)
		{
			success_recv_and_dec(retcode);
		}
	}
	else
	{
		if(isset_flag(INCOMPLATE_READ))
		{
			clear_flag(INCOMPLATE_READ);
			goto do_select;
		}
		_rcv_queue.wr_reserve(MAX_DATABUFFERSIZE);
		retcode = TEMP_FAILURE_RETRY(recv(sock,_rcv_queue.wr_buf(),_rcv_queue.wr_size(),MSG_NOSIGNAL));
		if(retcode == -1 && (errno == EAGAIN || errno == EWOULDblock()))
		{
			do_select:
				retcode = waitForRead();
				if(retcode == 1)
				{
					retcode = TEMP_FAILURE_RETRY(recv(sock,_rcv_queue.wr_buf(),_rcv_queue.wr_size(),MSG_NOGIGNAL));
				}
				else
				{
					return retcode;
				}
		}
		if(retcode > 0)
		{
			success_recv();
		}
	}
	if(!retcode)
	{
		return -1;
	}
	return retcode;
}
DWORD Socket::packetUnpack(BYTE *in,const DWORD packetLen,BYTE *out)
{
	DWORD recvCmdLen = packetLen - PH_LEN;
	if(PACKET_ZIP == ((*(DWORD*)in) & PACKET_ZIP))
	{
		SWORD unZipLen = MAX_DATASIZE;
		SWORD retcode = zlib_uncompress(out,&unZipLen,&(in[PH_LEN]),recvCmdLen);
		switch(retcode)
		{
			case Z_OK:
				break;
			case Z_MEM_ERROR:
				break;
			case Z_BUF_ERROR:
				break;
			case Z_DATA_ERROR:
				break;
		}
		return unZipLen;
	}
	else
	{
		bcopy(&(in[PH_LEN]),out,recvCmdLen);
		return recvCmdLen;
	}
}
DWORD Socket::getMaxDataSize()const
{
	return Socket::MAX_DATASIZE;
}
				


int Socket::sendData(const DWORD dwNum)
{
	tQueue.rd_flip( dwNum );
	m_dwSendCount += dwNum;
	int size = tQueue.rd_size();
	if(!size) return dwNum;
	tQueue.lock();
	DWORD sendNum = read(socket,tQueue.rd_buf(),size);
	tQueue.unlock();
	if(sendNum) return size;
	else if(sendNum < 0)
	{
		if(errno == EAGAIN) return -1;
	}
	else
	{
		return -1;
	}
	return size;
}

