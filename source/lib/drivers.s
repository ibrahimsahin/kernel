.global osdk_getch
.global osdk_putchar
.global osdk_setxy
.global osdk_getxy
.global osdk_reboot

osdk_getch:
	inb	$0x60, %al
	ret

osdk_putchar:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%eax
	pushl	%ebx
	pushw	%es
	movw	$0x10, %ax
	movw	%ax, %es
	movl	$0x0b8000, %ebx
	movb	8(%ebp), %al
	movb	12(%ebp), %ah
	addl	16(%ebp), %ebx
	movb	%al, %es:(%ebx)
	incl	%ebx
	movb	%ah, %es:(%ebx)
	popw	%es
	popl	%ebx
	popl	%eax	
	movl	%ebp, %esp
	pop	%ebp
	ret
	
osdk_setxy:
	ret

osdk_getxy:
	ret

osdk_reboot:
	ret

