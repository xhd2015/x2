/**
 * Dec 9, 2017 by 13774
 *
 */
#include "test_all_precompiled.h"
//#define AS_MACRO

using namespace std;

class Foo{
public:
	virtual ~Foo(){}
	void print(){}
};
class Bar:public Foo{
public:
	virtual ~Bar(){}
	virtual void bar(){}
	virtual void barfoo() {cout << "barfoo"<<endl;} //一个指针，这个指针指向了关联类的表
};
int main(int argc,char *argv[])
{
	static_cast<Foo*>(nullptr)->print();
	Foo *f=new Bar;
	cout << typeid(f).name() << endl;
	cout << typeid(*f).name() << endl;
	cout << typeid(Bar).name() << endl;


	cout << "END."<<endl;
	return 0;
}
