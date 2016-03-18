#include "hextob64.h"

int hextob64(const unsigned char *in, const int in_len, unsigned char* out)
{
    int idx_in = 0, idx_out = 0;
    const unsigned char b64symbols[64] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    
    do
    {
        out[idx_out++] = b64symbols[(in[idx_in] & 0xFC) >> 2];
        if ((idx_in+1) < in_len)
        {
            out[idx_out++] = b64symbols[((in[idx_in]&0x03)<<4)|((in[idx_in+1]&0xF0)>>4)];
            if ((idx_in+2) < in_len)
            {
                out[idx_out++] = b64symbols[((in[idx_in+1]&0x0F)<<2) | ((in[idx_in+2]&0xC0)>>6)];
                out[idx_out++] = b64symbols[in[idx_in+2]&0x3F];
            }
            else
            {
                // only 2 bytes to process
                out[idx_out++] = b64symbols[(in[idx_in+1]&0x0F)<<2];
                out[idx_out++] = (unsigned char)'=';
            }
        }
        else 
        {
            // only 1 byte to process
            out[idx_out++] = b64symbols[(in[idx_in]&0x03)<<4];
            out[idx_out++] = (unsigned char)'=';
            out[idx_out++] = (unsigned char)'=';
        }
        
        idx_in += 3;
        
    } while(idx_in < in_len);
       
    return idx_out;
}

int b64tohex(const unsigned char *in, const int in_len, unsigned char* out)
{
    do
    {   
        out[idx_out] = find_index(in[idx_in])<<2 | (find_index(in[idx_in+1]) & 0x30)>>4;
        if (idx_in+4 < in_len)
        {
            out[idx_out+1] = (find_index(in[idx_in+1]) & 0x0F)<<4 | (find_index(in[idx_in+2]) & 0x3C)>>2;
        }

        idx_in += 4;

    } while (idx_in < in_len);

    return idx_out;
}

int find_index(char x)
{
    int i;
    const unsigned char b64symbols[64] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    for (i=0; i<sizeof(b64symbols); i++)
    {
        if ( x == b64symbols[i])
            return i;
    }

    return 0;
}

int hextob64_sizehelper(const int in_len)
{
    return ((in_len + (in_len%3))/3)*4;
}

int b64tohex_sizehelper(const int in_len)
{
    return ((in_len + (in_len%4))/4)*3;
}
