	.file	"macro.cpp"
	.section	.text$_ZN4UtilC1Ev,"x"
	.linkonce discard
	.align 2
	.globl	__ZN4UtilC1Ev
	.def	__ZN4UtilC1Ev;	.scl	2;	.type	32;	.endef
__ZN4UtilC1Ev:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	%ecx, -4(%ebp)
	nop
	leave
	ret
	.section	.text$_ZN4UtilD1Ev,"x"
	.linkonce discard
	.align 2
	.globl	__ZN4UtilD1Ev
	.def	__ZN4UtilD1Ev;	.scl	2;	.type	32;	.endef
__ZN4UtilD1Ev:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	%ecx, -4(%ebp)
	nop
	leave
	ret
	.text
	.globl	__Z4testv
	.def	__Z4testv;	.scl	2;	.type	32;	.endef
__Z4testv:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	leal	-22(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN4UtilC1Ev
	leal	-21(%ebp), %eax
	movl	%eax, -12(%ebp)
/APP
 # 54 "macro.cpp" 1
	nop 
	nop
	nop
	
 # 0 "" 2
/NO_APP
	movl	-12(%ebp), %eax
	movl	%eax, -20(%ebp)
	leal	-21(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN4UtilD1Ev
/APP
 # 60 "macro.cpp" 1
	nop 
	nop
	nop
	nop
	
 # 0 "" 2
/NO_APP
	leal	-22(%ebp), %eax
	movl	%eax, -16(%ebp)
	leal	-22(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN4UtilD1Ev
	nop
	leave
	ret
	.ident	"GCC: (GNU) 5.4.0"
