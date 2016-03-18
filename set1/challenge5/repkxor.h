#ifndef __REPKXOR_H_
#define __REPKXOR_H_

int repkxor(const unsigned char* key, const unsigned int klen,
            const unsigned char* in,  const unsigned int ilen,
            unsigned char* out, unsigned int *olen);

#endif
