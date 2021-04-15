Implement the methods defined inside “kernel/sched_exp.c”. In that file there are
five methods with given signatures:
void sched_exp_round_robin();
void sched_exp_priority_queue();
void sched_exp_dynamic_priority_queue();
void sched_exp_new_task_created(exp_task * new_task);
void sched_exp_task_ended();
 Inside the method “sched_exp_round_robin” you should implement the round robin
scheduling algorithm. It is a preemptive algorithm.
 Inside the method “sched_exp_priority_queue” you should implement the priority
queue scheduling algorithm. The priority of each task is assigned randomly when the
task is created. The priority of each task is constant for its lifetime. This algorithm
should be implemented as a preemptive algorithm (A new task might interrupt a task
running on the CPU, if the new task has a higher priority).
 Inside the method “sched_exp_dynamic_priority_queue” you should implement the
priority queue scheduling algorithm. When a task created, an initial priority will be
assigned randomly. Priority of each process on the waiting queue will be increased by
one after each task switch. After a process is scheduled to CPU, it will be assigned to
its initial priority. It is a preemptive algorithm.
 Inside the method “sched_exp_new_task_created” you should insert the task named
new_task to the process queue.
 Inside  the  method  “sched_exp_task_ended”  you  should  remove  the  task  named
current_task from the process queue.
For switching the current task with new one inside the scheduling implementations you should
assign  the  new  task  pointer  to  the  variable  “current_task”.  It  is  defined  at  top  of
“kernel/sched_exp.c” with signature “exp_task * current_task;”.
You should only modify the file  “sched_exp.c” and  “common.h” from the base files. You
can add your custom header files into include directory and C files into kernel directory. If you
add new C (filename.c) file, you should append  “filename.o”to “KERNELOUT”label inside
the Makefile at kernel directory.
In  “common.h” there are two definition:  “SCHED” and  “PC_FREQ”. You can control the
scheduling algorithm and task creation frequency with these variables. Also you can check
the  current  scheduling  algorithm  at  compile  time  like  the  method  “schedular” inside
“main.c”.