	.file	"virtual-size.cpp"
	.section .rdata,"dr"
.LC0:
	.ascii "B:printb \0"
	.section	.text$_ZN1B6printbEv,"x"
	.linkonce discard
	.align 2
	.globl	_ZN1B6printbEv
	.def	_ZN1B6printbEv;	.scl	2;	.type	32;	.endef
	.seh_proc	_ZN1B6printbEv
_ZN1B6printbEv:
.LFB11:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$32, %rsp
	.seh_stackalloc	32
	.seh_endprologue
	movq	%rcx, 16(%rbp)
	leaq	.LC0(%rip), %rcx
	call	puts
	nop
	addq	$32, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.section .rdata,"dr"
.LC1:
	.ascii "Bson2:printb \0"
	.section	.text$_ZN5Bson26printbEv,"x"
	.linkonce discard
	.align 2
	.globl	_ZN5Bson26printbEv
	.def	_ZN5Bson26printbEv;	.scl	2;	.type	32;	.endef
	.seh_proc	_ZN5Bson26printbEv
_ZN5Bson26printbEv:
.LFB12:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$32, %rsp
	.seh_stackalloc	32
	.seh_endprologue
	movq	%rcx, 16(%rbp)
	leaq	.LC1(%rip), %rcx
	call	puts
	nop
	addq	$32, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.section	.text$_ZN1BC2Ev,"x"
	.linkonce discard
	.align 2
	.globl	_ZN1BC2Ev
	.def	_ZN1BC2Ev;	.scl	2;	.type	32;	.endef
	.seh_proc	_ZN1BC2Ev
_ZN1BC2Ev:
.LFB15:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	.seh_endprologue
	movq	%rcx, 16(%rbp)
	leaq	16+_ZTV1B(%rip), %rdx
	movq	16(%rbp), %rax
	movq	%rdx, (%rax)
	nop
	popq	%rbp
	ret
	.seh_endproc
	.section	.text$_ZN1BC1Ev,"x"
	.linkonce discard
	.align 2
	.globl	_ZN1BC1Ev
	.def	_ZN1BC1Ev;	.scl	2;	.type	32;	.endef
	.seh_proc	_ZN1BC1Ev
_ZN1BC1Ev:
.LFB16:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	.seh_endprologue
	movq	%rcx, 16(%rbp)
	leaq	16+_ZTV1B(%rip), %rdx
	movq	16(%rbp), %rax
	movq	%rdx, (%rax)
	nop
	popq	%rbp
	ret
	.seh_endproc
	.section	.text$_ZN4BsonC1Ev,"x"
	.linkonce discard
	.align 2
	.globl	_ZN4BsonC1Ev
	.def	_ZN4BsonC1Ev;	.scl	2;	.type	32;	.endef
	.seh_proc	_ZN4BsonC1Ev
_ZN4BsonC1Ev:
.LFB19:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$32, %rsp
	.seh_stackalloc	32
	.seh_endprologue
	movq	%rcx, 16(%rbp)
	movq	16(%rbp), %rax
	movq	%rax, %rcx
	call	_ZN1BC2Ev
	leaq	16+_ZTV4Bson(%rip), %rdx
	movq	16(%rbp), %rax
	movq	%rdx, (%rax)
	nop
	addq	$32, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.section	.text$_ZN5Bson2C1Ev,"x"
	.linkonce discard
	.align 2
	.globl	_ZN5Bson2C1Ev
	.def	_ZN5Bson2C1Ev;	.scl	2;	.type	32;	.endef
	.seh_proc	_ZN5Bson2C1Ev
_ZN5Bson2C1Ev:
.LFB22:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$32, %rsp
	.seh_stackalloc	32
	.seh_endprologue
	movq	%rcx, 16(%rbp)
	movq	16(%rbp), %rax
	movq	%rax, %rcx
	call	_ZN1BC2Ev
	leaq	16+_ZTV5Bson2(%rip), %rdx
	movq	16(%rbp), %rax
	movq	%rdx, (%rax)
	nop
	addq	$32, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.def	__main;	.scl	2;	.type	32;	.endef
	.section .rdata,"dr"
	.align 8
.LC2:
	.ascii "sizeof(A) is %d,sizeof(D) is %d,sizeof(C) is %d,sizeof(B) is %d,sizeof(Bson) is %d,sizeof(Bson2) is %d\12\0"
	.text
	.globl	main
	.def	main;	.scl	2;	.type	32;	.endef
	.seh_proc	main
