.global osdk_timerhz

osdk_timerhz:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%eax
	pushl	%ebx
	pushl	%edx
	movb	$0x36, %al
	outb	%al, $0x43
	movw	8(%ebp), %bx
	movw	$0x34dc, %ax 
	movw	$0x12, %dx
	divw	%bx
	outb	%al, $0x40
	movb	%ah, %al
	outb	%al, $0x40
	popl	%edx
	popl	%ebx
	popl	%eax
	movl	%ebp, %esp
	popl	%ebp
	ret

