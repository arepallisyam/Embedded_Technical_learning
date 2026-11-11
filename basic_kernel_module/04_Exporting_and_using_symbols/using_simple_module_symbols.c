#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

int simple_driver_init(void);
void simple_driver_exit(void);
int simple_driver_function(void);

int simple_driver_init(void)
{
	printk(KERN_ALERT "Inside the %s function\n", __FUNCTION__);
	simple_driver_function();
	return 0;
}

void simple_driver_exit(void)
{
	printk(KERN_ALERT "Inside the %s function\n", __FUNCTION__);
}

module_init(simple_driver_init);
module_exit(simple_driver_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("USING THE SYMBOLS");
