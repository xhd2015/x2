	.file	"protected_main.cpp"
/APP
	.code32 
	
	.text 
	movw $0b11000,%ax 
	movw %ax,%ds 
	mov  %ax,%es 
	mov %ax,%gs 
	mov %ax,%fs 
	mov $0b100000,%ax 
	movw %ax,%ss 
	mov  $512*4,%esp 
	call _protectedEntryHolder 
	DIE: 
	jmp DIE 
	
	.section .rdata,"dr"
LC0:
	.ascii "Entered Protected Mode.\12\0"
LC1:
	.ascii "tss0 written\12\0"
LC2:
	.ascii "Had ltr done.\12\0"
LC3:
	.ascii "int 0x24 by CPL0.\12\0"
LC4:
	.ascii "Changing CPL to 3.\12\0"
/NO_APP
	.text
	.globl	_protectedEntryHolder
	.def	_protectedEntryHolder;	.scl	2;	.type	32;	.endef
_protectedEntryHolder:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$356, %esp
	call	__ZN4Util3clrEv
	movl	__ZN4Util11MODE_COMMONE, %eax
	movl	%eax, 4(%esp)
	movl	$LC0, (%esp)
	call	__ZN4Util8printStrEPKci
	leal	-124(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN3TSSC1Ev
	leal	-124(%ebp), %eax
	leal	8(%eax), %ebx
	movl	$0, 8(%esp)
	movl	$0, 4(%esp)
	movl	$4, (%esp)
	call	__ZN4Util7makeSelEiii
	movw	%ax, (%ebx)
	leal	-124(%ebp), %eax
	addl	$4, %eax
	movl	$1532, (%eax)
	leal	-124(%ebp), %eax
	movl	$17408, 4(%esp)
	movl	$65536, (%esp)
	movl	%eax, %ecx
	call	__ZN3TSS13writeToMemoryEii
	subl	$8, %esp
	movl	__ZN4Util11MODE_COMMONE, %eax
	movl	%eax, 4(%esp)
	movl	$LC1, (%esp)
	call	__ZN4Util8printStrEPKci
	movl	__ZN17SegmentDescriptor17TYPE_S_TSS_32_AVLE, %eax
	movsbl	%al, %edx
	leal	-139(%ebp), %eax
	movl	$1, 24(%esp)
	movl	$0, 20(%esp)
	movl	$0, 16(%esp)
	movl	$0, 12(%esp)
	movl	%edx, 8(%esp)
	movl	$103, 4(%esp)
	movl	$17408, (%esp)
	movl	%eax, %ecx
	call	__ZN17SegmentDescriptorC1EPciccccc
	subl	$28, %esp
	leal	-139(%ebp), %eax
	movl	$40376, 4(%esp)
	movl	$65536, (%esp)
	movl	%eax, %ecx
	call	__ZN17SegmentDescriptor13writeToMemoryEiPc
	subl	$8, %esp
	movl	$0, 8(%esp)
	movl	$0, 4(%esp)
	movl	$5, (%esp)
	call	__ZN4Util7makeSelEiii
	cwtl
	movl	%eax, (%esp)
	call	__ZN4Util3ltrEi
	movl	__ZN4Util11MODE_COMMONE, %eax
	movl	%eax, 4(%esp)
	movl	$LC2, (%esp)
	call	__ZN4Util8printStrEPKci
	leal	-150(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN18SelectorDescriptorC1Ev
	movl	__ZN17SegmentDescriptor5DPL_3E, %ecx
	movl	__ZN18SelectorDescriptor8TYPE_INTE, %edx
	movl	$_intDefault, %ebx
	leal	-150(%ebp), %eax
	movl	$1, 20(%esp)
	movl	$1, 16(%esp)
	movl	%ecx, 12(%esp)
	movl	%edx, 8(%esp)
	movl	%ebx, 4(%esp)
	movl	$16, (%esp)
	movl	%eax, %ecx
	call	__ZN18SelectorDescriptor4initEiiiiii
	subl	$24, %esp
	movl	$0, -12(%ebp)
L3:
	movl	_intLen, %eax
	cmpl	%eax, -12(%ebp)
	je	L2
	movl	__ZN17SegmentDescriptor5DPL_3E, %ebx
	movl	__ZN18SelectorDescriptor8TYPE_INTE, %ecx
	movl	_intAddresses, %eax
	movl	-12(%ebp), %edx
	sall	$2, %edx
	addl	%edx, %eax
	movl	(%eax), %edx
	leal	-150(%ebp), %eax
	movl	$1, 20(%esp)
	movl	$1, 16(%esp)
	movl	%ebx, 12(%esp)
	movl	%ecx, 8(%esp)
	movl	%edx, 4(%esp)
	movl	$16, (%esp)
	movl	%eax, %ecx
	call	__ZN18SelectorDescriptor4initEiiiiii
	subl	$24, %esp
	movl	-12(%ebp), %eax
	addl	$4992, %eax
	leal	0(,%eax,8), %edx
	leal	-150(%ebp), %eax
	movl	%edx, 4(%esp)
	movl	$65536, (%esp)
	movl	%eax, %ecx
	call	__ZN18SelectorDescriptor13writeToMemoryEii
	subl	$8, %esp
	addl	$1, -12(%ebp)
	jmp	L3
L2:
	movl	$74565, (%esp)
	call	__ZN4Util10insertMarkEi
	movl	__ZN4Util11MODE_COMMONE, %eax
	movl	$65536, %ecx
	movl	$LC3, %ebx
	movl	%eax, %edx
/APP
 # 58 "protected_main.cpp" 1
	int $0x24
	
 # 0 "" 2
/NO_APP
	leal	-151(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN8IO_8259AC1Ev
	leal	-151(%ebp), %eax
	movl	$1, 12(%esp)
	movl	$0, 8(%esp)
	movl	$0, 4(%esp)
	movl	$0, (%esp)
	movl	%eax, %ecx
	call	__ZN8IO_8259A8sendICW1Eiiii
	subl	$16, %esp
	leal	-151(%ebp), %eax
	movl	$1, 12(%esp)
	movl	$0, 8(%esp)
	movl	$0, 4(%esp)
	movl	$1, (%esp)
	movl	%eax, %ecx
	call	__ZN8IO_8259A8sendICW1Eiiii
	subl	$16, %esp
	leal	-151(%ebp), %eax
	movl	$32, 4(%esp)
	movl	$0, (%esp)
	movl	%eax, %ecx
	call	__ZN8IO_8259A8sendICW2Eii
	subl	$8, %esp
	leal	-151(%ebp), %eax
	movl	$40, 4(%esp)
	movl	$1, (%esp)
	movl	%eax, %ecx
	call	__ZN8IO_8259A8sendICW2Eii
	subl	$8, %esp
	leal	-151(%ebp), %eax
	movl	$4, 4(%esp)
	movl	$0, (%esp)
	movl	%eax, %ecx
	call	__ZN8IO_8259A8sendICW3Eii
	subl	$8, %esp
	leal	-151(%ebp), %eax
	movl	$2, 4(%esp)
	movl	$1, (%esp)
	movl	%eax, %ecx
	call	__ZN8IO_8259A8sendICW3Eii
	subl	$8, %esp
	leal	-151(%ebp), %eax
	movl	$1, 16(%esp)
	movl	$0, 12(%esp)
	movl	$0, 8(%esp)
	movl	$0, 4(%esp)
	movl	$0, (%esp)
	movl	%eax, %ecx
	call	__ZN8IO_8259A8sendICW4Eiiiii
	subl	$20, %esp
	leal	-151(%ebp), %eax
	movl	$1, 16(%esp)
	movl	$0, 12(%esp)
	movl	$0, 8(%esp)
	movl	$0, 4(%esp)
	movl	$1, (%esp)
	movl	%eax, %ecx
	call	__ZN8IO_8259A8sendICW4Eiiiii
	subl	$20, %esp
	leal	-151(%ebp), %eax
	movl	$254, 4(%esp)
	movl	$0, (%esp)
	movl	%eax, %ecx
	call	__ZN8IO_8259A8sendOCW1Eii
	subl	$8, %esp
	leal	-151(%ebp), %eax
	movl	$255, 4(%esp)
	movl	$1, (%esp)
	movl	%eax, %ecx
	call	__ZN8IO_8259A8sendOCW1Eii
	subl	$8, %esp
	leal	-152(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN7IO_8253C1Ev
	leal	-152(%ebp), %eax
	movl	$1, 4(%esp)
	movl	$0, (%esp)
	movl	%eax, %ecx
	call	__ZN7IO_825312setTimeMicroEij
	subl	$8, %esp
	movl	__ZN17SegmentDescriptor22TYPE_U_CODE_CONFORMINGE, %eax
	movsbl	%al, %edx
	leal	-167(%ebp), %eax
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
	leal	-182(%ebp), %eax
	movl	$1, 24(%esp)
	movl	$1, 20(%esp)
	movl	$1, 16(%esp)
	movl	$3, 12(%esp)
	movl	%edx, 8(%esp)
	movl	$65535, 4(%esp)
	movl	$0, (%esp)
	movl	%eax, %ecx
	call	__ZN17SegmentDescriptorC1EPciccccc
	subl	$28, %esp
	movl	__ZN17SegmentDescriptor12TYPE_U_STACKE, %eax
	movsbl	%al, %edx
	leal	-197(%ebp), %eax
	movl	$1, 24(%esp)
	movl	$1, 20(%esp)
	movl	$1, 16(%esp)
	movl	$3, 12(%esp)
	movl	%edx, 8(%esp)
	movl	$2048, 4(%esp)
	movl	$0, (%esp)
	movl	%eax, %ecx
	call	__ZN17SegmentDescriptorC1EPciccccc
	subl	$28, %esp
	leal	-167(%ebp), %eax
	movl	$40384, 4(%esp)
	movl	$65536, (%esp)
	movl	%eax, %ecx
	call	__ZN17SegmentDescriptor13writeToMemoryEiPc
	subl	$8, %esp
	leal	-182(%ebp), %eax
	movl	$40392, 4(%esp)
	movl	$65536, (%esp)
	movl	%eax, %ecx
	call	__ZN17SegmentDescriptor13writeToMemoryEiPc
	subl	$8, %esp
	leal	-197(%ebp), %eax
	movl	$40400, 4(%esp)
	movl	$65536, (%esp)
	movl	%eax, %ecx
	call	__ZN17SegmentDescriptor13writeToMemoryEiPc
	subl	$8, %esp
	leal	-309(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN3TSSC1Ev
	leal	-309(%ebp), %eax
	leal	76(%eax), %ebx
	movl	$0, 8(%esp)
	movl	$3, 4(%esp)
	movl	$6, (%esp)
	call	__ZN4Util7makeSelEiii
	movw	%ax, (%ebx)
	leal	-309(%ebp), %eax
	addl	$32, %eax
	movl	$_forTss1, %edx
	movl	%edx, (%eax)
	leal	-309(%ebp), %eax
	leal	80(%eax), %ebx
	movl	$0, 8(%esp)
	movl	$3, 4(%esp)
	movl	$8, (%esp)
	call	__ZN4Util7makeSelEiii
	movw	%ax, (%ebx)
	leal	-309(%ebp), %eax
	addl	$56, %eax
	movl	$1020, (%eax)
	leal	-309(%ebp), %eax
	leal	8(%eax), %ebx
	movl	$0, 8(%esp)
	movl	$0, 4(%esp)
	movl	$4, (%esp)
	call	__ZN4Util7makeSelEiii
	movw	%ax, (%ebx)
	leal	-309(%ebp), %eax
	addl	$4, %eax
	movl	$508, (%eax)
	leal	-309(%ebp), %eax
	addl	$36, %eax
	movl	$514, (%eax)
	leal	-309(%ebp), %eax
	addl	$84, %eax
	movw	$59, (%eax)
	leal	-309(%ebp), %eax
	movl	$17512, 4(%esp)
	movl	$65536, (%esp)
	movl	%eax, %ecx
	call	__ZN3TSS13writeToMemoryEii
	subl	$8, %esp
	movl	__ZN17SegmentDescriptor17TYPE_S_TSS_32_AVLE, %eax
	movsbl	%al, %edx
	leal	-324(%ebp), %eax
	movl	$1, 24(%esp)
	movl	$0, 20(%esp)
	movl	$0, 16(%esp)
	movl	$0, 12(%esp)
	movl	%edx, 8(%esp)
	movl	$103, 4(%esp)
	movl	$17512, (%esp)
	movl	%eax, %ecx
	call	__ZN17SegmentDescriptorC1EPciccccc
	subl	$28, %esp
	leal	-324(%ebp), %eax
	movl	$40408, 4(%esp)
	movl	$65536, (%esp)
	movl	%eax, %ecx
	call	__ZN17SegmentDescriptor13writeToMemoryEiPc
	subl	$8, %esp
/APP
 # 102 "protected_main.cpp" 1
	sti 
	
 # 0 "" 2
/NO_APP
	movl	__ZN4Util11MODE_COMMONE, %eax
	movl	%eax, 4(%esp)
	movl	$LC4, (%esp)
	call	__ZN4Util8printStrEPKci
	call	__ZN4Util9getEflagsEv
	movl	$_afterCPL3, %edx
	movl	$67, 16(%esp)
	movl	$2044, 12(%esp)
	movl	%eax, 8(%esp)
	movl	$51, 4(%esp)
	movl	%edx, (%esp)
	call	__ZN4Util9changeCPLEiiiii
	leal	-324(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN17SegmentDescriptorD1Ev
	leal	-309(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN3TSSD1Ev
	leal	-197(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN17SegmentDescriptorD1Ev
	leal	-182(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN17SegmentDescriptorD1Ev
	leal	-167(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN17SegmentDescriptorD1Ev
	leal	-152(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN7IO_8253D1Ev
	leal	-151(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN8IO_8259AD1Ev
	leal	-150(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN18SelectorDescriptorD1Ev
	leal	-139(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN17SegmentDescriptorD1Ev
	leal	-124(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN3TSSD1Ev
	nop
	movl	-4(%ebp), %ebx
	leave
	ret
	.section .rdata,"dr"
LC5:
	.ascii "int 0x24 by CPL3.\12\0"
	.text
	.globl	_afterCPL3
	.def	_afterCPL3;	.scl	2;	.type	32;	.endef
_afterCPL3:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$52, %esp
/APP
 # 116 "protected_main.cpp" 1
	pushw $0x3b 
	popw %ds 
	
 # 0 "" 2
/NO_APP
	movl	__ZN4Util11MODE_COMMONE, %eax
	movl	$65536, %ecx
	movl	$LC5, %ebx
	movl	%eax, %edx
/APP
 # 117 "protected_main.cpp" 1
	int $0x24
	
 # 0 "" 2
/NO_APP
	movl	$349816, (%esp)
	call	__ZN4Util10insertMarkEi
	movl	__ZN4Util11MODE_COMMONE, %edx
	leal	-28(%ebp), %eax
	movl	$1, 12(%esp)
	movl	%edx, 8(%esp)
	movl	$40, 4(%esp)
	movl	$0, (%esp)
	movl	%eax, %ecx
	call	__ZN17SimpleCharRotatorC1Eiiii
	subl	$16, %esp
	leal	-28(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN17SimpleCharRotator3runEv
	leal	-28(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN17SimpleCharRotatorD1Ev
	nop
	movl	-4(%ebp), %ebx
	leave
	ret
	.globl	_forTss1
	.def	_forTss1;	.scl	2;	.type	32;	.endef
_forTss1:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$56, %esp
	movl	__ZN4Util11MODE_COMMONE, %edx
	movl	__ZN4Util10MODE_FL_ONE, %eax
	orl	%eax, %edx
	movl	__ZN4Util12MODE_BG_BLUEE, %eax
	orl	%eax, %edx
	leal	-28(%ebp), %eax
	movl	$1, 12(%esp)
	movl	%edx, 8(%esp)
	movl	$50, 4(%esp)
	movl	$0, (%esp)
	movl	%eax, %ecx
	call	__ZN17SimpleCharRotatorC1Eiiii
	subl	$16, %esp
	leal	-28(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN17SimpleCharRotator3runEv
	leal	-28(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN17SimpleCharRotatorD1Ev
	nop
	leave
	ret
/APP
	.section .stack 
	.org 512*4 
	
	.ident	"GCC: (GNU) 5.4.0"
	.def	__ZN4Util3clrEv;	.scl	2;	.type	32;	.endef
	.def	__ZN4Util8printStrEPKci;	.scl	2;	.type	32;	.endef
	.def	__ZN3TSSC1Ev;	.scl	2;	.type	32;	.endef
	.def	__ZN4Util7makeSelEiii;	.scl	2;	.type	32;	.endef
	.def	__ZN3TSS13writeToMemoryEii;	.scl	2;	.type	32;	.endef
	.def	__ZN17SegmentDescriptorC1EPciccccc;	.scl	2;	.type	32;	.endef
	.def	__ZN17SegmentDescriptor13writeToMemoryEiPc;	.scl	2;	.type	32;	.endef
	.def	__ZN4Util3ltrEi;	.scl	2;	.type	32;	.endef
	.def	__ZN18SelectorDescriptorC1Ev;	.scl	2;	.type	32;	.endef
	.def	_intDefault;	.scl	2;	.type	32;	.endef
	.def	__ZN18SelectorDescriptor4initEiiiiii;	.scl	2;	.type	32;	.endef
	.def	__ZN18SelectorDescriptor13writeToMemoryEii;	.scl	2;	.type	32;	.endef
	.def	__ZN4Util10insertMarkEi;	.scl	2;	.type	32;	.endef
	.def	__ZN8IO_8259AC1Ev;	.scl	2;	.type	32;	.endef
	.def	__ZN8IO_8259A8sendICW1Eiiii;	.scl	2;	.type	32;	.endef
	.def	__ZN8IO_8259A8sendICW2Eii;	.scl	2;	.type	32;	.endef
	.def	__ZN8IO_8259A8sendICW3Eii;	.scl	2;	.type	32;	.endef
	.def	__ZN8IO_8259A8sendICW4Eiiiii;	.scl	2;	.type	32;	.endef
	.def	__ZN8IO_8259A8sendOCW1Eii;	.scl	2;	.type	32;	.endef
	.def	__ZN7IO_8253C1Ev;	.scl	2;	.type	32;	.endef
	.def	__ZN7IO_825312setTimeMicroEij;	.scl	2;	.type	32;	.endef
	.def	__ZN4Util9getEflagsEv;	.scl	2;	.type	32;	.endef
	.def	__ZN4Util9changeCPLEiiiii;	.scl	2;	.type	32;	.endef
	.def	__ZN17SegmentDescriptorD1Ev;	.scl	2;	.type	32;	.endef
	.def	__ZN3TSSD1Ev;	.scl	2;	.type	32;	.endef
	.def	__ZN7IO_8253D1Ev;	.scl	2;	.type	32;	.endef
	.def	__ZN8IO_8259AD1Ev;	.scl	2;	.type	32;	.endef
	.def	__ZN18SelectorDescriptorD1Ev;	.scl	2;	.type	32;	.endef
	.def	__ZN17SimpleCharRotatorC1Eiiii;	.scl	2;	.type	32;	.endef
	.def	__ZN17SimpleCharRotator3runEv;	.scl	2;	.type	32;	.endef
	.def	__ZN17SimpleCharRotatorD1Ev;	.scl	2;	.type	32;	.endef
