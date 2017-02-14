	.file	"libx2.cpp"
/APP
	.code32 
	
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
	.globl	__ZN4Util13videoSelectorE
	.data
	.align 4
__ZN4Util13videoSelectorE:
	.long	8
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
 # 100 "libx2.cpp" 1
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
 # 115 "libx2.cpp" 1
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
 # 119 "libx2.cpp" 1
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
 # 126 "libx2.cpp" 1
	movl %ds:(%ebx),%eax 
	
 # 0 "" 2
/NO_APP
	movl	%eax, -12(%ebp)
	cmpl	$65536, 8(%ebp)
	je	L20
	movl	-8(%ebp), %eax
/APP
 # 127 "libx2.cpp" 1
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
 # 132 "libx2.cpp" 1
	mov %ds,%ebx
	movw %ax,%ds 
	
 # 0 "" 2
/NO_APP
	movl	%ebx, %eax
	movl	%eax, -8(%ebp)
L23:
/APP
 # 140 "libx2.cpp" 1
	movl 4+4*2(%ebp),%ebx 
	movb 4+4*3(%ebp),%al 
	movb %al,%ds:(%ebx) 
	
 # 0 "" 2
/NO_APP
	cmpl	$65536, 8(%ebp)
	je	L25
	movl	-8(%ebp), %eax
/APP
 # 141 "libx2.cpp" 1
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
 # 145 "libx2.cpp" 1
	mov %ds,%ebx
	movw %ax,%ds 
	
 # 0 "" 2
/NO_APP
	movl	%ebx, %eax
	movl	%eax, -8(%ebp)
L27:
/APP
 # 153 "libx2.cpp" 1
	movl 4+4*2(%ebp),%ebx 
	movw 4+4*3(%ebp),%ax 
	movw %ax,%ds:(%ebx) 
	
 # 0 "" 2
/NO_APP
	cmpl	$65536, 8(%ebp)
	je	L29
	movl	-8(%ebp), %eax
/APP
 # 154 "libx2.cpp" 1
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
 # 158 "libx2.cpp" 1
	mov %ds,%ebx
	movw %ax,%ds 
	
 # 0 "" 2
/NO_APP
	movl	%ebx, %eax
	movl	%eax, -8(%ebp)
L31:
/APP
 # 166 "libx2.cpp" 1
	movl 4+4*2(%ebp),%ebx 
	mov 4+4*3(%ebp),%eax 
	mov %eax,%ds:(%ebx) 
	
 # 0 "" 2
/NO_APP
	cmpl	$65536, 8(%ebp)
	je	L33
	movl	-8(%ebp), %eax
/APP
 # 167 "libx2.cpp" 1
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
 # 172 "libx2.cpp" 1
	mov %es,%ax 
	
 # 0 "" 2
/NO_APP
	movl	%eax, -12(%ebp)
	cmpl	$65536, 16(%ebp)
	jne	L35
/APP
 # 172 "libx2.cpp" 1
	push %ds 
	pop %es 
	
 # 0 "" 2
/NO_APP
	jmp	L36
L35:
	movl	16(%ebp), %eax
/APP
 # 172 "libx2.cpp" 1
	movw %ax,%es 
	
 # 0 "" 2
/NO_APP
L36:
	cmpl	$65536, 8(%ebp)
	je	L37
	movl	8(%ebp), %eax
/APP
 # 173 "libx2.cpp" 1
	mov %ds,%ebx
	movw %ax,%ds 
	
 # 0 "" 2
/NO_APP
	movl	%ebx, %eax
	movl	%eax, -8(%ebp)
L37:
/APP
 # 185 "libx2.cpp" 1
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
 # 187 "libx2.cpp" 1
	mov %ax,%ds 
	
 # 0 "" 2
/NO_APP
L38:
	movl	-12(%ebp), %eax
/APP
 # 188 "libx2.cpp" 1
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
	.globl	__ZN4Util3ltrEi
	.def	__ZN4Util3ltrEi;	.scl	2;	.type	32;	.endef
__ZN4Util3ltrEi:
	pushl	%ebp
	movl	%esp, %ebp
/APP
 # 209 "libx2.cpp" 1
	ltr 4+4*1(%ebp) 
	
 # 0 "" 2
