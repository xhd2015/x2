	.file	"set.cpp"
/APP
	movzwl %ax,%eax
	
/NO_APP
	.text
	.globl	_int0x24
	.def	_int0x24;	.scl	2;	.type	32;	.endef
_int0x24:
	pushl	%ebp
	movl	%esp, %ebp
/APP
 # 7 "set.cpp" 1
	INT_24: 
	
 # 0 "" 2
 # 11 "set.cpp" 1
	iret 
	
 # 0 "" 2
/NO_APP
	nop
	popl	%ebp
	ret
/APP
	.set _int0x24,INT_24 
	
	.ident	"GCC: (GNU) 5.4.0"
