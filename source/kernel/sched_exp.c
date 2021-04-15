#include <sched_exp.h>
#include <tasks.h>
#include <mem.h>
#include <common.h>

pexp_task current_task;

struct list {
    exp_task  * element;
    struct list *next;
    struct list *prev;
};

struct list *first=NULL, *last=NULL;

struct list* malloc_(exp_task *new_task)
{
	struct list *temp= (struct list *)malloc(sizeof(struct list));
	temp->element = new_task;
	temp->next=NULL;
	return temp;
}

void add_list(exp_task *new_task)
{
    struct list * temp=malloc_(new_task);
    if(first == NULL)
    {
        first = temp;
  	temp->prev = NULL;
    }
    else
    {
        last->next = temp;
        temp->prev = last;
    }
    last = temp;
    temp->next = NULL;
}

void list_pr(exp_task *new_task)
{
    struct list * hold=malloc_(new_task);
    if(first == NULL)
    {
        first = hold;
        hold->prev = NULL;
        last = hold;
        hold->next = NULL;
    }
    else
    {//there are elements in the queue more than one
        if((hold->element->priority > first->element->priority))
        {//new_task's priority bigger than priority of the all tasks
            hold->next=first;
            first->prev=hold;
            first=hold;
        }

        else if((hold->element->priority == first->element->priority) && first->element->task_id!=0)
        {
            first->next->prev=NULL;
            first->next->prev=hold;
            hold->next=first->next;
            first->next=NULL;
            first->next=hold;
            hold->prev=first;
        }

        else
        {
            struct list *temp;
            temp=first->next;
            while(1)
            {
                if(hold->element->priority > temp->element->priority)
                {//location found
                    temp->prev->next=NULL;
                    temp->prev->next=hold;
                    hold->next=temp;
                    hold->prev=temp->prev;
                    temp->prev=NULL;
                    temp->prev=hold;
                    break;
                 }
                 if(temp->next==NULL)
                 {
                    add_list(new_task);
                    break;
                 }
                 temp=temp->next;
            }
         }
     }
}


void list_set()
{
	if(first==NULL)
		return;

	else if(first->next != NULL)
        {
            struct list *temp;
            last->next=first;
            temp=first->next;
            first->next=NULL;
            temp->prev=NULL;
            first->prev=last;
            first=temp;
            last=last->next;
	}
}


void drop_element()
{
    if(first==NULL)
	return;

    else if(first->next != NULL)
    {
	struct list *temp;
	temp=first->next;
	first->next=NULL;
        temp->prev=NULL;
	first=temp;
    }
    else if(first->next == NULL)
    {
	first=NULL;
        last=NULL;
    }
}


void priority_manage()
{
    struct list *temp;
    temp=first;
    while(1)
    {
        if(temp->element->priority != 10 && temp->element->task_id != 0)
            temp->element->priority++;

        temp=temp->next;
        if(temp==NULL)
            break;
    }
    if( first->element->priority == 10 && first->next->element->priority == 10 )
    {
        first->element->priority=first->element->initial_priority;
        temp=first;
        drop_element();
        list_pr( temp->element );
    }
}

void sched_exp_round_robin()
{
    current_task=first->element;
    current_task->ts_cnt++;
    if(first->next != NULL)
    {
        osdk_task_switch_wrapper( first->element , first->next->element );
        list_set();
    }
    else if(first->next == NULL)
        osdk_task_switch_wrapper( first->element , first->element );

    current_task=first->element;

}

void sched_exp_priority_queue()
{
    current_task->ts_cnt++;
    if(first->next == NULL)
        osdk_task_switch_wrapper( first->element , first->element );
    else if(first->next != NULL)
        osdk_task_switch_wrapper( current_task , first->element );

    current_task=first->element;
}

void sched_exp_dynamic_priority_queue()
{
    current_task->ts_cnt++;
    if(first->next == NULL)
        osdk_task_switch_wrapper( first->element , first->element );
    else if(first->next != NULL)
    {
        osdk_task_switch_wrapper( current_task , first->element );
        priority_manage();
    }
    current_task=first->element;
}


void sched_exp_new_task_created(exp_task * new_task)
{
    osdk_task_create_wrapper( new_task );
    new_task->priority=new_task->initial_priority;
    if(SCHED ==1 || SCHED==2)
        list_pr( new_task );
    else if(SCHED==0)
        add_list(new_task);
}

void sched_exp_task_ended()
{

    if(first->next != NULL)
	osdk_task_ended_switch_wrapper( first->element , first->next->element );

    else if(first->next == NULL)
	osdk_task_ended_switch_wrapper( first->element , first->element );

    current_task=first->element;
    drop_element();
}
