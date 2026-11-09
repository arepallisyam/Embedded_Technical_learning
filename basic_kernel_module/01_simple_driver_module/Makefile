
#obj-m := simple_driver.o  # only this line will present in makefile in method one

#========================================================
# Method 1: Direct Terminal Compilation
#========================================================

# obj-m := simple_driver.o

# Commands to execute directly in the terminal:
#
# make -C /lib/modules/$(uname -r)/build M=$PWD modules
# make -C /lib/modules/$(uname -r)/build M=$PWD clean


#========================================================
# Method 2: Compilation Using Makefile
#========================================================

obj-m := simple_driver.o

KDIR := /lib/modules/$(shell uname -r)/build
PWD  := $(shell pwd)

all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean


#========================================================
# Method 1: Direct Terminal Commands
#========================================================
#
# make -C /lib/modules/$(uname -r)/build M=$PWD modules
# make -C /lib/modules/$(uname -r)/build M=$PWD clean
#
#========================================================


#========================================================
# Method 2: Using Makefile
#========================================================
#
# make
# make clean
#
#========================================================

#===========================
#
#Important: Both methods use the same kernel build system. For Method 1, keep obj-m := simple_driver.o in the Makefile and run the commands directly. 
#For Method 2, use make and make clean.
#
#=======================================

