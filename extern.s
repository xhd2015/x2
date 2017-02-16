	.file	"extern.cpp"
	.text
	.globl	__Z4testv
	.def	__Z4testv;	.scl	2;	.type	32;	.endef
__Z4testv:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	movl	$_x, -4(%ebp)
	movl	$_x, -4(%ebp)
	movl	_e, %eax
	movl	(%eax), %eax
	movl	%eax, -4(%ebp)
	movl	_e, %eax
	movl	%eax, -4(%ebp)
	movl	_o, %eax
	movl	(%eax), %eax
	movl	%eax, -4(%ebp)
	movl	_o, %eax
	movl	%eax, -4(%ebp)
	movl	_a, %eax
	movl	%eax, -4(%ebp)
	movl	$_a, -4(%ebp)
	movl	$_z, -4(%ebp)
	movl	$_z, -4(%ebp)
	movl	_y, %eax
	movl	%eax, -4(%ebp)
	movl	$_y, -4(%ebp)
	nop
	leave
	ret
	.ident	"GCC: (GNU) 5.4.0"
	.def	_x;	.scl	2;	.type	32;	.endef
