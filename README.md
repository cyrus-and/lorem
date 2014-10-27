lorem
=====

Lorem ipsum generator as a Linux kernel module.

Build
-----

    make

Example
-------

Load the module into the kernel:

    sudo make insert

Generate 1GB of lorem ipsum in your home folder:

    dd if=/dev/lorem of=~/lorem.txt bs=1 count=1G

Finally remove the module from the kernel:

    sudo make remove
