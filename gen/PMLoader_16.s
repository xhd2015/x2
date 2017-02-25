	.file	"PMLoader.cpp"
/APP
	.code16gcc 
	
/NO_APP
	.globl	__ZN8PMLoader8SAFE_SEGE
	.section .rdata,"dr"
	.align 4
__ZN8PMLoader8SAFE_SEGE:
	.long	256
	.globl	__ZN8PMLoader7SECSIZEE
	.align 4
__ZN8PMLoader7SECSIZEE:
	.long	512
	.globl	__ZN8PMLoader11STACK_STARTE
	.align 4
__ZN8PMLoader11STACK_STARTE:
	.space 4
	.globl	__ZN8PMLoader10STACK_SIZEE
	.align 4
__ZN8PMLoader10STACK_SIZEE:
	.long	2048
	.globl	__ZN8PMLoader9IDT_STARTE
	.align 4
__ZN8PMLoader9IDT_STARTE:
	.long	2048
	.globl	__ZN8PMLoader8IDT_SIZEE
	.align 4
__ZN8PMLoader8IDT_SIZEE:
	.long	512
	.globl	__ZN8PMLoader9GDT_STARTE
	.align 4
__ZN8PMLoader9GDT_STARTE:
	.long	2560
	.globl	__ZN8PMLoader8GDT_SIZEE
	.align 4
__ZN8PMLoader8GDT_SIZEE:
	.long	1024
	.globl	__ZN8PMLoader13TSS_AREA_SIZEE
	.align 4
__ZN8PMLoader13TSS_AREA_SIZEE:
	.long	1024
	.globl	__ZN8PMLoader14TSS_AREA_STARTE
	.align 4
__ZN8PMLoader14TSS_AREA_STARTE:
	.long	3584
	.globl	__ZN8PMLoader12TSS_MIN_SIZEE
	.align 4
__ZN8PMLoader12TSS_MIN_SIZEE:
	.long	104
	.globl	__ZN8PMLoader14FREE_HEAP_SIZEE
	.align 4
__ZN8PMLoader14FREE_HEAP_SIZEE:
	.long	2560
	.globl	__ZN8PMLoader15FREE_HEAP_STARTE
	.align 4
__ZN8PMLoader15FREE_HEAP_STARTE:
	.long	4608
	.globl	__ZN8PMLoader10CODE_STARTE
	.align 4
__ZN8PMLoader10CODE_STARTE:
	.long	7168
	.globl	__ZN8PMLoader8CODE_SEGE
	.align 4
__ZN8PMLoader8CODE_SEGE:
	.space 4
	.globl	__ZN8PMLoader10CODE_LIMITE
	.align 4
__ZN8PMLoader10CODE_LIMITE:
	.long	1048575
	.globl	__ZN8PMLoader6JMPSEGE
	.align 4
__ZN8PMLoader6JMPSEGE:
	.long	16
	.globl	__ZN8PMLoader6DRIVERE
	.align 4
__ZN8PMLoader6DRIVERE:
	.space 4
	.globl	__ZN8PMLoader12REAL_SECNUMSE
	.align 4
__ZN8PMLoader12REAL_SECNUMSE:
	.long	16
	.globl	__ZN8PMLoader17PROTECTED_SECNUMSE
	.align 4
__ZN8PMLoader17PROTECTED_SECNUMSE:
	.long	60
	.globl	__ZN8PMLoader8TEMP_SEGE
	.align 4
__ZN8PMLoader8TEMP_SEGE:
	.long	2560
	.text
	.align 2
	.globl	__ZN8PMLoaderC2Ev
	.def	__ZN8PMLoaderC2Ev;	.scl	2;	.type	32;	.endef
__ZN8PMLoaderC2Ev:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	%ecx, -4(%ebp)
	nop
	leave
	ret
	.globl	__ZN8PMLoaderC1Ev
	.def	__ZN8PMLoaderC1Ev;	.scl	2;	.type	32;	.endef
	.set	__ZN8PMLoaderC1Ev,__ZN8PMLoaderC2Ev
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
/APP
 # 53 "PMLoader.cpp" 1
	inb $0x92,%al 
	orb $0b00000010,%al 
	outb %al,$0x92 
	
 # 0 "" 2
