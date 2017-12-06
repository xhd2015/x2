

#include "test_all_precompiled.h"
#include <regex>

using namespace std;

//void * operator new(size_t n)
//{
//	return ::new char;
//}

int main(int argc,char *argv[])
{
	new int;
	cout << "END."<<endl;
}
