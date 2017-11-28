#include<cstdio>
inline void t();
__attribute__((always_inline)) extern inline void v()
{
	int a=0;
	printf("0");
}

void t()
{
	printf("t");
}

class M{
public:
	__attribute__((always_inline)) inline static void t();
	static void m();

};
void M::t()
{
	printf("9090");
}
void M::m()
{
	printf("m");
}
int mark(int a)
{
}
__attribute__((always_inline)) inline void L2();
__attribute__((always_inline)) inline void L1()
{
	mark(0x1);
	L2();
}
__attribute__((always_inline)) inline void L2()
{
	L1();
	mark(0x2);
}


void test()
{
	int a=10;

	printf("10 \n");
	L2();
}
