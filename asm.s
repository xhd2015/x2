	.file	"asm.cpp"
/APP
	_LOP:
	_What = _LOP 
	
/NO_APP
	.text
	.globl	__Z4testv
	.def	__Z4testv;	.scl	2;	.type	32;	.endef
__Z4testv:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	movl	$_LOP, -4(%ebp)
	movl	_What, %eax
	movl	%eax, -8(%ebp)
	movl	$_What, -12(%ebp)
	movl	$0, -16(%ebp)
	nop
	leave
	ret
	.ident	"GCC: (GNU) 5.4.0"
