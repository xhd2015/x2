	.file	"main.cpp"
/APP
	.text 
	.code16gcc 
	STARTSEG = 0x7c0 
	STACKSIZE = 512*2
	ljmp $STARTSEG,$HERE 
	HERE: 
	cli 
	mov $STARTSEG,%ax 
	mov %ax,%ds 
	mov %ax,%ss 
	mov %ax,%es 
	mov $STACKSIZE,%sp 
	#mov %ax,%sp 
	call _readLaterSectors
	call __Z8theEntryv 
	DIE:
	jmp DIE 
	
/NO_APP
	.text
	.globl	_readLaterSectors
	.def	_readLaterSectors;	.scl	2;	.type	32;	.endef
_readLaterSectors:
	pushl	%ebp
	movl	%esp, %ebp
/APP
 # 43 "main.cpp" 1
	READLEN =  16-2
	push %es
	mov $STARTSEG,%ax 
	mov %ax,%es
	mov $STACKSIZE,%bx
	xor %dx,%dx 
	mov $0x0003,%cx 
	mov $0x200+READLEN,%ax 
	int $0x13 
	pop %es 
	
 # 0 "" 2
/NO_APP
	nop
	popl	%ebp
	ret
	.section .rdata,"dr"
LC0:
	.ascii "Hello World!\0"
LC1:
	.ascii "Load Tested.\12\0"
LC2:
	.ascii "SegmentDescriptor Right!!!\12\0"
LC3:
	.ascii "Util The End.\12\0"
	.section	.test_section,"x"
	.globl	__Z8theEntryv
	.def	__Z8theEntryv;	.scl	2;	.type	32;	.endef
