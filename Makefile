obj-m += hello_dev.o

KDIR := /lib/modules/$(shell uname -r)/build

PWD := $(shell pwd)

all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules
