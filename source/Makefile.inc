CC = gcc -m32
AS = as -32
LD = ld -melf_i386
AR = ar
RANLIB = ranlib
CFLAGS = -Wall -O -nostdinc -nostdlib -fstrength-reduce \
	 -fomit-frame-pointer -finline-functions -fno-builtin \
	 -ffreestanding -nostartfiles -nodefaultlibs \
	 -I../include
STUDENTNO = 20673618
RTIME = 30
