	.file	"IOProgramer.cpp"
/APP
	.code32 
	
/NO_APP
	.globl	__ZN8IO_8259A5PORTSE
	.section .rdata,"dr"
	.align 4
__ZN8IO_8259A5PORTSE:
	.long	32
	.long	160
	.long	33
	.long	161
	.text
	.align 2
	.globl	__ZN8IO_8259AC2Ev
	.def	__ZN8IO_8259AC2Ev;	.scl	2;	.type	32;	.endef
__ZN8IO_8259AC2Ev:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	%ecx, -4(%ebp)
	nop
	leave
	ret
	.globl	__ZN8IO_8259AC1Ev
	.def	__ZN8IO_8259AC1Ev;	.scl	2;	.type	32;	.endef
	.set	__ZN8IO_8259AC1Ev,__ZN8IO_8259AC2Ev
	.align 2
	.globl	__ZN8IO_8259AD2Ev
	.def	__ZN8IO_8259AD2Ev;	.scl	2;	.type	32;	.endef
__ZN8IO_8259AD2Ev:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	%ecx, -4(%ebp)
	nop
	leave
	ret
	.globl	__ZN8IO_8259AD1Ev
	.def	__ZN8IO_8259AD1Ev;	.scl	2;	.type	32;	.endef
	.set	__ZN8IO_8259AD1Ev,__ZN8IO_8259AD2Ev
	.align 2
	.globl	__ZN8IO_8259A8sendICW1Eiiii
	.def	__ZN8IO_8259A8sendICW1Eiiii;	.scl	2;	.type	32;	.endef
__ZN8IO_8259A8sendICW1Eiiii:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	%ecx, -12(%ebp)
	movl	$125340049, (%esp)
	call	__ZN4Util10insertMarkEi
	movl	12(%ebp), %eax
	andl	$1, %eax
	sall	$3, %eax
	orl	$16, %eax
	movl	%eax, %edx
	movl	16(%ebp), %eax
	andl	$1, %eax
	addl	%eax, %eax
	orl	%eax, %edx
	movl	20(%ebp), %eax
	andl	$1, %eax
	movl	%edx, %ecx
	orl	%eax, %ecx
	movl	8(%ebp), %eax
	movl	__ZN8IO_8259A5PORTSE(,%eax,4), %edx
	movl	%ecx, %eax
/APP
 # 58 "IOProgramer.cpp" 1
	outb %al,%dx 
	
 # 0 "" 2
/NO_APP
	nop
	leave
	ret	$16
	.align 2
	.globl	__ZN8IO_8259A8sendICW2Eii
	.def	__ZN8IO_8259A8sendICW2Eii;	.scl	2;	.type	32;	.endef
__ZN8IO_8259A8sendICW2Eii:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	%ecx, -12(%ebp)
	movl	$125340050, (%esp)
	call	__ZN4Util10insertMarkEi
	movl	8(%ebp), %eax
	addl	$2, %eax
	movl	__ZN8IO_8259A5PORTSE(,%eax,4), %edx
	movl	12(%ebp), %eax
/APP
 # 70 "IOProgramer.cpp" 1
	outb %al,%dx 
	
 # 0 "" 2
/NO_APP
	nop
	leave
	ret	$8
	.align 2
	.globl	__ZN8IO_8259A8sendICW3Eii
	.def	__ZN8IO_8259A8sendICW3Eii;	.scl	2;	.type	32;	.endef
__ZN8IO_8259A8sendICW3Eii:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	%ecx, -12(%ebp)
	movl	$125340051, (%esp)
	call	__ZN4Util10insertMarkEi
	movl	8(%ebp), %eax
	addl	$2, %eax
	movl	__ZN8IO_8259A5PORTSE(,%eax,4), %edx
	movl	12(%ebp), %eax
/APP
 # 82 "IOProgramer.cpp" 1
	outb %al,%dx 
	
 # 0 "" 2
/NO_APP
	nop
	leave
	ret	$8
	.align 2
	.globl	__ZN8IO_8259A8sendICW4Eiiiii
	.def	__ZN8IO_8259A8sendICW4Eiiiii;	.scl	2;	.type	32;	.endef
