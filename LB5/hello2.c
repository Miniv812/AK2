// SPDX-License-Identifier: GPL-2.0
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/moduleparam.h>
#include <linux/errno.h>
#include "hello1.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Vlad Chmulenko");
MODULE_DESCRIPTION("Module hello2 using print_hello from hello1");
MODULE_VERSION("0.1");

static uint count = 1;
module_param(count, uint, 0644);
MODULE_PARM_DESC(count, "Count of 'Hello, world!' prints");

static int __init hello2_init(void)
{
	uint i;

	if (count == 0 || (count >= 5 && count <= 10)) {
		pr_warn("Warning: count is %u\n", count);
	} else if (count > 10) {
		pr_err("Error: count %u is greater than 10\n", count);
		return -EINVAL;
	}

	for (i = 0; i < count; i++)
		print_hello();

	return 0;
}

static void __exit hello2_exit(void)
{
	pr_info("hello2 module unloaded\n");
}

module_init(hello2_init);
module_exit(hello2_exit);
