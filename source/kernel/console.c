#include <console.h>
#include <i386.h>
#include <string.h>

//FIXME
#include <tasks.h>

unsigned char *video = (unsigned char *) VIDEO;
unsigned int keybstat=0;

pos_t pos;

/* The US Keyboard Map */
char kbdus[128] ={
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
  '9', '0', '-', '=', '\b',	/* Backspace */
  '\t',			/* Tab */
  'q', 'w', 'e', 'r',	/* 19 */
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',	/* Enter key */
    0,			/* 29   - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */
 '\'', '`',   0,		/* Left shift */
 '\\', 'z', 'x', 'c', 'v', 'b', 'n',			/* 49 */
  'm', ',', '.', '/',   0,				/* Right shift */
  '*',
    0,	/* Alt */
  ' ',	/* Space bar */
    0,	/* Caps lock */
    0,	/* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,	/* < ... F10 */
    0,	/* 69 - Num lock*/
    0,	/* Scroll Lock */
    0,	/* Home key */
    0,	/* Up Arrow */
    0,	/* Page Up */
  '-',
    0,	/* Left Arrow */
    0,
    0,	/* Right Arrow */
  '+',
    0,	/* 79 - End key*/
    0,	/* Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0,   0,   0,
    0,	/* F11 Key */
    0,	/* F12 Key */
    0,	/* All other keys are undefined */
};	


void putchar(char c)
{
	unsigned int offset;
	switch(c)
	{
		case '\n':
			pos.x=0;
  			pos.y++;
			return;
		case '\t':
			pos.x+=6;
			return;
	}

  	if(pos.x==(COLUMNS-1)){
		pos.x=0;
		pos.y++;
	}
	if(pos.y==(LINES-1)){
		pos.x=0;
		pos.y=0;
	}
	offset = ((pos.y * COLUMNS + pos.x)*2 );
	video=(unsigned char *)(0xb8000+offset);
     	*video=c;
	video++;
	*video=COLOR;
	video++;
	pos.x++;
}

void clearscr(void)
{
	int i;
	pos.x=0;
	pos.y=0;
	video=(unsigned char *)(0xb8000);
	for(i=0 ; i < (COLUMNS * LINES *2) ; i++)
	{
		video[i]=' ';
		i++;
		video[i]=COLOR;
	}
	pos.x=0;
	pos.y=0;
}

int keyb_busy()
{
	if(osdk_in(0x64) & 0x2)
		return 1;
	else return 0;
}

void keyb_led(byte_t stat)
{
	while(keyb_busy());
	osdk_out(0x60, 0xed);
	while(keyb_busy());
	osdk_out(0x60, stat);
}


void kbd_interrupt(int num, int err) {
    int key;
    key = osdk_getch();
    switch (key) {
        case 0x45:
            clearscr();
            if ((keybstat & NUM_LOCK) == 0) {
                printf("Turning ON Num lock\n");
                keybstat = keybstat | NUM_LOCK;
                keyb_led(keybstat);
            } else {
                printf("Turning OFF Num lock\n");
                keybstat = keybstat & !NUM_LOCK;
                keyb_led(keybstat);
            }
            break;
        case 0x46:
            clearscr();
            if ((keybstat & SCROLL_LOCK) == 0) {
                printf("Turning ON Scroll lock\n");
                keybstat = keybstat | SCROLL_LOCK;
                keyb_led(keybstat);
            } else {
                printf("Turning OFF Scroll lock\n");
                keybstat = keybstat & !SCROLL_LOCK;
                keyb_led(keybstat);
            }
            break;
        case 0x3a:
            clearscr();
            if ((keybstat & CAPS_LOCK) == 0) {
                printf("Turning ON Caps lock\n");
                keybstat = keybstat | CAPS_LOCK;
                keyb_led(keybstat);
            } else {
                printf("Turning OFF Caps lock\n");
                keybstat = keybstat & !CAPS_LOCK;
                keyb_led(keybstat);
            }
            break;
    }
    switch (kbdus[key]) {
        case 'h':
            clearscr();
            printf("Press t to display current task information\n");
            break;
        case 't':
            clearscr();
            print_task();
            break;
    }
}
