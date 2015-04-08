/*************************************************************************
	> File Name: device.c
	> Author: fwj
	> Mail: fuwenjie2011@126.com 
	> Created Time: 2015年03月20日 星期五 10时24分57秒
 ************************************************************************/
#include <linux/module.h>
#include <linux/init.h>

#include <linux/device.h>
#include <linux/sysfs.h>

#include "bus.h"

MODULE_LICENSE("Dual BSD/GPL");   //内核license
static char module_name[64] = "coffe"; 
//extern struct bus_type usb_bus;
//extern int usb_device_register(struct device* dev);
//extern void usb_device_unregister(struct device* dev);
#if 0
struct bus_type usb_bus = {
	.name = "usb-fwj",
};
#endif

static void usb_dev_release(struct device *dev)
{
	printk("usb dev release\n");
}

/* define usb device */
#if 0 
struct device_type usb_device_type = {
	.name = "usb_device",
	.release = usb_dev_release,
};

const struct device_type *type_usb = &usb_device_type;

struct device usb_device = {
	.init_name = "usb_fwj",
//	.type = type_usb,
//	.bus = &usb_bus,
	.release = usb_dev_release,
};
#endif

struct usb_device mouse_dev = {
	.VenderID = 0x1122,
	.DeviceID = 0x3344,
	.dev = {
		.init_name = "usb_fwj",
		.release = usb_dev_release,
	},
};

ssize_t show_device_version(struct device *dev, struct device_attribute *attr, char *buf)
{
	//'\0' and '\n'
	return snprintf(buf, strlen(module_name)+2, "%s\n", module_name);
}

ssize_t store_device_version(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
	//'\0' and '\n'
	return snprintf(module_name, strlen(buf)+2, "%s\n", buf);
}

static DEVICE_ATTR(version, 0777, show_device_version, store_device_version);

static int __init usb_device_init(void)
{
	int ret;

	//总线注册，必须检测返回值
//	ret = device_register(&usb_device);
	ret = usb_device_register(&mouse_dev);
	if(ret){
		printk("usb device register failed\n");
		return ret;
	}

#if 0
	ret = device_create_file(&usb_device, &dev_attr_version);
	if(ret){
		printk("usb device create file failed\n");
		return ret;
	}
#endif

	printk("usb device register ok\n");
	return 0;
}

static void __exit usb_device_exit(void)
{
//	device_remove_file(&usb_device, &dev_attr_version);
//	device_unregister(&usb_device);
	usb_device_unregister(&mouse_dev);
	printk("usb device unregsiter\n");
}

module_init(usb_device_init);
module_exit(usb_device_exit);
