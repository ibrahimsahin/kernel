include ../Makefile.inc

LIBOUT = cpuid.o  debug.o  drivers.o  \
	 gdt.o  i386.o  idt.o  interrupt.o  isr.o  \
	 paging.o  pic.o  pit.o  ports.o  string.o  \
         temp.o  tss.o  utility.o
TLIBOUT = i386.o
LIBOS= libos.a

all: $(LIBOS)

$(LIBOS): force_look $(TLIBOUT)
	$(AR) $(ARFLAGS) $(LIBOS) $(TLIBOUT)
	$(RANLIB) $(LIBOS)

*.o: $*.s
	$(AS) -32 -c -o $*.o $*.s

clean:
	rm -f $(LIBOUT) $(LIBOS);

force_look:
	true
