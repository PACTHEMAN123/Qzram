int qatCompress(struct crypto_comp *comp,
                 const void *src, const void *dst, 
                 unsigned int *dst_len);

int qatDecompress(struct crypto_comp *comp,
                 const void *src, unsigned int src_len,
                 void *dst, unsigned int *dst_len);
