#include "baseSuperClient.h"

SuperClient::SuperClient():TcpClientBufferQueue("服务器管理器客户端"),verify(false)
{
}

SuperClient::~SuperClient()
{
}

void SuperClient::run()
{
	TcpClientBuffer::run();
#if 0
	SubNetService::getInstance().Terminate();
#endif
}

bool SuperClient::msgParseStart(const Cmd::NullCmd *nullCmd,const DWORD cmdLen)
{
#if 0
	using namespace Cmd::Server;
	switch(nullCmd->byParam)
	{
		case GAMETIME_START_SERVERCMD_PARA:
			{
				stGameTimeServerCmd *cmd = (stGameTimeServerCmd*)nullCmd;
				return true;
			}
			break;
		case GAMEZONE_START_SERVERCMD_PARA:
			{
				stGameZoneStartServerCmd *cmd = (stGameZoneStartServerCmd*)nullCmd;
				SubNetService::getInstance().setZoneID(cmd->zone);
				SubNetService::getInstance().setZoneName(cmd->name);
				return true;
			}
			break;
		case RESPONSE_START_SERVERCMD_PARA:
			{
				stResponseStartServerCmd *cmd = (stResponseStartServerCmd*)nullCmd;
				SubNetService::getInstance.setServerInfo(cmd);
				return true;
			}
			break;
		case SERVERENTRY_NOTIFYME_START_SERVERCMD_PARA:
			{
				stServerEntryNotifyMeStartServerCmd *cmd = (stServerEntryNotifyMeStartServerCmd*)nullCmd;
				for(size_t index = 0;index < cmd->size;++index)
				{
					SubNetService::getInstance().addServerEntry(cmd->entry[index]);
				}
				if(!verify)
				{
					verify = true;
				}
				return true;
			}
			break;
		case SERVERENTRY_NOTIFYOTHER_START_SERVERCMD_PARA:
			{
				stServerEntryNotifyOtherStartServerCmd *cmd = (stServerEntryNotifyOtherStartServerCmd*)nullCmd;
				if(SubNetService::getInstance().addServerEntry(cmd->entry))
				{
					if(SubNetService::getInstance().getServerType() > cmd->entry.serverType)
					{
						SubNetService::getInstance().addNewServer(cmd->entry.serverType);
					}
				}
				if(SubNetService::getInstance().getServerType < cmd->entry.serverType)
				{
					return sendCmd(cmd,cmdLen);
				}
				return true;
			}
			break;
		case OK_START_SERVERCMD_PARA:
			{
				SubNetService::getInstance().startupOver();
				return true;
			}
			break;
		case SHUTDOWN_START_SERVERCMD_PARA:
			{
				SubNetService::getInstance().TerminateWait();
				return true;
			}
			break;
		case RELOAD_TABLE_SERVERCMD_PARA:
			{
				stReloadTableStartServerCmd *rev = (stReloadTableStartServerCmd*)nullCmd;
				if(reloadDBManager(rev->name))
				{
				}
				return true;
			}
			break;
		default:
			break;
	}
#endif
	return false;
}

bool SuperClient::msgParseForward(const Cmd::NullCmd *nullCmd,const DWORD cmdLen)
{
#if 0
	using namespace Cmd::Server;
	if(!SubNetService::getInstance().startup)
	{
		return false;
	}
	switch(nullCmd->byParam)
	{
		case FL_SERVER_FORWARD_SERVERCMD:
			{
				stFLServerForwardServerCmd *rev = (stFLServerForwardServerCmd*)nullCmd;
				SubNetService::getInstance().msgParse_FLServer((Cmd::NullCmd*)rev->data,rev->dataSize);
				return true;
			}
			break;
		case MONITOR_SERVER_FORWARD_SERVERCMD:
			{
				stMonitorServerForwardServerCmd *rev = (stMonitorServerForwardServerCmd*)nullCmd;
				SubNetService::getInstance().msgParse_MonitorServer((Cmd::NullCmd*)rev->data,rev->dataSize);
				return true;
			}
			break;
		case NAME_SERVER_FORWARD_SERVERCMD:
			{
				stNameServerForwardServerCmd *rev = (stNameServerForwardServerCmd*)nullCmd;
				SubNetService::getInstance().msgParse_NameServer((Cmd::NullCmd*)rev->data,rev->dataSize);
				return true;
			}
			break;
		case USER_SERVER_FORWARD_SERVERCMD:
			{
				stUserServerForwardServerCmd *rev = (stUserServerForwardServerCmd*)nullCmd;
				SubNetService::getInstance().msgParse_UserServer((Cmd::NullCmd*)rev->data,rev->dataSize);
				return true;
			}
			break;
		case SHARE_FORWARD_SERVERCMD:
			{
				stShareForwardServerCmd *rev = (stShareForwardServerCmd*)nullCmd;
				SubNetService::getInstance().msgParseLogin((Cmd::NullCmd*)rev->data,rev->dataSize);
				return true;
			}
			break;
		case INFO_SERVER_FORWARD_SERVERCMD:
			{
				stInfoServerForwardServerCmd *rev = (stInfoServerForwardServerCmd*)nullCmd;
				SubNetService::getInstance().msgParse_InfoServer((Cmd::NullCmd*)rev->data,rev->dataSize);
				return true;
			}
			break;
		case ROLE_SERVER_FORWARD_SERVERCMD:
			{
				stRoleServerForwardServerCmd *rev = (stRoleServerForwardServerCmd*)nullCmd;
				SubNetService::getInstance().msgParse_RoleServer(Cmd::NullCmd*)rev->data,rev->dataSize);
				return true;
			}
			break;
		default:
			{
				SubNetService::getInstance().msgParse_SuperService(nullCmd,cmdLen);
				return true;
			}
			break;
	}
#endif
	return false;
}

bool SuperClient::msgParse(const Cmd::NullCmd *nullCmd,const DWORD cmdLen)
{
#if 0
	if(!SubNetService::getInstance().startup)
	{
		return false;
	}
	return SubNetService::getInstance().msgParse_SuperService(nullCmd,cmdLen);
#endif
}


		


