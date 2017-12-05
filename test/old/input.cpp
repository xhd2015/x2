
#include <iostream>
#include <sstream>
using namespace std;
int main()
{
	int i=0;
	while(true)
	{
		std::string s;
		std::getline(std::cin,s);
		std::stringstream ss(s);
		std::string reads;
		while(!ss.eof())
		{
			ss>>reads;
			std::cout << i++ << ": "<<reads<<std::endl;
		}
	}

	return 0;
}
