	.file	"interrupts.cpp"
/APP
	.code32 
	
	.global _INT_24
	_INT_24:
	
/NO_APP
	.text
	.globl	_int0x24
	.def	_int0x24;	.scl	2;	.type	32;	.endef
_int0x24:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$36, %esp
	movl	%edx, %eax
	movl	%ecx, -12(%ebp)
	movl	%ebx, -16(%ebp)
	movl	%eax, -20(%ebp)
	movl	-12(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZN4Util8enter_dsEi
	movl	-16(%ebp), %eax
	movl	-20(%ebp), %edx
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
	call	__ZN4Util8printStrEPKci
	movl	-12(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZN4Util8leave_dsEi
/APP
 # 38 "interrupts.cpp" 1
	leave 
	iret 
	
 # 0 "" 2
/NO_APP
	nop
	addl	$36, %esp
	popl	%ebx
	popl	%ebp
	ret
	.ident	"GCC: (GNU) 5.4.0"
	.def	__ZN4Util8enter_dsEi;	.scl	2;	.type	32;	.endef
	.def	__ZN4Util8printStrEPKci;	.scl	2;	.type	32;	.endef
	.def	__ZN4Util8leave_dsEi;	.scl	2;	.type	32;	.endef
