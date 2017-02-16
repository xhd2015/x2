	.file	"test.cpp"
	.text
	.align 2
	.globl	__ZN4TestC2Ev
	.def	__ZN4TestC2Ev;	.scl	2;	.type	32;	.endef
__ZN4TestC2Ev:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	%ecx, -4(%ebp)
	nop
	leave
	ret
	.globl	__ZN4TestC1Ev
	.def	__ZN4TestC1Ev;	.scl	2;	.type	32;	.endef
	.set	__ZN4TestC1Ev,__ZN4TestC2Ev
	.align 2
	.globl	__ZN4TestD2Ev
	.def	__ZN4TestD2Ev;	.scl	2;	.type	32;	.endef
__ZN4TestD2Ev:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	%ecx, -4(%ebp)
	nop
	leave
	ret
	.globl	__ZN4TestD1Ev
	.def	__ZN4TestD1Ev;	.scl	2;	.type	32;	.endef
	.set	__ZN4TestD1Ev,__ZN4TestD2Ev
	.section .rdata,"dr"
LC0:
	.ascii "Current size:\0"
LC1:
	.ascii "Get : \0"
	.text
	.align 2
	.globl	__ZN4Test9testQueueEv
	.def	__ZN4Test9testQueueEv;	.scl	2;	.type	32;	.endef
