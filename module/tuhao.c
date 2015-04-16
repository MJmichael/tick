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

static int baby_need_money(struct notifier_block *this, unsigned long event, void *ptr)
{
	if(event != 0)  //不是金钱需求关我鸟事
	{
		return NOTIFY_DONE; //Don't care
	}
	printk("[Tuhao]:Hi Baby, give you 10000$.\n");
	return NOTIFY_OK;
}

static struct notifier_block cash_notifier =
{
	.notifier_call = baby_need_money,
	.priority = 2,
};

static int __init tuhao_register(void)
{
	int err;
	printk("[Tuhao]Tuhao register cash_requirment response to Godness...");

	err = register_godness_notifier(&cash_notifier);
	if (err)
	{
		printk("Refused!\n");
		return -1;
	}
	printk("Accepted!\n");

	return err;
}

static void __exit tuhao_unregister(void)
{
	unregister_godness_notifier(&cash_notifier);
	printk("[Tuhao]Tuhao is giving up Godness!(Son of bitch)\n");
}

module_init(tuhao_register);
module_exit(tuhao_unregister);
