#ifndef AES128ECB_H_
#define AES128ECB_H_

int aes128ecb_decrypt(const unsigned char* encryptedbuffer, int encryptedlen,
                      unsigned char* clearbuffer, int * clearlen, const unsigned char* key);

#endif /*AES128ECB_H_*/
