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

MODULE_LICENSE("Dual BSD/GPL");   //内核license
static char module_name[64] = "coffe"; 
extern struct bus_type usb_bus;

struct device_driver usb_driver = {
	.name = "usb_driver",
	.bus = &usb_bus,
//	.release = usb_dev_release,
};

ssize_t show_driver_version(struct device_driver *dev, char *buf)
{
	//'\0' and '\n'
	return snprintf(buf, strlen(module_name)+2, "%s\n", module_name);
}

ssize_t store_driver_version(struct device_driver *dev, const char *buf, size_t count)
{
	//'\0' and '\n'
	return snprintf(module_name, strlen(buf)+2, "%s\n", buf);
}

static DRIVER_ATTR(version, 0777, show_driver_version, store_driver_version);

static int __init usb_driver_init(void)
{
	int ret;

	//总线注册，必须检测返回值
	ret = driver_register(&usb_driver);
	if(ret){
		printk("usb driver register failed\n");
		return ret;
	}

	ret = driver_create_file(&usb_driver, &driver_attr_version);
	if(ret){
		printk("usb driver create file failed\n");
		return ret;
	}

	printk("usb driver register ok\n");
	return 0;
}

static void __exit usb_driver_exit(void)
{
	driver_remove_file(&usb_driver, &driver_attr_version);
	driver_unregister(&usb_driver);
	printk("usb driver unregsiter\n");
}

module_init(usb_driver_init);
module_exit(usb_driver_exit);
