#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/moduleparam.h>

int count =1;
module_param(count, int, 0);

int module_param_init(void)
{
	int index = 0;
	printk(KERN_INFO "Inside the %s function\n", __FUNCTION__);
	for(index = 0; index < count; index++)
	{
		printk(KERN_INFO "Hello : Index = %d\n", index);
	}
	return 0;
}

void module_param_exit(void)
{
	printk(KERN_INFO "Inside the %s function\n", __FUNCTION__);
}

module_init(module_param_init);
module_exit(module_param_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Passing the parameters to module");
