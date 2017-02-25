	.file	"Memory.cpp"
/APP
	.code32 
	
/NO_APP
	.text
	.align 2
	.globl	__ZN16MemoryDescriptorC2Eiji
	.def	__ZN16MemoryDescriptorC2Eiji;	.scl	2;	.type	32;	.endef
__ZN16MemoryDescriptorC2Eiji:
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
	movl	16(%ebp), %edx
	movl	%edx, 8(%eax)
	nop
	leave
	ret	$12
	.globl	__ZN16MemoryDescriptorC1Eiji
	.def	__ZN16MemoryDescriptorC1Eiji;	.scl	2;	.type	32;	.endef
	.set	__ZN16MemoryDescriptorC1Eiji,__ZN16MemoryDescriptorC2Eiji
	.align 2
	.globl	__ZN16MemoryDescriptor4initEiji
	.def	__ZN16MemoryDescriptor4initEiji;	.scl	2;	.type	32;	.endef
__ZN16MemoryDescriptor4initEiji:
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
	movl	16(%ebp), %edx
	movl	%edx, 8(%eax)
	movl	-4(%ebp), %eax
	leave
	ret	$12
	.align 2
	.globl	__ZN16MemoryDescriptorD2Ev
	.def	__ZN16MemoryDescriptorD2Ev;	.scl	2;	.type	32;	.endef
__ZN16MemoryDescriptorD2Ev:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	%ecx, -4(%ebp)
	nop
	leave
	ret
	.globl	__ZN16MemoryDescriptorD1Ev
	.def	__ZN16MemoryDescriptorD1Ev;	.scl	2;	.type	32;	.endef
	.set	__ZN16MemoryDescriptorD1Ev,__ZN16MemoryDescriptorD2Ev
	.align 2
	.globl	__ZN16MemoryDescriptor8getStartEv
	.def	__ZN16MemoryDescriptor8getStartEv;	.scl	2;	.type	32;	.endef
__ZN16MemoryDescriptor8getStartEv:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	%ecx, -4(%ebp)
	movl	-4(%ebp), %eax
	movl	(%eax), %eax
	leave
	ret
	.align 2
	.globl	__ZN16MemoryDescriptor12setAllocableEi
	.def	__ZN16MemoryDescriptor12setAllocableEi;	.scl	2;	.type	32;	.endef
__ZN16MemoryDescriptor12setAllocableEi:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	%ecx, -4(%ebp)
	movl	-4(%ebp), %eax
	movl	8(%ebp), %edx
	movl	%edx, 8(%eax)
	movl	-4(%ebp), %eax
	leave
	ret	$4
	.align 2
	.globl	__ZN16MemoryDescriptor8setLimitEj
	.def	__ZN16MemoryDescriptor8setLimitEj;	.scl	2;	.type	32;	.endef
__ZN16MemoryDescriptor8setLimitEj:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	%ecx, -4(%ebp)
	movl	-4(%ebp), %eax
	movl	8(%ebp), %edx
	movl	%edx, 4(%eax)
	nop
	leave
	ret	$4
	.align 2
	.globl	__ZN16MemoryDescriptor8getLimitEv
	.def	__ZN16MemoryDescriptor8getLimitEv;	.scl	2;	.type	32;	.endef
__ZN16MemoryDescriptor8getLimitEv:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	%ecx, -4(%ebp)
	movl	-4(%ebp), %eax
	movl	4(%eax), %eax
	leave
	ret
	.align 2
	.globl	__ZN16MemoryDescriptor11isAllocableEv
	.def	__ZN16MemoryDescriptor11isAllocableEv;	.scl	2;	.type	32;	.endef
__ZN16MemoryDescriptor11isAllocableEv:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	%ecx, -4(%ebp)
	movl	-4(%ebp), %eax
	movl	8(%eax), %eax
	leave
	ret
	.align 2
	.globl	__ZN16MemoryDescriptor8setStartEi
	.def	__ZN16MemoryDescriptor8setStartEi;	.scl	2;	.type	32;	.endef
__ZN16MemoryDescriptor8setStartEi:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	%ecx, -4(%ebp)
	movl	-4(%ebp), %eax
	movl	8(%ebp), %edx
	movl	%edx, (%eax)
	nop
	leave
	ret	$4
	.align 2
	.globl	__ZN13MemoryManagerC2EP19SimpleMemoryManagerI8TreeNodeI16MemoryDescriptorEE
	.def	__ZN13MemoryManagerC2EP19SimpleMemoryManagerI8TreeNodeI16MemoryDescriptorEE;	.scl	2;	.type	32;	.endef
