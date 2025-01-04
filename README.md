# proj64-linux-anony-page-compression

## Task

[题目链接](https://github.com/oscomp/proj64-linux-anony-page-compression)

Linux 内核中的内存缓存机制`zram`是将匿名页压缩后进行保存，以节省内存的开销。`zram`使用的压缩算法的性能及压缩率对内存回收的效率有很大的影响，且解压缩性能会影响pagefault的响应时间，因此，`zram`使用的压缩算法的压缩率和性能非常关键。当前内核支持的压缩算法(`lz4`、`lzo`等)并非针对匿名页定制的压缩算法，本项目目标是针对匿名页特征，设计出高压缩率高性能的压缩算法。

## Introduction

我们利用了 Intel&reg; 机器的特性，使用 Intel&reg; QuickAssist Technology (QAT) 的硬件支持来增强压缩效果。将原 `zram` 的部分压缩算法使用 QATzip 加速。

## 安装方法

### 1.克隆本项目至本地
```bash
git clone https://gitlab.eduxiji.net/T202418123994973
```

### 2.部署QAT

[QATzip安装](https://github.com/intel/QATzip)

参照官方仓库安装。具体需要先 `QATlib` （QATzip运行的必要硬件驱动支持）。接着安装`QATzip`。

### 3.编译该项目

记模块的名字为`NAME`，在`Makefile`中默认为`qzram`，用户也可以自定义。

编译
```bash
make
```

清除所有编译结果
```bash
make clean
```

### 4.基本使用
加入模块，默认创建一个`zram`设备：使用`lz4`算法压缩、8G大小、作为系统内最高优先级的交换空间
```bash
make insmod
```

移除模块
```bash
make rmmod
```

[基本用法](https://docs.kernel.org/admin-guide/blockdev/zram.html)和原来的`zram`保持一致，因为我们只对压缩的部分进行了处理。












