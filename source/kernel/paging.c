#include <paging.h>
#include <mem.h>
#include <string.h>

unsigned int *PD;
unsigned int *PT;

void init_paging() {
    PD = (unsigned int *) 0x100000;
    PT = (unsigned int *) 0x101000;

    bzero(PD, 4096);

    unsigned int i;
    for (i = 0; i < 0x8000000; i += 0x1000) {
        if (!(osdk_mem_map(PD, i, i, PAGE_WRITE | PAGE_USER | PAGE_PRESENT))) {
            if (!osdk_table_map(PD, i, PT, PAGE_WRITE | PAGE_USER | PAGE_PRESENT)) {
                printf("ERROR Table Already Mapped Please Unmap First 0x%x\n", PT);
            }
            PT += 0x400;
            if (!(osdk_mem_map(PD, i, i, PAGE_WRITE | PAGE_USER | PAGE_PRESENT))) {
                printf("ERROR Mapping 0x%x To 0x%x\n", i, i);
                panic("");
            }
            osdk_flush((void*)i);
        }
    }


    PT = (unsigned int *) 0x101000;
    osdk_set_pd(PD);

    osdk_enable_paging();
    osdk_flush_all();

}
