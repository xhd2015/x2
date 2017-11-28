	.file	"exception.cpp"
/APP
	.code32 
	
	.section .rdata,"dr"
LC0:
	.ascii "in test_nothrow %d\12\0"
	.def	___gxx_personality_sj0;	.scl	2;	.type	32;	.endef
	.def	__Unwind_SjLj_Register;	.scl	2;	.type	32;	.endef
	.def	__Unwind_SjLj_Unregister;	.scl	2;	.type	32;	.endef
/NO_APP
	.text
	.globl	__Z12test_nothrowv
	.def	__Z12test_nothrowv;	.scl	2;	.type	32;	.endef
__Z12test_nothrowv:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$104, %esp
	movl	$___gxx_personality_sj0, -52(%ebp)
	movl	$LLSDA7, -48(%ebp)
	leal	-76(%ebp), %eax
	movl	%eax, (%esp)
	call	__Unwind_SjLj_Register
	movl	$10, -12(%ebp)
	movl	-12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$LC0, (%esp)
	movl	$0, -72(%ebp)
	call	_printf
	movl	$20, -12(%ebp)
	nop
	leal	-76(%ebp), %eax
	movl	%eax, (%esp)
	call	__Unwind_SjLj_Unregister
	leave
	ret
	.section	.gcc_except_table,"w"
LLSDA7:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 LLSDACSE7-LLSDACSB7
LLSDACSB7:
LLSDACSE7:
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
	movl	$LLSDA8, -64(%ebp)
	leal	-60(%ebp), %eax
	leal	-24(%ebp), %ecx
	movl	%ecx, (%eax)
	movl	$L6, %edx
	movl	%edx, 4(%eax)
	movl	%esp, 8(%eax)
	leal	-92(%ebp), %eax
	movl	%eax, (%esp)
	call	__Unwind_SjLj_Register
	movl	$9, -28(%ebp)
	movl	_c, %eax
	cmpl	$10, %eax
	jne	L3
	movl	$1, (%esp)
	call	___cxa_allocate_exception
	movl	$0, 8(%esp)
	movl	$__ZTI10Texception, 4(%esp)
	movl	%eax, (%esp)
	movl	$1, -88(%ebp)
	call	___cxa_throw
L3:
	movl	$11, -28(%ebp)
	movl	$20, -32(%ebp)
	movl	$19, -28(%ebp)
	jmp	L8
L6:
	leal	24(%ebp), %ebp
	movl	-84(%ebp), %eax
	movl	-80(%ebp), %edx
	cmpl	$-1, %edx
	je	L5
	movl	%eax, (%esp)
	movl	$-1, -88(%ebp)
	call	__Unwind_SjLj_Resume
L5:
	movl	%eax, (%esp)
	movl	$-1, -88(%ebp)
	call	___cxa_call_unexpected
L8:
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
	.align 4
LLSDA8:
	.byte	0xff
	.byte	0
	.uleb128 LLSDATT8-LLSDATTD8
LLSDATTD8:
	.byte	0x1
	.uleb128 LLSDACSE8-LLSDACSB8
LLSDACSB8:
	.uleb128 0
	.uleb128 0x1
LLSDACSE8:
	.byte	0x7f
	.byte	0
	.align 4
	.long	__ZTI10Texception
LLSDATT8:
	.byte	0x1
	.byte	0
	.text
	.globl	_before_try
	.bss
	.align 4
_before_try:
	.space 4
	.globl	_in_catch
	.align 4
_in_catch:
	.space 4
	.globl	_after_catch
	.align 4
_after_catch:
	.space 4
	.def	___main;	.scl	2;	.type	32;	.endef
	.text
	.globl	_main
	.def	_main;	.scl	2;	.type	32;	.endef
_main:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	andl	$-16, %esp
	subl	$96, %esp
	movl	$___gxx_personality_sj0, 52(%esp)
	movl	$LLSDA9, 56(%esp)
	leal	60(%esp), %eax
	movl	%ebp, (%eax)
	movl	$L15, %edx
	movl	%edx, 4(%eax)
	movl	%esp, 8(%eax)
	leal	28(%esp), %eax
	movl	%eax, (%esp)
	call	__Unwind_SjLj_Register
	call	___main
	movl	$1, _before_try
	movl	$0, 92(%esp)
	movl	$1, 32(%esp)
	call	__Z4testv
L14:
	movl	$3, _after_catch
	movl	$0, %eax
	movl	%eax, 24(%esp)
	jmp	L17
L15:
	movl	36(%esp), %eax
	movl	40(%esp), %edx
	cmpl	$1, %edx
	je	L13
	movl	%eax, (%esp)
	movl	$-1, 32(%esp)
	call	__Unwind_SjLj_Resume
L13:
	movl	%eax, (%esp)
	call	___cxa_begin_catch
	movl	$2, _in_catch
	movl	$1, 88(%esp)
	call	___cxa_end_catch
	jmp	L14
L17:
	leal	28(%esp), %eax
	movl	%eax, (%esp)
	call	__Unwind_SjLj_Unregister
	movl	24(%esp), %eax
	leal	-12(%ebp), %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.section	.gcc_except_table,"w"
	.align 4
LLSDA9:
	.byte	0xff
	.byte	0
	.uleb128 LLSDATT9-LLSDATTD9
LLSDATTD9:
	.byte	0x1
	.uleb128 LLSDACSE9-LLSDACSB9
LLSDACSB9:
	.uleb128 0
	.uleb128 0x1
LLSDACSE9:
	.byte	0x1
	.byte	0
	.align 4
	.long	__ZTI10Texception
LLSDATT9:
	.text
	.globl	__ZTI10Texception
	.section	.rdata$_ZTI10Texception,"dr"
	.linkonce same_size
	.align 4
__ZTI10Texception:
	.long	__ZTVN10__cxxabiv117__class_type_infoE+8
	.long	__ZTS10Texception
	.globl	__ZTS10Texception
	.section	.rdata$_ZTS10Texception,"dr"
	.linkonce same_size
	.align 4
__ZTS10Texception:
	.ascii "10Texception\0"
	.ident	"GCC: (GNU) 5.4.0"
	.def	_printf;	.scl	2;	.type	32;	.endef
	.def	___cxa_allocate_exception;	.scl	2;	.type	32;	.endef
	.def	___cxa_throw;	.scl	2;	.type	32;	.endef
	.def	__Unwind_SjLj_Resume;	.scl	2;	.type	32;	.endef
	.def	___cxa_call_unexpected;	.scl	2;	.type	32;	.endef
	.def	___cxa_begin_catch;	.scl	2;	.type	32;	.endef
	.def	___cxa_end_catch;	.scl	2;	.type	32;	.endef
