#include "lzav.h"

int lzav_compress(const void *src, unsigned int src_len,
                    const void *dst, unsigned int *dst_len)
{
    int max_len = lzav_compress_bound(src_len);
    
}