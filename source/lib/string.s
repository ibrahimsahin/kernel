.set	MAXX, 80			
.set	MAXY, 25			
.set	COLOR, 0x7			

POSX:	.long	0x0			
POSY:	.long	0x0			

writestr:
	pushl	%eax
	pushl	%ebx
	pushl	%ecx
	pushl	%edx
.w_loop:
	movl	$MAXX, %eax
	movl	POSY, %ebx
	mull	%ebx
	addl	POSX, %eax
	movl	$0x2, %ebx
	mull	%ebx
	movl	$0xb8000, %edx
	addl	%eax, %edx
.w_write:
	movb	(%ecx), %al
	orb	%al, %al
	jz	.w_end
	cmpb	$0xa, %al
	je	.w_linefeed
	movb	%al, (%edx)
	incl	%edx
	movb	$COLOR, (%edx)
	incl	%edx
	incl	%ecx
	cmpl	$MAXX-0x1, POSX
	je	.w_newline
	cmpl	$MAXY-0x1, POSY
	je	.w_scrollup
	incl	POSX
	jmp	.w_loop
.w_linefeed:
	incl	%ecx
.w_newline:
	movl	$0x0, POSX
	incl	POSY
	jmp	.w_loop
.w_scrollup:
	movl	$0x0, POSX
	movl	$0x0, POSY
	jmp	.w_loop
.w_end:
	popl	%edx
	popl	%ecx
	popl	%ebx
	popl	%eax
	ret

clrscr:
	pushl	%ecx
	pushl	%edx
	movl	$0xb8000, %edx
	movw	$MAXX * MAXY * 0x2, %cx
.c_loop:
	orw	%cx, %cx
	jz	.c_end
	movb	$0x0, (%edx)
	incl	%edx
	decw	%cx
	jmp	.c_loop
.c_end:
	movl	$0x0, POSX
	movl	$0x0, POSY
	popl	%edx
	popl	%ecx
	ret

