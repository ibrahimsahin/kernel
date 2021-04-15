#ifndef COMMON_H
#define	COMMON_H

#define NULL 0

/* SCHEDULE TYPES*/
#define SCHED_RR 0
#define SCHED_PQ 1
#define SCHED_DPQ 2

/*CURRENT SCHEDULE TYPE
 you will modify the SCHED variable to test each algorithm*/
#define SCHED SCHED_RR

/*A new task created at each PC_FREQ timer click*/
#define PC_FREQ 255


void panic(char *);



#endif	/* COMMON_H */

