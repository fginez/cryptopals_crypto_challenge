#include "../include/cryptopals.h"
#include "../include/libutil.h"
#include "../include/encryption_oracle.h"
#include "../include/aes_common.h"
#include "../include/aes128cbc.h"
#include "../include/aes128ecb.h"
#include <openssl/rand.h>

int encryption_oracle(const unsigned char* input, const unsigned int input_len,
					  unsigned char* output, unsigned int *output_len, const unsigned int max_output_len) {
	int method;
	return encryption_oracle_ex(input, input_len, output, output_len, max_output_len, &method);
}

int encryption_oracle_ex(const unsigned char* input, const unsigned int input_len,
						 unsigned char* output, unsigned int *output_len, const unsigned int max_output_len, int* method_used)
{
	int i;
	int variable_len[6] = {5,6,7,8,9,10};
	int method = rand() % 2;
	int idx_var_len = rand() % sizeof(variable_len)/sizeof(int);
	int rnd_var_len = variable_len[idx_var_len];
	int local_input_len;
	unsigned char rnd_buffer_a[10], rnd_buffer_b[10];
	unsigned char key[BLOCK_LEN];
	unsigned char* local_input = NULL;

	*method_used = method;

	RAND_bytes(key, BLOCK_LEN);

	// Fill random buffer
	for (i=0; i<rnd_var_len; i++) {
		rnd_buffer_a[i] = rand() % 0xFF;
		rnd_buffer_b[i] = rand() % 0xFF;
	}
	
	local_input_len = input_len + 2*rnd_var_len;
	if ( local_input_len % BLOCK_LEN ) {
		local_input_len += (BLOCK_LEN - (local_input_len % BLOCK_LEN));
	}

	if(max_output_len < local_input_len) {
		printf("encryption_oracle_ex fail - short output buffer\n");
		return -1;
	}

	local_input = (unsigned	char*) malloc(local_input_len);
	if ( NULL == local_input ) {
		printf("Out of memory\n");
		return -1;
	}
	memset(local_input, 0, local_input_len);
	memcpy(&local_input[0], rnd_buffer_a, variable_len[idx_var_len]);
	memcpy(&local_input[0+variable_len[idx_var_len]], input, input_len);
	memcpy(&local_input[0+input_len+variable_len[idx_var_len]], rnd_buffer_b, variable_len[idx_var_len]);	

	if (method) {
		// Use CBC
		unsigned char iv[BLOCK_LEN];
		RAND_bytes(iv, BLOCK_LEN);
		if ( 0 != aes128cbc_encrypt(local_input, local_input_len, 
									output, output_len, max_output_len, 
									key, sizeof(key), 
									iv, sizeof(iv)) ) {
			printf("Encrypt fail\n");
			free(local_input);
			return -1;
		}
	} else {
		// Use ECB
		if ( 0 != aes128ecb_encrypt(local_input, local_input_len,
						  output, (int*) output_len, max_output_len,
						  key, sizeof(key)) ) {
			printf("Encrypt fail\n");
			free(local_input);
			return -1;
		}
	}

	free(local_input);
	return 0;
}

int detect_mode()
{
	// Tamanho minimo: 5 + input + 5 = 10 + input
	// Tamanho maximo: 10 + input + 10 = 20 + input
	unsigned char  input[] = "ParangaricoTirimirruaro";
	unsigned int   input_len = strlen((char*)input);
	unsigned int output_len, max_output_len;
	unsigned char* choosen_input = NULL;
	unsigned char* output = NULL;
	unsigned int choosen_len = 2*BLOCK_LEN + input_len + (input_len%BLOCK_LEN) + 2*BLOCK_LEN;
	int expected_method = 0;

	choosen_input = (unsigned char*) malloc(choosen_len);
	if ( NULL == choosen_input ) {
		printf("Out of memory!\n");
		return -1;
	}

	max_output_len = choosen_len + 30;
	output = (unsigned char*) malloc(max_output_len);
	if ( NULL == output ) {
		free(choosen_input);
		printf("Out of memory!\n");
		return -1;
	}

	memset((char*) choosen_input, 0, choosen_len);
	memcpy((char*) &choosen_input[2*BLOCK_LEN], input, input_len);

	if ( 0 == encryption_oracle_ex( choosen_input, choosen_len,
		                            output, &output_len, max_output_len, &expected_method ) ) {
		// Search for equal blocks -- if found, ECB has been used
		unsigned int i, found, iNumBlocks = output_len / BLOCK_LEN;
		unsigned char* pFirst = &output[ 1 * BLOCK_LEN ];
		found = 0;
		for(i=2; i<iNumBlocks; i++){
			unsigned char* pSecond = &output[ i * BLOCK_LEN ];
			if ( 0 == CRYPTO_memcmp(pFirst, pSecond, BLOCK_LEN) ) {
				found = 1;
				break;
			}
		}

		if(found) {
			printf("ECB detected (expected %s)\n", (expected_method?"CBC":"ECB"));
		} else {
			printf("CBC detected (expected %s)\n", (expected_method?"CBC":"ECB"));
		}
		
	} else {
		printf("Encryption oracle error\n");
		free(choosen_input);
		free(output);
		return -1;
	}

	free(choosen_input);
	free(output);
	return 0;
}
