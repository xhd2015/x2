	.file	"main.cpp"
/APP
	.text 
	.code16gcc 
	STARTSEG = 0x7c0 
	STACKSIZE = 512*2
	ljmp $STARTSEG,$HERE 
	HERE: 
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
 # 40 "main.cpp" 1
	READLEN = 20 
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
	.ascii "Right!!!\12\0"
LC3:
	.ascii "The End.\12\0"
	.section	.test_section,"x"
	.globl	__Z8theEntryv
	.def	__Z8theEntryv;	.scl	2;	.type	32;	.endef
__Z8theEntryv:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$184, %esp
	movl	$7, 4(%esp)
	movl	$LC0, (%esp)
	call	__ZN4Util8printStrEPKci
	leal	-24(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN4UtilC1Ev
	leal	-24(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN4Util4testEv
	leal	-25(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN8PMLoaderC1Ev
	leal	-25(%ebp), %eax
	movl	$512, 16(%esp)
	movl	$0, 12(%esp)
	movl	$1984, 8(%esp)
	movl	$512, 4(%esp)
	movl	$1984, (%esp)
	movl	%eax, %ecx
	call	__ZN8PMLoader7memcopyEiiiii
	subl	$20, %esp
	leal	-25(%ebp), %eax
	movl	$1, 24(%esp)
	movl	$1, 20(%esp)
	movl	$0, 16(%esp)
	movl	$0, 12(%esp)
	movl	$0, 8(%esp)
	movl	$0, 4(%esp)
	movl	$1984, (%esp)
	movl	%eax, %ecx
	call	__ZN8PMLoader11readSectorsEiiiiiii
	subl	$28, %esp
	testl	%eax, %eax
	setne	%al
	testb	%al, %al
	je	L3
	movl	$7, 4(%esp)
	movl	$LC1, (%esp)
	call	__ZN4Util8printStrEPKci
L3:
	movl	__ZN17SegmentDescriptor5DPL_0E, %eax
	movsbl	%al, %ecx
	movl	__ZN17SegmentDescriptor11TYPE_U_DATAE, %eax
	movsbl	%al, %edx
	leal	-40(%ebp), %eax
	movl	%ecx, 12(%esp)
	movl	%edx, 8(%esp)
	movl	$1024, 4(%esp)
	movl	$31744, (%esp)
	movl	%eax, %ecx
	call	__ZN17SegmentDescriptorC1EPcicc
	subl	$16, %esp
	movl	$4659, (%esp)
	call	__ZN4Util10insertMarkEi
	leal	-40(%ebp), %eax
	leal	-48(%ebp), %edx
	movl	%edx, 4(%esp)
	movl	$65536, (%esp)
	movl	%eax, %ecx
	call	__ZN17SegmentDescriptor13writeToMemoryEiPc
	subl	$8, %esp
	movl	__ZN17SegmentDescriptor5DPL_0E, %eax
	movsbl	%al, %ecx
	movl	__ZN17SegmentDescriptor11TYPE_U_DATAE, %eax
	movsbl	%al, %edx
	leal	-63(%ebp), %eax
	movl	%ecx, 12(%esp)
	movl	%edx, 8(%esp)
	movl	$0, 4(%esp)
	movl	$0, (%esp)
	movl	%eax, %ecx
	call	__ZN17SegmentDescriptorC1EPcicc
	subl	$16, %esp
	movl	$4658, (%esp)
	call	__ZN4Util10insertMarkEi
	leal	-48(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	$65536, 4(%esp)
	leal	-63(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZN17SegmentDescriptor10fromMemoryEPS_iPc
	leal	-63(%ebp), %eax
	leal	-71(%ebp), %edx
	movl	%edx, 4(%esp)
	movl	$65536, (%esp)
	movl	%eax, %ecx
	call	__ZN17SegmentDescriptor13writeToMemoryEiPc
	subl	$8, %esp
	leal	-40(%ebp), %eax
	leal	-63(%ebp), %edx
	movl	%edx, (%esp)
	movl	%eax, %ecx
	call	__ZN17SegmentDescriptor6equalsERS_
	subl	$4, %esp
	testl	%eax, %eax
	setne	%al
	testb	%al, %al
	je	L4
	movl	$7, 4(%esp)
	movl	$LC2, (%esp)
	call	__ZN4Util8printStrEPKci
L4:
	movl	$7, 4(%esp)
	movl	$LC3, (%esp)
	call	__ZN4Util8printStrEPKci
	leal	-25(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN8PMLoader9enableA20Ev
	leal	-25(%ebp), %eax
	movl	$1024, 4(%esp)
	movl	$400, (%esp)
	movl	%eax, %ecx
	call	__ZN8PMLoader7setidtrEsi
	subl	$8, %esp
	leal	-25(%ebp), %eax
	movl	$1424, 4(%esp)
	movl	$800, (%esp)
	movl	%eax, %ecx
	call	__ZN8PMLoader7setgdtrEsi
	subl	$8, %esp
	movl	__ZN17SegmentDescriptor5DPL_0E, %eax
	movsbl	%al, %ecx
	movl	__ZN17SegmentDescriptor11TYPE_U_DATAE, %eax
	movsbl	%al, %edx
	leal	-86(%ebp), %eax
	movl	%ecx, 12(%esp)
	movl	%edx, 8(%esp)
	movl	$0, 4(%esp)
	movl	$0, (%esp)
	movl	%eax, %ecx
	call	__ZN17SegmentDescriptorC1EPcicc
	subl	$16, %esp
	movl	__ZN17SegmentDescriptor22TYPE_U_CODE_CONFORMINGE, %eax
	movsbl	%al, %edx
	leal	-101(%ebp), %eax
	movl	$0, 12(%esp)
	movl	%edx, 8(%esp)
	movl	$10240, 4(%esp)
	movl	$31744, (%esp)
	movl	%eax, %ecx
	call	__ZN17SegmentDescriptorC1EPcicc
	subl	$16, %esp
	movl	__ZN17SegmentDescriptor11TYPE_U_DATAE, %eax
	movsbl	%al, %edx
	leal	-116(%ebp), %eax
	movl	$0, 12(%esp)
	movl	%edx, 8(%esp)
	movl	$10240, 4(%esp)
	movl	$31744, (%esp)
	movl	%eax, %ecx
	call	__ZN17SegmentDescriptorC1EPcicc
	subl	$16, %esp
	movl	__ZN17SegmentDescriptor12TYPE_U_STACKE, %eax
	movsbl	%al, %edx
	leal	-131(%ebp), %eax
	movl	$0, 12(%esp)
	movl	%edx, 8(%esp)
	movl	$10240, 4(%esp)
	movl	$31744, (%esp)
	movl	%eax, %ecx
	call	__ZN17SegmentDescriptorC1EPcicc
	subl	$16, %esp
	movl	__ZN17SegmentDescriptor11TYPE_U_DATAE, %eax
	movsbl	%al, %edx
	leal	-146(%ebp), %eax
	movl	$0, 12(%esp)
	movl	%edx, 8(%esp)
	movl	$4000, 4(%esp)
	movl	$753664, (%esp)
	movl	%eax, %ecx
	call	__ZN17SegmentDescriptorC1EPcicc
	subl	$16, %esp
	movl	$4660, (%esp)
	call	__ZN4Util10insertMarkEi
	movl	__ZN17SegmentDescriptor11TYPE_U_DATAE, %eax
	movsbl	%al, %edx
	movl	__ZN17SegmentDescriptor5DPL_0E, %eax
	movsbl	%al, %ecx
	leal	-23(%ebp), %eax
	movl	%ecx, 12(%esp)
	movl	%edx, 8(%esp)
	movl	$0, 4(%esp)
	movl	$0, (%esp)
	movl	%eax, %ecx
	call	__ZN17SegmentDescriptorC1EPcicc
	subl	$16, %esp
	movl	-23(%ebp), %eax
	movl	%eax, -86(%ebp)
	movl	-19(%ebp), %eax
	movl	%eax, -82(%ebp)
	movl	-15(%ebp), %eax
	movl	%eax, -78(%ebp)
	movzwl	-11(%ebp), %eax
	movw	%ax, -74(%ebp)
	movzbl	-9(%ebp), %eax
	movb	%al, -72(%ebp)
	leal	-23(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN17SegmentDescriptorD1Ev
	leal	-86(%ebp), %eax
	movl	$1424, 4(%esp)
	movl	$0, (%esp)
	movl	%eax, %ecx
	call	__ZN17SegmentDescriptor13writeToMemoryEiPc
	subl	$8, %esp
	leal	-146(%ebp), %eax
	movl	$1432, 4(%esp)
	movl	$0, (%esp)
	movl	%eax, %ecx
	call	__ZN17SegmentDescriptor13writeToMemoryEiPc
	subl	$8, %esp
	leal	-101(%ebp), %eax
	movl	$1440, 4(%esp)
	movl	$0, (%esp)
	movl	%eax, %ecx
	call	__ZN17SegmentDescriptor13writeToMemoryEiPc
	subl	$8, %esp
	leal	-116(%ebp), %eax
	movl	$1448, 4(%esp)
	movl	$0, (%esp)
	movl	%eax, %ecx
	call	__ZN17SegmentDescriptor13writeToMemoryEiPc
	subl	$8, %esp
	leal	-131(%ebp), %eax
	movl	$1456, 4(%esp)
	movl	$0, (%esp)
	movl	%eax, %ecx
	call	__ZN17SegmentDescriptor13writeToMemoryEiPc
	subl	$8, %esp
	leal	-146(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN17SegmentDescriptorD1Ev
	leal	-131(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN17SegmentDescriptorD1Ev
	leal	-116(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN17SegmentDescriptorD1Ev
	leal	-101(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN17SegmentDescriptorD1Ev
	leal	-86(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN17SegmentDescriptorD1Ev
	leal	-63(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN17SegmentDescriptorD1Ev
	leal	-40(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN17SegmentDescriptorD1Ev
	leal	-25(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN8PMLoaderD1Ev
	leal	-24(%ebp), %eax
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
	.def	__ZN8PMLoaderC1Ev;	.scl	2;	.type	32;	.endef
	.def	__ZN8PMLoader7memcopyEiiiii;	.scl	2;	.type	32;	.endef
	.def	__ZN8PMLoader11readSectorsEiiiiiii;	.scl	2;	.type	32;	.endef
	.def	__ZN17SegmentDescriptorC1EPcicc;	.scl	2;	.type	32;	.endef
	.def	__ZN4Util10insertMarkEi;	.scl	2;	.type	32;	.endef
	.def	__ZN17SegmentDescriptor13writeToMemoryEiPc;	.scl	2;	.type	32;	.endef
	.def	__ZN17SegmentDescriptor10fromMemoryEPS_iPc;	.scl	2;	.type	32;	.endef
	.def	__ZN17SegmentDescriptor6equalsERS_;	.scl	2;	.type	32;	.endef
	.def	__ZN8PMLoader9enableA20Ev;	.scl	2;	.type	32;	.endef
	.def	__ZN8PMLoader7setidtrEsi;	.scl	2;	.type	32;	.endef
	.def	__ZN8PMLoader7setgdtrEsi;	.scl	2;	.type	32;	.endef
	.def	__ZN17SegmentDescriptorD1Ev;	.scl	2;	.type	32;	.endef
	.def	__ZN8PMLoaderD1Ev;	.scl	2;	.type	32;	.endef
	.def	__ZN4UtilD1Ev;	.scl	2;	.type	32;	.endef
