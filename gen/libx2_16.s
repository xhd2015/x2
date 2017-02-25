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
	.globl	__ZN4Util10MODE_FL_ONE
	.section .rdata,"dr"
	.align 4
__ZN4Util10MODE_FL_ONE:
	.long	128
	.globl	__ZN4Util11MODE_FL_OFFE
	.align 4
__ZN4Util11MODE_FL_OFFE:
	.long	127
	.globl	__ZN4Util11MODE_BG_REDE
	.align 4
__ZN4Util11MODE_BG_REDE:
	.long	32
	.globl	__ZN4Util13MODE_BG_GREENE
	.align 4
__ZN4Util13MODE_BG_GREENE:
	.long	16
	.globl	__ZN4Util12MODE_BG_BLUEE
	.align 4
__ZN4Util12MODE_BG_BLUEE:
	.long	8
	.globl	__ZN4Util13MODE_BG_WHITEE
	.align 4
__ZN4Util13MODE_BG_WHITEE:
	.long	56
	.globl	__ZN4Util10MODE_BG_RGE
	.align 4
__ZN4Util10MODE_BG_RGE:
	.long	48
	.globl	__ZN4Util10MODE_BG_RBE
	.align 4
__ZN4Util10MODE_BG_RBE:
	.long	40
	.globl	__ZN4Util10MODE_BG_BGE
	.align 4
__ZN4Util10MODE_BG_BGE:
	.long	24
	.globl	__ZN4Util13MODE_BG_BLACKE
	.align 4
__ZN4Util13MODE_BG_BLACKE:
	.space 4
	.globl	__ZN4Util11MODE_FG_REDE
	.align 4
__ZN4Util11MODE_FG_REDE:
	.long	4
	.globl	__ZN4Util13MODE_FG_GREENE
	.align 4
__ZN4Util13MODE_FG_GREENE:
	.long	2
	.globl	__ZN4Util12MODE_FG_BLUEE
	.align 4
__ZN4Util12MODE_FG_BLUEE:
	.long	1
	.globl	__ZN4Util13MODE_FG_WHITEE
	.align 4
__ZN4Util13MODE_FG_WHITEE:
	.long	7
	.globl	__ZN4Util10MODE_FG_RGE
	.align 4
__ZN4Util10MODE_FG_RGE:
	.long	6
	.globl	__ZN4Util10MODE_FG_RBE
	.align 4
__ZN4Util10MODE_FG_RBE:
	.long	5
	.globl	__ZN4Util10MODE_FG_BGE
	.align 4
__ZN4Util10MODE_FG_BGE:
	.long	3
	.globl	__ZN4Util13MODE_FG_BLACKE
	.align 4
__ZN4Util13MODE_FG_BLACKE:
	.space 4
	.globl	__ZN4Util11MODE_COMMONE
	.align 4
__ZN4Util11MODE_COMMONE:
	.long	7
	.globl	__ZN4Util8SCREEN_XE
	.align 4
__ZN4Util8SCREEN_XE:
	.long	25
	.globl	__ZN4Util8SCREEN_YE
	.align 4
__ZN4Util8SCREEN_YE:
	.long	80
	.globl	__ZN4Util11SEG_CURRENTE
	.align 4
__ZN4Util11SEG_CURRENTE:
	.long	65536
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
	cmpb	$8, -28(%ebp)
	jne	L12
	movl	__ZN4Util1yE, %eax
	testl	%eax, %eax
	jle	L15
	movl	__ZN4Util1yE, %eax
	subl	$1, %eax
	movl	%eax, __ZN4Util1yE
	jmp	L15
L12:
	movl	__ZN4Util1yE, %eax
	cmpl	$80, %eax
	jne	L14
	call	__ZN4Util7newLineEv
L14:
	movl	__ZN4Util1xE, %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	sall	$4, %eax
	movl	%eax, %edx
	movl	__ZN4Util1yE, %eax
	addl	%edx, %eax
	addl	%eax, %eax
	movl	%eax, -12(%ebp)
	movl	__ZN4Util13videoSelectorE, %edx
	movzbl	-28(%ebp), %eax
	movl	-12(%ebp), %ebx
	movl	12(%ebp), %ecx
/APP
 # 105 "libx2.cpp" 1
	push %es
	mov %dx,%es
	movb %al,%es:(%bx) 
	inc %ebx 
	movb %cl,%es:(%bx) 
	pop %es 
	
 # 0 "" 2
/NO_APP
	movl	__ZN4Util1yE, %eax
	addl	$1, %eax
	movl	%eax, __ZN4Util1yE
	jmp	L8
L15:
	nop
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
 # 120 "libx2.cpp" 1
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
	je	L19
	movl	8(%ebp), %eax
/APP
 # 124 "libx2.cpp" 1
	mov %ds,%ebx
	movw %ax,%ds 
	
 # 0 "" 2
/NO_APP
	movl	%ebx, %eax
	movl	%eax, -8(%ebp)
L19:
	movl	12(%ebp), %edx
	movl	8(%ebp), %eax
	movl	%edx, %ebx
