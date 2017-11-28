
#define AS_MACRO __attribute__((always_inline))
#include<cstdio>
class A{
public:
	virtual void v0()=0;
	virtual void v1(){printf("#A::v1--%d\n",1);}
	virtual void v4f()final{printf("#A::v4 final--%d\n",2);}
	virtual void v5(){printf("#A::v5--%d\n",7);}


};
class B:public A{
public:
	void v0(){printf("#B::v0--%d\n",5);}
	void v1(){printf("#B::v1--%d\n",3);}
	//void v4f() {printf("#B::v4 final--%d\n",6);}

};

class C:public B{
public:
	void v3(){printf("#C::v3--%d\n",4);}

};

int main()
{
	B b;
	A* p=&b;//p can only point to method that is already in A
	p->v0();
	p->v1();
	p->v4f();
	//p->v3();
}
