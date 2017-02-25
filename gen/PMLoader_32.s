	.file	"PMLoader.cpp"
/APP
	.code32 
	
/NO_APP
	.globl	__ZN8PMLoader8SAFE_SEGE
	.section .rdata,"dr"
	.align 4
__ZN8PMLoader8SAFE_SEGE:
	.long	256
	.globl	__ZN8PMLoader7SECSIZEE
	.align 4
__ZN8PMLoader7SECSIZEE:
	.long	512
	.globl	__ZN8PMLoader11STACK_STARTE
	.align 4
__ZN8PMLoader11STACK_STARTE:
	.space 4
	.globl	__ZN8PMLoader10STACK_SIZEE
	.align 4
__ZN8PMLoader10STACK_SIZEE:
	.long	2048
	.globl	__ZN8PMLoader9IDT_STARTE
	.align 4
__ZN8PMLoader9IDT_STARTE:
	.long	2048
	.globl	__ZN8PMLoader8IDT_SIZEE
	.align 4
__ZN8PMLoader8IDT_SIZEE:
	.long	512
	.globl	__ZN8PMLoader9GDT_STARTE
	.align 4
__ZN8PMLoader9GDT_STARTE:
	.long	2560
	.globl	__ZN8PMLoader8GDT_SIZEE
	.align 4
__ZN8PMLoader8GDT_SIZEE:
	.long	1024
	.globl	__ZN8PMLoader13TSS_AREA_SIZEE
	.align 4
__ZN8PMLoader13TSS_AREA_SIZEE:
	.long	1024
	.globl	__ZN8PMLoader14TSS_AREA_STARTE
	.align 4
__ZN8PMLoader14TSS_AREA_STARTE:
	.long	3584
	.globl	__ZN8PMLoader12TSS_MIN_SIZEE
	.align 4
__ZN8PMLoader12TSS_MIN_SIZEE:
	.long	104
	.globl	__ZN8PMLoader14FREE_HEAP_SIZEE
	.align 4
__ZN8PMLoader14FREE_HEAP_SIZEE:
	.long	2560
	.globl	__ZN8PMLoader15FREE_HEAP_STARTE
	.align 4
__ZN8PMLoader15FREE_HEAP_STARTE:
	.long	4608
	.globl	__ZN8PMLoader10CODE_STARTE
	.align 4
__ZN8PMLoader10CODE_STARTE:
	.long	7168
	.globl	__ZN8PMLoader8CODE_SEGE
	.align 4
__ZN8PMLoader8CODE_SEGE:
	.space 4
	.globl	__ZN8PMLoader10CODE_LIMITE
	.align 4
__ZN8PMLoader10CODE_LIMITE:
	.long	1048575
	.globl	__ZN8PMLoader6JMPSEGE
	.align 4
__ZN8PMLoader6JMPSEGE:
	.long	16
	.globl	__ZN8PMLoader6DRIVERE
	.align 4
__ZN8PMLoader6DRIVERE:
	.space 4
	.globl	__ZN8PMLoader12REAL_SECNUMSE
	.align 4
__ZN8PMLoader12REAL_SECNUMSE:
	.long	16
	.globl	__ZN8PMLoader17PROTECTED_SECNUMSE
	.align 4
__ZN8PMLoader17PROTECTED_SECNUMSE:
	.long	60
	.globl	__ZN8PMLoader8TEMP_SEGE
	.align 4
__ZN8PMLoader8TEMP_SEGE:
	.long	2560
	.ident	"GCC: (GNU) 5.4.0"
