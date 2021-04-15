.global	osdk_get_code_start
.global	osdk_get_code_end

osdk_get_code_start:
	pushl	%ebp
	movl	%esp, %ebp
	movl	code_start, %eax
	movl	%ebp, %esp
	popl	%ebp
	ret

osdk_get_code_end:
	pushl	%ebp
	movl	%esp, %ebp
	movl	code_end, %eax
	movl	%ebp, %esp
	popl	%ebp
	ret
