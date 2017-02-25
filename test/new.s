	.file	"new.cpp"
	.def	___main;	.scl	2;	.type	32;	.endef
	.text
	.globl	_main
	.def	_main;	.scl	2;	.type	32;	.endef
_main:
	pushl	%ebp
	movl	%esp, %ebp
	andl	$-16, %esp
	subl	$32, %esp
	call	___main
	movl	$4, (%esp)
	call	__Znwj
	movl	%eax, 28(%esp)
	movl	28(%esp), %eax
	movl	(%eax), %eax
	movl	%eax, 24(%esp)
	movl	28(%esp), %eax
	movl	%eax, (%esp)
	call	__ZdlPv
	movl	$0, %eax
	leave
	ret
	.ident	"GCC: (GNU) 5.4.0"
	.def	__Znwj;	.scl	2;	.type	32;	.endef
	.def	__ZdlPv;	.scl	2;	.type	32;	.endef
