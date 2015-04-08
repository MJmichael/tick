/*************************************************************************
	> File Name: bus.c
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

/* match 函数 */
int usb_bus_match(struct device* dev, struct device_driver *drv)
{
#if 1
	if(dev==NULL || drv==NULL)
	{
		printk("NULL pointer\n");
		return -1;
	}

	if(!strcmp(dev_name(dev), drv->name))
		printk("match sucess\n");
	else
		printk("match faild\n");
#endif
	printk("dev->init_name:%s\n", dev->init_name);
	printk("dev->name:%s\n", dev_name(dev));
	printk("drv->name:%s\n", drv->name);

	return 0;
}

struct bus_type usb_bus = {
	.name = "usb-fwj",
	.match = usb_bus_match,
};

/* 单独编译的模块需要导出符号，在别的模块中才可以使用 */
EXPORT_SYMBOL(usb_bus);

static ssize_t show_bus_name(struct bus_type *bus, char *buf)
{
	//'\0' and '\n'
	return snprintf(buf, strlen(module_name)+2, "%s\n", module_name);
}

static ssize_t store_bus_name(struct bus_type *bus, const char *buf, size_t count)
{
	//'\0' and '\n'
	return snprintf(module_name, strlen(buf)+2, "%s\n", buf);
}

static BUS_ATTR(name, 0777, show_bus_name, store_bus_name);

static int __init usb_bus_init(void)
{
	int ret;

	//总线注册，必须检测返回值
	ret = bus_register(&usb_bus);
	if(ret){
		printk("usb bus register failed\n");
		return ret;
	}

	ret = bus_create_file(&usb_bus, &bus_attr_name);
	if(ret){
		printk("usb bus create file failed\n");
		return ret;
	}

	printk("usb bus register ok\n");
	return 0;
}

static void __exit usb_bus_exit(void)
{
	bus_remove_file(&usb_bus, &bus_attr_name);
	bus_unregister(&usb_bus);
	printk("usb bus unregsiter\n");
}

module_init(usb_bus_init);
module_exit(usb_bus_exit);
