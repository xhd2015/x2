	.file	"libx2.cpp"
/APP
	.code16gcc
/NO_APP
	.globl	__ZN4Util1xE
	.bss
	.align 4
__ZN4Util1xE:
	.space 4
	.globl	__ZN4Util1yE
	.align 4
__ZN4Util1yE:
	.space 4
	.globl	__ZN4Util13videoSelectorE
	.data
	.align 4
__ZN4Util13videoSelectorE:
	.long	47104
	.section .rdata,"dr"
LC0:
	.ascii ">>>Init\0"
	.text
	.align 2
	.globl	__ZN4UtilC2Ev
	.def	__ZN4UtilC2Ev;	.scl	2;	.type	32;	.endef
__ZN4UtilC2Ev:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	%ecx, -12(%ebp)
	movl	$7, 4(%esp)
	movl	$LC0, (%esp)
	call	__ZN4Util8printStrEPKci
	call	__ZN4Util7newLineEv
	nop
	leave
	ret
	.globl	__ZN4UtilC1Ev
	.def	__ZN4UtilC1Ev;	.scl	2;	.type	32;	.endef
	.set	__ZN4UtilC1Ev,__ZN4UtilC2Ev
	.section .rdata,"dr"
LC1:
	.ascii ">>>Destroy\0"
	.text
	.align 2
	.globl	__ZN4UtilD2Ev
	.def	__ZN4UtilD2Ev;	.scl	2;	.type	32;	.endef
__ZN4UtilD2Ev:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	%ecx, -12(%ebp)
	movl	$7, 4(%esp)
	movl	$LC1, (%esp)
	call	__ZN4Util8printStrEPKci
	call	__ZN4Util7newLineEv
	nop
	leave
	ret
	.globl	__ZN4UtilD1Ev
	.def	__ZN4UtilD1Ev;	.scl	2;	.type	32;	.endef
	.set	__ZN4UtilD1Ev,__ZN4UtilD2Ev
	.section .rdata,"dr"
LC2:
	.ascii ">>>test\0"
	.text
	.align 2
	.globl	__ZN4Util4testEv
	.def	__ZN4Util4testEv;	.scl	2;	.type	32;	.endef
__ZN4Util4testEv:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	%ecx, -12(%ebp)
	movl	$7, 4(%esp)
	movl	$LC2, (%esp)
	call	__ZN4Util8printStrEPKci
	call	__ZN4Util7newLineEv
	nop
	leave
	ret
	.align 2
	.globl	__ZN4Util8printStrEPKci
	.def	__ZN4Util8printStrEPKci;	.scl	2;	.type	32;	.endef
__ZN4Util8printStrEPKci:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
L6:
	movl	8(%ebp), %eax
	movzbl	(%eax), %eax
	testb	%al, %al
	je	L7
	movl	8(%ebp), %eax
	leal	1(%eax), %edx
	movl	%edx, 8(%ebp)
	movzbl	(%eax), %eax
	movsbl	%al, %eax
	movl	12(%ebp), %edx
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
	call	__ZN4Util9printCharEci
	jmp	L6
L7:
	nop
	leave
	ret
	.align 2
	.globl	__ZN4Util9printCharEci
	.def	__ZN4Util9printCharEci;	.scl	2;	.type	32;	.endef
__ZN4Util9printCharEci:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$36, %esp
	movl	8(%ebp), %eax
	movb	%al, -28(%ebp)
	cmpb	$10, -28(%ebp)
	jne	L9
	call	__ZN4Util7newLineEv
	jmp	L8
L9:
	cmpb	$13, -28(%ebp)
	jne	L11
	movl	$0, __ZN4Util1yE
	jmp	L8
L11:
	movl	__ZN4Util1yE, %eax
	cmpl	$160, %eax
	jne	L12
	call	__ZN4Util7newLineEv
L12:
	movl	__ZN4Util1xE, %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	sall	$5, %eax
	movl	%eax, %edx
	movl	__ZN4Util1yE, %eax
	addl	%edx, %eax
	movl	%eax, -12(%ebp)
	movl	__ZN4Util13videoSelectorE, %edx
	movzbl	-28(%ebp), %eax
	movl	-12(%ebp), %ebx
	movl	12(%ebp), %ecx
/APP
 # 61 "libx2.cpp" 1
	push %es
	mov %dx,%es
	movb %al,%es:(%bx) 
	inc %ebx 
	movb %cl,%es:(%bx) 
	pop %es 
	
 # 0 "" 2
/NO_APP
	movl	__ZN4Util1yE, %eax
	addl	$2, %eax
	movl	%eax, __ZN4Util1yE
L8:
	addl	$36, %esp
	popl	%ebx
	popl	%ebp
	ret
	.align 2
	.globl	__ZN4Util7newLineEv
	.def	__ZN4Util7newLineEv;	.scl	2;	.type	32;	.endef
