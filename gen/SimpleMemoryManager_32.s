	.file	"SimpleMemoryManager.cpp"
	.section	.text$_ZN19SimpleMemoryManagerI8ListNodeIiEEC2Eij,"x"
	.linkonce discard
	.align 2
	.globl	__ZN19SimpleMemoryManagerI8ListNodeIiEEC2Eij
	.def	__ZN19SimpleMemoryManagerI8ListNodeIiEEC2Eij;	.scl	2;	.type	32;	.endef
__ZN19SimpleMemoryManagerI8ListNodeIiEEC2Eij:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$20, %esp
	movl	%ecx, -20(%ebp)
	movl	-20(%ebp), %eax
	movl	8(%ebp), %edx
	movl	%edx, (%eax)
	movl	-20(%ebp), %eax
	movl	12(%ebp), %edx
	movl	%edx, 4(%eax)
	movl	8(%ebp), %edx
	movl	-20(%ebp), %eax
	movl	%edx, 8(%eax)
	movl	-20(%ebp), %eax
	movl	$0, 12(%eax)
	movl	12(%ebp), %eax
	shrl	$4, %eax
	movl	%eax, %edx
	movl	-20(%ebp), %eax
	movl	%edx, 16(%eax)
	movl	-20(%ebp), %eax
	movl	$0, 20(%eax)
	movl	$0, -4(%ebp)
L3:
	movl	-20(%ebp), %eax
	movl	16(%eax), %edx
	movl	-4(%ebp), %eax
	cmpl	%eax, %edx
	je	L4
	movl	-20(%ebp), %eax
	movl	8(%eax), %eax
	movl	-4(%ebp), %edx
	sall	$4, %edx
	addl	%edx, %eax
	movl	%eax, -8(%ebp)
	movl	-8(%ebp), %eax
	movl	$-1, (%eax)
	addl	$1, -4(%ebp)
	jmp	L3
L4:
	nop
	leave
	ret	$8
	.section	.text$_ZN19SimpleMemoryManagerI8ListNodeIiEEC1Eij,"x"
	.linkonce discard
	.align 2
	.globl	__ZN19SimpleMemoryManagerI8ListNodeIiEEC1Eij
	.def	__ZN19SimpleMemoryManagerI8ListNodeIiEEC1Eij;	.scl	2;	.type	32;	.endef
__ZN19SimpleMemoryManagerI8ListNodeIiEEC1Eij:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$20, %esp
	movl	%ecx, -20(%ebp)
	movl	-20(%ebp), %eax
	movl	8(%ebp), %edx
	movl	%edx, (%eax)
	movl	-20(%ebp), %eax
	movl	12(%ebp), %edx
	movl	%edx, 4(%eax)
	movl	8(%ebp), %edx
	movl	-20(%ebp), %eax
	movl	%edx, 8(%eax)
	movl	-20(%ebp), %eax
	movl	$0, 12(%eax)
	movl	12(%ebp), %eax
	shrl	$4, %eax
	movl	%eax, %edx
	movl	-20(%ebp), %eax
	movl	%edx, 16(%eax)
	movl	-20(%ebp), %eax
	movl	$0, 20(%eax)
	movl	$0, -4(%ebp)
L7:
	movl	-20(%ebp), %eax
	movl	16(%eax), %edx
	movl	-4(%ebp), %eax
	cmpl	%eax, %edx
	je	L8
	movl	-20(%ebp), %eax
	movl	8(%eax), %eax
	movl	-4(%ebp), %edx
	sall	$4, %edx
	addl	%edx, %eax
	movl	%eax, -8(%ebp)
	movl	-8(%ebp), %eax
	movl	$-1, (%eax)
	addl	$1, -4(%ebp)
	jmp	L7
L8:
	nop
	leave
	ret	$8
	.section	.text$_ZN19SimpleMemoryManagerI8ListNodeIiEED2Ev,"x"
	.linkonce discard
	.align 2
	.globl	__ZN19SimpleMemoryManagerI8ListNodeIiEED2Ev
	.def	__ZN19SimpleMemoryManagerI8ListNodeIiEED2Ev;	.scl	2;	.type	32;	.endef
