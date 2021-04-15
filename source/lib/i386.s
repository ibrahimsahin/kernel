.global start						
.global osdk_lock
.global osdk_unlock

.set STACKSIZE, 1024000
.set PDSIZE, 1024*4
.set PTSIZE, 1024*4
.set PTNUM, 1024


.section .text

code_start:
start:
	jmp osdk_main					

	.align 4					

	mb_magic:
		.long 0x1BADB002			
	mb_flags:
		.long 0x00000003			
	mb_checksum:
		.long -(0x1BADB002+0x00000003)		
	mb_header_addr:
		.long 0x0				
	mb_load_addr:
		.long 0x0				
	mb_load_end_addr:
		.long 0x0				
	mb_bss_end_addr:
		.long 0x0				
	mb_entry_addr:
		.long 0x0				
	mb_mode_type:
		.long 0x0				
	mb_width:
		.long 0x0				
	mb_height:
		.long 0x0				
	mb_depth:
		.long 0x0				



.align 0x1000						

osdk_main:
	pushl	$0x0					
	popfl
	movl	$STACK + STACKSIZE - 0x1, %esp		 
	pushl	%eax
	pushl	%ebx
	call	clrscr
	call	init_gdt
	call	init_isr
	call	init_idt
	call	remap_pic
	call	init_tr
	call	init_cpuid
	call	get_cpu_speed
	popl	%ebx
	popl	%eax
	pushl	%ebx
	pushl	%eax
	movl	$1024, ksize
	movl	$76, rsize
 	movl	$0, task
	call	main					
	jmp	.					
	cli						
	hlt						

.include "isr.s"
.include "idt.s"
.include "gdt.s"
.include "tss.s"
.include "pic.s"
.include "pit.s"
.include "interrupt.s"
.include "ports.s"
.include "drivers.s"
.include "paging.s"
.include "cpuid.s"
.include "utility.s"
.include "string.s"
.include "debug.s"
.include "temp.s"


code_end:

.section .bss
	.align 32
	.lcomm	STACK, STACKSIZE		


