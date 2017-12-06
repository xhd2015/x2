	.file	"test_new_no_stdlib.cpp"
	.section .rdata,"dr"
__ZStL19piecewise_construct:
	.space 1
	.align 4
__ZN9__gnu_cxxL21__default_lock_policyE:
	.long	2
__ZStL13allocator_arg:
	.space 1
__ZStL6ignore:
	.space 1
	.def	___main;	.scl	2;	.type	32;	.endef
	.text
	.globl	_main
	.def	_main;	.scl	2;	.type	32;	.endef
_main:
	pushl	%ebp
	movl	%esp, %ebp
	andl	$-16, %esp
	subl	$16, %esp
	call	___main
	movl	$30, (%esp)
	call	_malloc
	movl	$30, (%esp)
	call	__Znaj
	movl	$0, %eax
	leave
	ret
	.ident	"GCC: (GNU) 6.4.0"
	.def	_malloc;	.scl	2;	.type	32;	.endef
	.def	__Znaj;	.scl	2;	.type	32;	.endef
