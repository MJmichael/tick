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

struct bus_type usb_bus = {
	.name = "usb-fwj",
};

static void usb_dev_release(struct device *dev)
{
	printk("usb dev release\n");
}

/* define usb device */
struct device_type usb_device = {
	.name = "usb_device",
//	.bus = &usb_bus;/*指定bus，会在bus生成软链接*/
	.release = usb_dev_release,
};

ssize_t show_device_name(struct device *dev, struct device_attribute *attr, char *buf)
{
	//'\0' and '\n'
	return snprintf(buf, strlen(module_name)+2, "%s\n", module_name);
}

ssize_t store_device_name(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
	//'\0' and '\n'
	return snprintf(module_name, strlen(buf)+2, "%s\n", buf);
}

static DEVICE_ATTR(version, 0777, show_device_name, store_device_name);

static int __init usb_device_init(void)
{
	int ret;

	//总线注册，必须检测返回值
	ret = device_register(&usb_device);
	if(ret){
		printk("usb bus register failed\n");
		return ret;
	}

	ret = device_create_file(&usb_device, &dev_attr_version_name);
	if(ret){
		printk("usb bus create file failed\n");
		return ret;
	}

	printk("usb bus register ok\n");
	return 0;
}

static void __exit usb_device_exit(void)
{
	device_remove_file(&usb_device, &dev_attr_version_name);
	device_unregister(&usb_device);
	printk("usb bus unregsiter\n");
}

module_init(usb_device_init);
module_exit(usb_device_exit);
