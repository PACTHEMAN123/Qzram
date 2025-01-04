# SPDX-License-Identifier: GPL-2.0-only
#zram-y	:=	zcomp.o zram_drv.o

#obj-$(CONFIG_ZRAM)	+=	zram.o


NAME = myzram
KDIR := /usr/lib/modules/5.15.0-126-generic/build/

obj-m := $(NAME).o

$(NAME)-objs := zcomp.o zram_drv.o qat.o qat-lz4.o

PWD := $(shell pwd)

build:
	$(MAKE) -C $(KDIR) M=$(PWD) modules EXTRA_LDFLAGS=-L/usr/local/lib/ -lqatzip

clean: 
	$(MAKE) -C $(KDIR) M=$(PWD) clean

insmod:
	sudo insmod $(NAME).ko num_devices=1 #默认就是1

rmmod:
	sudo rmmod $(NAME)