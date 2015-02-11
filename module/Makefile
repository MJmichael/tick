#Makefile for modules

obj-m=hello.o
obj-m+=lock.o

KERNELDIR:=/lib/modules/$(shell uname -r)/build
#KERNELDIR:=/home/fwj/amlogic/out/target/product/m201/obj/KERNEL_OBJ
PWD:=$(shell pwd)

.PHONY : clean modules

modules:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
clean:
	-@rm $(obj-m) *.ko *.mod.* modules.* Module.*
