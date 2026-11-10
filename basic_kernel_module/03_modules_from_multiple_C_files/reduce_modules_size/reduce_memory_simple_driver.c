#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

int simple_driver_init(void);
void simple_driver_exit(void);

__init int simple_driver_init(void)
{
	printk(KERN_ALERT "Inside the %s function\n", __FUNCTION__);
	return 0;
}


void simple_driver_exit(void)
{
	printk(KERN_ALERT "Inside the %s function\n", __FUNCTION__);
	printk(KERN_INFO "Bye Syam\n");
}

module_init(simple_driver_init);
module_exit(simple_driver_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("A Simple LINUX Driver Module");
MODULE_AUTHOR("SYAM");
MODULE_VERSION("1.0");
