#include <linux/init.h>
#include <linux/module.h>

#include <linux/fs.h> /* For the charecter driver suppport  */

int char_open(struct inode *, struct file *);
ssize_t char_read(struct file *, char __user *, size_t, loff_t *);
ssize_t char_write(struct file *, const char __user *, size_t, loff_t *);
int char_close(struct inode *, struct file *);

int char_open(struct inode *pinode, struct file *pfile)
{
	printk(KERN_ALERT "Inside the %s function\n", __FUNCTION__);
	return 0;
}

ssize_t char_read(struct file *pfile, char __user *buffer, size_t length, loff_t *offset)
{
	printk(KERN_ALERT "Inside the %s function\n", __FUNCTION__);
	return 0;
}

ssize_t char_write(struct file *pfile, const char __user *buffer, size_t length, loff_t *offset)
{
	printk(KERN_ALERT "Inside the %s function\n", __FUNCTION__);
	return length;
}

int char_close(struct inode *pinode, struct file *pfile)
{
	printk(KERN_ALERT "Inside the %s function\n", __FUNCTION__);
	return 0;
}

/* To hold the file operations performed on this device */
struct file_operations char_driver_file_operation = {
	.owner = THIS_MODULE,
	.open = char_open,
	.read = char_read,
	.write = char_write,
	.release = char_close,
};


int simple_char_driver_init(void)
{
	printk(KERN_ALERT "Inside the %s function\n", __FUNCTION__);

	/* Register with the kernel and indicate that we are registering a character device driver */
	register_chrdev(220 /*Major Number */,
			"simple char dev" /*Name of the driver*/,
			&char_driver_file_operation /*File Operations*/);
	return 0;
}

void simple_char_driver_exit(void)
{
	printk(KERN_ALERT "Inside the %s function\n", __FUNCTION__);
	
	/* unregister the character device driver */
	unregister_chrdev(240, "simple char dev");
}

module_init(simple_char_driver_init);
module_exit(simple_char_driver_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("SIMPLE CHAR DRIVER");
MODULE_AUTHOR("SYAM");
