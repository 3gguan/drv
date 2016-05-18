IMOD := netlink_kernel
IMOD_SRC := netlink_kernel_init.o printhex.o

ifneq ($(KERNELRELEASE),)
obj-m := $(IMOD).o
$(IMOD)-y := $(IMOD_SRC)

else
KDIR ?= /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

default:
	$(MAKE) -C $(KDIR) M=$$PWD

endif
.PHONY: clean
. clean:
	-rm -rf *.mod.c *.o *.order *.symvers *.ko
