#include "baseTest.h"
namespace Test
{
	Logger *logger = NULL;
	int randBetween(int min,int max)
	{
		int grap = 0;
		if( min == max )
		{
			return min;
		}
		if( min > max )
		{
			grap = min - max;
			return max +  rand() % (grap + 1);
		}
		else
		{
			grap = max - min;
			return min + rand() % (grap + 1);
		}
	}

	char upper(char value)
	{
		if(value >= 'A' && value <= 'Z')
		{
			value += 32;
		}
		return value;
	}
	SWORD lib_uncompress(Bytef *dest,uLongf *destLen,const Bytef *source,uLong sourceLen)
	{
		z_stream stream;
		SWORD err;
		stream.next_in = (Bytef*)source;
		stream.avail_in = (uInt)sourceLen;
		if((uLong)stream.avail_in != sourceLen)
		{
			return Z_BUF_ERROR;
		}
		stream.next_out = dest;
		stream.avail_out = (uInt)*destLen;
		if((uLong)stream.avail_out != *destLen)
		{
			return Z_BUF_ERROR;
		}
		stream.zalloc = (alloc_func)calloc_Test;
		stream.zfree = (free_func)cfree_Test;
		err = inflateInit(&stream);
		if(err != Z_OK)
		{
			return err;
		}
		err = inflate(&stream,Z_FINISH);
		if(err != Z_STREAM_END)
		{
			inflateEnd(&stream);
			return err == Z_OK ? Z_BUF_ERROR :err;
		}
		*destLen = stream.total_out;
		err = inflateEnd(&stream);
		return err;
	}
	SWORD lib_compress2(Bytef *dest,uLongf *destLen,const Bytef *source,QWORD sourceLen,const SWORD level)
	{
		z_stream stream;
		SWORD err;
		stream.next_in = (Bytef*)source;
		stream.avail_in = (uInt)sourceLen;
		stream.next_out = dest;
		stream.avail_out = (uInt)*destLen;
		if((uLong)stream.avail_out != *destLen)
		{
			return Z_BUF_ERROR;
		}
		stream.zalloc = (alloc_func)calloc_Test;
		stream.zfree = (free_func)cfree_Test;
		stream.opaque = (voidpf)0;
		err = deflateInit(&stream,level);
		if(err != Z_OK)
		{
			return err;
		}
		err = deflate(&stream,Z_FINISH);
		if(err != Z_STREAM_END)
		{
			deflateEnd(&stream);
			return err == Z_OK ? Z_BUF_ERROR : err;
		}
		*destLen = stream.total_out;
		err = deflateEnd(&stream);
		return err;
	}
	voidpf calloc_Test(voidpf opaque,DWORD items,DWORD size)
	{
		return (voidpf)malloc(items * size);
	}
	void cfree_Test(voidpf opaque,voidpf ptr)
	{
		free(ptr);
	}
	SWORD lib_compress(Bytef *dest,uLongf *destLen,const Bytef *source,QWORD sourceLen)
	{
		return lib_compress2(dest,destLen,source,sourceLen,Z_DEFAULT_COMPRESSION);
	}
		


}
