#include "../include/cryptopals.h"
#include "../include/libutil.h"
#include "../include/detect_aes128ecb.h"

char* s1c8_getdesc()
{
	return "here comes set 1 challenge 8 description";
}

int s1c8_main()
{
	int iFileLen, iBufferLen;
	char *pFile, *pHexBuffer;
	const char token[] = {0x0A, 0x00};
	
	printf("Detecting AES128-ECB\n");
	
	iFileLen = LoadFile("8.txt", &pFile);
	if ( 0 < iFileLen )
	{
		char* pToken = 0;
	
		printf("File loaded [len=%d]\n", iFileLen);
			
		pToken = strtok(pFile, token);
		while (NULL != pToken)
		{	
			int iChunkLen = 0;
						
			iChunkLen = strlen(pToken);
			pHexBuffer = (char*) malloc((iChunkLen/2) + 1);
			if ( NULL != pHexBuffer )
			{					
				memset(pHexBuffer, 0, (iChunkLen/2) + 1);
				asciib2hexb(pToken, iChunkLen, pHexBuffer, &iBufferLen);
				printf("Decoded chunk to hex bytes [new len=%d]\n", iBufferLen);
				if ( 0 != detect_aes128ecb(pHexBuffer, iBufferLen) )
				{
					printf("AES128ECB DETECTED @Chunk: ");
					print_hex((const unsigned char*)pHexBuffer, iBufferLen);
					printf("\n");
				}
				
				free(pHexBuffer);
			}
			
			pToken = strtok(NULL, token);
		}
	}
		
	return 0;	
}