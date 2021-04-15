#ifndef _TASKS_H
#define _TASKS_H

#include <sched_exp.h>


#define TASK_STACK_SIZE 2000

#define NONE -1

extern int task;

void print_task();

void task0_main();

void task1_main(void);
void task2_main(void);
void task3_main(void);
void task4_main(void);

void osdk_task_create_wrapper(pexp_task new_task);
void osdk_task_switch_wrapper(pexp_task old_task, pexp_task new_task);
void osdk_task_ended_switch_wrapper(pexp_task old_task, pexp_task new_task);

#endif
