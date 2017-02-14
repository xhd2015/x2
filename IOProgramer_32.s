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
	out %al,%dx 
	
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
	out %al,%dx 
	
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
	out %al,%dx 
	
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
	out %al,%dx 
	
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
	out %al,%dx 
	
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
	out %al,%dx 
	
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
	subl	$56, %esp
	movl	%ecx, -28(%ebp)
	movl	12(%ebp), %eax
	imull	$1193, %eax, %eax
	movl	%eax, -12(%ebp)
	movl	-28(%ebp), %eax
	movl	$0, 12(%esp)
	movl	$3, 8(%esp)
	movl	$3, 4(%esp)
	movl	$0, (%esp)
	movl	%eax, %ecx
	call	__ZN7IO_825315sendControlByteEiiii
	subl	$16, %esp
	movl	8(%ebp), %eax
	movl	__ZN7IO_82535PORTSE(,%eax,4), %eax
	movl	-12(%ebp), %edx
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
	call	__ZN4Util4outbEii
	movl	-12(%ebp), %eax
	sarl	$8, %eax
	movl	%eax, %edx
	movl	8(%ebp), %eax
	movl	__ZN7IO_82535PORTSE(,%eax,4), %eax
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
	call	__ZN4Util4outbEii
	nop
	leave
	ret	$8
	.align 2
	.globl	__ZN7IO_825312setTimeMicroEij
	.def	__ZN7IO_825312setTimeMicroEij;	.scl	2;	.type	32;	.endef
__ZN7IO_825312setTimeMicroEij:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$56, %esp
	movl	%ecx, -28(%ebp)
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
	movl	-28(%ebp), %eax
	movl	$0, 12(%esp)
	movl	$3, 8(%esp)
	movl	$3, 4(%esp)
	movl	$0, (%esp)
	movl	%eax, %ecx
	call	__ZN7IO_825315sendControlByteEiiii
	subl	$16, %esp
	movl	-12(%ebp), %edx
	movl	8(%ebp), %eax
	movl	__ZN7IO_82535PORTSE(,%eax,4), %eax
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
	call	__ZN4Util4outbEii
	movl	-12(%ebp), %eax
	shrl	$8, %eax
	movl	%eax, %edx
	movl	8(%ebp), %eax
	movl	__ZN7IO_82535PORTSE(,%eax,4), %eax
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
	call	__ZN4Util4outbEii
	nop
	leave
	ret	$8
	.align 2
	.globl	__ZN7IO_825315sendControlByteEiiii
	.def	__ZN7IO_825315sendControlByteEiiii;	.scl	2;	.type	32;	.endef
__ZN7IO_825315sendControlByteEiiii:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	%ecx, -12(%ebp)
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
	movl	%eax, 4(%esp)
	movl	%edx, (%esp)
	call	__ZN4Util4outbEii
	nop
	leave
	ret	$16
	.ident	"GCC: (GNU) 5.4.0"
	.def	__ZN4Util10insertMarkEi;	.scl	2;	.type	32;	.endef
	.def	__ZN4Util4outbEii;	.scl	2;	.type	32;	.endef
