idt_info:
	idt_limit:	.word	0xff * 0x8 - 0x1
	idt_address:	.long	idt
	
idt:	
	.rept	0xff
		.long 0x0
		.long 0x0
	.endr
idt_end:

set_idesc0:
	pushl	%eax
	pushl	%ebx
	pushl	%ecx
	pushl	%edx
	pushl	%esi
	movl	$0x8, %eax
	mull	%ecx
	addl	$idt, %eax
	movl	%ebx, %edx
	andl	$0xffff, %ebx
	shrl	$0x10, %edx
	movl	%eax, %esi
	movw	%bx, (%esi)
	movw	$0x8, 2(%esi)
	movb	$0x0, 4(%esi)
	movb	$0x8e, 5(%esi)		# 10001110b
	movw	%dx, 6(%esi)
	popl	%esi
	popl	%edx
	popl	%ecx
	popl	%ebx
	popl	%eax
	ret

set_idesc3:
	pushl	%eax
	pushl	%ebx
	pushl	%ecx
	pushl	%edx
	pushl	%esi
	movl	$0x8, %eax
	mull	%ecx
	addl	$idt, %eax
	movl	%ebx, %edx
	andl	$0xffff, %ebx
	shrl	$0x10, %edx
	movl	%eax, %esi
	movw	%bx, (%esi)
	movw	$0x8, 2(%esi)
	movb	$0x0, 4(%esi)
	movb	$0xee, 5(%esi)		# 11101110b
	movw	%dx, 6(%esi)
	popl	%esi
	popl	%edx
	popl	%ecx
	popl	%ebx
	popl	%eax
	ret

init_idt:
	lidt	(idt_info)
	ret

