#include <linux/sched.h>

struct os_tasks {
    struct task_struct *task;
    char* desc;
    int pid;
};

void do_something(struct os_tasks* tasks);
