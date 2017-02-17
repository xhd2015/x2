	.file	"init.cpp"
	.section	.text$_ZN1TC1Eii,"x"
	.linkonce discard
	.align 2
	.globl	__ZN1TC1Eii
	.def	__ZN1TC1Eii;	.scl	2;	.type	32;	.endef
__ZN1TC1Eii:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	%ecx, -4(%ebp)
	movl	-4(%ebp), %eax
	movl	4(%eax), %edx
	movl	12(%ebp), %eax
	addl	%eax, %edx
	movl	-4(%ebp), %eax
	movl	%edx, (%eax)
	movl	-4(%ebp), %eax
	movl	(%eax), %edx
	movl	8(%ebp), %eax
	addl	%eax, %edx
	movl	-4(%ebp), %eax
	movl	%edx, 4(%eax)
	nop
	leave
	ret	$8
	.section	.text$_ZN1TD1Ev,"x"
	.linkonce discard
	.align 2
	.globl	__ZN1TD1Ev
	.def	__ZN1TD1Ev;	.scl	2;	.type	32;	.endef
__ZN1TD1Ev:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	%ecx, -4(%ebp)
	nop
	leave
	ret
	.section	.text$_ZN2T2C1Ev,"x"
	.linkonce discard
	.align 2
	.globl	__ZN2T2C1Ev
	.def	__ZN2T2C1Ev;	.scl	2;	.type	32;	.endef
__ZN2T2C1Ev:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	%ecx, -12(%ebp)
	movl	-12(%ebp), %eax
	movl	$0, 4(%esp)
	movl	$1, (%esp)
	movl	%eax, %ecx
	call	__ZN1TC1Eii
	subl	$8, %esp
	movl	-12(%ebp), %eax
	movl	$0, 8(%eax)
	movl	-12(%ebp), %eax
	movl	$0, (%eax)
	nop
	leave
	ret
	.section	.text$_ZN2T2D1Ev,"x"
	.linkonce discard
	.align 2
	.globl	__ZN2T2D1Ev
	.def	__ZN2T2D1Ev;	.scl	2;	.type	32;	.endef
__ZN2T2D1Ev:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	%ecx, -12(%ebp)
	movl	-12(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN1TD1Ev
	nop
	leave
	ret
	.text
	.globl	__Z4testv
	.def	__Z4testv;	.scl	2;	.type	32;	.endef
__Z4testv:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$56, %esp
	leal	-24(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN2T2C1Ev
	movl	$0, -16(%ebp)
/APP
 # 35 "init.cpp" 1
	#t2end 
	
 # 0 "" 2
/NO_APP
	leal	-32(%ebp), %eax
	movl	$0, 4(%esp)
	movl	$0, (%esp)
	movl	%eax, %ecx
	call	__ZN1TC1Eii
	subl	$8, %esp
	movl	%eax, -12(%ebp)
	movl	$0, -12(%ebp)
	movl	$0, -12(%ebp)
	movl	__ZN1K1bE, %eax
	movl	%eax, -12(%ebp)
	movl	__ZN8PMLoader1aE, %eax
	movl	%eax, -12(%ebp)
	movl	__ZN8PMLoader6JMPSEGE, %eax
	movl	%eax, -12(%ebp)
	movl	__ZN8PMLoader10CODE_STARTE, %eax
	movl	%eax, -12(%ebp)
	movl	__ZN8PMLoader12rEAL_SECNUMSE, %eax
	movl	%eax, -12(%ebp)
	leal	-32(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN1TD1Ev
	leal	-24(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN2T2D1Ev
	nop
	leave
	ret
	.ident	"GCC: (GNU) 5.4.0"
