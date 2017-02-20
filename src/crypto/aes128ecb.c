#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>

#include "../include/aes128ecb.h"

int aes128ecb_encrypt(const unsigned char* clearbuffer, const int clearlen,
                      unsigned char* encryptedbuffer, int * encryptedlen, const int maxencryptedlen,
                      const unsigned char* key, const int keylen)
{
	int tmplen;
	EVP_CIPHER_CTX * ctx;

	ERR_load_crypto_strings();
	OpenSSL_add_all_algorithms();
	OPENSSL_config(NULL);

	printf("aes128ecb_encrypt [in] inp=%8.8X il=%d k=%8.8X kl=%d\n",
           (unsigned int) clearbuffer,
           (unsigned int) clearlen,
           (unsigned int) key,
		   (unsigned int) keylen);

	if ( 16 != keylen )
	{
		return -1;
	}

	if ( maxencryptedlen < clearlen )
	{
		return -1;
	}

	if ( !(ctx = EVP_CIPHER_CTX_new()) )
	{
		return -1;
	}	

	if (1 != EVP_EncryptInit_ex(ctx, EVP_aes_128_ecb(), NULL, key, NULL))
	{
		return -1;
	}

	if (1 != EVP_EncryptUpdate(ctx, encryptedbuffer, encryptedlen, clearbuffer, clearlen))
	{
		return -1;
	}

	EVP_CIPHER_CTX_set_padding(ctx, 0);

	if (1 != EVP_EncryptFinal_ex(ctx, encryptedbuffer + (*encryptedlen), &tmplen) )
	{
		return -1;
	}

	EVP_CIPHER_CTX_free(ctx);

	*encryptedlen += tmplen;

	printf("aes128ecb_encrypt [out] outp=%8.8X ol=%d\n",
           (unsigned int) encryptedbuffer,
           (unsigned int) *encryptedlen);

	return 0;
}

int aes128ecb_decrypt(const unsigned char* encryptedbuffer, const int encryptedlen,
                      unsigned char* clearbuffer, int * clearlen, const int maxclearlen,
					  const unsigned char* key, const int keylen)
{
	int tmplen;
	EVP_CIPHER_CTX * ctx;

	ERR_load_crypto_strings();
	OpenSSL_add_all_algorithms();
	OPENSSL_config(NULL);

	printf("aes128ecb_decrypt [in] inp=%8.8X il=%d k=%8.8X kl=%d\n",
           (unsigned int) encryptedbuffer,
           (unsigned int) encryptedlen,
           (unsigned int) key,
		   (unsigned int) keylen);

	if ( 16 != keylen )
	{
		return -1;
	}

	if ( maxclearlen < encryptedlen )
	{
		return -1;
	}

	if ( !(ctx = EVP_CIPHER_CTX_new()) )
	{
		printf("openSSL error: %s\n", ERR_error_string(ERR_get_error(), NULL));
		return -1;
	}

	if (1 != EVP_DecryptInit_ex(ctx, EVP_aes_128_ecb(), NULL, key, NULL))
	{
		printf("openSSL error: %s\n", ERR_error_string(ERR_get_error(), NULL));
		return -1;
	}

	if (1 != EVP_DecryptUpdate(ctx, clearbuffer, clearlen, encryptedbuffer, encryptedlen))
	{
		printf("openSSL error: %s\n", ERR_error_string(ERR_get_error(), NULL));
		return -1;
	}

	EVP_CIPHER_CTX_set_padding(ctx, 0);

	if (1 != EVP_DecryptFinal_ex(ctx, clearbuffer + (*clearlen), &tmplen) )
	{
		printf("openSSL error: %s\n", ERR_error_string(ERR_get_error(), NULL));
		return -1;
	}

	// It is important to keep this call at this exact point.
	// If you use it before, padding will be re-enabled, causing
	// EVP_DecryptFinal_ex to return "bad decrypt".
	EVP_CIPHER_CTX_free(ctx);

	*clearlen += tmplen;

	printf("aes128ecb_decrypt [out] outp=%8.8X ol=%d\n",
           (unsigned int) clearbuffer,
           (unsigned int) *clearlen);

	return 0;
}
