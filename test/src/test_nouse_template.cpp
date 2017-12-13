/**
 * Dec 12, 2017 by 13774
 *
 */
#include "test_all_precompiled.h"
//#define AS_MACRO

//#include <conceptual/ExtFunctional.h>

using namespace std;

template <class __Tp,class __Alloctor=typename std::allocator<__Tp>>
class MyVec:public std::vector<__Tp,__Alloctor>
{
public:
	template <class __Base,class __Alloc2>
	operator MyVec<__Base,__Alloc2>&()
	{
		return *reinterpret_cast<MyVec<__Base,__Alloc2>*>(this);
	}
};



namespace {
	template <int...V>
	struct __Int2Type{
		static constexpr int values[]={V...};
	};
}
template <int...V>
struct Int2Type:public __Int2Type<V...>{
	enum {value = __Int2Type<V...>::values[0] };
};
template <int V>
struct Int2Type<V>{
	enum{value = V};
};

int main(int argc,char *argv[])
{

	Int2Type<1,2> hello;

	cout << Int2Type<1>::value << endl;
	cout << hello.values[0] << endl;
	cout << hello.values[1] << endl;
	cout << hello.values[3] << endl;

	cout << "END."<<endl;
	return 0;
}
