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