__ZN19SimpleMemoryManagerI8ListNodeIiEED2Ev:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	%ecx, -4(%ebp)
	nop
	leave
	ret
	.section	.text$_ZN19SimpleMemoryManagerI8ListNodeIiEED1Ev,"x"
	.linkonce discard
	.align 2
	.globl	__ZN19SimpleMemoryManagerI8ListNodeIiEED1Ev
	.def	__ZN19SimpleMemoryManagerI8ListNodeIiEED1Ev;	.scl	2;	.type	32;	.endef
__ZN19SimpleMemoryManagerI8ListNodeIiEED1Ev:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	%ecx, -4(%ebp)
	nop
	leave
	ret
	.section	.text$_ZN19SimpleMemoryManagerI8ListNodeIiEE6getNewEv,"x"
	.linkonce discard
	.align 2
	.globl	__ZN19SimpleMemoryManagerI8ListNodeIiEE6getNewEv
	.def	__ZN19SimpleMemoryManagerI8ListNodeIiEE6getNewEv;	.scl	2;	.type	32;	.endef
__ZN19SimpleMemoryManagerI8ListNodeIiEE6getNewEv:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$36, %esp
	movl	%ecx, -36(%ebp)
	movl	$0, -4(%ebp)
	movl	-36(%ebp), %eax
	movl	%eax, -20(%ebp)
	movl	-20(%ebp), %eax
	movl	12(%eax), %edx
	movl	-20(%ebp), %eax
	movl	16(%eax), %eax
	cmpl	%eax, %edx
	sete	%al
	movzbl	%al, %eax
	testl	%eax, %eax
	sete	%al
	testb	%al, %al
	je	L13
	movl	$0, -8(%ebp)
L17:
	movl	-36(%ebp), %eax
	movl	16(%eax), %edx
	movl	-8(%ebp), %eax
	cmpl	%eax, %edx
	je	L13
	movl	-36(%ebp), %eax
	movl	8(%eax), %edx
	movl	-36(%ebp), %eax
	movl	20(%eax), %eax
	sall	$4, %eax
	addl	%edx, %eax
	movl	%eax, -12(%ebp)
	movl	-12(%ebp), %eax
	movl	(%eax), %eax
	cmpl	$-1, %eax
	sete	%al
	movzbl	%al, %eax
	testl	%eax, %eax
	setne	%al
	testb	%al, %al
	je	L16
	movl	-36(%ebp), %eax
	movl	8(%eax), %edx
	movl	-36(%ebp), %eax
	movl	20(%eax), %eax
	sall	$4, %eax
	addl	%edx, %eax
	movl	%eax, -4(%ebp)
	movl	-4(%ebp), %eax
	movl	%eax, -16(%ebp)
	movl	-16(%ebp), %eax
	movl	$0, (%eax)
	movl	-36(%ebp), %eax
	movl	12(%eax), %eax
	leal	1(%eax), %edx
	movl	-36(%ebp), %eax
	movl	%edx, 12(%eax)
	movl	-36(%ebp), %eax
	movl	20(%eax), %eax
	leal	1(%eax), %edx
	movl	-36(%ebp), %eax
	movl	16(%eax), %ecx
	movl	%edx, %eax
	movl	$0, %edx
	divl	%ecx
	movl	-36(%ebp), %eax
	movl	%edx, 20(%eax)
	jmp	L13
L16:
	movl	-36(%ebp), %eax
	movl	20(%eax), %eax
	leal	1(%eax), %edx
	movl	-36(%ebp), %eax
	movl	16(%eax), %ecx
	movl	%edx, %eax
	movl	$0, %edx
	divl	%ecx
	movl	-36(%ebp), %eax
	movl	%edx, 20(%eax)
	addl	$1, -8(%ebp)
	jmp	L17
L13:
	movl	-4(%ebp), %eax
	leave
	ret
	.section	.text$_ZN19SimpleMemoryManagerI8ListNodeIiEE8withdrawEPS1_,"x"
	.linkonce discard
	.align 2
	.globl	__ZN19SimpleMemoryManagerI8ListNodeIiEE8withdrawEPS1_
	.def	__ZN19SimpleMemoryManagerI8ListNodeIiEE8withdrawEPS1_;	.scl	2;	.type	32;	.endef
