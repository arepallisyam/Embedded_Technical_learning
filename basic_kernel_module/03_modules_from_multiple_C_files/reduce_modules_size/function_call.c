#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

int simple_driver_init(void);
void simple_driver_exit(void);

__init int simple_driver_function1(void)
{
	printk(KERN_ALERT "Inside the function1\n");
	return 0;
}

int simple_driver_function2(void)
{
	printk(KERN_ALERT "Inside the function2\n");
	return 0;
}

__initdata int count = 5;

__init int simple_driver_init(void)
{
	int index =0;

	printk(KERN_ALERT "Inside the %s function\n", __FUNCTION__);

	for(index = 0; index < count; index++)
	{
		printk(KERN_ALERT "Index = %d\n",index);
	}

	simple_driver_function1();
	simple_driver_function2();
	return 0;
}


void simple_driver_exit(void)
{
	printk(KERN_ALERT "Inside the %s function\n", __FUNCTION__);
	printk(KERN_INFO "Bye Syam\n");
	simple_driver_function2();
}

module_init(simple_driver_init);
module_exit(simple_driver_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("A Simple LINUX Driver Module");
MODULE_AUTHOR("SYAM");
MODULE_VERSION("1.0");
