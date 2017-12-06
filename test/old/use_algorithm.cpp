
#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;

int main()
{
	int a[]={1,2,4,5,4,5,6};
	int n=sizeof(a)/sizeof(int);
	auto il=lower_bound(a,a+n,5);
	auto iu=upper_bound(a,a+n,5);
	auto ifind=find(a,a+n,4);
	printf("%d=%d\n",ifind-a,*ifind);
	printf("%d=%d,%d=%d\n",(il-a),*il,(iu-a),*iu);
}