__ZN19SimpleMemoryManagerI8ListNodeIiEE8withdrawEPS1_:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$20, %esp
	movl	%ecx, -20(%ebp)
	movl	8(%ebp), %eax
	movl	%eax, -8(%ebp)
	movl	-8(%ebp), %eax
	movl	(%eax), %eax
	cmpl	$-1, %eax
	sete	%al
	movzbl	%al, %eax
	testl	%eax, %eax
	sete	%al
	testb	%al, %al
	je	L22
	movl	8(%ebp), %eax
	movl	%eax, -4(%ebp)
	movl	-4(%ebp), %eax
	movl	$-1, (%eax)
	movl	-20(%ebp), %eax
	movl	12(%eax), %eax
	leal	-1(%eax), %edx
	movl	-20(%ebp), %eax
	movl	%edx, 12(%eax)
	movl	8(%ebp), %edx
	movl	-20(%ebp), %eax
	movl	(%eax), %eax
	subl	%eax, %edx
	movl	%edx, %eax
	shrl	$4, %eax
	movl	%eax, %edx
	movl	-20(%ebp), %eax
	movl	%edx, 20(%eax)
L22:
	nop
	leave
	ret	$4
	.section	.text$_ZN19SimpleMemoryManagerI8ListNodeIiEE8freeNextEPS1_,"x"
	.linkonce discard
	.align 2
	.globl	__ZN19SimpleMemoryManagerI8ListNodeIiEE8freeNextEPS1_
	.def	__ZN19SimpleMemoryManagerI8ListNodeIiEE8freeNextEPS1_;	.scl	2;	.type	32;	.endef
__ZN19SimpleMemoryManagerI8ListNodeIiEE8freeNextEPS1_:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$20, %esp
	movl	%ecx, -20(%ebp)
	movl	8(%ebp), %eax
	movl	%eax, -4(%ebp)
L26:
	cmpl	$0, -4(%ebp)
	je	L27
	movl	-4(%ebp), %eax
	movl	%eax, -8(%ebp)
	movl	-8(%ebp), %eax
	movl	$-1, (%eax)
	movl	-4(%ebp), %eax
	movl	%eax, -12(%ebp)
	movl	-12(%ebp), %eax
	movl	8(%eax), %eax
	movl	%eax, -4(%ebp)
	movl	-20(%ebp), %eax
	movl	12(%eax), %eax
	leal	-1(%eax), %edx
	movl	-20(%ebp), %eax
	movl	%edx, 12(%eax)
	jmp	L26
L27:
	nop
	leave
	ret	$4
	.section	.text$_ZN19SimpleMemoryManagerI8ListNodeIiEE12freePreviousEPS1_,"x"
	.linkonce discard
	.align 2
	.globl	__ZN19SimpleMemoryManagerI8ListNodeIiEE12freePreviousEPS1_
	.def	__ZN19SimpleMemoryManagerI8ListNodeIiEE12freePreviousEPS1_;	.scl	2;	.type	32;	.endef
__ZN19SimpleMemoryManagerI8ListNodeIiEE12freePreviousEPS1_:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$20, %esp
	movl	%ecx, -20(%ebp)
	movl	8(%ebp), %eax
	movl	%eax, -4(%ebp)
L31:
	cmpl	$0, -4(%ebp)
	je	L32
	movl	-4(%ebp), %eax
	movl	%eax, -8(%ebp)
	movl	-8(%ebp), %eax
	movl	$-1, (%eax)
	movl	-4(%ebp), %eax
	movl	%eax, -12(%ebp)
	movl	-12(%ebp), %eax
	movl	12(%eax), %eax
	movl	%eax, -4(%ebp)
	movl	-20(%ebp), %eax
	movl	12(%eax), %eax
	leal	-1(%eax), %edx
	movl	-20(%ebp), %eax
	movl	%edx, 12(%eax)
	jmp	L31
L32:
	nop
	leave
	ret	$4
	.section	.text$_ZN19SimpleMemoryManagerI8ListNodeIiEE6isFullEv,"x"
	.linkonce discard
	.align 2
	.globl	__ZN19SimpleMemoryManagerI8ListNodeIiEE6isFullEv
	.def	__ZN19SimpleMemoryManagerI8ListNodeIiEE6isFullEv;	.scl	2;	.type	32;	.endef
