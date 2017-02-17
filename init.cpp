
#include "init_help.h"

class T{
public:
	const static int a=0;
public:
	T(int x,int y=0):x(x+this->y),y(this->x+y)
	{

	}
	~T(){}
	int y,x;

};

class T2{
public:
	
	T2():t(T(1))
	{
		a=0;
		t.y=0;	
	}
	~T2(){}
	T t;
	int a;

};

void test()
{
	T2 t2;
	t2.a=0;
	__asm__("#t2end \n\t");
	T a(0);
	int t;
	__asm__("":"=a"(t));
	t=T::a;
	t=K::a;
	t=K::b;
	t=PMLoader::a;
	t=PMLoader::JMPSEG;
	t=PMLoader::CODE_START;
	t=PMLoader::rEAL_SECNUMS;
}
