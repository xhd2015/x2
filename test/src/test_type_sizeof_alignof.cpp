/**
 * Dec 4, 2017 by 13774
 *
 */

#include "test_all_precompiled.h"
//#define AS_MACRO

using namespace std;

template <size_t __Align>
class Foo{ //大小至少是1，否则无法有效使用内存。
public:
	__attribute__((aligned(__Align)))
	class Meta{
		int a;
		int b;
	}f;


};

int main(int argc,char *argv[])
{
	cout << alignof(Foo<4>::Meta) << endl;
	cout << alignof(Foo<8>::Meta) << endl;
	cout << alignof(Foo<4>().f) << endl;
	cout << alignof(Foo<8>().f) << endl;
	cout << sizeof(Foo<4>::Meta) << endl;
	cout << sizeof(Foo<8>::Meta) << endl;
	cout << sizeof(Foo<4>().f) << endl;
	cout << sizeof(Foo<8>().f) << endl;
	cout << "END."<<endl;
	return 0;
}