__ZN8IO_8259A8sendICW4Eiiiii:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	%ecx, -12(%ebp)
	movl	$125340052, (%esp)
	call	__ZN4Util10insertMarkEi
	movl	12(%ebp), %eax
	andl	$1, %eax
	sall	$4, %eax
	movl	%eax, %edx
	movl	16(%ebp), %eax
	andl	$1, %eax
	sall	$3, %eax
	orl	%eax, %edx
	movl	20(%ebp), %eax
	andl	$1, %eax
	addl	%eax, %eax
	orl	%eax, %edx
	movl	24(%ebp), %eax
	andl	$1, %eax
	orl	%edx, %eax
	movl	8(%ebp), %edx
	addl	$2, %edx
	movl	__ZN8IO_8259A5PORTSE(,%edx,4), %edx
/APP
 # 97 "IOProgramer.cpp" 1
	outb %al,%dx 
	
 # 0 "" 2
/NO_APP
	nop
	leave
	ret	$20
	.align 2
	.globl	__ZN8IO_8259A8sendOCW1Eii
	.def	__ZN8IO_8259A8sendOCW1Eii;	.scl	2;	.type	32;	.endef
__ZN8IO_8259A8sendOCW1Eii:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	%ecx, -4(%ebp)
	movl	8(%ebp), %eax
	addl	$2, %eax
	movl	__ZN8IO_8259A5PORTSE(,%eax,4), %edx
	movl	12(%ebp), %eax
/APP
 # 107 "IOProgramer.cpp" 1
	outb %al,%dx 
	
 # 0 "" 2
/NO_APP
	nop
	leave
	ret	$8
	.align 2
	.globl	__ZN8IO_8259A8sendOCW2Eii
	.def	__ZN8IO_8259A8sendOCW2Eii;	.scl	2;	.type	32;	.endef
__ZN8IO_8259A8sendOCW2Eii:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	%ecx, -12(%ebp)
	movl	$125340055, (%esp)
	call	__ZN4Util10insertMarkEi
	movl	12(%ebp), %eax
	andl	$231, %eax
	movl	%eax, %ecx
	movl	8(%ebp), %eax
	movl	__ZN8IO_8259A5PORTSE(,%eax,4), %edx
	movl	%ecx, %eax
/APP
 # 118 "IOProgramer.cpp" 1
	outb %al,%dx 
	
 # 0 "" 2
/NO_APP
	nop
	leave
	ret	$8
	.globl	__ZN7IO_82535PORTSE
	.section .rdata,"dr"
	.align 4
__ZN7IO_82535PORTSE:
	.long	64
	.long	65
	.long	66
	.long	67
	.globl	__ZN7IO_82536MAXNUME
	.align 4
__ZN7IO_82536MAXNUME:
	.long	1193180
	.globl	__ZN7IO_82539MAX_MICROE
	.align 4
__ZN7IO_82539MAX_MICROE:
	.long	3599
	.text
	.align 2
	.globl	__ZN7IO_8253C2Ev
	.def	__ZN7IO_8253C2Ev;	.scl	2;	.type	32;	.endef
__ZN7IO_8253C2Ev:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	%ecx, -4(%ebp)
	nop
	leave
	ret
	.globl	__ZN7IO_8253C1Ev
	.def	__ZN7IO_8253C1Ev;	.scl	2;	.type	32;	.endef
	.set	__ZN7IO_8253C1Ev,__ZN7IO_8253C2Ev
	.align 2
	.globl	__ZN7IO_8253D2Ev
	.def	__ZN7IO_8253D2Ev;	.scl	2;	.type	32;	.endef
__ZN7IO_8253D2Ev:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	%ecx, -4(%ebp)
	nop
	leave
	ret
	.globl	__ZN7IO_8253D1Ev
	.def	__ZN7IO_8253D1Ev;	.scl	2;	.type	32;	.endef
	.set	__ZN7IO_8253D1Ev,__ZN7IO_8253D2Ev
	.align 2
	.globl	__ZN7IO_825311setTimeMillEij
	.def	__ZN7IO_825311setTimeMillEij;	.scl	2;	.type	32;	.endef
__ZN7IO_825311setTimeMillEij:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$72, %esp
	movl	%ecx, -44(%ebp)
	movl	12(%ebp), %eax
	imull	$1193, %eax, %eax
	movl	%eax, -12(%ebp)
	movl	-44(%ebp), %eax
	movl	$0, 12(%esp)
	movl	$3, 8(%esp)
	movl	$3, 4(%esp)
	movl	$0, (%esp)
	movl	%eax, %ecx
	call	__ZN7IO_825315sendControlByteEiiii
	subl	$16, %esp
	movl	8(%ebp), %eax
	movl	__ZN7IO_82535PORTSE(,%eax,4), %eax
	movl	%eax, -16(%ebp)
	movl	-12(%ebp), %eax
	movl	%eax, -28(%ebp)
	movl	-16(%ebp), %edx
	movl	-28(%ebp), %eax
