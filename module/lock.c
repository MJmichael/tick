#include <linux/list.h>
#include <linux/slab.h>
#include <linux/string.h>
#include <linux/semaphore.h>
#include <linux/errno.h>
#include <linux/list.h>
#include <linux/spinlock.h>
#include <linux/spinlock_types.h>

#include <linux/module.h>

struct object{
	int id;
	char name[32];
	int popularity;

	struct list_head list; //list
};

//lock 
//static DEFINE_SEMAPHORE(cache_lock);
static DEFINE_SPINLOCK(cache_lock);
static LIST_HEAD(cache);
static unsigned int cache_num = 0;
#define MAX_CACHE_SIZE 10

//must hold cache_lock
static struct object *__cache_find(int id)
{
	struct object *pos;

	list_for_each_entry(pos, &cache, list)
	{
		if(pos->id == id){
			printk("id:%d, name:%s\n", pos->id, pos->name);
			pos->popularity++;

			return pos;
		}
	}

	return NULL;
}

//must hold cache_lock
static void __cache_del(struct object *obj)
{
	BUG_ON(!obj);//obj NULL
	list_del(&obj->list);
	kfree(obj);

	cache_num--;
}

static void __cache_add(struct object *obj)
{
	BUG_ON(!obj);//obj NULL
	list_add(&cache, &obj->list);

	if(++cache_num > MAX_CACHE_SIZE)
	{
		struct object *pos, *out=NULL;
		list_for_each_entry(pos, &cache, list)
		{
			if(!out||out->popularity < pos->popularity)
				out=pos;
		}
		
		__cache_del(out);
	}
}

int cache_add(int id, const char* name)
{
	struct object *obj;
	unsigned long flags;

	if((obj = kmalloc(sizeof(struct object), GFP_KERNEL)) == NULL)
		return -ENOMEM;

	obj->id = id;
	strlcpy(obj->name, name, sizeof(struct object));
	obj->popularity = 0;

//semaphore --> spin_lock
//	down(&cache_lock);
	spin_lock_irqsave(&cache_lock, flags);
	__cache_add(obj);
	spin_unlock_irqrestore(&cache_lock, flags);
//	up(&cache_lock);

	return 0;
}

void cache_delete(int id)
{
	unsigned long flags;

//semaphore --> spin_lock
//	down(&cache_lock);
	spin_lock_irqsave(&cache_lock, flags);
	__cache_del(__cache_find(id));
	spin_unlock_irqrestore(&cache_lock, flags);
//	up(&cache_lock);
}

int cache_find(int id, char *name)
{
	struct object *obj;
	int ret = -ENOENT;
	unsigned long flags;

//	down(&cache_lock);
	spin_lock_irqsave(&cache_lock, flags);
	obj = __cache_find(id);

	if(obj){
		ret = 0;
		strcpy(name, obj->name);
	}
	spin_unlock_irqrestore(&cache_lock, flags);
//	up(&cache_lock);

	return ret;
}

static int lock_init(void)
{
	printk("lock init");
	return 0;
}

static void lock_exit(void)
{
	printk("lock exit");
}


MODULE_LICENSE("Dual GPL/BSD");
module_init(lock_init);
module_exit(lock_exit);