/APP
 # 131 "libx2.cpp" 1
	movl %ds:(%ebx),%eax 
	
 # 0 "" 2
/NO_APP
	movl	%eax, -12(%ebp)
	cmpl	$65536, 8(%ebp)
	je	L20
	movl	-8(%ebp), %eax
/APP
 # 132 "libx2.cpp" 1
	mov %ax,%ds 
	
 # 0 "" 2
/NO_APP
L20:
	movl	-12(%ebp), %eax
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
	subl	$16, %esp
	cmpl	$65536, 8(%ebp)
	je	L23
	movl	8(%ebp), %eax
/APP
 # 137 "libx2.cpp" 1
	mov %ds,%ebx
	movw %ax,%ds 
	
 # 0 "" 2
/NO_APP
	movl	%ebx, %eax
	movl	%eax, -8(%ebp)
L23:
/APP
 # 145 "libx2.cpp" 1
	movl 4+4*2(%ebp),%ebx 
	movb 4+4*3(%ebp),%al 
	movb %al,%ds:(%ebx) 
	
 # 0 "" 2
/NO_APP
	cmpl	$65536, 8(%ebp)
	je	L25
	movl	-8(%ebp), %eax
/APP
 # 146 "libx2.cpp" 1
	mov %ax,%ds 
	
 # 0 "" 2
/NO_APP
L25:
	nop
	addl	$16, %esp
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
	subl	$16, %esp
	cmpl	$65536, 8(%ebp)
	je	L27
	movl	8(%ebp), %eax
/APP
 # 150 "libx2.cpp" 1
	mov %ds,%ebx
	movw %ax,%ds 
	
 # 0 "" 2
/NO_APP
	movl	%ebx, %eax
	movl	%eax, -8(%ebp)
L27:
/APP
 # 158 "libx2.cpp" 1
	movl 4+4*2(%ebp),%ebx 
	movw 4+4*3(%ebp),%ax 
	movw %ax,%ds:(%ebx) 
	
 # 0 "" 2
/NO_APP
	cmpl	$65536, 8(%ebp)
	je	L29
	movl	-8(%ebp), %eax
/APP
 # 159 "libx2.cpp" 1
	mov %ax,%ds 
	
 # 0 "" 2
/NO_APP
L29:
	nop
	addl	$16, %esp
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
	subl	$16, %esp
	cmpl	$65536, 8(%ebp)
	je	L31
	movl	8(%ebp), %eax
/APP
 # 163 "libx2.cpp" 1
	mov %ds,%ebx
	movw %ax,%ds 
	
 # 0 "" 2
/NO_APP
	movl	%ebx, %eax
	movl	%eax, -8(%ebp)
L31:
/APP
 # 171 "libx2.cpp" 1
	movl 4+4*2(%ebp),%ebx 
	mov 4+4*3(%ebp),%eax 
	mov %eax,%ds:(%ebx) 
	
 # 0 "" 2
/NO_APP
	cmpl	$65536, 8(%ebp)
	je	L33
	movl	-8(%ebp), %eax
/APP
 # 172 "libx2.cpp" 1
	mov %ax,%ds 
	
 # 0 "" 2
/NO_APP
L33:
	nop
	addl	$16, %esp
	popl	%ebx
	popl	%ebp
	ret
	.align 2
	.globl	__ZN4Util7memcopyEiiiii
	.def	__ZN4Util7memcopyEiiiii;	.scl	2;	.type	32;	.endef
__ZN4Util7memcopyEiiiii:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$16, %esp
/APP
 # 177 "libx2.cpp" 1
	mov %es,%ax 
	
 # 0 "" 2
/NO_APP
	movl	%eax, -12(%ebp)
	cmpl	$65536, 16(%ebp)
	jne	L35
/APP
 # 177 "libx2.cpp" 1
	push %ds 
	pop %es 
	
 # 0 "" 2
/NO_APP
	jmp	L36
L35:
	movl	16(%ebp), %eax
/APP
 # 177 "libx2.cpp" 1
	movw %ax,%es 
	
 # 0 "" 2
/NO_APP
L36:
	cmpl	$65536, 8(%ebp)
	je	L37
	movl	8(%ebp), %eax
/APP
 # 178 "libx2.cpp" 1
	mov %ds,%ebx
	movw %ax,%ds 
	
 # 0 "" 2
/NO_APP
	movl	%ebx, %eax
	movl	%eax, -8(%ebp)
L37:
/APP
 # 190 "libx2.cpp" 1
	push %esi 
	push %edi 
	mov 4+4*2(%ebp),%esi 
	mov 4+4*4(%ebp),%edi 
	mov 4+4*5(%ebp),%ecx 
	cld 
	rep movsb 
	pop %edi 
	pop %esi 
	
 # 0 "" 2
/NO_APP
	cmpl	$65536, 8(%ebp)
	je	L38
	movl	-8(%ebp), %eax
/APP
 # 192 "libx2.cpp" 1
	mov %ax,%ds 
	
 # 0 "" 2
