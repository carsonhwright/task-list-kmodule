#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>
#include <linux/list.h>

#include "../include/utils.h"

struct task_struct *task;

void do_something(struct os_tasks* os_tasks) {
    rcu_read_lock();
    for_each_process(task) {
        // I don't think this is right
        os_tasks->task = task;
    }
    rcu_read_unlock();
}