major number and the minor number of the device, so linux associates /dev/ entry to the corresponding driver running in the kernel space by the major number.
so the other way of saying so the major number represents a unique of identifying a driver which can be associated with a particular device and minor number basically corresponds to the number of instances of the device.

# Linux Character and Block Device Drivers – Major and Minor Numbers
- 1. Introduction

	- In Linux, device files are represented under the /dev directory. These files act as an interface between user-space applications and kernel-space device drivers.

- Linux uses two important numbers to identify devices:

    - Major Number
    - Minor Number

# Major Number

The major number identifies the device driver associated with a device file.

In other words, the Linux kernel uses the major number to determine which device driver should handle the operations performed on that device file.

# Minor Number

The minor number is used by the device driver to distinguish between different devices or instances managed by the same driver.

For example, a single driver may manage multiple devices. The major number identifies the driver, while the minor number helps the driver identify the specific device.

In simple terms:

    Major number → Identifies the device driver.
    Minor number → Identifies a particular device or instance handled by that driver.
    
# Understanding Device Files Using ls -l

We can use the ls -l command to examine device files inside the /dev directory.
2.1 Listing Character Device Files

Execute the following command:
ls -l /dev | head

Example output:
syamprasad@administrator:~$ ls -l /dev | head

total 0
crw-------   1 root root 10, 264 Nov 18 06:56 acpi_thermal_rel
crw-r--r--   1 root root 10, 235 Nov 18 06:56 autofs
drwxr-xr-x   2 root root      460 Nov 18 06:56 block

In the output, observe the first character of the file permissions:

    c → Character device.
    b → Block device.
    d → Directory.
    - → Regular file.

For example:
text

crw------- 1 root root 10, 264 acpi_thermal_rel

Here:

    c indicates that it is a character device.
    10 is the major number.
    264 is the minor number.


#  Listing Block Device Files

To identify block devices associated with storage devices, execute:
bash

ls -l /dev | grep sda

Example output:
text

syamprasad@administrator:~$ ls -l /dev | grep sda

brw-rw---- 1 root disk 8, 0 Nov 18 07:05 sda
brw-rw---- 1 root disk 8, 1 Nov 18 07:05 sda1


Device		Type	Major Number	Minor Number
/dev/sda	Block	8	0
/dev/sda1	Block	8	1

Explanation:

    b indicates that these are block devices.
    8 is the major number, which identifies the driver responsible for handling these devices.
    0 and 1 are minor numbers that distinguish between the disk and its partition.

For this example:

    /dev/sda represents the entire disk.
    /dev/sda1 represents the first partition of that disk.

Important: The same major number can be associated with multiple devices managed by the same driver. The minor number helps distinguish between them.

 # 3. Understanding the Linux Device Driver Header File

Linux provides header files that contain structures and function definitions required for implementing device drivers.

One important header file is:

/lib/modules/$(uname -r)/build/include/linux/fs.h

To open this file:
vi /lib/modules/$(uname -r)/build/include/linux/fs.h

For example:
/lib/modules/7.0.0-42-generic/build/include/linux/fs.h
Inside this header file, we can find the definition of the file_operations structure.

Some important function pointers are:

ssize_t (*read)(struct file *, char __user *, size_t, loff_t *);

ssize_t (*write)(struct file *, const char __user *, size_t, loff_t *);

int (*open)(struct inode *, struct file *);

int (*release)(struct inode *, struct file *);

# Understanding These Functions
Function	Purpose
open()	Called when a user-space application opens the device file.
read()	Called when an application reads data from the device.
write()	Called when an application writes data to the device.
release()	Called when the device file is closed.

These functions act as communication interfaces between user-space applications and the kernel-space device driver.

For example:

When we execute:
cat /dev/simple_char_device

The kernel invokes the read() function implemented by the character device driver, provided the driver has registered the corresponding operation.

Similarly, when we execute:
echo "testing" > /dev/simple_char_device

The kernel invokes the driver's write() function.

# Loading the Character Device Driver

After implementing the character device driver and compiling it, we get a kernel module file with the .ko extension.

For example:

simple_char_driver.ko

To load the driver into the Linux kernel, execute:
sudo insmod simple_char_driver.ko


Verify Whether the Driver Is Loaded

Execute:

lsmod | grep sim

Example output:
simple_char_driver  12288  0


# 5. Identifying the Major Number

After loading the character device driver, we need to identify its assigned major number.

Linux maintains a list of registered character and block device drivers in:
/proc/devices

