/**
 * Dec 9, 2017 by 13774
 *
 */
#include "test_all_precompiled.h"
//#define AS_MACRO

using namespace std;

class Foo{
public:

//	Foo&& operator<<(int) &&
//	{
//		cout << "rvalue << "<<endl;
//		return std::move(*this);
//	}
};

void bar(const Foo &f)
{
	cout << "bar1" << endl;
}
void bar(Foo &&f)
{
	cout << "bar2" << endl;
}
void bar(Foo &f)
{
	cout << "bar3"<<endl;
}
//void bar(Foo f)
//{
//	cout << "bar4"<<endl;
//}

template <class __Tp>
void foo(__Tp &&f)
{
	bar(std::forward<__Tp>(f));
}


void foo(Foo &f)
{

}
template <class __Foo>
__Foo &&operator<<(__Foo &&foo,int)
{
	cout << "lvalue << "<<endl;
	return std::forward<__Foo>(foo);
}

int main(int argc,char *argv[])
{
	Foo f;
	foo(f);
	foo(Foo());

	f << 1;
	Foo() << 1;
	Foo{} << 1;

	cout << "END."<<endl;
	return 0;
}
