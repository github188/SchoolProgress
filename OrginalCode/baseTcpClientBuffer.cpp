#include "baseTcpClientBuffer.h"

bool TcpClientBuffer::listeningSend()
{
	if(!m_pSocket)
	{
		return false;
	}
	return m_pSocket->sync();
}

bool TcpClientBuffer::listeningRecv()
{
	SDWORD retcode = m_pSocket->recvToBuf_NoPoll();
	CheckConditonReturn(retcode!=-1,false);
	do
	{
		BYTE cmd[Socket::s_maxDataSize];
		SDWORD cmdLen = m_pSocket->recvToCmd_NoPoll(cmd,sizeof(cmd));
		CheckConditonReturn(cmdLen>0,true);
		
		Cmd::NullCmd *nullCmd = (Cmd::NullCmd*)cmd;
		Global::logger->debug("client accept the msg:%u,%u",nullCmd->byCmd,nullCmd->byParam);
		if(Cmd::CMD_NULL == nullCmd->byCmd)
		{
			if(Cmd::SERVER_PARA_NULL == nullCmd->byParam)
			{
				LogErrorCheckCondition(sendCmd(nullCmd,sizeof(*nullCmd)),true,"管理服务器客户端发送信号数据失败%s,%u",m_ip,m_port);
			}
			else if(Cmd::CLIENT_PARA_NULL == nullCmd->byParam)
			{
			}
		}
		else
		{
			parse(nullCmd,cmdLen);
			analysisRecvingCmd( nullCmd->byCmd,nullCmd->byParam,cmdLen );
		}
	}while( true );
	return true;
}


void TcpClientBuffer::sync()
{
	if(m_pSocket)
	{
		m_pSocket->force_sync();
	}
}

bool TcpClientBuffer::sendCmd(const void *strCmd,const int cmdLen)
{
	LogErrorCheckCondition(m_pSocket,false,"套接字发送消息失败套接子为空");
	
	Cmd::NullCmd *nullCmd = (Cmd::NullCmd*)strCmd;
	analysisSendingCmd(nullCmd->byCmd,nullCmd->byParam,cmdLen);
	return m_pSocket->sendCmd(strCmd,cmdLen,m_bufferFlg);
}

void TcpClientBuffer::run()
{
	m_bufferFlg = true;
	struct pollfd pfds;
	struct pollfd pfds_r;
	m_pSocket->fillPollFd(pfds,POLLIN|POLLOUT|POLLERR|POLLPRI);
	m_pSocket->fillPollFd(pfds_r,POLLIN|POLLOUT|POLLERR|POLLPRI);
	QWORD time = m_usleepTime;
	while(!isFinal())
	{
		setRuning();
		struct timespec beginTv,endTv;
		clock_gettime(CLOCK_REALTIME,&beginTv);
		if(TEMP_FAILURE_RETRY(::poll(&pfds_r,1,time/1000L)) > 0)
		{
			if(pfds_r.revents & POLLERR)
			{
				break;
			}
			else
			{
				if(pfds_r.revents & POLLIN)
				{
					if(!listeningRecv())
					{
						if(m_reconnect)
						{
							break;
						}
						else
						{
							break;
						}
					}
				}
			}
		}
		clock_gettime(CLOCK_REALTIME,&_tv_2);
		long end = endTv.tv_sec * 1000000L + endTv.tv_nsec / 1000L;
		long begin = beginTv.tv_sec * 1000000L + beginTv.tv_nsec / 1000L;
		time -= (end - begin);
		if(time <= 0)
		{
			if(TEMP_FAILURE_RETRY(::poll(&pfds,1,0) > 0) > 0)
			{
				if(pfds.revents & POLLERR)
				{
					break;
				}
				else
				{
					if(pfds.revents & POLLIN)
					{
						if(!listeningRecv())
						{
							if(m_reconnect)
							{
								break;
							}
							else
							{
								break;
							}
						}
					}
					if(pfds.revents & POLLOUT)
					{
						if(!listeningSend())
						{
							if(m_reconnect)
							{
								break;
							}
							else
							{
								break;
							}
						}
					}
				}
			}
			time = m_usleepTime;
		}
	}
	sync();
	m_bufferFlg = false;
}

bool TcpClientBufferQueue::parse(const Cmd::NullCmd *nullCmd,const unsigned int cmdLen)
{
	return cmdMsgParse(nullCmd,cmdLen);
}


