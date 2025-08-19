#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

static int hello_init(void)
{
	printk(KERN_INFO "Hello, Wrold\n");
	return 0;
}

static void hello_exit(void)
{
	printk(KERN_INFO "Goodbye, World\n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_AUTHOR("KCCI-AIOT");
MODULE_DESCRIPTION("test module");
MODULE_LICENSE("Dual BSD/GPL");


