/**
 * Dec 1, 2017 by 13774
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

//#define AS_MACRO __attribute__((always_inline))
#define AS_MACRO

using u64_t = unsigned long long;
using u32_t = unsigned int;
using u16_t = unsigned short;

template <typename __DEF_SIZE_TYPE,int __DEF_ALIGNMENT>
class LinearSourceDescriptor{} ;//模板

#define __DEF_SIZE_TYPE u32_t
#define __DEF_ALIGNMENT 4
#include "foo.cpp.RAW"

#define __DEF_SIZE_TYPE u64_t
#define __DEF_ALIGNMENT 8
#include "foo.cpp.RAW"

//template<>
bool  LinearSourceDescriptor<u32_t,4>::isAllocable() const
{
	return true;
}

template <class T1,class T2>
class Foo{

};

template <class T2>
class Foo<int,T2>
{

};


int main(int argc,char *argv[])
{
	LinearSourceDescriptor<u32_t,4> l1(0,0);
	LinearSourceDescriptor<u64_t,8> l2(0,0);
	cout << alignof(l1)<<endl;
	cout << alignof(l2)<<endl;
	cout << l1.isAllocable() << endl;
	cout << " "<<endl;
	return 0;
}