__ZN4Test9testQueueEv:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$216, %esp
	movl	%ecx, -172(%ebp)
	movl	__ZN4Util11MODE_COMMONE, %edx
	leal	-37(%ebp), %eax
	movl	%edx, 16(%esp)
	movl	$30, 12(%esp)
	movl	$5, 8(%esp)
	movl	$0, 4(%esp)
	movl	$5, (%esp)
	movl	%eax, %ecx
	call	__ZN7PrinterC1Ejjjji
	subl	$20, %esp
	leal	-167(%ebp), %eax
	movl	$100, 4(%esp)
	leal	-147(%ebp), %edx
	movl	%edx, (%esp)
	movl	%eax, %ecx
	call	__ZN5QueueIhEC1EPhj
	subl	$8, %esp
	movb	$97, -9(%ebp)
	movzbl	-9(%ebp), %edx
	leal	-167(%ebp), %eax
	movl	%edx, (%esp)
	movl	%eax, %ecx
	call	__ZN5QueueIhE3addEh
	subl	$4, %esp
	leal	-167(%ebp), %eax
	movl	$98, (%esp)
	movl	%eax, %ecx
	call	__ZN5QueueIhE3addEh
	subl	$4, %esp
	leal	-167(%ebp), %eax
	movl	$118, (%esp)
	movl	%eax, %ecx
	call	__ZN5QueueIhE3addEh
	subl	$4, %esp
	movl	-159(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	$10, 4(%esp)
	leal	-47(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZN4Util10digitToStrEPcji
	leal	-37(%ebp), %eax
	movl	$LC0, (%esp)
	movl	%eax, %ecx
	call	__ZN7Printer5putszEPc
	subl	$4, %esp
	leal	-37(%ebp), %eax
	leal	-47(%ebp), %edx
	movl	%edx, (%esp)
	movl	%eax, %ecx
	call	__ZN7Printer5putszEPc
	subl	$4, %esp
	leal	-37(%ebp), %eax
	movl	$10, (%esp)
	movl	%eax, %ecx
	call	__ZN7Printer4putcEi
	subl	$4, %esp
	leal	-167(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN5QueueIhE6removeEv
	movb	%al, -9(%ebp)
	leal	-37(%ebp), %eax
	movl	$LC1, (%esp)
	movl	%eax, %ecx
	call	__ZN7Printer5putszEPc
	subl	$4, %esp
	movzbl	-9(%ebp), %edx
	leal	-37(%ebp), %eax
	movl	%edx, (%esp)
	movl	%eax, %ecx
	call	__ZN7Printer4putcEi
	subl	$4, %esp
	leal	-167(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN5QueueIhE6removeEv
	movb	%al, -9(%ebp)
	movzbl	-9(%ebp), %edx
	leal	-37(%ebp), %eax
	movl	%edx, (%esp)
	movl	%eax, %ecx
	call	__ZN7Printer4putcEi
	subl	$4, %esp
	leal	-167(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN5QueueIhE6removeEv
	movb	%al, -9(%ebp)
	movzbl	-9(%ebp), %edx
	leal	-37(%ebp), %eax
	movl	%edx, (%esp)
	movl	%eax, %ecx
	call	__ZN7Printer4putcEi
	subl	$4, %esp
	leal	-167(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN5QueueIhED1Ev
	leal	-37(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN7PrinterD1Ev
	nop
	leave
	ret
	.align 2
	.globl	__ZN4Test3runEv
	.def	__ZN4Test3runEv;	.scl	2;	.type	32;	.endef
__ZN4Test3runEv:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	%ecx, -12(%ebp)
	movl	-12(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN4Test9testQueueEv
	nop
	leave
	ret
	.section	.text$_ZN5QueueIhEC1EPhj,"x"
	.linkonce discard
	.align 2
	.globl	__ZN5QueueIhEC1EPhj
	.def	__ZN5QueueIhEC1EPhj;	.scl	2;	.type	32;	.endef
__ZN5QueueIhEC1EPhj:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	%ecx, -4(%ebp)
	movl	-4(%ebp), %eax
	movl	8(%ebp), %edx
	movl	%edx, (%eax)
	movl	-4(%ebp), %eax
	movl	12(%ebp), %edx
	movl	%edx, 4(%eax)
	movl	-4(%ebp), %eax
	movl	$0, 8(%eax)
	movl	-4(%ebp), %eax
	movl	$0, 12(%eax)
	movl	-4(%ebp), %eax
	movl	$0, 16(%eax)
	nop
	leave
	ret	$8
	.section	.text$_ZN5QueueIhED1Ev,"x"
	.linkonce discard
	.align 2
	.globl	__ZN5QueueIhED1Ev
	.def	__ZN5QueueIhED1Ev;	.scl	2;	.type	32;	.endef
__ZN5QueueIhED1Ev:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	%ecx, -4(%ebp)
	nop
	leave
	ret
	.section	.text$_ZN5QueueIhE3addEh,"x"
	.linkonce discard
	.align 2
	.globl	__ZN5QueueIhE3addEh
	.def	__ZN5QueueIhE3addEh;	.scl	2;	.type	32;	.endef
__ZN5QueueIhE3addEh:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	%ecx, -20(%ebp)
	movl	8(%ebp), %eax
	movb	%al, -24(%ebp)
	movl	-20(%ebp), %eax
	movl	%eax, -4(%ebp)
	movl	-4(%ebp), %eax
	movl	8(%eax), %edx
	movl	-4(%ebp), %eax
	movl	4(%eax), %eax
	cmpl	%eax, %edx
	sete	%al
	movzbl	%al, %eax
	testl	%eax, %eax
	setne	%al
	testb	%al, %al
	je	L10
	movl	$0, %eax
	jmp	L11
L10:
	movl	-20(%ebp), %eax
	movl	(%eax), %edx
	movl	-20(%ebp), %eax
	movl	12(%eax), %eax
	addl	%eax, %edx
	movzbl	-24(%ebp), %eax
	movb	%al, (%edx)
	movl	-20(%ebp), %eax
	movl	12(%eax), %eax
	leal	1(%eax), %edx
	movl	-20(%ebp), %eax
	movl	%edx, 12(%eax)
	movl	-20(%ebp), %eax
	movl	8(%eax), %eax
	leal	1(%eax), %edx
	movl	-20(%ebp), %eax
	movl	%edx, 8(%eax)
	movl	-20(%ebp), %eax
	movl	12(%eax), %edx
	movl	-20(%ebp), %eax
	movl	4(%eax), %eax
	cmpl	%eax, %edx
	jne	L12
	movl	-20(%ebp), %eax
	movl	$0, 12(%eax)
L12:
	movl	$1, %eax
L11:
	leave
	ret	$4
	.section	.text$_ZN5QueueIhE6removeEv,"x"
	.linkonce discard
	.align 2
	.globl	__ZN5QueueIhE6removeEv
	.def	__ZN5QueueIhE6removeEv;	.scl	2;	.type	32;	.endef
__ZN5QueueIhE6removeEv:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$20, %esp
	movl	%ecx, -20(%ebp)
	movl	-20(%ebp), %eax
	movl	%eax, -8(%ebp)
	movl	-8(%ebp), %eax
	movl	8(%eax), %eax
	testl	%eax, %eax
	sete	%al
	movzbl	%al, %eax
	testl	%eax, %eax
	setne	%al
	testb	%al, %al
	je	L15
	movl	$0, %eax
	jmp	L16
L15:
	movl	-20(%ebp), %eax
	movl	(%eax), %edx
	movl	-20(%ebp), %eax
	movl	16(%eax), %eax
	addl	%edx, %eax
	movzbl	(%eax), %eax
	movb	%al, -1(%ebp)
	movl	-20(%ebp), %eax
	movl	16(%eax), %eax
	leal	1(%eax), %edx
	movl	-20(%ebp), %eax
	movl	%edx, 16(%eax)
	movl	-20(%ebp), %eax
	movl	8(%eax), %eax
	leal	-1(%eax), %edx
	movl	-20(%ebp), %eax
	movl	%edx, 8(%eax)
	movl	-20(%ebp), %eax
	movl	16(%eax), %edx
	movl	-20(%ebp), %eax
	movl	4(%eax), %eax
	cmpl	%eax, %edx
	jne	L17
	movl	-20(%ebp), %eax
	movl	$0, 16(%eax)
L17:
	movzbl	-1(%ebp), %eax
L16:
	leave
	ret
	.ident	"GCC: (GNU) 5.4.0"
	.def	__ZN7PrinterC1Ejjjji;	.scl	2;	.type	32;	.endef
	.def	__ZN4Util10digitToStrEPcji;	.scl	2;	.type	32;	.endef
	.def	__ZN7Printer5putszEPc;	.scl	2;	.type	32;	.endef
	.def	__ZN7Printer4putcEi;	.scl	2;	.type	32;	.endef
	.def	__ZN7PrinterD1Ev;	.scl	2;	.type	32;	.endef
