#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>

#include "../include/pkcs7padding.h"
#include "../include/inplace_xor.h"
#include "../include/aes128cbc.h"


int aes128cbc_encrypt(	const unsigned char* clearbuffer, const unsigned int clearlen,
						unsigned char* encryptedbuffer, unsigned int * encryptedlen, const unsigned int maxencryptedlen,
						const unsigned char* key, const int keylen,
						const unsigned char* iv, const int ivlen)
{
  unsigned char * padded_buffer = NULL, * pOut = NULL;
  unsigned char input_block[BLOCK_LEN];
  unsigned char next_iv[BLOCK_LEN];
  unsigned int  num_blocks, padded_len, i;

  // Calculate padded length
  padded_len = pkcs7padding_size(clearlen, BLOCK_LEN);
  if ( padded_len > maxencryptedlen ) {
    return -1;
  }

  padded_buffer = (unsigned char*) malloc(padded_len);
  if ( NULL == padded_buffer ) {
    return -1;
  }

  if ( -1 == pkcs7padding(BLOCK_LEN, clearlen, clearbuffer, &padded_len, padded_len, padded_buffer) ){
    return -1;
  }

  num_blocks = padded_len / BLOCK_LEN;

  memcpy(next_iv, iv, BLOCK_LEN);

  for ( i=0; i<num_blocks; i++) {
	int curr_block_len;
    // Build input block
    memcpy(input_block, &padded_buffer[i*BLOCK_LEN], BLOCK_LEN);
    inplace_xor(input_block, next_iv, BLOCK_LEN);

    // Encrypt
    aes128ecb_encrypt(input_block, BLOCK_LEN,
                      &encryptedbuffer[i*BLOCK_LEN], &curr_block_len, BLOCK_LEN,
                      key, keylen);

    // update IV
    if ( i<num_blocks )
      memcpy(next_iv, &encryptedbuffer[i*BLOCK_LEN], BLOCK_LEN);
  }

  *encryptedlen = padded_len;
  memcpy(encryptedbuffer, padded_buffer, padded_len);
  free(padded_buffer);

  return 0;
}

int aes128cbc_decrypt(const unsigned char* encryptedbuffer, const int encryptedlen,
                      unsigned char* clearbuffer, int * clearlen, const int maxclearlen,
					  const unsigned char* key, const int keylen,
					  const unsigned char* iv, const int ivlen)
{
	unsigned int num_blocks, i;
	unsigned char next_iv[BLOCK_LEN];

	num_blocks = encryptedlen / BLOCK_LEN;

	memcpy(next_iv, iv, ivlen);

	for ( i=0; i<num_blocks; i++ ) {
		int curr_block_len;

		aes128ecb_decrypt(&encryptedbuffer[i*BLOCK_LEN], encryptedlen,
						  &clearbuffer[i*BLOCK_LEN], &curr_block_len, BLOCK_LEN,
						  key, keylen);

		inplace_xor(&clearbuffer[i*BLOCK_LEN], next_iv, BLOCK_LEN);

		if ( i<num_blocks )
			memcpy(next_iv, &encryptedbuffer[i*BLOCK_LEN], BLOCK_LEN);

		*clearlen+=BLOCK_LEN;
	}

	return 0;
}
