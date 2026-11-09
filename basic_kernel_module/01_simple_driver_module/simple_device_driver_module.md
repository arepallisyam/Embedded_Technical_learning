Creating, Building, Loading, and Removing a Simple Linux Kernel Module
# 1. Introduction

A Linux Kernel Module (LKM) is a piece of code that can be loaded into or removed from the Linux kernel dynamically without rebooting the system.

In this document, we will learn how to:

Create a simple Linux kernel module.
Create a Makefile to compile the module.
Build the kernel module and generate a .ko file.
Insert the module into the running kernel.
Verify whether the module is loaded.
Remove the module from the kernel.
View kernel log messages.

# 2. Create the Source File

First, create a C source file named simple_driver.c.

vi simple_driver.c

Add the following code:

#include <linux/init.h>
#include <linux/module.h>

int simple_driver_init(void);
void simple_driver_exit(void);

int simple_driver_init(void)
{
    printk(KERN_ALERT "Inside the %s function\n", __FUNCTION__);
    return 0;
}

void simple_driver_exit(void)
{
    printk(KERN_ALERT "Inside the %s function\n", __FUNCTION__);
}

module_init(simple_driver_init);
module_exit(simple_driver_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("A Simple Device Driver Module");
MODULE_AUTHOR("Syam");

Explanation
#include <linux/init.h> – Provides initialization and cleanup-related definitions.
#include <linux/module.h> – Provides Linux kernel module-related definitions.
simple_driver_init() – This function executes when the module is loaded into the kernel.
simple_driver_exit() – This function executes when the module is removed from the kernel.
printk() – Used to print messages to the kernel log.
module_init() – Registers the module initialization function.
module_exit() – Registers the module cleanup function.
MODULE_LICENSE("GPL") – Specifies the module license.
MODULE_DESCRIPTION() – Provides a description of the module.
MODULE_AUTHOR() – Specifies the module author.

3. Create the Makefile

Create a file named Makefile in the same directory.
vi Makefile

Add the following line:

makefile
obj-m := simple_module.o

Explanation
obj-m tells the kernel build system to compile the source file as a loadable kernel module.
simple_module.o is the object file generated from simple_module.c.
The final output will be simple_module.ko.

Note: Make sure to use lowercase obj-m, not Obj-m.

4. Compile the Kernel Module

Before compiling, ensure that the kernel headers and build dependencies for your running kernel are installed.

Execute the following command:

bash
make -C /lib/modules/$(uname -r)/build M=$PWD modules

Explanation
make – Invokes the build system.
-C /lib/modules/$(uname -r)/build – Specifies the kernel build directory corresponding to the currently running kernel.
M=$PWD – Specifies the current working directory containing the module source code.
modules – Instructs the kernel build system to build the module.
Expected Output

After successful compilation, the following file will be generated:

text
simple_module.ko


The .ko extension stands for Kernel Object.

To verify the generated files:

ls

5. Clean the Build Files

To remove the generated object files and other build-related files, execute:

make -C /lib/modules/$(uname -r)/build M=$PWD clean


This command cleans the files generated during compilation.

6. Insert the Kernel Module

After successfully generating the simple_module.ko file, insert the module into the running Linux kernel.

Execute:
sudo insmod simple_module.ko

Explanation
insmod stands for Insert Module.
It loads the specified kernel module into the running kernel.
sudo provides the root privileges required to insert a kernel module.

If the command executes successfully, the module will be loaded into the kernel.

7. Verify Whether the Module Is Loaded

To check whether the module has been successfully loaded, execute:

lsmod


To search specifically for our module:

lsmod | grep simple_module


If the module is loaded successfully, you should see an entry similar to:

text
simple_module    16384    0


The output confirms that the simple_module is currently loaded into the kernel.

8. Remove the Kernel Module

To remove the loaded kernel module, execute:

sudo rmmod simple_module

Explanation
rmmod stands for Remove Module.
It removes the specified module from the running kernel.
When the module is removed, the simple_module_exit() function is executed.

To verify that the module has been removed:

lsmod | grep simple_module

If there is no output, the module is no longer loaded.

9. Check Kernel Log Messages

The printk() function is used to print messages from the kernel module.

To view the kernel log messages, execute:

sudo dmesg


To continuously monitor kernel messages:

sudo dmesg -w


Alternatively, on systems that use rsyslog, you can check:

bash
sudo tail -f /var/log/syslog

Expected Log Messages

When the module is inserted:

text
Inside the simple_driver_init function


When the module is removed:

text
Inside the simple_driver_exit function


These messages confirm that the initialization and cleanup functions are executing successfully.

10. Complete Command Summary
Operation	Command
Create C file	vi simple_module.c
Create Makefile	vi Makefile
Compile module	make -C /lib/modules/$(uname -r)/build M=$PWD modules
Clean build files	make -C /lib/modules/$(uname -r)/build M=$PWD clean
Insert module	sudo insmod simple_module.ko
Check loaded modules	lsmod
Search specific module	lsmod | grep simple_module
Remove module	sudo rmmod simple_module
View kernel logs	sudo dmesg
Monitor kernel logs	sudo dmesg -w
Monitor system logs	sudo tail -f /var/log/syslog
11. Execution Flow

The overall workflow for creating and testing a simple Linux kernel module is:

text
       Create Source File
        simple_module.c
               |
               v
         Create Makefile
               |
               v
       Compile Kernel Module
               |
               v
        simple_module.ko
               |
               v
        Insert the Module
      sudo insmod simple_module.ko
               |
               v
       Verify Using lsmod
               |
               v
       Check Kernel Logs
               |
               v
        Remove the Module
      sudo rmmod simple_module
               |
               v
       Check Removal Logs

12. Conclusion

In this exercise, we created and compiled a simple Linux kernel module and generated a .ko file.

We then loaded the module into the running Linux kernel using insmod, verified its presence using lsmod, and removed it using rmmod.

Finally, we verified the execution of the module initialization and cleanup functions by checking the kernel log messages.

This exercise provides a basic understanding of Linux kernel module development and the module loading and unloading process.
