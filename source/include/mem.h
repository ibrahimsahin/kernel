#ifndef _MEM_H
#define _MEM_H

void bzero(void *, unsigned int);

void memset(void * address,unsigned char value,unsigned int size);
void *memcpy(void * dest, void * src, unsigned int len);
void * malloc(unsigned int size);
void mprintf(char *fmt, ...);
#endif
