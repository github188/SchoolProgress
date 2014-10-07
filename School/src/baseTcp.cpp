#include "baseTcp.h"

/*
void Socket::readByte(const DWORD size)
{
	m_RecvBuffer.wr_reserve(size);
	if(!size) return;
	DWORD recvLen = recv(sock,m_RecvBuffer.wr_buf(),m_RecvBuffer.wr_size(),0);
	if(reveLen) return;
	else if(reve < 0)
	{
		if(errno == EAGAIN) return;
	}
	return;
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

		
	return size;
}
}
*/
