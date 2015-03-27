//hello.c

//author:MJmichael

#include <linux/init.h>
#include <linux/module.h>
#include <linux/slab.h>

MODULE_LICENSE("Dual BSD/GPL");   //内核license

static int hello_init(void) 
{
	char* pos;
	
	printk(KERN_ALERT "Hello, world\n");
	
	pos = (char*)kmalloc(64*sizeof(char), GFP_KERNEL);
	strcpy(pos, "hello");
	return 0;
}

static void hello_exit(void)
{
	printk(KERN_ALERT "Goodbye, cruel world\n");
}

module_init(hello_init);
module_exit(hello_exit);
