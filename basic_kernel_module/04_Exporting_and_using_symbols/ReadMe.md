make -C /lib/modules/$(uname -r)/build M=$PWD modules
make -C /lib/modules/$(uname -r)/build M=$PWD clean
sudo tail /var/log/syslog
sudo tail -f \/var/log/syslog

- Your terminal prompt is displaying the full directory path. You can shorten it using a few methods.
        export PS1='\u@\h:\W$ ' 

- open the two programs in split screen :
    vsplit ./export_simple_module_symbols.c