/NO_APP
	nop
	popl	%ebp
	ret
	.align 2
	.globl	__ZN4Util7makeSelEiii
	.def	__ZN4Util7makeSelEiii;	.scl	2;	.type	32;	.endef
__ZN4Util7makeSelEiii:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %eax
	sall	$3, %eax
	movl	%eax, %edx
	movl	16(%ebp), %eax
	andl	$1, %eax
	sall	$2, %eax
	orl	%eax, %edx
	movl	12(%ebp), %eax
	andl	$3, %eax
	orl	%edx, %eax
	popl	%ebp
	ret
	.align 2
	.globl	__ZN4Util6getCPLEv
	.def	__ZN4Util6getCPLEv;	.scl	2;	.type	32;	.endef
__ZN4Util6getCPLEv:
	pushl	%ebp
	movl	%esp, %ebp
/APP
 # 224 "libx2.cpp" 1
	mov %cs,%ax 
	and $0b11,%al 
	
 # 0 "" 2
/NO_APP
	nop
	popl	%ebp
	ret
	.align 2
	.globl	__ZN4Util6getDPLEi
	.def	__ZN4Util6getDPLEi;	.scl	2;	.type	32;	.endef
__ZN4Util6getDPLEi:
	pushl	%ebp
	movl	%esp, %ebp
/APP
 # 231 "libx2.cpp" 1
	movw 4+4*1(%ebp),%ax 
	and $0b11,%al 
	
 # 0 "" 2
/NO_APP
	nop
	popl	%ebp
	ret
	.align 2
	.globl	__ZN4Util9changeCPLEiiiii
	.def	__ZN4Util9changeCPLEiiiii;	.scl	2;	.type	32;	.endef
__ZN4Util9changeCPLEiiiii:
	pushl	%ebp
	movl	%esp, %ebp
/APP
 # 238 "libx2.cpp" 1
	add $4*2,%esp 
	iret 
	
 # 0 "" 2
/NO_APP
	nop
	popl	%ebp
	ret
	.align 2
	.globl	__ZN4Util9getEflagsEv
	.def	__ZN4Util9getEflagsEv;	.scl	2;	.type	32;	.endef
__ZN4Util9getEflagsEv:
	pushl	%ebp
	movl	%esp, %ebp
/APP
 # 245 "libx2.cpp" 1
	pushfl 
	popl %eax 
	
 # 0 "" 2
/NO_APP
	nop
	popl	%ebp
	ret
	.align 2
	.globl	__ZN4Util4outbEii
	.def	__ZN4Util4outbEii;	.scl	2;	.type	32;	.endef
__ZN4Util4outbEii:
	pushl	%ebp
	movl	%esp, %ebp
	movl	12(%ebp), %eax
	movl	8(%ebp), %edx
/APP
 # 254 "libx2.cpp" 1
	out %al,%dx 
	
 # 0 "" 2
/NO_APP
	nop
	popl	%ebp
	ret
	.globl	__ZN17SimpleCharRotator12rotateShapesE
	.section .rdata,"dr"
	.align 4
__ZN17SimpleCharRotator12rotateShapesE:
	.byte	95
	.byte	8
	.byte	0
	.byte	92
	.byte	8
	.byte	0
	.byte	124
	.byte	8
	.byte	0
	.byte	47
	.byte	8
	.byte	0
	.text
	.align 2
	.globl	__ZN17SimpleCharRotatorC2Eiiii
	.def	__ZN17SimpleCharRotatorC2Eiiii;	.scl	2;	.type	32;	.endef
__ZN17SimpleCharRotatorC2Eiiii:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	%ecx, -4(%ebp)
	movl	-4(%ebp), %eax
	movl	8(%ebp), %edx
	movl	%edx, (%eax)
	movl	-4(%ebp), %eax
	movl	12(%ebp), %edx
	movl	%edx, 4(%eax)
	movl	-4(%ebp), %eax
	movl	16(%ebp), %edx
	movl	%edx, 8(%eax)
	movl	-4(%ebp), %eax
	movl	$0, 12(%eax)
	movl	-4(%ebp), %eax
	movl	20(%ebp), %edx
	movl	%edx, 16(%eax)
	nop
	leave
	ret	$16
	.globl	__ZN17SimpleCharRotatorC1Eiiii
	.def	__ZN17SimpleCharRotatorC1Eiiii;	.scl	2;	.type	32;	.endef
	.set	__ZN17SimpleCharRotatorC1Eiiii,__ZN17SimpleCharRotatorC2Eiiii
	.align 2
	.globl	__ZN17SimpleCharRotatorD2Ev
	.def	__ZN17SimpleCharRotatorD2Ev;	.scl	2;	.type	32;	.endef
