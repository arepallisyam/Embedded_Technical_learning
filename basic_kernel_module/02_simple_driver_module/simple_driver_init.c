#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

int simple_driver_init(void);

int simple_driver_init(void)
{
	printk(KERN_ALERT "Inside the %s function\n", __FUNCTION__);
	return 0;
}

module_init(simple_driver_init);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("A Simple LINUX Driver Module");
MODULE_AUTHOR("SYAM");
MODULE_VERSION("1.0");
