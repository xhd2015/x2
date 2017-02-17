	.file	"interrupts.cpp"
/APP
	.code32 
	
/NO_APP
	.globl	___intAddresses
	.data
	.align 32
___intAddresses:
	.long	_int0x0
	.long	_int0x1
	.long	_int0x2
	.long	_int0x3
	.long	_int0x4
	.long	_int0x5
	.long	_int0x6
	.long	_int0x7
	.long	_int0x8
	.long	_int0x9
	.long	_int0xa
	.long	_int0xb
	.long	_int0xc
	.long	_int0xd
	.long	_int0xe
	.long	_int0xf
	.long	_int0x10
	.long	_int0x11
	.long	_int0x12
	.long	_int0x13
	.long	_int0x14
	.long	_int0x15
	.long	_int0x16
	.long	_int0x17
	.long	_int0x18
	.long	_int0x19
	.long	_int0x1a
	.long	_int0x1b
	.long	_int0x1c
	.long	_int0x1d
	.long	_int0x1e
	.long	_int0x1f
	.long	-1
	.long	-1
	.long	_intDefault
	.long	_intDefault
	.long	_int0x24
	.long	_int0x25
	.globl	_intAddresses
	.align 4
_intAddresses:
	.long	___intAddresses
	.globl	_intLen
	.align 4
_intLen:
	.long	38
	.section .rdata,"dr"
LC0:
	.ascii "int 0x0:#DE\12\0"
	.text
	.globl	_int0x0
	.def	_int0x0;	.scl	2;	.type	32;	.endef
_int0x0:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$36, %esp
/APP
 # 63 "interrupts.cpp" 1
	leave 
	
 # 0 "" 2
 # 64 "interrupts.cpp" 1
	jmp . 
	
 # 0 "" 2
/NO_APP
	movl	$21840, (%esp)
	call	__ZN4Util10insertMarkEi
	movl	$0, 8(%esp)
	movl	$0, 4(%esp)
	movl	$3, (%esp)
	call	__ZN4Util7makeSelEiii
	cwtl
	movl	%eax, -16(%ebp)
	movl	__ZN4Util11SEG_CURRENTE, %eax
	cmpl	%eax, -16(%ebp)
	je	L2
	movl	-16(%ebp), %eax
/APP
 # 67 "interrupts.cpp" 1
	mov %ds,%ebx
	movw %ax,%ds 
	
 # 0 "" 2
/NO_APP
	movl	%ebx, %eax
	movl	%eax, -12(%ebp)
L2:
	movl	__ZN4Util11MODE_COMMONE, %eax
	movl	%eax, 4(%esp)
	movl	$LC0, (%esp)
	call	__ZN4Util8printStrEPKci
	movl	__ZN4Util11SEG_CURRENTE, %eax
	cmpl	%eax, -16(%ebp)
	je	L3
	movl	-12(%ebp), %eax
/APP
 # 69 "interrupts.cpp" 1
	mov %ax,%ds 
	
 # 0 "" 2
/NO_APP
L3:
/APP
 # 70 "interrupts.cpp" 1
	leave 
	
 # 0 "" 2
 # 71 "interrupts.cpp" 1
	jmp . 
	
 # 0 "" 2
 # 72 "interrupts.cpp" 1
	leave 
	iret 
	
 # 0 "" 2
/NO_APP
	nop
	addl	$36, %esp
	popl	%ebx
	popl	%ebp
	ret
	.section .rdata,"dr"
LC1:
	.ascii "int 0x1:Trap exception\12\0"
	.text
	.globl	_int0x1
	.def	_int0x1;	.scl	2;	.type	32;	.endef
_int0x1:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$36, %esp
/APP
 # 81 "interrupts.cpp" 1
	leave 
	
 # 0 "" 2
 # 82 "interrupts.cpp" 1
	jmp . 
	
 # 0 "" 2
/NO_APP
	movl	$21841, (%esp)
	call	__ZN4Util10insertMarkEi
	movl	$0, 8(%esp)
	movl	$0, 4(%esp)
	movl	$3, (%esp)
	call	__ZN4Util7makeSelEiii
	cwtl
	movl	%eax, -16(%ebp)
	movl	__ZN4Util11SEG_CURRENTE, %eax
	cmpl	%eax, -16(%ebp)
	je	L5
	movl	-16(%ebp), %eax
/APP
 # 85 "interrupts.cpp" 1
	mov %ds,%ebx
	movw %ax,%ds 
	
 # 0 "" 2
/NO_APP
	movl	%ebx, %eax
	movl	%eax, -12(%ebp)
L5:
	movl	__ZN4Util11MODE_COMMONE, %eax
	movl	%eax, 4(%esp)
	movl	$LC1, (%esp)
	call	__ZN4Util8printStrEPKci
	movl	__ZN4Util11SEG_CURRENTE, %eax
	cmpl	%eax, -16(%ebp)
	je	L6
	movl	-12(%ebp), %eax
/APP
 # 87 "interrupts.cpp" 1
	mov %ax,%ds 
	
 # 0 "" 2
/NO_APP
L6:
/APP
 # 88 "interrupts.cpp" 1
	leave 
	iret 
	
 # 0 "" 2
/NO_APP
	nop
	addl	$36, %esp
	popl	%ebx
	popl	%ebp
	ret
	.section .rdata,"dr"
LC2:
	.ascii "int 0x2.\12\0"
	.text
	.globl	_int0x2
	.def	_int0x2;	.scl	2;	.type	32;	.endef
_int0x2:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$36, %esp
	movl	$0, 8(%esp)
	movl	$0, 4(%esp)
	movl	$3, (%esp)
	call	__ZN4Util7makeSelEiii
	cwtl
	movl	%eax, -16(%ebp)
	movl	__ZN4Util11SEG_CURRENTE, %eax
	cmpl	%eax, -16(%ebp)
	je	L8
	movl	-16(%ebp), %eax
/APP
 # 98 "interrupts.cpp" 1
	mov %ds,%ebx
	movw %ax,%ds 
	
 # 0 "" 2
/NO_APP
	movl	%ebx, %eax
	movl	%eax, -12(%ebp)
L8:
	movl	__ZN4Util11MODE_COMMONE, %eax
	movl	%eax, 4(%esp)
	movl	$LC2, (%esp)
	call	__ZN4Util8printStrEPKci
	movl	__ZN4Util11SEG_CURRENTE, %eax
	cmpl	%eax, -16(%ebp)
	je	L9
	movl	-12(%ebp), %eax
/APP
 # 100 "interrupts.cpp" 1
	mov %ax,%ds 
	
 # 0 "" 2
/NO_APP
L9:
/APP
 # 101 "interrupts.cpp" 1
	leave 
	iret 
	
 # 0 "" 2
/NO_APP
	nop
	addl	$36, %esp
	popl	%ebx
	popl	%ebp
	ret
	.section .rdata,"dr"
LC3:
	.ascii "int 0x3.\12\0"
	.text
	.globl	_int0x3
	.def	_int0x3;	.scl	2;	.type	32;	.endef
_int0x3:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$36, %esp
	movl	$0, 8(%esp)
	movl	$0, 4(%esp)
	movl	$3, (%esp)
	call	__ZN4Util7makeSelEiii
	cwtl
	movl	%eax, -16(%ebp)
	movl	__ZN4Util11SEG_CURRENTE, %eax
	cmpl	%eax, -16(%ebp)
	je	L11
	movl	-16(%ebp), %eax
/APP
 # 111 "interrupts.cpp" 1
	mov %ds,%ebx
	movw %ax,%ds 
	
 # 0 "" 2
/NO_APP
	movl	%ebx, %eax
	movl	%eax, -12(%ebp)
L11:
	movl	__ZN4Util11MODE_COMMONE, %eax
	movl	%eax, 4(%esp)
	movl	$LC3, (%esp)
	call	__ZN4Util8printStrEPKci
	movl	__ZN4Util11SEG_CURRENTE, %eax
	cmpl	%eax, -16(%ebp)
	je	L12
	movl	-12(%ebp), %eax
/APP
 # 113 "interrupts.cpp" 1
	mov %ax,%ds 
	
 # 0 "" 2
/NO_APP
L12:
/APP
 # 114 "interrupts.cpp" 1
	leave 
	iret 
	
 # 0 "" 2
/NO_APP
	nop
	addl	$36, %esp
	popl	%ebx
	popl	%ebp
	ret
	.section .rdata,"dr"
LC4:
	.ascii "int 0x4.\12\0"
	.text
	.globl	_int0x4
	.def	_int0x4;	.scl	2;	.type	32;	.endef
