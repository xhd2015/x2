
#include <cstdio>
struct A{
void foo()
{
	printf("A::foo %d\n",this->a);
}
int a;
};

struct B{
void fu()
{
	printf("B::fu %d\n",this->b);
}
int b;
};

struct C:public B,public A{

};

int main()
{
	C c;
	c.a=10;
	c.b=40;
	A *pa=&c;
	pa->foo();
	C *pc=(C*)pa;
	pc->foo();
	pc->fu();
	pa=(A*)43;
	pc=(C*)54;
	
	pa=(A*)(int*)434;
	pc=(C*)(int*)544;
	B b;
	pa=(A*)&b;

}

