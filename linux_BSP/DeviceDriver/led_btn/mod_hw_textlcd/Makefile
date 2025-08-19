MOD := mod_hw_textlcd
obj-m := $(MOD).o
PWD := $(shell pwd)
ARCH = ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf-
#ARCH = 

#KDIR := /lib/modules/$(shell uname -r)/build
KDIR := /home/ubuntu/udoo_linux_bsp/kernel/linux_kernel-3.14-1.0.x-udoo

default:
	$(MAKE) -C $(KDIR) M=$(PWD) modules $(ARCH)
	cp $(MOD).ko /srv/nfs

clean:
	rm -rf $(MOD).ko
	rm -rf $(MOD)*.o
	rm -rf $(MOD)*mod*
	rm -rf Module.*
	rm -rf modules.*
	rm -rf .$(MOD)*
	rm -rf .Module.*
	rm -rf .modules.*
	rm -rf .tmp_versions
