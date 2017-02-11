	.file	"Descriptor.cpp"
/APP
	.code16gcc 
	
/NO_APP
	.text
	.align 2
	.globl	__ZN10DescriptorC2Ev
	.def	__ZN10DescriptorC2Ev;	.scl	2;	.type	32;	.endef
__ZN10DescriptorC2Ev:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	%ecx, -4(%ebp)
	nop
	leave
	ret
	.globl	__ZN10DescriptorC1Ev
	.def	__ZN10DescriptorC1Ev;	.scl	2;	.type	32;	.endef
	.set	__ZN10DescriptorC1Ev,__ZN10DescriptorC2Ev
	.align 2
	.globl	__ZN10DescriptorD2Ev
	.def	__ZN10DescriptorD2Ev;	.scl	2;	.type	32;	.endef
__ZN10DescriptorD2Ev:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	%ecx, -4(%ebp)
	nop
	leave
	ret
	.globl	__ZN10DescriptorD1Ev
	.def	__ZN10DescriptorD1Ev;	.scl	2;	.type	32;	.endef
	.set	__ZN10DescriptorD1Ev,__ZN10DescriptorD2Ev
	.globl	__ZN17SegmentDescriptor12TYPE_U_STACKE
	.section .rdata,"dr"
	.align 4
__ZN17SegmentDescriptor12TYPE_U_STACKE:
	.long	6
	.globl	__ZN17SegmentDescriptor11TYPE_U_DATAE
	.align 4
__ZN17SegmentDescriptor11TYPE_U_DATAE:
	.long	2
	.globl	__ZN17SegmentDescriptor25TYPE_U_CODE_NONCONFORMINGE
	.align 4
__ZN17SegmentDescriptor25TYPE_U_CODE_NONCONFORMINGE:
	.long	10
	.globl	__ZN17SegmentDescriptor22TYPE_U_CODE_CONFORMINGE
	.align 4
__ZN17SegmentDescriptor22TYPE_U_CODE_CONFORMINGE:
	.long	14
	.align 4
__ZL15TYPE_S_UNUSED_1:
	.space 4
	.align 4
__ZL15TYPE_S_UNUSED_2:
	.long	8
	.align 4
__ZL15TYPE_S_UNUSED_3:
	.long	10
	.align 4
__ZL15TYPE_S_UNUSED_4:
	.long	13
	.align 4
__ZL17TYPE_S_TSS_16_AVL:
	.long	1
	.align 4
__ZL18TYPE_S_TSS_16_BUSY:
	.long	3
	.align 4
__ZL17TYPE_S_TSS_32_AVL:
	.long	9
	.align 4
__ZL18TYPE_S_TSS_32_BUSY:
	.long	11
	.align 4
__ZL18TYPE_S_CALLGATE_16:
	.long	4
	.align 4
__ZL18TYPE_S_CALLGATE_32:
	.long	12
	.align 4
__ZL15TYPE_S_TASKGATE:
	.long	5
	.align 4
__ZL17TYPE_S_INTGATE_16:
	.long	6
	.align 4
__ZL18TYPE_S_TRAPGATE_16:
	.long	7
	.align 4
__ZL17TYPE_S_INTGATE_32:
	.long	14
	.align 4
__ZL18TYPE_S_TRAPGATE_32:
	.long	15
	.globl	__ZN17SegmentDescriptor5DPL_0E
	.align 4
__ZN17SegmentDescriptor5DPL_0E:
	.space 4
	.globl	__ZN17SegmentDescriptor5DPL_1E
	.align 4
__ZN17SegmentDescriptor5DPL_1E:
	.long	1
	.globl	__ZN17SegmentDescriptor5DPL_2E
	.align 4
__ZN17SegmentDescriptor5DPL_2E:
	.long	2
	.globl	__ZN17SegmentDescriptor5DPL_3E
	.align 4
__ZN17SegmentDescriptor5DPL_3E:
	.long	3
	.text
	.align 2
	.globl	__ZN17SegmentDescriptorD2Ev
	.def	__ZN17SegmentDescriptorD2Ev;	.scl	2;	.type	32;	.endef
