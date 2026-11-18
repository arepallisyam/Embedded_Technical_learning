sudo insmod modules_param.ko count=5
- notice that the name that you giving in the command that is the count variable should be exactly the same name as what you've given in your code.
- after giving the "count = 5" hello print got printed five times so because our count was set to five.
- it's a optinal to pass a module parameter.


# second Method to change the count value:

- we have changeing the value of count now by modifying the sys module entry.

syamprasad@administrator:~$ ls -l /sys/module/modules_param/parameters/count 
-rw-r--r-- 1 root root 4096 Nov 11 13:02 /sys/module/modules_param/parameters/count
syamprasad@administrator:~$ cat /sys/module/modules_param/parameters/count 
1
syamprasad@administrator:~$ echo 5 | sudo tee /sys/module/modules_param/parameters/count 
[sudo] password for syamprasad: 
5
syamprasad@administrator:~$ cat /sys/module/modules_param/parameters/count 
5
syamprasad@administrator:~$ 

- we have to give the permission in module_param.
    - Ex: module_param(count, int, 0644);

- module_param : is macro to be used for exporting a global varibale as a module parameter and it takes three paramenters the first parameter of the variable itself the second one is the type if the variable and the third last field is basically the permission.
- If you give a ZERO value here means you would it basically means you don't want to cahnge this module variable after the module has been loaded into kernel space and if you give a NON-ZERO value here which is typically 644 and in octal you are basically indicating that you allow the user to change the value of this parameter after loading it into kernel space.


