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
class OPPP{
public:
	OPPP(OPPP f,T2 h){}
};

class K_{
public:K_(){__asm__("");}
};
class _EaV4{
public: _EaV4(OPPP f,_EaV4 g,T2 h){__asm__("");}
	_EaV4(){__asm__("");}
};
class OOO{public: OOO(){__asm__("");}};
void test()
{
	T2 t2;
	K_ kk;
	_EaV4 l1;
	OOO	l2;	
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
