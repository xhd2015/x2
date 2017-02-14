	.file	"extern.cpp"
	.globl	_a
	.bss
	.align 4
_a:
	.space 4
	.text
	.globl	__Z4testv
	.def	__Z4testv;	.scl	2;	.type	32;	.endef
__Z4testv:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	movl	_a, %eax
	movl	%eax, -4(%ebp)
	nop
	leave
	ret
	.ident	"GCC: (GNU) 5.4.0"
