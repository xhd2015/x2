
#include <new>
#include <iostream>
using namespace std;

int main()
{
	int *a=new int;
	int *b=new int[10];
	int *c=new int[1000];
	int *d=new int[10000];
	cout << std::hex<<std::showbase
		<<size_t(a)<<','
		<<size_t(b)<<","
		<<size_t(c)<<","
		<<size_t(d)<<","
		<<endl;
	

}
