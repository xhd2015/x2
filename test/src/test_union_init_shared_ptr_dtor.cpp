/**
 * Dec 8, 2017 by 13774
 *
 */
#include "test_all_precompiled.h"
//#define AS_MACRO

using namespace std;
class Bar{
public:
	DEFUN(Bar);
	DEFUN(~Bar);
	void DEFUN(bar);

};
class Widget{
public:
	DEFUN(Widget);
	DEFUN(~Widget);
};
class Foo{
public:
//	DEFUN(Foo);
	Foo(shared_ptr<Bar> &&pbar):pbar(pbar)
{
		DEOUT();
}
	DEFUN(~Foo);
	union{
		Bar b;
		Widget w;
	};
	shared_ptr<Bar> pbar;
};

template <class T>
AS_MACRO void destruct(T *t)
{
	DEOUT();
	t->~T();
}


int main(int argc,char *argv[])
{
	Bar b;
	Foo f(shared_ptr<Bar>(&b,&destruct<Bar>));
	size_t addr = reinterpret_cast<size_t>(&destruct<Bar>);
	cout <<addr<<endl;
	cout << &f <<endl;
	cout << "END."<<endl;
	return 0;
}
