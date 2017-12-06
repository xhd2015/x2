	.file	"use_implement.cpp"
	.def	___gxx_personality_sj0;	.scl	2;	.type	32;	.endef
	.def	__Unwind_SjLj_Register;	.scl	2;	.type	32;	.endef
	.def	__Unwind_SjLj_Unregister;	.scl	2;	.type	32;	.endef
	.text
	.globl	__Z4testv
	.def	__Z4testv;	.scl	2;	.type	32;	.endef
__Z4testv:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$108, %esp
	movl	$___gxx_personality_sj0, -68(%ebp)
	movl	$LLSDA0, -64(%ebp)
	leal	-60(%ebp), %eax
	leal	-24(%ebp), %ebx
	movl	%ebx, (%eax)
	movl	$L3, %edx
	movl	%edx, 4(%eax)
	movl	%esp, 8(%eax)
	leal	-92(%ebp), %eax
	movl	%eax, (%esp)
	call	__Unwind_SjLj_Register
	leal	-29(%ebp), %eax
	movl	$-1, -88(%ebp)
	movl	%eax, %ecx
	call	__ZN4PackIiEC1Ev
	leal	-29(%ebp), %eax
	movl	$1, -88(%ebp)
	movl	%eax, %ecx
	call	__ZN4PackIiE3getEv
	movl	%eax, -28(%ebp)
	leal	-29(%ebp), %eax
	movl	$-1, -88(%ebp)
	movl	%eax, %ecx
	call	__ZN4PackIiED1Ev
	jmp	L5
L3:
	leal	24(%ebp), %ebp
	movl	-84(%ebp), %eax
	movl	%eax, -96(%ebp)
	leal	-29(%ebp), %eax
	movl	$0, -88(%ebp)
	movl	%eax, %ecx
	call	__ZN4PackIiED1Ev
	movl	-96(%ebp), %eax
	movl	%eax, (%esp)
	movl	$-1, -88(%ebp)
	call	__Unwind_SjLj_Resume
L5:
	leal	-92(%ebp), %eax
	movl	%eax, (%esp)
	call	__Unwind_SjLj_Unregister
	addl	$108, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.section	.gcc_except_table,"w"
LLSDA0:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 LLSDACSE0-LLSDACSB0
LLSDACSB0:
	.uleb128 0
	.uleb128 0
LLSDACSE0:
	.text
	.ident	"GCC: (GNU) 5.4.0"
	.def	__ZN4PackIiEC1Ev;	.scl	2;	.type	32;	.endef
	.def	__ZN4PackIiE3getEv;	.scl	2;	.type	32;	.endef
	.def	__ZN4PackIiED1Ev;	.scl	2;	.type	32;	.endef
	.def	__Unwind_SjLj_Resume;	.scl	2;	.type	32;	.endef
