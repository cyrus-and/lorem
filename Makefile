obj-m += lorem.o

all:
	$(MAKE) -C /lib/modules/$(shell uname -r)/build M=$(shell pwd)

clean:
	$(MAKE) -C /lib/modules/$(shell uname -r)/build M=$(shell pwd) clean

insert:
	insmod lorem.ko

remove:
	-rmmod lorem.ko

reload: remove insert

.PHONY: all clean insert remove reload
