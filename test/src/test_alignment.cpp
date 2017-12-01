/**
 * Dec 1, 2017 by 13774
 *
 */

/**
 * 此文件测试了通过一个宏来定义一个class版本的多个范例
 */

#include <cstring>
#include <cstdlib>
#include <cstddef>
#include <cstdio>
#include <regex>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#define AS_MACRO __attribute__((always_inline))
using u64_t = unsigned long long;
using u32_t = unsigned int;

template <typename __SizeType,int __AlignType>
class Node{};

template <class __Node>
class NodeUtil{
public:
	static void foo(__Node *node,int i)
	{
		cout << "foo("<<i<<")"<<endl;
		cout << "node->a="<<node->a<<endl;
	}
};



#define DEF_CLASS_NODE(__Type,__Num) 													\
	template <> 																		\
	class Node<__Type,__Num>{															\
		friend class NodeUtil<Node<__Type,__Num>>;										\
		using __I_SizeType = __Type; 													\
		enum {__I_Num=(__Num) }; 														\
	public:																				\
		using This=Node<__I_SizeType,__I_Num>; 											\
		using __NodeUtil = NodeUtil<This>;												\
	public:																				\
		AS_MACRO void foo(int i){__NodeUtil::foo(this,i);}								\
	private:																			\
		__I_SizeType a=123;																\
	}

#pragma pack(push,8)
DEF_CLASS_NODE(u64_t,8);
#pragma pack(pop)

#pragma pack(push,4)
DEF_CLASS_NODE(u32_t,4);
#pragma pack(pop)

//template class NodeUtil<Node<u64_t,8>>;
//template class NodeUtil<Node<u32_t,4>>;



int main(int argc,char *argv[])
{
	Node<u64_t,8> n1;
	Node<u32_t,4> n2;

	n1.foo(8);
	n2.foo(7);

	cout << " "<<endl;
	return 0;
}