__ZN13MemoryManagerC2EP19SimpleMemoryManagerI8TreeNodeI16MemoryDescriptorEE:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	%ecx, -12(%ebp)
	movl	-12(%ebp), %eax
	movl	8(%ebp), %edx
	movl	%edx, (%esp)
	movl	%eax, %ecx
	call	__ZN4TreeI16MemoryDescriptorEC2EP19SimpleMemoryManagerI8TreeNodeIS0_EE
	subl	$4, %esp
	nop
	leave
	ret	$4
	.globl	__ZN13MemoryManagerC1EP19SimpleMemoryManagerI8TreeNodeI16MemoryDescriptorEE
	.def	__ZN13MemoryManagerC1EP19SimpleMemoryManagerI8TreeNodeI16MemoryDescriptorEE;	.scl	2;	.type	32;	.endef
	.set	__ZN13MemoryManagerC1EP19SimpleMemoryManagerI8TreeNodeI16MemoryDescriptorEE,__ZN13MemoryManagerC2EP19SimpleMemoryManagerI8TreeNodeI16MemoryDescriptorEE
	.align 2
	.globl	__ZN13MemoryManagerC2EP19SimpleMemoryManagerI8TreeNodeI16MemoryDescriptorEEiji
	.def	__ZN13MemoryManagerC2EP19SimpleMemoryManagerI8TreeNodeI16MemoryDescriptorEEiji;	.scl	2;	.type	32;	.endef
