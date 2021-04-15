/* 
 * File:   sched_exp.h
 * Author: kazim
 *
 * Created on November 18, 2010, 7:55 PM
 */

#ifndef SCHED_EXP_H
#define	SCHED_EXP_H

#include <i386.h>
#include <common.h>

typedef void(*task_main)();

typedef struct _exp_task{
    task_t *task;
    int priority;
    int initial_priority;
    int ts_cnt;
    int task_id;
    task_main main;
    unsigned char * stack;
}exp_task,*pexp_task;


void sched_exp_round_robin();
void sched_exp_priority_queue();
void sched_exp_dynamic_priority_queue();
void sched_exp_new_task_created(exp_task * new_task);
void sched_exp_task_ended();

extern pexp_task current_task;

#endif	/* SCHED_EXP_H */

