
#include <stddef.h>
#include <stdio.h>
struct foo{
	int a;
	char b;
};
int main()
{
	size_t k=offsetof(struct foo,b);
	printf("%d\n",k);


}
