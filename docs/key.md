# 关键代码思路

我们的思路从 zram 调用函数进行压缩开始，解压缩同理。

## 原代码出口

我们留意到，在 linux v5.0 中，zram 部分的主要代码位于`linux/driver/blocks/zram/`下，可以直接单独编译为模块。zram 所用到的 lz4、lzo、zstd 等压缩算法，都已经与该模块解耦合，并不包含在 zram 模块的代码中。很容易找到压缩的核心函数：

```c
int zcomp_compress(struct zcomp_strm *zstrm,
		const void *src, unsigned int *dst_len)
{
	...
	*dst_len = PAGE_SIZE * 2;

	return crypto_comp_compress(zstrm->tfm,
			src, PAGE_SIZE,
			zstrm->buffer, dst_len);
}
```

函数的参数里，`zstrm`用于传递基本的压缩信息：压缩的上下文、使用的压缩算法等，以便于后续处理。我们可以直接将`crypto_comp_compress`，改为我们使用的压缩算法的入口。这样就可以实现 zram 压缩算法的改变，而无需变动其他部分。

## QAT接口

`qatzip.h`的接口相对于 QATlib 的接口，更简洁直接。所以在最开始时，我们尝试使用`qatzip.h`以及链接 QATzip 编译出的静态库，来实现 zram 对 QATzip 的使用。

但在内核模块的编写中，必须使用内核的函数、头文件。QATzip 是面向用户态编写的，注定了我们无法轻松移植到内核中。我们又尝试了 QATlib：QATlib 提供了硬件驱动支持，可以在内核态使用，然而又因为相关文档太少，尝试失败。

迫于时间原因，我们选择了一个不被提倡的做法：在内核模块中调用用户程序。

```c
// in qat-lz4.c: lz4compression

// 用户态程序的路径
#define APPNAME "/usr/local/bin/qzip"  

...
// 用户态程序参数
char *argv[] = {APPNAME, "-O", "lz4", fileName, "-o", fileName, NULL};  

...
// 调用用户态程序
ret = call_usermodehelper(APPNAME, argv, NULL, UMH_WAIT_PROC);
```

注意用户程序只能接收文件名作为参数，我们还需要将传入的内存转变为文件的形式：具体过程为：`input -> file0 -> file0.lz4 -> output`。利用`/dev/shm/`下可以快速创建删除临时文件的特性。

```c
// in qat-lz4.c: lz4compression

struct file* fpIn = filp_open(fileName, O_WRONLY | O_CREAT, 0777);
ret = kernel_write(fpIn, input, input_len, &pos1);

// call user mode
...

struct file* fpOut = filp_open(fileNamelz4, O_RDONLY, 0);
int r = kernel_read(fpOut, output, 8192, &pos2);

```

解压缩同理。在初步完成代码，尝试运行中，遇到了 crash 的情况，通过查看内核日志，判断是文件读写导致的。开始时，我们维护一个全局计数`currentIndex`，每创建一次文件`currentIndex++` ，用其作为文件的名字的结尾，这样使得不重复使用同名文件，避免冲突。但在多进程压缩的场景下，该冲突无法避免。如果加锁的话，IO性能将下降更加严重。

我们需要确保每个进程使用的文件名独一无二即可。我们选择用PID（进程号，进程独一无二的标识数），来创建文件。类似下面这种方法。

```c
pid_t pid = current->pid;
sprintf(fileName, fileNameTemplate, pid);
sprintf(fileNamelz4, fileNameTemplatelz4, pid);
```

## QAT入口封装

为了使得代码可拓展性更强，我们用`qat.h` `qat.c`封装了`qat-lz4`的代码。我们以后可以支持使用 QAT 的其他功能，比如：`qat-zstd`。只需要在`qat.c`中解析`zstrm`就可以实现任务的分发。符合模块化编程的思想。





