# 测试部分

## 实验环境
- linux发行版：Ubuntu-22.04.5 
- linux内核：5.15.0-126-generic
- 基本配置：96核、128G内存
- QATlib：linux Hardware Version 2.0
- QATzip：24.09

## 测试数据
- SPEC CPU 2017 suite: SPECrate&reg;2017 Interger
- SPEC CPU 2017 benchmark: `502.gcc_r` `505.mcf_r` `525.x264_r` `531.deepsjeng_r` `557.xz_r`

用来模拟多种场景下系统的 workload：大量编译、路径规划、视频压缩、AI计算、通用数据压缩

## 测试方法

### 1.部署SPEC CPU 2017

[官方指南](https://www.spec.org/cpu2017/Docs/install-guide-unix.html)

最终会安装好测试集：cpu2017文件夹

测试所用配置：见`try.cfg`文件

### 2.使用`cgroup v2`限制内存运行

为了验证`zram`的性能，我们需要加大其 workload ：通过限制运行内存，系统将更多使用交换空间，即需要测试的`zram`。
```bash
# spec2017需要在用户态使用，而cgroup添加进程时需要更高权限，这点会在 cgexec 冲突，通过下面命令解决：
sudo chmod o+w /sys/fs/cgroup/cgroup.procs 

# 创建一个名为 test 的 cgroup
sudo cgcreate -a $USER:$USER -g memory:test -t $USER:$USER

# 设置分组的内存限制，注意不能太小，否则过多的交换空间IO会导致性能过低
sudo cgset -r memory.max=4g test

# 在cpu2017下启动单个 benchmark (502.gcc_r)
cgexec -g memory:test2 runcpu --config=try  502.gcc_r
```

### 3.收集/处理数据

运行程序过程中，在`data`目录下，手动随机使用脚本`data_record.sh` 收集`qzram`的参数。

```bash
# under data/
chmod +x data_record.sh

# (*) when need to record qzram
./data_record.sh

# after recording qzram
echo "" >> f1.txt
echo "" >> f2.txt
```

测试完`qzram`后，切换到`origin`的分支，此分支为原来的`zram`，类似之前的步骤编译安装即可。

```bash
git checkout origin
make rmmod
make clean
make
make insmod
```
接着重复上面的步骤，继续测试。

最后通过`compress_rate.py` `compress_speed.py`来分析数据，得出测试结果。

## 测试结果

我们利用`zramctl`和`/sys/block/<dev>/stat`的实时输出，计算压缩率和测试压缩/解压速度。

利用`zramctl`的参数：`DATA`(当前写入zram的数据大小)，`COMPR`(压缩后数据实际大小) 来计算压缩率：
$$ RATIO_{compress} = 1 - \frac{COMPR}{DATA} $$

利用`/sys/block/<dev>/stat`的参数：`read I/Os`(总读IO数)，`read ticks`(总的读IO耗费时间)，`write I/Os`(总写IO数)，`write ticks`（总的写IO耗费时间）来计算IO速度：
$$ \bar{T}_{read} = \frac{N_{IO_{read}}}{N_{tick_{read}}} $$

$$ \bar{T}_{write} = \frac{N_{IO_{write}}}{N_{tick_{write}}} $$

| 测试项 | 测试结果 |
| ---- | ----- |
| qzram的平均压缩率 | 0.90442 |
| zram的平均压缩率 | 0.34446 |
| qzram的平均读用时| 0.84686 ms|
|qzram的平均写用时| 1.12253 ms|
|zram的平均读用时| 0.00246 ms|
|zram的平均写用时| 0.00654 ms|

可以发现，目前的设计会使得压缩率提高，但严重牺牲了压缩/解压速度。后续还可以有很多优化空间，但目前限于时间未能开展。