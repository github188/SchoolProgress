#ifndef BASE_FUN_H
#define BASE_FUN_H
#include<string.h>


#define DELETE(x) { if( (x) )	{ delete (x);	(x) = NULL;	} }
#define DELETE_VEC(x) { if( (x) )	{ delete [] (x); (x) = NULL; } }


#define bcopy(src,des,desSize) memcpy(des,src,desSize)

#define bzero(ptr,size) memset(ptr,0,size)

#endif