/APP
 # 365 "libx2.h" 1
	outb %al,%dx 
	
 # 0 "" 2
/NO_APP
	movl	-12(%ebp), %eax
	sarl	$8, %eax
	movl	%eax, %edx
	movl	8(%ebp), %eax
	movl	__ZN7IO_82535PORTSE(,%eax,4), %eax
	movl	%eax, -20(%ebp)
	movl	%edx, -24(%ebp)
	movl	-20(%ebp), %edx
	movl	-24(%ebp), %eax
/APP
 # 365 "libx2.h" 1
	outb %al,%dx 
	
 # 0 "" 2
/NO_APP
	nop
	leave
	ret	$8
	.align 2
	.globl	__ZN7IO_825312setTimeMicroEij
	.def	__ZN7IO_825312setTimeMicroEij;	.scl	2;	.type	32;	.endef
__ZN7IO_825312setTimeMicroEij:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$72, %esp
	movl	%ecx, -44(%ebp)
	cmpl	$3599, 12(%ebp)
	jbe	L13
	movl	$3599, 12(%ebp)
L13:
	movl	12(%ebp), %eax
	imull	$1193180, %eax, %eax
	movl	$1125899907, %edx
	mull	%edx
	movl	%edx, %eax
	shrl	$18, %eax
	movl	%eax, -12(%ebp)
	movl	-44(%ebp), %eax
	movl	$0, 12(%esp)
	movl	$3, 8(%esp)
	movl	$3, 4(%esp)
	movl	$0, (%esp)
	movl	%eax, %ecx
	call	__ZN7IO_825315sendControlByteEiiii
	subl	$16, %esp
	movl	-12(%ebp), %eax
	movl	8(%ebp), %edx
	movl	__ZN7IO_82535PORTSE(,%edx,4), %edx
	movl	%edx, -16(%ebp)
	movl	%eax, -28(%ebp)
	movl	-16(%ebp), %edx
	movl	-28(%ebp), %eax
/APP
 # 365 "libx2.h" 1
	outb %al,%dx 
	
 # 0 "" 2
/NO_APP
	movl	-12(%ebp), %eax
	shrl	$8, %eax
	movl	%eax, %edx
	movl	8(%ebp), %eax
	movl	__ZN7IO_82535PORTSE(,%eax,4), %eax
	movl	%eax, -20(%ebp)
	movl	%edx, -24(%ebp)
	movl	-20(%ebp), %edx
	movl	-24(%ebp), %eax
/APP
 # 365 "libx2.h" 1
	outb %al,%dx 
	
 # 0 "" 2
/NO_APP
	nop
	leave
	ret	$8
	.align 2
	.globl	__ZN7IO_825315sendControlByteEiiii
	.def	__ZN7IO_825315sendControlByteEiiii;	.scl	2;	.type	32;	.endef
__ZN7IO_825315sendControlByteEiiii:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$20, %esp
	movl	%ecx, -20(%ebp)
	movl	8(%ebp), %eax
	sall	$6, %eax
	movzbl	%al, %eax
	movl	12(%ebp), %edx
	andl	$3, %edx
	sall	$4, %edx
	orl	%eax, %edx
	movl	16(%ebp), %eax
	andl	$7, %eax
	addl	%eax, %eax
	orl	%eax, %edx
	movl	20(%ebp), %eax
	andl	$1, %eax
	orl	%edx, %eax
	movl	$67, %edx
	movl	%edx, -4(%ebp)
	movl	%eax, -8(%ebp)
	movl	-4(%ebp), %edx
	movl	-8(%ebp), %eax
/APP
 # 365 "libx2.h" 1
	outb %al,%dx 
	
 # 0 "" 2
/NO_APP
	nop
	leave
	ret	$16
	.globl	__ZN8Keyboard9PORT_DATAE
	.section .rdata,"dr"
	.align 4
__ZN8Keyboard9PORT_DATAE:
	.long	96
	.globl	__ZN8Keyboard12PORT_CONTROLE
	.align 4
__ZN8Keyboard12PORT_CONTROLE:
	.long	100
	.globl	__ZN8Keyboard8PORT_PPIE
	.align 4
__ZN8Keyboard8PORT_PPIE:
	.long	97
	.globl	__ZN8Keyboard13NO_DATA_ERRORE
	.align 4
