#include "qat-lz4.h"
#include "linux/types.h"
#include "linux/crypto.h"

/* alternative to crypto_comp_compress */

int qatCompress(struct crypto_comp *comp,
                const u8 *src, unsigned int src_len,
                u8 *dst, unsigned int *dst_len)
{
    int ret;
    ret = lz4compression((char *)src, src_len, (char *)dst, dst_len);
    return ret;
}

int qatDecompress(struct crypto_comp *comp,
                    const u8 *src, unsigned int src_len,
                    u8 *dst, unsigned int *dst_len)
{
    int ret;
    ret = lz4decompression((char *)src, src_len, (char *)dst, dst_len);
    return ret;
}