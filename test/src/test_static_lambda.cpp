/**
 * Dec 6, 2017 by 13774
 *
 */
#include "test_all_precompiled.h"
//#define AS_MACRO

using namespace std;

class Foo{
public:
	using ftype=ptrdiff_t (*)();
	using ftype2=std::function<ptrdiff_t()>;
	static ftype2 ptrBase(){
		return nullptr;
	}
};


int main(int argc,char *argv[])
{
	static int i=120;
	class Bar:public Foo{
		public:

			static int ptrBase(){
				return i;
			}

	};
	i=1232;
	cout << Bar::ptrBase()<< endl;
	cout << "END."<<endl;
	return 0;
}
