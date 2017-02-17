	.file	"List.cpp"
	.section	.text$_ZN8ListNodeIiEC2EiPS0_S1_,"x"
	.linkonce discard
	.align 2
	.globl	__ZN8ListNodeIiEC2EiPS0_S1_
	.def	__ZN8ListNodeIiEC2EiPS0_S1_;	.scl	2;	.type	32;	.endef
__ZN8ListNodeIiEC2EiPS0_S1_:
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
	.section	.text$_ZN8ListNodeIiEC1EiPS0_S1_,"x"
	.linkonce discard
	.align 2
	.globl	__ZN8ListNodeIiEC1EiPS0_S1_
	.def	__ZN8ListNodeIiEC1EiPS0_S1_;	.scl	2;	.type	32;	.endef
__ZN8ListNodeIiEC1EiPS0_S1_:
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
	je	L17
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
	je	L17
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
L17:
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
	je	L25
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
	je	L25
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
L25:
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
	je	L34
	movl	-52(%ebp), %eax
	movl	%eax, -24(%ebp)
	movl	-24(%ebp), %eax
	movl	8(%eax), %eax
	movl	%eax, -8(%ebp)
	cmpl	$0, -8(%ebp)
	je	L33
	movl	-8(%ebp), %eax
	movl	%eax, -4(%ebp)
	movl	8(%ebp), %eax
	movl	%eax, -28(%ebp)
	movl	-4(%ebp), %eax
	movl	-28(%ebp), %edx
	movl	%edx, 12(%eax)
L33:
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
L34:
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
	je	L39
	movl	-52(%ebp), %eax
	movl	%eax, -24(%ebp)
	movl	-24(%ebp), %eax
	movl	12(%eax), %eax
	movl	%eax, -8(%ebp)
	cmpl	$0, -8(%ebp)
	je	L38
	movl	-8(%ebp), %eax
	movl	%eax, -4(%ebp)
	movl	8(%ebp), %eax
	movl	%eax, -28(%ebp)
	movl	-4(%ebp), %eax
	movl	-28(%ebp), %edx
	movl	%edx, 8(%eax)
L38:
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
L39:
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
	.section	.text$_ZN10LinkedListIiEC2Ev,"x"
	.linkonce discard
	.align 2
	.globl	__ZN10LinkedListIiEC2Ev
	.def	__ZN10LinkedListIiEC2Ev;	.scl	2;	.type	32;	.endef
__ZN10LinkedListIiEC2Ev:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	%ecx, -12(%ebp)
	movl	-12(%ebp), %eax
	movl	$0, 8(%esp)
	movl	$0, 4(%esp)
	movl	$0, (%esp)
	movl	%eax, %ecx
	call	__ZN8ListNodeIiEC1EiPS0_S1_
	subl	$12, %esp
	movl	-12(%ebp), %eax
	movl	-12(%ebp), %edx
	addl	$16, %edx
	movl	$0, 8(%esp)
	movl	%eax, 4(%esp)
	movl	$0, (%esp)
	movl	%edx, %ecx
	call	__ZN8ListNodeIiEC1EiPS0_S1_
	subl	$12, %esp
	movl	-12(%ebp), %eax
	movl	$0, 32(%eax)
	nop
	leave
	ret
	.section	.text$_ZN10LinkedListIiEC1Ev,"x"
	.linkonce discard
	.align 2
	.globl	__ZN10LinkedListIiEC1Ev
	.def	__ZN10LinkedListIiEC1Ev;	.scl	2;	.type	32;	.endef
__ZN10LinkedListIiEC1Ev:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	%ecx, -12(%ebp)
	movl	-12(%ebp), %eax
	movl	$0, 8(%esp)
	movl	$0, 4(%esp)
	movl	$0, (%esp)
	movl	%eax, %ecx
	call	__ZN8ListNodeIiEC1EiPS0_S1_
	subl	$12, %esp
	movl	-12(%ebp), %eax
	movl	-12(%ebp), %edx
	addl	$16, %edx
	movl	$0, 8(%esp)
	movl	%eax, 4(%esp)
	movl	$0, (%esp)
	movl	%edx, %ecx
	call	__ZN8ListNodeIiEC1EiPS0_S1_
	subl	$12, %esp
	movl	-12(%ebp), %eax
	movl	$0, 32(%eax)
	nop
	leave
	ret
	.section	.text$_ZN10LinkedListIiED2Ev,"x"
	.linkonce discard
	.align 2
	.globl	__ZN10LinkedListIiED2Ev
	.def	__ZN10LinkedListIiED2Ev;	.scl	2;	.type	32;	.endef
