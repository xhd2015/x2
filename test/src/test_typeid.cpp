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
#include <typeinfo>

using namespace std;


int main(int argc,char *argv[])
{
	size_t a,b;
	cout << typeid(decltype(a)).name()<<endl;
	cout << typeid(decltype(a-b)).name()<<endl;
	cout << sizeof(unsigned long long)<<endl;
	cout << sizeof(size_t)<<endl;
	return 0;
}