/NO_APP
L38:
	movl	-12(%ebp), %eax
/APP
 # 193 "libx2.cpp" 1
	mov %ax,%es 
	
 # 0 "" 2
/NO_APP
	nop
	addl	$16, %esp
	popl	%ebx
	popl	%ebp
	ret
	.align 2
	.globl	__ZN4Util3clrEv
	.def	__ZN4Util3clrEv;	.scl	2;	.type	32;	.endef
__ZN4Util3clrEv:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	$0, 4(%esp)
	movl	$0, (%esp)
	call	__ZN4Util9setCursorEii
	movl	$0, -12(%ebp)
L43:
	cmpl	$25, -12(%ebp)
	je	L40
	movl	$0, -16(%ebp)
L42:
	cmpl	$80, -16(%ebp)
	je	L41
	movl	$7, 4(%esp)
	movl	$32, (%esp)
	call	__ZN4Util9printCharEci
	addl	$1, -16(%ebp)
	jmp	L42
L41:
	addl	$1, -12(%ebp)
	jmp	L43
L40:
	movl	$0, 4(%esp)
	movl	$0, (%esp)
	call	__ZN4Util9setCursorEii
	nop
	leave
	ret
	.align 2
	.globl	__ZN4Util9setCursorEii
	.def	__ZN4Util9setCursorEii;	.scl	2;	.type	32;	.endef
__ZN4Util9setCursorEii:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %ecx
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
	movl	12(%ebp), %ecx
	movl	$1717986919, %edx
	movl	%ecx, %eax
	imull	%edx
	sarl	$5, %edx
	movl	%ecx, %eax
	sarl	$31, %eax
	subl	%eax, %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	sall	$4, %eax
	subl	%eax, %ecx
	movl	%ecx, %edx
	movl	%edx, __ZN4Util1yE
	nop
	popl	%ebp
	ret
	.align 2
	.globl	__ZN4Util14readSectorsCHSEiiiiiii
	.def	__ZN4Util14readSectorsCHSEiiiiiii;	.scl	2;	.type	32;	.endef
__ZN4Util14readSectorsCHSEiiiiiii:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
/APP
 # 685 "libx2.cpp" 1
	push %es
	mov 4+4*1(%ebp),%eax 
	movw %ax,%es
	movw 4+4*2(%ebp),%bx
	movb 4+4*3(%ebp),%dl 
	movb 4+4*5(%ebp),%dh 
	movw 4+4*4(%ebp),%cx 
	shl   $6,%cx 
	addb 4+4*6(%ebp),%cl 
	movb $0x02,%ah 
	movb 4+4*7(%ebp),%al 
	int $0x13 
	pop %es 
	xor %eax,%eax 
	jc error 
	mov $1,%eax 
	error:
	
 # 0 "" 2
/NO_APP
	movl	%eax, -4(%ebp)
	movl	-4(%ebp), %eax
	leave
	ret
	.align 2
	.globl	__ZN4Util11readSectorsEiiiii
	.def	__ZN4Util11readSectorsEiiiii;	.scl	2;	.type	32;	.endef
__ZN4Util11readSectorsEiiiii:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	pushl	%ebx
	subl	$28, %esp
	movl	20(%ebp), %ecx
	movl	$954437177, %edx
	movl	%ecx, %eax
	imull	%edx
	sarl	$2, %edx
	movl	%ecx, %eax
	sarl	$31, %eax
	subl	%eax, %edx
	movl	%edx, %eax
	sall	$3, %eax
	addl	%edx, %eax
	addl	%eax, %eax
	subl	%eax, %ecx
	movl	%ecx, %edx
	leal	1(%edx), %esi
	movl	20(%ebp), %ebx
	movl	$954437177, %edx
	movl	%ebx, %eax
	imull	%edx
	sarl	$3, %edx
	movl	%ebx, %eax
	sarl	$31, %eax
	movl	%edx, %ecx
	subl	%eax, %ecx
	movl	%ecx, %eax
	sall	$3, %eax
	addl	%ecx, %eax
	sall	$2, %eax
	subl	%eax, %ebx
	movl	%ebx, %ecx
	movl	$954437177, %edx
	movl	%ecx, %eax
	imull	%edx
	sarl	$2, %edx
	movl	%ecx, %eax
	sarl	$31, %eax
	movl	%edx, %ebx
	subl	%eax, %ebx
	movl	20(%ebp), %ecx
	movl	$954437177, %edx
	movl	%ecx, %eax
	imull	%edx
	sarl	$3, %edx
	movl	%ecx, %eax
	sarl	$31, %eax
	subl	%eax, %edx
	movl	24(%ebp), %eax
	movl	%eax, 24(%esp)
	movl	%esi, 20(%esp)
	movl	%ebx, 16(%esp)
	movl	%edx, 12(%esp)
	movl	16(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	__ZN4Util14readSectorsCHSEiiiiiii
	addl	$28, %esp
	popl	%ebx
	popl	%esi
	popl	%ebp
	ret
	.ident	"GCC: (GNU) 5.4.0"
