	.file	"test_or.cpp"
	.def	___main;	.scl	2;	.type	32;	.endef
	.section .rdata,"dr"
	.align 4
LC0:
	.ascii "sizeof(A)=%d,y=%x,k.c=%x,k.d=%x\12\0"
	.text
	.globl	_main
	.def	_main;	.scl	2;	.type	32;	.endef
_main:
	pushl	%ebp
	movl	%esp, %ebp
	andl	$-16, %esp
	subl	$48, %esp
	call	___main
	movl	36(%esp), %eax
	andl	$-16777216, %eax
	orb	$-1, %al
	movl	%eax, 36(%esp)
	movb	$-16, 39(%esp)
	movzbl	40(%esp), %eax
	orl	$1, %eax
	movb	%al, 40(%esp)
	movzbl	40(%esp), %eax
	orl	$2, %eax
	movb	%al, 40(%esp)
	movl	36(%esp), %eax
	sall	$8, %eax
	sarl	$8, %eax
	movl	%eax, %edx
	movzbl	39(%esp), %eax
	movsbl	%al, %eax
	sall	$24, %eax
	orl	%edx, %eax
	movl	%eax, 44(%esp)
	movzbl	40(%esp), %eax
	sall	$6, %eax
	sarb	$7, %al
	movsbl	%al, %edx
	movzbl	40(%esp), %eax
	sall	$7, %eax
	sarb	$7, %al
	movsbl	%al, %eax
	movl	%edx, 16(%esp)
	movl	%eax, 12(%esp)
	movl	44(%esp), %eax
	movl	%eax, 8(%esp)
	movl	$8, 4(%esp)
	movl	$LC0, (%esp)
	call	_printf
	movl	$0, %eax
	leave
	ret
	.ident	"GCC: (GNU) 5.4.0"
	.def	_printf;	.scl	2;	.type	32;	.endef
