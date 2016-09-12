#include <string.h>

int detect_aes128ecb(const char* in, const int len)
{
	int iBlockLen = 128 / 8;	// 16bytes
	int i;
	char *pBlockA, *pBlockB;
	
	for (i=0; i<len; i+=iBlockLen)
	{
		int j;
		pBlockA = (char*) in + i;
		
		for ( j=(i+iBlockLen); j<len; j+=iBlockLen )
		{
			pBlockB = (char*) in + j;
			
			if ( 0 == memcmp(pBlockA, pBlockB, iBlockLen) )
			{
				// Block is equal
				return 1;	
			}			
		}
	} 
	return 0;
}