__ZN19SimpleMemoryManagerI8ListNodeIiEE6isFullEv:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	%ecx, -4(%ebp)
	movl	-4(%ebp), %eax
	movl	12(%eax), %edx
	movl	-4(%ebp), %eax
	movl	16(%eax), %eax
	cmpl	%eax, %edx
	sete	%al
	movzbl	%al, %eax
	leave
	ret
	.section	.text$_ZN19SimpleMemoryManagerI8ListNodeIiEE6getLenEv,"x"
	.linkonce discard
	.align 2
	.globl	__ZN19SimpleMemoryManagerI8ListNodeIiEE6getLenEv
	.def	__ZN19SimpleMemoryManagerI8ListNodeIiEE6getLenEv;	.scl	2;	.type	32;	.endef
__ZN19SimpleMemoryManagerI8ListNodeIiEE6getLenEv:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	%ecx, -4(%ebp)
	movl	-4(%ebp), %eax
	movl	16(%eax), %eax
	leave
	ret
	.section	.text$_ZN19SimpleMemoryManagerI8ListNodeIiEE10getCurSizeEv,"x"
	.linkonce discard
	.align 2
	.globl	__ZN19SimpleMemoryManagerI8ListNodeIiEE10getCurSizeEv
	.def	__ZN19SimpleMemoryManagerI8ListNodeIiEE10getCurSizeEv;	.scl	2;	.type	32;	.endef
__ZN19SimpleMemoryManagerI8ListNodeIiEE10getCurSizeEv:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	%ecx, -4(%ebp)
	movl	-4(%ebp), %eax
	movl	12(%eax), %eax
	leave
	ret
	.section	.text$_ZN19SimpleMemoryManagerI8ListNodeIiEE8getStartEv,"x"
	.linkonce discard
	.align 2
	.globl	__ZN19SimpleMemoryManagerI8ListNodeIiEE8getStartEv
	.def	__ZN19SimpleMemoryManagerI8ListNodeIiEE8getStartEv;	.scl	2;	.type	32;	.endef
__ZN19SimpleMemoryManagerI8ListNodeIiEE8getStartEv:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	%ecx, -4(%ebp)
	movl	-4(%ebp), %eax
	movl	(%eax), %eax
	leave
	ret
	.section	.text$_ZN19SimpleMemoryManagerI8ListNodeIiEE8getLimitEv,"x"
	.linkonce discard
	.align 2
	.globl	__ZN19SimpleMemoryManagerI8ListNodeIiEE8getLimitEv
	.def	__ZN19SimpleMemoryManagerI8ListNodeIiEE8getLimitEv;	.scl	2;	.type	32;	.endef
__ZN19SimpleMemoryManagerI8ListNodeIiEE8getLimitEv:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	%ecx, -4(%ebp)
	movl	-4(%ebp), %eax
	movl	4(%eax), %eax
	leave
	ret
	.section	.text$_ZN19SimpleMemoryManagerI8TreeNodeI16MemoryDescriptorEEC2Eij,"x"
	.linkonce discard
	.align 2
	.globl	__ZN19SimpleMemoryManagerI8TreeNodeI16MemoryDescriptorEEC2Eij
	.def	__ZN19SimpleMemoryManagerI8TreeNodeI16MemoryDescriptorEEC2Eij;	.scl	2;	.type	32;	.endef
__ZN19SimpleMemoryManagerI8TreeNodeI16MemoryDescriptorEEC2Eij:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$20, %esp
	movl	%ecx, -20(%ebp)
	movl	-20(%ebp), %eax
	movl	8(%ebp), %edx
	movl	%edx, (%eax)
	movl	-20(%ebp), %eax
	movl	12(%ebp), %edx
	movl	%edx, 4(%eax)
	movl	8(%ebp), %edx
	movl	-20(%ebp), %eax
	movl	%edx, 8(%eax)
	movl	-20(%ebp), %eax
	movl	$0, 12(%eax)
	movl	12(%ebp), %eax
	shrl	$5, %eax
	movl	%eax, %edx
	movl	-20(%ebp), %eax
	movl	%edx, 16(%eax)
	movl	-20(%ebp), %eax
	movl	$0, 20(%eax)
	movl	$0, -4(%ebp)
