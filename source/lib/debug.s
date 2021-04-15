.global osdk_get_tss_ss0
.global osdk_get_tss_esp0
.global osdk_get_ss
.global osdk_get_esp
.global osdk_get_eflags
.global osdk_set_tr
.global osdk_get_cs
.global osdk_get_cr0
.global osdk_get_cr4

osdk_get_tss_ss0:
	movl	ss0, %eax
	ret
osdk_get_tss_esp0:
	movl	esp0, %eax
	ret
osdk_get_ss:
	xorl	%eax, %eax
	movw	ss, %ax
	ret
osdk_get_esp:
	movl	esp, %eax
	ret
osdk_get_eflags:
	pushfl
	popl	%eax
	ret
osdk_set_tr:
	xorl	%eax, %eax
	str	%ax
	ret
osdk_get_cs:
	xorl	%eax, %eax
	movw	%cs, %ax
	ret
osdk_get_cr0:
	xorl	%eax, %eax
	movl	%cr0, %eax
	ret
osdk_get_cr4:
	xorl	%eax, %eax
	mov	%cr4, %eax
	ret


