#include<cstdio>
#define SEG_CURRENT 0x10000

class Util{
public:
	Util(){}
	~Util(){}
	__attribute__((always_inline)) inline static  void enterEs(int seg,int temp);
	__attribute__((always_inline)) inline static void leaveEs(int& temp);


};
 void Util::enterEs(int seg,int temp)
 {
     __asm__ __volatile__(
	"mov %%es,%%ax\n\t"
	"mov %%ax,%0 \n\t"
	:"=m"(temp)
	:
	:);
    if(seg==SEG_CURRENT)
    {
        __asm__ __volatile__(
            "mov %%ds,%%ax \n\t"
            "mov %%ax,%%es \n\t"
            :
            :
            :"eax"
        );
    }else{
        __asm__ __volatile__(
        "mov %%ax,%%es \n\t"
        :
        :"a"(seg)
        :
        );
    }
 }
void Util::leaveEs(int& temp)
{
    __asm__ __volatile__(
	"mov %0,%%ax \n\t"
	"nop \n\t"
	"nop \n\t"
	"mov %%ax,%%es \n\t"
	:
	:"m"(temp)
	:"eax"
	);
}

__attribute__((always_inline)) inline void P(Util u)
{
	__asm__("nop \n\tnop\n\tnop\n\t");
	Util* pu=&u;

}
__attribute__((always_inline)) inline void Q(Util& u)
{
	__asm__("nop \n\tnop\n\tnop\n\tnop\n\t");
	Util* pu=&u;

}

void test()
{
	Util u0;
	P(u0);
	Q(u0);
/*
	int a=5;
	Util::enterEs(0x10000,a);
	
	Util::leaveEs(a);
	Util::leaveEs(a);
	Util::enterEs(0x10000,a);
*/
}
