#ifndef _CONSOLE_H
#define _CONSOLE_H

#include <i386.h>

#define VIDEO	0xb8000
#define COLUMNS	80
#define LINES	25
#define COLOR 9

#define CAPS_LOCK 0x4
#define NUM_LOCK 0x2
#define SCROLL_LOCK 0x1

typedef struct pos_t
{
	unsigned int x;
 	unsigned int y;
}pos_t;

extern pos_t pos;
extern char kbdus[128];
extern unsigned int keybstat;

void clearscr(void);
void putchar(char);
int keyb_busy(void);
void keyb_led(byte_t);
void kbd_interrupt(int num, int err);

#endif