__ZN8Keyboard13NO_DATA_ERRORE:
	.long	65536
	.globl	__ZN8Keyboard11KEY_MAP_STDE
LC0:
	.ascii "UNUSED\0"
LC1:
	.ascii "ESC\0"
LC2:
	.ascii "1\0"
LC3:
	.ascii "2\0"
LC4:
	.ascii "3\0"
LC5:
	.ascii "4\0"
LC6:
	.ascii "5\0"
LC7:
	.ascii "6\0"
LC8:
	.ascii "7\0"
LC9:
	.ascii "8\0"
LC10:
	.ascii "9\0"
LC11:
	.ascii "0\0"
LC12:
	.ascii "_\0"
LC13:
	.ascii "=\0"
LC14:
	.ascii "BS\0"
LC15:
	.ascii "TAB\0"
LC16:
	.ascii "q\0"
LC17:
	.ascii "w\0"
LC18:
	.ascii "e\0"
LC19:
	.ascii "r\0"
LC20:
	.ascii "t\0"
LC21:
	.ascii "y\0"
LC22:
	.ascii "u\0"
LC23:
	.ascii "i\0"
LC24:
	.ascii "o\0"
LC25:
	.ascii "p\0"
LC26:
	.ascii "[\0"
LC27:
	.ascii "]\0"
LC28:
	.ascii "Enter\0"
LC29:
	.ascii "CNTL\0"
LC30:
	.ascii "a\0"
LC31:
	.ascii "s\0"
LC32:
	.ascii "d\0"
LC33:
	.ascii "f\0"
LC34:
	.ascii "g\0"
LC35:
	.ascii "h\0"
LC36:
	.ascii "j\0"
LC37:
	.ascii "k\0"
LC38:
	.ascii "l\0"
LC39:
	.ascii ";\0"
LC40:
	.ascii "'\0"
LC41:
	.ascii "`\0"
LC42:
	.ascii "LSHFT\0"
LC43:
	.ascii "\\\0"
LC44:
	.ascii "z\0"
LC45:
	.ascii "x\0"
LC46:
	.ascii "c\0"
LC47:
	.ascii "v\0"
LC48:
	.ascii "b\0"
LC49:
	.ascii "n\0"
LC50:
	.ascii "m\0"
LC51:
	.ascii ",\0"
LC52:
	.ascii ".\0"
LC53:
	.ascii "/\0"
LC54:
	.ascii "RSHFT\0"
LC55:
	.ascii "*\0"
LC56:
	.ascii "ALT\0"
LC57:
	.ascii " \0"
LC58:
	.ascii "CAP\0"
LC59:
	.ascii "F1\0"
LC60:
	.ascii "F2\0"
LC61:
	.ascii "F3\0"
LC62:
	.ascii "F4\0"
LC63:
	.ascii "F5\0"
LC64:
	.ascii "F6\0"
LC65:
	.ascii "F7\0"
LC66:
	.ascii "F8\0"
LC67:
	.ascii "F9\0"
LC68:
	.ascii "F10\0"
LC69:
	.ascii "NUML\0"
LC70:
	.ascii "CtrlBreak\0"
LC71:
	.ascii "Home\0"
LC72:
	.ascii "Up\0"
LC73:
	.ascii "PgUp\0"
LC74:
	.ascii "-\0"
LC75:
	.ascii "Left\0"
LC76:
	.ascii "Center\0"
LC77:
	.ascii "Right\0"
LC78:
	.ascii "+\0"
LC79:
	.ascii "End\0"
LC80:
	.ascii "Down\0"
LC81:
	.ascii "PgDn\0"
LC82:
	.ascii "Ins\0"
LC83:
	.ascii "Del\0"
LC84:
	.ascii "Unknown\0"
LC85:
	.ascii "F11\0"
LC86:
	.ascii "F12\0"
LC87:
	.ascii "Unkown\0"
LC88:
	.ascii "Windows\0"
LC89:
	.ascii "Menu\0"
	.data
	.align 32
