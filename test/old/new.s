	.file	"new.cpp"
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
	.section	.text$_ZN1TC1EiiPS_,"x"
	.linkonce discard
	.align 2
	.globl	__ZN1TC1EiiPS_
	.def	__ZN1TC1EiiPS_;	.scl	2;	.type	32;	.endef
__ZN1TC1EiiPS_:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	%ecx, -4(%ebp)
	nop
	leave
	ret	$12
	.def	___main;	.scl	2;	.type	32;	.endef
	.text
	.globl	_main
	.def	_main;	.scl	2;	.type	32;	.endef
_main:
	leal	4(%esp), %ecx
	andl	$-16, %esp
	pushl	-4(%ecx)
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	pushl	%ecx
	subl	$32, %esp
	call	___main
	leal	-20(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$4, (%esp)
	call	__ZnwjPv
	testl	%eax, %eax
	je	L6
	movl	$4, (%eax)
L6:
	movl	%eax, -12(%ebp)
	leal	-20(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$1, (%esp)
	call	__ZnwjPv
	movl	%eax, %ebx
	testl	%ebx, %ebx
	je	L7
	movl	$0, 8(%esp)
	movl	$10, 4(%esp)
	movl	$9, (%esp)
	movl	%ebx, %ecx
	call	__ZN1TC1EiiPS_
	subl	$12, %esp
	movl	%ebx, %eax
	jmp	L8
L7:
	movl	%ebx, %eax
L8:
	movl	%eax, -16(%ebp)
	movl	$0, %eax
	leal	-8(%ebp), %esp
	popl	%ecx
	popl	%ebx
	popl	%ebp
	leal	-4(%ecx), %esp
	ret
	.ident	"GCC: (GNU) 5.4.0"
