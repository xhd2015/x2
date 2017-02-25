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
	movl	$15, 8(%esp)
	movl	$20, 4(%esp)
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
	.ascii "-->\0"
LC1:
	.ascii ":\0"
LC2:
	.ascii "\12\0"
	.text
	.align 2
	.globl	__ZN4Test14dumpMemoryDataERK16MemoryDescriptor
	.def	__ZN4Test14dumpMemoryDataERK16MemoryDescriptor;	.scl	2;	.type	32;	.endef
__ZN4Test14dumpMemoryDataERK16MemoryDescriptor:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	__ZZN4Test14dumpMemoryDataERK16MemoryDescriptorE5count, %eax
	leal	1(%eax), %edx
	movl	%edx, __ZZN4Test14dumpMemoryDataERK16MemoryDescriptorE5count
	movl	%eax, 8(%esp)
	movl	$10, 4(%esp)
	leal	-18(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZN4Util10digitToStrEPcji
	movl	__ZN4Util11MODE_COMMONE, %eax
	movl	%eax, 4(%esp)
	leal	-18(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZN4Util8printStrEPKci
	movl	__ZN4Util11MODE_COMMONE, %eax
	movl	%eax, 4(%esp)
	movl	$LC0, (%esp)
	call	__ZN4Util8printStrEPKci
	movl	8(%ebp), %ecx
	call	__ZN16MemoryDescriptor8getStartEv
	movl	%eax, 8(%esp)
	movl	$10, 4(%esp)
	leal	-18(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZN4Util10digitToStrEPcji
	movl	__ZN4Util11MODE_COMMONE, %eax
	movl	%eax, 4(%esp)
	leal	-18(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZN4Util8printStrEPKci
	movl	__ZN4Util11MODE_COMMONE, %eax
	movl	%eax, 4(%esp)
	movl	$LC1, (%esp)
	call	__ZN4Util8printStrEPKci
	movl	8(%ebp), %ecx
	call	__ZN16MemoryDescriptor8getLimitEv
	movl	%eax, 8(%esp)
	movl	$10, 4(%esp)
	leal	-18(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZN4Util10digitToStrEPcji
	movl	__ZN4Util11MODE_COMMONE, %eax
	movl	%eax, 4(%esp)
	leal	-18(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZN4Util8printStrEPKci
	movl	__ZN4Util11MODE_COMMONE, %eax
	movl	%eax, 4(%esp)
	movl	$LC1, (%esp)
	call	__ZN4Util8printStrEPKci
	movl	8(%ebp), %ecx
	call	__ZN16MemoryDescriptor11isAllocableEv
	movl	%eax, 8(%esp)
	movl	$10, 4(%esp)
	leal	-18(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZN4Util10digitToStrEPcji
	movl	__ZN4Util11MODE_COMMONE, %eax
	movl	%eax, 4(%esp)
	leal	-18(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZN4Util8printStrEPKci
	movl	__ZN4Util11MODE_COMMONE, %eax
	movl	%eax, 4(%esp)
	movl	$LC2, (%esp)
	call	__ZN4Util8printStrEPKci
	nop
	leave
	ret
	.align 2
	.globl	__ZN4Test14dumpMemoryDataERKi
	.def	__ZN4Test14dumpMemoryDataERKi;	.scl	2;	.type	32;	.endef
__ZN4Test14dumpMemoryDataERKi:
	pushl	%ebp
	movl	%esp, %ebp
	nop
	popl	%ebp
	ret
	.section .rdata,"dr"
LC3:
	.ascii "DUMP SMM: \0"
	.text
	.align 2
	.globl	__ZN4Test7dumpSMMEP19SimpleMemoryManagerI8TreeNodeI16MemoryDescriptorEE
	.def	__ZN4Test7dumpSMMEP19SimpleMemoryManagerI8TreeNodeI16MemoryDescriptorEE;	.scl	2;	.type	32;	.endef
__ZN4Test7dumpSMMEP19SimpleMemoryManagerI8TreeNodeI16MemoryDescriptorEE:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$56, %esp
	movl	__ZN4Util11MODE_COMMONE, %eax
	movl	%eax, 4(%esp)
	movl	$LC3, (%esp)
	call	__ZN4Util8printStrEPKci
	movl	8(%ebp), %eax
	movl	%eax, -12(%ebp)
	movl	-12(%ebp), %eax
	movl	16(%eax), %eax
	movl	%eax, 8(%esp)
	movl	$10, 4(%esp)
	leal	-30(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZN4Util10digitToStrEPcji
	movl	__ZN4Util11MODE_COMMONE, %eax
	movl	%eax, 4(%esp)
	leal	-30(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZN4Util8printStrEPKci
	movl	__ZN4Util11MODE_COMMONE, %eax
	movl	%eax, 4(%esp)
	movl	$LC1, (%esp)
	call	__ZN4Util8printStrEPKci
	movl	8(%ebp), %eax
	movl	%eax, -16(%ebp)
	movl	-16(%ebp), %eax
	movl	12(%eax), %eax
	movl	%eax, 8(%esp)
	movl	$10, 4(%esp)
	leal	-30(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZN4Util10digitToStrEPcji
	movl	__ZN4Util11MODE_COMMONE, %eax
	movl	%eax, 4(%esp)
	leal	-30(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZN4Util8printStrEPKci
	movl	__ZN4Util11MODE_COMMONE, %eax
	movl	%eax, 4(%esp)
	movl	$LC1, (%esp)
	call	__ZN4Util8printStrEPKci
	movl	8(%ebp), %eax
	movl	%eax, -20(%ebp)
	movl	-20(%ebp), %eax
	movl	4(%eax), %eax
	movl	%eax, 8(%esp)
	movl	$10, 4(%esp)
	leal	-30(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZN4Util10digitToStrEPcji
	movl	__ZN4Util11MODE_COMMONE, %eax
	movl	%eax, 4(%esp)
	leal	-30(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZN4Util8printStrEPKci
	movl	__ZN4Util11MODE_COMMONE, %eax
	movl	%eax, 4(%esp)
	movl	$LC2, (%esp)
	call	__ZN4Util8printStrEPKci
	nop
	leave
	ret
	.section .rdata,"dr"
LC4:
	.ascii "Head: \0"
LC5:
	.ascii "NO_\0"
	.text
	.align 2
	.globl	__ZN4Test6dumpMMER13MemoryManager
	.def	__ZN4Test6dumpMMER13MemoryManager;	.scl	2;	.type	32;	.endef
__ZN4Test6dumpMMER13MemoryManager:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$56, %esp
	movl	__ZN4Util11MODE_COMMONE, %eax
	movl	%eax, 4(%esp)
	movl	$LC4, (%esp)
	call	__ZN4Util8printStrEPKci
	movl	8(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN4TreeI16MemoryDescriptorE7getHeadEv
	movl	%eax, -28(%ebp)
	movl	-28(%ebp), %eax
	addl	$4, %eax
	movl	%eax, (%esp)
	call	__ZN4Test14dumpMemoryDataERK16MemoryDescriptor
	movl	$0, -12(%ebp)
	movl	8(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN4TreeI16MemoryDescriptorE7getHeadEv
	movl	%eax, %ecx
	call	__ZN8TreeNodeI16MemoryDescriptorE6getSonEv
	movl	%eax, -16(%ebp)
L14:
	cmpl	$0, -16(%ebp)
	je	L15
	movl	-12(%ebp), %eax
	leal	1(%eax), %edx
	movl	%edx, -12(%ebp)
	movl	%eax, 8(%esp)
	movl	$10, 4(%esp)
	leal	-38(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZN4Util10digitToStrEPcji
	movl	__ZN4Util11MODE_COMMONE, %eax
	movl	%eax, 4(%esp)
	movl	$LC5, (%esp)
	call	__ZN4Util8printStrEPKci
	movl	__ZN4Util11MODE_COMMONE, %eax
	movl	%eax, 4(%esp)
	leal	-38(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZN4Util8printStrEPKci
	movl	__ZN4Util11MODE_COMMONE, %eax
	movl	%eax, 4(%esp)
	movl	$LC1, (%esp)
	call	__ZN4Util8printStrEPKci
	movl	-16(%ebp), %eax
	movl	%eax, -24(%ebp)
	movl	-24(%ebp), %eax
	addl	$4, %eax
	movl	%eax, (%esp)
	call	__ZN4Test14dumpMemoryDataERK16MemoryDescriptor
	movl	-16(%ebp), %eax
	movl	%eax, -20(%ebp)
	movl	-20(%ebp), %eax
	movl	16(%eax), %eax
	movl	%eax, -16(%ebp)
	jmp	L14
L15:
	nop
	leave
	ret
	.section .rdata,"dr"
LC6:
	.ascii "Testing: Memory. \12\0"
LC7:
	.ascii "done init 1.\12\0"
LC8:
	.ascii "done allocFreeStart.\12\0"
LC9:
	.ascii "End .\12\0"
	.text
	.align 2
	.globl	__ZN4Test10testMemoryEv
	.def	__ZN4Test10testMemoryEv;	.scl	2;	.type	32;	.endef
__ZN4Test10testMemoryEv:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$104, %esp
	movl	%ecx, -76(%ebp)
	movl	-76(%ebp), %eax
	movl	$LC6, (%esp)
	movl	%eax, %ecx
	call	__ZN7Printer5putszEPc
	subl	$4, %esp
	movl	$1280, %ecx
	movl	__ZN8PMLoader15FREE_HEAP_STARTE, %edx
	leal	-56(%ebp), %eax
	movl	%ecx, 4(%esp)
	movl	%edx, (%esp)
	movl	%eax, %ecx
	call	__ZN19SimpleMemoryManagerI8TreeNodeI16MemoryDescriptorEEC1Eij
	subl	$8, %esp
	leal	-64(%ebp), %eax
	movl	$0, 12(%esp)
	movl	$1048575, 8(%esp)
	movl	$0, 4(%esp)
	leal	-56(%ebp), %edx
	movl	%edx, (%esp)
	movl	%eax, %ecx
	call	__ZN13MemoryManagerC1EP19SimpleMemoryManagerI8TreeNodeI16MemoryDescriptorEEiji
	subl	$16, %esp
	movl	__ZN8PMLoader10CODE_STARTE, %eax
	movl	%eax, %edx
	leal	-32(%ebp), %eax
	movl	%edx, 8(%esp)
	movl	$0, 4(%esp)
	leal	-64(%ebp), %edx
	movl	%edx, (%esp)
	movl	%eax, %ecx
	call	__ZN13MemoryManager14allocFreeStartEij
	subl	$12, %esp
	leal	-32(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN13MemoryManagerD1Ev
	movl	-76(%ebp), %eax
	movl	$LC7, (%esp)
	movl	%eax, %ecx
	call	__ZN7Printer5putszEPc
	subl	$4, %esp
	movl	__ZN8PMLoader10CODE_LIMITE, %ecx
	movl	$1374389535, %edx
	movl	%ecx, %eax
	imull	%edx
	sarl	$5, %edx
	movl	%ecx, %eax
	sarl	$31, %eax
	subl	%eax, %edx
	movl	%edx, %eax
	movl	%eax, %ecx
	movl	__ZN8PMLoader10CODE_STARTE, %edx
	leal	-24(%ebp), %eax
	movl	%ecx, 8(%esp)
	movl	%edx, 4(%esp)
	leal	-64(%ebp), %edx
	movl	%edx, (%esp)
	movl	%eax, %ecx
	call	__ZN13MemoryManager14allocFreeStartEij
	subl	$12, %esp
	leal	-24(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN13MemoryManagerD1Ev
	movl	-76(%ebp), %eax
	movl	$LC8, (%esp)
	movl	%eax, %ecx
	call	__ZN7Printer5putszEPc
	subl	$4, %esp
	leal	-64(%ebp), %eax
	movl	$4, (%esp)
	movl	%eax, %ecx
	call	__ZN13MemoryManager4mnewEj
	subl	$4, %esp
	movl	%eax, -12(%ebp)
	movl	-12(%ebp), %eax
	movl	-76(%ebp), %edx
	addl	$56, %edx
	movl	%eax, 8(%esp)
	movl	$10, 4(%esp)
	movl	%edx, (%esp)
	call	__ZN4Util10digitToStrEPcji
	movl	-76(%ebp), %eax
	leal	56(%eax), %edx
	movl	-76(%ebp), %eax
	movl	%edx, (%esp)
	movl	%eax, %ecx
	call	__ZN7Printer5putszEPc
	subl	$4, %esp
	movl	-76(%ebp), %eax
	movl	$LC1, (%esp)
	movl	%eax, %ecx
	call	__ZN7Printer5putszEPc
	subl	$4, %esp
	movl	-12(%ebp), %eax
	movl	(%eax), %eax
	movl	-76(%ebp), %edx
	addl	$56, %edx
	movl	%eax, 8(%esp)
	movl	$10, 4(%esp)
	movl	%edx, (%esp)
	call	__ZN4Util10digitToStrEPcji
	movl	-76(%ebp), %eax
	leal	56(%eax), %edx
	movl	-76(%ebp), %eax
	movl	%edx, (%esp)
	movl	%eax, %ecx
	call	__ZN7Printer5putszEPc
	subl	$4, %esp
	movl	-76(%ebp), %eax
	movl	$LC2, (%esp)
	movl	%eax, %ecx
	call	__ZN7Printer5putszEPc
	subl	$4, %esp
	leal	-64(%ebp), %eax
	movl	$4, (%esp)
	movl	%eax, %ecx
	call	__ZN13MemoryManager4mnewEj
	subl	$4, %esp
	movl	%eax, -16(%ebp)
	movl	-16(%ebp), %eax
	movl	-76(%ebp), %edx
	addl	$56, %edx
	movl	%eax, 8(%esp)
	movl	$10, 4(%esp)
	movl	%edx, (%esp)
	call	__ZN4Util10digitToStrEPcji
	movl	-76(%ebp), %eax
	leal	56(%eax), %edx
	movl	-76(%ebp), %eax
	movl	%edx, (%esp)
	movl	%eax, %ecx
	call	__ZN7Printer5putszEPc
	subl	$4, %esp
	movl	-76(%ebp), %eax
	movl	$LC1, (%esp)
	movl	%eax, %ecx
	call	__ZN7Printer5putszEPc
	subl	$4, %esp
	movl	-16(%ebp), %eax
	movl	(%eax), %eax
	movl	-76(%ebp), %edx
	addl	$56, %edx
	movl	%eax, 8(%esp)
	movl	$10, 4(%esp)
	movl	%edx, (%esp)
	call	__ZN4Util10digitToStrEPcji
	movl	-76(%ebp), %eax
	leal	56(%eax), %edx
	movl	-76(%ebp), %eax
	movl	%edx, (%esp)
	movl	%eax, %ecx
	call	__ZN7Printer5putszEPc
	subl	$4, %esp
	leal	-64(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZN4Test6dumpMMER13MemoryManager
	movl	-76(%ebp), %eax
	movl	$LC2, (%esp)
	movl	%eax, %ecx
	call	__ZN7Printer5putszEPc
	subl	$4, %esp
	movl	-76(%ebp), %eax
	movl	$LC9, (%esp)
	movl	%eax, %ecx
	call	__ZN7Printer5putszEPc
	subl	$4, %esp
	leal	-64(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN13MemoryManagerD1Ev
	leal	-56(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN19SimpleMemoryManagerI8TreeNodeI16MemoryDescriptorEED1Ev
	nop
	leave
	ret
	.section .rdata,"dr"
LC10:
	.ascii "Testing: List. \12\0"
LC11:
	.ascii "size is:\0"
LC12:
	.ascii "\12Free:\0"
LC13:
	.ascii "\12End.\12\0"
	.text
	.align 2
	.globl	__ZN4Test8testListEv
	.def	__ZN4Test8testListEv;	.scl	2;	.type	32;	.endef
__ZN4Test8testListEv:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$136, %esp
	movl	%ecx, -108(%ebp)
	movl	-108(%ebp), %eax
	movl	$LC10, (%esp)
	movl	%eax, %ecx
	call	__ZN7Printer5putszEPc
	subl	$4, %esp
	movl	$1600, %ecx
	movl	__ZN8PMLoader15FREE_HEAP_STARTE, %edx
	leal	-74(%ebp), %eax
	movl	%ecx, 4(%esp)
	movl	%edx, (%esp)
	movl	%eax, %ecx
	call	__ZN19SimpleMemoryManagerI8ListNodeIiEEC1Eij
	subl	$8, %esp
	leal	-90(%ebp), %eax
	leal	-74(%ebp), %edx
	movl	%edx, (%esp)
	movl	%eax, %ecx
	call	__ZN10LinkedListIiEC1EP19SimpleMemoryManagerI8ListNodeIiEE
	subl	$4, %esp
	movl	$5, -40(%ebp)
	leal	-90(%ebp), %eax
	leal	-40(%ebp), %edx
	movl	%edx, (%esp)
	movl	%eax, %ecx
	call	__ZN10LinkedListIiE6appendERKi
	subl	$4, %esp
	movl	%eax, -12(%ebp)
	movl	-12(%ebp), %eax
	movl	%eax, -16(%ebp)
	movl	-16(%ebp), %eax
	addl	$4, %eax
	movl	(%eax), %eax
	movl	%eax, 8(%esp)
	movl	$10, 4(%esp)
	leal	-50(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZN4Util10digitToStrEPcji
	movl	-108(%ebp), %eax
	leal	-50(%ebp), %edx
	movl	%edx, (%esp)
	movl	%eax, %ecx
	call	__ZN7Printer5putszEPc
	subl	$4, %esp
	movl	-108(%ebp), %eax
	movl	$LC2, (%esp)
	movl	%eax, %ecx
	call	__ZN7Printer5putszEPc
	subl	$4, %esp
	movl	$7, -36(%ebp)
	leal	-90(%ebp), %eax
	leal	-36(%ebp), %edx
	movl	%edx, (%esp)
	movl	%eax, %ecx
	call	__ZN10LinkedListIiE6appendERKi
	subl	$4, %esp
	movl	$6, -32(%ebp)
	leal	-90(%ebp), %eax
	leal	-32(%ebp), %edx
	movl	%edx, (%esp)
	movl	%eax, %ecx
	call	__ZN10LinkedListIiE6appendERKi
	subl	$4, %esp
	movl	-108(%ebp), %eax
	movl	$LC11, (%esp)
	movl	%eax, %ecx
	call	__ZN7Printer5putszEPc
	subl	$4, %esp
	movl	-78(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	$10, 4(%esp)
	leal	-50(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZN4Util10digitToStrEPcji
	movl	-108(%ebp), %eax
	leal	-50(%ebp), %edx
	movl	%edx, (%esp)
	movl	%eax, %ecx
	call	__ZN7Printer5putszEPc
	subl	$4, %esp
	movl	-108(%ebp), %eax
	movl	$LC2, (%esp)
	movl	%eax, %ecx
	call	__ZN7Printer5putszEPc
	subl	$4, %esp
	leal	-90(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN10LinkedListIiE6removeEv
	movl	%eax, -12(%ebp)
	movl	-12(%ebp), %eax
	movl	%eax, -20(%ebp)
	movl	-20(%ebp), %eax
	addl	$4, %eax
	movl	(%eax), %eax
	movl	%eax, 8(%esp)
	movl	$10, 4(%esp)
	leal	-50(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZN4Util10digitToStrEPcji
	leal	-74(%ebp), %eax
	movl	-12(%ebp), %edx
	movl	%edx, (%esp)
	movl	%eax, %ecx
	call	__ZN19SimpleMemoryManagerI8ListNodeIiEE8withdrawEPS1_
	subl	$4, %esp
	movl	-108(%ebp), %eax
	leal	-50(%ebp), %edx
	movl	%edx, (%esp)
	movl	%eax, %ecx
	call	__ZN7Printer5putszEPc
	subl	$4, %esp
	leal	-90(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN10LinkedListIiE6removeEv
	movl	%eax, -12(%ebp)
	movl	-12(%ebp), %eax
	movl	%eax, -24(%ebp)
	movl	-24(%ebp), %eax
	addl	$4, %eax
	movl	(%eax), %eax
	movl	%eax, 8(%esp)
	movl	$10, 4(%esp)
	leal	-50(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZN4Util10digitToStrEPcji
	leal	-74(%ebp), %eax
	movl	-12(%ebp), %edx
	movl	%edx, (%esp)
	movl	%eax, %ecx
	call	__ZN19SimpleMemoryManagerI8ListNodeIiEE8withdrawEPS1_
	subl	$4, %esp
	movl	-108(%ebp), %eax
	leal	-50(%ebp), %edx
	movl	%edx, (%esp)
	movl	%eax, %ecx
	call	__ZN7Printer5putszEPc
	subl	$4, %esp
	leal	-90(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN10LinkedListIiE6removeEv
	movl	%eax, -12(%ebp)
	movl	-12(%ebp), %eax
	movl	%eax, -28(%ebp)
	movl	-28(%ebp), %eax
	addl	$4, %eax
	movl	(%eax), %eax
	movl	%eax, 8(%esp)
	movl	$10, 4(%esp)
	leal	-50(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZN4Util10digitToStrEPcji
	leal	-74(%ebp), %eax
	movl	-12(%ebp), %edx
	movl	%edx, (%esp)
	movl	%eax, %ecx
	call	__ZN19SimpleMemoryManagerI8ListNodeIiEE8withdrawEPS1_
	subl	$4, %esp
	movl	-108(%ebp), %eax
	leal	-50(%ebp), %edx
	movl	%edx, (%esp)
	movl	%eax, %ecx
	call	__ZN7Printer5putszEPc
	subl	$4, %esp
	leal	-90(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN10LinkedListIiE4freeEv
	movl	-62(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	$10, 4(%esp)
	leal	-50(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZN4Util10digitToStrEPcji
	movl	-108(%ebp), %eax
	movl	$LC12, (%esp)
	movl	%eax, %ecx
	call	__ZN7Printer5putszEPc
	subl	$4, %esp
	movl	-108(%ebp), %eax
	leal	-50(%ebp), %edx
	movl	%edx, (%esp)
	movl	%eax, %ecx
	call	__ZN7Printer5putszEPc
	subl	$4, %esp
	movl	-108(%ebp), %eax
	movl	$LC13, (%esp)
	movl	%eax, %ecx
	call	__ZN7Printer5putszEPc
	subl	$4, %esp
	leal	-90(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN10LinkedListIiED1Ev
	leal	-74(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN19SimpleMemoryManagerI8ListNodeIiEED1Ev
	nop
	leave
	ret
	.section .rdata,"dr"
LC14:
	.ascii "Testing: Queue. \12\0"
LC15:
	.ascii "Current size:\0"
LC16:
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
	movl	-156(%ebp), %eax
	movl	$LC14, (%esp)
	movl	%eax, %ecx
	call	__ZN7Printer5putszEPc
	subl	$4, %esp
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
	movl	$LC15, (%esp)
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
	movl	$LC16, (%esp)
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
	call	__ZN4Test10testMemoryEv
	nop
	leave
	ret
.lcomm __ZZN4Test14dumpMemoryDataERK16MemoryDescriptorE5count,4,4
	.ident	"GCC: (GNU) 5.4.0"
	.def	__ZN7PrinterC1Ejjjji;	.scl	2;	.type	32;	.endef
	.def	__ZN7PrinterD1Ev;	.scl	2;	.type	32;	.endef
	.def	__ZN4Util10digitToStrEPcji;	.scl	2;	.type	32;	.endef
	.def	__ZN4Util8printStrEPKci;	.scl	2;	.type	32;	.endef
	.def	__ZN16MemoryDescriptor8getStartEv;	.scl	2;	.type	32;	.endef
	.def	__ZN16MemoryDescriptor8getLimitEv;	.scl	2;	.type	32;	.endef
	.def	__ZN16MemoryDescriptor11isAllocableEv;	.scl	2;	.type	32;	.endef
	.def	__ZN4TreeI16MemoryDescriptorE7getHeadEv;	.scl	2;	.type	32;	.endef
	.def	__ZN8TreeNodeI16MemoryDescriptorE6getSonEv;	.scl	2;	.type	32;	.endef
	.def	__ZN7Printer5putszEPc;	.scl	2;	.type	32;	.endef
	.def	__ZN19SimpleMemoryManagerI8TreeNodeI16MemoryDescriptorEEC1Eij;	.scl	2;	.type	32;	.endef
	.def	__ZN13MemoryManagerC1EP19SimpleMemoryManagerI8TreeNodeI16MemoryDescriptorEEiji;	.scl	2;	.type	32;	.endef
	.def	__ZN13MemoryManager14allocFreeStartEij;	.scl	2;	.type	32;	.endef
	.def	__ZN13MemoryManagerD1Ev;	.scl	2;	.type	32;	.endef
	.def	__ZN13MemoryManager4mnewEj;	.scl	2;	.type	32;	.endef
	.def	__ZN19SimpleMemoryManagerI8TreeNodeI16MemoryDescriptorEED1Ev;	.scl	2;	.type	32;	.endef
	.def	__ZN19SimpleMemoryManagerI8ListNodeIiEEC1Eij;	.scl	2;	.type	32;	.endef
	.def	__ZN10LinkedListIiEC1EP19SimpleMemoryManagerI8ListNodeIiEE;	.scl	2;	.type	32;	.endef
	.def	__ZN10LinkedListIiE6appendERKi;	.scl	2;	.type	32;	.endef
	.def	__ZN10LinkedListIiE6removeEv;	.scl	2;	.type	32;	.endef
	.def	__ZN19SimpleMemoryManagerI8ListNodeIiEE8withdrawEPS1_;	.scl	2;	.type	32;	.endef
	.def	__ZN10LinkedListIiE4freeEv;	.scl	2;	.type	32;	.endef
	.def	__ZN10LinkedListIiED1Ev;	.scl	2;	.type	32;	.endef
	.def	__ZN19SimpleMemoryManagerI8ListNodeIiEED1Ev;	.scl	2;	.type	32;	.endef
	.def	__ZN5QueueIhEC1EPhj;	.scl	2;	.type	32;	.endef
	.def	__ZN5QueueIhE3addEh;	.scl	2;	.type	32;	.endef
	.def	__ZN7Printer4putcEi;	.scl	2;	.type	32;	.endef
	.def	__ZN5QueueIhE6removeEv;	.scl	2;	.type	32;	.endef
	.def	__ZN5QueueIhED1Ev;	.scl	2;	.type	32;	.endef
