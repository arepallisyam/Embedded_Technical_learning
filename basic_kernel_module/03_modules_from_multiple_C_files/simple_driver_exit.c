#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

void simple_driver_exit(void);

void simple_driver_exit(void)
{
	printk(KERN_ALERT "Inside the only %s function\n", __FUNCTION__);
	printk(KERN_INFO "Bye Syam\n");
}

module_exit(simple_driver_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("A Simple LINUX Driver Module");
MODULE_AUTHOR("SYAM");
MODULE_VERSION("1.0");
