#ifndef _KERNEL_H
#define _KERNEL_H

#include <common.h>

extern unsigned int timer;
extern unsigned int seconds;

int main(unsigned int, multiboot_info_t *);

void schedular(void);
#endif