_int0x4:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$36, %esp
	movl	$0, 8(%esp)
	movl	$0, 4(%esp)
	movl	$3, (%esp)
	call	__ZN4Util7makeSelEiii
	cwtl
	movl	%eax, -16(%ebp)
	movl	__ZN4Util11SEG_CURRENTE, %eax
	cmpl	%eax, -16(%ebp)
	je	L14
	movl	-16(%ebp), %eax
/APP
 # 124 "interrupts.cpp" 1
	mov %ds,%ebx
	movw %ax,%ds 
	
 # 0 "" 2
/NO_APP
	movl	%ebx, %eax
	movl	%eax, -12(%ebp)
L14:
	movl	__ZN4Util11MODE_COMMONE, %eax
	movl	%eax, 4(%esp)
	movl	$LC4, (%esp)
	call	__ZN4Util8printStrEPKci
	movl	__ZN4Util11SEG_CURRENTE, %eax
	cmpl	%eax, -16(%ebp)
	je	L15
	movl	-12(%ebp), %eax
/APP
 # 126 "interrupts.cpp" 1
	mov %ax,%ds 
	
 # 0 "" 2
/NO_APP
L15:
/APP
 # 127 "interrupts.cpp" 1
	leave 
	iret 
	
 # 0 "" 2
/NO_APP
	nop
	addl	$36, %esp
	popl	%ebx
	popl	%ebp
	ret
	.section .rdata,"dr"
LC5:
	.ascii "int 0x5.\12\0"
	.text
	.globl	_int0x5
	.def	_int0x5;	.scl	2;	.type	32;	.endef
_int0x5:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$36, %esp
	movl	$0, 8(%esp)
	movl	$0, 4(%esp)
	movl	$3, (%esp)
	call	__ZN4Util7makeSelEiii
	cwtl
	movl	%eax, -16(%ebp)
	movl	__ZN4Util11SEG_CURRENTE, %eax
	cmpl	%eax, -16(%ebp)
	je	L17
	movl	-16(%ebp), %eax
/APP
 # 137 "interrupts.cpp" 1
	mov %ds,%ebx
	movw %ax,%ds 
	
 # 0 "" 2
/NO_APP
	movl	%ebx, %eax
	movl	%eax, -12(%ebp)
L17:
	movl	__ZN4Util11MODE_COMMONE, %eax
	movl	%eax, 4(%esp)
	movl	$LC5, (%esp)
	call	__ZN4Util8printStrEPKci
	movl	__ZN4Util11SEG_CURRENTE, %eax
	cmpl	%eax, -16(%ebp)
	je	L18
	movl	-12(%ebp), %eax
/APP
 # 139 "interrupts.cpp" 1
	mov %ax,%ds 
	
 # 0 "" 2
/NO_APP
L18:
/APP
 # 140 "interrupts.cpp" 1
	leave 
	iret 
	
 # 0 "" 2
/NO_APP
	nop
	addl	$36, %esp
	popl	%ebx
	popl	%ebp
	ret
	.section .rdata,"dr"
LC6:
	.ascii "int 0x6.\12\0"
	.text
	.globl	_int0x6
	.def	_int0x6;	.scl	2;	.type	32;	.endef
_int0x6:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$36, %esp
	movl	$0, 8(%esp)
	movl	$0, 4(%esp)
	movl	$3, (%esp)
	call	__ZN4Util7makeSelEiii
	cwtl
	movl	%eax, -16(%ebp)
	movl	__ZN4Util11SEG_CURRENTE, %eax
	cmpl	%eax, -16(%ebp)
	je	L20
	movl	-16(%ebp), %eax
/APP
 # 150 "interrupts.cpp" 1
	mov %ds,%ebx
	movw %ax,%ds 
	
 # 0 "" 2
/NO_APP
	movl	%ebx, %eax
	movl	%eax, -12(%ebp)
L20:
	movl	__ZN4Util11MODE_COMMONE, %eax
	movl	%eax, 4(%esp)
	movl	$LC6, (%esp)
	call	__ZN4Util8printStrEPKci
	movl	__ZN4Util11SEG_CURRENTE, %eax
	cmpl	%eax, -16(%ebp)
	je	L21
	movl	-12(%ebp), %eax
/APP
 # 152 "interrupts.cpp" 1
	mov %ax,%ds 
	
 # 0 "" 2
/NO_APP
L21:
/APP
 # 153 "interrupts.cpp" 1
	leave 
	iret 
	
 # 0 "" 2
/NO_APP
	nop
	addl	$36, %esp
	popl	%ebx
	popl	%ebp
	ret
	.section .rdata,"dr"
LC7:
	.ascii "int 0x7.\12\0"
	.text
	.globl	_int0x7
	.def	_int0x7;	.scl	2;	.type	32;	.endef
_int0x7:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$36, %esp
	movl	$0, 8(%esp)
	movl	$0, 4(%esp)
	movl	$3, (%esp)
	call	__ZN4Util7makeSelEiii
	cwtl
	movl	%eax, -16(%ebp)
	movl	__ZN4Util11SEG_CURRENTE, %eax
	cmpl	%eax, -16(%ebp)
	je	L23
	movl	-16(%ebp), %eax
/APP
 # 164 "interrupts.cpp" 1
	mov %ds,%ebx
	movw %ax,%ds 
	
 # 0 "" 2
/NO_APP
	movl	%ebx, %eax
	movl	%eax, -12(%ebp)
L23:
	movl	__ZN4Util11MODE_COMMONE, %eax
	movl	%eax, 4(%esp)
	movl	$LC7, (%esp)
	call	__ZN4Util8printStrEPKci
	movl	__ZN4Util11SEG_CURRENTE, %eax
	cmpl	%eax, -16(%ebp)
	je	L24
	movl	-12(%ebp), %eax
/APP
 # 166 "interrupts.cpp" 1
	mov %ax,%ds 
	
 # 0 "" 2
/NO_APP
L24:
/APP
 # 167 "interrupts.cpp" 1
	leave 
	iret 
	
 # 0 "" 2
/NO_APP
	nop
	addl	$36, %esp
	popl	%ebx
	popl	%ebp
	ret
	.section .rdata,"dr"
LC8:
	.ascii "int 0x9.\12\0"
	.text
	.globl	_int0x8
	.def	_int0x8;	.scl	2;	.type	32;	.endef
_int0x8:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$36, %esp
	movl	$0, 8(%esp)
	movl	$0, 4(%esp)
	movl	$3, (%esp)
	call	__ZN4Util7makeSelEiii
	cwtl
	movl	%eax, -16(%ebp)
	movl	__ZN4Util11SEG_CURRENTE, %eax
	cmpl	%eax, -16(%ebp)
	je	L26
	movl	-16(%ebp), %eax
/APP
 # 177 "interrupts.cpp" 1
	mov %ds,%ebx
	movw %ax,%ds 
	
 # 0 "" 2
/NO_APP
	movl	%ebx, %eax
	movl	%eax, -12(%ebp)
L26:
	movl	__ZN4Util11MODE_COMMONE, %eax
	movl	%eax, 4(%esp)
	movl	$LC8, (%esp)
	call	__ZN4Util8printStrEPKci
	movl	__ZN4Util11SEG_CURRENTE, %eax
	cmpl	%eax, -16(%ebp)
	je	L27
	movl	-12(%ebp), %eax
/APP
 # 179 "interrupts.cpp" 1
	mov %ax,%ds 
	
 # 0 "" 2
/NO_APP
L27:
/APP
 # 180 "interrupts.cpp" 1
	leave 
	iret 
	
 # 0 "" 2
/NO_APP
	nop
	addl	$36, %esp
	popl	%ebx
	popl	%ebp
	ret
	.globl	_int0x9
	.def	_int0x9;	.scl	2;	.type	32;	.endef
_int0x9:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$36, %esp
	movl	$0, 8(%esp)
	movl	$0, 4(%esp)
	movl	$3, (%esp)
	call	__ZN4Util7makeSelEiii
	cwtl
	movl	%eax, -16(%ebp)
	movl	__ZN4Util11SEG_CURRENTE, %eax
	cmpl	%eax, -16(%ebp)
	je	L29
	movl	-16(%ebp), %eax
/APP
 # 190 "interrupts.cpp" 1
	mov %ds,%ebx
	movw %ax,%ds 
	
 # 0 "" 2
/NO_APP
	movl	%ebx, %eax
	movl	%eax, -12(%ebp)
L29:
	movl	__ZN4Util11MODE_COMMONE, %eax
	movl	%eax, 4(%esp)
	movl	$LC8, (%esp)
	call	__ZN4Util8printStrEPKci
	movl	__ZN4Util11SEG_CURRENTE, %eax
	cmpl	%eax, -16(%ebp)
	je	L30
	movl	-12(%ebp), %eax
