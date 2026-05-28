#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>
#include <linux/list.h>
#include <linux/slab.h>

#include "../include/utils.h"

#define NOMINAL 0

struct task_struct *task;
struct task_struct *child_reader, *deep_reader;
struct task_struct *parent_reader;
// struct list_head *child_list;
struct list_head *parent_list;
static LIST_HEAD(lifo_queue_head);

/*Push a task_struct to the front of the lifo queue*/
static int push_task(struct task_struct task) {
    struct task_lifo_item *new_item;
    new_item = kmalloc(sizeof(new_item), GFP_KERNEL);
    if (!new_item) {
        // OS No Memory Error
        return -ENOMEM;
    }
    new_item->task_item = task;
    list_add(&new_item->head, lifo_queue_head);
    printk("Added new task item %s\tpid: %d\n.", task->comm, task->pid);

    return NOMINAL;

}

/*pop the most recent entry from the task list
*/
static int pop_task(void) {
    struct task_lifo_item *lifo_item;
    if (list_empty(&lifo_queue_head)) {
        printk("LiFo queue empty\n");
    } else {
        // I realize now that this isn't right, I still need siblings from this item, so return type probably needs to be the task itself
        // TODO this line is failing macro expansion at compile
        lifo_item = list_first_entry(&lifo_queue_head, struct task_lifo_item, task_item);
        list_del(&lifo_item->head);
        printk("Task: %s\t--\t%d", lifo_item->task_item.comm, lifo_item->task_item.pid);
        kfree(lifo_item);
    }
    return NOMINAL;
}

void print_linear(struct os_tasks* os_tasks) {
    rcu_read_lock();
    for_each_process(task) {
        // I don't think this is right
        // os_tasks->task = task;
        
        printk("task-name: %s\n\tpid: %d\n\tstatus: %d", task->comm, task->pid, task->__state);
        // printk("\t-- parent: %d", task->parent);
        // what do I do with the children?
        
        }
        // list_for_each(parent_list &init_task.parent) {
        //     parent_reader = list_entry(list, struct task_scrutct, sibling);
        //     // printk()
        //     task
        // }
    
    rcu_read_unlock();
}

void print_process_tree() {
    int count = 0;
    int depth_count = 0;
    struct list_head *child_list, *deep_list;
    // struct task_struct deep_entry;
    rcu_read_lock();
    list_for_each(child_list, &init_task.children) {
        child_reader = list_entry(child_list, struct task_struct, sibling);
        
        printk("child: %s -- pid: %d -- COUNT-depth : %d-%d ", child_reader->comm, child_reader->pid, count, depth_count);
        while (1) {
            /** 
            TODO this is untested, 
            
            NOTE recursion in "kernelspace" is a nono, the stack space
            is like 4-8KB, so it needs to be really simple. Recursion keeps crashing the kernel 
            when I do it.
            
            Below demonstrates that there is a level
            that we're catching onto in this process tree, just need a way to generate it
            
            duh, need to make a LIFO, we did it in the other project I think, just need to use the list_head thing
            **/
            list_for_each(deep_list, &child_reader->children){

                deep_reader = list_entry(deep_list, struct task_struct, sibling);
                printk("deep: %s -- pid: %d -- COUNT-depth : %d-%d ", deep_reader->comm, deep_reader->pid, count, depth_count++);
            }
            count ++;
            depth_count = 0;
            
        }
        
        // for_each_process(child_reader){
        //     list_for_each(deep_list, &child_reader->children){
        //         deep_entry = list_entry(deep_list, struct task_struct, sibling);
        //         printk("child?: %s -- pid: %d -- COUNT-depth : %d-%d ", deep_entry.comm, deep_entry.pid, count, depth_count++);
        //     }
        // }
        
    }
    rcu_read_unlock();
}
