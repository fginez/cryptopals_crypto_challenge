#include <stdio.h>
#include <stdlib.h>
#include "fileops.h"

int GetFileLen(const char* szFilename);

int LoadFile(const char* szFilename, char** ppBuffer)
{
	int iBytesRead = 0;
	int iFileLen = GetFileLen(szFilename);

	if ( 0 < iFileLen )
	{
		*ppBuffer = (char*) malloc(iFileLen);
		if ( NULL != *ppBuffer )
		{
			FILE* fp = fopen (szFilename, "rb");
			if ( NULL != fp )
			{			
				iBytesRead = fread(*ppBuffer, 1, iFileLen, fp);			
				fflush(fp);
				fclose(fp);
			}
		}
	}
	
	return iBytesRead;
}

int GetFileLen(const char* szFilename)
{
	FILE* fp;
	int iFileLen = 0;
	fp = fopen(szFilename, "rb");
	if ( NULL != fp )
	{
		fseek(fp, 0, SEEK_END);
		iFileLen = ftell(fp);
		fclose(fp);
	}
	
	return iFileLen;	
}
