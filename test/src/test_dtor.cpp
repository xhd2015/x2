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
class Foo2{
protected:
	~Foo2(){
		cout << "~Foo2"<<endl;
	}
};
class Widget{
public:
	~Widget(){
		cout << "~Widget" << endl;
	}
};
class Widget2{
public:
	~Widget2(){
		cout <<"~Widget2"<<endl;
	}
};

class Bar : public Foo,public Foo2{
public:
	~Bar(){
		cout << "~Bar" << endl;
	}
	Widget w;
	Widget2 w2;
};

//class Widget{
//public:
//	Widget(Foo & f):f(f){}
//	Foo &f;
//};

int main(int argc,char *argv[])
{
	Bar b;
//	b.~Bar();
	cout << "END."<<endl;
	return 0;
}
