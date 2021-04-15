gdt_info:
	gdt_limit:	.word	gdt_end - gdt - 0x1
	gdt_address:	.long	gdt

gdt:
	null_desc:		.long	0x0
				.long	0x0
	flat_code:		.word	0xffff
				.word	0x0
				.byte	0x0
				.byte	0x9a		
				.byte	0xcf	 	
				.byte	0x0
	flat_data:		.word	0xffff
				.word	0x0
				.byte	0x0
				.byte	0x92		
				.byte	0xcf		
				.byte	0x0
	user_code:		.word	0xffff
				.word	0x0
				.byte	0x0
				.byte	0xfa 		
				.byte	0xcf		
				.byte	0x0
	user_data:		.word	0xffff
				.word	0x0
				.byte	0x0
				.byte	0xf2		
				.byte	0xcf		
				.byte	0x0
	task_state:		.long	0x0
				.long	0x0
gdt_end:

init_gdt:
	pushl	%eax
	lgdt	(gdt_info)
flush_gdt:
	movw	$0x10, %ax
	movw	%ax, %ds
	movw	%ax, %es
	movw	%ax, %gs
	movw	%ax, %fs
	movw	%ax, %ss
	ljmp	$0x8, $flush_gdt_return
flush_gdt_return:
	popl	%eax	
	ret