L45:
	movl	-20(%ebp), %eax
	movl	16(%eax), %edx
	movl	-4(%ebp), %eax
	cmpl	%eax, %edx
	je	L46
	movl	-20(%ebp), %eax
	movl	8(%eax), %eax
	movl	-4(%ebp), %edx
	sall	$5, %edx
	addl	%edx, %eax
	movl	%eax, -8(%ebp)
	movl	-8(%ebp), %eax
	movl	$-1, (%eax)
	addl	$1, -4(%ebp)
	jmp	L45
L46:
	nop
	leave
	ret	$8
	.section	.text$_ZN19SimpleMemoryManagerI8TreeNodeI16MemoryDescriptorEEC1Eij,"x"
	.linkonce discard
	.align 2
	.globl	__ZN19SimpleMemoryManagerI8TreeNodeI16MemoryDescriptorEEC1Eij
	.def	__ZN19SimpleMemoryManagerI8TreeNodeI16MemoryDescriptorEEC1Eij;	.scl	2;	.type	32;	.endef
__ZN19SimpleMemoryManagerI8TreeNodeI16MemoryDescriptorEEC1Eij:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$20, %esp
	movl	%ecx, -20(%ebp)
	movl	-20(%ebp), %eax
	movl	8(%ebp), %edx
	movl	%edx, (%eax)
	movl	-20(%ebp), %eax
	movl	12(%ebp), %edx
	movl	%edx, 4(%eax)
	movl	8(%ebp), %edx
	movl	-20(%ebp), %eax
	movl	%edx, 8(%eax)
	movl	-20(%ebp), %eax
	movl	$0, 12(%eax)
	movl	12(%ebp), %eax
	shrl	$5, %eax
	movl	%eax, %edx
	movl	-20(%ebp), %eax
	movl	%edx, 16(%eax)
	movl	-20(%ebp), %eax
	movl	$0, 20(%eax)
	movl	$0, -4(%ebp)
L49:
	movl	-20(%ebp), %eax
	movl	16(%eax), %edx
	movl	-4(%ebp), %eax
	cmpl	%eax, %edx
	je	L50
	movl	-20(%ebp), %eax
	movl	8(%eax), %eax
	movl	-4(%ebp), %edx
	sall	$5, %edx
	addl	%edx, %eax
	movl	%eax, -8(%ebp)
	movl	-8(%ebp), %eax
	movl	$-1, (%eax)
	addl	$1, -4(%ebp)
	jmp	L49
L50:
	nop
	leave
	ret	$8
	.section	.text$_ZN19SimpleMemoryManagerI8TreeNodeI16MemoryDescriptorEED2Ev,"x"
	.linkonce discard
	.align 2
	.globl	__ZN19SimpleMemoryManagerI8TreeNodeI16MemoryDescriptorEED2Ev
	.def	__ZN19SimpleMemoryManagerI8TreeNodeI16MemoryDescriptorEED2Ev;	.scl	2;	.type	32;	.endef
__ZN19SimpleMemoryManagerI8TreeNodeI16MemoryDescriptorEED2Ev:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	%ecx, -4(%ebp)
	nop
	leave
	ret
	.section	.text$_ZN19SimpleMemoryManagerI8TreeNodeI16MemoryDescriptorEED1Ev,"x"
	.linkonce discard
	.align 2
	.globl	__ZN19SimpleMemoryManagerI8TreeNodeI16MemoryDescriptorEED1Ev
	.def	__ZN19SimpleMemoryManagerI8TreeNodeI16MemoryDescriptorEED1Ev;	.scl	2;	.type	32;	.endef
__ZN19SimpleMemoryManagerI8TreeNodeI16MemoryDescriptorEED1Ev:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	%ecx, -4(%ebp)
	nop
	leave
	ret
	.section	.text$_ZN19SimpleMemoryManagerI8TreeNodeI16MemoryDescriptorEE6getNewEv,"x"
	.linkonce discard
	.align 2
	.globl	__ZN19SimpleMemoryManagerI8TreeNodeI16MemoryDescriptorEE6getNewEv
	.def	__ZN19SimpleMemoryManagerI8TreeNodeI16MemoryDescriptorEE6getNewEv;	.scl	2;	.type	32;	.endef
