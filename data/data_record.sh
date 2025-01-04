#!/bin/bash

# 文件路径
file1="f1.txt"
file2="f2.txt"

# 获取 zramctl 第二行的输出并追加到 file1.txt
zramctl | sed -n '2p' >> $file1

# 获取 /sys/block/zram0/stat 的内容并追加到 file2.txt
cat /sys/block/zram0/stat >> $file2