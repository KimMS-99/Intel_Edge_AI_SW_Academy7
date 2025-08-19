APP := uart3_irq_app
MOD := uart3_driver_irq

obj-m := $(MOD).o

CROSS = ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf-
CC := arm-linux-gnueabihf-gcc

KDIR := /home/ubuntu/pi_bsp/kernel/linux
PWD := $(shell pwd)

default: clean $(APP)
	$(MAKE) -C $(KDIR) M=$(PWD) modules $(CROSS)
	cp $(MOD).ko $(APP) /srv/nfs_ubuntu/uart3

$(APP): $(APP).c
	$(CC) $^ -o $@

clean:
	rm -rf *.o *.ko *.mod.* .*.cmd *.symvers *.order .tmp_versions $(APP)