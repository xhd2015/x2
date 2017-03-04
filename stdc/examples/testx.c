
#include <stdio.h>
void (*t())()
{
	printf("t\n");
}
int main()
{
	printf("main\n");
	t();

}
