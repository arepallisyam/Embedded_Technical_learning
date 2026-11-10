
#obj-m := simple_driver.o  # only this line will present in makefile in method one

#========================================================
# Method 1: Direct Terminal Compilation
#========================================================

obj-m := simple_driver.o
obj-m += simple_driver_init.o
obj-m += simple_driver_exit.o

obj-m := combined_simple_module.o
combined_simple_module-objs := simple_driver_init.o simple_driver_exit.o

# Commands to execute directly in the terminal:
#
# make -C /lib/modules/$(uname -r)/build M=$PWD modules
# make -C /lib/modules/$(uname -r)/build M=$PWD clean



