#include <stdlib.h>
#include <stdio.h>

int cmp(const int *a,const int *b)
{
	return *a-*b;
}
int main()
{
	
	long c=strtol(" ff01KKK",NULL,16);
	printf("%x \n",c);
	int arr[]={4,6,9,8};
	int nlen=sizeof(arr)/sizeof(arr[0]);
	qsort(arr,nlen,sizeof(arr[0]),cmp);
	for(int i=0;i<nlen;i++)
		printf("%d ",arr[i]);
	printf("\n");	

}
