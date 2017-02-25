
class T{
public:
	int a;
};
#include <cstdio>
int main()
{
	T* t=new T;
	int c=t->a;
	printf("delete\n");
	delete t;

}
