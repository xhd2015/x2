#include <malloc.h>
#include <stdio.h>
#include <limits.h>

int main()
{
	int times=40;
	malloc(40);
	printf("Pre malloc %d\n",40);
	
	for(int i=0;i<times;i++)
	{
		malloc(INT_MAX/times);
		printf("malloc size=%d\n",INT_MAX/times);
	}
	fflush(stdout);
	while(1);

}