__ZN17SegmentDescriptorD2Ev:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	%ecx, -4(%ebp)
	movl	-4(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN10DescriptorD2Ev
	nop
	leave
	ret
	.globl	__ZN17SegmentDescriptorD1Ev
	.def	__ZN17SegmentDescriptorD1Ev;	.scl	2;	.type	32;	.endef
	.set	__ZN17SegmentDescriptorD1Ev,__ZN17SegmentDescriptorD2Ev
	.align 2
	.globl	__ZN17SegmentDescriptorC2EPcicc
	.def	__ZN17SegmentDescriptorC2EPcicc;	.scl	2;	.type	32;	.endef
__ZN17SegmentDescriptorC2EPcicc:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$12, %esp
	movl	%ecx, -4(%ebp)
	movl	16(%ebp), %edx
	movl	20(%ebp), %eax
	movb	%dl, -8(%ebp)
	movb	%al, -12(%ebp)
	movl	-4(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN10DescriptorC2Ev
	movl	-4(%ebp), %eax
	movb	$0, 4(%eax)
	movl	-4(%ebp), %eax
	movb	$1, 5(%eax)
	movl	-4(%ebp), %eax
	movb	$0, 6(%eax)
	movl	-4(%ebp), %eax
	movb	$0, 7(%eax)
	movl	-4(%ebp), %eax
	movb	$1, 11(%eax)
	movl	-4(%ebp), %eax
	movzbl	-12(%ebp), %edx
	movb	%dl, 12(%eax)
	movl	-4(%ebp), %eax
	movb	$1, 13(%eax)
	movl	-4(%ebp), %eax
	movzbl	-8(%ebp), %edx
	movb	%dl, 14(%eax)
	movl	-4(%ebp), %eax
	movl	8(%ebp), %edx
	movl	%edx, (%eax)
	movl	-4(%ebp), %eax
	addl	$8, %eax
	movl	12(%ebp), %edx
	movw	%dx, (%eax)
	movl	12(%ebp), %eax
	andl	$983040, %eax
	sarl	$16, %eax
	movl	%eax, %edx
	movl	-4(%ebp), %eax
	movb	%dl, 10(%eax)
	nop
	leave
	ret	$16
	.globl	__ZN17SegmentDescriptorC1EPcicc
	.def	__ZN17SegmentDescriptorC1EPcicc;	.scl	2;	.type	32;	.endef
	.set	__ZN17SegmentDescriptorC1EPcicc,__ZN17SegmentDescriptorC2EPcicc
	.align 2
	.globl	__ZN17SegmentDescriptor6equalsERS_
	.def	__ZN17SegmentDescriptor6equalsERS_;	.scl	2;	.type	32;	.endef
__ZN17SegmentDescriptor6equalsERS_:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	%ecx, -4(%ebp)
	movl	-4(%ebp), %eax
	movl	(%eax), %edx
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	cmpl	%eax, %edx
	jne	L6
	movl	-4(%ebp), %eax
	addl	$8, %eax
	movl	(%eax), %edx
	movl	8(%ebp), %eax
	addl	$8, %eax
	movzwl	(%eax), %eax
	cwtl
	xorl	%edx, %eax
	andl	$1048575, %eax
	testl	%eax, %eax
	jne	L6
	movl	-4(%ebp), %eax
	movzbl	11(%eax), %edx
	movl	8(%ebp), %eax
	movzbl	11(%eax), %eax
	cmpb	%al, %dl
	jne	L6
	movl	-4(%ebp), %eax
	movzbl	6(%eax), %edx
	movl	8(%ebp), %eax
	movzbl	6(%eax), %eax
	cmpb	%al, %dl
	jne	L6
	movl	-4(%ebp), %eax
	movzbl	5(%eax), %edx
	movl	8(%ebp), %eax
	movzbl	5(%eax), %eax
	cmpb	%al, %dl
	jne	L6
	movl	-4(%ebp), %eax
	movzbl	13(%eax), %edx
	movl	8(%ebp), %eax
	movzbl	13(%eax), %eax
	cmpb	%al, %dl
	jne	L6
	movl	-4(%ebp), %eax
	movzbl	14(%eax), %edx
	movl	8(%ebp), %eax
	movzbl	14(%eax), %eax
	cmpb	%al, %dl
	jne	L6
	movl	-4(%ebp), %eax
	movzbl	4(%eax), %edx
	movl	8(%ebp), %eax
	movzbl	4(%eax), %eax
	cmpb	%al, %dl
	jne	L6
	movl	-4(%ebp), %eax
	movzbl	7(%eax), %edx
	movl	8(%ebp), %eax
	movzbl	7(%eax), %eax
	cmpb	%al, %dl
	jne	L6
	movl	-4(%ebp), %eax
	movzbl	12(%eax), %edx
	movl	8(%ebp), %eax
	movzbl	12(%eax), %eax
	cmpb	%al, %dl
	jne	L6
	movl	$1, %eax
	jmp	L7
L6:
	movl	$0, %eax
L7:
	leave
	ret	$4
	.align 2
	.globl	__ZN17SegmentDescriptor13writeToMemoryEiPc
	.def	__ZN17SegmentDescriptor13writeToMemoryEiPc;	.scl	2;	.type	32;	.endef
__ZN17SegmentDescriptor13writeToMemoryEiPc:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$56, %esp
	movl	%ecx, -28(%ebp)
	movl	12(%ebp), %eax
	movl	%eax, -12(%ebp)
	movl	-28(%ebp), %eax
	addl	$8, %eax
	movzwl	(%eax), %eax
	cwtl
	movzwl	%ax, %edx
	movl	-12(%ebp), %eax
	movl	%edx, 8(%esp)
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZN4Util4setwEiii
	addl	$2, -12(%ebp)
	movl	-28(%ebp), %eax
	movl	(%eax), %eax
	movzwl	%ax, %edx
	movl	-12(%ebp), %eax
	movl	%edx, 8(%esp)
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZN4Util4setwEiii
	addl	$2, -12(%ebp)
	movl	-28(%ebp), %eax
	movl	(%eax), %eax
	andl	$16711680, %eax
	sarl	$16, %eax
	movl	%eax, %edx
	movl	-12(%ebp), %eax
	movl	%edx, 8(%esp)
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZN4Util4setbEiii
	addl	$1, -12(%ebp)
	movl	-28(%ebp), %eax
	movzbl	11(%eax), %eax
	movsbl	%al, %eax
	sall	$7, %eax
	movzbl	%al, %edx
	movl	-28(%ebp), %eax
	movzbl	12(%eax), %eax
	movsbl	%al, %eax
	andl	$3, %eax
	sall	$5, %eax
	orl	%eax, %edx
	movl	-28(%ebp), %eax
	movzbl	13(%eax), %eax
	movsbl	%al, %eax
	andl	$1, %eax
	sall	$4, %eax
	orl	%eax, %edx
	movl	-28(%ebp), %eax
	movzbl	14(%eax), %eax
	movsbl	%al, %eax
	andl	$15, %eax
	orl	%eax, %edx
	movl	-12(%ebp), %eax
	movl	%edx, 8(%esp)
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZN4Util4setbEiii
	addl	$1, -12(%ebp)
	movl	-28(%ebp), %eax
	movzbl	4(%eax), %eax
	movsbl	%al, %eax
	sall	$7, %eax
	movzbl	%al, %edx
	movl	-28(%ebp), %eax
	movzbl	5(%eax), %eax
	movsbl	%al, %eax
	andl	$1, %eax
	sall	$6, %eax
	orl	%eax, %edx
	movl	-28(%ebp), %eax
	movzbl	6(%eax), %eax
	movsbl	%al, %eax
	andl	$1, %eax
	sall	$5, %eax
	orl	%eax, %edx
	movl	-28(%ebp), %eax
	movzbl	7(%eax), %eax
	movsbl	%al, %eax
	andl	$1, %eax
	sall	$4, %eax
	orl	%eax, %edx
	movl	-28(%ebp), %eax
	addl	$8, %eax
	movl	(%eax), %eax
	andl	$983040, %eax
	sarl	$16, %eax
	orl	%eax, %edx
	movl	-12(%ebp), %eax
	movl	%edx, 8(%esp)
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZN4Util4setbEiii
	addl	$1, -12(%ebp)
	movl	-28(%ebp), %eax
	movl	(%eax), %eax
	shrl	$24, %eax
	movl	%eax, %edx
	movl	-12(%ebp), %eax
	movl	%edx, 8(%esp)
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZN4Util4setbEiii
	addl	$1, -12(%ebp)
	nop
	leave
	ret	$8
	.align 2
	.globl	__ZN17SegmentDescriptor10fromMemoryEPS_iPc
	.def	__ZN17SegmentDescriptor10fromMemoryEPS_iPc;	.scl	2;	.type	32;	.endef
__ZN17SegmentDescriptor10fromMemoryEPS_iPc:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	8(%ebp), %eax
	addl	$8, %eax
	movl	%eax, -12(%ebp)
	movl	16(%ebp), %eax
	movl	%eax, -16(%ebp)
	movl	-16(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	12(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZN4Util3getEii
	movl	%eax, %edx
	movl	-12(%ebp), %eax
	movw	%dx, (%eax)
	addl	$2, -16(%ebp)
	movl	8(%ebp), %eax
	movl	%eax, -12(%ebp)
	movl	-16(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	12(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZN4Util3getEii
	movl	%eax, %edx
	movl	-12(%ebp), %eax
	movw	%dx, (%eax)
	addl	$2, -16(%ebp)
	movl	8(%ebp), %eax
	addl	$2, %eax
	movl	%eax, -12(%ebp)
	movl	-16(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	12(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZN4Util3getEii
	movl	%eax, %edx
	movl	-12(%ebp), %eax
	movb	%dl, (%eax)
	addl	$1, -16(%ebp)
	movl	8(%ebp), %eax
	movzbl	14(%eax), %eax
	movsbl	%al, %eax
	movl	%eax, -12(%ebp)
	movl	-16(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	12(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZN4Util3getEii
	andl	$15, %eax
	movl	%eax, %edx
	movl	-12(%ebp), %eax
	movb	%dl, (%eax)
	movl	8(%ebp), %eax
	movzbl	13(%eax), %eax
	movsbl	%al, %eax
	movl	%eax, -12(%ebp)
	movl	-16(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	12(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZN4Util3getEii
	andl	$16, %eax
	sarl	$4, %eax
	movl	%eax, %edx
	movl	-12(%ebp), %eax
	movb	%dl, (%eax)
	movl	8(%ebp), %eax
	movzbl	12(%eax), %eax
	movsbl	%al, %eax
	movl	%eax, -12(%ebp)
	movl	-16(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	12(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZN4Util3getEii
	andl	$96, %eax
	sarl	$5, %eax
	movl	%eax, %edx
	movl	-12(%ebp), %eax
	movb	%dl, (%eax)
	movl	8(%ebp), %eax
	movzbl	11(%eax), %eax
	movsbl	%al, %eax
	movl	%eax, -12(%ebp)
	movl	-16(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	12(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZN4Util3getEii
	andl	$128, %eax
	sarl	$7, %eax
	movl	%eax, %edx
	movl	-12(%ebp), %eax
	movb	%dl, (%eax)
	addl	$1, -16(%ebp)
	movl	8(%ebp), %eax
	addl	$8, %eax
	addl	$2, %eax
	movl	%eax, -12(%ebp)
	movl	-16(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	12(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZN4Util3getEii
	andl	$15, %eax
	movl	%eax, %edx
	movl	-12(%ebp), %eax
	movb	%dl, (%eax)
	movl	8(%ebp), %eax
	movzbl	7(%eax), %eax
	movsbl	%al, %eax
	movl	%eax, -12(%ebp)
	movl	-16(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	12(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZN4Util3getEii
	andl	$16, %eax
	sarl	$4, %eax
	movl	%eax, %edx
	movl	-12(%ebp), %eax
	movb	%dl, (%eax)
	movl	8(%ebp), %eax
	movzbl	6(%eax), %eax
	movsbl	%al, %eax
	movl	%eax, -12(%ebp)
	movl	-16(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	12(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZN4Util3getEii
	andl	$32, %eax
	sarl	$5, %eax
	movl	%eax, %edx
	movl	-12(%ebp), %eax
	movb	%dl, (%eax)
	movl	8(%ebp), %eax
	movzbl	5(%eax), %eax
	movsbl	%al, %eax
	movl	%eax, -12(%ebp)
	movl	-16(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	12(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZN4Util3getEii
	andl	$64, %eax
	sarl	$6, %eax
	movl	%eax, %edx
	movl	-12(%ebp), %eax
	movb	%dl, (%eax)
	movl	8(%ebp), %eax
	movzbl	4(%eax), %eax
	movsbl	%al, %eax
	movl	%eax, -12(%ebp)
	movl	-16(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	12(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZN4Util3getEii
	andl	$128, %eax
	sarl	$7, %eax
	movl	%eax, %edx
	movl	-12(%ebp), %eax
	movb	%dl, (%eax)
	addl	$1, -16(%ebp)
	movl	8(%ebp), %eax
	addl	$3, %eax
	movl	%eax, -12(%ebp)
	movl	-16(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	12(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZN4Util3getEii
	movl	%eax, %edx
	movl	-12(%ebp), %eax
	movb	%dl, (%eax)
	addl	$1, -16(%ebp)
	addl	$1, -12(%ebp)
	nop
	leave
	ret
	.ident	"GCC: (GNU) 5.4.0"
	.def	__ZN4Util4setwEiii;	.scl	2;	.type	32;	.endef
	.def	__ZN4Util4setbEiii;	.scl	2;	.type	32;	.endef
	.def	__ZN4Util3getEii;	.scl	2;	.type	32;	.endef
