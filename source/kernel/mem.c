#include <mem.h>
#include <string.h>

#include "i386.h"

unsigned char memory[0x3200000];

unsigned char mprintf_memory[0xA00000] = {0};

unsigned int mem_start = (unsigned int)&memory[0];
unsigned int mem_next = -1;

unsigned char * mprintf_idx = &mprintf_memory[0];
unsigned char * mprintf_end = &mprintf_memory[0x9FFFFF];

void * malloc(unsigned int size){
    unsigned int res;
    if(mem_next==-1){
        mem_next=mem_start;
    }
    res=mem_next;
    mem_next+=size;
    return (void *)res;
}


void bzero(void *b, unsigned int len)
{
	int i;
	unsigned char *mem = (unsigned char *)b;
	for(i=0 ; i<len ; i++)
		*mem++ = 0x0;
}

void memset(void * address,unsigned char value,unsigned int size){
    unsigned char * tmp=(unsigned char*)address;
    unsigned int i;
    for(i=0;i<size;i++){
        tmp[i]=value;
    }
}


void *memcpy(void * dest, void * src, unsigned int len){
    unsigned int i;
    unsigned char *tmp1=(unsigned char*)dest,*tmp2=(unsigned char*)src;

    for(i=0;i<len;i++){
        tmp1[i]=tmp2[i];
    }
    return dest;
}


void mputchar(char c)
{
    *mprintf_idx=c;
    mprintf_idx++;
    if(mprintf_idx==mprintf_end){
        osdk_lock();
        printf("Ended\n");
        for(;;);
    }
}

void mputs(char *s)
{
	while(*s)
		mputchar(*s++);
}


void mprintf(char *fmt, ...)
{
	__builtin_va_list va;
	__builtin_va_start(va, fmt);

	char buffer[256];
	char *str;

	while(*fmt){
		switch(*fmt)
		{
			case '%':
				fmt++;
				switch(*fmt)
				{
					case 'd':
						itoa(__builtin_va_arg(va ,int), DEC, buffer);
						mputs(buffer);
						break;
					case 'x':
						uitoa(__builtin_va_arg(va ,unsigned int), HEX, buffer);
						mputs(buffer);
						break;
					case 's':
						str=(char *)__builtin_va_arg(va, int);
						mputs(str);
						break;
				}
				break;
			default:
				mputchar(*fmt);
				break;
		}
		fmt++;
	}
	__builtin_va_end(va);
}