Execute:
cat /proc/devices | grep simple

Example output:
220 simple char dev

Here:

    220 is the major number.
    simple char dev is the registered device name.
    char indicates that it is a character device driver.

We will use this major number while creating the device node.

- Note: The major number shown here is an example. If the driver dynamically allocates a major number, it may change when the module is loaded again.




# 6. Creating a Character Device Node Using mknod

Loading a character device driver into the kernel does not automatically guarantee that a device file will be created under /dev.

We need to create a device node manually using the mknod command (unless the driver or userspace device manager creates it automatically).

Syntax:
bash

sudo mknod -m 666 <device_name> c <major_number> <minor_number>

Parameter	Description
mknod		Creates a special device file.
-m 666		Sets read and write permissions for all users.
c		Specifies a character device.
220		Major number.
0		Minor number.

Execute:

sudo mknod -m 666 /dev/simple_char_device c 220 0

This creates a character device node named:
/dev/simple_char_device

# Verify the Device Node

Execute:
ls -l /dev/simple_char_device

Example output:

crw-rw-rw- 1 root root 220, 0 Nov 18 08:40 /dev/simple_char_device

Explanation:

    c → Character device.
    rw-rw-rw- → Read and write permissions for everyone.
    220 → Major number.
    0 → Minor number.

Now the device node is created and associated with the registered character device driver through its major and minor numbers.

Security note: Permission 666 allows every local user to read from and write to the device. For real applications, use appropriate restricted permissions.

# 7. Monitoring Kernel Logs

To monitor kernel messages while interacting with the character device driver, execute:

sudo tail -f /var/log/syslog

This continuously displays new log messages written to the system log.

Alternatively, we can use:

sudo dmesg -w

This continuously monitors kernel messages.

For example, when we open, read, or write to the character device, the driver may generate log messages using printk().

These messages can help us understand which driver functions are being invoked.

# 8. Reading Data From the Character Device

After creating the device node, we can access it from user space.

Execute:

cat /dev/simple_char_device

What happens internally?

    The cat command opens /dev/simple_char_device.
    The Linux kernel identifies the character device using its major and minor numbers.
    The kernel routes the operation to the registered device driver.
    The driver's open() function is invoked.
    The driver's read() function is invoked to retrieve data.
    The returned data is displayed in the terminal.

The actual output depends on the implementation of the driver's read() function.


# 9. Writing Data to the Character Device

To write data into the character device, execute:

echo "testing" | sudo tee /dev/simple_char_device

Alternatively:
sudo sh -c 'echo "testing" > /dev/simple_char_device'

Why not simply use sudo echo "testing" > /dev/simple_char_device?

Because the shell performs the output redirection (>) before executing sudo. Therefore, the redirection itself may fail due to insufficient permissions.
What Happens Internally?

    The echo command generates the string testing.
    The data is written to /dev/simple_char_device.
    The Linux kernel identifies the corresponding character device driver.
    The driver's open() function is invoked.
    The driver's write() function is invoked.
    The driver processes the data according to its implementation.

The driver's write() function is responsible for handling the data received from user space.

# 10. Complete Command Reference

Step	Command							Purpose
1	ls -l /dev						List device files.
2	find /dev -type c					List character device files.
3	ls -l /dev | grep sda					Identify block devices associated with sda.
4	vi /lib/modules/$(uname -r)/build/include/linux/fs.h	Examine the Linux filesystem header.
5	sudo insmod simple_char_driver.ko			Load the character device driver.
6	lsmod | grep sim					Verify that the driver is loaded.
7	cat /proc/devices | grep simple				Identify the registered major number.
8	sudo mknod -m 666 /dev/simple_char_device c 220 0	Create the character device node.
9	ls -l /dev/simple_char_device				Verify the device node.
10	sudo dmesg -w						Monitor kernel messages.
11	cat /dev/simple_char_device				Read data from the device.
12	echo "testing" | sudo tee /dev/simple_char_device	Write data to the device.

# Key Takeaways

    - Device files are available under the /dev directory.
    - Linux supports character devices and block devices.
    - The major number identifies the registered device driver.
    - The minor number identifies a particular device or instance handled by the driver.
    - /proc/devices provides information about registered device drivers.
    - insmod loads a kernel module into the running kernel.
    - mknod creates a device node using the major and minor numbers.
    - file_operations defines the operations that a device driver can support.
    - User-space applications interact with device drivers through device files.
    - The read() and write() functions provide communication between user space and kernel space.




















    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
 
    
    
    
