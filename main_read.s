	.file	"main_read.cpp"
/APP
	NONSECTION:
	.word 0xaa55
	
	.code16gcc
	.section .rdata,"dr"
LC0:
	.ascii "Hello World!\0"
/NO_APP
	.section	.text,"x"
	.globl	__Z8theEntryv
	.def	__Z8theEntryv;	.scl	2;	.type	32;	.endef
__Z8theEntryv:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	$7, 4(%esp)
	movl	$LC0, (%esp)
	call	__ZN4Util8printStrEPKci
	nop
	leave
	ret
	.ident	"GCC: (GNU) 5.4.0"
	.def	__ZN4Util8printStrEPKci;	.scl	2;	.type	32;	.endef