__ZN19SimpleMemoryManagerI8TreeNodeI16MemoryDescriptorEE6getNewEv:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$36, %esp
	movl	%ecx, -36(%ebp)
	movl	$0, -4(%ebp)
	movl	-36(%ebp), %eax
	movl	%eax, -20(%ebp)
	movl	-20(%ebp), %eax
	movl	12(%eax), %edx
	movl	-20(%ebp), %eax
	movl	16(%eax), %eax
	cmpl	%eax, %edx
	sete	%al
	movzbl	%al, %eax
	testl	%eax, %eax
	sete	%al
	testb	%al, %al
	je	L55
	movl	$0, -8(%ebp)
L59:
	movl	-36(%ebp), %eax
	movl	16(%eax), %edx
	movl	-8(%ebp), %eax
	cmpl	%eax, %edx
	je	L55
	movl	-36(%ebp), %eax
	movl	8(%eax), %edx
	movl	-36(%ebp), %eax
	movl	20(%eax), %eax
	sall	$5, %eax
	addl	%edx, %eax
	movl	%eax, -12(%ebp)
	movl	-12(%ebp), %eax
	movl	(%eax), %eax
	cmpl	$-1, %eax
	sete	%al
	movzbl	%al, %eax
	testl	%eax, %eax
	setne	%al
	testb	%al, %al
	je	L58
	movl	-36(%ebp), %eax
	movl	8(%eax), %edx
	movl	-36(%ebp), %eax
	movl	20(%eax), %eax
	sall	$5, %eax
	addl	%edx, %eax
	movl	%eax, -4(%ebp)
	movl	-4(%ebp), %eax
	movl	%eax, -16(%ebp)
	movl	-16(%ebp), %eax
	movl	$0, (%eax)
	movl	-36(%ebp), %eax
	movl	12(%eax), %eax
	leal	1(%eax), %edx
	movl	-36(%ebp), %eax
	movl	%edx, 12(%eax)
	movl	-36(%ebp), %eax
	movl	20(%eax), %eax
	leal	1(%eax), %edx
	movl	-36(%ebp), %eax
	movl	16(%eax), %ecx
	movl	%edx, %eax
	movl	$0, %edx
	divl	%ecx
	movl	-36(%ebp), %eax
	movl	%edx, 20(%eax)
	jmp	L55
L58:
	movl	-36(%ebp), %eax
	movl	20(%eax), %eax
	leal	1(%eax), %edx
	movl	-36(%ebp), %eax
	movl	16(%eax), %ecx
	movl	%edx, %eax
	movl	$0, %edx
	divl	%ecx
	movl	-36(%ebp), %eax
	movl	%edx, 20(%eax)
	addl	$1, -8(%ebp)
	jmp	L59
L55:
	movl	-4(%ebp), %eax
	leave
	ret
	.section	.text$_ZN19SimpleMemoryManagerI8TreeNodeI16MemoryDescriptorEE8withdrawEPS2_,"x"
	.linkonce discard
	.align 2
	.globl	__ZN19SimpleMemoryManagerI8TreeNodeI16MemoryDescriptorEE8withdrawEPS2_
	.def	__ZN19SimpleMemoryManagerI8TreeNodeI16MemoryDescriptorEE8withdrawEPS2_;	.scl	2;	.type	32;	.endef
__ZN19SimpleMemoryManagerI8TreeNodeI16MemoryDescriptorEE8withdrawEPS2_:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$20, %esp
	movl	%ecx, -20(%ebp)
	movl	8(%ebp), %eax
	movl	%eax, -8(%ebp)
	movl	-8(%ebp), %eax
	movl	(%eax), %eax
	cmpl	$-1, %eax
	sete	%al
	movzbl	%al, %eax
	testl	%eax, %eax
	sete	%al
	testb	%al, %al
	je	L64
	movl	8(%ebp), %eax
	movl	%eax, -4(%ebp)
	movl	-4(%ebp), %eax
	movl	$-1, (%eax)
	movl	-20(%ebp), %eax
	movl	12(%eax), %eax
	leal	-1(%eax), %edx
	movl	-20(%ebp), %eax
	movl	%edx, 12(%eax)
	movl	8(%ebp), %edx
	movl	-20(%ebp), %eax
	movl	(%eax), %eax
	subl	%eax, %edx
	movl	%edx, %eax
	shrl	$5, %eax
	movl	%eax, %edx
	movl	-20(%ebp), %eax
	movl	%edx, 20(%eax)