/APP
 # 192 "interrupts.cpp" 1
	mov %ax,%ds 
	
 # 0 "" 2
/NO_APP
L30:
/APP
 # 193 "interrupts.cpp" 1
	leave 
	iret 
	
 # 0 "" 2
/NO_APP
	nop
	addl	$36, %esp
	popl	%ebx
	popl	%ebp
	ret
	.section .rdata,"dr"
LC9:
	.ascii "int 0xa.\12\0"
	.text
	.globl	_int0xa
	.def	_int0xa;	.scl	2;	.type	32;	.endef
_int0xa:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$36, %esp
	movl	$0, 8(%esp)
	movl	$0, 4(%esp)
	movl	$3, (%esp)
	call	__ZN4Util7makeSelEiii
	cwtl
	movl	%eax, -16(%ebp)
	movl	__ZN4Util11SEG_CURRENTE, %eax
	cmpl	%eax, -16(%ebp)
	je	L32
	movl	-16(%ebp), %eax
/APP
 # 203 "interrupts.cpp" 1
	mov %ds,%ebx
	movw %ax,%ds 
	
 # 0 "" 2
/NO_APP
	movl	%ebx, %eax
	movl	%eax, -12(%ebp)
L32:
	movl	__ZN4Util11MODE_COMMONE, %eax
	movl	%eax, 4(%esp)
	movl	$LC9, (%esp)
	call	__ZN4Util8printStrEPKci
	movl	__ZN4Util11SEG_CURRENTE, %eax
	cmpl	%eax, -16(%ebp)
	je	L33
	movl	-12(%ebp), %eax
/APP
 # 205 "interrupts.cpp" 1
	mov %ax,%ds 
	
 # 0 "" 2
/NO_APP
L33:
/APP
 # 206 "interrupts.cpp" 1
	leave 
	iret 
	
 # 0 "" 2
/NO_APP
	nop
	addl	$36, %esp
	popl	%ebx
	popl	%ebp
	ret
	.section .rdata,"dr"
LC10:
	.ascii "int 0xb.\12\0"
	.text
	.globl	_int0xb
	.def	_int0xb;	.scl	2;	.type	32;	.endef
_int0xb:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$36, %esp
	movl	$0, 8(%esp)
	movl	$0, 4(%esp)
	movl	$3, (%esp)
	call	__ZN4Util7makeSelEiii
	cwtl
	movl	%eax, -16(%ebp)
	movl	__ZN4Util11SEG_CURRENTE, %eax
	cmpl	%eax, -16(%ebp)
	je	L35
	movl	-16(%ebp), %eax
/APP
 # 216 "interrupts.cpp" 1
	mov %ds,%ebx
	movw %ax,%ds 
	
 # 0 "" 2
/NO_APP
	movl	%ebx, %eax
	movl	%eax, -12(%ebp)
L35:
	movl	__ZN4Util11MODE_COMMONE, %eax
	movl	%eax, 4(%esp)
	movl	$LC10, (%esp)
	call	__ZN4Util8printStrEPKci
	movl	__ZN4Util11SEG_CURRENTE, %eax
	cmpl	%eax, -16(%ebp)
	je	L36
	movl	-12(%ebp), %eax
/APP
 # 218 "interrupts.cpp" 1
	mov %ax,%ds 
	
 # 0 "" 2
/NO_APP
L36:
/APP
 # 219 "interrupts.cpp" 1
	leave 
	iret 
	
 # 0 "" 2
/NO_APP
	nop
	addl	$36, %esp
	popl	%ebx
	popl	%ebp
	ret
	.section .rdata,"dr"
LC11:
	.ascii "int 0xc.\12\0"
	.text
	.globl	_int0xc
	.def	_int0xc;	.scl	2;	.type	32;	.endef
_int0xc:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$36, %esp
	movl	$0, 8(%esp)
	movl	$0, 4(%esp)
	movl	$3, (%esp)
	call	__ZN4Util7makeSelEiii
	cwtl
	movl	%eax, -16(%ebp)
	movl	__ZN4Util11SEG_CURRENTE, %eax
	cmpl	%eax, -16(%ebp)
	je	L38
	movl	-16(%ebp), %eax
/APP
 # 229 "interrupts.cpp" 1
	mov %ds,%ebx
	movw %ax,%ds 
	
 # 0 "" 2
/NO_APP
	movl	%ebx, %eax
	movl	%eax, -12(%ebp)
L38:
	movl	__ZN4Util11MODE_COMMONE, %eax
	movl	%eax, 4(%esp)
	movl	$LC11, (%esp)
	call	__ZN4Util8printStrEPKci
	movl	__ZN4Util11SEG_CURRENTE, %eax
	cmpl	%eax, -16(%ebp)
	je	L39
	movl	-12(%ebp), %eax
/APP
 # 231 "interrupts.cpp" 1
	mov %ax,%ds 
	
 # 0 "" 2
/NO_APP
L39:
/APP
 # 232 "interrupts.cpp" 1
	leave 
	iret 
	
 # 0 "" 2
/NO_APP
	nop
	addl	$36, %esp
	popl	%ebx
	popl	%ebp
	ret
	.section .rdata,"dr"
LC12:
	.ascii "int 0xd:#GP\12\0"
	.text
	.globl	_int0xd
	.def	_int0xd;	.scl	2;	.type	32;	.endef
_int0xd:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$52, %esp
/APP
 # 241 "interrupts.cpp" 1
	leave 
	
 # 0 "" 2
 # 242 "interrupts.cpp" 1
	jmp . 
	
 # 0 "" 2
/NO_APP
	movl	$21853, (%esp)
	call	__ZN4Util10insertMarkEi
/APP
 # 250 "interrupts.cpp" 1
	mov %esp,%edx 
	
 # 0 "" 2
/NO_APP
	movl	%eax, -16(%ebp)
	movl	%ebx, -20(%ebp)
	movl	%ecx, -24(%ebp)
	movl	%edx, -28(%ebp)
	movl	$0, 8(%esp)
	movl	$0, 4(%esp)
	movl	$3, (%esp)
	call	__ZN4Util7makeSelEiii
	cwtl
	movl	%eax, -32(%ebp)
	movl	__ZN4Util11SEG_CURRENTE, %eax
	cmpl	%eax, -32(%ebp)
	je	L41
	movl	-32(%ebp), %eax
/APP
 # 252 "interrupts.cpp" 1
	mov %ds,%ebx
	movw %ax,%ds 
	
 # 0 "" 2
/NO_APP
	movl	%ebx, %eax
	movl	%eax, -12(%ebp)
L41:
	movl	__ZN4Util11MODE_COMMONE, %eax
	movl	%eax, 4(%esp)
	movl	$LC12, (%esp)
	call	__ZN4Util8printStrEPKci
	movl	__ZN4Util11SEG_CURRENTE, %eax
	cmpl	%eax, -32(%ebp)
	je	L42
	movl	-12(%ebp), %eax
/APP
 # 254 "interrupts.cpp" 1
	mov %ax,%ds 
	
 # 0 "" 2
/NO_APP
L42:
/APP
 # 255 "interrupts.cpp" 1
	jmp . 
	
 # 0 "" 2
 # 256 "interrupts.cpp" 1
	iret 
	
 # 0 "" 2
/NO_APP
	nop
	addl	$52, %esp
	popl	%ebx
	popl	%ebp
	ret
	.section .rdata,"dr"
LC13:
	.ascii "int 0xe.\12\0"
	.text
	.globl	_int0xe
	.def	_int0xe;	.scl	2;	.type	32;	.endef
_int0xe:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$36, %esp
	movl	$0, 8(%esp)
	movl	$0, 4(%esp)
	movl	$3, (%esp)
	call	__ZN4Util7makeSelEiii
	cwtl
	movl	%eax, -16(%ebp)
	movl	__ZN4Util11SEG_CURRENTE, %eax
	cmpl	%eax, -16(%ebp)
	je	L44
	movl	-16(%ebp), %eax
/APP
 # 266 "interrupts.cpp" 1
	mov %ds,%ebx
	movw %ax,%ds 
	
 # 0 "" 2
/NO_APP
	movl	%ebx, %eax
	movl	%eax, -12(%ebp)
L44:
	movl	__ZN4Util11MODE_COMMONE, %eax
	movl	%eax, 4(%esp)
	movl	$LC13, (%esp)
	call	__ZN4Util8printStrEPKci
	movl	__ZN4Util11SEG_CURRENTE, %eax
	cmpl	%eax, -16(%ebp)
	je	L45
	movl	-12(%ebp), %eax
