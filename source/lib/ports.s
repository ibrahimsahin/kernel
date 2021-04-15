.global osdk_in
.global osdk_out

osdk_in:
	pushl	%ebp
	movl	%esp, %ebp
	pushw	%dx
	movw	8(%ebp), %dx
	inb	%dx, %al
	popw	%dx
	movl	%ebp, %esp
	pop	%ebp
	ret

osdk_out:
	pushl	%ebp
	movl	%esp, %ebp
	pushw	%ax
	pushw	%dx
	movw	8(%ebp), %dx
	movb	12(%ebp), %al
	outb	%al, %dx
	popw	%dx
	popw	%ax
	movl	%ebp, %esp
	pop	%ebp
	ret

