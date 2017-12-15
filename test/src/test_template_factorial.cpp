#include <iostream>
template <int N>
struct Factorial{
	enum {value = N*Factorial<N-1>::value};
};
template <>
struct Factorial<1>{
	enum {value = 1};
};

int main()
{
	enum { N = 1000000000};
	std::cout << Factorial<N>::value << std::endl;
}