/APP
 # 268 "interrupts.cpp" 1
	mov %ax,%ds 
	
 # 0 "" 2
/NO_APP
L45:
/APP
 # 269 "interrupts.cpp" 1
	leave 
	iret 
	
 # 0 "" 2
/NO_APP
	nop
	addl	$36, %esp
	popl	%ebx
	popl	%ebp
	ret
	.section .rdata,"dr"
LC14:
	.ascii "int 0xf.\12\0"
	.text
	.globl	_int0xf
	.def	_int0xf;	.scl	2;	.type	32;	.endef
_int0xf:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$36, %esp
	movl	$0, 8(%esp)
	movl	$0, 4(%esp)
	movl	$3, (%esp)
	call	__ZN4Util7makeSelEiii
	cwtl
	movl	%eax, -16(%ebp)
	movl	__ZN4Util11SEG_CURRENTE, %eax
	cmpl	%eax, -16(%ebp)
	je	L47
	movl	-16(%ebp), %eax
/APP
 # 279 "interrupts.cpp" 1
	mov %ds,%ebx
	movw %ax,%ds 
	
 # 0 "" 2
/NO_APP
	movl	%ebx, %eax
	movl	%eax, -12(%ebp)
L47:
	movl	__ZN4Util11MODE_COMMONE, %eax
	movl	%eax, 4(%esp)
	movl	$LC14, (%esp)
	call	__ZN4Util8printStrEPKci
	movl	__ZN4Util11SEG_CURRENTE, %eax
	cmpl	%eax, -16(%ebp)
	je	L48
	movl	-12(%ebp), %eax
/APP
 # 281 "interrupts.cpp" 1
	mov %ax,%ds 
	
 # 0 "" 2
/NO_APP
L48:
/APP
 # 282 "interrupts.cpp" 1
	leave 
	iret 
	
 # 0 "" 2
/NO_APP
	nop
	addl	$36, %esp
	popl	%ebx
	popl	%ebp
	ret
	.section .rdata,"dr"
LC15:
	.ascii "int 0x10.\12\0"
	.text
	.globl	_int0x10
	.def	_int0x10;	.scl	2;	.type	32;	.endef
_int0x10:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$36, %esp
	movl	$0, 8(%esp)
	movl	$0, 4(%esp)
	movl	$3, (%esp)
	call	__ZN4Util7makeSelEiii
	cwtl
	movl	%eax, -16(%ebp)
	movl	__ZN4Util11SEG_CURRENTE, %eax
	cmpl	%eax, -16(%ebp)
	je	L50
	movl	-16(%ebp), %eax
/APP
 # 292 "interrupts.cpp" 1
	mov %ds,%ebx
	movw %ax,%ds 
	
 # 0 "" 2
/NO_APP
	movl	%ebx, %eax
	movl	%eax, -12(%ebp)
L50:
	movl	__ZN4Util11MODE_COMMONE, %eax
	movl	%eax, 4(%esp)
	movl	$LC15, (%esp)
	call	__ZN4Util8printStrEPKci
	movl	__ZN4Util11SEG_CURRENTE, %eax
	cmpl	%eax, -16(%ebp)
	je	L51
	movl	-12(%ebp), %eax
/APP
 # 294 "interrupts.cpp" 1
	mov %ax,%ds 
	
 # 0 "" 2
/NO_APP
L51:
/APP
 # 295 "interrupts.cpp" 1
	leave 
	iret 
	
 # 0 "" 2
/NO_APP
	nop
	addl	$36, %esp
	popl	%ebx
	popl	%ebp
	ret
	.section .rdata,"dr"
LC16:
	.ascii "int 0x11.\12\0"
	.text
	.globl	_int0x11
	.def	_int0x11;	.scl	2;	.type	32;	.endef
_int0x11:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$36, %esp
	movl	$0, 8(%esp)
	movl	$0, 4(%esp)
	movl	$3, (%esp)
	call	__ZN4Util7makeSelEiii
	cwtl
	movl	%eax, -16(%ebp)
	movl	__ZN4Util11SEG_CURRENTE, %eax
	cmpl	%eax, -16(%ebp)
	je	L53
	movl	-16(%ebp), %eax
/APP
 # 305 "interrupts.cpp" 1
	mov %ds,%ebx
	movw %ax,%ds 
	
 # 0 "" 2
/NO_APP
	movl	%ebx, %eax
	movl	%eax, -12(%ebp)
L53:
	movl	__ZN4Util11MODE_COMMONE, %eax
	movl	%eax, 4(%esp)
	movl	$LC16, (%esp)
	call	__ZN4Util8printStrEPKci
	movl	__ZN4Util11SEG_CURRENTE, %eax
	cmpl	%eax, -16(%ebp)
	je	L54
	movl	-12(%ebp), %eax
/APP
 # 307 "interrupts.cpp" 1
	mov %ax,%ds 
	
 # 0 "" 2
/NO_APP
L54:
/APP
 # 308 "interrupts.cpp" 1
	leave 
	iret 
	
 # 0 "" 2
/NO_APP
	nop
	addl	$36, %esp
	popl	%ebx
	popl	%ebp
	ret
	.section .rdata,"dr"
LC17:
	.ascii "int 0x12.\12\0"
	.text
	.globl	_int0x12
	.def	_int0x12;	.scl	2;	.type	32;	.endef
_int0x12:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$36, %esp
	movl	$0, 8(%esp)
	movl	$0, 4(%esp)
	movl	$3, (%esp)
	call	__ZN4Util7makeSelEiii
	cwtl
	movl	%eax, -16(%ebp)
	movl	__ZN4Util11SEG_CURRENTE, %eax
	cmpl	%eax, -16(%ebp)
	je	L56
	movl	-16(%ebp), %eax
/APP
 # 318 "interrupts.cpp" 1
	mov %ds,%ebx
	movw %ax,%ds 
	
 # 0 "" 2
/NO_APP
	movl	%ebx, %eax
	movl	%eax, -12(%ebp)
L56:
	movl	__ZN4Util11MODE_COMMONE, %eax
	movl	%eax, 4(%esp)
	movl	$LC17, (%esp)
	call	__ZN4Util8printStrEPKci
	movl	__ZN4Util11SEG_CURRENTE, %eax
	cmpl	%eax, -16(%ebp)
	je	L57
	movl	-12(%ebp), %eax
/APP
 # 320 "interrupts.cpp" 1
	mov %ax,%ds 
	
 # 0 "" 2
/NO_APP
L57:
/APP
 # 321 "interrupts.cpp" 1
	leave 
	iret 
	
 # 0 "" 2
/NO_APP
	nop
	addl	$36, %esp
	popl	%ebx
	popl	%ebp
	ret
	.section .rdata,"dr"
LC18:
	.ascii "int 0x13.\12\0"
	.text
	.globl	_int0x13
	.def	_int0x13;	.scl	2;	.type	32;	.endef
_int0x13:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$36, %esp
	movl	$0, 8(%esp)
	movl	$0, 4(%esp)
	movl	$3, (%esp)
	call	__ZN4Util7makeSelEiii
	cwtl
	movl	%eax, -16(%ebp)
	movl	__ZN4Util11SEG_CURRENTE, %eax
	cmpl	%eax, -16(%ebp)
	je	L59
	movl	-16(%ebp), %eax
/APP
 # 331 "interrupts.cpp" 1
	mov %ds,%ebx
	movw %ax,%ds 
	
 # 0 "" 2
/NO_APP
	movl	%ebx, %eax
	movl	%eax, -12(%ebp)
L59:
	movl	__ZN4Util11MODE_COMMONE, %eax
	movl	%eax, 4(%esp)
	movl	$LC18, (%esp)
	call	__ZN4Util8printStrEPKci
	movl	__ZN4Util11SEG_CURRENTE, %eax
	cmpl	%eax, -16(%ebp)
	je	L60
	movl	-12(%ebp), %eax
/APP
 # 333 "interrupts.cpp" 1
	mov %ax,%ds 
	
 # 0 "" 2
/NO_APP
L60:
/APP
 # 334 "interrupts.cpp" 1
	leave 
	iret 
	
 # 0 "" 2
/NO_APP
	nop
	addl	$36, %esp
	popl	%ebx
	popl	%ebp
	ret
	.section .rdata,"dr"
LC19:
	.ascii "int 0x14.\12\0"
	.text
	.globl	_int0x14
	.def	_int0x14;	.scl	2;	.type	32;	.endef
