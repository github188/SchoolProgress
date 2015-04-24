#include "baseTcpTaskQueue.h"

bool TcpTaskQueue::parse(const Cmd::NullCmd *cmd,const unsigned int cmdLen)
{
	return CmdMsgParse(cmd,cmdLen);
}