__ZN10LinkedListIiED2Ev:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	%ecx, -12(%ebp)
	movl	-12(%ebp), %eax
	addl	$16, %eax
	movl	%eax, %ecx
	call	__ZN8ListNodeIiED1Ev
	movl	-12(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN8ListNodeIiED1Ev
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
	subl	$24, %esp
	movl	%ecx, -12(%ebp)
	movl	-12(%ebp), %eax
	addl	$16, %eax
	movl	%eax, %ecx
	call	__ZN8ListNodeIiED1Ev
	movl	-12(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN8ListNodeIiED1Ev
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
	movl	%eax, -4(%ebp)
	movl	-4(%ebp), %eax
	movl	8(%eax), %eax
	nop
	leave
	ret
	.section	.text$_ZN10LinkedListIiE8setFirstEP8ListNodeIiE,"x"
	.linkonce discard
	.align 2
	.globl	__ZN10LinkedListIiE8setFirstEP8ListNodeIiE
	.def	__ZN10LinkedListIiE8setFirstEP8ListNodeIiE;	.scl	2;	.type	32;	.endef
__ZN10LinkedListIiE8setFirstEP8ListNodeIiE:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$20, %esp
	movl	%ecx, -20(%ebp)
	movl	-20(%ebp), %eax
	movl	%eax, -4(%ebp)
	movl	8(%ebp), %eax
	movl	%eax, -8(%ebp)
	movl	-4(%ebp), %eax
	movl	-8(%ebp), %edx
	movl	%edx, 8(%eax)
	nop
	leave
	ret	$4
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
	addl	$16, %eax
	movl	%eax, -4(%ebp)
	movl	-4(%ebp), %eax
	movl	8(%eax), %eax
	nop
	leave
	ret
	.section	.text$_ZN10LinkedListIiE6appendEP8ListNodeIiE,"x"
	.linkonce discard
	.align 2
	.globl	__ZN10LinkedListIiE6appendEP8ListNodeIiE
	.def	__ZN10LinkedListIiE6appendEP8ListNodeIiE;	.scl	2;	.type	32;	.endef
__ZN10LinkedListIiE6appendEP8ListNodeIiE:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$36, %esp
	movl	%ecx, -36(%ebp)
	movl	-36(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN10LinkedListIiE7getLastEv
	movl	%eax, -4(%ebp)
	movl	-4(%ebp), %eax
	movl	%eax, -12(%ebp)
	movl	8(%ebp), %eax
	movl	%eax, -24(%ebp)
	movl	-12(%ebp), %eax
	movl	-24(%ebp), %edx
	movl	%edx, 8(%eax)
	movl	-4(%ebp), %eax
	movl	%eax, -20(%ebp)
	movl	-20(%ebp), %eax
	movl	8(%eax), %eax
	testl	%eax, %eax
	setne	%al
	movzbl	%al, %eax
	testl	%eax, %eax
	setne	%al
	testb	%al, %al
	je	L58
	movl	8(%ebp), %eax
	movl	%eax, -16(%ebp)
	movl	-4(%ebp), %eax
	movl	%eax, -32(%ebp)
	movl	-16(%ebp), %eax
	movl	-32(%ebp), %edx
	movl	%edx, 12(%eax)
	movl	-36(%ebp), %eax
	addl	$16, %eax
	movl	%eax, -8(%ebp)
	movl	8(%ebp), %eax
	movl	%eax, -28(%ebp)
	movl	-8(%ebp), %eax
	movl	-28(%ebp), %edx
	movl	%edx, 8(%eax)
	movl	-36(%ebp), %eax
	movl	32(%eax), %eax
	leal	1(%eax), %edx
	movl	-36(%ebp), %eax
	movl	%edx, 32(%eax)
L58:
	nop
	leave
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
	cmpl	-4(%ebp), %eax
	je	L60
	movl	-4(%ebp), %eax
	movl	%eax, -12(%ebp)
	movl	-12(%ebp), %eax
	movl	12(%eax), %eax
	movl	%eax, -8(%ebp)
	movl	-36(%ebp), %eax
	addl	$16, %eax
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
	movl	32(%eax), %eax
	leal	-1(%eax), %edx
	movl	-36(%ebp), %eax
	movl	%edx, 32(%eax)
	movl	-4(%ebp), %eax
	jmp	L62
L60:
	movl	$0, %eax
L62:
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
	movl	$0, 32(%eax)
	movl	-36(%ebp), %eax
	movl	%eax, -4(%ebp)
L67:
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
	je	L65
	movl	-4(%ebp), %eax
	movl	%eax, -8(%ebp)
	movl	-8(%ebp), %eax
	movl	8(%eax), %eax
	movl	%eax, -4(%ebp)
	movl	-36(%ebp), %eax
	movl	32(%eax), %eax
	leal	1(%eax), %edx
	movl	-36(%ebp), %eax
	movl	%edx, 32(%eax)
	jmp	L67
L65:
	movl	-36(%ebp), %eax
	addl	$16, %eax
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
	movl	32(%eax), %eax
	leave
	ret
	.ident	"GCC: (GNU) 5.4.0"
	.def	__ZN16SimpleMemoryNodeC2Ei;	.scl	2;	.type	32;	.endef
	.def	__ZN16SimpleMemoryNodeD2Ev;	.scl	2;	.type	32;	.endef
