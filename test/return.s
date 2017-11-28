	.file	"return.cpp"
	.section	.text$_ZN1TC1Ec,"x"
	.linkonce discard
	.align 2
	.globl	__ZN1TC1Ec
	.def	__ZN1TC1Ec;	.scl	2;	.type	32;	.endef
__ZN1TC1Ec:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	%ecx, -4(%ebp)
	movl	8(%ebp), %eax
	movb	%al, -8(%ebp)
	movl	-4(%ebp), %eax
	movzbl	-8(%ebp), %edx
	movb	%dl, (%eax)
	nop
	leave
	ret	$4
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
	.section	.text$_ZN1T1hEi,"x"
	.linkonce discard
	.align 2
	.globl	__ZN1T1hEi
	.def	__ZN1T1hEi;	.scl	2;	.type	32;	.endef
__ZN1T1hEi:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$72, %esp
	movl	%ecx, -44(%ebp)
	leal	-18(%ebp), %eax
	movl	$2, (%esp)
	movl	%eax, %ecx
	call	__ZN1TC1Ec
	subl	$4, %esp
	leal	-28(%ebp), %eax
	movl	$34, (%esp)
	movl	%eax, %ecx
	call	__ZN1TC1Ec
	subl	$4, %esp
	leal	-28(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN1TD1Ev
	leal	-18(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN1TD1Ev
	nop
	movl	-44(%ebp), %eax
	leave
	ret	$8
	.section	.text$_ZN1T1kEv,"x"
	.linkonce discard
	.align 2
	.globl	__ZN1T1kEv
	.def	__ZN1T1kEv;	.scl	2;	.type	32;	.endef
__ZN1T1kEv:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$52, %esp
	movl	%ecx, -28(%ebp)
	leal	-18(%ebp), %eax
	movl	$1, (%esp)
	movl	%eax, %ecx
	call	__ZN1TC1Ec
	subl	$4, %esp
	movl	$0, %ebx
	leal	-18(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN1TD1Ev
	movl	%ebx, %eax
	movl	-4(%ebp), %ebx
	leave
	ret
	.text
	.globl	__Z4testv
	.def	__Z4testv;	.scl	2;	.type	32;	.endef
__Z4testv:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$56, %esp
	leal	-32(%ebp), %eax
	movl	$3, (%esp)
	movl	%eax, %ecx
	call	__ZN1TC1Ec
	subl	$4, %esp
/APP
 # 25 "return.cpp" 1
	mov $0x6,%ecx 
	
 # 0 "" 2
/NO_APP
	leal	-22(%ebp), %eax
	movl	$4, 4(%esp)
	leal	-32(%ebp), %edx
	movl	%edx, (%esp)
	movl	%eax, %ecx
	call	__ZN1T1hEi
	subl	$8, %esp
	leal	-22(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN1TD1Ev
	leal	-32(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN1T1kEv
	movl	%eax, -12(%ebp)
	leal	-32(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN1TD1Ev
	nop
	leave
	ret
	.ident	"GCC: (GNU) 5.4.0"
