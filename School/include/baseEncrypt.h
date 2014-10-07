#ifndef BASE_ENCRYPT_H
#define BASE_ENCRYPT_H
#include "baseDef.h"
#include <iostream>
#include <vector.h>
#include <zlib.h>
#include <openssl/aes.h>
#include "baseDef.h"
using namespace std;
class Encrypt
{
	public:
		std::vector<BYTE> ipp_testbuf;
		DWORD ipp_testlen;
		BYTE ipp_testenc;
		BYTE *data_addr;
		BYTE *buffer_addr;
		BYTE *pctx_addr;
	public:
		Encrypt();
		~Encrypt();
		enum encMethod
		{
			ENCDEC_NONE,
			ENCDEC_DES,
			ENCDEC_RCS,
			ENCDEC_IPP
		};
		void random_key_des(DES_cblock *ret);
		void set_key_des(const_DES_cblock *key);
		void set_key_des_ipp(Ipp8u *key);
		void set_key_rc5(const BYTE *data,SWORD len,SWORD rounds);
		SWORD encdec(void *data,DWORD len,bool enc);
		void setEncMethod(encMethod methond);
		encMethod getEncMethod() const;
	private:
		void DES_rand_key(DES_cblock *ret);
		void DES_set_key(const_DES_cblock *key,DES_key_schedule *schedule);
		void DES_encrypt1(DES_LONG *data,DES_key_schedule *ks,SWORD enc);
		void DES_encrypt3(DES_LONG *data,DES_key_schedule *ks1,DES_key_schedule *ks2,DES_key_schedule *ks3);
		void DES_decrypt3(DES_LONG *data,DES_key_schedule *ks1,DES_key_schedule *ks2,DES_key_schedule *ks3);
		void RC5_32_set_key(RC5_32_KEY *key,SWORD len,const BYTE *data,SWORD rounds);
		void RC5_32_encrypt(RC5_32_INF *d,RC5_32_KEY *key);
		void RC5_32_decrypt(RC5_32_INF *d,RC5_32_KEY *key);
		void idea_set_encrypt_key(const BYTE *key,IDEA_KEY_SCHEDULE *ks);
		void idea_set_decrypt_key(IDEA_KEY_SCHEDULE *ek,IDEA_KEY_SCHEDULE *dk);
		void idea_encrypt(QWORD *d,IDEA_KEY_SCHEDULE *key);
		void CAST_set_key(CAST_KEY *key,SWORD len,const BYTE *data);
		void CAST_encrypt(CAST_LONG *data,CAST_KEY *key);
		void CAST_decrypt(CAST_LONG *data,CAST_KEY *key);
		SWORD encdec_des(BYTE *data,DWORD len,bool enc);
		SWORD encdec_des_ipp(BYTE *data,DWORD len,bool enc);
		SWORD encdec_rc5(BYTE *data,DWORD len,bool enc);
		DES_key_schedule key_des;
		RC5_32_KEY key_rc5;
		bool haveKey_des;
		bool haveKey_rc5;
		encMethod method;
		IppsDESSpec *pCtx;
		SWORD ctxSize;
		std::vector<BYTE> ipp_buffer;
};


#endif


