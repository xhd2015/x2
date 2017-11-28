#include<new>
#include<cstdio>
class T{
public:
	T(int a,int b,T* c){}
};

int main()
{
	int a;
	int *b=new(&a) int(4);
	printf("%d\n",a);
	T*	c=new((T*)&a) T(9,10,(T*)0);
	return 0;
}
