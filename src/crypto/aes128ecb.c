#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>

#include "aes128ecb.h"

int aes128ecb_decrypt(const unsigned char* encryptedbuffer, int encryptedlen,
                      unsigned char* clearbuffer, int * clearlen, const unsigned char* key)
{
	int tmplen;
	EVP_CIPHER_CTX * ctx;
	
	ERR_load_crypto_strings();
	OpenSSL_add_all_algorithms();
	OPENSSL_config(NULL);
	
	printf("aes128ecb_decrypt [in] inp=%8.8X il=%d k=%8.8X\n", 
           (unsigned int) encryptedbuffer, 
           (unsigned int) encryptedlen, 
           (unsigned int) key); 
	
	if ( !(ctx = EVP_CIPHER_CTX_new()) )
	{
		return -1;
	}
	
	if (1 != EVP_DecryptInit_ex(ctx, EVP_aes_128_ecb(), NULL, key, NULL))
	{
		return -1;
	}
	
	if (1 != EVP_DecryptUpdate(ctx, clearbuffer, clearlen, encryptedbuffer, encryptedlen))
	{
		return -1;	
	}
	
	if (1 != EVP_DecryptFinal_ex(ctx, clearbuffer + (*clearlen), &tmplen) )
	{
		return -1;
	}
	
	EVP_CIPHER_CTX_free(ctx);

	*clearlen += tmplen;

	printf("aes128ecb_decrypt [out] outp=%8.8X ol=%d\n", 
           (unsigned int) clearbuffer, 
           (unsigned int) *clearlen); 
           	
	return 0;
}