__ZN13MemoryManagerC2EP19SimpleMemoryManagerI8TreeNodeI16MemoryDescriptorEEiji:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$72, %esp
	movl	%ecx, -28(%ebp)
	movl	-28(%ebp), %eax
	movl	8(%ebp), %edx
	movl	%edx, (%esp)
	movl	%eax, %ecx
	call	__ZN13MemoryManagerC1EP19SimpleMemoryManagerI8TreeNodeI16MemoryDescriptorEE
	subl	$4, %esp
	leal	-20(%ebp), %eax
	movl	20(%ebp), %edx
	movl	%edx, 8(%esp)
	movl	16(%ebp), %edx
	movl	%edx, 4(%esp)
	movl	12(%ebp), %edx
	movl	%edx, (%esp)
	movl	%eax, %ecx
	call	__ZN16MemoryDescriptorC1Eiji
	subl	$12, %esp
	movl	8(%ebp), %ecx
	call	__ZN19SimpleMemoryManagerI8TreeNodeI16MemoryDescriptorEE6getNewEv
	movl	%eax, %edx
	movl	$0, 16(%esp)
	movl	$0, 12(%esp)
	movl	$0, 8(%esp)
	movl	$0, 4(%esp)
	leal	-20(%ebp), %eax
	movl	%eax, (%esp)
	movl	%edx, %ecx
	call	__ZN8TreeNodeI16MemoryDescriptorE4initERKS0_PS1_S4_S4_S4_
	subl	$20, %esp
	movl	%eax, %edx
	movl	-28(%ebp), %eax
	movl	%edx, (%esp)
	movl	%eax, %ecx
	call	__ZN4TreeI16MemoryDescriptorE7setHeadEP8TreeNodeIS0_E
	subl	$4, %esp
	leal	-20(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN16MemoryDescriptorD1Ev
	nop
	leave
	ret	$16
	.globl	__ZN13MemoryManagerC1EP19SimpleMemoryManagerI8TreeNodeI16MemoryDescriptorEEiji
	.def	__ZN13MemoryManagerC1EP19SimpleMemoryManagerI8TreeNodeI16MemoryDescriptorEEiji;	.scl	2;	.type	32;	.endef
	.set	__ZN13MemoryManagerC1EP19SimpleMemoryManagerI8TreeNodeI16MemoryDescriptorEEiji,__ZN13MemoryManagerC2EP19SimpleMemoryManagerI8TreeNodeI16MemoryDescriptorEEiji
	.align 2
	.globl	__ZN13MemoryManagerD2Ev
	.def	__ZN13MemoryManagerD2Ev;	.scl	2;	.type	32;	.endef
__ZN13MemoryManagerD2Ev:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	%ecx, -12(%ebp)
	movl	-12(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN4TreeI16MemoryDescriptorED2Ev
	nop
	leave
	ret
	.globl	__ZN13MemoryManagerD1Ev
	.def	__ZN13MemoryManagerD1Ev;	.scl	2;	.type	32;	.endef
	.set	__ZN13MemoryManagerD1Ev,__ZN13MemoryManagerD2Ev
	.align 2
	.globl	__ZN13MemoryManager16withDrawToParentEv
	.def	__ZN13MemoryManager16withDrawToParentEv;	.scl	2;	.type	32;	.endef
__ZN13MemoryManager16withDrawToParentEv:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	%ecx, -4(%ebp)
	nop
	leave
	ret
	.align 2
	.globl	__ZN13MemoryManager12allocOutNodeEP8TreeNodeI16MemoryDescriptorEij
	.def	__ZN13MemoryManager12allocOutNodeEP8TreeNodeI16MemoryDescriptorEij;	.scl	2;	.type	32;	.endef
__ZN13MemoryManager12allocOutNodeEP8TreeNodeI16MemoryDescriptorEij:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$120, %esp
	movl	%ecx, -76(%ebp)
	movl	$0, -12(%ebp)
	cmpl	$0, 8(%ebp)
	je	L20
	movl	8(%ebp), %eax
	movl	%eax, -24(%ebp)
	movl	-24(%ebp), %eax
	addl	$4, %eax
	movl	%eax, %ecx
	call	__ZN16MemoryDescriptor8getStartEv
	movl	%eax, %edx
	movl	12(%ebp), %eax
	subl	%edx, %eax
	movl	%eax, -20(%ebp)
	movl	8(%ebp), %eax
	movl	%eax, -48(%ebp)
	movl	-48(%ebp), %eax
	addl	$4, %eax
	movl	%eax, %ecx
	call	__ZN16MemoryDescriptor8getLimitEv
	subl	16(%ebp), %eax
	subl	-20(%ebp), %eax
	movl	%eax, -28(%ebp)
	cmpl	$0, -20(%ebp)
	je	L23
	movl	8(%ebp), %eax
	movl	%eax, -16(%ebp)
	movl	-16(%ebp), %eax
	leal	4(%eax), %edx
	movl	-20(%ebp), %eax
	movl	%eax, (%esp)
	movl	%edx, %ecx
	call	__ZN16MemoryDescriptor8setLimitEj
	subl	$4, %esp
	leal	-72(%ebp), %eax
	movl	$0, 8(%esp)
	movl	16(%ebp), %edx
	movl	%edx, 4(%esp)
	movl	12(%ebp), %edx
	movl	%edx, (%esp)
	movl	%eax, %ecx
	call	__ZN16MemoryDescriptorC1Eiji
	subl	$12, %esp
	movl	-76(%ebp), %eax
	movl	(%eax), %eax
	movl	%eax, %ecx
	call	__ZN19SimpleMemoryManagerI8TreeNodeI16MemoryDescriptorEE6getNewEv
	movl	%eax, %edx
	movl	$0, 16(%esp)
	movl	$0, 12(%esp)
	movl	$0, 8(%esp)
	movl	$0, 4(%esp)
	leal	-72(%ebp), %eax
	movl	%eax, (%esp)
	movl	%edx, %ecx
	call	__ZN8TreeNodeI16MemoryDescriptorE4initERKS0_PS1_S4_S4_S4_
	subl	$20, %esp
	movl	%eax, -12(%ebp)
	leal	-72(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN16MemoryDescriptorD1Ev
	movl	8(%ebp), %eax
	movl	-12(%ebp), %edx
	movl	%edx, (%esp)
	movl	%eax, %ecx
	call	__ZN8ListNodeI16MemoryDescriptorE10insertNextEPS1_
	subl	$4, %esp
	jmp	L25
L23:
	movl	8(%ebp), %eax
	movl	%eax, -12(%ebp)
	movl	-12(%ebp), %eax
	movl	%eax, -36(%ebp)
	movl	-36(%ebp), %eax
	leal	4(%eax), %edx
	movl	12(%ebp), %eax
	movl	%eax, (%esp)
	movl	%edx, %ecx
	call	__ZN16MemoryDescriptor8setStartEi
	subl	$4, %esp
	movl	-12(%ebp), %eax
	movl	%eax, -40(%ebp)
	movl	-40(%ebp), %eax
	leal	4(%eax), %edx
	movl	16(%ebp), %eax
	movl	%eax, (%esp)
	movl	%edx, %ecx
	call	__ZN16MemoryDescriptor8setLimitEj
	subl	$4, %esp
	movl	-12(%ebp), %eax
	movl	%eax, -32(%ebp)
	movl	-32(%ebp), %eax
	addl	$4, %eax
	movl	$0, (%esp)
	movl	%eax, %ecx
	call	__ZN16MemoryDescriptor12setAllocableEi
	subl	$4, %esp
L25:
	cmpl	$0, -28(%ebp)
	je	L20
	movl	12(%ebp), %edx
	movl	16(%ebp), %eax
	addl	%edx, %eax
	movl	%eax, %ecx
	leal	-60(%ebp), %eax
	movl	$1, 8(%esp)
	movl	-28(%ebp), %edx
	movl	%edx, 4(%esp)
	movl	%ecx, (%esp)
	movl	%eax, %ecx
	call	__ZN16MemoryDescriptorC1Eiji
	subl	$12, %esp
	movl	-76(%ebp), %eax
	movl	(%eax), %eax
	movl	%eax, %ecx
	call	__ZN19SimpleMemoryManagerI8TreeNodeI16MemoryDescriptorEE6getNewEv
	movl	%eax, %edx
	movl	$0, 16(%esp)
	movl	$0, 12(%esp)
	movl	$0, 8(%esp)
	movl	$0, 4(%esp)
	leal	-60(%ebp), %eax
	movl	%eax, (%esp)
	movl	%edx, %ecx
	call	__ZN8TreeNodeI16MemoryDescriptorE4initERKS0_PS1_S4_S4_S4_
	subl	$20, %esp
	movl	%eax, -44(%ebp)
	leal	-60(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN16MemoryDescriptorD1Ev
	movl	-12(%ebp), %eax
	movl	-44(%ebp), %edx
	movl	%edx, (%esp)
	movl	%eax, %ecx
	call	__ZN8ListNodeI16MemoryDescriptorE10insertNextEPS1_
	subl	$4, %esp
L20:
	movl	-12(%ebp), %eax
	leave
	ret	$12
	.align 2
	.globl	__ZN13MemoryManager14allocFreeStartEij
	.def	__ZN13MemoryManager14allocFreeStartEij;	.scl	2;	.type	32;	.endef
__ZN13MemoryManager14allocFreeStartEij:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$56, %esp
	movl	%ecx, -28(%ebp)
	movl	8(%ebp), %eax
	movl	(%eax), %edx
	movl	-28(%ebp), %eax
	movl	%edx, (%esp)
	movl	%eax, %ecx
	call	__ZN13MemoryManagerC1EP19SimpleMemoryManagerI8TreeNodeI16MemoryDescriptorEE
	subl	$4, %esp
	cmpl	$0, 16(%ebp)
	je	L32
	movl	8(%ebp), %ecx
	call	__ZN13MemoryManager13isNullManagerEv
	testl	%eax, %eax
	je	L33
L32:
	movl	$1, %eax
	jmp	L34
L33:
	movl	$0, %eax
L34:
	testb	%al, %al
	je	L35
	movl	-28(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN13MemoryManager7setNullEv
	jmp	L38
L35:
	movl	8(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN4TreeI16MemoryDescriptorE7getHeadEv
	movl	%eax, (%esp)
	movl	8(%ebp), %ecx
	call	__ZN13MemoryManager16copyOnAllocationEP8TreeNodeI16MemoryDescriptorE
	subl	$4, %esp
	movl	8(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN4TreeI16MemoryDescriptorE7getHeadEv
	movl	%eax, %edx
	movl	16(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	%edx, (%esp)
	call	__ZN13MemoryManager14findFirstStartEP8TreeNodeI16MemoryDescriptorEij
	movl	%eax, -12(%ebp)
	movl	16(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	-12(%ebp), %eax
	movl	%eax, (%esp)
	movl	8(%ebp), %ecx
	call	__ZN13MemoryManager12allocOutNodeEP8TreeNodeI16MemoryDescriptorEij
	subl	$12, %esp
	movl	%eax, %edx
	movl	-28(%ebp), %eax
	movl	%edx, (%esp)
	movl	%eax, %ecx
	call	__ZN4TreeI16MemoryDescriptorE7setHeadEP8TreeNodeIS0_E
	subl	$4, %esp
L38:
	nop
	movl	-28(%ebp), %eax
	leave
	ret	$12
	.align 2
	.globl	__ZN13MemoryManager9allocFreeEj
	.def	__ZN13MemoryManager9allocFreeEj;	.scl	2;	.type	32;	.endef
__ZN13MemoryManager9allocFreeEj:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	%ecx, -4(%ebp)
	nop
	movl	-4(%ebp), %eax
	leave
	ret	$8
	.align 2
	.globl	__ZN13MemoryManager4mnewEj
	.def	__ZN13MemoryManager4mnewEj;	.scl	2;	.type	32;	.endef
__ZN13MemoryManager4mnewEj:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$56, %esp
	movl	%ecx, -28(%ebp)
	movl	-28(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN4TreeI16MemoryDescriptorE7getHeadEv
	movl	%eax, %edx
	movl	8(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	%edx, (%esp)
	call	__ZN13MemoryManager12findFirstLenEP8TreeNodeI16MemoryDescriptorEj
	movl	%eax, -12(%ebp)
	cmpl	$0, -12(%ebp)
	je	L41
	movl	-12(%ebp), %eax
	movl	%eax, -24(%ebp)
	movl	-24(%ebp), %eax
	addl	$4, %eax
	movl	%eax, %ecx
	call	__ZN16MemoryDescriptor8getStartEv
	movl	%eax, %ecx
	movl	-28(%ebp), %eax
	movl	8(%ebp), %edx
	movl	%edx, 8(%esp)
	movl	%ecx, 4(%esp)
	movl	-12(%ebp), %edx
	movl	%edx, (%esp)
	movl	%eax, %ecx
	call	__ZN13MemoryManager12allocOutNodeEP8TreeNodeI16MemoryDescriptorEij
	subl	$12, %esp
	movl	%eax, -20(%ebp)
	cmpl	$0, -20(%ebp)
	je	L41
	movl	-20(%ebp), %eax
	movl	%eax, -16(%ebp)
	movl	-16(%ebp), %eax
	addl	$4, %eax
	movl	%eax, %ecx
	call	__ZN16MemoryDescriptor8getStartEv
	jmp	L45
L41:
	movl	$0, %eax
L45:
	leave
	ret	$4
	.align 2
	.globl	__ZN13MemoryManager7mdeleteEPvj
	.def	__ZN13MemoryManager7mdeleteEPvj;	.scl	2;	.type	32;	.endef
__ZN13MemoryManager7mdeleteEPvj:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	%ecx, -4(%ebp)
	nop
	leave
	ret	$8
	.align 2
	.globl	__ZN13MemoryManager4freeEv
	.def	__ZN13MemoryManager4freeEv;	.scl	2;	.type	32;	.endef
__ZN13MemoryManager4freeEv:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	%ecx, -4(%ebp)
	nop
	leave
	ret
	.align 2
	.globl	__ZN13MemoryManager14findFirstStartEP8TreeNodeI16MemoryDescriptorEij
	.def	__ZN13MemoryManager14findFirstStartEP8TreeNodeI16MemoryDescriptorEij;	.scl	2;	.type	32;	.endef
__ZN13MemoryManager14findFirstStartEP8TreeNodeI16MemoryDescriptorEij:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$36, %esp
	movl	8(%ebp), %ecx
	call	__ZN8TreeNodeI16MemoryDescriptorE6getSonEv
	movl	%eax, -12(%ebp)
L53:
	cmpl	$0, -12(%ebp)
	je	L49
	movl	-12(%ebp), %eax
	movl	%eax, -24(%ebp)
	movl	-24(%ebp), %eax
	addl	$4, %eax
	movl	%eax, %ecx
	call	__ZN16MemoryDescriptor8getStartEv
	cmpl	12(%ebp), %eax
	jle	L49
	movl	$1, %eax
	jmp	L51
L49:
	movl	$0, %eax
L51:
	testb	%al, %al
	je	L52
	movl	-12(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZN13MemoryManager13nextAllocableEP8TreeNodeI16MemoryDescriptorE
	movl	%eax, -12(%ebp)
	jmp	L53
L52:
	cmpl	$0, -12(%ebp)
	je	L54
	movl	-12(%ebp), %eax
	movl	%eax, -20(%ebp)
	movl	-20(%ebp), %eax
	addl	$4, %eax
	movl	%eax, %ecx
	call	__ZN16MemoryDescriptor8getLimitEv
	subl	16(%ebp), %eax
	movl	%eax, %ebx
	movl	-12(%ebp), %eax
	movl	%eax, -16(%ebp)
	movl	-16(%ebp), %eax
	addl	$4, %eax
	movl	%eax, %ecx
	call	__ZN16MemoryDescriptor8getStartEv
	movl	%eax, %edx
	movl	12(%ebp), %eax
	subl	%edx, %eax
	cmpl	%eax, %ebx
	jge	L54
	movl	$1, %eax
	jmp	L57
L54:
	movl	$0, %eax
L57:
	testb	%al, %al
	je	L58
	movl	-12(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZN13MemoryManager13nextAllocableEP8TreeNodeI16MemoryDescriptorE
	movl	%eax, -12(%ebp)
	jmp	L52
L58:
	movl	-12(%ebp), %eax
	addl	$36, %esp
	popl	%ebx
	popl	%ebp
	ret
	.align 2
	.globl	__ZN13MemoryManager12findFirstLenEP8TreeNodeI16MemoryDescriptorEj
	.def	__ZN13MemoryManager12findFirstLenEP8TreeNodeI16MemoryDescriptorEj;	.scl	2;	.type	32;	.endef
__ZN13MemoryManager12findFirstLenEP8TreeNodeI16MemoryDescriptorEj:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	8(%ebp), %ecx
	call	__ZN8TreeNodeI16MemoryDescriptorE6getSonEv
	movl	%eax, -12(%ebp)
	movl	-12(%ebp), %eax
	movl	%eax, -20(%ebp)
	movl	-20(%ebp), %eax
	addl	$4, %eax
	movl	%eax, %ecx
	call	__ZN16MemoryDescriptor11isAllocableEv
	testl	%eax, %eax
	sete	%al
	testb	%al, %al
	je	L62
	movl	-12(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZN13MemoryManager13nextAllocableEP8TreeNodeI16MemoryDescriptorE
	movl	%eax, -12(%ebp)
L62:
	cmpl	$0, -12(%ebp)
	je	L63
	movl	-12(%ebp), %eax
	movl	%eax, -16(%ebp)
	movl	-16(%ebp), %eax
	addl	$4, %eax
	movl	%eax, %ecx
	call	__ZN16MemoryDescriptor8getLimitEv
	cmpl	12(%ebp), %eax
	jnb	L63
	movl	$1, %eax
	jmp	L65
L63:
	movl	$0, %eax
L65:
	testb	%al, %al
	je	L66
	movl	-12(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZN13MemoryManager13nextAllocableEP8TreeNodeI16MemoryDescriptorE
	movl	%eax, -12(%ebp)
	jmp	L62
L66:
	movl	-12(%ebp), %eax
	leave
	ret
	.align 2
	.globl	__ZN13MemoryManager13isNullManagerEv
	.def	__ZN13MemoryManager13isNullManagerEv;	.scl	2;	.type	32;	.endef
__ZN13MemoryManager13isNullManagerEv:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	%ecx, -12(%ebp)
	movl	-12(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN4TreeI16MemoryDescriptorE7getHeadEv
	testl	%eax, %eax
	sete	%al
	movzbl	%al, %eax
	leave
	ret
	.align 2
	.globl	__ZN13MemoryManager7setNullEv
	.def	__ZN13MemoryManager7setNullEv;	.scl	2;	.type	32;	.endef
__ZN13MemoryManager7setNullEv:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	%ecx, -12(%ebp)
	movl	-12(%ebp), %eax
	movl	$0, (%esp)
	movl	%eax, %ecx
	call	__ZN4TreeI16MemoryDescriptorE7setHeadEP8TreeNodeIS0_E
	subl	$4, %esp
	nop
	leave
	ret
	.align 2
	.globl	__ZN13MemoryManager20locateForInsertationEP8TreeNodeI16MemoryDescriptorES3_
	.def	__ZN13MemoryManager20locateForInsertationEP8TreeNodeI16MemoryDescriptorES3_;	.scl	2;	.type	32;	.endef
__ZN13MemoryManager20locateForInsertationEP8TreeNodeI16MemoryDescriptorES3_:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$48, %esp
	cmpl	$0, 8(%ebp)
	je	L72
	cmpl	$0, 12(%ebp)
	jne	L73
L72:
	movl	$0, %eax
	jmp	L74
L73:
	movl	8(%ebp), %eax
	movl	%eax, -8(%ebp)
	movl	12(%ebp), %eax
	movl	%eax, -20(%ebp)
	movl	-20(%ebp), %eax
	addl	$4, %eax
	movl	%eax, %ecx
	call	__ZN16MemoryDescriptor8getStartEv
	movl	%eax, -16(%ebp)
	movl	12(%ebp), %eax
	movl	%eax, -52(%ebp)
	movl	-52(%ebp), %eax
	addl	$4, %eax
	movl	%eax, %ecx
	call	__ZN16MemoryDescriptor8getLimitEv
	movl	%eax, -24(%ebp)
L83:
	cmpl	$0, -8(%ebp)
	je	L77
	movl	-8(%ebp), %eax
	movl	%eax, -32(%ebp)
	movl	-32(%ebp), %eax
	addl	$4, %eax
	movl	%eax, %ecx
	call	__ZN16MemoryDescriptor8getStartEv
	movl	%eax, %edx
	movl	-16(%ebp), %eax
	subl	%edx, %eax
	movl	%eax, %ebx
	movl	-8(%ebp), %eax
	movl	%eax, -12(%ebp)
	movl	-12(%ebp), %eax
	addl	$4, %eax
	movl	%eax, %ecx
	call	__ZN16MemoryDescriptor8getLimitEv
	cmpl	%eax, %ebx
	jge	L77
	movl	$1, %eax
	jmp	L80
L77:
	movl	$0, %eax
L80:
	testb	%al, %al
	je	L81
	movl	-8(%ebp), %eax
	movl	%eax, -28(%ebp)
	movl	-28(%ebp), %eax
	movl	16(%eax), %eax
	movl	%eax, -8(%ebp)
	jmp	L83
L81:
	cmpl	$0, -8(%ebp)
	je	L84
	movl	-8(%ebp), %eax
	movl	%eax, -36(%ebp)
	movl	-36(%ebp), %eax
	movl	16(%eax), %eax
	testl	%eax, %eax
	setne	%al
	testb	%al, %al
	je	L86
	movl	-8(%ebp), %eax
	movl	%eax, -48(%ebp)
	movl	-48(%ebp), %eax
	movl	16(%eax), %eax
	movl	%eax, -44(%ebp)
	movl	-44(%ebp), %eax
	movl	%eax, -40(%ebp)
	movl	-40(%ebp), %eax
	addl	$4, %eax
	movl	%eax, %ecx
	call	__ZN16MemoryDescriptor8getStartEv
	subl	-16(%ebp), %eax
	movl	%eax, %edx
	movl	-24(%ebp), %eax
	cmpl	%eax, %edx
	setge	%al
	testb	%al, %al
	je	L89
	movl	-8(%ebp), %eax
	jmp	L74
L89:
	movl	$0, %eax
	jmp	L74
L86:
	movl	-8(%ebp), %eax
	jmp	L74
L84:
	movl	$0, %eax
L74:
	addl	$48, %esp
	popl	%ebx
	popl	%ebp
	ret
	.align 2
	.globl	__ZN13MemoryManager9addToTreeEP8TreeNodeI16MemoryDescriptorES3_
	.def	__ZN13MemoryManager9addToTreeEP8TreeNodeI16MemoryDescriptorES3_;	.scl	2;	.type	32;	.endef
__ZN13MemoryManager9addToTreeEP8TreeNodeI16MemoryDescriptorES3_:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZN13MemoryManager20locateForInsertationEP8TreeNodeI16MemoryDescriptorES3_
	movl	%eax, -4(%ebp)
	nop
	leave
	ret
	.align 2
	.globl	__ZN13MemoryManager16copyOnAllocationEP8TreeNodeI16MemoryDescriptorE
	.def	__ZN13MemoryManager16copyOnAllocationEP8TreeNodeI16MemoryDescriptorE;	.scl	2;	.type	32;	.endef
__ZN13MemoryManager16copyOnAllocationEP8TreeNodeI16MemoryDescriptorE:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	pushl	%ebx
	subl	$80, %esp
	movl	%ecx, -44(%ebp)
	movl	8(%ebp), %ecx
	call	__ZN8TreeNodeI16MemoryDescriptorE6getSonEv
	testl	%eax, %eax
	sete	%al
	testb	%al, %al
	je	L92
	movl	8(%ebp), %eax
	movl	%eax, -20(%ebp)
	movl	-20(%ebp), %eax
	addl	$4, %eax
	movl	%eax, -12(%ebp)
	movl	-12(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN16MemoryDescriptor11isAllocableEv
	testl	%eax, %eax
	sete	%al
	movzbl	%al, %ebx
	movl	-12(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN16MemoryDescriptor8getLimitEv
	movl	%eax, %esi
	movl	-12(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN16MemoryDescriptor8getStartEv
	movl	%eax, %edx
	leal	-32(%ebp), %eax
	movl	%ebx, 8(%esp)
	movl	%esi, 4(%esp)
	movl	%edx, (%esp)
	movl	%eax, %ecx
	call	__ZN16MemoryDescriptorC1Eiji
	subl	$12, %esp
	movl	-44(%ebp), %eax
	movl	(%eax), %eax
	movl	%eax, %ecx
	call	__ZN19SimpleMemoryManagerI8TreeNodeI16MemoryDescriptorEE6getNewEv
	movl	%eax, %edx
	movl	$0, 16(%esp)
	movl	$0, 12(%esp)
	movl	$0, 8(%esp)
	movl	$0, 4(%esp)
	leal	-32(%ebp), %eax
	movl	%eax, (%esp)
	movl	%edx, %ecx
	call	__ZN8TreeNodeI16MemoryDescriptorE4initERKS0_PS1_S4_S4_S4_
	subl	$20, %esp
	movl	%eax, -16(%ebp)
	leal	-32(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN16MemoryDescriptorD1Ev
	movl	-16(%ebp), %eax
	movl	8(%ebp), %edx
	movl	%edx, (%esp)
	movl	%eax, %ecx
	call	__ZN8TreeNodeI16MemoryDescriptorE9setFatherEPS1_
	subl	$4, %esp
	movl	-16(%ebp), %eax
	movl	%eax, (%esp)
	movl	8(%ebp), %ecx
	call	__ZN8TreeNodeI16MemoryDescriptorE6setSonEPS1_
	subl	$4, %esp
	movl	-16(%ebp), %eax
	jmp	L94
L92:
	movl	8(%ebp), %ecx
	call	__ZN8TreeNodeI16MemoryDescriptorE6getSonEv
L94:
	leal	-8(%ebp), %esp
	popl	%ebx
	popl	%esi
	popl	%ebp
	ret	$4
	.align 2
	.globl	__ZN13MemoryManager13nextAllocableEP8TreeNodeI16MemoryDescriptorE
	.def	__ZN13MemoryManager13nextAllocableEP8TreeNodeI16MemoryDescriptorE;	.scl	2;	.type	32;	.endef
__ZN13MemoryManager13nextAllocableEP8TreeNodeI16MemoryDescriptorE:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	cmpl	$0, 8(%ebp)
	je	L96
L101:
	movl	8(%ebp), %eax
	movl	%eax, -8(%ebp)
	movl	-8(%ebp), %eax
	movl	16(%eax), %eax
	movl	%eax, 8(%ebp)
	cmpl	$0, 8(%ebp)
	je	L98
	movl	8(%ebp), %eax
	movl	%eax, -4(%ebp)
	movl	-4(%ebp), %eax
	addl	$4, %eax
	movl	%eax, %ecx
	call	__ZN16MemoryDescriptor11isAllocableEv
	testl	%eax, %eax
	jne	L98
	movl	$1, %eax
	jmp	L100
L98:
	movl	$0, %eax
L100:
	testb	%al, %al
	je	L96
	jmp	L101
L96:
	movl	8(%ebp), %eax
	leave
	ret
	.ident	"GCC: (GNU) 5.4.0"
	.def	__ZN4TreeI16MemoryDescriptorEC2EP19SimpleMemoryManagerI8TreeNodeIS0_EE;	.scl	2;	.type	32;	.endef
	.def	__ZN19SimpleMemoryManagerI8TreeNodeI16MemoryDescriptorEE6getNewEv;	.scl	2;	.type	32;	.endef
	.def	__ZN8TreeNodeI16MemoryDescriptorE4initERKS0_PS1_S4_S4_S4_;	.scl	2;	.type	32;	.endef
	.def	__ZN4TreeI16MemoryDescriptorE7setHeadEP8TreeNodeIS0_E;	.scl	2;	.type	32;	.endef
	.def	__ZN4TreeI16MemoryDescriptorED2Ev;	.scl	2;	.type	32;	.endef
	.def	__ZN8ListNodeI16MemoryDescriptorE10insertNextEPS1_;	.scl	2;	.type	32;	.endef
	.def	__ZN4TreeI16MemoryDescriptorE7getHeadEv;	.scl	2;	.type	32;	.endef
	.def	__ZN8TreeNodeI16MemoryDescriptorE6getSonEv;	.scl	2;	.type	32;	.endef
	.def	__ZN8TreeNodeI16MemoryDescriptorE9setFatherEPS1_;	.scl	2;	.type	32;	.endef
	.def	__ZN8TreeNodeI16MemoryDescriptorE6setSonEPS1_;	.scl	2;	.type	32;	.endef
