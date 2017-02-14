	.file	"TSS.cpp"
	.text
	.align 2
	.globl	__ZN3TSSC2Ev
	.def	__ZN3TSSC2Ev;	.scl	2;	.type	32;	.endef
__ZN3TSSC2Ev:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	%ecx, -4(%ebp)
	movl	-4(%ebp), %eax
	addl	$100, %eax
	leal	8(%eax), %edx
	movl	-4(%ebp), %eax
	movl	%edx, 104(%eax)
	movl	-4(%ebp), %eax
	leal	100(%eax), %edx
	movl	-4(%ebp), %eax
	movl	%edx, 108(%eax)
	nop
	leave
	ret
	.globl	__ZN3TSSC1Ev
	.def	__ZN3TSSC1Ev;	.scl	2;	.type	32;	.endef
	.set	__ZN3TSSC1Ev,__ZN3TSSC2Ev
	.align 2
	.globl	__ZN3TSSD2Ev
	.def	__ZN3TSSD2Ev;	.scl	2;	.type	32;	.endef
__ZN3TSSD2Ev:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	%ecx, -4(%ebp)
	nop
	leave
	ret
	.globl	__ZN3TSSD1Ev
	.def	__ZN3TSSD1Ev;	.scl	2;	.type	32;	.endef
	.set	__ZN3TSSD1Ev,__ZN3TSSD2Ev
	.align 2
	.globl	__ZN3TSS13writeToMemoryEii
	.def	__ZN3TSS13writeToMemoryEii;	.scl	2;	.type	32;	.endef
__ZN3TSS13writeToMemoryEii:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$56, %esp
	movl	%ecx, -12(%ebp)
	movl	-12(%ebp), %eax
	movl	%eax, %edx
	movl	$104, 16(%esp)
	movl	12(%ebp), %eax
	movl	%eax, 12(%esp)
	movl	8(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	%edx, 4(%esp)
	movl	$65536, (%esp)
	call	__ZN4Util7memcopyEiiiii
	nop
	leave
	ret	$8
	.align 2
	.globl	__ZN3TSS18ensureReservedZeroEv
	.def	__ZN3TSS18ensureReservedZeroEv;	.scl	2;	.type	32;	.endef
__ZN3TSS18ensureReservedZeroEv:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$68, %esp
	movl	%ecx, -68(%ebp)
	movl	-68(%ebp), %eax
	addl	$2, %eax
	movl	%eax, -52(%ebp)
	movl	-68(%ebp), %eax
	addl	$8, %eax
	addl	$2, %eax
	movl	%eax, -48(%ebp)
	movl	-68(%ebp), %eax
	addl	$16, %eax
	addl	$2, %eax
	movl	%eax, -44(%ebp)
	movl	-68(%ebp), %eax
	addl	$24, %eax
	addl	$2, %eax
	movl	%eax, -40(%ebp)
	movl	-68(%ebp), %eax
	addl	$72, %eax
	addl	$2, %eax
	movl	%eax, -36(%ebp)
	movl	-68(%ebp), %eax
	addl	$76, %eax
	addl	$2, %eax
	movl	%eax, -32(%ebp)
	movl	-68(%ebp), %eax
	addl	$80, %eax
	addl	$2, %eax
	movl	%eax, -28(%ebp)
	movl	-68(%ebp), %eax
	addl	$84, %eax
	addl	$2, %eax
	movl	%eax, -24(%ebp)
	movl	-68(%ebp), %eax
	addl	$88, %eax
	addl	$2, %eax
	movl	%eax, -20(%ebp)
	movl	-68(%ebp), %eax
	addl	$92, %eax
	addl	$2, %eax
	movl	%eax, -16(%ebp)
	movl	-68(%ebp), %eax
	addl	$96, %eax
	addl	$2, %eax
	movl	%eax, -12(%ebp)
	movl	$11, %eax
	movl	%eax, -8(%ebp)
	movl	$0, -4(%ebp)
L6:
	movl	-4(%ebp), %eax
	cmpl	-8(%ebp), %eax
	je	L5
	movl	-4(%ebp), %eax
	movl	-52(%ebp,%eax,4), %eax
	movw	$0, (%eax)
	addl	$1, -4(%ebp)
	jmp	L6
L5:
	movl	-68(%ebp), %eax
	addl	$100, %eax
	movl	-68(%ebp), %edx
	addl	$100, %edx
	movzwl	(%edx), %edx
	andl	$1, %edx
	movw	%dx, (%eax)
	nop
	leave
	ret
	.align 2
	.globl	__ZN3TSS10fromMemoryERS_ii
	.def	__ZN3TSS10fromMemoryERS_ii;	.scl	2;	.type	32;	.endef
__ZN3TSS10fromMemoryERS_ii:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	8(%ebp), %eax
	movl	$104, 16(%esp)
	movl	%eax, 12(%esp)
	movl	$65536, 8(%esp)
	movl	16(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	12(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZN4Util7memcopyEiiiii
	movl	8(%ebp), %ecx
	call	__ZN3TSS18ensureReservedZeroEv
	nop
	leave
	ret
	.ident	"GCC: (GNU) 5.4.0"
	.def	__ZN4Util7memcopyEiiiii;	.scl	2;	.type	32;	.endef
