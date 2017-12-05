

#include <cstdio>

/*
__asm__(".section .rdata,\"dr\"\n\t");
__asm__("a:\n\t"
	".long  2,3,5,8,13,21 \n\t"
	"size = 6 \n\t"
	"m = 2 \n\t"
	"n = 5 \n\t");
*/
int a[]={2,3,5,8,13,21};
int m=1;
int n=5;
int main()
{

	int eax;
	/*
	printf("sizeof(int)= %d\n",sizeof(int));
	int s=0;
	s+=a[0];
	int j=5;
	s+=a[j];
	*/
	__asm__ __volatile__(
	"xor %%rbx,%%rbx \n\t"
	"xor %%rax,%%rax \n\t"
	"mov  $a,%%rbx    #ebx作为指向当前所要加的数的指针\n\t"
	"mov  m(%%rip),%%eax \n\t"
	"shl	$2,%%eax \n\t"
	"add   %%rax,%%rbx\n\t"
	"xor	%%rcx,%%rcx \n\t"
	"mov n(%%rip),%%ecx\n\t"
	"mov m(%%rip),%%eax \n\t"
	"sub  %%rax,%%rcx  #ecx = n – m作为计数器\n\t"
	"xor     %%rax,%%rax  #eax将作为累加器\n\t"
	".add_one_integer:\n\t"
	"#add  (%%rbx),%%eax                #累加\n\t"
	"mov	(,%%rbx),%%eax \n\t"
	"add  $4,%%rbx                    #ebx指向下一个数\n\t"
	"#loop .add_one_integer\n\t"
	:"=a"(eax)
	:
	:"rcx"
	);
	printf("rax %d\n",eax);
/*
	__asm__("popq %rax \n\t");
*/

}