__ZN17SimpleCharRotatorD2Ev:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	%ecx, -4(%ebp)
	nop
	leave
	ret
	.globl	__ZN17SimpleCharRotatorD1Ev
	.def	__ZN17SimpleCharRotatorD1Ev;	.scl	2;	.type	32;	.endef
	.set	__ZN17SimpleCharRotatorD1Ev,__ZN17SimpleCharRotatorD2Ev
	.align 2
	.globl	__ZN17SimpleCharRotator11setPositionEii
	.def	__ZN17SimpleCharRotator11setPositionEii;	.scl	2;	.type	32;	.endef
__ZN17SimpleCharRotator11setPositionEii:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	%ecx, -4(%ebp)
	movl	-4(%ebp), %eax
	movl	8(%ebp), %edx
	movl	%edx, (%eax)
	movl	-4(%ebp), %eax
	movl	12(%ebp), %edx
	movl	%edx, 4(%eax)
	nop
	leave
	ret	$8
	.align 2
	.globl	__ZN17SimpleCharRotator7setAttrEi
	.def	__ZN17SimpleCharRotator7setAttrEi;	.scl	2;	.type	32;	.endef
__ZN17SimpleCharRotator7setAttrEi:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	%ecx, -4(%ebp)
	movl	-4(%ebp), %eax
	movl	8(%ebp), %edx
	movl	%edx, 8(%eax)
	nop
	leave
	ret	$4
	.align 2
	.globl	__ZN17SimpleCharRotator3runEv
	.def	__ZN17SimpleCharRotator3runEv;	.scl	2;	.type	32;	.endef
__ZN17SimpleCharRotator3runEv:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$12, %esp
	movl	%ecx, -8(%ebp)
L58:
	movl	-8(%ebp), %eax
	movl	4(%eax), %edx
	movl	-8(%ebp), %eax
	movl	(%eax), %eax
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
	call	__ZN4Util9setCursorEii
	movl	$21857, (%esp)
	call	__ZN4Util10insertMarkEi
	movl	-8(%ebp), %eax
	movl	12(%eax), %eax
	leal	__ZN17SimpleCharRotator12rotateShapesE(%eax), %ebx
	movl	-8(%ebp), %eax
	movl	8(%eax), %eax
	movl	$65536, %ecx
	movl	%eax, %edx
/APP
 # 282 "libx2.cpp" 1
	int $0x24
	
 # 0 "" 2
/NO_APP
	movl	-8(%ebp), %eax
	movl	12(%eax), %edx
	movl	-8(%ebp), %eax
	movl	16(%eax), %eax
	imull	%edx, %eax
	addl	$3, %eax
	movl	$12, %ecx
	movl	$0, %edx
	divl	%ecx
	movl	%edx, %eax
	movl	%eax, %edx
	movl	-8(%ebp), %eax
	movl	%edx, 12(%eax)
	jmp	L58
	.globl	__ZN7Printer12SCREEN_MAX_XE
	.section .rdata,"dr"
	.align 4
__ZN7Printer12SCREEN_MAX_XE:
	.long	25
	.globl	__ZN7Printer12SCREEN_MAX_YE
	.align 4
__ZN7Printer12SCREEN_MAX_YE:
	.long	80
	.text
	.align 2
	.globl	__ZN7PrinterC2Eiiiii
	.def	__ZN7PrinterC2Eiiiii;	.scl	2;	.type	32;	.endef
__ZN7PrinterC2Eiiiii:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	%ecx, -4(%ebp)
	cmpl	$25, 8(%ebp)
	jg	L60
	movl	8(%ebp), %eax
	jmp	L61
L60:
	movl	$24, %eax
L61:
	movl	-4(%ebp), %edx
	movl	%eax, (%edx)
	cmpl	$80, 12(%ebp)
	jg	L62
	movl	12(%ebp), %eax
	jmp	L63
L62:
	movl	$79, %eax
L63:
	movl	-4(%ebp), %edx
	movl	%eax, 4(%edx)
	movl	20(%ebp), %eax
	cmpl	$80, %eax
	jg	L64
	movl	20(%ebp), %eax
	jmp	L65
