	.file	"PMLoader.cpp"
/APP
	.code16gcc 
	
/NO_APP
	.text
	.align 2
	.globl	__ZN8PMLoaderC2Eiiiii
	.def	__ZN8PMLoaderC2Eiiiii;	.scl	2;	.type	32;	.endef
__ZN8PMLoaderC2Eiiiii:
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
	movl	20(%ebp), %edx
	movl	%edx, 12(%eax)
	movl	-4(%ebp), %eax
	movl	24(%ebp), %edx
	movl	%edx, 16(%eax)
	nop
	leave
	ret	$20
	.globl	__ZN8PMLoaderC1Eiiiii
	.def	__ZN8PMLoaderC1Eiiiii;	.scl	2;	.type	32;	.endef
	.set	__ZN8PMLoaderC1Eiiiii,__ZN8PMLoaderC2Eiiiii
	.align 2
	.globl	__ZN8PMLoaderD2Ev
	.def	__ZN8PMLoaderD2Ev;	.scl	2;	.type	32;	.endef
__ZN8PMLoaderD2Ev:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	%ecx, -4(%ebp)
	nop
	leave
	ret
	.globl	__ZN8PMLoaderD1Ev
	.def	__ZN8PMLoaderD1Ev;	.scl	2;	.type	32;	.endef
	.set	__ZN8PMLoaderD1Ev,__ZN8PMLoaderD2Ev
	.align 2
	.globl	__ZN8PMLoader9enableA20Ev
	.def	__ZN8PMLoader9enableA20Ev;	.scl	2;	.type	32;	.endef
__ZN8PMLoader9enableA20Ev:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	%ecx, -4(%ebp)
/APP
 # 27 "PMLoader.cpp" 1
	inb $0x92,%al 
	orb $0b00000010,%al 
	outb %al,$0x92 
	
 # 0 "" 2
/NO_APP
	nop
	leave
	ret
	.align 2
	.globl	__ZN8PMLoader7setidtrEsi
	.def	__ZN8PMLoader7setidtrEsi;	.scl	2;	.type	32;	.endef
__ZN8PMLoader7setidtrEsi:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	%ecx, -4(%ebp)
	movl	8(%ebp), %eax
	movw	%ax, -8(%ebp)
/APP
 # 36 "PMLoader.cpp" 1
	movw 4+4*1(%ebp),%ax 
	movw %ax,4+4*1+2(%ebp) 
	lidt 4+4*1+2(%ebp) 
	
 # 0 "" 2
/NO_APP
	nop
	leave
	ret	$8
	.align 2
	.globl	__ZN8PMLoader7setgdtrEsi
	.def	__ZN8PMLoader7setgdtrEsi;	.scl	2;	.type	32;	.endef
__ZN8PMLoader7setgdtrEsi:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	%ecx, -4(%ebp)
	movl	8(%ebp), %eax
	movw	%ax, -8(%ebp)
/APP
 # 44 "PMLoader.cpp" 1
	movw 4+4*1(%ebp),%ax 
	movw %ax,4+4*1+2(%ebp) 
	lgdt 4+4*1+2(%ebp) 
	
 # 0 "" 2
/NO_APP
	nop
	leave
	ret	$8
	.align 2
	.globl	__ZN8PMLoader14enterProtectedEv
	.def	__ZN8PMLoader14enterProtectedEv;	.scl	2;	.type	32;	.endef
__ZN8PMLoader14enterProtectedEv:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	%ecx, -4(%ebp)
/APP
 # 57 "PMLoader.cpp" 1
	mov %cr0,%eax 
	or $0x1,%eax 
	mov %eax,%cr0 
	ljmp $JMPSEG,$JMPOFF 
	
 # 0 "" 2
/NO_APP
	nop
	leave
	ret
	.align 2
	.globl	__ZN8PMLoader19adjustProtectedCodeEv
	.def	__ZN8PMLoader19adjustProtectedCodeEv;	.scl	2;	.type	32;	.endef
__ZN8PMLoader19adjustProtectedCodeEv:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	pushl	%ebx
	subl	$48, %esp
	movl	%ecx, -12(%ebp)
	movl	-12(%ebp), %eax
	movl	12(%eax), %eax
	cmpl	$2570, %eax
	jg	L8
	movl	-12(%ebp), %eax
	movl	8(%eax), %ecx
	movl	-12(%ebp), %eax
	movl	4(%eax), %edx
	movl	-12(%ebp), %eax
	movl	(%eax), %eax
	movl	%ecx, 16(%esp)
	movl	%edx, 12(%esp)
	movl	%eax, 8(%esp)
	movl	$0, 4(%esp)
	movl	$2571, (%esp)
	call	__ZN4Util11readSectorsEiiiii
	movl	-12(%ebp), %eax
	movl	8(%eax), %eax
	sall	$9, %eax
	movl	%eax, %ecx
	movl	-12(%ebp), %eax
	movl	16(%eax), %edx
	movl	-12(%ebp), %eax
	movl	12(%eax), %eax
	movl	%ecx, 16(%esp)
	movl	%edx, 12(%esp)
	movl	%eax, 8(%esp)
	movl	$0, 4(%esp)
	movl	$2571, (%esp)
	call	__ZN4Util7memcopyEiiiii
	jmp	L10
