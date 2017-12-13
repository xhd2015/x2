/**
 * Dec 7, 2017 by 13774
 *
 */
#include "test_all_precompiled.h"
//#define AS_MACRO

using namespace std;

class Foo{
public:
	Foo(int &a):a(a){}
	int &a;
	~Foo()
	{
		cout << "~Foo" << endl;
	}
};

int main(int argc,char *argv[])
{
	int a=0;
	Foo f(a);
	cout << f.a << endl;
	int b=4;

	new (&f) Foo(b);
	cout <<f.a <<endl;
	cout << "END."<<endl;
	return 0;
}
