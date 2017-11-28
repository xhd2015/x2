	.file	"virtual-final.cpp"
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
	.ascii "#A::v4 final--%d\12\0"
	.section	.text$_ZN1A3v4fEv,"x"
	.linkonce discard
	.align 2
	.globl	__ZN1A3v4fEv
	.def	__ZN1A3v4fEv;	.scl	2;	.type	32;	.endef
__ZN1A3v4fEv:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	%ecx, -12(%ebp)
	movl	$2, 4(%esp)
	movl	$LC0, (%esp)
	call	__Z6printfPKcz
	nop
	leave
	ret
	.section .rdata,"dr"
LC1:
	.ascii "#A::v5--%d\12\0"
	.section	.text$_ZN1A2v5Ev,"x"
	.linkonce discard
	.align 2
	.globl	__ZN1A2v5Ev
	.def	__ZN1A2v5Ev;	.scl	2;	.type	32;	.endef
__ZN1A2v5Ev:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	%ecx, -12(%ebp)
	movl	$7, 4(%esp)
	movl	$LC1, (%esp)
	call	__Z6printfPKcz
	nop
	leave
	ret
	.section .rdata,"dr"
LC2:
	.ascii "#B::v0--%d\12\0"
	.section	.text$_ZN1B2v0Ev,"x"
	.linkonce discard
	.align 2
	.globl	__ZN1B2v0Ev
	.def	__ZN1B2v0Ev;	.scl	2;	.type	32;	.endef
__ZN1B2v0Ev:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	%ecx, -12(%ebp)
	movl	$5, 4(%esp)
	movl	$LC2, (%esp)
	call	__Z6printfPKcz
	nop
	leave
	ret
	.section .rdata,"dr"
LC3:
	.ascii "#B::v1--%d\12\0"
	.section	.text$_ZN1B2v1Ev,"x"
	.linkonce discard
	.align 2
	.globl	__ZN1B2v1Ev
	.def	__ZN1B2v1Ev;	.scl	2;	.type	32;	.endef
__ZN1B2v1Ev:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	%ecx, -12(%ebp)
	movl	$3, 4(%esp)
	movl	$LC3, (%esp)
	call	__Z6printfPKcz
	nop
	leave
	ret
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
	movl	$__ZTV1B+8, %eax
	movl	%eax, 8(%esp)
	leal	8(%esp), %eax
	movl	%eax, 12(%esp)
	movl	12(%esp), %eax
	movl	(%eax), %eax
	movl	(%eax), %eax
	movl	12(%esp), %edx
	movl	%edx, %ecx
	call	*%eax
	movl	12(%esp), %eax
	movl	(%eax), %eax
	addl	$4, %eax
	movl	(%eax), %eax
	movl	12(%esp), %edx
	movl	%edx, %ecx
	call	*%eax
	movl	12(%esp), %eax
	movl	%eax, %ecx
	call	__ZN1A3v4fEv
	movl	$0, %eax
	leave
	ret
	.globl	__ZTV1B
	.section	.rdata$_ZTV1B,"dr"
	.linkonce same_size
	.align 4
__ZTV1B:
	.long	0
	.long	__ZTI1B
	.long	__ZN1B2v0Ev
	.long	__ZN1B2v1Ev
	.long	__ZN1A3v4fEv
	.long	__ZN1A2v5Ev
	.globl	__ZTI1B
	.section	.rdata$_ZTI1B,"dr"
	.linkonce same_size
	.align 4
__ZTI1B:
	.long	__ZTVN10__cxxabiv120__si_class_type_infoE+8
	.long	__ZTS1B
	.long	__ZTI1A
	.globl	__ZTS1B
	.section	.rdata$_ZTS1B,"dr"
	.linkonce same_size
__ZTS1B:
	.ascii "1B\0"
	.globl	__ZTI1A
	.section	.rdata$_ZTI1A,"dr"
	.linkonce same_size
	.align 4
__ZTI1A:
	.long	__ZTVN10__cxxabiv117__class_type_infoE+8
	.long	__ZTS1A
	.globl	__ZTS1A
	.section	.rdata$_ZTS1A,"dr"
	.linkonce same_size
__ZTS1A:
	.ascii "1A\0"
	.ident	"GCC: (GNU) 5.4.0"
	.def	___mingw_vprintf;	.scl	2;	.type	32;	.endef