main:
.LFB13:
	pushq	%rbp
	.seh_pushreg	%rbp
	pushq	%rbx
	.seh_pushreg	%rbx
	subq	$88, %rsp
	.seh_stackalloc	88
	leaq	128(%rsp), %rbp
	.seh_setframe	%rbp, 128
	.seh_endprologue
	call	__main
	leaq	-64(%rbp), %rax
	movq	%rax, %rcx
	call	_ZN1BC1Ev
	movq	$8, 48(%rsp)
	movq	$8, 40(%rsp)
	movq	$8, 32(%rsp)
	movl	$1, %r9d
	movl	$1, %r8d
	movl	$5, %edx
	leaq	.LC2(%rip), %rcx
	call	printf
	movl	$8, %ecx
	call	_Znwm
	movq	%rax, %rbx
	movq	%rbx, %rcx
	call	_ZN1BC1Ev
	movq	%rbx, -56(%rbp)
	movq	-56(%rbp), %rax
	movq	(%rax), %rax
	movq	(%rax), %rax
	movq	-56(%rbp), %rdx
	movq	%rdx, %rcx
	call	*%rax
	movl	$8, %ecx
	call	_Znwm
	movq	%rax, %rbx
	movq	%rbx, %rcx
	call	_ZN4BsonC1Ev
	movq	%rbx, -56(%rbp)
	movq	-56(%rbp), %rax
	movq	(%rax), %rax
	movq	(%rax), %rax
	movq	-56(%rbp), %rdx
	movq	%rdx, %rcx
	call	*%rax
	movl	$8, %ecx
	call	_Znwm
	movq	%rax, %rbx
	movq	%rbx, %rcx
	call	_ZN5Bson2C1Ev
	movq	%rbx, -56(%rbp)
	movq	-56(%rbp), %rax
	movq	(%rax), %rax
	movq	(%rax), %rax
	movq	-56(%rbp), %rdx
	movq	%rdx, %rcx
	call	*%rax
	movl	$0, %eax
	addq	$88, %rsp
	popq	%rbx
	popq	%rbp
	ret
	.seh_endproc
	.globl	_ZTV5Bson2
	.section	.rdata$_ZTV5Bson2,"dr"
	.linkonce same_size
	.align 8
_ZTV5Bson2:
	.quad	0
	.quad	_ZTI5Bson2
	.quad	_ZN5Bson26printbEv
	.globl	_ZTV4Bson
	.section	.rdata$_ZTV4Bson,"dr"
	.linkonce same_size
	.align 8
_ZTV4Bson:
	.quad	0
	.quad	_ZTI4Bson
	.quad	_ZN1B6printbEv
	.globl	_ZTV1B
	.section	.rdata$_ZTV1B,"dr"
	.linkonce same_size
	.align 8
_ZTV1B:
	.quad	0
	.quad	_ZTI1B
	.quad	_ZN1B6printbEv
	.globl	_ZTI5Bson2
	.section	.rdata$_ZTI5Bson2,"dr"
	.linkonce same_size
	.align 8
_ZTI5Bson2:
	.quad	_ZTVN10__cxxabiv120__si_class_type_infoE+16
	.quad	_ZTS5Bson2
	.quad	_ZTI1B
	.globl	_ZTS5Bson2
	.section	.rdata$_ZTS5Bson2,"dr"
	.linkonce same_size
_ZTS5Bson2:
	.ascii "5Bson2\0"
	.globl	_ZTI4Bson
	.section	.rdata$_ZTI4Bson,"dr"
	.linkonce same_size
	.align 8
_ZTI4Bson:
	.quad	_ZTVN10__cxxabiv120__si_class_type_infoE+16
	.quad	_ZTS4Bson
	.quad	_ZTI1B
	.globl	_ZTS4Bson
	.section	.rdata$_ZTS4Bson,"dr"
	.linkonce same_size
_ZTS4Bson:
	.ascii "4Bson\0"
	.globl	_ZTI1B
	.section	.rdata$_ZTI1B,"dr"
	.linkonce same_size
	.align 8
_ZTI1B:
	.quad	_ZTVN10__cxxabiv117__class_type_infoE+16
	.quad	_ZTS1B
	.globl	_ZTS1B
	.section	.rdata$_ZTS1B,"dr"
	.linkonce same_size
_ZTS1B:
	.ascii "1B\0"
	.ident	"GCC: (GNU) 5.4.0"
	.def	puts;	.scl	2;	.type	32;	.endef
	.def	printf;	.scl	2;	.type	32;	.endef
	.def	__real__Znwm;	.scl	2;	.type	32;	.endef
	.def	_Znwm;	.scl	2;	.type	32;	.endef
