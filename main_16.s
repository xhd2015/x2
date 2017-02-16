	.file	"main.cpp"
/APP
	.text 
	.code16gcc 
	STARTSEG = 0x7c0 
	STACKSIZE = 512*2 
	TEMP_SEG = 0xa00 
	
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
	pushw $TEMP_SEG 
	pushw $__Z8theEntryv 
	ljmpw *(%esp) 
	
/NO_APP
	.text
	.globl	_readLaterSectors
	.def	_readLaterSectors;	.scl	2;	.type	32;	.endef
_readLaterSectors:
	pushl	%ebp
	movl	%esp, %ebp
/APP
 # 48 "main.cpp" 1
	READLEN =  16 -2  
	push %es
	movw $TEMP_SEG,%ax 
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
	pushl	%ebx
	subl	$100, %esp
/APP
 # 58 "main.cpp" 1
	movl $TEMP_SEG,%eax 
	mov %eax,%ds
	mov %eax,%es 
	mov %eax,%ss 
	
 # 0 "" 2
/NO_APP
	movl	__ZN8PMLoader7SECSIZEE, %edx
	movl	__ZN8PMLoader8TEMP_SEGE, %eax
	movl	%edx, 16(%esp)
	movl	$0, 12(%esp)
	movl	%eax, 8(%esp)
	movl	$0, 4(%esp)
	movl	$1984, (%esp)
	call	__ZN4Util7memcopyEiiiii
	movl	__ZN4Util11MODE_COMMONE, %eax
	movl	%eax, 4(%esp)
	movl	$LC0, (%esp)
	call	__ZN4Util8printStrEPKci
	leal	-13(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN4UtilC1Ev
	leal	-13(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN4Util4testEv
	movl	__ZN8PMLoader8TEMP_SEGE, %eax
	sall	$4, %eax
	movl	%eax, -12(%ebp)
	movl	__ZN8PMLoader8TEMP_SEGE, %edx
	movl	__ZN8PMLoader8TEMP_SEGE, %eax
	movl	$512, 16(%esp)
	movl	$0, 12(%esp)
	movl	%edx, 8(%esp)
	movl	$512, 4(%esp)
	movl	%eax, (%esp)
	call	__ZN4Util7memcopyEiiiii
	movl	$1365, (%esp)
	call	__ZN4Util10insertMarkEi
	movl	__ZN8PMLoader8TEMP_SEGE, %eax
	movl	$1, 16(%esp)
	movl	$0, 12(%esp)
	movl	$0, 8(%esp)
	movl	$0, 4(%esp)
	movl	%eax, (%esp)
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
	movsbl	%al, %ebx
	movl	__ZN17SegmentDescriptor11TYPE_U_DATAE, %eax
	movsbl	%al, %ecx
	movl	-12(%ebp), %edx
	leal	-28(%ebp), %eax
	movl	$1, 24(%esp)
	movl	$1, 20(%esp)
	movl	$1, 16(%esp)
	movl	%ebx, 12(%esp)
	movl	%ecx, 8(%esp)
	movl	$1024, 4(%esp)
	movl	%edx, (%esp)
	movl	%eax, %ecx
	call	__ZN17SegmentDescriptorC1EPciccccc
	subl	$28, %esp
	leal	-28(%ebp), %eax
	leal	-36(%ebp), %edx
	movl	%edx, 4(%esp)
	movl	$65536, (%esp)
	movl	%eax, %ecx
	call	__ZN17SegmentDescriptor13writeToMemoryEiPc
	subl	$8, %esp
	movl	__ZN17SegmentDescriptor5DPL_0E, %eax
	movsbl	%al, %ecx
	movl	__ZN17SegmentDescriptor11TYPE_U_DATAE, %eax
	movsbl	%al, %edx
	leal	-51(%ebp), %eax
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
	leal	-36(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	$65536, 4(%esp)
	leal	-51(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZN17SegmentDescriptor10fromMemoryEPS_iPc
	leal	-51(%ebp), %eax
	leal	-59(%ebp), %edx
	movl	%edx, 4(%esp)
	movl	$65536, (%esp)
	movl	%eax, %ecx
	call	__ZN17SegmentDescriptor13writeToMemoryEiPc
	subl	$8, %esp
	leal	-28(%ebp), %eax
	leal	-51(%ebp), %edx
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
	call	__ZN8PMLoader11mainProcessEv
	leal	-51(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN17SegmentDescriptorD1Ev
	leal	-28(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN17SegmentDescriptorD1Ev
	leal	-13(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN4UtilD1Ev
	nop
	movl	-4(%ebp), %ebx
	leave
	ret
/APP
	.section .last_section 
	.org 2 
	.word 0xaa55 
	
	.ident	"GCC: (GNU) 5.4.0"
	.def	__ZN4Util7memcopyEiiiii;	.scl	2;	.type	32;	.endef
	.def	__ZN4Util8printStrEPKci;	.scl	2;	.type	32;	.endef
	.def	__ZN4UtilC1Ev;	.scl	2;	.type	32;	.endef
	.def	__ZN4Util4testEv;	.scl	2;	.type	32;	.endef
	.def	__ZN4Util10insertMarkEi;	.scl	2;	.type	32;	.endef
	.def	__ZN4Util11readSectorsEiiiii;	.scl	2;	.type	32;	.endef
	.def	__ZN17SegmentDescriptorC1EPciccccc;	.scl	2;	.type	32;	.endef
	.def	__ZN17SegmentDescriptor13writeToMemoryEiPc;	.scl	2;	.type	32;	.endef
	.def	__ZN17SegmentDescriptor10fromMemoryEPS_iPc;	.scl	2;	.type	32;	.endef
	.def	__ZN17SegmentDescriptor6equalsERS_;	.scl	2;	.type	32;	.endef
	.def	__ZN8PMLoader11mainProcessEv;	.scl	2;	.type	32;	.endef
	.def	__ZN17SegmentDescriptorD1Ev;	.scl	2;	.type	32;	.endef
	.def	__ZN4UtilD1Ev;	.scl	2;	.type	32;	.endef
