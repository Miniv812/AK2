ifneq ($(KERNELRELEASE),)
# kbuild part of makefile
ccflags-y += -I$(src)/inc
obj-m := hello1.o hello2.o
else
# normal makefile
KDIR ?= $(HOME)/repos/linux-stable

default:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean

endif
