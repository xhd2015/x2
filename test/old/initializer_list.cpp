
#include <iostream>
#include <vector>
#include <initializer_list>
using namespace std;

struct T{
	/*explicit*/ T(int){std::cout<<"T(int)"<<endl;
	}
};

class L{
public:
	L(initializer_list<T> l)
	{
		auto it=begin(l),itend=end(l);
		std::cout<<"L(init_l<T>)"<<endl;
		
	}
};

class LL{
public:
	LL()=default;
	LL(initializer_list<L>){std::cout<<"LL(list)"<<endl;}
};
std::string *p1,*p2;
void doA(std::string &&s)
{
	std::cout << "doA && "<<std::endl;
}
/*
void doA(const std::string &s)
{
	std::cout << "doA const & "<<std::endl;
}
*/
void doA_(initializer_list<std::string> &&l)
{
	std::cout << "doA_ &&"<<std::endl;
	//auto it=std::begin(l);
	initializer_list<std::string>::iterator it=l.begin();
	//doA(std::move(*it));
	//doA(static_cast<const std::string&&>(*it));
	//doA("aa");
}
void doA_(const initializer_list<std::string> &l)
{
	std::cout << "doA_ const &"<<std::endl;
	auto it=std::begin(l);
	//doA(*it);
}
	
void doAA()
{
	initializer_list<std::string> l={"a","b"};
	doA_(l);//doA_ const &
	doA_(std::move(l));//doA_ &&
	doA_({"c","d"});

}
class MyPair{
public:
	MyPair()=default;
	//MyPair& operator=(
	MyPair(int a,const std::string& s)
	{
		std::cout << "MyPair(int,const std::string&)"<<std::endl;
	}
	//MyPair(int
};
#include <utility>
#include <tuple>
int main()
{
	std::tuple<int,int,std::string> mt={0,0,"1"};
	int n=9;
	std::cout << "mt<2>="<<std::get<2>(mt)<<std::endl;
	auto amt=std::tuple_cat(std::move(mt),std::tie(n));
	std::get<0>(amt)=2;
	std::get<3>(amt)=10;
	std::cout << "mt<2>="<<std::get<2>(mt)<<std::endl;
	std::cout << "n="<<n<<std::endl;
	std::vector<MyPair> vec={
		{0,"what is"},
		{1,"here is"}
	};
	MyPair mp={3,"there is"};
	getchar();
	doAA();
	getchar();
	L l{0,9,8,77};
	LL ll;
	ll=LL({ {0 }, {9}}) ;
}
