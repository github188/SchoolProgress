#ifndef BASE_CMD_H
#define BASE_CMD_H
#include "baseDef.h"
namespace Cmd
{
	struct t_NullCmd
	{
		t_NullCmd()
		{
			bzero(this,sizeof(*this));
		}
		BYTE byCmd;
		BYTE param;
	};
	
	struct t_ZipCmdPackNullCmd : public t_NullCmd
	{
	};
};
#endif
	