L64:
	movl	$80, %eax
L65:
	movl	-4(%ebp), %edx
	movl	%eax, 8(%edx)
	movl	16(%ebp), %eax
	cmpl	$25, %eax
	jg	L66
	movl	16(%ebp), %eax
	jmp	L67
L66:
	movl	$25, %eax
L67:
	movl	-4(%ebp), %edx
	movl	%eax, 12(%edx)
	movl	-4(%ebp), %eax
	movl	(%eax), %edx
	movl	-4(%ebp), %eax
	movl	%edx, 16(%eax)
	movl	-4(%ebp), %eax
	movl	4(%eax), %edx
	movl	-4(%ebp), %eax
	movl	%edx, 20(%eax)
	movl	-4(%ebp), %eax
	movl	24(%ebp), %edx
	movl	%edx, 24(%eax)
	nop
	leave
	ret	$20
	.globl	__ZN7PrinterC1Eiiiii
	.def	__ZN7PrinterC1Eiiiii;	.scl	2;	.type	32;	.endef
	.set	__ZN7PrinterC1Eiiiii,__ZN7PrinterC2Eiiiii
	.align 2
	.globl	__ZN7PrinterD2Ev
	.def	__ZN7PrinterD2Ev;	.scl	2;	.type	32;	.endef
__ZN7PrinterD2Ev:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	%ecx, -4(%ebp)
	nop
	leave
	ret
	.globl	__ZN7PrinterD1Ev
	.def	__ZN7PrinterD1Ev;	.scl	2;	.type	32;	.endef
	.set	__ZN7PrinterD1Ev,__ZN7PrinterD2Ev
	.align 2
	.globl	__ZN7Printer4moveEi
	.def	__ZN7Printer4moveEi;	.scl	2;	.type	32;	.endef
__ZN7Printer4moveEi:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	%ecx, -4(%ebp)
	movl	-4(%ebp), %eax
	movl	20(%eax), %edx
	movl	8(%ebp), %eax
	addl	%eax, %edx
	movl	-4(%ebp), %eax
	movl	%edx, 20(%eax)
L72:
	movl	-4(%ebp), %eax
	movl	20(%eax), %eax
	testl	%eax, %eax
	jns	L70
	movl	-4(%ebp), %eax
	movl	20(%eax), %edx
	movl	-4(%ebp), %eax
	movl	8(%eax), %eax
	addl	%eax, %edx
	movl	-4(%ebp), %eax
	movl	%edx, 20(%eax)
	movl	-4(%ebp), %eax
	movl	16(%eax), %eax
	leal	-1(%eax), %edx
	movl	-4(%ebp), %eax
	movl	%edx, 16(%eax)
	movl	-4(%ebp), %eax
	movl	16(%eax), %eax
	cmpl	$-1, %eax
	jne	L72
	movl	-4(%ebp), %eax
	movl	12(%eax), %edx
	movl	-4(%ebp), %eax
	movl	%edx, 16(%eax)
	jmp	L72
L70:
	movl	-4(%ebp), %eax
	movl	20(%eax), %edx
	movl	-4(%ebp), %eax
	movl	8(%eax), %eax
	cmpl	%eax, %edx
	jl	L75
	movl	-4(%ebp), %eax
	movl	20(%eax), %edx
	movl	-4(%ebp), %eax
	movl	8(%eax), %eax
	subl	%eax, %edx
	movl	-4(%ebp), %eax
	movl	%edx, 20(%eax)
	movl	-4(%ebp), %eax
	movl	16(%eax), %eax
	leal	1(%eax), %edx
	movl	-4(%ebp), %eax
	movl	%edx, 16(%eax)
	movl	-4(%ebp), %eax
	movl	16(%eax), %edx
	movl	-4(%ebp), %eax
	movl	12(%eax), %eax
	cmpl	%eax, %edx
	jne	L70
	movl	-4(%ebp), %eax
	movl	12(%eax), %eax
	leal	-1(%eax), %edx
	movl	-4(%ebp), %eax
	movl	%edx, 16(%eax)
	jmp	L70
L75:
	nop
	leave
	ret	$4
	.align 2
	.globl	__ZN7Printer4putcEi
	.def	__ZN7Printer4putcEi;	.scl	2;	.type	32;	.endef
