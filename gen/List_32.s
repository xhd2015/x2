	.file	"List.cpp"
	.section	.text$_ZN8ListNodeIiEC2ERKiPS0_S3_,"x"
	.linkonce discard
	.align 2
	.globl	__ZN8ListNodeIiEC2ERKiPS0_S3_
	.def	__ZN8ListNodeIiEC2ERKiPS0_S3_;	.scl	2;	.type	32;	.endef
__ZN8ListNodeIiEC2ERKiPS0_S3_:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	%ecx, -12(%ebp)
	movl	-12(%ebp), %eax
	movl	$-1, (%esp)
	movl	%eax, %ecx
	call	__ZN16SimpleMemoryNodeC2Ei
	subl	$4, %esp
	movl	8(%ebp), %eax
	movl	(%eax), %edx
	movl	-12(%ebp), %eax
	movl	%edx, 4(%eax)
	movl	-12(%ebp), %eax
	movl	12(%ebp), %edx
	movl	%edx, 8(%eax)
	movl	-12(%ebp), %eax
	movl	16(%ebp), %edx
	movl	%edx, 12(%eax)
	nop
	leave
	ret	$12
	.section	.text$_ZN8ListNodeIiEC1ERKiPS0_S3_,"x"
	.linkonce discard
	.align 2
	.globl	__ZN8ListNodeIiEC1ERKiPS0_S3_
	.def	__ZN8ListNodeIiEC1ERKiPS0_S3_;	.scl	2;	.type	32;	.endef
__ZN8ListNodeIiEC1ERKiPS0_S3_:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	%ecx, -12(%ebp)
	movl	-12(%ebp), %eax
	movl	$-1, (%esp)
	movl	%eax, %ecx
	call	__ZN16SimpleMemoryNodeC2Ei
	subl	$4, %esp
	movl	8(%ebp), %eax
	movl	(%eax), %edx
	movl	-12(%ebp), %eax
	movl	%edx, 4(%eax)
	movl	-12(%ebp), %eax
	movl	12(%ebp), %edx
	movl	%edx, 8(%eax)
	movl	-12(%ebp), %eax
	movl	16(%ebp), %edx
	movl	%edx, 12(%eax)
	nop
	leave
	ret	$12
	.section	.text$_ZN8ListNodeIiE4initERKiPS0_S3_,"x"
	.linkonce discard
	.align 2
	.globl	__ZN8ListNodeIiE4initERKiPS0_S3_
	.def	__ZN8ListNodeIiE4initERKiPS0_S3_;	.scl	2;	.type	32;	.endef
__ZN8ListNodeIiE4initERKiPS0_S3_:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	%ecx, -4(%ebp)
	movl	8(%ebp), %eax
	movl	(%eax), %edx
	movl	-4(%ebp), %eax
	movl	%edx, 4(%eax)
	movl	-4(%ebp), %eax
	movl	12(%ebp), %edx
	movl	%edx, 8(%eax)
	movl	-4(%ebp), %eax
	movl	16(%ebp), %edx
	movl	%edx, 12(%eax)
	movl	-4(%ebp), %eax
	leave
	ret	$12
	.section	.text$_ZN8ListNodeIiED2Ev,"x"
	.linkonce discard
	.align 2
	.globl	__ZN8ListNodeIiED2Ev
	.def	__ZN8ListNodeIiED2Ev;	.scl	2;	.type	32;	.endef
