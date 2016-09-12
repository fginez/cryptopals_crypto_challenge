#include "../include/cryptopals.h"
#include "../include/libutil.h"
#include "../include/hextob64.h"
#include "../include/break_repkxor.h"

int s1c6_test()
{
	char* pFile;
	int iFileLen;
	int i;
	
	iFileLen = LoadFile("6.txt", &pFile);
	if ( 0 < iFileLen ) 
	{
		int iDecodedLen = b64tohex_sizehelper(iFileLen);
		int iOutLen;
		char* pDecodedFile = (char*) malloc(iDecodedLen);

		printf("Encoded file begin: ");
		print_hex((unsigned char*) pFile, 10); printf("\n");
		printf("Encoded file end: ");
		print_hex((unsigned char*) &pFile[iFileLen-11], 10); printf("\n");
		
		iOutLen = b64tohex((const unsigned char*) pFile, iFileLen, (unsigned char*) pDecodedFile);

		printf("Decoded file begin: ");
		print_hex((unsigned char*) pDecodedFile, 10); printf("\n");
		printf("Decoded file end: ");
		print_hex((unsigned char*) &pDecodedFile[iOutLen-10], 10); printf("\n");
		
		break_it((unsigned char*) pDecodedFile, iOutLen);
		
		printf("Resulting file:\n");
		
		for (i=0; i<iOutLen;i++)
		{
			printf("%c", pDecodedFile[i]);
		}
		printf("\n");
	}
	
	return 0;
}

