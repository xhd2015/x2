#include <iostream>
using namespace std;

int main()
{
	int * const pi=nullptr;
	const int * pi2=nullptr;
//	const int const * pi3 = nullptr; // error, 重复的const
	const int * const pi4 = nullptr;
	const int * const & ref1=pi4;
//	const int * const & const ref2=pi4; // 错误 引用本身就是const

	return 0;
}
