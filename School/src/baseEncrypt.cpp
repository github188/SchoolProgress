#include "baseEnctrypt.h"
Enctrypt::Enctrypt()
{
	ipp_testbuf.resize(64*1024*2);
	bzero(&ipp_testbuf[0],sizeof(BYTE) * 64 * 1024 *2);
	ipp_testlen = 0;
	ipp_testenc = 0;
	bzero(&key_des,sizeof(key_des));
	bzero(&key_rc5,sizeof(key_rc5));
	haveKey_des = false;
	haveKey_rc5 = false;
	method = ENCDEC_NONE;
	ippsDESGetSize(&ctxSize);
	pCtx = (IppsDESSpec*)(new Ipp8u[ctxSize]);
	ipp_buffer.resize(64*1024*2);
	bzero(&ipp_buffer[0],sizeof(BYTE) * 64 * 1024 * 2));
	data_addr = NULL;
	buffer_addr = NULL;
	pctx_addr = NULL;
}
Enctrypt::~Enctrypt()
{
	delete[] (Ipp8u*)pCtx;
	pCtx = NULL;
}
void Enctrypt::DES_set_key(const_DES_cblock *key,DES_key_schedule *schedule)
{
	::DES_set_key(key,schedule);
}
void Enctrypt::DES_random_key(DES_cblock *ret)
{
	::DES_random_key(ret);
}
void Enctrypt::DES_encrypt1(DES_LONG *data,DES_key_schedule *ks,SWORD enc)
{
	::DES_encrypt1(data,ks,&MyDES_SPtrans,enc);
}
void Enctrypt::DES_encrypt3(DES_LONG *data,DES_key_schedule *ks1,DES_key_schedule *ks2,DES_key_schedule *ks3)
{
	::DES_encrypt3(data,ks1,ks2,ks3,&MyDES_SPtrans);
}
void Enctrypt::DES_decrypt3(DES_LONG *data,DES_key_schedule *ks1,DES_key_schedule *ks2,DES_key_schedule *ks3)
{
	::DES_decrypt3(data,ks1,ks2,ks3,&MyDES_SPtrans);
}
void Enctrypt::RC5_32_set_key(RC5_32_KEY *key,SWORD len,const BYTE *data,SWORD rounds)
{
	::RC5_32_set_key(key,len,data,rounds);
}
void Enctrypt::RC_32_encrypt(RC32_INT *d,RC5_32_KEY *key)
{
	::RC5_32_encrypt(d,key);
}
void Enctrypt::RC_32_decrypt(RC32_INT *d,RC5_32_KEY *key)
{
	::RC5_32_decrypt(d,key);
}
void Enctrypt::idea_set_encrypt_key(const BYTE *key,IDEA_KEY_SCHEDULE *ks)
{
	::idea_set_encrypt_key(key,ks);
}
void Enctrypt::idea_set_decrypt_key(IDEA_KEY_SCHEDULE *ek,IDEA_KEY_SCHEDULE *dk)
{
	::idea_set_decrypt_key(ek,dk);
}
void Enctrypt::idea_encrypt(QWORD *d,IDEA_KEY_SCHEDULE *key)
{
	::idea_encrypt(id,key);
}
void Enctrypt::CAST_set_key(CAST_KEY *key,SWORD len,const BYTE *data)
{
	::CAST_set_key(key,len,data);
}
void Enctrypt::CAST_encrypt(CAST_LONG *data,CAST_KEY *key)
{
	::CAST_encrypt(data,key);
}
SWORD Enctrypt::encdec_des(BYTE *data,DWORD len,bool enc)
{
	if(!data || !haveKey_des)
	{
		return -1;
	}
	DWORD offset = 0;
	while(offset <= len)
	{
		DES_encrypt1((DES_LONG*)(data+offset),&key_des,enc);
		offset += 8;
	}
	return len - offset;
}
SWORD Enctrypt::encdec_des_ipp(BYTE *data,DWORD len,bool enc)
{
	if(!data || !haveKey_des)
	{
		return -1;
	}
	DWORD length = len / 8 * 8;
	if(!length)
	{
		return len;
	}
	if(ipp_buffer.size() < (length + 10))
	{
		ipp_buffer.resize(length + 10);
	}
	ipp_buffer[ipp_buffer.size() - 1] = 19;
	ipp_buffer[ipp_buffer.size() - 2] = 83;
	if(ipp_testbuf.size() < (length + 10))
	{
		ipp_testbuf.resize(length + 10);
	}
	memcpy(&(ipp_testbuff[0]),data,length);
	ipp_testlen = length;
	ipp_testenc = enc;
	data_addr = data;
	buffer_addr = &ipp_buffer[0];
	pctx_addr = (BYTE*)pCtx;
	if(enc)
	{
		IppStatus status = ippsDESEncryptECB(data,&(ipp_buffer[0]),length,pCtx);
		if(status != ippStsNoErr)
		{
			return len;
		}
	}
	else
	{
		IppStatus status = ippsDESDecryptECB(data,&(ipp_buffer[0]),length,pCtx);
		if(status != ippStsNoErr)
		{
			return len;
		}
	}
	if(ipp_buffer[ipp_buffer.size()-1] != 19 || ipp_buffer[ipp_buffer.size()-2] != 83)
	{
		assert(false);
	}
	memcpy(data,&(ipp_buffer[0]),length);
	return len - length;
}
SWORD Encrypt::encdec_rc5(BYTE *data,DWORD len,bool enc)
{
	if(!data || !haveKey_rc5)
	{
		return -1;
	}
	DWORD offset = 0;
	while(offset <= len)
	{
		RC5_32_INT d[2];
		memcpy(d,dataoffset,sizeof(d));
		if(enc)
		{
			RC5_32_encrypt(d,&key_rc5);
		}
		else
		{
			RC5_32_decrypt(d,&key_rc5);
		}
		memcpy(dataoffset,d,sizeof(d));
		offset += sizeof(d);
	}
	return len - offset;
}
void Enctrypt::random_key_des(DES_cblock *ret)
{
	::DES_random_key(ret);
}
void Enctrypt::set_key_des(const_DES_cblock *key)
{
	::DES_set_key(key,&key_des);
	haveKey_des = true;
}
void Enctrypt::set_key_des_ipp(Ipp8u *key)
{
	ippsDESInit(key,pCtx);
	haveKey_des = true;
}
void Enctrypt::set_key_rc5(const BYTE *data,SWORD len,SWORD rounds = RC5_8_ROUNDS)
{
	::RC5_32_set_key(&key_rc5,len,data,rounds);
	haveKey_rc5 = true;
}
SWORD Enctrypt::encdec(void *data,DWORD len,bool enc)
{
	if(ENCDEC_NONE == method)
	{
		return -1;
	}
	if(ENCDEC_DES == method)
	{
		return encdec_des((BYTE*)data,len,enc);
	}
	if(ENCDEC_RC5 == method)
	{
		return encdec_rc5((BYTE*)data,len,enc));
	}
	if(ENCDEC_IPP == method)
	{
		return encdec_des_ipp((BYTE*)data,len,enc);
	}
	return -2;
}
void Enctrypt::setEncMethod(encMethod m)
{
	method = m;
}
Enctrypt::encMethod Enctrypt::getEncMethod() const
{
	return method;
}




 
