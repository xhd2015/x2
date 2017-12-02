/**
 * Dec 2, 2017 by 13774
 *
 */

#include <cstring>
#include <cstdlib>
#include <cstddef>
#include <cstdio>
#include <regex>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

template <class T>
class V{
public:
	template <class M>
	void foo2()
	{
		cout << "foo2"<<endl;
	}
	template <class M>
	static void foo();

};


template<class T>
template <class M>
inline void V<T>::foo() {
	cout <<typeid(T).name()<<endl;
	cout <<typeid(M).name()<<endl;

	cout <<"foo"<<endl;
}


int main(int argc,char *argv[])
{
	V<short>::foo<int>();
	V<short> v;
	v.foo2<int>();
	cout << " "<<endl;
	return 0;
}
