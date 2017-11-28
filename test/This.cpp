

#include <cstdio>
class This{
public:
	static int a;
};
int This::a=9;
class C{
public:
	typedef C This;
	static int a;
	void printa()
	{
		printf("This::a = %d\n",This::a);
		printf("::This::a = %d\n",::This::a);
	}
	void printa_out();
};
int C::a=10;
void C::printa_out()
	{
		printf("This::a = %d\n",This::a);
		printf("::This::a = %d\n",::This::a);
	}

int main()
{
	C c;
	c.printa();
	c.printa_out();

}
