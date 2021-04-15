#include <i386.h>
#include <tasks.h>
#include <string.h>
#include <mem.h>
#include <console.h>
#include <sched_exp.h>

int task;
extern pexp_task current_task;

void task0_main() {
    for (;;);
}

void osdk_task_create_wrapper(pexp_task new_task) {
    osdk_task_create(new_task->task, new_task->main, new_task->stack);
    mprintf("task created: %d\n", new_task->task_id);
}

void osdk_task_switch_wrapper(pexp_task old_task, pexp_task new_task) {
    osdk_task_switch(new_task->task);
    mprintf("old task: %d (%d)-> new task: %d\n", old_task->task_id,old_task->ts_cnt,new_task->task_id);
}


void osdk_task_ended_switch_wrapper(pexp_task old_task, pexp_task new_task){
    mprintf("task ended: %d\n", current_task->task_id);
    osdk_task_switch(new_task->task);
    mprintf("old task: %d (%d)-> new task: %d\n", old_task->task_id,old_task->ts_cnt,new_task->task_id);
}

void task1_main() {
    int i, j;
    unsigned long k=0;
    printf("Task Started.\n");

    for (i = 0; i < 100000; i++) {
        for (j = 0; j < 5000; j++){
		k+=i*2+j*3%123456;
	}
    }
    printf("%d\n",k);
    asm("int $100");
}

void print_task() {
    task_t *t = current_task->task;
    printf("Task ID : %d\n", current_task->task_id);
    printf("Task Priority : %d\n", current_task->priority);
    printf("ss3= 0x%x\n", t->regs.ss3);
    printf("esp3= 0x%x\n", t->regs.esp3);
    printf("eflags= 0x%x\n", t->regs.eflags);
    printf("cs= 0x%x\n", t->regs.cs);
    printf("eip= 0x%x\n", t->regs.eip);
    printf("eax= 0x%x\n", t->regs.eax);
    printf("ecx= 0x%x\n", t->regs.ecx);
    printf("edx= 0x%x\n", t->regs.edx);
    printf("ebx= 0x%x\n", t->regs.ebx);
    printf("esp= 0x%x\n", t->regs.esp);
    printf("ebp= 0x%x\n", t->regs.ebp);
    printf("esi= 0x%x\n", t->regs.esi);
    printf("edi= 0x%x\n", t->regs.edi);
    printf("gs= 0x%x\n", t->regs.gs);
    printf("fs= 0x%x\n", t->regs.fs);
    printf("es= 0x%x\n", t->regs.es);
    printf("ds= 0x%x\n", t->regs.ds);
    printf("error= 0x%x\n", t->regs.error);
    printf("interrupt= 0x%x\n", t->regs.interrupt);
}