_int0x14:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$36, %esp
	movl	$0, 8(%esp)
	movl	$0, 4(%esp)
	movl	$3, (%esp)
	call	__ZN4Util7makeSelEiii
	cwtl
	movl	%eax, -16(%ebp)
	movl	__ZN4Util11SEG_CURRENTE, %eax
	cmpl	%eax, -16(%ebp)
	je	L62
	movl	-16(%ebp), %eax
/APP
 # 344 "interrupts.cpp" 1
	mov %ds,%ebx
	movw %ax,%ds 
	
 # 0 "" 2
/NO_APP
	movl	%ebx, %eax
	movl	%eax, -12(%ebp)
L62:
	movl	__ZN4Util11MODE_COMMONE, %eax
	movl	%eax, 4(%esp)
	movl	$LC19, (%esp)
	call	__ZN4Util8printStrEPKci
	movl	__ZN4Util11SEG_CURRENTE, %eax
	cmpl	%eax, -16(%ebp)
	je	L63
	movl	-12(%ebp), %eax
/APP
 # 346 "interrupts.cpp" 1
	mov %ax,%ds 
	
 # 0 "" 2
/NO_APP
L63:
/APP
 # 347 "interrupts.cpp" 1
	leave 
	iret 
	
 # 0 "" 2
/NO_APP
	nop
	addl	$36, %esp
	popl	%ebx
	popl	%ebp
	ret
	.section .rdata,"dr"
LC20:
	.ascii "int 0x15.\12\0"
	.text
	.globl	_int0x15
	.def	_int0x15;	.scl	2;	.type	32;	.endef
_int0x15:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$36, %esp
	movl	$0, 8(%esp)
	movl	$0, 4(%esp)
	movl	$3, (%esp)
	call	__ZN4Util7makeSelEiii
	cwtl
	movl	%eax, -16(%ebp)
	movl	__ZN4Util11SEG_CURRENTE, %eax
	cmpl	%eax, -16(%ebp)
	je	L65
	movl	-16(%ebp), %eax
/APP
 # 357 "interrupts.cpp" 1
	mov %ds,%ebx
	movw %ax,%ds 
	
 # 0 "" 2
/NO_APP
	movl	%ebx, %eax
	movl	%eax, -12(%ebp)
L65:
	movl	__ZN4Util11MODE_COMMONE, %eax
	movl	%eax, 4(%esp)
	movl	$LC20, (%esp)
	call	__ZN4Util8printStrEPKci
	movl	__ZN4Util11SEG_CURRENTE, %eax
	cmpl	%eax, -16(%ebp)
	je	L66
	movl	-12(%ebp), %eax
/APP
 # 359 "interrupts.cpp" 1
	mov %ax,%ds 
	
 # 0 "" 2
/NO_APP
L66:
/APP
 # 360 "interrupts.cpp" 1
	leave 
	iret 
	
 # 0 "" 2
/NO_APP
	nop
	addl	$36, %esp
	popl	%ebx
	popl	%ebp
	ret
	.section .rdata,"dr"
LC21:
	.ascii "int 0x16.\12\0"
	.text
	.globl	_int0x16
	.def	_int0x16;	.scl	2;	.type	32;	.endef
_int0x16:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$36, %esp
	movl	$0, 8(%esp)
	movl	$0, 4(%esp)
	movl	$3, (%esp)
	call	__ZN4Util7makeSelEiii
	cwtl
	movl	%eax, -16(%ebp)
	movl	__ZN4Util11SEG_CURRENTE, %eax
	cmpl	%eax, -16(%ebp)
	je	L68
	movl	-16(%ebp), %eax
/APP
 # 370 "interrupts.cpp" 1
	mov %ds,%ebx
	movw %ax,%ds 
	
 # 0 "" 2
/NO_APP
	movl	%ebx, %eax
	movl	%eax, -12(%ebp)
L68:
	movl	__ZN4Util11MODE_COMMONE, %eax
	movl	%eax, 4(%esp)
	movl	$LC21, (%esp)
	call	__ZN4Util8printStrEPKci
	movl	__ZN4Util11SEG_CURRENTE, %eax
	cmpl	%eax, -16(%ebp)
	je	L69
	movl	-12(%ebp), %eax
/APP
 # 372 "interrupts.cpp" 1
	mov %ax,%ds 
	
 # 0 "" 2
/NO_APP
L69:
/APP
 # 373 "interrupts.cpp" 1
	leave 
	iret 
	
 # 0 "" 2
/NO_APP
	nop
	addl	$36, %esp
	popl	%ebx
	popl	%ebp
	ret
	.section .rdata,"dr"
LC22:
	.ascii "int 0x17.\12\0"
	.text
	.globl	_int0x17
	.def	_int0x17;	.scl	2;	.type	32;	.endef
_int0x17:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$36, %esp
	movl	$0, 8(%esp)
	movl	$0, 4(%esp)
	movl	$3, (%esp)
	call	__ZN4Util7makeSelEiii
	cwtl
	movl	%eax, -16(%ebp)
	movl	__ZN4Util11SEG_CURRENTE, %eax
	cmpl	%eax, -16(%ebp)
	je	L71
	movl	-16(%ebp), %eax
/APP
 # 383 "interrupts.cpp" 1
	mov %ds,%ebx
	movw %ax,%ds 
	
 # 0 "" 2
/NO_APP
	movl	%ebx, %eax
	movl	%eax, -12(%ebp)
L71:
	movl	__ZN4Util11MODE_COMMONE, %eax
	movl	%eax, 4(%esp)
	movl	$LC22, (%esp)
	call	__ZN4Util8printStrEPKci
	movl	__ZN4Util11SEG_CURRENTE, %eax
	cmpl	%eax, -16(%ebp)
	je	L72
	movl	-12(%ebp), %eax
/APP
 # 385 "interrupts.cpp" 1
	mov %ax,%ds 
	
 # 0 "" 2
/NO_APP
L72:
/APP
 # 386 "interrupts.cpp" 1
	leave 
	iret 
	
 # 0 "" 2
/NO_APP
	nop
	addl	$36, %esp
	popl	%ebx
	popl	%ebp
	ret
	.section .rdata,"dr"
LC23:
	.ascii "int 0x18.\12\0"
	.text
	.globl	_int0x18
	.def	_int0x18;	.scl	2;	.type	32;	.endef
_int0x18:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$36, %esp
	movl	$0, 8(%esp)
	movl	$0, 4(%esp)
	movl	$3, (%esp)
	call	__ZN4Util7makeSelEiii
	cwtl
	movl	%eax, -16(%ebp)
	movl	__ZN4Util11SEG_CURRENTE, %eax
	cmpl	%eax, -16(%ebp)
	je	L74
	movl	-16(%ebp), %eax
/APP
 # 396 "interrupts.cpp" 1
	mov %ds,%ebx
	movw %ax,%ds 
	
 # 0 "" 2
/NO_APP
	movl	%ebx, %eax
	movl	%eax, -12(%ebp)
L74:
	movl	__ZN4Util11MODE_COMMONE, %eax
	movl	%eax, 4(%esp)
	movl	$LC23, (%esp)
	call	__ZN4Util8printStrEPKci
	movl	__ZN4Util11SEG_CURRENTE, %eax
	cmpl	%eax, -16(%ebp)
	je	L75
	movl	-12(%ebp), %eax
/APP
 # 398 "interrupts.cpp" 1
	mov %ax,%ds 
	
 # 0 "" 2
/NO_APP
L75:
/APP
 # 399 "interrupts.cpp" 1
	leave 
	iret 
	
 # 0 "" 2
/NO_APP
	nop
	addl	$36, %esp
	popl	%ebx
	popl	%ebp
	ret
	.section .rdata,"dr"
LC24:
	.ascii "int 0x19.\12\0"
	.text
	.globl	_int0x19
	.def	_int0x19;	.scl	2;	.type	32;	.endef
_int0x19:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$36, %esp
	movl	$0, 8(%esp)
	movl	$0, 4(%esp)
	movl	$3, (%esp)
	call	__ZN4Util7makeSelEiii
	cwtl
	movl	%eax, -16(%ebp)
	movl	__ZN4Util11SEG_CURRENTE, %eax
	cmpl	%eax, -16(%ebp)
	je	L77
	movl	-16(%ebp), %eax
/APP
 # 409 "interrupts.cpp" 1
	mov %ds,%ebx
	movw %ax,%ds 
	
 # 0 "" 2
/NO_APP
	movl	%ebx, %eax
	movl	%eax, -12(%ebp)
L77:
	movl	__ZN4Util11MODE_COMMONE, %eax
	movl	%eax, 4(%esp)
	movl	$LC24, (%esp)
	call	__ZN4Util8printStrEPKci
	movl	__ZN4Util11SEG_CURRENTE, %eax
	cmpl	%eax, -16(%ebp)
	je	L78
	movl	-12(%ebp), %eax
