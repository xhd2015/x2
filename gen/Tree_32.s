	.file	"Tree.cpp"
	.section	.text$_ZN4TreeI16MemoryDescriptorEC2EP19SimpleMemoryManagerI8TreeNodeIS0_EE,"x"
	.linkonce discard
	.align 2
	.globl	__ZN4TreeI16MemoryDescriptorEC2EP19SimpleMemoryManagerI8TreeNodeIS0_EE
	.def	__ZN4TreeI16MemoryDescriptorEC2EP19SimpleMemoryManagerI8TreeNodeIS0_EE;	.scl	2;	.type	32;	.endef
__ZN4TreeI16MemoryDescriptorEC2EP19SimpleMemoryManagerI8TreeNodeIS0_EE:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	%ecx, -12(%ebp)
	movl	-12(%ebp), %eax
	movl	8(%ebp), %edx
	movl	%edx, (%eax)
	movl	8(%ebp), %ecx
	call	__ZN19SimpleMemoryManagerI8TreeNodeI16MemoryDescriptorEE6getNewEv
	movl	%eax, %edx
	movl	-12(%ebp), %eax
	movl	%edx, 4(%eax)
	nop
	leave
	ret	$4
	.section	.text$_ZN4TreeI16MemoryDescriptorEC1EP19SimpleMemoryManagerI8TreeNodeIS0_EE,"x"
	.linkonce discard
	.align 2
	.globl	__ZN4TreeI16MemoryDescriptorEC1EP19SimpleMemoryManagerI8TreeNodeIS0_EE
	.def	__ZN4TreeI16MemoryDescriptorEC1EP19SimpleMemoryManagerI8TreeNodeIS0_EE;	.scl	2;	.type	32;	.endef
__ZN4TreeI16MemoryDescriptorEC1EP19SimpleMemoryManagerI8TreeNodeIS0_EE:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	%ecx, -12(%ebp)
	movl	-12(%ebp), %eax
	movl	8(%ebp), %edx
	movl	%edx, (%eax)
	movl	8(%ebp), %ecx
	call	__ZN19SimpleMemoryManagerI8TreeNodeI16MemoryDescriptorEE6getNewEv
	movl	%eax, %edx
	movl	-12(%ebp), %eax
	movl	%edx, 4(%eax)
	nop
	leave
	ret	$4
	.section	.text$_ZN4TreeI16MemoryDescriptorED2Ev,"x"
	.linkonce discard
	.align 2
	.globl	__ZN4TreeI16MemoryDescriptorED2Ev
	.def	__ZN4TreeI16MemoryDescriptorED2Ev;	.scl	2;	.type	32;	.endef
__ZN4TreeI16MemoryDescriptorED2Ev:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	%ecx, -4(%ebp)
	nop
	leave
	ret
	.section	.text$_ZN4TreeI16MemoryDescriptorED1Ev,"x"
	.linkonce discard
	.align 2
	.globl	__ZN4TreeI16MemoryDescriptorED1Ev
	.def	__ZN4TreeI16MemoryDescriptorED1Ev;	.scl	2;	.type	32;	.endef
__ZN4TreeI16MemoryDescriptorED1Ev:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	%ecx, -4(%ebp)
	nop
	leave
	ret
	.section	.text$_ZN4TreeI16MemoryDescriptorE7getHeadEv,"x"
	.linkonce discard
	.align 2
	.globl	__ZN4TreeI16MemoryDescriptorE7getHeadEv
	.def	__ZN4TreeI16MemoryDescriptorE7getHeadEv;	.scl	2;	.type	32;	.endef
__ZN4TreeI16MemoryDescriptorE7getHeadEv:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	%ecx, -12(%ebp)
	movl	-12(%ebp), %eax
	movl	4(%eax), %eax
	movl	%eax, %ecx
	call	__ZN8TreeNodeI16MemoryDescriptorE6getSonEv
	leave
	ret
	.section	.text$_ZN4TreeI16MemoryDescriptorE7setHeadEP8TreeNodeIS0_E,"x"
	.linkonce discard
	.align 2
	.globl	__ZN4TreeI16MemoryDescriptorE7setHeadEP8TreeNodeIS0_E
	.def	__ZN4TreeI16MemoryDescriptorE7setHeadEP8TreeNodeIS0_E;	.scl	2;	.type	32;	.endef
__ZN4TreeI16MemoryDescriptorE7setHeadEP8TreeNodeIS0_E:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	%ecx, -12(%ebp)
	movl	-12(%ebp), %eax
	movl	4(%eax), %eax
	movl	8(%ebp), %edx
	movl	%edx, (%esp)
	movl	%eax, %ecx
	call	__ZN8TreeNodeI16MemoryDescriptorE6setSonEPS1_
	subl	$4, %esp
	movl	-12(%ebp), %eax
	leave
	ret	$4
	.section	.text$_ZN4TreeI16MemoryDescriptorE4freeEv,"x"
	.linkonce discard
	.align 2
	.globl	__ZN4TreeI16MemoryDescriptorE4freeEv
	.def	__ZN4TreeI16MemoryDescriptorE4freeEv;	.scl	2;	.type	32;	.endef
