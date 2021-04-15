/* 
 * File:   interrupt.h
 * Author: kazim
 *
 * Created on November 11, 2010, 9:22 AM
 */

#ifndef INTERRUPT_H
#define	INTERRUPT_H

#include <common.h>
#include <i386.h>

typedef void (* interrupt_handler)(int num,int err);

void interrupt(int num, int err);

void register_interrupt_handler(int num,interrupt_handler handler);

void init_default_interrupt_handlers();

#endif	/* INTERRUPT_H */

