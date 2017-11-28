
#include <iostream>
class T{
public:
	T()
	{
		std::cout<<"T()"<<std::endl;
	}
};

int main()
{
	for(int i=0;i<9;i++)
	{
		T t;
	}
}
