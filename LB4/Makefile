ifneq ($(KERNELRELEASE),)
# kbuild part of makefile
obj-m := hello.o
else
# normal makefile
KDIR ?= $(HOME)/repos/linux-stable

default:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean

endif