__ZN8ListNodeIiED2Ev:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	%ecx, -12(%ebp)
	movl	-12(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN16SimpleMemoryNodeD2Ev
	nop
	leave
	ret
	.section	.text$_ZN8ListNodeIiED1Ev,"x"
	.linkonce discard
	.align 2
	.globl	__ZN8ListNodeIiED1Ev
	.def	__ZN8ListNodeIiED1Ev;	.scl	2;	.type	32;	.endef
__ZN8ListNodeIiED1Ev:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	%ecx, -12(%ebp)
	movl	-12(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN16SimpleMemoryNodeD2Ev
	nop
	leave
	ret
	.section	.text$_ZN8ListNodeIiE7getDataEv,"x"
	.linkonce discard
	.align 2
	.globl	__ZN8ListNodeIiE7getDataEv
	.def	__ZN8ListNodeIiE7getDataEv;	.scl	2;	.type	32;	.endef
__ZN8ListNodeIiE7getDataEv:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	%ecx, -4(%ebp)
	movl	-4(%ebp), %eax
	addl	$4, %eax
	leave
	ret
	.section	.text$_ZN8ListNodeIiE7setDataERKi,"x"
	.linkonce discard
	.align 2
	.globl	__ZN8ListNodeIiE7setDataERKi
	.def	__ZN8ListNodeIiE7setDataERKi;	.scl	2;	.type	32;	.endef
__ZN8ListNodeIiE7setDataERKi:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	%ecx, -4(%ebp)
	movl	8(%ebp), %eax
	movl	(%eax), %edx
	movl	-4(%ebp), %eax
	movl	%edx, 4(%eax)
	nop
	leave
	ret	$4
	.section	.text$_ZN8ListNodeIiE7getNextEv,"x"
	.linkonce discard
	.align 2
	.globl	__ZN8ListNodeIiE7getNextEv
	.def	__ZN8ListNodeIiE7getNextEv;	.scl	2;	.type	32;	.endef
__ZN8ListNodeIiE7getNextEv:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	%ecx, -4(%ebp)
	movl	-4(%ebp), %eax
	movl	8(%eax), %eax
	leave
	ret
	.section	.text$_ZN8ListNodeIiE11getPreviousEv,"x"
	.linkonce discard
	.align 2
	.globl	__ZN8ListNodeIiE11getPreviousEv
	.def	__ZN8ListNodeIiE11getPreviousEv;	.scl	2;	.type	32;	.endef
__ZN8ListNodeIiE11getPreviousEv:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	%ecx, -4(%ebp)
	movl	-4(%ebp), %eax
	movl	12(%eax), %eax
	leave
	ret
	.section	.text$_ZN8ListNodeIiE7setNextEPS0_,"x"
	.linkonce discard
	.align 2
	.globl	__ZN8ListNodeIiE7setNextEPS0_
	.def	__ZN8ListNodeIiE7setNextEPS0_;	.scl	2;	.type	32;	.endef
__ZN8ListNodeIiE7setNextEPS0_:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	%ecx, -4(%ebp)
	movl	-4(%ebp), %eax
	movl	8(%ebp), %edx
	movl	%edx, 8(%eax)
	nop
	leave
	ret	$4
	.section	.text$_ZN8ListNodeIiE11setPreviousEPS0_,"x"
	.linkonce discard
	.align 2
	.globl	__ZN8ListNodeIiE11setPreviousEPS0_
	.def	__ZN8ListNodeIiE11setPreviousEPS0_;	.scl	2;	.type	32;	.endef
__ZN8ListNodeIiE11setPreviousEPS0_:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	%ecx, -4(%ebp)
	movl	-4(%ebp), %eax
	movl	8(%ebp), %edx
	movl	%edx, 12(%eax)
	nop
	leave
	ret	$4
	.section	.text$_ZN8ListNodeIiE10removeNextEv,"x"
	.linkonce discard
	.align 2
	.globl	__ZN8ListNodeIiE10removeNextEv
	.def	__ZN8ListNodeIiE10removeNextEv;	.scl	2;	.type	32;	.endef
__ZN8ListNodeIiE10removeNextEv:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$52, %esp
	movl	%ecx, -52(%ebp)
	movl	-52(%ebp), %eax
	movl	%eax, -12(%ebp)
	movl	-12(%ebp), %eax
	movl	8(%eax), %eax
	movl	%eax, -8(%ebp)
	movl	-52(%ebp), %eax
	movl	%eax, -32(%ebp)
	movl	-32(%ebp), %eax
	movl	8(%eax), %eax
	testl	%eax, %eax
	setne	%al
	movzbl	%al, %eax
	testl	%eax, %eax
	setne	%al
	testb	%al, %al
	je	L19
	movl	-8(%ebp), %eax
	movl	%eax, -20(%ebp)
	movl	-20(%ebp), %eax
	movl	8(%eax), %eax
	movl	-52(%ebp), %edx
	movl	%edx, -24(%ebp)
	movl	%eax, -36(%ebp)
	movl	-24(%ebp), %eax
	movl	-36(%ebp), %edx
	movl	%edx, 8(%eax)
	movl	-8(%ebp), %eax
	movl	%eax, -4(%ebp)
	movl	-4(%ebp), %eax
	movl	8(%eax), %eax
	testl	%eax, %eax
	setne	%al
	movzbl	%al, %eax
	testl	%eax, %eax
	setne	%al
	testb	%al, %al
	je	L19
	movl	-8(%ebp), %eax
	movl	%eax, -28(%ebp)
	movl	-28(%ebp), %eax
	movl	8(%eax), %eax
	movl	%eax, -16(%ebp)
	movl	-52(%ebp), %eax
	movl	%eax, -40(%ebp)
	movl	-16(%ebp), %eax
	movl	-40(%ebp), %edx
	movl	%edx, 12(%eax)
L19:
	movl	-8(%ebp), %eax
	leave
	ret
	.section	.text$_ZN8ListNodeIiE14removePreviousEv,"x"
	.linkonce discard
	.align 2
	.globl	__ZN8ListNodeIiE14removePreviousEv
	.def	__ZN8ListNodeIiE14removePreviousEv;	.scl	2;	.type	32;	.endef
__ZN8ListNodeIiE14removePreviousEv:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$52, %esp
	movl	%ecx, -52(%ebp)
	movl	-52(%ebp), %eax
	movl	%eax, -12(%ebp)
	movl	-12(%ebp), %eax
	movl	12(%eax), %eax
	movl	%eax, -8(%ebp)
	movl	-52(%ebp), %eax
	movl	%eax, -32(%ebp)
	movl	-32(%ebp), %eax
	movl	12(%eax), %eax
	testl	%eax, %eax
	setne	%al
	movzbl	%al, %eax
	testl	%eax, %eax
	setne	%al
	testb	%al, %al
	je	L27
	movl	-8(%ebp), %eax
	movl	%eax, -20(%ebp)
	movl	-20(%ebp), %eax
	movl	12(%eax), %eax
	movl	-52(%ebp), %edx
	movl	%edx, -24(%ebp)
	movl	%eax, -36(%ebp)
	movl	-24(%ebp), %eax
	movl	-36(%ebp), %edx
	movl	%edx, 12(%eax)
	movl	-8(%ebp), %eax
	movl	%eax, -4(%ebp)
	movl	-4(%ebp), %eax
	movl	12(%eax), %eax
	testl	%eax, %eax
	setne	%al
	movzbl	%al, %eax
	testl	%eax, %eax
	setne	%al
	testb	%al, %al
	je	L27
	movl	-8(%ebp), %eax
	movl	%eax, -28(%ebp)
	movl	-28(%ebp), %eax
	movl	12(%eax), %eax
	movl	%eax, -16(%ebp)
	movl	-52(%ebp), %eax
	movl	%eax, -40(%ebp)
	movl	-16(%ebp), %eax
	movl	-40(%ebp), %edx
	movl	%edx, 8(%eax)
L27:
	movl	-8(%ebp), %eax
	leave
	ret
	.section	.text$_ZN8ListNodeIiE10insertNextEPS0_,"x"
	.linkonce discard
	.align 2
	.globl	__ZN8ListNodeIiE10insertNextEPS0_
	.def	__ZN8ListNodeIiE10insertNextEPS0_;	.scl	2;	.type	32;	.endef
__ZN8ListNodeIiE10insertNextEPS0_:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$52, %esp
	movl	%ecx, -52(%ebp)
	cmpl	$0, 8(%ebp)
	je	L36
	movl	-52(%ebp), %eax
	movl	%eax, -24(%ebp)
	movl	-24(%ebp), %eax
	movl	8(%eax), %eax
	movl	%eax, -8(%ebp)
	cmpl	$0, -8(%ebp)
	je	L35
	movl	-8(%ebp), %eax
	movl	%eax, -4(%ebp)
	movl	8(%ebp), %eax
	movl	%eax, -28(%ebp)
	movl	-4(%ebp), %eax
	movl	-28(%ebp), %edx
	movl	%edx, 12(%eax)
L35:
	movl	8(%ebp), %eax
	movl	%eax, -16(%ebp)
	movl	-52(%ebp), %eax
	movl	%eax, -40(%ebp)
	movl	-16(%ebp), %eax
	movl	-40(%ebp), %edx
	movl	%edx, 12(%eax)
	movl	8(%ebp), %eax
	movl	%eax, -20(%ebp)
	movl	-8(%ebp), %eax
	movl	%eax, -36(%ebp)
	movl	-20(%ebp), %eax
	movl	-36(%ebp), %edx
	movl	%edx, 8(%eax)
	movl	-52(%ebp), %eax
	movl	%eax, -12(%ebp)
	movl	8(%ebp), %eax
	movl	%eax, -32(%ebp)
	movl	-12(%ebp), %eax
	movl	-32(%ebp), %edx
	movl	%edx, 8(%eax)
L36:
	nop
	leave
	ret	$4
	.section	.text$_ZN8ListNodeIiE14insertPreviousEPS0_,"x"
	.linkonce discard
	.align 2
	.globl	__ZN8ListNodeIiE14insertPreviousEPS0_
	.def	__ZN8ListNodeIiE14insertPreviousEPS0_;	.scl	2;	.type	32;	.endef
__ZN8ListNodeIiE14insertPreviousEPS0_:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$52, %esp
	movl	%ecx, -52(%ebp)
	cmpl	$0, 8(%ebp)
	je	L41
	movl	-52(%ebp), %eax
	movl	%eax, -24(%ebp)
	movl	-24(%ebp), %eax
	movl	12(%eax), %eax
	movl	%eax, -8(%ebp)
	cmpl	$0, -8(%ebp)
	je	L40
	movl	-8(%ebp), %eax
	movl	%eax, -4(%ebp)
	movl	8(%ebp), %eax
	movl	%eax, -28(%ebp)
	movl	-4(%ebp), %eax
	movl	-28(%ebp), %edx
	movl	%edx, 8(%eax)
L40:
	movl	8(%ebp), %eax
	movl	%eax, -16(%ebp)
	movl	-52(%ebp), %eax
	movl	%eax, -40(%ebp)
	movl	-16(%ebp), %eax
	movl	-40(%ebp), %edx
	movl	%edx, 8(%eax)
	movl	8(%ebp), %eax
	movl	%eax, -20(%ebp)
	movl	-8(%ebp), %eax
	movl	%eax, -36(%ebp)
	movl	-20(%ebp), %eax
	movl	-36(%ebp), %edx
	movl	%edx, 12(%eax)
	movl	-52(%ebp), %eax
	movl	%eax, -12(%ebp)
	movl	8(%ebp), %eax
	movl	%eax, -32(%ebp)
	movl	-12(%ebp), %eax
	movl	-32(%ebp), %edx
	movl	%edx, 12(%eax)
L41:
	nop
	leave
	ret	$4
	.section	.text$_ZN8ListNodeIiE7hasNextEv,"x"
	.linkonce discard
	.align 2
	.globl	__ZN8ListNodeIiE7hasNextEv
	.def	__ZN8ListNodeIiE7hasNextEv;	.scl	2;	.type	32;	.endef
__ZN8ListNodeIiE7hasNextEv:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	%ecx, -4(%ebp)
	movl	-4(%ebp), %eax
	movl	8(%eax), %eax
	testl	%eax, %eax
	setne	%al
	movzbl	%al, %eax
	leave
	ret
	.section	.text$_ZN8ListNodeIiE11hasPreviousEv,"x"
	.linkonce discard
	.align 2
	.globl	__ZN8ListNodeIiE11hasPreviousEv
	.def	__ZN8ListNodeIiE11hasPreviousEv;	.scl	2;	.type	32;	.endef
__ZN8ListNodeIiE11hasPreviousEv:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	%ecx, -4(%ebp)
	movl	-4(%ebp), %eax
	movl	12(%eax), %eax
	testl	%eax, %eax
	setne	%al
	movzbl	%al, %eax
	leave
	ret
	.section	.text$_ZN10LinkedListIiEC2EP19SimpleMemoryManagerI8ListNodeIiEE,"x"
	.linkonce discard
	.align 2
	.globl	__ZN10LinkedListIiEC2EP19SimpleMemoryManagerI8ListNodeIiEE
	.def	__ZN10LinkedListIiEC2EP19SimpleMemoryManagerI8ListNodeIiEE;	.scl	2;	.type	32;	.endef
__ZN10LinkedListIiEC2EP19SimpleMemoryManagerI8ListNodeIiEE:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	%ecx, -12(%ebp)
	movl	-12(%ebp), %eax
	movl	8(%ebp), %edx
	movl	%edx, (%esp)
	movl	%eax, %ecx
	call	__ZN10LinkedListIiE4initEP19SimpleMemoryManagerI8ListNodeIiEE
	subl	$4, %esp
	nop
	leave
	ret	$4
	.section	.text$_ZN10LinkedListIiEC1EP19SimpleMemoryManagerI8ListNodeIiEE,"x"
	.linkonce discard
	.align 2
	.globl	__ZN10LinkedListIiEC1EP19SimpleMemoryManagerI8ListNodeIiEE
	.def	__ZN10LinkedListIiEC1EP19SimpleMemoryManagerI8ListNodeIiEE;	.scl	2;	.type	32;	.endef
__ZN10LinkedListIiEC1EP19SimpleMemoryManagerI8ListNodeIiEE:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	%ecx, -12(%ebp)
	movl	-12(%ebp), %eax
	movl	8(%ebp), %edx
	movl	%edx, (%esp)
	movl	%eax, %ecx
	call	__ZN10LinkedListIiE4initEP19SimpleMemoryManagerI8ListNodeIiEE
	subl	$4, %esp
	nop
	leave
	ret	$4
	.section	.text$_ZN10LinkedListIiE4initEP19SimpleMemoryManagerI8ListNodeIiEE,"x"
	.linkonce discard
	.align 2
	.globl	__ZN10LinkedListIiE4initEP19SimpleMemoryManagerI8ListNodeIiEE
	.def	__ZN10LinkedListIiE4initEP19SimpleMemoryManagerI8ListNodeIiEE;	.scl	2;	.type	32;	.endef
__ZN10LinkedListIiE4initEP19SimpleMemoryManagerI8ListNodeIiEE:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$56, %esp
	movl	%ecx, -28(%ebp)
	movl	-28(%ebp), %eax
	movl	$0, 12(%eax)
	movl	-28(%ebp), %eax
	movl	8(%ebp), %edx
	movl	%edx, (%eax)
	movl	-28(%ebp), %eax
	movl	(%eax), %eax
	movl	%eax, %ecx
	call	__ZN19SimpleMemoryManagerI8ListNodeIiEE6getNewEv
	movl	%eax, %edx
	movl	-28(%ebp), %eax
	movl	%edx, 4(%eax)
	movl	-28(%ebp), %eax
	movl	(%eax), %eax
	movl	%eax, %ecx
	call	__ZN19SimpleMemoryManagerI8ListNodeIiEE6getNewEv
	movl	%eax, %edx
	movl	-28(%ebp), %eax
	movl	%edx, 8(%eax)
	movl	$0, -16(%ebp)
	movl	-28(%ebp), %eax
	movl	4(%eax), %eax
	movl	$0, 8(%esp)
	movl	$0, 4(%esp)
	leal	-16(%ebp), %edx
	movl	%edx, (%esp)
	movl	%eax, %ecx
	call	__ZN8ListNodeIiE4initERKiPS0_S3_
	subl	$12, %esp
	movl	-28(%ebp), %eax
	movl	4(%eax), %edx
	movl	$0, -12(%ebp)
	movl	-28(%ebp), %eax
	movl	8(%eax), %eax
	movl	$0, 8(%esp)
	movl	%edx, 4(%esp)
	leal	-12(%ebp), %edx
	movl	%edx, (%esp)
	movl	%eax, %ecx
	call	__ZN8ListNodeIiE4initERKiPS0_S3_
	subl	$12, %esp
	nop
	leave
	ret	$4
	.section	.text$_ZN10LinkedListIiED2Ev,"x"
	.linkonce discard
	.align 2
	.globl	__ZN10LinkedListIiED2Ev
	.def	__ZN10LinkedListIiED2Ev;	.scl	2;	.type	32;	.endef
__ZN10LinkedListIiED2Ev:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	%ecx, -4(%ebp)
	nop
	leave
	ret
	.section	.text$_ZN10LinkedListIiED1Ev,"x"
	.linkonce discard
	.align 2
	.globl	__ZN10LinkedListIiED1Ev
	.def	__ZN10LinkedListIiED1Ev;	.scl	2;	.type	32;	.endef
__ZN10LinkedListIiED1Ev:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	%ecx, -4(%ebp)
	nop
	leave
	ret
	.section	.text$_ZN10LinkedListIiE8getFirstEv,"x"
	.linkonce discard
	.align 2
	.globl	__ZN10LinkedListIiE8getFirstEv
	.def	__ZN10LinkedListIiE8getFirstEv;	.scl	2;	.type	32;	.endef
__ZN10LinkedListIiE8getFirstEv:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$20, %esp
	movl	%ecx, -20(%ebp)
	movl	-20(%ebp), %eax
	movl	4(%eax), %eax
	movl	%eax, -4(%ebp)
	movl	-4(%ebp), %eax
	movl	8(%eax), %eax
	nop
	leave
	ret
	.section	.text$_ZN10LinkedListIiE7getLastEv,"x"
	.linkonce discard
	.align 2
	.globl	__ZN10LinkedListIiE7getLastEv
	.def	__ZN10LinkedListIiE7getLastEv;	.scl	2;	.type	32;	.endef
__ZN10LinkedListIiE7getLastEv:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$20, %esp
	movl	%ecx, -20(%ebp)
	movl	-20(%ebp), %eax
	movl	8(%eax), %eax
	movl	%eax, -4(%ebp)
	movl	-4(%ebp), %eax
	movl	8(%eax), %eax
	nop
	leave
	ret
	.section	.text$_ZN10LinkedListIiE6appendERKi,"x"
	.linkonce discard
	.align 2
	.globl	__ZN10LinkedListIiE6appendERKi
	.def	__ZN10LinkedListIiE6appendERKi;	.scl	2;	.type	32;	.endef
__ZN10LinkedListIiE6appendERKi:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$72, %esp
	movl	%ecx, -44(%ebp)
	movl	-44(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN10LinkedListIiE7getLastEv
	movl	%eax, -12(%ebp)
	movl	-44(%ebp), %eax
	movl	(%eax), %eax
	movl	%eax, %ecx
	call	__ZN19SimpleMemoryManagerI8ListNodeIiEE6getNewEv
	movl	%eax, -16(%ebp)
	movl	-12(%ebp), %eax
	movl	%eax, -20(%ebp)
	movl	-20(%ebp), %eax
	movl	8(%eax), %edx
	movl	-16(%ebp), %eax
	movl	-12(%ebp), %ecx
	movl	%ecx, 8(%esp)
	movl	%edx, 4(%esp)
	movl	8(%ebp), %edx
	movl	%edx, (%esp)
	movl	%eax, %ecx
	call	__ZN8ListNodeIiE4initERKiPS0_S3_
	subl	$12, %esp
	movl	-12(%ebp), %eax
	movl	%eax, -24(%ebp)
	movl	-16(%ebp), %eax
	movl	%eax, -36(%ebp)
	movl	-24(%ebp), %eax
	movl	-36(%ebp), %edx
	movl	%edx, 8(%eax)
	movl	-44(%ebp), %eax
	movl	8(%eax), %eax
	movl	%eax, -28(%ebp)
	movl	-16(%ebp), %eax
	movl	%eax, -32(%ebp)
	movl	-28(%ebp), %eax
	movl	-32(%ebp), %edx
	movl	%edx, 8(%eax)
	movl	-44(%ebp), %eax
	movl	12(%eax), %eax
	leal	1(%eax), %edx
	movl	-44(%ebp), %eax
	movl	%edx, 12(%eax)
	movl	-16(%ebp), %eax
	leave
	ret	$4
	.section	.text$_ZN10LinkedListIiE10appendHeadERKi,"x"
	.linkonce discard
	.align 2
	.globl	__ZN10LinkedListIiE10appendHeadERKi
	.def	__ZN10LinkedListIiE10appendHeadERKi;	.scl	2;	.type	32;	.endef
__ZN10LinkedListIiE10appendHeadERKi:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	pushl	%ebx
	subl	$48, %esp
	movl	%ecx, -28(%ebp)
	movl	-28(%ebp), %eax
	movl	4(%eax), %esi
	movl	-28(%ebp), %eax
	movl	4(%eax), %eax
	movl	%eax, -16(%ebp)
	movl	-16(%ebp), %eax
	movl	8(%eax), %ebx
	movl	-28(%ebp), %eax
	movl	(%eax), %eax
	movl	%eax, %ecx
	call	__ZN19SimpleMemoryManagerI8ListNodeIiEE6getNewEv
	movl	%eax, %edx
	movl	%esi, 8(%esp)
	movl	%ebx, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	movl	%edx, %ecx
	call	__ZN8ListNodeIiE4initERKiPS0_S3_
	subl	$12, %esp
	movl	%eax, -12(%ebp)
	movl	-28(%ebp), %eax
	movl	4(%eax), %eax
	movl	%eax, -20(%ebp)
	movl	-12(%ebp), %eax
	movl	%eax, -24(%ebp)
	movl	-20(%ebp), %eax
	movl	-24(%ebp), %edx
	movl	%edx, 8(%eax)
	movl	-12(%ebp), %eax
	leal	-8(%ebp), %esp
	popl	%ebx
	popl	%esi
	popl	%ebp
	ret	$4
	.section	.text$_ZN10LinkedListIiE6removeEv,"x"
	.linkonce discard
	.align 2
	.globl	__ZN10LinkedListIiE6removeEv
	.def	__ZN10LinkedListIiE6removeEv;	.scl	2;	.type	32;	.endef
__ZN10LinkedListIiE6removeEv:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$36, %esp
	movl	%ecx, -36(%ebp)
	movl	-36(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN10LinkedListIiE7getLastEv
	movl	%eax, -4(%ebp)
	movl	-36(%ebp), %eax
	movl	4(%eax), %eax
	cmpl	-4(%ebp), %eax
	je	L64
	movl	-4(%ebp), %eax
	movl	%eax, -12(%ebp)
	movl	-12(%ebp), %eax
	movl	12(%eax), %eax
	movl	%eax, -8(%ebp)
	movl	-36(%ebp), %eax
	movl	8(%eax), %eax
	movl	%eax, -16(%ebp)
	movl	-8(%ebp), %eax
	movl	%eax, -28(%ebp)
	movl	-16(%ebp), %eax
	movl	-28(%ebp), %edx
	movl	%edx, 8(%eax)
	movl	-8(%ebp), %eax
	movl	%eax, -20(%ebp)
	movl	$0, -24(%ebp)
	movl	-20(%ebp), %eax
	movl	-24(%ebp), %edx
	movl	%edx, 8(%eax)
	movl	-36(%ebp), %eax
	movl	12(%eax), %eax
	leal	-1(%eax), %edx
	movl	-36(%ebp), %eax
	movl	%edx, 12(%eax)
	movl	-4(%ebp), %eax
	jmp	L66
L64:
	movl	$0, %eax
L66:
	leave
	ret
	.section	.text$_ZN10LinkedListIiE10removeHeadEv,"x"
	.linkonce discard
	.align 2
	.globl	__ZN10LinkedListIiE10removeHeadEv
	.def	__ZN10LinkedListIiE10removeHeadEv;	.scl	2;	.type	32;	.endef
__ZN10LinkedListIiE10removeHeadEv:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$52, %esp
	movl	%ecx, -52(%ebp)
	movl	-52(%ebp), %eax
	movl	4(%eax), %eax
	movl	%eax, -12(%ebp)
	movl	-12(%ebp), %eax
	movl	8(%eax), %eax
	movl	%eax, -8(%ebp)
	movl	-8(%ebp), %eax
	movl	%eax, -28(%ebp)
	movl	-28(%ebp), %eax
	movl	8(%eax), %eax
	testl	%eax, %eax
	setne	%al
	movzbl	%al, %eax
	testl	%eax, %eax
	setne	%al
	testb	%al, %al
	je	L70
	movl	-52(%ebp), %eax
	movl	4(%eax), %eax
	movl	-8(%ebp), %edx
	movl	%edx, -20(%ebp)
	movl	-20(%ebp), %edx
	movl	8(%edx), %edx
	movl	%edx, -4(%ebp)
	movl	%eax, -32(%ebp)
	movl	-4(%ebp), %eax
	movl	-32(%ebp), %edx
	movl	%edx, 12(%eax)
L70:
	movl	-8(%ebp), %eax
	movl	%eax, -24(%ebp)
	movl	-24(%ebp), %eax
	movl	8(%eax), %eax
	movl	-52(%ebp), %edx
	movl	4(%edx), %edx
	movl	%edx, -16(%ebp)
	movl	%eax, -36(%ebp)
	movl	-16(%ebp), %eax
	movl	-36(%ebp), %edx
	movl	%edx, 8(%eax)
	movl	-8(%ebp), %eax
	leave
	ret
	.section	.text$_ZN10LinkedListIiE7refreshEv,"x"
	.linkonce discard
	.align 2
	.globl	__ZN10LinkedListIiE7refreshEv
	.def	__ZN10LinkedListIiE7refreshEv;	.scl	2;	.type	32;	.endef
__ZN10LinkedListIiE7refreshEv:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$36, %esp
	movl	%ecx, -36(%ebp)
	movl	-36(%ebp), %eax
	movl	$0, 12(%eax)
	movl	-36(%ebp), %eax
	movl	4(%eax), %eax
	movl	%eax, -4(%ebp)
L78:
	movl	-4(%ebp), %eax
	movl	%eax, -16(%ebp)
	movl	-16(%ebp), %eax
	movl	8(%eax), %eax
	testl	%eax, %eax
	setne	%al
	movzbl	%al, %eax
	testl	%eax, %eax
	setne	%al
	testb	%al, %al
	je	L76
	movl	-4(%ebp), %eax
	movl	%eax, -8(%ebp)
	movl	-8(%ebp), %eax
	movl	8(%eax), %eax
	movl	%eax, -4(%ebp)
	movl	-36(%ebp), %eax
	movl	12(%eax), %eax
	leal	1(%eax), %edx
	movl	-36(%ebp), %eax
	movl	%edx, 12(%eax)
	jmp	L78
L76:
	movl	-36(%ebp), %eax
	movl	8(%eax), %eax
	movl	%eax, -12(%ebp)
	movl	-4(%ebp), %eax
	movl	%eax, -20(%ebp)
	movl	-12(%ebp), %eax
	movl	-20(%ebp), %edx
	movl	%edx, 8(%eax)
	nop
	leave
	ret
	.section	.text$_ZN10LinkedListIiE7getSizeEv,"x"
	.linkonce discard
	.align 2
	.globl	__ZN10LinkedListIiE7getSizeEv
	.def	__ZN10LinkedListIiE7getSizeEv;	.scl	2;	.type	32;	.endef
__ZN10LinkedListIiE7getSizeEv:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	%ecx, -4(%ebp)
	movl	-4(%ebp), %eax
	movl	12(%eax), %eax
	leave
	ret
	.section	.text$_ZN10LinkedListIiE4freeEv,"x"
	.linkonce discard
	.align 2
	.globl	__ZN10LinkedListIiE4freeEv
	.def	__ZN10LinkedListIiE4freeEv;	.scl	2;	.type	32;	.endef
__ZN10LinkedListIiE4freeEv:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	%ecx, -12(%ebp)
	movl	-12(%ebp), %eax
	movl	8(%eax), %edx
	movl	-12(%ebp), %eax
	movl	(%eax), %eax
	movl	%edx, (%esp)
	movl	%eax, %ecx
	call	__ZN19SimpleMemoryManagerI8ListNodeIiEE8withdrawEPS1_
	subl	$4, %esp
	movl	-12(%ebp), %eax
	movl	4(%eax), %edx
	movl	-12(%ebp), %eax
	movl	(%eax), %eax
	movl	%edx, (%esp)
	movl	%eax, %ecx
	call	__ZN19SimpleMemoryManagerI8ListNodeIiEE8freeNextEPS1_
	subl	$4, %esp
	nop
	leave
	ret
	.section	.text$_ZN8ListNodeI16MemoryDescriptorEC2ERKS0_PS1_S4_,"x"
	.linkonce discard
	.align 2
	.globl	__ZN8ListNodeI16MemoryDescriptorEC2ERKS0_PS1_S4_
	.def	__ZN8ListNodeI16MemoryDescriptorEC2ERKS0_PS1_S4_;	.scl	2;	.type	32;	.endef
__ZN8ListNodeI16MemoryDescriptorEC2ERKS0_PS1_S4_:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	%ecx, -12(%ebp)
	movl	-12(%ebp), %eax
	movl	$-1, (%esp)
	movl	%eax, %ecx
	call	__ZN16SimpleMemoryNodeC2Ei
	subl	$4, %esp
	movl	-12(%ebp), %eax
	movl	8(%ebp), %edx
	movl	(%edx), %ecx
	movl	%ecx, 4(%eax)
	movl	4(%edx), %ecx
	movl	%ecx, 8(%eax)
	movl	8(%edx), %edx
	movl	%edx, 12(%eax)
	movl	-12(%ebp), %eax
	movl	12(%ebp), %edx
	movl	%edx, 16(%eax)
	movl	-12(%ebp), %eax
	movl	16(%ebp), %edx
	movl	%edx, 20(%eax)
	nop
	leave
	ret	$12
	.section	.text$_ZN8ListNodeI16MemoryDescriptorEC1ERKS0_PS1_S4_,"x"
	.linkonce discard
	.align 2
	.globl	__ZN8ListNodeI16MemoryDescriptorEC1ERKS0_PS1_S4_
	.def	__ZN8ListNodeI16MemoryDescriptorEC1ERKS0_PS1_S4_;	.scl	2;	.type	32;	.endef
__ZN8ListNodeI16MemoryDescriptorEC1ERKS0_PS1_S4_:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	%ecx, -12(%ebp)
	movl	-12(%ebp), %eax
	movl	$-1, (%esp)
	movl	%eax, %ecx
	call	__ZN16SimpleMemoryNodeC2Ei
	subl	$4, %esp
	movl	-12(%ebp), %eax
	movl	8(%ebp), %edx
	movl	(%edx), %ecx
	movl	%ecx, 4(%eax)
	movl	4(%edx), %ecx
	movl	%ecx, 8(%eax)
	movl	8(%edx), %edx
	movl	%edx, 12(%eax)
	movl	-12(%ebp), %eax
	movl	12(%ebp), %edx
	movl	%edx, 16(%eax)
	movl	-12(%ebp), %eax
	movl	16(%ebp), %edx
	movl	%edx, 20(%eax)
	nop
	leave
	ret	$12
	.section	.text$_ZN8ListNodeI16MemoryDescriptorE4initERKS0_PS1_S4_,"x"
	.linkonce discard
	.align 2
	.globl	__ZN8ListNodeI16MemoryDescriptorE4initERKS0_PS1_S4_
	.def	__ZN8ListNodeI16MemoryDescriptorE4initERKS0_PS1_S4_;	.scl	2;	.type	32;	.endef
__ZN8ListNodeI16MemoryDescriptorE4initERKS0_PS1_S4_:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	%ecx, -4(%ebp)
	movl	-4(%ebp), %eax
	movl	8(%ebp), %edx
	movl	(%edx), %ecx
	movl	%ecx, 4(%eax)
	movl	4(%edx), %ecx
	movl	%ecx, 8(%eax)
	movl	8(%edx), %edx
	movl	%edx, 12(%eax)
	movl	-4(%ebp), %eax
	movl	12(%ebp), %edx
	movl	%edx, 16(%eax)
	movl	-4(%ebp), %eax
	movl	16(%ebp), %edx
	movl	%edx, 20(%eax)
	movl	-4(%ebp), %eax
	leave
	ret	$12
	.section	.text$_ZN8ListNodeI16MemoryDescriptorED2Ev,"x"
	.linkonce discard
	.align 2
	.globl	__ZN8ListNodeI16MemoryDescriptorED2Ev
	.def	__ZN8ListNodeI16MemoryDescriptorED2Ev;	.scl	2;	.type	32;	.endef
__ZN8ListNodeI16MemoryDescriptorED2Ev:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	%ecx, -12(%ebp)
	movl	-12(%ebp), %eax
	addl	$4, %eax
	movl	%eax, %ecx
	call	__ZN16MemoryDescriptorD1Ev
	movl	-12(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN16SimpleMemoryNodeD2Ev
	nop
	leave
	ret
	.section	.text$_ZN8ListNodeI16MemoryDescriptorED1Ev,"x"
	.linkonce discard
	.align 2
	.globl	__ZN8ListNodeI16MemoryDescriptorED1Ev
	.def	__ZN8ListNodeI16MemoryDescriptorED1Ev;	.scl	2;	.type	32;	.endef
__ZN8ListNodeI16MemoryDescriptorED1Ev:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	%ecx, -12(%ebp)
	movl	-12(%ebp), %eax
	addl	$4, %eax
	movl	%eax, %ecx
	call	__ZN16MemoryDescriptorD1Ev
	movl	-12(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN16SimpleMemoryNodeD2Ev
	nop
	leave
	ret
	.section	.text$_ZN8ListNodeI16MemoryDescriptorE7getDataEv,"x"
	.linkonce discard
	.align 2
	.globl	__ZN8ListNodeI16MemoryDescriptorE7getDataEv
	.def	__ZN8ListNodeI16MemoryDescriptorE7getDataEv;	.scl	2;	.type	32;	.endef
__ZN8ListNodeI16MemoryDescriptorE7getDataEv:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	%ecx, -4(%ebp)
	movl	-4(%ebp), %eax
	addl	$4, %eax
	leave
	ret
	.section	.text$_ZN8ListNodeI16MemoryDescriptorE7setDataERKS0_,"x"
	.linkonce discard
	.align 2
	.globl	__ZN8ListNodeI16MemoryDescriptorE7setDataERKS0_
	.def	__ZN8ListNodeI16MemoryDescriptorE7setDataERKS0_;	.scl	2;	.type	32;	.endef
__ZN8ListNodeI16MemoryDescriptorE7setDataERKS0_:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	%ecx, -4(%ebp)
	movl	-4(%ebp), %eax
	movl	8(%ebp), %edx
	movl	(%edx), %ecx
	movl	%ecx, 4(%eax)
	movl	4(%edx), %ecx
	movl	%ecx, 8(%eax)
	movl	8(%edx), %edx
	movl	%edx, 12(%eax)
	nop
	leave
	ret	$4
	.section	.text$_ZN8ListNodeI16MemoryDescriptorE7getNextEv,"x"
	.linkonce discard
	.align 2
	.globl	__ZN8ListNodeI16MemoryDescriptorE7getNextEv
	.def	__ZN8ListNodeI16MemoryDescriptorE7getNextEv;	.scl	2;	.type	32;	.endef
__ZN8ListNodeI16MemoryDescriptorE7getNextEv:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	%ecx, -4(%ebp)
	movl	-4(%ebp), %eax
	movl	16(%eax), %eax
	leave
	ret
	.section	.text$_ZN8ListNodeI16MemoryDescriptorE11getPreviousEv,"x"
	.linkonce discard
	.align 2
	.globl	__ZN8ListNodeI16MemoryDescriptorE11getPreviousEv
	.def	__ZN8ListNodeI16MemoryDescriptorE11getPreviousEv;	.scl	2;	.type	32;	.endef
__ZN8ListNodeI16MemoryDescriptorE11getPreviousEv:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	%ecx, -4(%ebp)
	movl	-4(%ebp), %eax
	movl	20(%eax), %eax
	leave
	ret
	.section	.text$_ZN8ListNodeI16MemoryDescriptorE7setNextEPS1_,"x"
	.linkonce discard
	.align 2
	.globl	__ZN8ListNodeI16MemoryDescriptorE7setNextEPS1_
	.def	__ZN8ListNodeI16MemoryDescriptorE7setNextEPS1_;	.scl	2;	.type	32;	.endef
__ZN8ListNodeI16MemoryDescriptorE7setNextEPS1_:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	%ecx, -4(%ebp)
	movl	-4(%ebp), %eax
	movl	8(%ebp), %edx
	movl	%edx, 16(%eax)
	nop
	leave
	ret	$4
	.section	.text$_ZN8ListNodeI16MemoryDescriptorE11setPreviousEPS1_,"x"
	.linkonce discard
	.align 2
	.globl	__ZN8ListNodeI16MemoryDescriptorE11setPreviousEPS1_
	.def	__ZN8ListNodeI16MemoryDescriptorE11setPreviousEPS1_;	.scl	2;	.type	32;	.endef
__ZN8ListNodeI16MemoryDescriptorE11setPreviousEPS1_:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	%ecx, -4(%ebp)
	movl	-4(%ebp), %eax
	movl	8(%ebp), %edx
	movl	%edx, 20(%eax)
	nop
	leave
	ret	$4
	.section	.text$_ZN8ListNodeI16MemoryDescriptorE10removeNextEv,"x"
	.linkonce discard
	.align 2
	.globl	__ZN8ListNodeI16MemoryDescriptorE10removeNextEv
	.def	__ZN8ListNodeI16MemoryDescriptorE10removeNextEv;	.scl	2;	.type	32;	.endef
__ZN8ListNodeI16MemoryDescriptorE10removeNextEv:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$52, %esp
	movl	%ecx, -52(%ebp)
	movl	-52(%ebp), %eax
	movl	%eax, -12(%ebp)
	movl	-12(%ebp), %eax
	movl	16(%eax), %eax
	movl	%eax, -8(%ebp)
	movl	-52(%ebp), %eax
	movl	%eax, -32(%ebp)
	movl	-32(%ebp), %eax
	movl	16(%eax), %eax
	testl	%eax, %eax
	setne	%al
	movzbl	%al, %eax
	testl	%eax, %eax
	setne	%al
	testb	%al, %al
	je	L100
	movl	-8(%ebp), %eax
	movl	%eax, -20(%ebp)
	movl	-20(%ebp), %eax
	movl	16(%eax), %eax
	movl	-52(%ebp), %edx
	movl	%edx, -24(%ebp)
	movl	%eax, -36(%ebp)
	movl	-24(%ebp), %eax
	movl	-36(%ebp), %edx
	movl	%edx, 16(%eax)
	movl	-8(%ebp), %eax
	movl	%eax, -4(%ebp)
	movl	-4(%ebp), %eax
	movl	16(%eax), %eax
	testl	%eax, %eax
	setne	%al
	movzbl	%al, %eax
	testl	%eax, %eax
	setne	%al
	testb	%al, %al
	je	L100
	movl	-8(%ebp), %eax
	movl	%eax, -28(%ebp)
	movl	-28(%ebp), %eax
	movl	16(%eax), %eax
	movl	%eax, -16(%ebp)
	movl	-52(%ebp), %eax
	movl	%eax, -40(%ebp)
	movl	-16(%ebp), %eax
	movl	-40(%ebp), %edx
	movl	%edx, 20(%eax)
L100:
	movl	-8(%ebp), %eax
	leave
	ret
	.section	.text$_ZN8ListNodeI16MemoryDescriptorE14removePreviousEv,"x"
	.linkonce discard
	.align 2
	.globl	__ZN8ListNodeI16MemoryDescriptorE14removePreviousEv
	.def	__ZN8ListNodeI16MemoryDescriptorE14removePreviousEv;	.scl	2;	.type	32;	.endef
__ZN8ListNodeI16MemoryDescriptorE14removePreviousEv:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$52, %esp
	movl	%ecx, -52(%ebp)
	movl	-52(%ebp), %eax
	movl	%eax, -12(%ebp)
	movl	-12(%ebp), %eax
	movl	20(%eax), %eax
	movl	%eax, -8(%ebp)
	movl	-52(%ebp), %eax
	movl	%eax, -32(%ebp)
	movl	-32(%ebp), %eax
	movl	20(%eax), %eax
	testl	%eax, %eax
	setne	%al
	movzbl	%al, %eax
	testl	%eax, %eax
	setne	%al
	testb	%al, %al
	je	L108
	movl	-8(%ebp), %eax
	movl	%eax, -20(%ebp)
	movl	-20(%ebp), %eax
	movl	20(%eax), %eax
	movl	-52(%ebp), %edx
	movl	%edx, -24(%ebp)
	movl	%eax, -36(%ebp)
	movl	-24(%ebp), %eax
	movl	-36(%ebp), %edx
	movl	%edx, 20(%eax)
	movl	-8(%ebp), %eax
	movl	%eax, -4(%ebp)
	movl	-4(%ebp), %eax
	movl	20(%eax), %eax
	testl	%eax, %eax
	setne	%al
	movzbl	%al, %eax
	testl	%eax, %eax
	setne	%al
	testb	%al, %al
	je	L108
	movl	-8(%ebp), %eax
	movl	%eax, -28(%ebp)
	movl	-28(%ebp), %eax
	movl	20(%eax), %eax
	movl	%eax, -16(%ebp)
	movl	-52(%ebp), %eax
	movl	%eax, -40(%ebp)
	movl	-16(%ebp), %eax
	movl	-40(%ebp), %edx
	movl	%edx, 16(%eax)
L108:
	movl	-8(%ebp), %eax
	leave
	ret
	.section	.text$_ZN8ListNodeI16MemoryDescriptorE10insertNextEPS1_,"x"
	.linkonce discard
	.align 2
	.globl	__ZN8ListNodeI16MemoryDescriptorE10insertNextEPS1_
	.def	__ZN8ListNodeI16MemoryDescriptorE10insertNextEPS1_;	.scl	2;	.type	32;	.endef
__ZN8ListNodeI16MemoryDescriptorE10insertNextEPS1_:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$52, %esp
	movl	%ecx, -52(%ebp)
	cmpl	$0, 8(%ebp)
	je	L117
	movl	-52(%ebp), %eax
	movl	%eax, -24(%ebp)
	movl	-24(%ebp), %eax
	movl	16(%eax), %eax
	movl	%eax, -8(%ebp)
	cmpl	$0, -8(%ebp)
	je	L116
	movl	-8(%ebp), %eax
	movl	%eax, -4(%ebp)
	movl	8(%ebp), %eax
	movl	%eax, -28(%ebp)
	movl	-4(%ebp), %eax
	movl	-28(%ebp), %edx
	movl	%edx, 20(%eax)
L116:
	movl	8(%ebp), %eax
	movl	%eax, -16(%ebp)
	movl	-52(%ebp), %eax
	movl	%eax, -40(%ebp)
	movl	-16(%ebp), %eax
	movl	-40(%ebp), %edx
	movl	%edx, 20(%eax)
	movl	8(%ebp), %eax
	movl	%eax, -20(%ebp)
	movl	-8(%ebp), %eax
	movl	%eax, -36(%ebp)
	movl	-20(%ebp), %eax
	movl	-36(%ebp), %edx
	movl	%edx, 16(%eax)
	movl	-52(%ebp), %eax
	movl	%eax, -12(%ebp)
	movl	8(%ebp), %eax
	movl	%eax, -32(%ebp)
	movl	-12(%ebp), %eax
	movl	-32(%ebp), %edx
	movl	%edx, 16(%eax)
L117:
	nop
	leave
	ret	$4
	.section	.text$_ZN8ListNodeI16MemoryDescriptorE14insertPreviousEPS1_,"x"
	.linkonce discard
	.align 2
	.globl	__ZN8ListNodeI16MemoryDescriptorE14insertPreviousEPS1_
	.def	__ZN8ListNodeI16MemoryDescriptorE14insertPreviousEPS1_;	.scl	2;	.type	32;	.endef
__ZN8ListNodeI16MemoryDescriptorE14insertPreviousEPS1_:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$52, %esp
	movl	%ecx, -52(%ebp)
	cmpl	$0, 8(%ebp)
	je	L122
	movl	-52(%ebp), %eax
	movl	%eax, -24(%ebp)
	movl	-24(%ebp), %eax
	movl	20(%eax), %eax
	movl	%eax, -8(%ebp)
	cmpl	$0, -8(%ebp)
	je	L121
	movl	-8(%ebp), %eax
	movl	%eax, -4(%ebp)
	movl	8(%ebp), %eax
	movl	%eax, -28(%ebp)
	movl	-4(%ebp), %eax
	movl	-28(%ebp), %edx
	movl	%edx, 16(%eax)
L121:
	movl	8(%ebp), %eax
	movl	%eax, -16(%ebp)
	movl	-52(%ebp), %eax
	movl	%eax, -40(%ebp)
	movl	-16(%ebp), %eax
	movl	-40(%ebp), %edx
	movl	%edx, 16(%eax)
	movl	8(%ebp), %eax
	movl	%eax, -20(%ebp)
	movl	-8(%ebp), %eax
	movl	%eax, -36(%ebp)
	movl	-20(%ebp), %eax
	movl	-36(%ebp), %edx
	movl	%edx, 20(%eax)
	movl	-52(%ebp), %eax
	movl	%eax, -12(%ebp)
	movl	8(%ebp), %eax
	movl	%eax, -32(%ebp)
	movl	-12(%ebp), %eax
	movl	-32(%ebp), %edx
	movl	%edx, 20(%eax)
L122:
	nop
	leave
	ret	$4
	.section	.text$_ZN8ListNodeI16MemoryDescriptorE7hasNextEv,"x"
	.linkonce discard
	.align 2
	.globl	__ZN8ListNodeI16MemoryDescriptorE7hasNextEv
	.def	__ZN8ListNodeI16MemoryDescriptorE7hasNextEv;	.scl	2;	.type	32;	.endef
__ZN8ListNodeI16MemoryDescriptorE7hasNextEv:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	%ecx, -4(%ebp)
	movl	-4(%ebp), %eax
	movl	16(%eax), %eax
	testl	%eax, %eax
	setne	%al
	movzbl	%al, %eax
	leave
	ret
	.section	.text$_ZN8ListNodeI16MemoryDescriptorE11hasPreviousEv,"x"
	.linkonce discard
	.align 2
	.globl	__ZN8ListNodeI16MemoryDescriptorE11hasPreviousEv
	.def	__ZN8ListNodeI16MemoryDescriptorE11hasPreviousEv;	.scl	2;	.type	32;	.endef
__ZN8ListNodeI16MemoryDescriptorE11hasPreviousEv:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	%ecx, -4(%ebp)
	movl	-4(%ebp), %eax
	movl	20(%eax), %eax
	testl	%eax, %eax
	setne	%al
	movzbl	%al, %eax
	leave
	ret
	.ident	"GCC: (GNU) 5.4.0"
	.def	__ZN16SimpleMemoryNodeC2Ei;	.scl	2;	.type	32;	.endef
	.def	__ZN16SimpleMemoryNodeD2Ev;	.scl	2;	.type	32;	.endef
	.def	__ZN19SimpleMemoryManagerI8ListNodeIiEE6getNewEv;	.scl	2;	.type	32;	.endef
	.def	__ZN19SimpleMemoryManagerI8ListNodeIiEE8withdrawEPS1_;	.scl	2;	.type	32;	.endef
	.def	__ZN19SimpleMemoryManagerI8ListNodeIiEE8freeNextEPS1_;	.scl	2;	.type	32;	.endef
	.def	__ZN16MemoryDescriptorD1Ev;	.scl	2;	.type	32;	.endef
