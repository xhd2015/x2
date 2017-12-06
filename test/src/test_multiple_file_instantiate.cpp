/**
 * Dec 2, 2017 by 13774
 *
 */
#include <typeinfo>
#include <cstring>
#include <cstdlib>
#include <cstddef>
#include <cstdio>
#include <regex>
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <new>
#include <memory>
#include "test_inc.h"

using u64_t = unsigned long long;
using u32_t = unsigned int;
using u16_t = unsigned short;
//#define AS_MACRO __attribute__((always_inline))
#define AS_MACRO

using namespace std;

class Foo:public Bar{
public:
};



int main(int argc,char *argv[])
{
//	print<int>(34);
//	print<short>(9);
	cout << "END."<<endl;
	return 0;
}

