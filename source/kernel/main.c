#include <i386.h>
#include <multiboot.h>
#include <kernel.h>
#include <string.h>
#include <console.h>
#include <tasks.h>
#include <mem.h>
#include <interrupt.h>
#include <paging.h>
#include <sched_exp.h>
#include <rand.h>

unsigned int timer = 0;
unsigned int seconds = 0;

cpuid_t cpuinfo;


void tmr_interrupt(int num, int err);
void task_ended_interrupt(int num, int err);

int main(unsigned int magic, multiboot_info_t *mbi) {

    /* Save CPU info in a cpuid structure */
    osdk_get_cpuid(&cpuinfo);

    /* Clears the screen */
    clearscr();


    init_default_interrupt_handlers();
    register_interrupt_handler(INT32, tmr_interrupt);
    register_interrupt_handler(INT33, kbd_interrupt);
    register_interrupt_handler(INT100, task_ended_interrupt);


    task = NONE;


    init_paging();

    osdk_timerhz(100);


    /* Unlock interrrupts */
    osdk_unlock();



    /* Forever loop */
    for (;;);
}

void panic(char *msg) {
    puts(msg);
    osdk_lock();
    for (;;);
}

int next_task = 0;

void tmr_interrupt(int num, int err) {
    if (timer == 0) {
        exp_task *t;

        t = (pexp_task) malloc(sizeof (exp_task));
        t->main = task0_main;
        t->task_id = next_task++;
        t->priority = 1;
        t->ts_cnt=0;
        t->task = (task_t*) malloc(sizeof (task_t));
        t->stack = (unsigned char*) malloc(sizeof (char) *TASK_STACK_SIZE);
        sched_exp_new_task_created(t);
    }
    timer++;
    schedular();
    if (timer % 100 == 0) {
        seconds++;
    }
    if (timer % PC_FREQ == 0) {
        exp_task *t;

        t = (pexp_task) malloc(sizeof (exp_task));
        t->main = task1_main;
        t->task_id = next_task++;
#if SCHED == SCHED_RR
        t->priority = t->initial_priority = 1;
#else
        t->priority = t->initial_priority = rand()%10+1;
#endif
        t->ts_cnt=0;
        t->task = (task_t*) malloc(sizeof (task_t));
        t->stack = (unsigned char*) malloc(sizeof (char) *TASK_STACK_SIZE);
        sched_exp_new_task_created(t);
    }
}

void schedular(void) {
#if SCHED == SCHED_RR
    sched_exp_round_robin();
#elif SCHED == SCHED_PQ
    sched_exp_priority_queue();
#elif SCHED == SCHED_DPQ
    sched_exp_dynamic_priority_queue();
#endif
}

void task_ended_interrupt(int num, int err) {
    sched_exp_task_ended();
}

