
#obj-m := simple_driver.o  # only this line will present in makefile in method one

#========================================================
# Method 1: Direct Terminal Compilation
#========================================================

obj-m := simple_driver.o
obj-m += reduce_memory_simple_driver.o
obj-m += function_call.o


# Commands to execute directly in the terminal:
#
# make -C /lib/modules/$(uname -r)/build M=$PWD modules
# make -C /lib/modules/$(uname -r)/build M=$PWD clean



