#ifndef AES128CBC_H_
#define AES128CBC_H_

#include "aes128ecb.h"
#include "aes_common.h"

int aes128cbc_encrypt(const unsigned char* clearbuffer, const unsigned int clearlen,
                      unsigned char* encryptedbuffer, unsigned int * encryptedlen, const unsigned int maxencryptedlen,
					            const unsigned char* key, const int keylen,
					            const unsigned char* iv, const int ivlen);

int aes128cbc_decrypt(const unsigned char* encryptedbuffer, const int encryptedlen,
                      unsigned char* clearbuffer, int * clearlen, const int maxclearlen,
                      const unsigned char* key, const int keylen,
                      const unsigned char* iv, const int ivlen);

#endif
