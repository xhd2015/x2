#include "exsup.h"
class Texception{};

void test() throw (Texception)
{
	throw Texception();

}
int main()
{
	try{
		int a=0;
	}catch(Texception te)
	{	
		int a=1;
	}
}
