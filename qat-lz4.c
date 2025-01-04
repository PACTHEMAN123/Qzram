#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/kmod.h>
#include <linux/slab.h>
#include <linux/sched.h>
#include <linux/fs.h>
#include <linux/string.h>
#include <linux/dcache.h>
#include <linux/namei.h>
#include <linux/err.h>
#include <linux/mount.h>
#include <linux/dirent.h>
#include <linux/limits.h>
#include <linux/fs_struct.h>


#define APPNAME "/usr/local/bin/qzip"  // 用户态程序的路径

long long countIndex = 0;
char* fileNameTemplate = "/dev/shm/tempPage%lu";
char* fileNameTemplatelz4 = "/dev/shm/tempPage%lu.lz4";

//#define TEST


// 注意output这个buffer需要提前准备好，大小可以设置为页面的大小
int lz4compression(char* input, int input_len, char* output, int* output_len) {
    int ret;
    long long currentIndex = countIndex++;
    char* fileName = (char*)kmalloc(100, GFP_KERNEL);
    if (!fileName) {
        printk(KERN_ERR "Failed to allocate memory for fileName\n");
        return -ENOMEM;
    }
    char* fileNamelz4 = (char*)kmalloc(100, GFP_KERNEL);
    if (!fileNamelz4) {
        printk(KERN_ERR "Failed to allocate memory for fileName7z\n");
        kfree(fileName);
        return -ENOMEM;
    }
    sprintf(fileName, fileNameTemplate, currentIndex);
    sprintf(fileNamelz4, fileNameTemplatelz4, currentIndex);
    char *argv[] = {APPNAME, "-O", "lz4", fileName, "-o", fileName, NULL};  // 用户态程序参数

#ifdef TEST
    printk(KERN_INFO "Input: %s\n", input);
    printk(KERN_INFO "Input length: %d\n", input_len);

    printk(KERN_INFO "[QAT_TEST] Compression start\n");
#endif

    struct file* fpIn = filp_open(fileName, O_WRONLY | O_CREAT, 0777);
    if (IS_ERR(fpIn)) {
        printk(KERN_ERR "Failed to open file %s for writing\n", fileName);
        kfree(fileName);
        kfree(fileNamelz4);
        return PTR_ERR(fpIn);
    }
    loff_t pos1 = 0;
    ret = kernel_write(fpIn, input, input_len, &pos1);
    if (ret < 0) {
        printk(KERN_ERR "Failed to write to file %s, ret: %d\n", fileName, ret);
        filp_close(fpIn, NULL);
        kfree(fileName);
        kfree(fileNamelz4);
        return ret;
    }
    filp_close(fpIn, NULL);

#ifdef TEST
    printk(KERN_INFO "[QAT_TEST] Compression write done\n");
    printk(KERN_INFO "file name: %s\n", fileName);
#endif

    int i;
    for (i = 0; i < sizeof(argv) / sizeof(argv[0]); i++) {
        printk(KERN_INFO "argv[%d]: %s\n", i, argv[i]);
    }

    // 调用用户态程序
    ret = call_usermodehelper(APPNAME, argv, NULL, UMH_WAIT_PROC);

#ifdef TEST
    printk(KERN_INFO "[QAT_TEST] Compression call done\n");

    printk(KERN_INFO "filelz4 name: %s\n", fileNamelz4);
#endif

    struct file* fpOut = filp_open(fileNamelz4, O_RDONLY, 0);
    if (IS_ERR(fpOut)) {
        printk(KERN_ERR "Failed to open file %s for reading\n", fileNamelz4);
        kfree(fileName);
        kfree(fileNamelz4);
        return PTR_ERR(fpOut);
    }

    loff_t pos2 = 0;
    int r = kernel_read(fpOut, output, 8192, &pos2);
    if (r < 0) {
        printk(KERN_ERR "Failed to read from file %s\n", fileNamelz4);
        filp_close(fpOut, NULL);
        kfree(fileName);
        kfree(fileNamelz4);
        return r;
    }
    *output_len = r;

    filp_close(fpOut, NULL);

#ifdef TEST
    printk(KERN_INFO "[QAT_TEST] Compression read done\n");
#endif

    //deleteFile(fileName7z);
    kfree(fileName);
    kfree(fileNamelz4);
    
    if (ret != 0) {
        printk(KERN_ERR "call compression failed\n");
        return -1;  // 返回错误
    }

#ifdef TEST
    printk(KERN_INFO "[QAT_TEST] Compression read finish\n");
#endif

    return 0;  // 成功
}