__ZN7Printer4putcEi:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$56, %esp
	movl	%ecx, -28(%ebp)
	movl	__ZN4Util13videoSelectorE, %eax
	movl	%eax, -16(%ebp)
/APP
 # 193 "libx2.h" 1
	mov %es,%ax
	
 # 0 "" 2
/NO_APP
	movl	%eax, -20(%ebp)
	cmpl	$65536, -16(%ebp)
	jne	L77
/APP
 # 202 "libx2.h" 1
	mov %ds,%ax 
	mov %ax,%es 
	
 # 0 "" 2
/NO_APP
	jmp	L78
L77:
	movl	-16(%ebp), %eax
/APP
 # 209 "libx2.h" 1
	mov %ax,%es 
	
 # 0 "" 2
/NO_APP
L78:
	movl	-28(%ebp), %eax
	movl	8(%ebp), %edx
	movl	%edx, (%esp)
	movl	%eax, %ecx
	call	__ZN7Printer20specailCharProcessorEi
	subl	$4, %esp
	testl	%eax, %eax
	je	L80
	jmp	L81
L80:
	movl	-28(%ebp), %eax
	movl	8(%ebp), %edx
	movl	%edx, (%esp)
	movl	%eax, %ecx
	call	__ZN7Printer6__putcEi
	subl	$4, %esp
	movl	-28(%ebp), %eax
	movl	$1, (%esp)
	movl	%eax, %ecx
	call	__ZN7Printer4moveEi
	subl	$4, %esp
	nop
L81:
	movl	-20(%ebp), %eax
	movl	%eax, -12(%ebp)
	movl	-12(%ebp), %eax
/APP
 # 214 "libx2.h" 1
	mov %ax,%es 
	
 # 0 "" 2
/NO_APP
	nop
	leave
	ret	$4
	.align 2
	.globl	__ZN7Printer5putszEPc
	.def	__ZN7Printer5putszEPc;	.scl	2;	.type	32;	.endef
__ZN7Printer5putszEPc:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$72, %esp
	movl	%ecx, -44(%ebp)
	movl	8(%ebp), %eax
	movl	%eax, -12(%ebp)
	movl	__ZN4Util13videoSelectorE, %eax
	movl	%eax, -24(%ebp)
/APP
 # 193 "libx2.h" 1
	mov %es,%ax
	
 # 0 "" 2
/NO_APP
	movl	%eax, -28(%ebp)
	cmpl	$65536, -24(%ebp)
	jne	L83
/APP
 # 202 "libx2.h" 1
	mov %ds,%ax 
	mov %ax,%es 
	
 # 0 "" 2
/NO_APP
	jmp	L84
L83:
	movl	-24(%ebp), %eax
/APP
 # 209 "libx2.h" 1
	mov %ax,%es 
	
 # 0 "" 2
/NO_APP
L84:
	movl	-12(%ebp), %eax
	movzbl	(%eax), %eax
	movsbl	%al, %edx
	movl	-44(%ebp), %eax
	movl	%edx, (%esp)
	movl	%eax, %ecx
	call	__ZN7Printer20specailCharProcessorEi
	subl	$4, %esp
	movl	%eax, -20(%ebp)
	cmpl	$-1, -20(%ebp)
	setne	%al
	testb	%al, %al
	je	L85
	cmpl	$0, -20(%ebp)
	jne	L86
	movl	-12(%ebp), %eax
	movzbl	(%eax), %eax
	movsbl	%al, %edx
	movl	-44(%ebp), %eax
	movl	%edx, (%esp)
	movl	%eax, %ecx
	call	__ZN7Printer6__putcEi
	subl	$4, %esp
	movl	-44(%ebp), %eax
	movl	$1, (%esp)
	movl	%eax, %ecx
	call	__ZN7Printer4moveEi
	subl	$4, %esp
L86:
	addl	$1, -12(%ebp)
	jmp	L84
L85:
	movl	-28(%ebp), %eax
	movl	%eax, -16(%ebp)
	movl	-16(%ebp), %eax
/APP
 # 214 "libx2.h" 1
	mov %ax,%es 
	
 # 0 "" 2
/NO_APP
	nop
	leave
	ret	$4
	.align 2
	.globl	__ZN7Printer5putsnEPci
	.def	__ZN7Printer5putsnEPci;	.scl	2;	.type	32;	.endef
