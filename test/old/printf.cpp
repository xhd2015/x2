#include <cstdio>

int main()
{
	const char *s="12345";
	printf("%.3s\n",s);
	printf("%.*s\n",4,s);
}
