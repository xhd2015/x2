
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

void test()
{
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
