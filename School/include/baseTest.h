#ifndef BASE_TEST_H
#define BASE_TEST_H
#include "baseLog.h"
#include "zlib.h"
#include "baseDef.h"
namespace Test
{
	extern Logger *logger;
	int randBetween(int min,int max);
	char upper(char value);
	SWORD lib_uncompress(Bytef *dest,uLongf *destLen,const Bytef *source,uLong sourceLen);
	SWORD lib_compress2(Bytef *dest,uLongf *destLen,const Bytef *source,QWORD sourceLen,const SWORD level);
	voidpf calloc_Test(voidpf opaque,DWORD items,DWORD size);
	SWORD lib_compress(Bytef *dest,uLongf *destLen,const Bytef *source,QWORD sourceLen);
	void cfree_Test(voidpf opaque,voidpf ptr);	

};

#endif
	
