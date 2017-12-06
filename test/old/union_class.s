	.file	"union_class.cpp"
	.section	.text$_ZnwjPv,"x"
	.linkonce discard
	.globl	__ZnwjPv
	.def	__ZnwjPv;	.scl	2;	.type	32;	.endef
__ZnwjPv:
	pushl	%ebp
	movl	%esp, %ebp
	movl	12(%ebp), %eax
	popl	%ebp
	ret
	.section .rdata,"dr"
LC0:
	.ascii "P\0"
	.section	.text$_ZN1PC1Ev,"x"
	.linkonce discard
	.align 2
	.globl	__ZN1PC1Ev
	.def	__ZN1PC1Ev;	.scl	2;	.type	32;	.endef
__ZN1PC1Ev:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	$LC0, (%esp)
	call	_puts
	nop
	leave
	ret
	.def	___main;	.scl	2;	.type	32;	.endef
	.section .rdata,"dr"
LC1:
	.ascii "t.a = %d,p.b=%d,p.c=%d\12\0"
	.text
	.globl	_main
	.def	_main;	.scl	2;	.type	32;	.endef
_main:
	pushl	%ebp
	movl	%esp, %ebp
	andl	$-16, %esp
	subl	$32, %esp
	call	___main
	leal	27(%esp), %eax
	movl	%eax, 4(%esp)
	movl	$5, (%esp)
	call	__ZnwjPv
	testl	%eax, %eax
	je	L6
	movl	%eax, (%esp)
	call	__ZN1PC1Ev
L6:
	leal	27(%esp), %eax
	movzbl	4(%eax), %eax
	movsbl	%al, %ecx
	leal	27(%esp), %eax
	movl	(%eax), %edx
	leal	27(%esp), %eax
	movl	(%eax), %eax
	movl	%ecx, 12(%esp)
	movl	%edx, 8(%esp)
	movl	%eax, 4(%esp)
	movl	$LC1, (%esp)
	call	_printf
	movl	$0, %eax
	leave
	ret
	.ident	"GCC: (GNU) 5.4.0"
	.def	_puts;	.scl	2;	.type	32;	.endef
	.def	_printf;	.scl	2;	.type	32;	.endef
