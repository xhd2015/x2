	.file	"virtual.cpp"
	.section .rdata,"dr"
.LC0:
	.ascii "A::foo %d\12\0"
	.section	.text$_ZN1A3fooEv,"x"
	.linkonce discard
	.align 2
	.globl	_ZN1A3fooEv
	.def	_ZN1A3fooEv;	.scl	2;	.type	32;	.endef
	.seh_proc	_ZN1A3fooEv
_ZN1A3fooEv:
.LFB10:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$32, %rsp
	.seh_stackalloc	32
	.seh_endprologue
	movq	%rcx, 16(%rbp)
	movq	16(%rbp), %rax
	movl	(%rax), %eax
	movl	%eax, %edx
	leaq	.LC0(%rip), %rcx
	call	printf
	nop
	addq	$32, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.section .rdata,"dr"
.LC1:
	.ascii "B::fu %d\12\0"
	.section	.text$_ZN1B2fuEv,"x"
	.linkonce discard
	.align 2
	.globl	_ZN1B2fuEv
	.def	_ZN1B2fuEv;	.scl	2;	.type	32;	.endef
	.seh_proc	_ZN1B2fuEv
_ZN1B2fuEv:
.LFB11:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$32, %rsp
	.seh_stackalloc	32
	.seh_endprologue
	movq	%rcx, 16(%rbp)
	movq	16(%rbp), %rax
	movl	(%rax), %eax
	movl	%eax, %edx
	leaq	.LC1(%rip), %rcx
	call	printf
	nop
	addq	$32, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.def	__main;	.scl	2;	.type	32;	.endef
	.text
	.globl	main
	.def	main;	.scl	2;	.type	32;	.endef
	.seh_proc	main
main:
.LFB12:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$80, %rsp
	.seh_stackalloc	80
	.seh_endprologue
	call	__main
	movl	$10, -28(%rbp)
	movl	$40, -32(%rbp)
	leaq	-32(%rbp), %rax
	addq	$4, %rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rcx
	call	_ZN1A3fooEv
	cmpq	$0, -8(%rbp)
	je	.L4
	movq	-8(%rbp), %rax
	subq	$4, %rax
	jmp	.L5
.L4:
	movl	$0, %eax
.L5:
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rax
	addq	$4, %rax
	movq	%rax, %rcx
	call	_ZN1A3fooEv
	movq	-16(%rbp), %rax
	movq	%rax, %rcx
	call	_ZN1B2fuEv
	movq	$43, -8(%rbp)
	movq	$54, -16(%rbp)
	movq	$434, -8(%rbp)
	movq	$544, -16(%rbp)
	leaq	-48(%rbp), %rax
	movq	%rax, -8(%rbp)
	movl	$0, %eax
	addq	$80, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.ident	"GCC: (GNU) 5.4.0"
	.def	printf;	.scl	2;	.type	32;	.endef
