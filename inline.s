	.file	"inline.cpp"
	.section	.text$_Z6printfPKcz,"x"
	.linkonce discard
	.globl	__Z6printfPKcz
	.def	__Z6printfPKcz;	.scl	2;	.type	32;	.endef
__Z6printfPKcz:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$36, %esp
	leal	12(%ebp), %eax
	movl	%eax, -12(%ebp)
	movl	-12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	___mingw_vprintf
	movl	%eax, %ebx
	movl	%ebx, %eax
	addl	$36, %esp
	popl	%ebx
	popl	%ebp
	ret
	.section .rdata,"dr"
LC0:
	.ascii "t\0"
	.section	.text$_Z1tv,"x"
	.linkonce discard
	.globl	__Z1tv
	.def	__Z1tv;	.scl	2;	.type	32;	.endef
__Z1tv:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	$LC0, (%esp)
	call	__Z6printfPKcz
	nop
	leave
	ret
	.section .rdata,"dr"
LC1:
	.ascii "m\0"
	.text
	.align 2
	.globl	__ZN1M1mEv
	.def	__ZN1M1mEv;	.scl	2;	.type	32;	.endef
__ZN1M1mEv:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	$LC1, (%esp)
	call	__Z6printfPKcz
	nop
	leave
	ret
	.section .rdata,"dr"
LC2:
	.ascii "10\0"
LC3:
	.ascii "0\0"
LC4:
	.ascii "9090\0"
	.text
	.globl	__Z4testv
	.def	__Z4testv;	.scl	2;	.type	32;	.endef
__Z4testv:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	$10, -12(%ebp)
	movl	$LC2, (%esp)
	call	__Z6printfPKcz
	movl	$0, -16(%ebp)
	movl	$LC3, (%esp)
	call	__Z6printfPKcz
	call	__Z1tv
	movl	$LC4, (%esp)
	call	__Z6printfPKcz
	call	__ZN1M1mEv
	nop
	leave
	ret
	.ident	"GCC: (GNU) 5.4.0"
	.def	___mingw_vprintf;	.scl	2;	.type	32;	.endef