__ZN4TreeI16MemoryDescriptorE4freeEv:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	%ecx, -4(%ebp)
	nop
	leave
	ret
	.section	.text$_ZN8TreeNodeI16MemoryDescriptorEC2ERKS0_PS1_S4_S4_S4_,"x"
	.linkonce discard
	.align 2
	.globl	__ZN8TreeNodeI16MemoryDescriptorEC2ERKS0_PS1_S4_S4_S4_
	.def	__ZN8TreeNodeI16MemoryDescriptorEC2ERKS0_PS1_S4_S4_S4_;	.scl	2;	.type	32;	.endef
__ZN8TreeNodeI16MemoryDescriptorEC2ERKS0_PS1_S4_S4_S4_:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	%ecx, -12(%ebp)
	movl	-12(%ebp), %eax
	movl	24(%ebp), %edx
	movl	%edx, 8(%esp)
	movl	20(%ebp), %edx
	movl	%edx, 4(%esp)
	movl	8(%ebp), %edx
	movl	%edx, (%esp)
	movl	%eax, %ecx
	call	__ZN8ListNodeI16MemoryDescriptorEC2ERKS0_PS1_S4_
	subl	$12, %esp
	movl	-12(%ebp), %eax
	movl	16(%ebp), %edx
	movl	%edx, 24(%eax)
	movl	-12(%ebp), %eax
	movl	12(%ebp), %edx
	movl	%edx, 28(%eax)
	nop
	leave
	ret	$20
	.section	.text$_ZN8TreeNodeI16MemoryDescriptorEC1ERKS0_PS1_S4_S4_S4_,"x"
	.linkonce discard
	.align 2
	.globl	__ZN8TreeNodeI16MemoryDescriptorEC1ERKS0_PS1_S4_S4_S4_
	.def	__ZN8TreeNodeI16MemoryDescriptorEC1ERKS0_PS1_S4_S4_S4_;	.scl	2;	.type	32;	.endef
__ZN8TreeNodeI16MemoryDescriptorEC1ERKS0_PS1_S4_S4_S4_:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	%ecx, -12(%ebp)
	movl	-12(%ebp), %eax
	movl	24(%ebp), %edx
	movl	%edx, 8(%esp)
	movl	20(%ebp), %edx
	movl	%edx, 4(%esp)
	movl	8(%ebp), %edx
	movl	%edx, (%esp)
	movl	%eax, %ecx
	call	__ZN8ListNodeI16MemoryDescriptorEC2ERKS0_PS1_S4_
	subl	$12, %esp
	movl	-12(%ebp), %eax
	movl	16(%ebp), %edx
	movl	%edx, 24(%eax)
	movl	-12(%ebp), %eax
	movl	12(%ebp), %edx
	movl	%edx, 28(%eax)
	nop
	leave
	ret	$20
	.section	.text$_ZN8TreeNodeI16MemoryDescriptorE4initERKS0_PS1_S4_S4_S4_,"x"
	.linkonce discard
	.align 2
	.globl	__ZN8TreeNodeI16MemoryDescriptorE4initERKS0_PS1_S4_S4_S4_
	.def	__ZN8TreeNodeI16MemoryDescriptorE4initERKS0_PS1_S4_S4_S4_;	.scl	2;	.type	32;	.endef
__ZN8TreeNodeI16MemoryDescriptorE4initERKS0_PS1_S4_S4_S4_:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	%ecx, -12(%ebp)
	movl	-12(%ebp), %eax
	movl	24(%ebp), %edx
	movl	%edx, 8(%esp)
	movl	20(%ebp), %edx
	movl	%edx, 4(%esp)
	movl	8(%ebp), %edx
	movl	%edx, (%esp)
	movl	%eax, %ecx
	call	__ZN8ListNodeI16MemoryDescriptorE4initERKS0_PS1_S4_
	subl	$12, %esp
	movl	-12(%ebp), %eax
	movl	12(%ebp), %edx
	movl	%edx, 28(%eax)
	movl	-12(%ebp), %eax
	movl	16(%ebp), %edx
	movl	%edx, 24(%eax)
	movl	-12(%ebp), %eax
	leave
	ret	$20
	.section	.text$_ZN8TreeNodeI16MemoryDescriptorED2Ev,"x"
	.linkonce discard
	.align 2
	.globl	__ZN8TreeNodeI16MemoryDescriptorED2Ev
	.def	__ZN8TreeNodeI16MemoryDescriptorED2Ev;	.scl	2;	.type	32;	.endef
