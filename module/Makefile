#Makefile for modules

#OBJ:=$(wildcard *.c)

#OBJ-O:=$(patsubst %.c, %.o, $(OBJ))
#obj-m=$(OBJ-O)

obj-m=hello.o
obj-m+=lock.o
obj-m+=lock_ref.o
#obj-m+=meson_uart.o
obj-m+=kobject.o
obj-m+=bus.o
obj-m+=device.o
obj-m+=driver.o
obj-m+=platform_driver.o
obj-m+=platform_device.o

KERNELDIR:=/lib/modules/$(shell uname -r)/build
#KERNELDIR:=/home/fwj/amlogic/out/target/product/m201/obj/KERNEL_OBJ
PWD:=$(shell pwd)

.PHONY : clean modules
modules:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules 
clean:
	-@rm $(obj-m) *.ko *.mod.* modules.* Module.*
