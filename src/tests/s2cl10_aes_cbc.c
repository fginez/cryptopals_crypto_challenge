#include "../include/cryptopals.h"
#include "../include/libutil.h"
#include "../include/hextob64.h"
#include "../include/aes128cbc.h"

char * s2c10_getdesc()
{
	return "Challenge 10 Implement AES CBC mode";
}

int  s2c10_main(int argc, char** argv)
{
	const unsigned char key[] = "YELLOW SUBMARINE";
	const unsigned char iv[16] = {0};

	int iEncodedLen, iDecodedLen;
	unsigned char* pEncodedFile, *pDecodedFile;
	printf("Testing AES128 Decryption in CBC mode\n");
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
												key, sizeof(key),
												iv, sizeof(iv)) )
					{
						printf("Decrypted file [len=%d]:\n", iClearLen);
						print_chars(pClearBuffer, iClearLen);
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
