#ifndef _NULLCMD_H
#define _NULLCMD_H
#include "baseDef.h"

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning(disable : 4200)
#endif
#pragma pack(1)
_CMD_NAMESPACE_BEGIN
const BYTE CMD_NULL = 0;
const BYTE PARA_NULL = 0;

struct NullCmd
{
	BYTE	byCmd;
	BYTE	byParam;
	NullCmd(const BYTE cmd = CMD_NULL,const BYTE para = PARA_NULL):byCmd(cmd),byParam(para)
	{
	}
};

const BYTE SERVER_PARA_NULL = 0;
struct ServerNullCmd : public NullCmd
{
	ServerNullCmd()
	{
		byCmd = CMD_NULL;
		byParam = SERVER_PARA_NULL;
	}
};
const BYTE CLIETN_PARA_NULL = 1;
struct ClientNullCmd : public NullCmd
{
	ClientNullCmd()
	{
		byCmd = CMD_NULL;
		byParam = CLIETN_PARA_NULL;
	}
};

const BYTE ZIP_CMD_PARA_NULL = 2;
struct ZipCmdPackNullCmd : public NullCmd
{
	ZipCmdPackNullCmd()
	{
		byCmd = CMD_NULL;
		byParam = ZIP_CMD_PARA_NULL;
		size = 0;
	}
	inline DWORD allSize()
	{
		return sizeof(*this) + size;
	}
	inline DWORD dataSize()
	{
		return size;
	}
	DWORD size;
	char data[0];
};

struct NullUserCmd : public NullCmd
{
	DWORD timeStamp;
};

_CMD_NAMESPACE_END

#pragma pack()
#ifdef _MSC_VER
#pragma warning( pop )
#endif

#endif
