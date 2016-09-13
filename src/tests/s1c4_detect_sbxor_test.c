#include "../include/cryptopals.h"
#include "../include/libutil.h"
#include "../include/sbxor_decode.h"

#define TEST_FILE 	"./tests/4.txt"

char* s1c4_getdesc()
{
	return "here comes set 1 challenge 4 description";
}

int load_test_file(const char* filename, char* buf, long* len)
{
	FILE* fp;
	long lsize;
	int rd;

	*len = 0;

	fp = fopen(filename, "rb");
	if ( NULL != fp )
	{
		fseek(fp, 0, SEEK_END);
		lsize = ftell(fp);
		fseek(fp, 0, SEEK_SET);

		if (NULL == buf)
		{
			if(len)
				*len = lsize;

			fclose(fp);
			return 0;
		}

		rd = fread(buf, 1, lsize, fp);

		*len = rd;

		fclose(fp);

		return 1;
	}

	return 0;	
}

int getline_from_b(const char* in, const int ilen, char** ptr_nextline, int* linelen)
{
	int i=0;
	
	while ( (in+i != NULL) && (i<ilen) )
	{
		if ( '\n' == *(in+i) )
		{
			*linelen = i;
			
			if ( (in+i+1) != NULL )
			{
				*ptr_nextline = (char*)(in+i+1);	
			}
			
			return 1;
		}
		i++;
	}
	
	return 0;
}

int s1c4_main()
{
	long len, line_len, line_number = 1;
	unsigned char* test_data = NULL;
	unsigned char* lineptr;

	load_test_file(TEST_FILE, NULL, &len);
	if ( len <= 0 )
		return 0;

	test_data = (unsigned char*) malloc(len);
	if ( NULL != test_data )
	{
		if (load_test_file(TEST_FILE, (char*)test_data, &len))
		{
			float best_score = 0;
			int   best_line = 1;
			
			while( getline_from_b((char*)test_data, len, (char**)&lineptr, (int*) &line_len) )
			{
				int decoded_line_len, bin_line_len;
				unsigned char xor_byte, *decoded_line, *bin_line;
				float score;

			    bin_line_len = line_len/2;

				bin_line = (unsigned char*) malloc(bin_line_len);
				if ( NULL == bin_line )
				{
					printf("FALTAL! out of memory");
					free(test_data);
					return 0;					
				}

				asciib2hexb((char*) test_data, 
					        (unsigned int)line_len, 
					        (char*) bin_line, 
					        &bin_line_len);

				decoded_line = malloc(bin_line_len + 1);
				if ( NULL != decoded_line )
				{
					memset((char*) decoded_line, 0, bin_line_len + 1);
					printf("Checking line %d - ", (int)line_number);
					print_chars(test_data, line_len);
					printf("...");

					brute_force_sbxor(	EN, 
									  	bin_line, 
									  	bin_line_len, 
						              	decoded_line, 
						              	(unsigned int*)&decoded_line_len, 
						              	&xor_byte, 
						              	&score  );

					if ( score >= best_score )
					{
						best_score = score;
						best_line = line_number;
						printf("score=%f xor byte guess:%c\n", score, xor_byte);
						printf("\toutput:");
						print_chars(decoded_line, decoded_line_len);
						printf("\n");
						printf("____________________________________________________________________________________________________\n");
						printf("\n\n");						
					}
					else
					{
						printf("skipped\n");	
					}

					free(bin_line);
					free(decoded_line);

				}
				else
				{
					printf("FALTAL! out of memory");
					free(bin_line);
					free(test_data);
					return 0;
				}
				
				line_number++;
				test_data = lineptr;
				len -= line_len;
			}
			
			printf("Best score (%f) achieved at line %d\n", best_score, best_line);
			
		}
		else
		{
			printf("Failed to reopen test file\n");
			return 0;
		}
	}

	printf("Failed to open test file\n");
	return 0;
}
