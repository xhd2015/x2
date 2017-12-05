
#include <vector>
#include <string>
#include <iostream>

namespace __StdEnv{
	using namespace std;
};
using namespace std;


using __String = __StdEnv::string;

template <class T>
using __Vector =typename __StdEnv::vector<T>;

using __Vector_String = __Vector<__String>;

using __Vector_String_cit = __Vector_String::const_iterator;// cit = const_iterator

int main()
{
	__Vector_String vs;
	__Vector_String_cit it=vs.cbegin(),itend=vs.cend();
	cout << (itend-it)<<endl;
}