__ZN8Keyboard11KEY_MAP_STDE:
	.long	LC0
	.long	LC1
	.long	LC2
	.long	LC3
	.long	LC4
	.long	LC5
	.long	LC6
	.long	LC7
	.long	LC8
	.long	LC9
	.long	LC10
	.long	LC11
	.long	LC12
	.long	LC13
	.long	LC14
	.long	LC15
	.long	LC16
	.long	LC17
	.long	LC18
	.long	LC19
	.long	LC20
	.long	LC21
	.long	LC22
	.long	LC23
	.long	LC24
	.long	LC25
	.long	LC26
	.long	LC27
	.long	LC28
	.long	LC29
	.long	LC30
	.long	LC31
	.long	LC32
	.long	LC33
	.long	LC34
	.long	LC35
	.long	LC36
	.long	LC37
	.long	LC38
	.long	LC39
	.long	LC40
	.long	LC41
	.long	LC42
	.long	LC43
	.long	LC44
	.long	LC45
	.long	LC46
	.long	LC47
	.long	LC48
	.long	LC49
	.long	LC50
	.long	LC51
	.long	LC52
	.long	LC53
	.long	LC54
	.long	LC55
	.long	LC56
	.long	LC57
	.long	LC58
	.long	LC59
	.long	LC60
	.long	LC61
	.long	LC62
	.long	LC63
	.long	LC64
	.long	LC65
	.long	LC66
	.long	LC67
	.long	LC68
	.long	LC69
	.long	LC70
	.long	LC71
	.long	LC72
	.long	LC73
	.long	LC74
	.long	LC75
	.long	LC76
	.long	LC77
	.long	LC78
	.long	LC79
	.long	LC80
	.long	LC81
	.long	LC82
	.long	LC83
	.long	LC84
	.long	LC84
	.long	LC84
	.long	LC85
	.long	LC86
	.long	LC87
	.long	LC84
	.long	LC88
	.long	LC84
	.long	LC89
	.globl	__ZN8Keyboard15KEY_MAP_STD_LENE
	.section .rdata,"dr"
	.align 4
__ZN8Keyboard15KEY_MAP_STD_LENE:
	.long	94
	.text
	.align 2
	.globl	__ZN8KeyboardC2Ev
	.def	__ZN8KeyboardC2Ev;	.scl	2;	.type	32;	.endef
__ZN8KeyboardC2Ev:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	%ecx, -4(%ebp)
	nop
	leave
	ret
	.globl	__ZN8KeyboardC1Ev
	.def	__ZN8KeyboardC1Ev;	.scl	2;	.type	32;	.endef
	.set	__ZN8KeyboardC1Ev,__ZN8KeyboardC2Ev
	.align 2
	.globl	__ZN8KeyboardD2Ev
	.def	__ZN8KeyboardD2Ev;	.scl	2;	.type	32;	.endef
__ZN8KeyboardD2Ev:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	%ecx, -4(%ebp)
	nop
	leave
	ret
	.globl	__ZN8KeyboardD1Ev
	.def	__ZN8KeyboardD1Ev;	.scl	2;	.type	32;	.endef
	.set	__ZN8KeyboardD1Ev,__ZN8KeyboardD2Ev
	.align 2
	.globl	__ZN8Keyboard11waitToWriteEv
	.def	__ZN8Keyboard11waitToWriteEv;	.scl	2;	.type	32;	.endef
__ZN8Keyboard11waitToWriteEv:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$20, %esp
	movl	%ecx, -20(%ebp)
L21:
	movl	-20(%ebp), %eax
	movl	%eax, -4(%ebp)
	movl	$100, %eax
	movl	%eax, -8(%ebp)
	movl	-8(%ebp), %eax
	movl	%eax, %edx
/APP
 # 375 "libx2.h" 1
	inb %dx,%al 
	
 # 0 "" 2
/NO_APP
	movl	%eax, -12(%ebp)
	movl	-12(%ebp), %eax
	andl	$2, %eax
	testl	%eax, %eax
	setne	%al
	testb	%al, %al
	je	L22
	jmp	L21
L22:
	nop
	leave
	ret
	.section .rdata,"dr"
LC90:
	.ascii "Exceed.\0"
	.text
	.align 2
	.globl	__ZN8Keyboard12getAsciiCharEh
	.def	__ZN8Keyboard12getAsciiCharEh;	.scl	2;	.type	32;	.endef
__ZN8Keyboard12getAsciiCharEh:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	%ecx, -4(%ebp)
	movl	8(%ebp), %eax
	movb	%al, -8(%ebp)
	cmpb	$94, -8(%ebp)
	ja	L24
	movzbl	-8(%ebp), %eax
	movl	__ZN8Keyboard11KEY_MAP_STDE(,%eax,4), %eax
	jmp	L25
L24:
	movl	$LC90, %eax
L25:
	leave
	ret	$4
	.ident	"GCC: (GNU) 5.4.0"
	.def	__ZN4Util10insertMarkEi;	.scl	2;	.type	32;	.endef
