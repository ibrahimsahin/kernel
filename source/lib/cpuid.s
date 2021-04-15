.global osdk_get_cpuid

vendor:		.long	0x0
		.long	0x0
		.long	0x0
std_eax:	.long	0x0
std_ebx:	.long	0x0
std_ecx:	.long	0x0
std_edx:	.long	0x0
ser_ecx:	.long	0x0
ser_edx:	.long	0x0

check_cpuid:
	pushfl
	popl	%eax
	movl	%eax, %ebx
	orl	$0x200000, %eax			
	pushl	%eax
	popfl
	pushfl
	popl	%eax
	cmpl	%ebx, %eax
	je	cpuid_not_supported
cpuid_supported:
	movl	$0x1, %eax
	ret
cpuid_not_supported:
	xorl	%eax, %eax
	ret

check_rdtsc:
	movl	std_edx, %eax
	andl	$0x10, %eax			
	jz	rdtsc_not_supported
rdtsc_supported:
	movl	$0x1, %eax
	ret
rdtsc_not_supported:
	xorl	%eax, %eax
	ret
	

init_cpuid:
	pushl	%eax
	pushl	%ebx
	pushl	%ecx
	pushl	%edx
	pushl	%esi
	movl	$vendor, %esi
	xorl	%eax, %eax
	cpuid
	movl	%ebx, (%esi)
	movl	%edx, 4(%esi)
	movl	%ecx, 8(%esi)
	movl	$0x1, %eax
	cpuid
	movl	%eax, std_eax
	movl	%ebx, std_ebx
	movl	%ecx, std_ecx
	movl	%edx, std_edx
	movl	$0x3, %eax
	cpuid
	movl	%ecx, ser_ecx
	mov	%edx, ser_edx
init_cpuid_end:
	popl	%esi	
	popl	%edx
	popl	%ecx
	popl	%ebx
	popl	%eax
	ret
no_cpuid:
	jmp	init_cpuid_end
no_rdtsc:
	jmp	init_cpuid_end

get_cpu_speed:
	ret


osdk_get_cpuid:
	pushl	%ebp
	movl	%esp, %ebp
	pushfl
	pushl	%ecx
	pushl	%esi
	pushl	%edi
	cld
	movl	$vendor, %esi
	movl	8(%ebp), %edi
	movl	$0x3, %ecx
	rep	movsd
	movb	$0x0, (%edi)
	movl	std_eax, %ecx
	movl	%ecx, 1(%edi)
	movl	std_ebx, %ecx
	movl	%ecx, 5(%edi)
	movl	std_ecx, %ecx
	movl	%ecx, 9(%edi)
	movl	std_edx, %ecx
	movl	%ecx, 13(%edi)
	movl	ser_ecx, %ecx
	movl	%ecx, 25(%edi)
	movl	ser_edx, %ecx
	movl	%ecx, 29(%edi)
	popl	%edi
	popl	%esi
	popl	%ecx
	popfl
	movl	%ebp, %esp
	popl	%ebp
	ret