/APP
 # 411 "interrupts.cpp" 1
	mov %ax,%ds 
	
 # 0 "" 2
/NO_APP
L78:
/APP
 # 412 "interrupts.cpp" 1
	leave 
	iret 
	
 # 0 "" 2
/NO_APP
	nop
	addl	$36, %esp
	popl	%ebx
	popl	%ebp
	ret
	.section .rdata,"dr"
LC25:
	.ascii "int 0x1a.\12\0"
	.text
	.globl	_int0x1a
	.def	_int0x1a;	.scl	2;	.type	32;	.endef
_int0x1a:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$36, %esp
	movl	$0, 8(%esp)
	movl	$0, 4(%esp)
	movl	$3, (%esp)
	call	__ZN4Util7makeSelEiii
	cwtl
	movl	%eax, -16(%ebp)
	movl	__ZN4Util11SEG_CURRENTE, %eax
	cmpl	%eax, -16(%ebp)
	je	L80
	movl	-16(%ebp), %eax
/APP
 # 422 "interrupts.cpp" 1
	mov %ds,%ebx
	movw %ax,%ds 
	
 # 0 "" 2
/NO_APP
	movl	%ebx, %eax
	movl	%eax, -12(%ebp)
L80:
	movl	__ZN4Util11MODE_COMMONE, %eax
	movl	%eax, 4(%esp)
	movl	$LC25, (%esp)
	call	__ZN4Util8printStrEPKci
	movl	__ZN4Util11SEG_CURRENTE, %eax
	cmpl	%eax, -16(%ebp)
	je	L81
	movl	-12(%ebp), %eax
/APP
 # 424 "interrupts.cpp" 1
	mov %ax,%ds 
	
 # 0 "" 2
/NO_APP
L81:
/APP
 # 425 "interrupts.cpp" 1
	leave 
	iret 
	
 # 0 "" 2
/NO_APP
	nop
	addl	$36, %esp
	popl	%ebx
	popl	%ebp
	ret
	.section .rdata,"dr"
LC26:
	.ascii "int 0x1b.\12\0"
	.text
	.globl	_int0x1b
	.def	_int0x1b;	.scl	2;	.type	32;	.endef
_int0x1b:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$36, %esp
	movl	$0, 8(%esp)
	movl	$0, 4(%esp)
	movl	$3, (%esp)
	call	__ZN4Util7makeSelEiii
	cwtl
	movl	%eax, -16(%ebp)
	movl	__ZN4Util11SEG_CURRENTE, %eax
	cmpl	%eax, -16(%ebp)
	je	L83
	movl	-16(%ebp), %eax
/APP
 # 435 "interrupts.cpp" 1
	mov %ds,%ebx
	movw %ax,%ds 
	
 # 0 "" 2
/NO_APP
	movl	%ebx, %eax
	movl	%eax, -12(%ebp)
L83:
	movl	__ZN4Util11MODE_COMMONE, %eax
	movl	%eax, 4(%esp)
	movl	$LC26, (%esp)
	call	__ZN4Util8printStrEPKci
	movl	__ZN4Util11SEG_CURRENTE, %eax
	cmpl	%eax, -16(%ebp)
	je	L84
	movl	-12(%ebp), %eax
/APP
 # 437 "interrupts.cpp" 1
	mov %ax,%ds 
	
 # 0 "" 2
/NO_APP
L84:
/APP
 # 438 "interrupts.cpp" 1
	leave 
	iret 
	
 # 0 "" 2
/NO_APP
	nop
	addl	$36, %esp
	popl	%ebx
	popl	%ebp
	ret
	.section .rdata,"dr"
LC27:
	.ascii "int 0x1c.\12\0"
	.text
	.globl	_int0x1c
	.def	_int0x1c;	.scl	2;	.type	32;	.endef
_int0x1c:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$36, %esp
	movl	$0, 8(%esp)
	movl	$0, 4(%esp)
	movl	$3, (%esp)
	call	__ZN4Util7makeSelEiii
	cwtl
	movl	%eax, -16(%ebp)
	movl	__ZN4Util11SEG_CURRENTE, %eax
	cmpl	%eax, -16(%ebp)
	je	L86
	movl	-16(%ebp), %eax
/APP
 # 448 "interrupts.cpp" 1
	mov %ds,%ebx
	movw %ax,%ds 
	
 # 0 "" 2
/NO_APP
	movl	%ebx, %eax
	movl	%eax, -12(%ebp)
L86:
	movl	__ZN4Util11MODE_COMMONE, %eax
	movl	%eax, 4(%esp)
	movl	$LC27, (%esp)
	call	__ZN4Util8printStrEPKci
	movl	__ZN4Util11SEG_CURRENTE, %eax
	cmpl	%eax, -16(%ebp)
	je	L87
	movl	-12(%ebp), %eax
/APP
 # 450 "interrupts.cpp" 1
	mov %ax,%ds 
	
 # 0 "" 2
/NO_APP
L87:
/APP
 # 451 "interrupts.cpp" 1
	leave 
	iret 
	
 # 0 "" 2
/NO_APP
	nop
	addl	$36, %esp
	popl	%ebx
	popl	%ebp
	ret
	.section .rdata,"dr"
LC28:
	.ascii "int 0x1d.\12\0"
	.text
	.globl	_int0x1d
	.def	_int0x1d;	.scl	2;	.type	32;	.endef
_int0x1d:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$36, %esp
	movl	$0, 8(%esp)
	movl	$0, 4(%esp)
	movl	$3, (%esp)
	call	__ZN4Util7makeSelEiii
	cwtl
	movl	%eax, -16(%ebp)
	movl	__ZN4Util11SEG_CURRENTE, %eax
	cmpl	%eax, -16(%ebp)
	je	L89
	movl	-16(%ebp), %eax
/APP
 # 461 "interrupts.cpp" 1
	mov %ds,%ebx
	movw %ax,%ds 
	
 # 0 "" 2
/NO_APP
	movl	%ebx, %eax
	movl	%eax, -12(%ebp)
L89:
	movl	__ZN4Util11MODE_COMMONE, %eax
	movl	%eax, 4(%esp)
	movl	$LC28, (%esp)
	call	__ZN4Util8printStrEPKci
	movl	__ZN4Util11SEG_CURRENTE, %eax
	cmpl	%eax, -16(%ebp)
	je	L90
	movl	-12(%ebp), %eax
/APP
 # 463 "interrupts.cpp" 1
	mov %ax,%ds 
	
 # 0 "" 2
/NO_APP
L90:
/APP
 # 464 "interrupts.cpp" 1
	leave 
	iret 
	
 # 0 "" 2
/NO_APP
	nop
	addl	$36, %esp
	popl	%ebx
	popl	%ebp
	ret
	.section .rdata,"dr"
LC29:
	.ascii "int 0x1e.\12\0"
	.text
	.globl	_int0x1e
	.def	_int0x1e;	.scl	2;	.type	32;	.endef
_int0x1e:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$36, %esp
	movl	$0, 8(%esp)
	movl	$0, 4(%esp)
	movl	$3, (%esp)
	call	__ZN4Util7makeSelEiii
	cwtl
	movl	%eax, -16(%ebp)
	movl	__ZN4Util11SEG_CURRENTE, %eax
	cmpl	%eax, -16(%ebp)
	je	L92
	movl	-16(%ebp), %eax
/APP
 # 474 "interrupts.cpp" 1
	mov %ds,%ebx
	movw %ax,%ds 
	
 # 0 "" 2
/NO_APP
	movl	%ebx, %eax
	movl	%eax, -12(%ebp)
L92:
	movl	__ZN4Util11MODE_COMMONE, %eax
	movl	%eax, 4(%esp)
	movl	$LC29, (%esp)
	call	__ZN4Util8printStrEPKci
	movl	__ZN4Util11SEG_CURRENTE, %eax
	cmpl	%eax, -16(%ebp)
	je	L93
	movl	-12(%ebp), %eax
/APP
 # 476 "interrupts.cpp" 1
	mov %ax,%ds 
	
 # 0 "" 2
/NO_APP
L93:
/APP
 # 477 "interrupts.cpp" 1
	leave 
	iret 
	
 # 0 "" 2
/NO_APP
	nop
	addl	$36, %esp
	popl	%ebx
	popl	%ebp
	ret
	.section .rdata,"dr"
LC30:
	.ascii "int 0x1f.\12\0"
	.text
	.globl	_int0x1f
	.def	_int0x1f;	.scl	2;	.type	32;	.endef
