#include <linux/kernel.h>
#include <linux/string.h>
#include <linux/err.h>
#include <linux/slab.h>
#include <linux/wait.h>
#include <linux/sched.h>
#include <linux/cpu.h>
#include <linux/crypto.h>

#include "zcomp.h"

#include "/usr/local/include/qatzip.h"

/*
 * use the qat the compress.
 */
int qatCompress(struct crypto_comp *comp,
                 const void *src, void *dst, 
                 unsigned int *dst_len)
{
    QzSession_T sess = {0};
    QzSessionParams_T params;

    int rc;

    rc = qzGetDefaults(&params);
    params.comp_lvl = 6;

    rc = qzInit(&sess, 1);

    rc = qzSetupSession(&sess, &params);

    int src_len = PAGE_SIZE * 2;
    rc = qzCompress(&sess, src, &src_len, dst, dst_len, 1);


    return rc;
}

int qatDecompress(struct crypto_comp *comp,
                 const void *src, unsigned int src_len,
                 void *dst, unsigned int *dst_len)
{
    QzSession_T sess = {0};
    QzSessionParams_T params;

    int rc;

    rc = qzGetDefaults(&params);
    params.comp_lvl = 6;

    rc = qzInit(&sess, 1);

    rc = qzSetupSession(&sess, &params);

    int src_length = src_len;
    rc = qzDecompress(&sess, src, &src_length, dst, dst_len);

    return rc;
}




