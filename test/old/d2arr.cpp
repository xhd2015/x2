#include <new>
#include <string>
#include <algorithm>
#include <iostream>
#include <array>
std::string toString(int pos[],int len)
{
	std::string s;
	std::for_each(pos,pos+len,[&s](int i){s+=std::to_string(i)+", ";});
	return s;
}

int main()
{
	extern int n;
	std::array<int,n> a;
	int *pos=new int[7] {0,1,-1};
	int *pos2=new int[7];
	int *pos3=new int[7]{-1};
	int *pos4=new int[7]();
	std::cout << toString(pos,7) << std::endl;
	std::cout << toString(pos2,7) << std::endl;
	std::cout << toString(pos3,7) << std::endl;
	std::cout << toString(pos4,7) << std::endl;

	return 0;
}