_int0x1f:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$36, %esp
	movl	$0, 8(%esp)
	movl	$0, 4(%esp)
	movl	$3, (%esp)
	call	__ZN4Util7makeSelEiii
	cwtl
	movl	%eax, -16(%ebp)
	movl	__ZN4Util11SEG_CURRENTE, %eax
	cmpl	%eax, -16(%ebp)
	je	L95
	movl	-16(%ebp), %eax
/APP
 # 487 "interrupts.cpp" 1
	mov %ds,%ebx
	movw %ax,%ds 
	
 # 0 "" 2
/NO_APP
	movl	%ebx, %eax
	movl	%eax, -12(%ebp)
L95:
	movl	__ZN4Util11MODE_COMMONE, %eax
	movl	%eax, 4(%esp)
	movl	$LC30, (%esp)
	call	__ZN4Util8printStrEPKci
	movl	__ZN4Util11SEG_CURRENTE, %eax
	cmpl	%eax, -16(%ebp)
	je	L96
	movl	-12(%ebp), %eax
/APP
 # 489 "interrupts.cpp" 1
	mov %ax,%ds 
	
 # 0 "" 2
/NO_APP
L96:
/APP
 # 490 "interrupts.cpp" 1
	leave 
	iret 
	
 # 0 "" 2
/NO_APP
	nop
	addl	$36, %esp
	popl	%ebx
	popl	%ebp
	ret
	.globl	__ZN8Int_0x207currentE
	.bss
	.align 4
__ZN8Int_0x207currentE:
	.space 4
/APP
	.text 
	.global _int0x20 
	_int0x20:
	 pusha 
	
/NO_APP
	.text
	.globl	__Z8_int0x20v
	.def	__Z8_int0x20v;	.scl	2;	.type	32;	.endef
