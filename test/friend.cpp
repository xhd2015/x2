
#include <utility>
#include <iostream>
class T{
public:
	T(int a):a(a){}
	T(T&& t):a(t.a){
	std::cout << t.a << std::endl;
}
private:
	int a;
};

int main()
{
	T t(9);
	T t2(std::move(t));
}
