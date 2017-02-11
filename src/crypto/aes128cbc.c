#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>

#include "../include/aes128cbc.h"

int aes128cbc_encrypt(const unsigned char* clearbuffer, const int clearlen,
                      unsigned char* encryptedbuffer, int * encryptedlen, const int maxencryptedlen,
					            const unsigned char* key, const int keylen,
					            const unsigned char* iv, const int ivlen)
{

  return 0;
}

int aes128cbc_decrypt(const unsigned char* encryptedbuffer, const int encryptedlen,
                      unsigned char* clearbuffer, int * clearlen, const int maxclearlen,
					  const unsigned char* key, const int keylen,
					  const unsigned char* iv, const int ivlen)
{

	return 0;
}
