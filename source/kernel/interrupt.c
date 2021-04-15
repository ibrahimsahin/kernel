#include <interrupt.h>

#include "string.h"

interrupt_handler handlers[256] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

void general_intterupt_noerror(int num, int err);
void general_intterupt_error(int num, int err);
void page_fault_interrupt(int num, int err);

char * interrupt_messages[] = {
    "*** Division By Zero Exception ***",
    "*** Debug ***",
    "*** Non Maskable Interrupt ***",
    "*** Breakpoint ***",
    "*** Into Detected Overflow ***",
    "*** Out of Bounds ***",
    "*** Invalid Opcode ***",
    "*** No Coprocessor ***",
    "*** Double Fault ***",
    "*** Coprocessor Segment Overrun ***",
    "*** Bad TSS ***",
    "*** Segment Not Present ***",
    "*** Stack Fault ***",
    "*** General Protection ***",
    "*** Page Fault ***",
    "*** Unknown Interrupt ***",
    "*** Coprocessor Fault ***",
    "*** Alignment Check Exception ***",
    "*** Machine Check ***"
};

void interrupt(int num, int err) {
    interrupt_handler h = handlers[num];
    if (h == 0) {
        panic("*** Unregistered Interrupt ***");
    } else {
        h(num, err);
    }
}

void register_interrupt_handler(int num, interrupt_handler handler) {
    handlers[num] = handler;
}

void init_default_interrupt_handlers() {
    register_interrupt_handler(INT0, general_intterupt_noerror);
    register_interrupt_handler(INT1, general_intterupt_noerror);
    register_interrupt_handler(INT2, general_intterupt_noerror);
    register_interrupt_handler(INT3, general_intterupt_noerror);
    register_interrupt_handler(INT4, general_intterupt_noerror);
    register_interrupt_handler(INT5, general_intterupt_noerror);
    register_interrupt_handler(INT6, general_intterupt_noerror);
    register_interrupt_handler(INT7, general_intterupt_noerror);
    register_interrupt_handler(INT8, general_intterupt_error);
    register_interrupt_handler(INT9, general_intterupt_noerror);
    register_interrupt_handler(INT10, general_intterupt_error);
    register_interrupt_handler(INT11, general_intterupt_error);
    register_interrupt_handler(INT12, general_intterupt_error);
    register_interrupt_handler(INT13, general_intterupt_error);
    register_interrupt_handler(INT14, page_fault_interrupt);
    register_interrupt_handler(INT15, general_intterupt_noerror);
    register_interrupt_handler(INT16, general_intterupt_noerror);
    register_interrupt_handler(INT17, general_intterupt_noerror);
    register_interrupt_handler(INT18, general_intterupt_noerror);
}

void general_intterupt_noerror(int num, int err) {
    panic(interrupt_messages[num]);
}

void general_intterupt_error(int num, int err) {
    printf("Error: 0x%x\n", err);
    panic(interrupt_messages[num]);
}

void page_fault_interrupt(int num, int err) {
    printf("Error: 0x%x\n", err);
    printf("Page Fault (CR2) = 0x%x\n", osdk_get_fault_address());
    panic(interrupt_messages[num]);
}


