.global osdk_task_create
.global osdk_task_switch

.align	4

task:	.long	0x0
ksize:	.long	0x0
rsize:	.long	0x0


tss:
	back_link:	.word	0x0
			.word	0x0
	esp0:		.long	0x0
	ss0:		.word	0x0
			.word	0x0
	esp1:		.long	0x0
	ss1:		.word	0x0
			.word	0x0
	esp2:		.long	0x0
	ss2:		.word	0x0
			.word	0x0
	cr3:		.long	0x0
	eip:		.long	0x0
	eflags:		.long	0x0
	eax:		.long	0x0
	ecx:		.long	0x0
	edx:		.long	0x0
	ebx:		.long	0x0
	esp:		.long	0x0
	ebp:		.long	0x0
	esi:		.long	0x0
	edi:		.long	0x0
	es:		.word	0x0
			.word	0x0
	cs:		.word	0x0
			.word	0x0
	ss:		.word	0x0
			.word	0x0
	ds:		.word	0x0
			.word	0x0
	fs:		.word	0x0
			.word	0x0
	gs:		.word	0x0
			.word	0x0
	ldt:		.word	0x0
			.word	0x0
			.word	0x0
	iobitmap:	.word	0x0

init_tr:
	pushl	%eax
	pushl	%ebx
	pushl	%ecx
	movl	$tss, %ecx
	movl	$task_state, %ebx
	movw	$0x67, (%ebx)
	movw	%cx, 2(%ebx)
	shrl	$0x10, %ecx
	movb	%cl, 4(%ebx)
	movb	$0x89, 5(%ebx)				
	movb	$0x0, 6(%ebx)				
	movb	%ch, 7(%ebx)
	movw	$0x28, %ax				
	ltr	%ax
	popl	%ecx
	popl	%ebx
	popl	%eax
	ret


osdk_task_create:
	pushl	%ebp
	movl	%esp, %ebp
	movl 	8(%ebp), %eax
	addl	ksize, %eax
	addl	rsize, %eax
	movl	%eax, %esp				
	pushl	$0x23					
	movl	16(%ebp), %eax
	pushl	%eax					
	pushl	$0x202					
	pushl	$0x1b					
	movl	12(%ebp), %eax
	pushl	%eax					
	pushl	$0x0					
	pushl	$0x0					
	pushl	$0x0					
	pushl	$0x0					
	pushl	$0x0					
	pushl	$0x0					
	pushl	$0x0					
	pushl	$0x0					
	pushl	$0x23					
	pushl	$0x23					
	pushl	$0x23					
	pushl	$0x23					
	pushl	$0x0					
	pushl	$0x20					
	movl	%esp, %eax
	movl	%ebp, %esp				
	popl	%ebp
	ret

osdk_task_switch:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %eax
	addl	ksize, %eax
	movl	%eax, task
	movl	%ebp, %esp
	popl	%ebp
	ret


