int qatCompress(struct crypto_comp *comp,
                const u8 *src, unsigned int src_len,
                u8 *dst, unsigned int *dst_len);

int qatDecompress(struct crypto_comp *comp,
                    const u8 *src, unsigned int src_len,
                    u8 *dst, unsigned int *dst_len);