/**
 * Nov 27, 2017 by 13774
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

class M{
public:
	int m;
};
class N{
public:
	int n;
};
class V:public M,public N{
public:
	int m;

};

extern constexpr int w=0;
int main(int argc,char *argv[])
{
	V v;
	V *pv=&v;
	M *pm=pv;
	N *pn=&v;
	cout << pv << endl;
	cout << pm << endl;
	cout << pn << endl;
	cout << (V*)pn << endl;
	return 0;
}
