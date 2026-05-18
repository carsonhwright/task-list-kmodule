#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/list.h>
#include "include/utils.h"

// am I acutally going to use this?
// static LIST_HEAD(task_list);

/* This function is called when the module is loaded
*/


// void traverse_list(struct something* something) {
// 	list_for_each_entry_safe(ptr, n, &birthday_list, list) {
// 		// struct birthday *obj = list_entry(ptr, struct birthday, ptr->list);
// 		printk(KERN_INFO "Day: %d\n", ptr->day);
// 		printk(KERN_INFO "Month: %d\n", ptr->month);
// 		printk(KERN_INFO "Year: %d\n", ptr->year);
// 		list_del(&ptr->list);
// 		kfree(ptr);
// 	}
// 	return;
// }

static int __init simple_init(void)
{
	printk(KERN_INFO "Loading Task List Module\n");
	struct os_tasks tasks;
	print_linear(&tasks);
	// struct task_struct *tasks;
	print_process_tree();
	// struct birthday *proto_person = make_person_proto();
	// traverse_list(proto_person);
	return 0;
}

/* This function is called when the module is removed.
*/
static void __exit simple_exit(void) {
	printk(KERN_INFO "Removing Module\n");
}


module_init(simple_init);
module_exit(simple_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("CHW");


