obj-m += netlinkKernelSpace.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
ins:
	sudo insmod netlinkKernelSpace.ko
rm:
	sudo rmmod netlinkKernelSpace
log:
	sudo dmesg | tail -$L