// 注意output这个buffer需要提前准备好，大小可以设置为页面的大小
int lz4decompression(char* input, int input_len, char* output, int* output_len) {
    int ret;
    long long currentIndex = countIndex++;

#ifdef TEST
    printk(KERN_INFO "decompression: currentIndex=%u\n", currentIndex);
#endif

    char* fileName = (char*)kmalloc(100, GFP_KERNEL);
    if (!fileName) {
        printk(KERN_ERR "Failed to allocate memory for fileName\n");
        return -ENOMEM;
    }
    char* fileNamelz4 = (char*)kmalloc(100, GFP_KERNEL);
    if (!fileNamelz4) {
        printk(KERN_ERR "Failed to allocate memory for fileName7z\n");
        kfree(fileName);
        return -ENOMEM;
    }
    sprintf(fileName, fileNameTemplate, currentIndex);
    sprintf(fileNamelz4, fileNameTemplatelz4, currentIndex);

#ifdef TEST
    printk(KERN_INFO "[QAT_TEST] fileName: %s\n", fileName);
    printk(KERN_INFO "[QAT_TEST] fileName7z: %s\n", fileNamelz4);
    printk(KERN_INFO "[QAT_TEST] Decompression start\n");
#endif

    struct file* fpIn = filp_open(fileNamelz4, O_WRONLY | O_CREAT, 0777);
    if (IS_ERR(fpIn)) {
        printk(KERN_ERR "Failed to open file %s for writing\n", fileNamelz4);
        kfree(fileName);
        kfree(fileNamelz4);
        return PTR_ERR(fpIn);
    }

    loff_t pos1 = 0;
    ret = kernel_write(fpIn, input, input_len, &pos1);

#ifdef TEST
    printk(KERN_INFO "Input length: %d\n", input_len);
#endif

    if (ret < 0) {
        printk(KERN_ERR "Failed to write to file %s\n", fileNamelz4);
        filp_close(fpIn, NULL);
        kfree(fileName);
        kfree(fileNamelz4);
        return ret;
    }
    filp_close(fpIn, NULL);

#ifdef TEST
    printk(KERN_INFO "after write, offset: %d\n", pos1);
    printk(KERN_INFO "[QAT_TEST] Decompression write done\n");
#endif

    char *argv[] = {APPNAME, "-d", fileNamelz4,  "-o", fileName, NULL};  // 用户态程序参数
    int i;
    for (i = 0; i < sizeof(argv) / sizeof(argv[0]); i++) {
        printk(KERN_INFO "argv[%d]: %s\n", i, argv[i]);
    }

    // 调用用户态程序
    ret = call_usermodehelper(APPNAME, argv, NULL, UMH_WAIT_PROC);

    printk(KERN_INFO "[QAT_TEST] Decompression call done, ret = %d\n", ret);

    
    struct file* fpOut = filp_open(fileName, O_RDONLY, 0);
    if (IS_ERR(fpOut)) {
        printk(KERN_ERR "Failed to open file %s for reading, error code: %ld\n", fileName, PTR_ERR(fpOut));
        kfree(fileName);
        kfree(fileNamelz4);
        return PTR_ERR(fpOut);
    }

    loff_t pos2 = 0;
    int r = kernel_read(fpOut, output, 8192, &pos2);
    if (r < 0) {
        printk(KERN_ERR "Failed to read from file %s\n", fileName);
        filp_close(fpOut, NULL);
        kfree(fileName);
        kfree(fileNamelz4);
        return r;
    }
    *output_len = r;
    filp_close(fpOut, NULL);

#ifdef TEST
    printk(KERN_INFO "[QAT_TEST] Decompression read done: %d\n", *output_len);
#endif

    //deleteFile(fileName);
    kfree(fileName);
    kfree(fileNamelz4);
    
    if (ret != 0) {
        printk(KERN_ERR "call decompression failed\n");
        return -1;  // 返回错误
    }

#ifdef TEST
    printk(KERN_INFO "[QAT_TEST] Decompression finish\n");
#endif

    return 0;  // 成功
}




