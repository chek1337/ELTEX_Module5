# Лабораторная работа №1

### Задание
Познакомиться с основами программирования на уровне ядра
### Ход работы
1) Установить необходимые заголовочные файлы
```bash
zeusubuntu@zeusubuntu:~$ sudo apt-get install build-essential linux-headers-$(uname -r)
```
2) Создать программный файл hellokernel.c
```C
#include <linux/module.h>   
#include <linux/kernel.h>   
#include <linux/init.h>  

MODULE_LICENSE("ELTEX");
MODULE_AUTHOR("Loychenko");
MODULE_DESCRIPTION("The program that makes \"Hello World!\"");

static int __init hello_init(void)
{
    printk(KERN_INFO "\"Hello world!\" module ON\n");
    return 0;
}

static void __exit hello_cleanup(void)
{
    printk(KERN_INFO "\"Hello world!\" module OFF\n");
}

module_init(hello_init);
module_exit(hello_cleanup);
```
3) Создать Makefile
```Makefile
obj-m += hellokernel.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
```
4) Выполнить компиляцию при помощи Makefile'а
```bash
zeusubuntu@zeusubuntu:~/Documents/ELTEX/ex1$ make
make -C /lib/modules/6.8.0-31-generic/build M=/home/zeusubuntu/Documents/ELTEX/ex1 modules
make[1]: вход в каталог «/usr/src/linux-headers-6.8.0-31-generic»
warning: the compiler differs from the one used to build the kernel
  The kernel was built by: x86_64-linux-gnu-gcc-13 (Ubuntu 13.2.0-23ubuntu4) 13.2.0
  You are using:           gcc-13 (Ubuntu 13.2.0-23ubuntu4) 13.2.0
  CC [M]  /home/zeusubuntu/Documents/ELTEX/ex1/hellokernel.o
  MODPOST /home/zeusubuntu/Documents/ELTEX/ex1/Module.symvers
  CC [M]  /home/zeusubuntu/Documents/ELTEX/ex1/hellokernel.mod.o
  LD [M]  /home/zeusubuntu/Documents/ELTEX/ex1/hellokernel.ko
  BTF [M] /home/zeusubuntu/Documents/ELTEX/ex1/hellokernel.ko
Skipping BTF generation for /home/zeusubuntu/Documents/ELTEX/ex1/hellokernel.ko due to unavailability of vmlinux
make[1]: выход из каталога «/usr/src/linux-headers-6.8.0-31-generic»
```
<p align="center">
  <img src="https://github.com/chek1337/ELTEX_Module5/blob/main/Lab1/screenshots/pic1.png" />
</p>

5) Проверить работоспособность своего модуля, вставив и убрав его 
<p align="center">
  <img src="https://github.com/chek1337/ELTEX_Module5/blob/main/Lab1/screenshots/pic2.png" />
</p>