__Z8_int0x20v:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	$349472, (%esp)
	call	__ZN4Util10insertMarkEi
	leal	-9(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN8IO_8259AC1Ev
	leal	-9(%ebp), %eax
	movl	$32, 4(%esp)
	movl	$0, (%esp)
	movl	%eax, %ecx
	call	__ZN8IO_8259A8sendOCW2Eii
	subl	$8, %esp
	movl	__ZN8Int_0x207currentE, %eax
	testl	%eax, %eax
	jne	L98
	movl	$1, __ZN8Int_0x207currentE
/APP
 # 515 "interrupts.cpp" 1
	ljmp $0b1001000,$0 
	
 # 0 "" 2
/NO_APP
	jmp	L99
L98:
	movl	$0, __ZN8Int_0x207currentE
/APP
 # 518 "interrupts.cpp" 1
	ljmp $0b101000,$0 
	
 # 0 "" 2
/NO_APP
L99:
/APP
 # 525 "interrupts.cpp" 1
	leave 
	popa 
	iret 
	
 # 0 "" 2
/NO_APP
	leal	-9(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN8IO_8259AD1Ev
	nop
	leave
	ret
/APP
	.text 
	.global _int0x21 
	_int0x21:
	 pusha 
	
	.section .rdata,"dr"
LC31:
	.ascii "->\0"
LC32:
	.ascii "  \0"
/NO_APP
	.text
	.globl	__Z8_int0x21v
	.def	__Z8_int0x21v;	.scl	2;	.type	32;	.endef
__Z8_int0x21v:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$168, %esp
	leal	-64(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN8KeyboardC1Ev
	movl	__ZN4Util11MODE_COMMONE, %edx
	leal	-120(%ebp), %eax
	movl	%edx, 16(%esp)
	movl	$80, 12(%esp)
	movl	$8, 8(%esp)
	movl	$0, 4(%esp)
	movl	$10, (%esp)
	movl	%eax, %ecx
	call	__ZN7PrinterC1Ejjjji
	subl	$20, %esp
	movl	__ZZ8_int0x21vE5lasty, %ecx
	movl	__ZZ8_int0x21vE5lastx, %edx
	leal	-120(%ebp), %eax
	movl	%ecx, 4(%esp)
	movl	%edx, (%esp)
	movl	%eax, %ecx
	call	__ZN7Printer6setPosEii
	subl	$8, %esp
	movl	__ZN8Keyboard9PORT_DATAE, %eax
	movl	%eax, -16(%ebp)
	movl	-16(%ebp), %eax
	movl	%eax, %edx
/APP
 # 367 "libx2.h" 1
	inb %dx,%al 
	
 # 0 "" 2
/NO_APP
	movl	%eax, -20(%ebp)
	movl	-20(%ebp), %eax
	movb	%al, -9(%ebp)
	movzbl	-9(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	$10, 4(%esp)
	movl	$__ZZ8_int0x21vE4save, (%esp)
	call	__ZN4Util10digitToStrEPcji
	movzbl	-9(%ebp), %eax
	testb	%al, %al
	js	L103
	leal	-120(%ebp), %eax
	movl	$__ZZ8_int0x21vE4save, (%esp)
	movl	%eax, %ecx
	call	__ZN7Printer5putszEPc
	subl	$4, %esp
	leal	-120(%ebp), %eax
	movl	$LC31, (%esp)
	movl	%eax, %ecx
	call	__ZN7Printer5putszEPc
	subl	$4, %esp
	movzbl	-9(%ebp), %edx
	leal	-64(%ebp), %eax
	movl	%edx, (%esp)
	movl	%eax, %ecx
	call	__ZN8Keyboard12getAsciiCharEh
	subl	$4, %esp
	movl	%eax, %edx
	leal	-120(%ebp), %eax
	movl	%edx, (%esp)
	movl	%eax, %ecx
	call	__ZN7Printer5putszEPc
	subl	$4, %esp
	leal	-120(%ebp), %eax
	movl	$LC32, (%esp)
	movl	%eax, %ecx
	call	__ZN7Printer5putszEPc
	subl	$4, %esp
	jmp	L104
L103:
	movzbl	-9(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	$10, 4(%esp)
	movl	$__ZZ8_int0x21vE4save, (%esp)
	call	__ZN4Util10digitToHexEPcjj
	leal	-120(%ebp), %eax
	movl	$__ZZ8_int0x21vE4save, (%esp)
	movl	%eax, %ecx
	call	__ZN7Printer5putszEPc
	subl	$4, %esp
	leal	-120(%ebp), %eax
	movl	$LC32, (%esp)
	movl	%eax, %ecx
	call	__ZN7Printer5putszEPc
	subl	$4, %esp
L104:
	movl	-104(%ebp), %eax
	movl	%eax, __ZZ8_int0x21vE5lastx
	movl	-100(%ebp), %eax
	movl	%eax, __ZZ8_int0x21vE5lasty
	movl	__ZN8Keyboard8PORT_PPIE, %eax
	movl	%eax, -44(%ebp)
	movl	-44(%ebp), %eax
	movl	%eax, %edx
/APP
 # 367 "libx2.h" 1
	inb %dx,%al 
	
 # 0 "" 2
/NO_APP
	movl	%eax, -48(%ebp)
	movl	-48(%ebp), %eax
	movl	%eax, -52(%ebp)
	movl	-52(%ebp), %eax
	orb	$-128, %al
	movl	%eax, %edx
	movl	__ZN8Keyboard8PORT_PPIE, %eax
	movl	%eax, -56(%ebp)
	movl	%edx, -60(%ebp)
	movl	-56(%ebp), %edx
	movl	-60(%ebp), %eax
/APP
 # 357 "libx2.h" 1
	outb %al,%dx 
	
 # 0 "" 2
/NO_APP
	movl	__ZN8Keyboard8PORT_PPIE, %eax
	movl	%eax, -24(%ebp)
	movl	-24(%ebp), %eax
	movl	%eax, %edx
/APP
 # 367 "libx2.h" 1
	inb %dx,%al 
	
 # 0 "" 2
/NO_APP
	movl	%eax, -28(%ebp)
	movl	-28(%ebp), %eax
	movl	%eax, -32(%ebp)
	movl	-32(%ebp), %eax
	andl	$127, %eax
	movl	%eax, %edx
	movl	__ZN8Keyboard8PORT_PPIE, %eax
	movl	%eax, -36(%ebp)
	movl	%edx, -40(%ebp)
	movl	-36(%ebp), %edx
	movl	-40(%ebp), %eax
/APP
 # 357 "libx2.h" 1
	outb %al,%dx 
	
 # 0 "" 2
/NO_APP
	leal	-121(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN8IO_8259AC1Ev
	leal	-121(%ebp), %eax
	movl	$32, 4(%esp)
	movl	$0, (%esp)
	movl	%eax, %ecx
	call	__ZN8IO_8259A8sendOCW2Eii
	subl	$8, %esp
/APP
 # 601 "interrupts.cpp" 1
	leave 
	popa 
	iret 
	
 # 0 "" 2
/NO_APP
	leal	-121(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN8IO_8259AD1Ev
	leal	-120(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN7PrinterD1Ev
	leal	-64(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN8KeyboardD1Ev
	nop
	leave
	ret
	.globl	_int0x24
	.def	_int0x24;	.scl	2;	.type	32;	.endef
_int0x24:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$52, %esp
	movl	$349476, (%esp)
	call	__ZN4Util10insertMarkEi
	movl	%edx, %eax
	movl	%ecx, -12(%ebp)
	movl	%ebx, -16(%ebp)
	movl	%eax, -20(%ebp)
	movl	-12(%ebp), %eax
	movl	%eax, -24(%ebp)
	movl	__ZN4Util11SEG_CURRENTE, %eax
	cmpl	%eax, -24(%ebp)
	je	L110
	movl	-24(%ebp), %eax
/APP
 # 300 "libx2.h" 1
	mov %ds,%bx 
	mov %ax,%ds 
	
 # 0 "" 2
/NO_APP
	movl	%ebx, %eax
	movl	%eax, -36(%ebp)
L110:
	movl	-16(%ebp), %eax
	movl	-20(%ebp), %edx
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
	call	__ZN4Util8printStrEPKci
	movl	-36(%ebp), %eax
	movl	-12(%ebp), %edx
	movl	%edx, -28(%ebp)
	movl	%eax, -32(%ebp)
	movl	__ZN4Util11SEG_CURRENTE, %eax
	cmpl	%eax, -28(%ebp)
	je	L111
	movl	-32(%ebp), %eax
/APP
 # 307 "libx2.h" 1
	mov %ax,%ds 
	
 # 0 "" 2
/NO_APP
L111:
/APP
 # 344 "libx2.h" 1
	leave 
	iret 
	
 # 0 "" 2
/NO_APP
	nop
	addl	$52, %esp
	popl	%ebx
	popl	%ebp
	ret
	.globl	_int0x25
	.def	_int0x25;	.scl	2;	.type	32;	.endef
_int0x25:
	pushl	%ebp
	movl	%esp, %ebp
/APP
 # 639 "interrupts.cpp" 1
	pusha 
	
 # 0 "" 2
 # 644 "interrupts.cpp" 1
	mov 4*3(%ebp),%eax 
	or $0x200,%eax 
	mov %eax,4*3(%ebp) 
	
 # 0 "" 2
 # 645 "interrupts.cpp" 1
	popa 
	
 # 0 "" 2
 # 646 "interrupts.cpp" 1
	leave 
	iret 
	
 # 0 "" 2
/NO_APP
	nop
	popl	%ebp
	ret
	.section .rdata,"dr"
LC33:
	.ascii "Default int process called.\12\0"
	.text
	.globl	_intDefault
	.def	_intDefault;	.scl	2;	.type	32;	.endef
_intDefault:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$52, %esp
	movl	$0, 8(%esp)
	movl	$0, 4(%esp)
	movl	$3, (%esp)
	call	__ZN4Util7makeSelEiii
	cwtl
	movl	%eax, -12(%ebp)
	movl	-12(%ebp), %eax
	movl	%eax, -16(%ebp)
	movl	__ZN4Util11SEG_CURRENTE, %eax
	cmpl	%eax, -16(%ebp)
	je	L114
	movl	-16(%ebp), %eax
/APP
 # 300 "libx2.h" 1
	mov %ds,%bx 
	mov %ax,%ds 
	
 # 0 "" 2
/NO_APP
	movl	%ebx, %eax
	movl	%eax, -28(%ebp)
L114:
	movl	__ZN4Util11MODE_COMMONE, %eax
	movl	%eax, 4(%esp)
	movl	$LC33, (%esp)
	call	__ZN4Util8printStrEPKci
	movl	-28(%ebp), %eax
	movl	-12(%ebp), %edx
	movl	%edx, -20(%ebp)
	movl	%eax, -24(%ebp)
	movl	__ZN4Util11SEG_CURRENTE, %eax
	cmpl	%eax, -20(%ebp)
	je	L115
	movl	-24(%ebp), %eax
/APP
 # 307 "libx2.h" 1
	mov %ax,%ds 
	
 # 0 "" 2
/NO_APP
L115:
	movl	$354185, (%esp)
	call	__ZN4Util10insertMarkEi
/APP
 # 344 "libx2.h" 1
	leave 
	iret 
	
 # 0 "" 2
/NO_APP
	nop
	addl	$52, %esp
	popl	%ebx
	popl	%ebp
	ret
	.globl	__ZN17InterruptsManager12intAddressesE
	.bss
	.align 4
__ZN17InterruptsManager12intAddressesE:
	.space 1
	.globl	__ZN17InterruptsManager6intLenE
	.align 4
__ZN17InterruptsManager6intLenE:
	.space 4
	.text
	.align 2
	.globl	__ZN17InterruptsManagerC2Ev
	.def	__ZN17InterruptsManagerC2Ev;	.scl	2;	.type	32;	.endef
__ZN17InterruptsManagerC2Ev:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	%ecx, -4(%ebp)
	nop
	leave
	ret
	.globl	__ZN17InterruptsManagerC1Ev
	.def	__ZN17InterruptsManagerC1Ev;	.scl	2;	.type	32;	.endef
	.set	__ZN17InterruptsManagerC1Ev,__ZN17InterruptsManagerC2Ev
	.align 2
	.globl	__ZN17InterruptsManagerD2Ev
	.def	__ZN17InterruptsManagerD2Ev;	.scl	2;	.type	32;	.endef
__ZN17InterruptsManagerD2Ev:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	%ecx, -4(%ebp)
	nop
	leave
	ret
	.globl	__ZN17InterruptsManagerD1Ev
	.def	__ZN17InterruptsManagerD1Ev;	.scl	2;	.type	32;	.endef
	.set	__ZN17InterruptsManagerD1Ev,__ZN17InterruptsManagerD2Ev
	.align 2
	.globl	__ZN17InterruptsManager10getIntAddrEj
	.def	__ZN17InterruptsManager10getIntAddrEj;	.scl	2;	.type	32;	.endef
__ZN17InterruptsManager10getIntAddrEj:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	%ecx, -4(%ebp)
	nop
	leave
	ret	$4
	.align 2
	.globl	__ZN17InterruptsManager10setIntAddrEj
	.def	__ZN17InterruptsManager10setIntAddrEj;	.scl	2;	.type	32;	.endef
__ZN17InterruptsManager10setIntAddrEj:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	%ecx, -4(%ebp)
	nop
	leave
	ret	$4
.lcomm __ZZ8_int0x21vE5lasty,4,4
.lcomm __ZZ8_int0x21vE5lastx,4,4
.lcomm __ZZ8_int0x21vE4save,10,4
	.data
	.align 4
__ZZ8_int0x21vE5index:
	.long	-1
.lcomm __ZZ8_int0x21vE5lasts,4,4
.lcomm __ZZ8_int0x21vE5times,4,4
	.ident	"GCC: (GNU) 5.4.0"
	.def	__ZN4Util10insertMarkEi;	.scl	2;	.type	32;	.endef
	.def	__ZN4Util7makeSelEiii;	.scl	2;	.type	32;	.endef
	.def	__ZN4Util8printStrEPKci;	.scl	2;	.type	32;	.endef
	.def	__ZN8IO_8259AC1Ev;	.scl	2;	.type	32;	.endef
	.def	__ZN8IO_8259A8sendOCW2Eii;	.scl	2;	.type	32;	.endef
	.def	__ZN8IO_8259AD1Ev;	.scl	2;	.type	32;	.endef
	.def	__ZN8KeyboardC1Ev;	.scl	2;	.type	32;	.endef
	.def	__ZN7PrinterC1Ejjjji;	.scl	2;	.type	32;	.endef
	.def	__ZN7Printer6setPosEii;	.scl	2;	.type	32;	.endef
	.def	__ZN4Util10digitToStrEPcji;	.scl	2;	.type	32;	.endef
	.def	__ZN7Printer5putszEPc;	.scl	2;	.type	32;	.endef
	.def	__ZN8Keyboard12getAsciiCharEh;	.scl	2;	.type	32;	.endef
	.def	__ZN4Util10digitToHexEPcjj;	.scl	2;	.type	32;	.endef
	.def	__ZN7PrinterD1Ev;	.scl	2;	.type	32;	.endef
	.def	__ZN8KeyboardD1Ev;	.scl	2;	.type	32;	.endef
