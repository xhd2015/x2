/**
 * Dec 9, 2017 by 13774
 *
 */
#include "test_all_precompiled.h"
//#define AS_MACRO

using namespace std;

class Foo{
public:
	Foo& operator=(const Foo &)  {
		cout << "operator="<<endl;
		return *this;}
	Foo()=default;
	Foo(const Foo &)
{
		cout << "copying" << endl;
}
	Foo(Foo &&){
		cout << "moving"<<endl;
	}
};

Foo foo_copy_move(Foo &&f)
{
	Foo f3=std::move(f);
	cout << "foo_copy_move"<<endl;
	cout << &f << endl;
	f3.~Foo();
	return f;
}
Foo&& foo_nothing(Foo &&f)
{
	cout << "foo_nothing" <<endl;
	cout << &f << endl;
	Foo localF=f;
	localF.~Foo();
	return std::move(f=localF);
}


int main(int argc,char *argv[])
{
	foo_copy_move(foo_copy_move(Foo()));
	foo_nothing(foo_nothing(Foo()));
	cout << "END."<<endl;
	return 0;
}
