

.globl _start,printf
.section .rdata
fmt:
	.ascii	"eax = %d\n\0"
a:
	.long 2,3,5,8,13,21
size = 6
m = 2
n = 5
.text
_start:
mov  $a,%ebx 	#ebx作为指向当前所要加的数的指针
add	  $m,%ebx	
xor	%eax,%eax  #eax将作为累加器
mov $n,%ecx
sub  $m,%ecx  #ecx = n – m作为计数器 
.add_one_integer:
add  (%ebx),%eax		#累加
add  $4,%ebx			#ebx指向下一个数
loop .add_one_integer

pushq %rax
pushq $fmt
call printf
addq	$8,%rsp
leave
ret
