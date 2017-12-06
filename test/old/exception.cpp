//#include "exsup.h"
#include <cstdio>
__asm__(".code32 \n\t");
class Texception{};
extern int c;
void test_nothrow() noexcept{
	int a=10;
	printf("in test_nothrow %d\n",a);
	a=20;
};
void test() throw (Texception)
{
	int a=9;
	if(c==10)
		throw Texception();
	a=11;
	int b=20;
	a=19;

}
int before_try,in_catch,after_catch;
int main()
{
	before_try=1;
	try{
		int a=0;
		test();
	}catch(Texception te)
	{	
		in_catch = 2;
		int a=1;
	}
	after_catch=3;
}
