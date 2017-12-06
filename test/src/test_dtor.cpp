/**
 * Dec 7, 2017 by 13774
 *
 */
#include "test_all_precompiled.h"
//#define AS_MACRO

using namespace std;

class Foo{
public:
	~Foo()
	{
		cout << "~Foo"<<endl;
	}
};

class Bar{
public:
	Foo f;
};

class Widget{
public:
	Widget(Foo & f):f(f){}
	Foo &f;
};

int main(int argc,char *argv[])
{
	Foo f;
	f.~Foo();//可以多次调用
	cout << "END."<<endl;
	return 0;
}