__Z8theEntryv:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$120, %esp
	movl	__ZN4Util11MODE_COMMONE, %eax
	movl	%eax, 4(%esp)
	movl	$LC0, (%esp)
	call	__ZN4Util8printStrEPKci
	leal	-9(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN4UtilC1Ev
	leal	-9(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN4Util4testEv
	movl	$512, 16(%esp)
	movl	$0, 12(%esp)
	movl	$1984, 8(%esp)
	movl	$512, 4(%esp)
	movl	$1984, (%esp)
	call	__ZN4Util7memcopyEiiiii
	movl	$1365, (%esp)
	call	__ZN4Util10insertMarkEi
	movl	$1, 16(%esp)
	movl	$0, 12(%esp)
	movl	$0, 8(%esp)
	movl	$0, 4(%esp)
	movl	$1984, (%esp)
	call	__ZN4Util11readSectorsEiiiii
	testl	%eax, %eax
	setne	%al
	testb	%al, %al
	je	L3
	movl	__ZN4Util11MODE_COMMONE, %eax
	movl	%eax, 4(%esp)
	movl	$LC1, (%esp)
	call	__ZN4Util8printStrEPKci
L3:
	movl	__ZN17SegmentDescriptor5DPL_0E, %eax
	movsbl	%al, %ecx
	movl	__ZN17SegmentDescriptor11TYPE_U_DATAE, %eax
	movsbl	%al, %edx
	leal	-24(%ebp), %eax
	movl	$1, 24(%esp)
	movl	$1, 20(%esp)
	movl	$1, 16(%esp)
	movl	%ecx, 12(%esp)
	movl	%edx, 8(%esp)
	movl	$1024, 4(%esp)
	movl	$31744, (%esp)
	movl	%eax, %ecx
	call	__ZN17SegmentDescriptorC1EPciccccc
	subl	$28, %esp
	leal	-24(%ebp), %eax
	leal	-32(%ebp), %edx
	movl	%edx, 4(%esp)
	movl	$65536, (%esp)
	movl	%eax, %ecx
	call	__ZN17SegmentDescriptor13writeToMemoryEiPc
	subl	$8, %esp
	movl	__ZN17SegmentDescriptor5DPL_0E, %eax
	movsbl	%al, %ecx
	movl	__ZN17SegmentDescriptor11TYPE_U_DATAE, %eax
	movsbl	%al, %edx
	leal	-47(%ebp), %eax
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
	leal	-32(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	$65536, 4(%esp)
	leal	-47(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZN17SegmentDescriptor10fromMemoryEPS_iPc
	leal	-47(%ebp), %eax
	leal	-55(%ebp), %edx
	movl	%edx, 4(%esp)
	movl	$65536, (%esp)
	movl	%eax, %ecx
	call	__ZN17SegmentDescriptor13writeToMemoryEiPc
	subl	$8, %esp
	leal	-24(%ebp), %eax
	leal	-47(%ebp), %edx
	movl	%edx, (%esp)
	movl	%eax, %ecx
	call	__ZN17SegmentDescriptor6equalsERS_
	subl	$4, %esp
	testl	%eax, %eax
	setne	%al
	testb	%al, %al
	je	L4
	movl	__ZN4Util11MODE_COMMONE, %eax
	movl	%eax, 4(%esp)
	movl	$LC2, (%esp)
	call	__ZN4Util8printStrEPKci
L4:
	movl	__ZN4Util11MODE_COMMONE, %eax
	movl	%eax, 4(%esp)
	movl	$LC3, (%esp)
	call	__ZN4Util8printStrEPKci
	leal	-75(%ebp), %eax
	movl	$0, 16(%esp)
	movl	$0, 12(%esp)
	movl	$34, 8(%esp)
	movl	$16, 4(%esp)
	movl	$0, (%esp)
	movl	%eax, %ecx
	call	__ZN8PMLoaderC1Eiiiii
	subl	$20, %esp
	leal	-75(%ebp), %eax
	movl	$2048, 24(%esp)
	movl	$1048575, 20(%esp)
	movl	$0, 16(%esp)
	movl	$800, 12(%esp)
	movl	$40336, 8(%esp)
	movl	$400, 4(%esp)
	movl	$39936, (%esp)
	movl	%eax, %ecx
	call	__ZN8PMLoader11mainProcessEisisiii
	subl	$28, %esp
	leal	-75(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN8PMLoaderD1Ev
	leal	-47(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN17SegmentDescriptorD1Ev
	leal	-24(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN17SegmentDescriptorD1Ev
	leal	-9(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN4UtilD1Ev
	nop
	leave
	ret
/APP
	.section .last_section 
	.org 2 
	.word 0xaa55 
	
	.ident	"GCC: (GNU) 5.4.0"
	.def	__ZN4Util8printStrEPKci;	.scl	2;	.type	32;	.endef
	.def	__ZN4UtilC1Ev;	.scl	2;	.type	32;	.endef
	.def	__ZN4Util4testEv;	.scl	2;	.type	32;	.endef
	.def	__ZN4Util7memcopyEiiiii;	.scl	2;	.type	32;	.endef
	.def	__ZN4Util10insertMarkEi;	.scl	2;	.type	32;	.endef
	.def	__ZN4Util11readSectorsEiiiii;	.scl	2;	.type	32;	.endef
	.def	__ZN17SegmentDescriptorC1EPciccccc;	.scl	2;	.type	32;	.endef
	.def	__ZN17SegmentDescriptor13writeToMemoryEiPc;	.scl	2;	.type	32;	.endef
	.def	__ZN17SegmentDescriptor10fromMemoryEPS_iPc;	.scl	2;	.type	32;	.endef
	.def	__ZN17SegmentDescriptor6equalsERS_;	.scl	2;	.type	32;	.endef
	.def	__ZN8PMLoaderC1Eiiiii;	.scl	2;	.type	32;	.endef
	.def	__ZN8PMLoader11mainProcessEisisiii;	.scl	2;	.type	32;	.endef
	.def	__ZN8PMLoaderD1Ev;	.scl	2;	.type	32;	.endef
	.def	__ZN17SegmentDescriptorD1Ev;	.scl	2;	.type	32;	.endef
	.def	__ZN4UtilD1Ev;	.scl	2;	.type	32;	.endef
