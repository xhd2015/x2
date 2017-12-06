	.file	"main.cpp"
	.globl	a
	.data
	.align 16
	.type	a, @object
	.size	a, 24
a:
	.long	2
	.long	3
	.long	5
	.long	8
	.long	13
	.long	21
	.globl	m
	.align 4
	.type	m, @object
	.size	m, 4
m:
	.long	2
	.globl	n
	.align 4
	.type	n, @object
	.size	n, 4
n:
	.long	5
	.section	.rodata
.LC0:
	.string	"rax %d\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
#APP
# 42 "main.cpp" 1
	#mov  $a,%rbx    #ebx作为指向当前所要加的数的指针
	#add    m(%rip),%rbx
	mov    $2,%rbx
	xor     %rax,%rax  #eax将作为累加器
	mov n(%rip),%rcx
	sub  m(%rip),%rcx  #ecx = n – m作为计数器
	.add_one_integer:
	#add  (%rbx),%rax                #累加
	mov	a(,%rbx,4),%eax 
	add  $4,%rbx                    #ebx指向下一个数
	#loop .add_one_integer
	
# 0 "" 2
#NO_APP
	movl	%eax, -4(%rbp)
	movl	$9, m(%rip)
	movl	-4(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.4) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
