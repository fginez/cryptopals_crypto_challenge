#include "../include/cryptopals.h"
#include "../include/libutil.h"
#include "../include/aes128ecb.h"
#include "../include/hextob64.h"

char* s1c7_getdesc()
{
	return "Challenge 7 AES in ECB mode";
}

int s1c7_main()
{
	const unsigned char key[] = "YELLOW SUBMARINE";
	int iEncodedLen, iDecodedLen;
	unsigned char* pEncodedFile, *pDecodedFile;
	printf("Testing AES128 Decryption in ECB mode\n");

	iEncodedLen = LoadFile("../src/tests/inputs/7.txt", (char**) &pEncodedFile);	
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
					
					if ( 0 == aes128ecb_decrypt(pDecodedFile, iDecodedLen, 
						                        pClearBuffer, &iClearLen, iDecodedLen,
												key, sizeof(key) -1) )
					{
						printf("Decrypted file [len=%d]:\n", iClearLen);
						print_chars(pClearBuffer, iClearLen);	
					}
					
					free(pClearBuffer);
				}
				else
				{
					printf("Out of memory @ pClearBuffer\n");	
				}
			}
			else
			{
				printf("Invalid decoded size\n");	
			}
			
			free(pDecodedFile);	
		}
		else
		{
			printf("Out of memory @ pDecodedFile\n");	
		}
		
		free(pEncodedFile);
	}
	else
	{
		printf("Failed to open file\n");	
	}
	
	
	return 0;	
}