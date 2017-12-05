/**
 * Nov 29, 2017 by 13774
 *
 */

/**
 * 此测试文件指出了函数指针的定义方式
 *  函数类型不能直接初始化，必须转化为函数指针
 */

#include <cstring>
#include <cstdlib>
#include <cstddef>
#include <cstdio>
#include <regex>
#include <iostream>
#include <string>
#include <functional>
#include <vector>

using namespace std;

class V{
public:
	static void foo(){
		cout << "foo" << endl;
	}

};
using my_foo=function<void(void)>;
typedef void (*my_foo2)();
using my_foo3 = void (*)();
using my_foo4 = std::vector<string>::size_type (void);

int main(int argc,char *argv[])
{
	/*
	 * 输出：
		St8functionIFvvEE
		PFvvE
		PFvvE
		FmvE
		foo
		foo
		PFvvE
	 *
	 */
	cout << typeid(my_foo).name() << endl;
	cout << typeid(my_foo2).name() << endl;
	cout << typeid(my_foo3).name() << endl;
	cout << typeid(my_foo4).name() << endl;
	auto f=V::foo;
	f();
	(*f)();
	cout << typeid(f).name() << endl;
//	my_foo4 f1=f; //错误，不能直接使用原始类型，而是使用指针
//	my_foo4* f2=f;
//	f2();


	cout << " "<<endl;
	return 0;
}
