
#include <iostream>
#include <cstdlib>

using namespace std;

class HasConst{
	public:
		const int a=4;
		int b;
};
bool checkHasConst(HasConst *p)
{
	return p->a==4;
}


int main()
{
	char space[sizeof(HasConst)]={time(NULL)%2==0?4:9};
	HasConst *p=(HasConst*)space;
	cout << "check:"<<checkHasConst(p)<<endl;

	return 0;
}

// 多次运行打印结果check 0,check 1交替出现 
