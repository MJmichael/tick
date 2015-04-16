/*************************************************************************
	> File Name: godness.c
	> Author: fwj
	> Mail: fuwenjie2011@126.com 
	> Created Time: Wed 15 Apr 2015 11:29:05 PM PDT
 ************************************************************************/
#include <asm/uaccess.h>
#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/notifier.h>
#include <linux/init.h>
#include <linux/types.h>
#include <linux/module.h>
#include <linux/kthread.h>
MODULE_LICENSE("GPL");

#define PHY_REQ 0 //物质需求
#define SPR_REQ 1 //精神需求
#define REQ_MAX SPR_REQ+1

extern void get_random_bytes(void* buf,int nbytes);
static struct task_struct *requirments_thread = NULL;
/*
 * * 女神所有的需求都会列在她的需求链里。这里我们定义了一个原始通知链，暂时没考虑锁的问题。
 * * step 1: define requirment_chain;
 * */
static RAW_NOTIFIER_HEAD(requirment_chain);

/*
 * * 如果谁想追求本女王，就来献殷勤吧
 * */
int register_godness_notifier(struct notifier_block *nb)
{
	return raw_notifier_chain_register(&requirment_chain, nb);
}
EXPORT_SYMBOL(register_godness_notifier);

/*
 * * 伺候不起的，赶紧Get out as soon as 
 * */
int unregister_godness_notifier(struct notifier_block *nb)
{
	return raw_notifier_chain_unregister(&requirment_chain, nb);
}
EXPORT_SYMBOL(unregister_godness_notifier);

/*
 * * 本女王开始提需求了，看看谁能才是真心的。
 * */
int call_godness_notifier_chain(unsigned long val, void *v)
{
	return raw_notifier_call_chain(&requirment_chain, val, v);
}
EXPORT_SYMBOL(call_godness_notifier_chain);

static int make_requirment_thread(void *data)
{
	int i = 10;
	struct completion cmpl;
	unsigned int requirment_type = 0;
	printk("[Godness]requirements thread starting...\n");
//	while((i--) > 0){
	while(1){
		init_completion(&cmpl);
		wait_for_completion_timeout(&cmpl, 3 * HZ);
		get_random_bytes(&requirment_type, sizeof(requirment_type));  //生成一个内核随机数
		requirment_type %= REQ_MAX;  //需求类型之可能是0或者1
		printk("[Godness]:requirment type: %d \n",requirment_type);
		call_godness_notifier_chain(requirment_type, NULL);
	}
	printk("[Godness]requirements thread ended!\n");
	return 0;
}

static int __init godness_init_notifier(void)
{
	printk("[Attention]The Godness coming into the world!\n");
	requirments_thread = kthread_run(make_requirment_thread, NULL, "Godness_requirments_thread");
	return 0;
}

static void __exit godness_exit_notifier(void)
{
	kthread_stop(requirments_thread);
	printk("[Attention]The Godness leaving out!\n");
}
module_init(godness_init_notifier);
module_exit(godness_exit_notifier);
