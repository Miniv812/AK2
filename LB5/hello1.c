// SPDX-License-Identifier: GPL-2.0
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/slab.h>
#include <linux/ktime.h>
#include "hello1.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Vlad Chmulenko");
MODULE_DESCRIPTION("Module hello1 exporting print_hello");
MODULE_VERSION("0.1");

struct my_list_node {
	struct list_head list;
	ktime_t time_before;
	ktime_t time_after;
};

static LIST_HEAD(my_list);

void print_hello(void)
{
	struct my_list_node *ptr;

	ptr = kmalloc(sizeof(*ptr), GFP_KERNEL);
	if (!ptr)
		return;

	ptr->time_before = ktime_get();
	pr_info("Hello, world!\n");
	ptr->time_after = ktime_get();

	list_add_tail(&ptr->list, &my_list);
}
EXPORT_SYMBOL(print_hello);

static int __init hello1_init(void)
{
	pr_info("hello1 module loaded\n");
	return 0;
}

static void __exit hello1_exit(void)
{
	struct my_list_node *ptr, *tmp;

	list_for_each_entry_safe(ptr, tmp, &my_list, list) {
		s64 duration = ktime_to_ns(ktime_sub(ptr->time_after,
						    ptr->time_before));

		pr_info("Print duration: %lld ns\n", duration);
		list_del(&ptr->list);
		kfree(ptr);
	}
	pr_info("hello1 module unloaded\n");
}

module_init(hello1_init);
module_exit(hello1_exit);
