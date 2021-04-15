init_pic:
remap_pic:
	pushl	%eax
	
	movb	$0x11, %al
	outb	%al, $0x20
	outb	%al, $0xa0
	
	movb	$0x20, %al
	outb	%al, $0x21
	movb	$0x28, %al
	outb	%al, $0xa1
	
	movb	$0x4, %al
	outb	%al, $0x21
	movb	$0x2, %al
	outb	%al, $0xa1
	
	movb	$0x1, %al
	outb	%al, $0x21
	outb	%al, $0xa1

	xorb	%al, %al
	outb	%al, $0x21
	outb	%al, $0xa1
	
	popl	%eax
	ret
