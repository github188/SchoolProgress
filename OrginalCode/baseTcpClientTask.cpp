
TcpClientTaskBase::TcpClientTaskBase(const std::string &ip,const DWORD port,const bool compress,const bool reConn,const DWORD reConnTimer) : pSocket(NULL),compress(compress),reConn(reConn),ip(ip),port(port),_tick_timer(reConnTimer,false,3600*1000L)
{
	lifeTime,now();
	state = close;
	terminate = TM_no;
	mainloop = false;
	fdsradd = false;
	tick = false;
}
void TcpClientTaskBase::resetTickTimer(DWORD howLong)
{
	_tick_timer.reset(howLong,Timer());
}
bool TcpClientTaskBase::connect()
{
	int retcode;
	int sock;
	struct sockaddr_in addr;
	sock = ::socket(PF_INET,SOCK_STREAM,0);
	if(sock==-1)
	{
		return false;
	}
	socklen_t windowSize = 128*1024;
	retcode = ::setsockopt(sock,SOL_SOCKET,SO_RCVBUF,&windowSize,size(windowSize));
	if(retcode==-1)
	{
		TEMP_FAILURE_RETRY(::close(sock));
		return false;
	}
	retcode = ::setsockopt(sock,SOL_SOCKET,SO_SNDBUF,&windowSize,sizeof(windowSize));
	if(retcode == -1)
	{
		TEMP_FAILURE_RETRY(::close(sock));
		return false;
	}
	bzero(&addr,sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(ip.c_str());
	addr.sin_port = htons(port);
	retcode = TEMP_FAILURE_RETRY(::connect(sock,(struct sockaddr*)&addr,sizeof(addr)));
	if(retcode == -1)
	{
		TEMP_FAILURE_RETRY(::close(sock));
		return false;
	}
	pSocket = new Socket(sock,&addr,compress);
	if(!pSocket)
	{
		TEMP_FAILURE_RETRY(::close(sock));
		return false;
	}
	Global::logger->info("创建到服务器%s,%u的连接成功",ip.c_str(),port);
	return true;
}
void TcpClientTaskBase::checkConn()
{
	Time currentTime;
	if(_tick_timer(currentTime))
	{
		if(checkTick())
		{
			Terminate(TcpClientBase::TM_sock_error);
			clearTick();
		}
		else
		{
			Cmd::t_ClientNullCmd tNullCmd;
			if(sendCmd(&tNullCmd,sizeof(tNullCmd)))
			{
				setTick();
			}
		}
	}
}
bool TcpClientTaskBase::sendCmd(const void *cmd,const int cmdLen)
{
	Cmd::t_NullCmd *ptNullCmd = (Cmd::t_NullCmd*)cmd;
	analysisSendingCmd(ptNullCmd->byCmd,ptNullCmd->byParam,cmdLen);
	switch(state)
	{
		case close:
			if(!pSocket)
			{
				return false;
			}
			return pSocket->sendCmd(cmd,cmdLen);
			break;
		case okay:
		case recycle:
			if(!pSocket)
			{
				return false;
			}
			return pSocket->sendCmd(cmd,cmdLen,true);
			break;
	}
	return false;
}
bool TcpClientTaskBase::sendLoginCmd()
{
	using namespace Cmd::Server;
	stLoginStartServerCmd cmd;
	cmd.ServerID = SubNetService::getInstance().getServerID();
	cmd.ServerType = SubNetService::getInstance().getServerType();
	return sendCmd(&cmd,sizeof(cmd));
}
bool TcpClientTaskBase::ListeningRecv(bool needRecv)
{
	int retcode = 0;
	if(needRecv)
	{
		retcode = pSocket->recvToBuf_NoPoll();
	}
	if(retcode == -1)
	{
		return false;
	}
	do{
		BYTE pstrcmd[Socket::MAX_DATASIZE];
		int cmdLen = pSocket->recvToCmd_NoPoll(pstrcmd,sizeof(pstrcmd));
		if(cmdLen<=0)
		{
			break;
		}
		Cmd::t_NullCmd *ptNullCmd = (Cmd::t_NullCmd*)pstcmd;
		if(ptNullCmd->byCmd == Cmd::CMD_NULL)
		{
			if(ptNullCmd->byParam == Cmd::SERVER_PARA_NULL)
			{
				if(!sendCmd(pstrcmd,cmdLen))
				{
					return false;
				}
			}
			else if(Cmd::CLIENT_PARA_NULL == ptNullCmd->byParam)
			{
				clearTick();
			}
			else if(Cmd::ZIP_CMD_PACK_PARA_NULL == ptNullCmd->byParam)
			{
				parse(ptNullCmd,cmdLen);
			}
		}
		else
		{
			parse(ptNullCmd,cmdLen);
			analysisRecvingCmd(ptNullCmd->byCmd,ptNullCmd->byParam,cmdLen);
		}
	}while(true);
	return true;
}
bool TcpClientTaskBase::ListeningSend()
{
	if(pSocket)
	{
		return pSocket->sync();
	}
	return false;
}
void TcpClientTaskBase::onReconnect()
{
}
void TcpClientTaskBase::getNextState()
{
	ConnState oldState = getState();
	lifeTime.now();
	switch(oldState)
	{
		case close:
			setState(sync);
			break;
		case sync:
			addToContainer();
			setState(okay);
			onReconnect();
			break;
		case okay:
			removeFromContainer();
			setState(recycle);
			break;
		case recycle:
			if(terminate == TM_service_close)
			{
				recycleConn();
			}
			setState(close);
			final();
			break;
	}
}
void TcpClientTaskBase::resetState()
{
	ConnState oldState = getState();
	lifeTime.now();
	setState(close);
	final();
}


