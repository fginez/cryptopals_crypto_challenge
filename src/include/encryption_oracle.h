#ifndef __ENCRYPTION_ORACLE_H__
#define __ENCRYPTION_ORACLE_H__


int encryption_oracle_ex(const unsigned char* input, const unsigned int input_len,
						 unsigned char* output, unsigned int *output_len, const unsigned int max_output_len, int* method_used);

int encryption_oracle(const unsigned char* input, const unsigned int input_len,
					  unsigned char* output, unsigned int *output_len, const unsigned int max_output_len);

int detect_mode();

#endif
