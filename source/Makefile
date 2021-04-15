include Makefile.inc

SUBDIRS = lib kernel
EXTRA = Makefile Makefile.inc linker.ld evalute.c include

KERNEL = kernel


all: clean
	$(CC) -o tmp.out evalute.c
	for d in $(SUBDIRS); do (cd $$d; $(MAKE) all;) done;
	$(LD) -Tlinker.ld lib/i386.o kernel/kernel.a -o bin/$(KERNEL)

clean:
	for d in $(SUBDIRS); do (cd $$d; $(MAKE) clean;) done;
	rm -f bin/$(KERNEL) tmp.out $(STUDENTNO).tar.gz evalute results 

deploy:
	./tmp.out
	rm -f results
	bash evalute $(RTIME)

submit: clean
	tar -czf $(STUDENTNO).tar.gz $(SUBDIRS) $(EXTRA)