__ZN7Printer5putsnEPci:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$72, %esp
	movl	%ecx, -44(%ebp)
	movl	8(%ebp), %eax
	movl	%eax, -12(%ebp)
	movl	__ZN4Util13videoSelectorE, %eax
	movl	%eax, -28(%ebp)
/APP
 # 193 "libx2.h" 1
	mov %es,%ax
	
 # 0 "" 2
/NO_APP
	movl	%eax, -32(%ebp)
	cmpl	$65536, -28(%ebp)
	jne	L88
/APP
 # 202 "libx2.h" 1
	mov %ds,%ax 
	mov %ax,%es 
	
 # 0 "" 2
/NO_APP
	jmp	L89
L88:
	movl	-28(%ebp), %eax
/APP
 # 209 "libx2.h" 1
	mov %ax,%es 
	
 # 0 "" 2
/NO_APP
L89:
	movl	$0, -16(%ebp)
L94:
	movl	-12(%ebp), %eax
	movzbl	(%eax), %eax
	movsbl	%al, %edx
	movl	-44(%ebp), %eax
	movl	%edx, (%esp)
	movl	%eax, %ecx
	call	__ZN7Printer20specailCharProcessorEi
	subl	$4, %esp
	movl	%eax, -24(%ebp)
	cmpl	$-1, -24(%ebp)
	je	L90
	movl	-16(%ebp), %eax
	cmpl	12(%ebp), %eax
	je	L90
	movl	$1, %eax
	jmp	L91
L90:
	movl	$0, %eax
L91:
	testb	%al, %al
	je	L92
	cmpl	$0, -24(%ebp)
	jne	L93
	movl	-12(%ebp), %eax
	movzbl	(%eax), %eax
	movsbl	%al, %edx
	movl	-44(%ebp), %eax
	movl	%edx, (%esp)
	movl	%eax, %ecx
	call	__ZN7Printer6__putcEi
	subl	$4, %esp
	movl	-44(%ebp), %eax
	movl	$1, (%esp)
	movl	%eax, %ecx
	call	__ZN7Printer4moveEi
	subl	$4, %esp
L93:
	addl	$1, -12(%ebp)
	addl	$1, -16(%ebp)
	jmp	L94
L92:
	movl	-32(%ebp), %eax
	movl	%eax, -20(%ebp)
	movl	-20(%ebp), %eax
/APP
 # 214 "libx2.h" 1
	mov %ax,%es 
	
 # 0 "" 2
/NO_APP
	nop
	leave
	ret	$8
	.align 2
	.globl	__ZN7Printer6setPosEii
	.def	__ZN7Printer6setPosEii;	.scl	2;	.type	32;	.endef
__ZN7Printer6setPosEii:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	%ecx, -4(%ebp)
	movl	-4(%ebp), %eax
	movl	12(%eax), %ecx
	movl	8(%ebp), %eax
	cltd
	idivl	%ecx
	movl	-4(%ebp), %eax
	movl	%edx, 16(%eax)
	movl	-4(%ebp), %eax
	movl	8(%eax), %ecx
	movl	12(%ebp), %eax
	cltd
	idivl	%ecx
	movl	-4(%ebp), %eax
	movl	%edx, 20(%eax)
	nop
	leave
	ret	$8
	.align 2
	.globl	__ZN7Printer7setModeEi
	.def	__ZN7Printer7setModeEi;	.scl	2;	.type	32;	.endef
__ZN7Printer7setModeEi:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	%ecx, -4(%ebp)
	movl	-4(%ebp), %eax
	movl	8(%ebp), %edx
	movl	%edx, 24(%eax)
	nop
	leave
	ret	$4
	.align 2
	.globl	__ZN7Printer20specailCharProcessorEi
	.def	__ZN7Printer20specailCharProcessorEi;	.scl	2;	.type	32;	.endef
__ZN7Printer20specailCharProcessorEi:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	%ecx, -20(%ebp)
	movl	$1, -4(%ebp)
	cmpl	$13, 8(%ebp)
	ja	L98
	movl	8(%ebp), %eax
	sall	$2, %eax
	addl	$L100, %eax
	movl	(%eax), %eax
	jmp	*%eax
	.section .rdata,"dr"
	.align 4