L64:
	nop
	leave
	ret	$4
	.section	.text$_ZN19SimpleMemoryManagerI8TreeNodeI16MemoryDescriptorEE8freeNextEPS2_,"x"
	.linkonce discard
	.align 2
	.globl	__ZN19SimpleMemoryManagerI8TreeNodeI16MemoryDescriptorEE8freeNextEPS2_
	.def	__ZN19SimpleMemoryManagerI8TreeNodeI16MemoryDescriptorEE8freeNextEPS2_;	.scl	2;	.type	32;	.endef
__ZN19SimpleMemoryManagerI8TreeNodeI16MemoryDescriptorEE8freeNextEPS2_:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$20, %esp
	movl	%ecx, -20(%ebp)
	movl	8(%ebp), %eax
	movl	%eax, -4(%ebp)
L68:
	cmpl	$0, -4(%ebp)
	je	L69
	movl	-4(%ebp), %eax
	movl	%eax, -8(%ebp)
	movl	-8(%ebp), %eax
	movl	$-1, (%eax)
	movl	-4(%ebp), %eax
	movl	%eax, -12(%ebp)
	movl	-12(%ebp), %eax
	movl	16(%eax), %eax
	movl	%eax, -4(%ebp)
	movl	-20(%ebp), %eax
	movl	12(%eax), %eax
	leal	-1(%eax), %edx
	movl	-20(%ebp), %eax
	movl	%edx, 12(%eax)
	jmp	L68
L69:
	nop
	leave
	ret	$4
	.section	.text$_ZN19SimpleMemoryManagerI8TreeNodeI16MemoryDescriptorEE12freePreviousEPS2_,"x"
	.linkonce discard
	.align 2
	.globl	__ZN19SimpleMemoryManagerI8TreeNodeI16MemoryDescriptorEE12freePreviousEPS2_
	.def	__ZN19SimpleMemoryManagerI8TreeNodeI16MemoryDescriptorEE12freePreviousEPS2_;	.scl	2;	.type	32;	.endef
__ZN19SimpleMemoryManagerI8TreeNodeI16MemoryDescriptorEE12freePreviousEPS2_:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$20, %esp
	movl	%ecx, -20(%ebp)
	movl	8(%ebp), %eax
	movl	%eax, -4(%ebp)
L73:
	cmpl	$0, -4(%ebp)
	je	L74
	movl	-4(%ebp), %eax
	movl	%eax, -8(%ebp)
	movl	-8(%ebp), %eax
	movl	$-1, (%eax)
	movl	-4(%ebp), %eax
	movl	%eax, -12(%ebp)
	movl	-12(%ebp), %eax
	movl	20(%eax), %eax
	movl	%eax, -4(%ebp)
	movl	-20(%ebp), %eax
	movl	12(%eax), %eax
	leal	-1(%eax), %edx
	movl	-20(%ebp), %eax
	movl	%edx, 12(%eax)
	jmp	L73
L74:
	nop
	leave
	ret	$4
	.section	.text$_ZN19SimpleMemoryManagerI8TreeNodeI16MemoryDescriptorEE6isFullEv,"x"
	.linkonce discard
	.align 2
	.globl	__ZN19SimpleMemoryManagerI8TreeNodeI16MemoryDescriptorEE6isFullEv
	.def	__ZN19SimpleMemoryManagerI8TreeNodeI16MemoryDescriptorEE6isFullEv;	.scl	2;	.type	32;	.endef
