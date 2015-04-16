/*************************************************************************
	> File Name: tuhao.c
	> Author: fwj
	> Mail: fuwenjie2011@126.com 
	> Created Time: Wed 15 Apr 2015 11:33:53 PM PDT
 ************************************************************************/
#include <linux/notifier.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/init.h>

extern int register_godness_notifier(struct notifier_block*);
extern int unregister_godness_notifier(struct notifier_block*);

static int sweet_heart_requirments(struct notifier_block *this, unsigned long event, void *ptr)
{
	switch(event)
	{
		case 0:
			printk("[GFS]: Hi Honey, the VISA is ready for you.\n");
			break;
		case 1:
			printk("[GFS]: Hi Honey, the piano is ready for you.\n");
			break;
		default:
			break;
	}

//	return NOTIFY_OK;
	return NOTIFY_STOP;
}

static struct notifier_block honey_notifier =
{
	.notifier_call = sweet_heart_requirments,
	.priority = 5,
};

static int __init honey_register(void)
{
	int err;
	printk("[Tuhao]Tuhao register cash_requirment response to Godness...");

	err = register_godness_notifier(&honey_notifier);
	if (err)
	{
		printk("Refused!\n");
		return -1;
	}
	printk("Accepted!\n");

	return err;
}

static void __exit honey_unregister(void)
{
	unregister_godness_notifier(&honey_notifier);
	printk("[Tuhao]Tuhao is giving up Godness!(Son of bitch)\n");
}

module_init(honey_register);
module_exit(honey_unregister);
