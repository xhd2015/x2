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
	.ascii "Running Test.\12\0"
LC2:
	.ascii "tss0 written\12\0"
LC3:
	.ascii "Had ltr done.\12\0"
LC4:
	.ascii "int 0x24 by CPL0.\12\0"
LC5:
	.ascii "Changing CPL to 3.\12\0"
/NO_APP
	.text
	.globl	_protectedEntryHolder
	.def	_protectedEntryHolder;	.scl	2;	.type	32;	.endef
_protectedEntryHolder:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$388, %esp
	call	__ZN4Util3clrEv
	movl	__ZN4Util11MODE_COMMONE, %edx
	leal	-40(%ebp), %eax
	movl	%edx, 16(%esp)
	movl	$20, 12(%esp)
	movl	$6, 8(%esp)
	movl	$30, 4(%esp)
	movl	$3, (%esp)
	movl	%eax, %ecx
	call	__ZN7PrinterC1Ejjjji
	subl	$20, %esp
	leal	-40(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN7Printer3clrEv
	leal	-40(%ebp), %eax
	movl	$LC0, (%esp)
	movl	%eax, %ecx
	call	__ZN7Printer5putszEPc
	subl	$4, %esp
	leal	-40(%ebp), %eax
	movl	$LC1, (%esp)
	movl	%eax, %ecx
	call	__ZN7Printer5putszEPc
	subl	$4, %esp
	leal	-41(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN4TestC1Ev
	leal	-41(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN4Test3runEv
	leal	-153(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN3TSSC1Ev
	leal	-153(%ebp), %eax
	leal	8(%eax), %ebx
	movl	$0, 8(%esp)
	movl	$0, 4(%esp)
	movl	$4, (%esp)
	call	__ZN4Util7makeSelEiii
	movw	%ax, (%ebx)
	leal	-153(%ebp), %eax
	addl	$4, %eax
	movl	$1532, (%eax)
	movl	__ZN8PMLoader14TSS_AREA_STARTE, %ecx
	movl	__ZN4Util11SEG_CURRENTE, %edx
	leal	-153(%ebp), %eax
	movl	%ecx, 4(%esp)
	movl	%edx, (%esp)
	movl	%eax, %ecx
	call	__ZN3TSS13writeToMemoryEii
	subl	$8, %esp
	leal	-40(%ebp), %eax
	movl	$LC2, (%esp)
	movl	%eax, %ecx
	call	__ZN7Printer5putszEPc
	subl	$4, %esp
	movl	__ZN17SegmentDescriptor17TYPE_S_TSS_32_AVLE, %eax
	movsbl	%al, %edx
	movl	__ZN8PMLoader12TSS_MIN_SIZEE, %eax
	leal	-1(%eax), %ecx
	movl	__ZN8PMLoader14TSS_AREA_STARTE, %eax
	movl	%eax, %ebx
	leal	-168(%ebp), %eax
	movl	$1, 24(%esp)
	movl	$0, 20(%esp)
	movl	$0, 16(%esp)
	movl	$0, 12(%esp)
	movl	%edx, 8(%esp)
	movl	%ecx, 4(%esp)
	movl	%ebx, (%esp)
	movl	%eax, %ecx
	call	__ZN17SegmentDescriptorC1EPciccccc
	subl	$28, %esp
	movl	__ZN8PMLoader9GDT_STARTE, %eax
	addl	$40, %eax
	movl	%eax, %ecx
	movl	__ZN4Util11SEG_CURRENTE, %edx
	leal	-168(%ebp), %eax
	movl	%ecx, 4(%esp)
	movl	%edx, (%esp)
	movl	%eax, %ecx
	call	__ZN17SegmentDescriptor13writeToMemoryEiPc
	subl	$8, %esp
	movl	$0, 8(%esp)
	movl	$0, 4(%esp)
	movl	$5, (%esp)
	call	__ZN4Util7makeSelEiii
	cwtl
	movl	%eax, -360(%ebp)
/APP
 # 268 "libx2.h" 1
	ltr -360(%ebp) 
	
 # 0 "" 2
/NO_APP
	leal	-40(%ebp), %eax
	movl	$LC3, (%esp)
	movl	%eax, %ecx
	call	__ZN7Printer5putszEPc
	subl	$4, %esp
	leal	-179(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN18SelectorDescriptorC1Ev
	movl	__ZN17SegmentDescriptor5DPL_3E, %ecx
	movl	__ZN18SelectorDescriptor8TYPE_INTE, %edx
	movl	$_intDefault, %ebx
	leal	-179(%ebp), %eax
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
	leal	-179(%ebp), %eax
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
	leal	0(,%eax,8), %edx
	movl	__ZN8PMLoader9IDT_STARTE, %eax
	leal	(%edx,%eax), %ecx
	movl	__ZN4Util11SEG_CURRENTE, %edx
	leal	-179(%ebp), %eax
	movl	%ecx, 4(%esp)
	movl	%edx, (%esp)
	movl	%eax, %ecx
	call	__ZN18SelectorDescriptor13writeToMemoryEii
	subl	$8, %esp
	addl	$1, -12(%ebp)
	jmp	L3
L2:
	movl	__ZN17SegmentDescriptor5DPL_3E, %ecx
	movl	__ZN18SelectorDescriptor8TYPE_INTE, %edx
	movl	$_int0x20, %ebx
	leal	-179(%ebp), %eax
	movl	$1, 20(%esp)
	movl	$1, 16(%esp)
	movl	%ecx, 12(%esp)
	movl	%edx, 8(%esp)
	movl	%ebx, 4(%esp)
	movl	$16, (%esp)
	movl	%eax, %ecx
	call	__ZN18SelectorDescriptor4initEiiiiii
	subl	$24, %esp
	movl	__ZN8PMLoader9IDT_STARTE, %eax
	leal	256(%eax), %ecx
	movl	__ZN4Util11SEG_CURRENTE, %edx
	leal	-179(%ebp), %eax
	movl	%ecx, 4(%esp)
	movl	%edx, (%esp)
	movl	%eax, %ecx
	call	__ZN18SelectorDescriptor13writeToMemoryEii
	subl	$8, %esp
	movl	__ZN17SegmentDescriptor5DPL_3E, %ecx
	movl	__ZN18SelectorDescriptor8TYPE_INTE, %edx
	movl	$_int0x21, %ebx
	leal	-179(%ebp), %eax
	movl	$1, 20(%esp)
	movl	$1, 16(%esp)
	movl	%ecx, 12(%esp)
	movl	%edx, 8(%esp)
	movl	%ebx, 4(%esp)
	movl	$16, (%esp)
	movl	%eax, %ecx
	call	__ZN18SelectorDescriptor4initEiiiiii
	subl	$24, %esp
	movl	__ZN8PMLoader9IDT_STARTE, %eax
	leal	264(%eax), %ecx
	movl	__ZN4Util11SEG_CURRENTE, %edx
	leal	-179(%ebp), %eax
	movl	%ecx, 4(%esp)
	movl	%edx, (%esp)
	movl	%eax, %ecx
	call	__ZN18SelectorDescriptor13writeToMemoryEii
	subl	$8, %esp
	movl	$74565, (%esp)
	call	__ZN4Util10insertMarkEi
	movl	__ZN4Util11SEG_CURRENTE, %eax
	movl	__ZN4Util11MODE_COMMONE, %edx
	movl	$LC4, %ebx
	movl	%eax, %ecx
/APP
 # 73 "protected_main.cpp" 1
	int $0x24
	
 # 0 "" 2
/NO_APP
	leal	-180(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN8IO_8259AC1Ev
	leal	-180(%ebp), %eax
	movl	$1, 12(%esp)
	movl	$0, 8(%esp)
	movl	$0, 4(%esp)
	movl	$0, (%esp)
	movl	%eax, %ecx
	call	__ZN8IO_8259A8sendICW1Eiiii
	subl	$16, %esp
	leal	-180(%ebp), %eax
	movl	$1, 12(%esp)
	movl	$0, 8(%esp)
	movl	$0, 4(%esp)
	movl	$1, (%esp)
	movl	%eax, %ecx
	call	__ZN8IO_8259A8sendICW1Eiiii
	subl	$16, %esp
	leal	-180(%ebp), %eax
	movl	$32, 4(%esp)
	movl	$0, (%esp)
	movl	%eax, %ecx
	call	__ZN8IO_8259A8sendICW2Eii
	subl	$8, %esp
	leal	-180(%ebp), %eax
	movl	$40, 4(%esp)
	movl	$1, (%esp)
	movl	%eax, %ecx
	call	__ZN8IO_8259A8sendICW2Eii
	subl	$8, %esp
	leal	-180(%ebp), %eax
	movl	$4, 4(%esp)
	movl	$0, (%esp)
	movl	%eax, %ecx
	call	__ZN8IO_8259A8sendICW3Eii
	subl	$8, %esp
	leal	-180(%ebp), %eax
	movl	$2, 4(%esp)
	movl	$1, (%esp)
	movl	%eax, %ecx
	call	__ZN8IO_8259A8sendICW3Eii
	subl	$8, %esp
	leal	-180(%ebp), %eax
	movl	$1, 16(%esp)
	movl	$0, 12(%esp)
	movl	$0, 8(%esp)
	movl	$0, 4(%esp)
	movl	$0, (%esp)
	movl	%eax, %ecx
	call	__ZN8IO_8259A8sendICW4Eiiiii
	subl	$20, %esp
	leal	-180(%ebp), %eax
	movl	$1, 16(%esp)
	movl	$0, 12(%esp)
	movl	$0, 8(%esp)
	movl	$0, 4(%esp)
	movl	$1, (%esp)
	movl	%eax, %ecx
	call	__ZN8IO_8259A8sendICW4Eiiiii
	subl	$20, %esp
	leal	-180(%ebp), %eax
	movl	$252, 4(%esp)
	movl	$0, (%esp)
	movl	%eax, %ecx
	call	__ZN8IO_8259A8sendOCW1Eii
	subl	$8, %esp
	leal	-180(%ebp), %eax
	movl	$255, 4(%esp)
	movl	$1, (%esp)
	movl	%eax, %ecx
	call	__ZN8IO_8259A8sendOCW1Eii
	subl	$8, %esp
	leal	-181(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN7IO_8253C1Ev
	leal	-181(%ebp), %eax
	movl	$1, 4(%esp)
	movl	$0, (%esp)
	movl	%eax, %ecx
	call	__ZN7IO_825312setTimeMicroEij
	subl	$8, %esp
	movl	__ZN17SegmentDescriptor22TYPE_U_CODE_CONFORMINGE, %eax
	movsbl	%al, %edx
	leal	-196(%ebp), %eax
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
	leal	-211(%ebp), %eax
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
	leal	-226(%ebp), %eax
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
	movl	__ZN8PMLoader9GDT_STARTE, %eax
	addl	$48, %eax
	movl	%eax, %ecx
	movl	__ZN4Util11SEG_CURRENTE, %edx
	leal	-196(%ebp), %eax
	movl	%ecx, 4(%esp)
	movl	%edx, (%esp)
	movl	%eax, %ecx
	call	__ZN17SegmentDescriptor13writeToMemoryEiPc
	subl	$8, %esp
	movl	__ZN8PMLoader9GDT_STARTE, %eax
	addl	$56, %eax
	movl	%eax, %ecx
	movl	__ZN4Util11SEG_CURRENTE, %edx
	leal	-211(%ebp), %eax
	movl	%ecx, 4(%esp)
	movl	%edx, (%esp)
	movl	%eax, %ecx
	call	__ZN17SegmentDescriptor13writeToMemoryEiPc
	subl	$8, %esp
	movl	__ZN8PMLoader9GDT_STARTE, %eax
	addl	$64, %eax
	movl	%eax, %ecx
	movl	__ZN4Util11SEG_CURRENTE, %edx
	leal	-226(%ebp), %eax
	movl	%ecx, 4(%esp)
	movl	%edx, (%esp)
	movl	%eax, %ecx
	call	__ZN17SegmentDescriptor13writeToMemoryEiPc
	subl	$8, %esp
	leal	-338(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN3TSSC1Ev
	leal	-338(%ebp), %eax
	leal	76(%eax), %ebx
	movl	$0, 8(%esp)
	movl	$3, 4(%esp)
	movl	$6, (%esp)
	call	__ZN4Util7makeSelEiii
	movw	%ax, (%ebx)
	leal	-338(%ebp), %eax
	addl	$32, %eax
	movl	$_forTss1, %edx
	movl	%edx, (%eax)
	leal	-338(%ebp), %eax
	leal	80(%eax), %ebx
	movl	$0, 8(%esp)
	movl	$3, 4(%esp)
	movl	$8, (%esp)
	call	__ZN4Util7makeSelEiii
	movw	%ax, (%ebx)
	leal	-338(%ebp), %eax
	addl	$56, %eax
	movl	$1020, (%eax)
	leal	-338(%ebp), %eax
	leal	8(%eax), %ebx
	movl	$0, 8(%esp)
	movl	$0, 4(%esp)
	movl	$4, (%esp)
	call	__ZN4Util7makeSelEiii
	movw	%ax, (%ebx)
	leal	-338(%ebp), %eax
	addl	$4, %eax
	movl	$508, (%eax)
	leal	-338(%ebp), %eax
	addl	$36, %eax
	movl	$514, (%eax)
	leal	-338(%ebp), %eax
	addl	$84, %eax
	movw	$59, (%eax)
	movl	__ZN8PMLoader14TSS_AREA_STARTE, %edx
	movl	__ZN8PMLoader12TSS_MIN_SIZEE, %eax
	leal	(%edx,%eax), %ecx
	movl	__ZN4Util11SEG_CURRENTE, %edx
	leal	-338(%ebp), %eax
	movl	%ecx, 4(%esp)
	movl	%edx, (%esp)
	movl	%eax, %ecx
	call	__ZN3TSS13writeToMemoryEii
	subl	$8, %esp
	movl	__ZN17SegmentDescriptor17TYPE_S_TSS_32_AVLE, %eax
	movsbl	%al, %edx
	movl	__ZN8PMLoader12TSS_MIN_SIZEE, %eax
	leal	-1(%eax), %ecx
	movl	__ZN8PMLoader14TSS_AREA_STARTE, %ebx
	movl	__ZN8PMLoader12TSS_MIN_SIZEE, %eax
	addl	%ebx, %eax
	movl	%eax, %ebx
	leal	-353(%ebp), %eax
	movl	$1, 24(%esp)
	movl	$0, 20(%esp)
	movl	$0, 16(%esp)
	movl	$0, 12(%esp)
	movl	%edx, 8(%esp)
	movl	%ecx, 4(%esp)
	movl	%ebx, (%esp)
	movl	%eax, %ecx
	call	__ZN17SegmentDescriptorC1EPciccccc
	subl	$28, %esp
	movl	__ZN8PMLoader9GDT_STARTE, %eax
	addl	$72, %eax
	movl	%eax, %ecx
	movl	__ZN4Util11SEG_CURRENTE, %edx
	leal	-353(%ebp), %eax
	movl	%ecx, 4(%esp)
	movl	%edx, (%esp)
	movl	%eax, %ecx
	call	__ZN17SegmentDescriptor13writeToMemoryEiPc
	subl	$8, %esp
/APP
 # 276 "libx2.h" 1
	sti 
	
 # 0 "" 2
/NO_APP
	leal	-40(%ebp), %eax
	movl	$LC5, (%esp)
	movl	%eax, %ecx
	call	__ZN7Printer5putszEPc
	subl	$4, %esp
	call	__ZN4Util9getEflagsEv
	movl	$_afterCPL3, %edx
	movl	$67, 16(%esp)
	movl	$2044, 12(%esp)
	movl	%eax, 8(%esp)
	movl	$51, 4(%esp)
	movl	%edx, (%esp)
	call	__ZN4Util9changeCPLEiiiii
	leal	-353(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN17SegmentDescriptorD1Ev
	leal	-338(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN3TSSD1Ev
	leal	-226(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN17SegmentDescriptorD1Ev
	leal	-211(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN17SegmentDescriptorD1Ev
	leal	-196(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN17SegmentDescriptorD1Ev
	leal	-181(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN7IO_8253D1Ev
	leal	-180(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN8IO_8259AD1Ev
	leal	-179(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN18SelectorDescriptorD1Ev
	leal	-168(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN17SegmentDescriptorD1Ev
	leal	-153(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN3TSSD1Ev
	leal	-41(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN4TestD1Ev
	leal	-40(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN7PrinterD1Ev
	nop
	movl	-4(%ebp), %ebx
	leave
	ret
	.section .rdata,"dr"
LC6:
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
 # 131 "protected_main.cpp" 1
	pushw $0x3b 
	popw %ds 
	
 # 0 "" 2
/NO_APP
	movl	__ZN4Util11SEG_CURRENTE, %eax
	movl	__ZN4Util11MODE_COMMONE, %edx
	movl	$LC6, %ebx
	movl	%eax, %ecx
/APP
 # 132 "protected_main.cpp" 1
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
	.section .free 
	. = . + 512*
	.ident	"GCC: (GNU) 5.4.0"
	.def	__ZN4Util3clrEv;	.scl	2;	.type	32;	.endef
	.def	__ZN7PrinterC1Ejjjji;	.scl	2;	.type	32;	.endef
	.def	__ZN7Printer3clrEv;	.scl	2;	.type	32;	.endef
	.def	__ZN7Printer5putszEPc;	.scl	2;	.type	32;	.endef
	.def	__ZN4TestC1Ev;	.scl	2;	.type	32;	.endef
	.def	__ZN4Test3runEv;	.scl	2;	.type	32;	.endef
	.def	__ZN3TSSC1Ev;	.scl	2;	.type	32;	.endef
	.def	__ZN4Util7makeSelEiii;	.scl	2;	.type	32;	.endef
	.def	__ZN3TSS13writeToMemoryEii;	.scl	2;	.type	32;	.endef
	.def	__ZN17SegmentDescriptorC1EPciccccc;	.scl	2;	.type	32;	.endef
	.def	__ZN17SegmentDescriptor13writeToMemoryEiPc;	.scl	2;	.type	32;	.endef
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
	.def	__ZN4TestD1Ev;	.scl	2;	.type	32;	.endef
	.def	__ZN7PrinterD1Ev;	.scl	2;	.type	32;	.endef
	.def	__ZN17SimpleCharRotatorC1Eiiii;	.scl	2;	.type	32;	.endef
	.def	__ZN17SimpleCharRotator3runEv;	.scl	2;	.type	32;	.endef
	.def	__ZN17SimpleCharRotatorD1Ev;	.scl	2;	.type	32;	.endef