__ZN19SimpleMemoryManagerI8TreeNodeI16MemoryDescriptorEE6isFullEv:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	%ecx, -4(%ebp)
	movl	-4(%ebp), %eax
	movl	12(%eax), %edx
	movl	-4(%ebp), %eax
	movl	16(%eax), %eax
	cmpl	%eax, %edx
	sete	%al
	movzbl	%al, %eax
	leave
	ret
	.section	.text$_ZN19SimpleMemoryManagerI8TreeNodeI16MemoryDescriptorEE6getLenEv,"x"
	.linkonce discard
	.align 2
	.globl	__ZN19SimpleMemoryManagerI8TreeNodeI16MemoryDescriptorEE6getLenEv
	.def	__ZN19SimpleMemoryManagerI8TreeNodeI16MemoryDescriptorEE6getLenEv;	.scl	2;	.type	32;	.endef
__ZN19SimpleMemoryManagerI8TreeNodeI16MemoryDescriptorEE6getLenEv:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	%ecx, -4(%ebp)
	movl	-4(%ebp), %eax
	movl	16(%eax), %eax
	leave
	ret
	.section	.text$_ZN19SimpleMemoryManagerI8TreeNodeI16MemoryDescriptorEE10getCurSizeEv,"x"
	.linkonce discard
	.align 2
	.globl	__ZN19SimpleMemoryManagerI8TreeNodeI16MemoryDescriptorEE10getCurSizeEv
	.def	__ZN19SimpleMemoryManagerI8TreeNodeI16MemoryDescriptorEE10getCurSizeEv;	.scl	2;	.type	32;	.endef
__ZN19SimpleMemoryManagerI8TreeNodeI16MemoryDescriptorEE10getCurSizeEv:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	%ecx, -4(%ebp)
	movl	-4(%ebp), %eax
	movl	12(%eax), %eax
	leave
	ret
	.section	.text$_ZN19SimpleMemoryManagerI8TreeNodeI16MemoryDescriptorEE8getStartEv,"x"
	.linkonce discard
	.align 2
	.globl	__ZN19SimpleMemoryManagerI8TreeNodeI16MemoryDescriptorEE8getStartEv
	.def	__ZN19SimpleMemoryManagerI8TreeNodeI16MemoryDescriptorEE8getStartEv;	.scl	2;	.type	32;	.endef
__ZN19SimpleMemoryManagerI8TreeNodeI16MemoryDescriptorEE8getStartEv:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	%ecx, -4(%ebp)
	movl	-4(%ebp), %eax
	movl	(%eax), %eax
	leave
	ret
	.section	.text$_ZN19SimpleMemoryManagerI8TreeNodeI16MemoryDescriptorEE8getLimitEv,"x"
	.linkonce discard
	.align 2
	.globl	__ZN19SimpleMemoryManagerI8TreeNodeI16MemoryDescriptorEE8getLimitEv
	.def	__ZN19SimpleMemoryManagerI8TreeNodeI16MemoryDescriptorEE8getLimitEv;	.scl	2;	.type	32;	.endef
__ZN19SimpleMemoryManagerI8TreeNodeI16MemoryDescriptorEE8getLimitEv:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	%ecx, -4(%ebp)
	movl	-4(%ebp), %eax
	movl	4(%eax), %eax
	leave
	ret
	.text
	.align 2
	.globl	__ZN16SimpleMemoryNodeC2Ei
	.def	__ZN16SimpleMemoryNodeC2Ei;	.scl	2;	.type	32;	.endef
__ZN16SimpleMemoryNodeC2Ei:
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
	.globl	__ZN16SimpleMemoryNodeC1Ei
	.def	__ZN16SimpleMemoryNodeC1Ei;	.scl	2;	.type	32;	.endef
	.set	__ZN16SimpleMemoryNodeC1Ei,__ZN16SimpleMemoryNodeC2Ei
	.align 2
	.globl	__ZN16SimpleMemoryNodeD2Ev
	.def	__ZN16SimpleMemoryNodeD2Ev;	.scl	2;	.type	32;	.endef
__ZN16SimpleMemoryNodeD2Ev:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	%ecx, -4(%ebp)
	nop
	leave
	ret
	.globl	__ZN16SimpleMemoryNodeD1Ev
	.def	__ZN16SimpleMemoryNodeD1Ev;	.scl	2;	.type	32;	.endef
	.set	__ZN16SimpleMemoryNodeD1Ev,__ZN16SimpleMemoryNodeD2Ev
	.ident	"GCC: (GNU) 5.4.0"
