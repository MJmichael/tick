/*************************************************************************
	> File Name: bus.h
	> Author: fwj
	> Mail: fuwenjie2011@126.com 
	> Created Time: 2015年04月08日 星期三 16时41分58秒
 ************************************************************************/
#ifndef _BUS_H
#define _BUS_H
#include <linux/device.h>

struct usb_device{
	unsigned long phys, virt;
	int irq;
	int VenderID, DeviceID;

	struct device dev;
};

struct usb_driver{
	int VenderID, DeviceID;

	struct device_driver drv;
};

/**
int usb_device_register(struct device *dev);
void usb_device_unregister(struct device *dev);

int usb_driver_register(struct device_driver *drv);
void usb_driver_unregister(struct device_driver *drv);
**/

int usb_device_register(struct usb_device *dev);
void usb_device_unregister(struct usb_device *dev);

int usb_driver_register(struct usb_driver *drv);
void usb_driver_unregister(struct usb_driver *drv);
#endif
