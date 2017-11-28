#include <cstdio>
#include <typeinfo>

class T{
public:
	__attribute__((always_inline)) inline static int initTarget(void *&p)
	{
		__asm__ __volatile__("":"=c"(p)::);
	}
	T getInstance(int c)
	{
		int* t;
		T::initTarget(t);
		t->a=60;
		this->a=30;
	}
		
	void print(){
		std::printf("print:%d\n",this->a);
	}
public:
	int a;
	int b;
	int c;
};

int main()
{
	T t;
	T x=t.getInstance(50);
	x.print();
	printf("%s\n",typeid(x).name());
}

	
