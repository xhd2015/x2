	.file	"extend.cpp"
	.section	.text$_ZN6FatherC2Ei,"x"
	.linkonce discard
	.align 2
	.globl	__ZN6FatherC2Ei
	.def	__ZN6FatherC2Ei;	.scl	2;	.type	32;	.endef
__ZN6FatherC2Ei:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	%ecx, -4(%ebp)
	movl	$__ZTV6Father+8, %edx
	movl	-4(%ebp), %eax
	movl	%edx, (%eax)
	nop
	leave
	ret	$4
	.section	.text$_ZN6Father1tEv,"x"
	.linkonce discard
	.align 2
	.globl	__ZN6Father1tEv
	.def	__ZN6Father1tEv;	.scl	2;	.type	32;	.endef
__ZN6Father1tEv:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	%ecx, -4(%ebp)
	nop
	leave
	ret
	.section	.text$_ZN6Father1vEv,"x"
	.linkonce discard
	.align 2
	.globl	__ZN6Father1vEv
	.def	__ZN6Father1vEv;	.scl	2;	.type	32;	.endef
__ZN6Father1vEv:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	%ecx, -4(%ebp)
	nop
	leave
	ret
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
	subl	$140, %esp
	movl	$___gxx_personality_sj0, -100(%ebp)
	movl	$LLSDA12, -96(%ebp)
	leal	-92(%ebp), %eax
	leal	-24(%ebp), %ebx
	movl	%ebx, (%eax)
	movl	$L6, %edx
	movl	%edx, 4(%eax)
	movl	%esp, 8(%eax)
	leal	-124(%ebp), %eax
	movl	%eax, (%esp)
	call	__Unwind_SjLj_Register
	leal	-48(%ebp), %eax
	movl	$9, (%esp)
	movl	%eax, %ecx
	call	__ZN3SonIiEC1Ei
	subl	$4, %esp
	leal	-68(%ebp), %eax
	movl	$7, (%esp)
	movl	%eax, %ecx
	call	__ZN3SonIiEC1Ei
	subl	$4, %esp
	movl	$0, -56(%ebp)
	movl	$1, -64(%ebp)
	movl	$2, -60(%ebp)
	movl	$3, -52(%ebp)
	leal	-68(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN3SonIiE1tEv
	leal	-68(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN3SonIiE1vEv
	leal	-68(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN6Father1tEv
	leal	-68(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN6Father1vEv
/APP
 # 44 "extend.cpp" 1
	#nothing 
	
 # 0 "" 2
/NO_APP
	movl	-28(%ebp), %eax
	movl	(%eax), %eax
	movl	(%eax), %eax
	movl	-28(%ebp), %edx
	movl	$1, -120(%ebp)
	movl	%edx, %ecx
	call	*%eax
	leal	-68(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN3SonIiED1Ev
	leal	-48(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN3SonIiED1Ev
	jmp	L8
L6:
	leal	24(%ebp), %ebp
	movl	-116(%ebp), %eax
	movl	%eax, -128(%ebp)
	leal	-68(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN3SonIiED1Ev
	movl	-128(%ebp), %eax
	movl	%eax, -128(%ebp)
	leal	-48(%ebp), %eax
	movl	%eax, %ecx
	call	__ZN3SonIiED1Ev
	movl	-128(%ebp), %eax
	movl	%eax, (%esp)
	movl	$-1, -120(%ebp)
	call	__Unwind_SjLj_Resume
L8:
	leal	-124(%ebp), %eax
	movl	%eax, (%esp)
	call	__Unwind_SjLj_Unregister
	leal	-12(%ebp), %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.section	.gcc_except_table,"w"
LLSDA12:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 LLSDACSE12-LLSDACSB12
LLSDACSB12:
	.uleb128 0
	.uleb128 0
LLSDACSE12:
	.text
	.section	.text$_ZN3SonIiEC1Ei,"x"
	.linkonce discard
	.align 2
	.globl	__ZN3SonIiEC1Ei
	.def	__ZN3SonIiEC1Ei;	.scl	2;	.type	32;	.endef
__ZN3SonIiEC1Ei:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	%ecx, -12(%ebp)
	movl	-12(%ebp), %eax
	movl	$5, (%esp)
	movl	%eax, %ecx
	call	__ZN6FatherC2Ei
	subl	$4, %esp
	movl	$__ZTV3SonIiE+8, %edx
	movl	-12(%ebp), %eax
	movl	%edx, (%eax)
	movl	-12(%ebp), %eax
	movl	8(%ebp), %edx
	movl	%edx, 12(%eax)
	nop
	leave
	ret	$4
	.section	.text$_ZN3SonIiED1Ev,"x"
	.linkonce discard
	.align 2
	.globl	__ZN3SonIiED1Ev
	.def	__ZN3SonIiED1Ev;	.scl	2;	.type	32;	.endef
__ZN3SonIiED1Ev:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	%ecx, -4(%ebp)
	movl	$__ZTV3SonIiE+8, %edx
	movl	-4(%ebp), %eax
	movl	%edx, (%eax)
	nop
	leave
	ret
	.section	.text$_ZN3SonIiE1tEv,"x"
	.linkonce discard
	.align 2
	.globl	__ZN3SonIiE1tEv
	.def	__ZN3SonIiE1tEv;	.scl	2;	.type	32;	.endef
__ZN3SonIiE1tEv:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	%ecx, -4(%ebp)
	nop
	leave
	ret
	.section	.text$_ZN3SonIiE1vEv,"x"
	.linkonce discard
	.align 2
	.globl	__ZN3SonIiE1vEv
	.def	__ZN3SonIiE1vEv;	.scl	2;	.type	32;	.endef
__ZN3SonIiE1vEv:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	%ecx, -4(%ebp)
	nop
	leave
	ret
	.globl	__ZTV3SonIiE
	.section	.rdata$_ZTV3SonIiE,"dr"
	.linkonce same_size
	.align 4
__ZTV3SonIiE:
	.long	0
	.long	__ZTI3SonIiE
	.long	__ZN3SonIiE1vEv
	.globl	__ZTV6Father
	.section	.rdata$_ZTV6Father,"dr"
	.linkonce same_size
	.align 4
__ZTV6Father:
	.long	0
	.long	__ZTI6Father
	.long	__ZN6Father1vEv
	.globl	__ZTI3SonIiE
	.section	.rdata$_ZTI3SonIiE,"dr"
	.linkonce same_size
	.align 4
__ZTI3SonIiE:
	.long	__ZTVN10__cxxabiv120__si_class_type_infoE+8
	.long	__ZTS3SonIiE
	.long	__ZTI6Father
	.globl	__ZTS3SonIiE
	.section	.rdata$_ZTS3SonIiE,"dr"
	.linkonce same_size
	.align 4
__ZTS3SonIiE:
	.ascii "3SonIiE\0"
	.globl	__ZTI6Father
	.section	.rdata$_ZTI6Father,"dr"
	.linkonce same_size
	.align 4
__ZTI6Father:
	.long	__ZTVN10__cxxabiv117__class_type_infoE+8
	.long	__ZTS6Father
	.globl	__ZTS6Father
	.section	.rdata$_ZTS6Father,"dr"
	.linkonce same_size
	.align 4
__ZTS6Father:
	.ascii "6Father\0"
	.ident	"GCC: (GNU) 5.4.0"
	.def	__Unwind_SjLj_Resume;	.scl	2;	.type	32;	.endef