L100:
	.long	L99
	.long	L98
	.long	L98
	.long	L98
	.long	L98
	.long	L98
	.long	L98
	.long	L98
	.long	L101
	.long	L102
	.long	L103
	.long	L98
	.long	L98
	.long	L104
	.text
L103:
	movl	-20(%ebp), %eax
	movl	16(%eax), %eax
	leal	1(%eax), %edx
	movl	-20(%ebp), %eax
	movl	12(%eax), %ecx
	movl	%edx, %eax
	cltd
	idivl	%ecx
	movl	-20(%ebp), %eax
	movl	%edx, 16(%eax)
	movl	-20(%ebp), %eax
	movl	$0, 20(%eax)
	jmp	L105
L104:
	movl	-20(%ebp), %eax
	movl	$0, 20(%eax)
	jmp	L105
L101:
	movl	-20(%ebp), %eax
	movl	$-1, (%esp)
	movl	%eax, %ecx
	call	__ZN7Printer4moveEi
	subl	$4, %esp
	jmp	L105
L102:
	movl	-20(%ebp), %eax
	movl	$4, (%esp)
	movl	%eax, %ecx
	call	__ZN7Printer4moveEi
	subl	$4, %esp
	jmp	L105
L99:
	movl	$-1, -4(%ebp)
	jmp	L105
L98:
	movl	$0, -4(%ebp)
	nop
L105:
	movl	-4(%ebp), %eax
	leave
	ret	$4
	.align 2
	.globl	__ZN7Printer6getPosEv
	.def	__ZN7Printer6getPosEv;	.scl	2;	.type	32;	.endef
__ZN7Printer6getPosEv:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	%ecx, -4(%ebp)
	movl	-4(%ebp), %eax
	movl	(%eax), %edx
	movl	-4(%ebp), %eax
	movl	16(%eax), %eax
	addl	%eax, %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	sall	$4, %eax
	movl	%eax, %ecx
	movl	-4(%ebp), %eax
	movl	4(%eax), %edx
	movl	-4(%ebp), %eax
	movl	20(%eax), %eax
	addl	%edx, %eax
	addl	%ecx, %eax
	addl	%eax, %eax
	leave
	ret
	.align 2
	.globl	__ZN7Printer6__putcEi
	.def	__ZN7Printer6__putcEi;	.scl	2;	.type	32;	.endef
__ZN7Printer6__putcEi:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	subl	$4, %esp
	movl	%ecx, -8(%ebp)
	movl	-8(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN7Printer6getPosEv
	movl	%eax, %ecx
	movl	-8(%ebp), %eax
	movl	24(%eax), %edx
	movl	8(%ebp), %eax
	movl	%ecx, %edi
/APP
 # 433 "libx2.cpp" 1
	mov %al,%es:(%edi) 
	mov %dl,%es:1(%edi) 
	
 # 0 "" 2
/NO_APP
	nop
	addl	$4, %esp
	popl	%edi
	popl	%ebp
	ret	$4
	.align 2
	.globl	__ZN7Printer3clrEv
	.def	__ZN7Printer3clrEv;	.scl	2;	.type	32;	.endef
__ZN7Printer3clrEv:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$56, %esp
	movl	%ecx, -28(%ebp)
	movl	-28(%ebp), %eax
	movl	$0, 4(%esp)
	movl	$0, (%esp)
	movl	%eax, %ecx
	call	__ZN7Printer6setPosEii
	subl	$8, %esp
	movl	$0, -12(%ebp)
L114:
	movl	-28(%ebp), %eax
	movl	12(%eax), %eax
	cmpl	-12(%ebp), %eax
	je	L111
	movl	$0, -16(%ebp)
L113:
	movl	-28(%ebp), %eax
	movl	8(%eax), %eax
	cmpl	-16(%ebp), %eax
	je	L112
	movl	-28(%ebp), %eax
	movl	$32, (%esp)
	movl	%eax, %ecx
	call	__ZN7Printer4putcEi
	subl	$4, %esp
	addl	$1, -16(%ebp)
	jmp	L113
L112:
	addl	$1, -12(%ebp)
	jmp	L114
L111:
	movl	-28(%ebp), %eax
	movl	$0, 4(%esp)
	movl	$0, (%esp)
	movl	%eax, %ecx
	call	__ZN7Printer6setPosEii
	subl	$8, %esp
	nop
	leave
	ret
	.ident	"GCC: (GNU) 5.4.0"
