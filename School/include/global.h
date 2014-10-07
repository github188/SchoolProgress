#ifndef GLOBAL_H
#define GLOBAL_H
#include<iostream>
#include<math.h>
#include<baseDef.h>
using namespace std;

namespace Global
{
	int randBetween(int min,int max);
};

namespace Cmd
{
	const BYTE CMD_NULL = 0;
	const BYTE PARA_NULL = 0;
	
	struct t_NullCmd
	{
		BYTE cmd;
		BYTE para;
		t_NullCmd(const BYTE _cmd = CMD_NULL,const BYTE _para = PARA_NULL):cmd(_cmd),para(_para)
		{
		}
	};
};

#endif
