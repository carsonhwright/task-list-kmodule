#include <linux/sched.h>

struct os_tasks {
    struct task_struct *task;
    char* desc;
    int pid;
};

struct task_lifo_item {
    struct task_struct task_item;
    struct list_head head;
};

void print_linear(struct os_tasks* tasks);
void print_process_tree(void);