__ZN4Util7newLineEv:
	pushl	%ebp
	movl	%esp, %ebp
	movl	$0, __ZN4Util1yE
	movl	__ZN4Util1xE, %eax
	leal	1(%eax), %ecx
	movl	$1374389535, %edx
	movl	%ecx, %eax
	imull	%edx
	sarl	$3, %edx
	movl	%ecx, %eax
	sarl	$31, %eax
	subl	%eax, %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	leal	0(,%eax,4), %edx
	addl	%edx, %eax
	subl	%eax, %ecx
	movl	%ecx, %edx
	movl	%edx, __ZN4Util1xE
	nop
	popl	%ebp
	ret
	.align 2
	.globl	__ZN4Util10insertMarkEi
	.def	__ZN4Util10insertMarkEi;	.scl	2;	.type	32;	.endef
__ZN4Util10insertMarkEi:
	pushl	%ebp
	movl	%esp, %ebp
/APP
 # 75 "libx2.cpp" 1
	nop 
	
 # 0 "" 2
/NO_APP
	nop
	popl	%ebp
	ret
	.align 2
	.globl	__ZN4Util3getEii
	.def	__ZN4Util3getEii;	.scl	2;	.type	32;	.endef
__ZN4Util3getEii:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$16, %esp
	cmpl	$65536, 8(%ebp)
	jne	L16
/APP
 # 87 "libx2.cpp" 1
	xor %eax,%eax 
	movw %ds,%ax 
	
 # 0 "" 2
/NO_APP
	movl	%eax, 8(%ebp)
L16:
	movl	12(%ebp), %edx
	movl	8(%ebp), %eax
	movl	%edx, %ebx
/APP
 # 98 "libx2.cpp" 1
	push %es 
	movw %ax,%es 
	movl %es:(%ebx),%eax 
	pop %es
	
 # 0 "" 2
/NO_APP
	movl	%eax, -8(%ebp)
	movl	-8(%ebp), %eax
	addl	$16, %esp
	popl	%ebx
	popl	%ebp
	ret
	.align 2
	.globl	__ZN4Util4setbEiii
	.def	__ZN4Util4setbEiii;	.scl	2;	.type	32;	.endef
__ZN4Util4setbEiii:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	cmpl	$65536, 8(%ebp)
	jne	L19
/APP
 # 111 "libx2.cpp" 1
	xor %eax,%eax 
	movw %ds,%ax 
	
 # 0 "" 2
/NO_APP
	movl	%eax, 8(%ebp)
L19:
/APP
 # 124 "libx2.cpp" 1
	push %es 
	movl 4+4*1(%ebp),%eax 
	movw %ax,%es 
	movl 4+4*2(%ebp),%ebx 
	movb 4+4*3(%ebp),%al 
	movb %al,%es:(%ebx) 
	pop %es 
	
 # 0 "" 2
/NO_APP
	nop
	popl	%ebx
	popl	%ebp
	ret
	.align 2
	.globl	__ZN4Util4setwEiii
	.def	__ZN4Util4setwEiii;	.scl	2;	.type	32;	.endef
__ZN4Util4setwEiii:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	cmpl	$65536, 8(%ebp)
	jne	L21
/APP
 # 136 "libx2.cpp" 1
	xor %eax,%eax 
	movw %ds,%ax 
	
 # 0 "" 2
/NO_APP
	movl	%eax, 8(%ebp)
L21:
/APP
 # 149 "libx2.cpp" 1
	push %es 
	movl 4+4*1(%ebp),%eax 
	movw %ax,%es 
	movl 4+4*2(%ebp),%ebx 
	movw 4+4*3(%ebp),%ax 
	movw %ax,%es:(%ebx) 
	pop %es 
	
 # 0 "" 2
/NO_APP
	nop
	popl	%ebx
	popl	%ebp
	ret
	.align 2
	.globl	__ZN4Util4setlEiii
	.def	__ZN4Util4setlEiii;	.scl	2;	.type	32;	.endef
__ZN4Util4setlEiii:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	cmpl	$65536, 8(%ebp)
	jne	L23
/APP
 # 161 "libx2.cpp" 1
	xor %eax,%eax 
	movw %ds,%ax 
	
 # 0 "" 2
/NO_APP
	movl	%eax, 8(%ebp)
L23:
/APP
 # 174 "libx2.cpp" 1
	push %es 
	movl 4+4*1(%ebp),%eax 
	movw %ax,%es 
	movl 4+4*2(%ebp),%ebx 
	mov 4+4*3(%ebp),%eax 
	mov %eax,%es:(%ebx) 
	pop %es 
	
 # 0 "" 2
/NO_APP
	nop
	popl	%ebx
	popl	%ebp
	ret
	.ident	"GCC: (GNU) 5.4.0"
