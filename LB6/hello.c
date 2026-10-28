// SPDX-License-Identifier: GPL-2.0
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/moduleparam.h>
#include <linux/list.h>
#include <linux/slab.h>
#include <linux/ktime.h>
#include <linux/errno.h>
#include <linux/bug.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Vlad Chmulenko");
MODULE_DESCRIPTION("Hello World! Module with BUG_ON and memory error injection");
MODULE_VERSION("0.1");

static uint count = 1;
module_param(count, uint, 0644);
MODULE_PARM_DESC(count, "Count of 'Hello, world!' prints");

struct my_list_node {
	struct list_head list;
	ktime_t event_time;
};

static LIST_HEAD(my_list);

static void __exit hello_exit(void)
{
	struct my_list_node *ptr, *tmp;

	list_for_each_entry_safe(ptr, tmp, &my_list, list) {
		pr_info("Event time: %lld ns\n", ktime_to_ns(ptr->event_time));
		list_del(&ptr->list);
		kfree(ptr);
	}
}

static int __init hello_init(void)
{
	struct my_list_node *ptr;
	uint i;

	BUG_ON(count > 10);

	if (count == 0 || (count >= 5 && count <= 10))
		pr_warn("Warning: count is %u\n", count);

	for (i = 0; i < count; i++) {
		if (i == 4) {
			pr_err("Simulating kmalloc failure on 5th element!\n");
			ptr = NULL;
		} else {
			ptr = kmalloc(sizeof(*ptr), GFP_KERNEL);
		}

		if (!ptr) {
			hello_exit();
			return -ENOMEM;
		}

		ptr->event_time = ktime_get();
		list_add_tail(&ptr->list, &my_list);

		pr_info("Hello, world!\n");
	}

	return 0;
}

module_init(hello_init);
module_exit(hello_exit);