/NO_APP
	nop
	popl	%ebp
	ret
	.align 2
	.globl	__ZN8PMLoader7setidtrEsi
	.def	__ZN8PMLoader7setidtrEsi;	.scl	2;	.type	32;	.endef
__ZN8PMLoader7setidtrEsi:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	8(%ebp), %eax
	movw	%ax, -4(%ebp)
/APP
 # 62 "PMLoader.cpp" 1
	movw 4+4*1(%ebp),%ax 
	movw %ax,4+4*1+2(%ebp) 
	lidt 4+4*1+2(%ebp) 
	
 # 0 "" 2
/NO_APP
	nop
	leave
	ret
	.align 2
	.globl	__ZN8PMLoader7setgdtrEsi
	.def	__ZN8PMLoader7setgdtrEsi;	.scl	2;	.type	32;	.endef
__ZN8PMLoader7setgdtrEsi:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	8(%ebp), %eax
	movw	%ax, -4(%ebp)
/APP
 # 70 "PMLoader.cpp" 1
	movw 4+4*1(%ebp),%ax 
	movw %ax,4+4*1+2(%ebp) 
	lgdt 4+4*1+2(%ebp) 
	
 # 0 "" 2
/NO_APP
	nop
	leave
	ret
	.align 2
	.globl	__ZN8PMLoader14enterProtectedEv
	.def	__ZN8PMLoader14enterProtectedEv;	.scl	2;	.type	32;	.endef
__ZN8PMLoader14enterProtectedEv:
	pushl	%ebp
	movl	%esp, %ebp
/APP
 # 83 "PMLoader.cpp" 1
	mov %cr0,%eax 
	or $0x1,%eax 
	mov %eax,%cr0 
	movw __ZN8PMLoader6JMPSEGE,%ax 
	movw __ZN8PMLoader10CODE_STARTE,%bx 
	pushw %ax 
	pushw %bx 
	ljmp *(%esp) 
	
 # 0 "" 2
/NO_APP
	nop
	popl	%ebp
	ret
	.align 2
	.globl	__ZN8PMLoader19adjustProtectedCodeEv
	.def	__ZN8PMLoader19adjustProtectedCodeEv;	.scl	2;	.type	32;	.endef
__ZN8PMLoader19adjustProtectedCodeEv:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	$60, 16(%esp)
	movl	$16, 12(%esp)
	movl	$0, 8(%esp)
	movl	$7168, 4(%esp)
	movl	$0, (%esp)
	call	__ZN4Util11readSectorsEiiiii
	nop
	leave
	ret
	.align 2
	.globl	__ZN8PMLoader11mainProcessEv
	.def	__ZN8PMLoader11mainProcessEv;	.scl	2;	.type	32;	.endef
