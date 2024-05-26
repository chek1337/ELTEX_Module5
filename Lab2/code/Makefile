obj-m += readwritekernel.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
ins:
	sudo insmod readwritekernel.ko
rm:
	sudo rmmod readwritekernel.ko
log:
	sudo dmesg | tail -$L