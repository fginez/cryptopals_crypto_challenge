#ifndef AES128ECB_H_
#define AES128ECB_H_

int aes128ecb_encrypt(const unsigned char* clearbuffer, const int clearlen,
                      unsigned char* encryptedbuffer, int * encryptedlen, const int maxencryptedlen,
					  const unsigned char* key, const int keylen);

int aes128ecb_decrypt(const unsigned char* encryptedbuffer, const int encryptedlen,
                      unsigned char* clearbuffer, int * clearlen, const int maxclearlen,
					  const unsigned char* key, const int keylen);

#endif /*AES128ECB_H_*/
