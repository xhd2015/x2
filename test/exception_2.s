	.file	"exception.cpp"
	.text
	.globl	___cxa_allocate_exception
	.def	___cxa_allocate_exception;	.scl	2;	.type	32;	.endef
___cxa_allocate_exception:
	pushl	%ebp
	movl	%esp, %ebp
	nop
	popl	%ebp
	ret
	.globl	___cxa_throw
	.def	___cxa_throw;	.scl	2;	.type	32;	.endef
___cxa_throw:
	pushl	%ebp
	movl	%esp, %ebp
	nop
	popl	%ebp
	ret
	.globl	__Z4testv
	.def	__Z4testv;	.scl	2;	.type	32;	.endef
__Z4testv:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$12, %esp
	movl	$1, (%esp)
	call	___cxa_allocate_exception
	movl	$0, 8(%esp)
	movl	$__ZTI10Texception, 4(%esp)
	movl	%eax, (%esp)
	call	___cxa_throw
	nop
	leave
	ret
	.def	___main;	.scl	2;	.type	32;	.endef
	.globl	_main
	.def	_main;	.scl	2;	.type	32;	.endef
_main:
	pushl	%ebp
	movl	%esp, %ebp
	andl	$-16, %esp
	subl	$16, %esp
	call	___main
	movl	$0, 12(%esp)
	movl	$0, %eax
	leave
	ret
	.globl	__ZTI10Texception
	.section	.rdata$_ZTI10Texception,"dr"
	.linkonce same_size
	.align 4
__ZTI10Texception:
	.long	__ZTVN10__cxxabiv117__class_type_infoE+8
	.long	__ZTS10Texception
	.globl	__ZTS10Texception
	.section	.rdata$_ZTS10Texception,"dr"
	.linkonce same_size
	.align 4
__ZTS10Texception:
	.ascii "10Texception\0"
	.ident	"GCC: (GNU) 5.4.0"
