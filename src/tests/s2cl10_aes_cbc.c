#include "../include/cryptopals.h"
#include "../include/libutil.h"
#include "../include/hextob64.h"
#include "../include/aes128cbc.h"
#include "../include/pkcs7padding.h"

#define TESTS	2

const unsigned char lengths[2][4] = {
	{16, 16, 16, 16},
	{32, 16, 16, 32},
};

const unsigned char inputs[2][32] = {
	{0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F},
	{0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
	 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F}
};

const unsigned char keys[2][16] = {
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
};

const unsigned char vectors[2][16] = {
	{0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01},
	{0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01},
};

const unsigned char outputs[2][32] = {
	{0x75, 0x80, 0x08, 0xE9, 0x2A, 0xD3, 0x34, 0x2A, 0x20, 0x7E, 0x4B, 0x28, 0x4E, 0xC4, 0x99, 0xCA},
	{0x75, 0x80, 0x08, 0xE9, 0x2A, 0xD3, 0x34, 0x2A, 0x20, 0x7E, 0x4B, 0x28, 0x4E, 0xC4, 0x99, 0xCA,
	 0x3B, 0x52, 0xC7, 0x82, 0xA0, 0xE0, 0xFC, 0x1E, 0xBC, 0x56, 0x13, 0xE1, 0xAE, 0x80, 0x0F, 0xCA}
};

char * s2c10_getdesc()
{
	return "Challenge 10 Implement AES CBC mode";
}

int s2c10_pretest() {
	int i =0, iClearLen, iEncryptedLen;
	unsigned char testbuffer[32], testbuffer2[32];

	printf("AES CBC pre-test\n");

	for(i=0; i<TESTS; i++) {
		printf( "Using set %d\n", i);
		if ( 0 == aes128cbc_encrypt(inputs[i], lengths[i][0],
									testbuffer, (unsigned int*) &iEncryptedLen, sizeof(testbuffer),
									keys[i], lengths[i][1],
									vectors[i], lengths[i][2]) ){

			if ( 0 != CRYPTO_memcmp(testbuffer, (void*)outputs[i], lengths[i][3]) ) {
				printf("Buffer comparison failed\n");
				return -1;
			}

		} else {
			printf("aes128cbc_encrypt failed\n");
			return -1;
		}

		if ( 0 == aes128cbc_decrypt(testbuffer, iEncryptedLen,
									testbuffer2, &iClearLen, sizeof(testbuffer2),
									keys[i], lengths[i][1],
									vectors[i], lengths[i][2]) ){

			if ( 0 != CRYPTO_memcmp(testbuffer2, (void*)inputs[i], lengths[i][0]) ) {
				printf("Buffer comparison failed\n");
				return -1;
			}

		} else {
			printf("aes128cbc_decrypt failed\n");
			return -1;
		}

	}

	printf("OK!\n");
	return 1;
}

int  s2c10_main(int argc, char** argv)
{
	const unsigned char key[] = "YELLOW SUBMARINE\0";
	const unsigned char iv[16] = {0};

	int iEncodedLen, iDecodedLen;
	unsigned char* pEncodedFile, *pDecodedFile;
	printf("Testing AES128 Decryption in CBC mode\n");

	if ( -1 == s2c10_pretest() ) {
		printf( "Pre-test failed\n");
		return -1;
	}


	iEncodedLen = LoadFile("../src/tests/inputs/10.txt", (char**) &pEncodedFile);
	if ( 0 < iEncodedLen )
	{
		iDecodedLen = b64tohex_sizehelper(iEncodedLen);
		pDecodedFile = (unsigned char*) malloc(iDecodedLen);
		if ( NULL != pDecodedFile )
		{
			iDecodedLen = b64tohex(pEncodedFile, iEncodedLen, pDecodedFile);
			if ( 0 < iDecodedLen )
			{
				unsigned char* pClearBuffer = (unsigned char*) malloc(iDecodedLen);
				printf("Binary file length=%d\n", iDecodedLen);
				if ( NULL != pClearBuffer )
				{
					int iClearLen = 0;

					if ( 0 == aes128cbc_decrypt(pDecodedFile, iDecodedLen,
						                        pClearBuffer, &iClearLen, iDecodedLen,
												key, strlen((char*)key),
												iv, sizeof(iv)) )
					{
						int unppaded_size = pkcs7unpadding_size(pClearBuffer, iClearLen, BLOCK_LEN );
						if ( -1 != unppaded_size ){
							iClearLen = unppaded_size;
						}
						printf("Decrypted file [len=%d]:\n", iClearLen);
						print_chars(pClearBuffer, iClearLen);
					} else {
						printf("Error: aes128cbc_decrypt failed\n");
					}

					free(pClearBuffer);
					free(pDecodedFile);
					free(pEncodedFile);
					return 0;
				}
				else
				{
					printf("Out of memory @ pClearBuffer\n");
					free(pDecodedFile);
					free(pEncodedFile);
					return -1;
				}
			}
			else
			{
				printf("Invalid decoded size\n");
				free(pDecodedFile);
				free(pEncodedFile);
				return -1;
			}
		}
		else
		{
			printf("Out of memory @ pDecodedFile\n");
			free(pEncodedFile);
			return -1;
		}
	}
	else
	{
		printf("Failed to open file\n");
		return -1;
	}
}
