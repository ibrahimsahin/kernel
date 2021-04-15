include ../Makefile.inc

KERNELOUT = console.o  main.o interrupt.o \
		mem.o  string.o  tasks.o \
		paging.o sched_exp.o rand.o

LIBKERNEL = kernel.a

all: $(LIBKERNEL)

$(LIBKERNEL): force_look $(KERNELOUT)
	$(AR) $(ARFLAGS) $(LIBKERNEL) $(KERNELOUT)
	$(RANLIB) $(LIBKERNEL)

*.o: $*.c
	$(CC) $(CFLAGS) -c -o $*.o $*.c

clean: 
	rm -f $(KERNELOUT) $(LIBKERNEL)

force_look:
