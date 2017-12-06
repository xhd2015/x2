#include <cstdio>
class T{
public:
	int a;int b;int c;

};

int main()
{
		char temp[sizeof(T)];	
		T *t=(T*)&temp;
	printf("%p  %p\n",t,temp);
	t->a=20;
	printf("%d\n",t->a);


}