L8:
	movl	-12(%ebp), %eax
	movl	8(%eax), %esi
	movl	-12(%ebp), %eax
	movl	4(%eax), %ebx
	movl	-12(%ebp), %eax
	movl	(%eax), %ecx
	movl	-12(%ebp), %eax
	movl	16(%eax), %edx
	movl	-12(%ebp), %eax
	movl	12(%eax), %eax
	movl	%esi, 16(%esp)
	movl	%ebx, 12(%esp)
	movl	%ecx, 8(%esp)
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
	call	__ZN4Util11readSectorsEiiiii
L10:
	nop
	addl	$48, %esp
	popl	%ebx
	popl	%esi
	popl	%ebp
	ret
	.align 2
	.globl	__ZN8PMLoader11mainProcessEisisiii
	.def	__ZN8PMLoader11mainProcessEisisiii;	.scl	2;	.type	32;	.endef
__ZN8PMLoader11mainProcessEisisiii:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$152, %esp
	movl	%ecx, -108(%ebp)
	movl	12(%ebp), %edx
	movl	20(%ebp), %eax
	movw	%dx, -112(%ebp)
	movw	%ax, -116(%ebp)
	movl	-108(%ebp), %eax
	movl	%eax, -12(%ebp)
	movl	__ZN17SegmentDescriptor5DPL_0E, %eax
	movsbl	%al, %ecx
	movl	__ZN17SegmentDescriptor11TYPE_U_DATAE, %eax
	movsbl	%al, %edx
	leal	-42(%ebp), %eax
	movl	$1, 24(%esp)
	movl	$1, 20(%esp)
	movl	$1, 16(%esp)
	movl	%ecx, 12(%esp)
	movl	%edx, 8(%esp)
	movl	$0, 4(%esp)
	movl	$0, (%esp)
	movl	%eax, %ecx
	call	__ZN17SegmentDescriptorC1EPciccccc
	subl	$28, %esp
	movl	__ZN17SegmentDescriptor25TYPE_U_CODE_NONCONFORMINGE, %eax
	movsbl	%al, %edx
	leal	-57(%ebp), %eax
	movl	$1, 24(%esp)
	movl	$1, 20(%esp)
	movl	$1, 16(%esp)
	movl	$0, 12(%esp)
	movl	%edx, 8(%esp)
	movl	28(%ebp), %edx
	movl	%edx, 4(%esp)
	movl	$0, (%esp)
	movl	%eax, %ecx
	call	__ZN17SegmentDescriptorC1EPciccccc
	subl	$28, %esp
	movl	__ZN17SegmentDescriptor11TYPE_U_DATAE, %eax
	movsbl	%al, %edx
	leal	-72(%ebp), %eax
	movl	$1, 24(%esp)
	movl	$1, 20(%esp)
	movl	$1, 16(%esp)
	movl	$0, 12(%esp)
	movl	%edx, 8(%esp)
	movl	28(%ebp), %edx
	movl	%edx, 4(%esp)
	movl	$0, (%esp)
	movl	%eax, %ecx
	call	__ZN17SegmentDescriptorC1EPciccccc
	subl	$28, %esp
	movl	__ZN17SegmentDescriptor12TYPE_U_STACKE, %eax
	movsbl	%al, %edx
	leal	-87(%ebp), %eax
	movl	$1, 24(%esp)
	movl	$1, 20(%esp)
	movl	$1, 16(%esp)
	movl	$0, 12(%esp)
	movl	%edx, 8(%esp)
	movl	32(%ebp), %edx
	movl	%edx, 4(%esp)
	movl	$0, (%esp)
	movl	%eax, %ecx
	call	__ZN17SegmentDescriptorC1EPciccccc
	subl	$28, %esp
	movl	__ZN17SegmentDescriptor11TYPE_U_DATAE, %eax
	movsbl	%al, %edx
	leal	-102(%ebp), %eax
	movl	$1, 24(%esp)
	movl	$1, 20(%esp)
	movl	$1, 16(%esp)
	movl	$0, 12(%esp)
	movl	%edx, 8(%esp)
	movl	$4000, 4(%esp)
	movl	$753664, (%esp)
	movl	%eax, %ecx
	call	__ZN17SegmentDescriptorC1EPciccccc
	subl	$28, %esp
	movl	__ZN17SegmentDescriptor11TYPE_U_DATAE, %eax
	movsbl	%al, %edx
	movl	__ZN17SegmentDescriptor5DPL_0E, %eax
	movsbl	%al, %ecx
	leal	-27(%ebp), %eax
	movl	$1, 24(%esp)
	movl	$1, 20(%esp)
	movl	$1, 16(%esp)
	movl	%ecx, 12(%esp)
	movl	%edx, 8(%esp)
	movl	$0, 4(%esp)
	movl	$0, (%esp)
	movl	%eax, %ecx
	call	__ZN17SegmentDescriptorC1EPciccccc
	subl	$28, %esp
	movl	-27(%ebp), %eax
	movl	%eax, -42(%ebp)
	movl	-23(%ebp), %eax
	movl	%eax, -38(%ebp)
	movl	-19(%ebp), %eax
	movl	%eax, -34(%ebp)
	movzwl	-15(%ebp), %eax
	movw	%ax, -30(%ebp)
	movzbl	-13(%ebp), %eax
	movb	%al, -28(%ebp)
	leal	-27(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN17SegmentDescriptorD1Ev
	movl	16(%ebp), %edx
	leal	-42(%ebp), %eax
	movl	%edx, 4(%esp)
	movl	$0, (%esp)
	movl	%eax, %ecx
	call	__ZN17SegmentDescriptor13writeToMemoryEiPc
	subl	$8, %esp
	movl	16(%ebp), %eax
	addl	$8, %eax
	movl	%eax, %edx
	leal	-102(%ebp), %eax
	movl	%edx, 4(%esp)
	movl	$0, (%esp)
	movl	%eax, %ecx
	call	__ZN17SegmentDescriptor13writeToMemoryEiPc
	subl	$8, %esp
	movl	16(%ebp), %eax
	addl	$16, %eax
	movl	%eax, %edx
	leal	-57(%ebp), %eax
	movl	%edx, 4(%esp)
	movl	$0, (%esp)
	movl	%eax, %ecx
	call	__ZN17SegmentDescriptor13writeToMemoryEiPc
	subl	$8, %esp
	movl	16(%ebp), %eax
	addl	$24, %eax
	movl	%eax, %edx
	leal	-72(%ebp), %eax
	movl	%edx, 4(%esp)
	movl	$0, (%esp)
	movl	%eax, %ecx
	call	__ZN17SegmentDescriptor13writeToMemoryEiPc
	subl	$8, %esp
	movl	16(%ebp), %eax
	addl	$32, %eax
	movl	%eax, %edx
	leal	-87(%ebp), %eax
	movl	%edx, 4(%esp)
	movl	$0, (%esp)
	movl	%eax, %ecx
	call	__ZN17SegmentDescriptor13writeToMemoryEiPc
	subl	$8, %esp
	movl	-12(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN8PMLoader19adjustProtectedCodeEv
	movl	-12(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN8PMLoader9enableA20Ev
	movswl	-112(%ebp), %edx
	movl	-12(%ebp), %eax
	movl	8(%ebp), %ecx
	movl	%ecx, 4(%esp)
	movl	%edx, (%esp)
	movl	%eax, %ecx
	call	__ZN8PMLoader7setidtrEsi
	subl	$8, %esp
	movswl	-116(%ebp), %edx
	movl	-12(%ebp), %eax
	movl	16(%ebp), %ecx
	movl	%ecx, 4(%esp)
	movl	%edx, (%esp)
	movl	%eax, %ecx
	call	__ZN8PMLoader7setgdtrEsi
	subl	$8, %esp
	movl	-12(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN8PMLoader14enterProtectedEv
	leal	-102(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN17SegmentDescriptorD1Ev
	leal	-87(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN17SegmentDescriptorD1Ev
	leal	-72(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN17SegmentDescriptorD1Ev
	leal	-57(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN17SegmentDescriptorD1Ev
	leal	-42(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN17SegmentDescriptorD1Ev
	nop
	leave
	ret	$28
	.ident	"GCC: (GNU) 5.4.0"
	.def	__ZN4Util11readSectorsEiiiii;	.scl	2;	.type	32;	.endef
	.def	__ZN4Util7memcopyEiiiii;	.scl	2;	.type	32;	.endef
	.def	__ZN17SegmentDescriptorC1EPciccccc;	.scl	2;	.type	32;	.endef
	.def	__ZN17SegmentDescriptorD1Ev;	.scl	2;	.type	32;	.endef
	.def	__ZN17SegmentDescriptor13writeToMemoryEiPc;	.scl	2;	.type	32;	.endef
