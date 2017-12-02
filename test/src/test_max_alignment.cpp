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

using u64_t = unsigned long long;
using u32_t = unsigned int;
using u16_t = unsigned short;
using namespace std;

#pragma pack(push,8)
class V{
public:
	char ch;
	int i;
};
#pragma pack(pop)

#pragma pack(push,4)
class V2{
public:
	char ch;
	int i;
} __attribute__((aligned(4)));
#pragma pack(pop)

#pragma pack(push,2)
class V3{
public:
	char ch;
	int i;
};
#pragma pack(pop)



int main(int argc,char *argv[])
{
	cout << __BIGGEST_ALIGNMENT__ << endl;
	cout << sizeof(__SIZE_TYPE__) <<endl;
	cout << __SIZEOF_LONG__ << endl;
	cout << sizeof(V)<<endl;
	cout << sizeof(V2) << endl;
	cout << sizeof(V3) << endl;

	cout << alignof(V)<<endl;
	cout << alignof(V2)<<endl;
	cout << alignof(V3)<<endl;

	return 0;
}
