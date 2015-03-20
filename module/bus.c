/*************************************************************************
	> File Name: bus.c
	> Author: fwj
	> Mail: fuwenjie2011@126.com 
	> Created Time: 2015年03月20日 星期五 10时24分57秒
 ************************************************************************/
#include <linux/module.h>
#include <linux/init.h>

#include <linux/device.h>

MODULE_LICENSE("Dual BSD/GPL");   //内核license

struct bus_type usb_bus = {
	.name = "usb-virual",
};

static int __init usb_bus_init(void)
{
	int ret;

	//总线注册，必须检测返回值
	ret = bus_register(&usb_bus);
	if(ret){
		printk("usb bus register failed\n");
		return ret;
	}

	printk("usb bus register ok\n");
	return 0;
}

static void __exit usb_bus_exit(void)
{
	bus_unregister(&usb_bus);
	printk("usb bus unregsiter\n");
}

module_init(usb_bus_init);
module_exit(usb_bus_exit);
