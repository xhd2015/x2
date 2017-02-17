	.file	"test.cpp"
	.text
	.align 2
	.globl	__ZN4TestC2Ev
	.def	__ZN4TestC2Ev;	.scl	2;	.type	32;	.endef
__ZN4TestC2Ev:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$56, %esp
	movl	%ecx, -12(%ebp)
	movl	__ZN4Util11MODE_COMMONE, %edx
	movl	-12(%ebp), %eax
	movl	%edx, 16(%esp)
	movl	$30, 12(%esp)
	movl	$5, 8(%esp)
	movl	$0, 4(%esp)
	movl	$5, (%esp)
	movl	%eax, %ecx
	call	__ZN7PrinterC1Ejjjji
	subl	$20, %esp
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
	subl	$24, %esp
	movl	%ecx, -12(%ebp)
	movl	-12(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN7PrinterD1Ev
	nop
	leave
	ret
	.globl	__ZN4TestD1Ev
	.def	__ZN4TestD1Ev;	.scl	2;	.type	32;	.endef
	.set	__ZN4TestD1Ev,__ZN4TestD2Ev
	.section .rdata,"dr"
LC0:
	.ascii "Testing: List. \12\0"
LC1:
	.ascii "\12\0"
LC2:
	.ascii "size is:\0"
LC3:
	.ascii "\12End.\12\0"
	.text
	.align 2
	.globl	__ZN4Test8testListEv
	.def	__ZN4Test8testListEv;	.scl	2;	.type	32;	.endef
__ZN4Test8testListEv:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$168, %esp
	movl	%ecx, -140(%ebp)
	movl	-140(%ebp), %eax
	movl	$LC0, (%esp)
	movl	%eax, %ecx
	call	__ZN7Printer5putszEPc
	subl	$4, %esp
	movl	$1600, %ecx
	movl	__ZN8PMLoader15FREE_HEAP_STARTE, %edx
	leal	-86(%ebp), %eax
	movl	%ecx, 4(%esp)
	movl	%edx, (%esp)
	movl	%eax, %ecx
	call	__ZN19SimpleMemoryManagerI8ListNodeIiEEC1Eij
	subl	$8, %esp
	leal	-122(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN10LinkedListIiEC1Ev
	leal	-86(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN19SimpleMemoryManagerI8ListNodeIiEE6getNewEv
	movl	%eax, -12(%ebp)
	movl	$5, -52(%ebp)
	movl	-12(%ebp), %eax
	movl	%eax, -16(%ebp)
	movl	-52(%ebp), %edx
	movl	-16(%ebp), %eax
	movl	%edx, 4(%eax)
	movl	-12(%ebp), %eax
	movl	%eax, -20(%ebp)
	movl	-20(%ebp), %eax
	addl	$4, %eax
	movl	(%eax), %eax
	movl	%eax, 8(%esp)
	movl	$10, 4(%esp)
	leal	-62(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZN4Util10digitToStrEPcji
	movl	-140(%ebp), %eax
	leal	-62(%ebp), %edx
	movl	%edx, (%esp)
	movl	%eax, %ecx
	call	__ZN7Printer5putszEPc
	subl	$4, %esp
	movl	-140(%ebp), %eax
	movl	$LC1, (%esp)
	movl	%eax, %ecx
	call	__ZN7Printer5putszEPc
	subl	$4, %esp
	leal	-122(%ebp), %eax
	movl	-12(%ebp), %edx
	movl	%edx, (%esp)
	movl	%eax, %ecx
	call	__ZN10LinkedListIiE6appendEP8ListNodeIiE
	subl	$4, %esp
	leal	-86(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN19SimpleMemoryManagerI8ListNodeIiEE6getNewEv
	movl	%eax, -12(%ebp)
	movl	$7, -48(%ebp)
	movl	-12(%ebp), %eax
	movl	%eax, -24(%ebp)
	movl	-48(%ebp), %edx
	movl	-24(%ebp), %eax
	movl	%edx, 4(%eax)
	leal	-122(%ebp), %eax
	movl	-12(%ebp), %edx
	movl	%edx, (%esp)
	movl	%eax, %ecx
	call	__ZN10LinkedListIiE6appendEP8ListNodeIiE
	subl	$4, %esp
	leal	-86(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN19SimpleMemoryManagerI8ListNodeIiEE6getNewEv
	movl	%eax, -12(%ebp)
	movl	$6, -44(%ebp)
	movl	-12(%ebp), %eax
	movl	%eax, -28(%ebp)
	movl	-44(%ebp), %edx
	movl	-28(%ebp), %eax
	movl	%edx, 4(%eax)
	leal	-122(%ebp), %eax
	movl	-12(%ebp), %edx
	movl	%edx, (%esp)
	movl	%eax, %ecx
	call	__ZN10LinkedListIiE6appendEP8ListNodeIiE
	subl	$4, %esp
	movl	-140(%ebp), %eax
	movl	$LC2, (%esp)
	movl	%eax, %ecx
	call	__ZN7Printer5putszEPc
	subl	$4, %esp
	movl	-90(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	$10, 4(%esp)
	leal	-62(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZN4Util10digitToStrEPcji
	movl	-140(%ebp), %eax
	leal	-62(%ebp), %edx
	movl	%edx, (%esp)
	movl	%eax, %ecx
	call	__ZN7Printer5putszEPc
	subl	$4, %esp
	movl	-140(%ebp), %eax
	movl	$LC1, (%esp)
	movl	%eax, %ecx
	call	__ZN7Printer5putszEPc
	subl	$4, %esp
	leal	-122(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN10LinkedListIiE6removeEv
	movl	%eax, -12(%ebp)
	movl	-12(%ebp), %eax
	movl	%eax, -32(%ebp)
	movl	-32(%ebp), %eax
	addl	$4, %eax
	movl	(%eax), %eax
	movl	%eax, 8(%esp)
	movl	$10, 4(%esp)
	leal	-62(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZN4Util10digitToStrEPcji
	movl	-140(%ebp), %eax
	leal	-62(%ebp), %edx
	movl	%edx, (%esp)
	movl	%eax, %ecx
	call	__ZN7Printer5putszEPc
	subl	$4, %esp
	leal	-122(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN10LinkedListIiE6removeEv
	movl	%eax, -12(%ebp)
	movl	-12(%ebp), %eax
	movl	%eax, -36(%ebp)
	movl	-36(%ebp), %eax
	addl	$4, %eax
	movl	(%eax), %eax
	movl	%eax, 8(%esp)
	movl	$10, 4(%esp)
	leal	-62(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZN4Util10digitToStrEPcji
	movl	-140(%ebp), %eax
	leal	-62(%ebp), %edx
	movl	%edx, (%esp)
	movl	%eax, %ecx
	call	__ZN7Printer5putszEPc
	subl	$4, %esp
	leal	-122(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN10LinkedListIiE6removeEv
	movl	%eax, -12(%ebp)
	movl	-12(%ebp), %eax
	movl	%eax, -40(%ebp)
	movl	-40(%ebp), %eax
	addl	$4, %eax
	movl	(%eax), %eax
	movl	%eax, 8(%esp)
	movl	$10, 4(%esp)
	leal	-62(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZN4Util10digitToStrEPcji
	movl	-140(%ebp), %eax
	leal	-62(%ebp), %edx
	movl	%edx, (%esp)
	movl	%eax, %ecx
	call	__ZN7Printer5putszEPc
	subl	$4, %esp
	movl	-140(%ebp), %eax
	movl	$LC3, (%esp)
	movl	%eax, %ecx
	call	__ZN7Printer5putszEPc
	subl	$4, %esp
	leal	-122(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN10LinkedListIiED1Ev
	leal	-86(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN19SimpleMemoryManagerI8ListNodeIiEED1Ev
	nop
	leave
	ret
	.section .rdata,"dr"
LC4:
	.ascii "Current size:\0"
LC5:
	.ascii "Get : \0"
	.text
	.align 2
	.globl	__ZN4Test9testQueueEv
	.def	__ZN4Test9testQueueEv;	.scl	2;	.type	32;	.endef
__ZN4Test9testQueueEv:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$184, %esp
	movl	%ecx, -156(%ebp)
	leal	-139(%ebp), %eax
	movl	$100, 4(%esp)
	leal	-119(%ebp), %edx
	movl	%edx, (%esp)
	movl	%eax, %ecx
	call	__ZN5QueueIhEC1EPhj
	subl	$8, %esp
	movb	$97, -9(%ebp)
	movzbl	-9(%ebp), %edx
	leal	-139(%ebp), %eax
	movl	%edx, (%esp)
	movl	%eax, %ecx
	call	__ZN5QueueIhE3addEh
	subl	$4, %esp
	leal	-139(%ebp), %eax
	movl	$98, (%esp)
	movl	%eax, %ecx
	call	__ZN5QueueIhE3addEh
	subl	$4, %esp
	leal	-139(%ebp), %eax
	movl	$118, (%esp)
	movl	%eax, %ecx
	call	__ZN5QueueIhE3addEh
	subl	$4, %esp
	movl	-131(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	$10, 4(%esp)
	leal	-19(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZN4Util10digitToStrEPcji
	movl	-156(%ebp), %eax
	movl	$LC4, (%esp)
	movl	%eax, %ecx
	call	__ZN7Printer5putszEPc
	subl	$4, %esp
	movl	-156(%ebp), %eax
	leal	-19(%ebp), %edx
	movl	%edx, (%esp)
	movl	%eax, %ecx
	call	__ZN7Printer5putszEPc
	subl	$4, %esp
	movl	-156(%ebp), %eax
	movl	$10, (%esp)
	movl	%eax, %ecx
	call	__ZN7Printer4putcEi
	subl	$4, %esp
	leal	-139(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN5QueueIhE6removeEv
	movb	%al, -9(%ebp)
	movl	-156(%ebp), %eax
	movl	$LC5, (%esp)
	movl	%eax, %ecx
	call	__ZN7Printer5putszEPc
	subl	$4, %esp
	movzbl	-9(%ebp), %edx
	movl	-156(%ebp), %eax
	movl	%edx, (%esp)
	movl	%eax, %ecx
	call	__ZN7Printer4putcEi
	subl	$4, %esp
	leal	-139(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN5QueueIhE6removeEv
	movb	%al, -9(%ebp)
	movzbl	-9(%ebp), %edx
	movl	-156(%ebp), %eax
	movl	%edx, (%esp)
	movl	%eax, %ecx
	call	__ZN7Printer4putcEi
	subl	$4, %esp
	leal	-139(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN5QueueIhE6removeEv
	movb	%al, -9(%ebp)
	movzbl	-9(%ebp), %edx
	movl	-156(%ebp), %eax
	movl	%edx, (%esp)
	movl	%eax, %ecx
	call	__ZN7Printer4putcEi
	subl	$4, %esp
	leal	-139(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN5QueueIhED1Ev
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
	call	__ZN4Test8testListEv
	nop
	leave
	ret
	.ident	"GCC: (GNU) 5.4.0"
	.def	__ZN7PrinterC1Ejjjji;	.scl	2;	.type	32;	.endef
	.def	__ZN7PrinterD1Ev;	.scl	2;	.type	32;	.endef
	.def	__ZN7Printer5putszEPc;	.scl	2;	.type	32;	.endef
	.def	__ZN19SimpleMemoryManagerI8ListNodeIiEEC1Eij;	.scl	2;	.type	32;	.endef
	.def	__ZN10LinkedListIiEC1Ev;	.scl	2;	.type	32;	.endef
	.def	__ZN19SimpleMemoryManagerI8ListNodeIiEE6getNewEv;	.scl	2;	.type	32;	.endef
	.def	__ZN4Util10digitToStrEPcji;	.scl	2;	.type	32;	.endef
	.def	__ZN10LinkedListIiE6appendEP8ListNodeIiE;	.scl	2;	.type	32;	.endef
	.def	__ZN10LinkedListIiE6removeEv;	.scl	2;	.type	32;	.endef
	.def	__ZN10LinkedListIiED1Ev;	.scl	2;	.type	32;	.endef
	.def	__ZN19SimpleMemoryManagerI8ListNodeIiEED1Ev;	.scl	2;	.type	32;	.endef
	.def	__ZN5QueueIhEC1EPhj;	.scl	2;	.type	32;	.endef
	.def	__ZN5QueueIhE3addEh;	.scl	2;	.type	32;	.endef
	.def	__ZN7Printer4putcEi;	.scl	2;	.type	32;	.endef
	.def	__ZN5QueueIhE6removeEv;	.scl	2;	.type	32;	.endef
	.def	__ZN5QueueIhED1Ev;	.scl	2;	.type	32;	.endef