__ZN8TreeNodeI16MemoryDescriptorED2Ev:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	%ecx, -12(%ebp)
	movl	-12(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN8ListNodeI16MemoryDescriptorED2Ev
	nop
	leave
	ret
	.section	.text$_ZN8TreeNodeI16MemoryDescriptorED1Ev,"x"
	.linkonce discard
	.align 2
	.globl	__ZN8TreeNodeI16MemoryDescriptorED1Ev
	.def	__ZN8TreeNodeI16MemoryDescriptorED1Ev;	.scl	2;	.type	32;	.endef
__ZN8TreeNodeI16MemoryDescriptorED1Ev:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	%ecx, -12(%ebp)
	movl	-12(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN8ListNodeI16MemoryDescriptorED2Ev
	nop
	leave
	ret
	.section	.text$_ZN8TreeNodeI16MemoryDescriptorE6setSonEPS1_,"x"
	.linkonce discard
	.align 2
	.globl	__ZN8TreeNodeI16MemoryDescriptorE6setSonEPS1_
	.def	__ZN8TreeNodeI16MemoryDescriptorE6setSonEPS1_;	.scl	2;	.type	32;	.endef
__ZN8TreeNodeI16MemoryDescriptorE6setSonEPS1_:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	%ecx, -4(%ebp)
	movl	-4(%ebp), %eax
	movl	8(%ebp), %edx
	movl	%edx, 24(%eax)
	nop
	leave
	ret	$4
	.section	.text$_ZN8TreeNodeI16MemoryDescriptorE9setFatherEPS1_,"x"
	.linkonce discard
	.align 2
	.globl	__ZN8TreeNodeI16MemoryDescriptorE9setFatherEPS1_
	.def	__ZN8TreeNodeI16MemoryDescriptorE9setFatherEPS1_;	.scl	2;	.type	32;	.endef
__ZN8TreeNodeI16MemoryDescriptorE9setFatherEPS1_:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	%ecx, -4(%ebp)
	nop
	leave
	ret	$4
	.section	.text$_ZN8TreeNodeI16MemoryDescriptorE6getSonEv,"x"
	.linkonce discard
	.align 2
	.globl	__ZN8TreeNodeI16MemoryDescriptorE6getSonEv
	.def	__ZN8TreeNodeI16MemoryDescriptorE6getSonEv;	.scl	2;	.type	32;	.endef
__ZN8TreeNodeI16MemoryDescriptorE6getSonEv:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	%ecx, -4(%ebp)
	movl	-4(%ebp), %eax
	movl	24(%eax), %eax
	leave
	ret
	.section	.text$_ZN8TreeNodeI16MemoryDescriptorE15getDirectFatherEv,"x"
	.linkonce discard
	.align 2
	.globl	__ZN8TreeNodeI16MemoryDescriptorE15getDirectFatherEv
	.def	__ZN8TreeNodeI16MemoryDescriptorE15getDirectFatherEv;	.scl	2;	.type	32;	.endef
__ZN8TreeNodeI16MemoryDescriptorE15getDirectFatherEv:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	%ecx, -4(%ebp)
	movl	-4(%ebp), %eax
	movl	28(%eax), %eax
	leave
	ret
	.section	.text$_ZN8TreeNodeI16MemoryDescriptorE9getParentEv,"x"
	.linkonce discard
	.align 2
	.globl	__ZN8TreeNodeI16MemoryDescriptorE9getParentEv
	.def	__ZN8TreeNodeI16MemoryDescriptorE9getParentEv;	.scl	2;	.type	32;	.endef
__ZN8TreeNodeI16MemoryDescriptorE9getParentEv:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$20, %esp
	movl	%ecx, -20(%ebp)
	movl	-20(%ebp), %eax
	movl	%eax, -4(%ebp)
L26:
	movl	-4(%ebp), %eax
	movl	%eax, -12(%ebp)
	movl	-12(%ebp), %eax
	movl	20(%eax), %eax
	testl	%eax, %eax
	setne	%al
	movzbl	%al, %eax
	testl	%eax, %eax
	setne	%al
	testb	%al, %al
	je	L24
	movl	-4(%ebp), %eax
	movl	%eax, -8(%ebp)
	movl	-8(%ebp), %eax
	movl	20(%eax), %eax
	movl	%eax, -4(%ebp)
	jmp	L26
L24:
	movl	-4(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN8TreeNodeI16MemoryDescriptorE15getDirectFatherEv
	leave
	ret
	.ident	"GCC: (GNU) 5.4.0"
	.def	__ZN19SimpleMemoryManagerI8TreeNodeI16MemoryDescriptorEE6getNewEv;	.scl	2;	.type	32;	.endef
	.def	__ZN8ListNodeI16MemoryDescriptorEC2ERKS0_PS1_S4_;	.scl	2;	.type	32;	.endef
	.def	__ZN8ListNodeI16MemoryDescriptorE4initERKS0_PS1_S4_;	.scl	2;	.type	32;	.endef
	.def	__ZN8ListNodeI16MemoryDescriptorED2Ev;	.scl	2;	.type	32;	.endef