__ZN8PMLoader11mainProcessEv:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$136, %esp
	call	__ZN8PMLoader19adjustProtectedCodeEv
	movl	__ZN17SegmentDescriptor5DPL_0E, %eax
	movsbl	%al, %ecx
	movl	__ZN17SegmentDescriptor11TYPE_U_DATAE, %eax
	movsbl	%al, %edx
	leal	-38(%ebp), %eax
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
	leal	-53(%ebp), %eax
	movl	$1, 24(%esp)
	movl	$1, 20(%esp)
	movl	$1, 16(%esp)
	movl	$0, 12(%esp)
	movl	%edx, 8(%esp)
	movl	$1048575, 4(%esp)
	movl	$0, (%esp)
	movl	%eax, %ecx
	call	__ZN17SegmentDescriptorC1EPciccccc
	subl	$28, %esp
	movl	__ZN17SegmentDescriptor11TYPE_U_DATAE, %eax
	movsbl	%al, %edx
	leal	-68(%ebp), %eax
	movl	$1, 24(%esp)
	movl	$1, 20(%esp)
	movl	$1, 16(%esp)
	movl	$0, 12(%esp)
	movl	%edx, 8(%esp)
	movl	$1048575, 4(%esp)
	movl	$0, (%esp)
	movl	%eax, %ecx
	call	__ZN17SegmentDescriptorC1EPciccccc
	subl	$28, %esp
	movl	__ZN17SegmentDescriptor12TYPE_U_STACKE, %eax
	movsbl	%al, %edx
	leal	-83(%ebp), %eax
	movl	$1, 24(%esp)
	movl	$1, 20(%esp)
	movl	$1, 16(%esp)
	movl	$0, 12(%esp)
	movl	%edx, 8(%esp)
	movl	$2048, 4(%esp)
	movl	$0, (%esp)
	movl	%eax, %ecx
	call	__ZN17SegmentDescriptorC1EPciccccc
	subl	$28, %esp
	movl	__ZN17SegmentDescriptor11TYPE_U_DATAE, %eax
	movsbl	%al, %edx
	leal	-98(%ebp), %eax
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
	leal	-23(%ebp), %eax
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
	movl	-23(%ebp), %eax
	movl	%eax, -38(%ebp)
	movl	-19(%ebp), %eax
	movl	%eax, -34(%ebp)
	movl	-15(%ebp), %eax
	movl	%eax, -30(%ebp)
	movzwl	-11(%ebp), %eax
	movw	%ax, -26(%ebp)
	movzbl	-9(%ebp), %eax
	movb	%al, -24(%ebp)
	leal	-23(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN17SegmentDescriptorD1Ev
	leal	-38(%ebp), %eax
	movl	$2560, 4(%esp)
	movl	$0, (%esp)
	movl	%eax, %ecx
	call	__ZN17SegmentDescriptor13writeToMemoryEiPc
	subl	$8, %esp
	leal	-98(%ebp), %eax
	movl	$2568, 4(%esp)
	movl	$0, (%esp)
	movl	%eax, %ecx
	call	__ZN17SegmentDescriptor13writeToMemoryEiPc
	subl	$8, %esp
	leal	-53(%ebp), %eax
	movl	$2576, 4(%esp)
	movl	$0, (%esp)
	movl	%eax, %ecx
	call	__ZN17SegmentDescriptor13writeToMemoryEiPc
	subl	$8, %esp
	leal	-68(%ebp), %eax
	movl	$2584, 4(%esp)
	movl	$0, (%esp)
	movl	%eax, %ecx
	call	__ZN17SegmentDescriptor13writeToMemoryEiPc
	subl	$8, %esp
	leal	-83(%ebp), %eax
	movl	$2592, 4(%esp)
	movl	$0, (%esp)
	movl	%eax, %ecx
	call	__ZN17SegmentDescriptor13writeToMemoryEiPc
	subl	$8, %esp
	call	__ZN8PMLoader9enableA20Ev
	movl	$2048, 4(%esp)
	movl	$511, (%esp)
	call	__ZN8PMLoader7setidtrEsi
	movl	$2560, 4(%esp)
	movl	$1023, (%esp)
	call	__ZN8PMLoader7setgdtrEsi
	call	__ZN8PMLoader14enterProtectedEv
	leal	-98(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN17SegmentDescriptorD1Ev
	leal	-83(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN17SegmentDescriptorD1Ev
	leal	-68(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN17SegmentDescriptorD1Ev
	leal	-53(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN17SegmentDescriptorD1Ev
	leal	-38(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN17SegmentDescriptorD1Ev
	nop
	leave
	ret
	.ident	"GCC: (GNU) 5.4.0"
	.def	__ZN4Util11readSectorsEiiiii;	.scl	2;	.type	32;	.endef
	.def	__ZN17SegmentDescriptorC1EPciccccc;	.scl	2;	.type	32;	.endef
	.def	__ZN17SegmentDescriptorD1Ev;	.scl	2;	.type	32;	.endef
	.def	__ZN17SegmentDescriptor13writeToMemoryEiPc;	.scl	2;	.type	32;	.endef
