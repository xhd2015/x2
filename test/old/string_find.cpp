

#include <string>

#include <iostream>

using namespace std;

int main()
{
	string s="not";
	cout << s.find("n") << endl;
	cout << s.find("i") << endl;
	cout << s.find("j") << endl;
	cout << s.npos << endl;
	return 0;
}

