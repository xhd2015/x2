	.file	"PMLoader.cpp"
/APP
	.code16gcc 
	
/NO_APP
	.text
	.align 2
	.globl	__ZN8PMLoaderC2Ev
	.def	__ZN8PMLoaderC2Ev;	.scl	2;	.type	32;	.endef
__ZN8PMLoaderC2Ev:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	%ecx, -4(%ebp)
	nop
	leave
	ret
	.globl	__ZN8PMLoaderC1Ev
	.def	__ZN8PMLoaderC1Ev;	.scl	2;	.type	32;	.endef
	.set	__ZN8PMLoaderC1Ev,__ZN8PMLoaderC2Ev
	.align 2
	.globl	__ZN8PMLoaderD2Ev
	.def	__ZN8PMLoaderD2Ev;	.scl	2;	.type	32;	.endef
__ZN8PMLoaderD2Ev:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	%ecx, -4(%ebp)
	nop
	leave
	ret
	.globl	__ZN8PMLoaderD1Ev
	.def	__ZN8PMLoaderD1Ev;	.scl	2;	.type	32;	.endef
	.set	__ZN8PMLoaderD1Ev,__ZN8PMLoaderD2Ev
	.align 2
	.globl	__ZN8PMLoader11readSectorsEiiiiiii
	.def	__ZN8PMLoader11readSectorsEiiiiiii;	.scl	2;	.type	32;	.endef
__ZN8PMLoader11readSectorsEiiiiiii:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$20, %esp
	movl	%ecx, -20(%ebp)
/APP
 # 39 "PMLoader.cpp" 1
	push %es
	mov 4+4*1(%ebp),%eax 
	movw %ax,%es
	movw 4+4*2(%ebp),%bx
	movb 4+4*3(%ebp),%dl 
	movb 4+4*4(%ebp),%dh 
	movw 4+4*5(%ebp),%cx 
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
	ret	$28
	.align 2
	.globl	__ZN8PMLoader9enableA20Ev
	.def	__ZN8PMLoader9enableA20Ev;	.scl	2;	.type	32;	.endef
__ZN8PMLoader9enableA20Ev:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	%ecx, -4(%ebp)
/APP
 # 49 "PMLoader.cpp" 1
	inb $0x92,%al 
	orb $0b00000010,%al 
	outb %al,$0x92 
	
 # 0 "" 2
/NO_APP
	nop
	leave
	ret
	.align 2
	.globl	__ZN8PMLoader7setidtrEsi
	.def	__ZN8PMLoader7setidtrEsi;	.scl	2;	.type	32;	.endef
__ZN8PMLoader7setidtrEsi:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	%ecx, -4(%ebp)
	movl	8(%ebp), %eax
	movw	%ax, -8(%ebp)
/APP
 # 58 "PMLoader.cpp" 1
	movw 4+4*1(%ebp),%ax 
	movw %ax,4+4*1+2(%ebp) 
	lidt 4+4*1+2(%ebp) 
	
 # 0 "" 2
/NO_APP
	nop
	leave
	ret	$8
	.align 2
	.globl	__ZN8PMLoader7setgdtrEsi
	.def	__ZN8PMLoader7setgdtrEsi;	.scl	2;	.type	32;	.endef
__ZN8PMLoader7setgdtrEsi:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	%ecx, -4(%ebp)
	movl	8(%ebp), %eax
	movw	%ax, -8(%ebp)
/APP
 # 66 "PMLoader.cpp" 1
	movw 4+4*1(%ebp),%ax 
	movw %ax,4+4*1+2(%ebp) 
	lgdt 4+4*1+2(%ebp) 
	
 # 0 "" 2
/NO_APP
	nop
	leave
	ret	$8
	.align 2
	.globl	__ZN8PMLoader11mainProcessEv
	.def	__ZN8PMLoader11mainProcessEv;	.scl	2;	.type	32;	.endef
__ZN8PMLoader11mainProcessEv:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	%ecx, -4(%ebp)
	nop
	leave
	ret
	.align 2
	.globl	__ZN8PMLoader7memcopyEiiiii
	.def	__ZN8PMLoader7memcopyEiiiii;	.scl	2;	.type	32;	.endef
__ZN8PMLoader7memcopyEiiiii:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	%ecx, -4(%ebp)
/APP
 # 92 "PMLoader.cpp" 1
	push %es 
	push %ds 
	push %esi 
	push %edi 
	mov 4+4*1(%ebp),%eax 
	movw %ax,%ds
	mov 4+4*2(%ebp),%esi 
	mov 4+4*3(%ebp),%eax 
	movw %ax,%es 
	mov 4+4*4(%ebp),%edi 
	mov 4+4*5(%ebp),%ecx 
	cld 
	rep movsb 
	pop %edi 
	pop %esi 
	pop %ds 
	pop %es 
	
 # 0 "" 2
/NO_APP
	nop
	leave
	ret	$20
	.ident	"GCC: (GNU) 5.4.0"
