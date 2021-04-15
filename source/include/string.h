#ifndef _STRING_H
#define _STRING_H

#define HEX 16
#define DEC 10
#define OCT 8
#define BIN 2

void itoa(int, unsigned int, char *);
void uitoa(unsigned int, unsigned int, char *);
char hexdigit(int);
int abs(int);
void printf(char *, ...);
void puts(char *);

#endif
