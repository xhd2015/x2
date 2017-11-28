#include <cstdio>
#include <new>
int main()
{
	int a;
	int *b=new (&a) int;
	*b=9;
	printf("%d\n",a);

}
