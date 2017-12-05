	.file	"initTarget.cpp"
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
	.section	.text$_ZN1T11getInstanceEi,"x"
	.linkonce discard
	.align 2
	.globl	__ZN1T11getInstanceEi
	.def	__ZN1T11getInstanceEi;	.scl	2;	.type	32;	.endef
__ZN1T11getInstanceEi:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$20, %esp
	movl	%ecx, -20(%ebp)
/APP
 # 7 "initTarget.cpp" 1
	mov %ecx,%eax 
	
 # 0 "" 2
/NO_APP
	movl	%eax, -4(%ebp)
	movl	-4(%ebp), %eax
	movl	$20, (%eax)
	movl	8(%ebp), %eax
	movl	$30, (%eax)
	nop
	movl	-20(%ebp), %eax
	leave
	ret	$8
	.section .rdata,"dr"
LC0:
	.ascii "print:%d\12\0"
	.section	.text$_ZN1T5printEv,"x"
	.linkonce discard
	.align 2
	.globl	__ZN1T5printEv
	.def	__ZN1T5printEv;	.scl	2;	.type	32;	.endef
__ZN1T5printEv:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	%ecx, -12(%ebp)
	movl	-12(%ebp), %eax
	movl	(%eax), %eax
	movl	%eax, 4(%esp)
	movl	$LC0, (%esp)
	call	__Z6printfPKcz
	nop
	leave
	ret
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
	pushl	%ecx
	subl	$52, %esp
	call	___main
	leal	-32(%ebp), %eax
	movl	$50, 4(%esp)
	leal	-20(%ebp), %edx
	movl	%edx, (%esp)
	movl	%eax, %ecx
	call	__ZN1T11getInstanceEi
	subl	$8, %esp
	leal	-32(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN1T5printEv
	.ident	"GCC: (GNU) 5.4.0"
	.def	___mingw_vprintf;	.scl	2;	.type	32;	.endef
