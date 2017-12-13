/**
 * Dec 12, 2017 by 13774
 *
 */
#include "test_all_precompiled.h"
//#define AS_MACRO

using namespace std;

class Foo{
public:
	virtual void print()
	{
		cout << "Foo print" << endl;
	}
	virtual ~Foo()
	{
		cout << "~Foo" << endl;
	}
};

class Bar:public Foo{
public:
	virtual void print()
	{
		cout << "Bar print" << endl;
	}
	virtual ~Bar(){
		cout << "~Bar" << endl;
	}
};


template <class PBase,class PDerived>
constexpr bool isBasePointerOf()
{
	return std::is_pointer<PBase>() && std::is_pointer<PDerived>() &&
			std::is_base_of<typename std::remove_pointer_t<PBase>,
					typename std::remove_pointer_t<PDerived>>();
}
// 将Tmplt<__Tp1>转换成Tmplt<__Tp2>, 如果__Tp1,__Tp2具有指针继承关系
template <template <class >class __Tmplt,class __TpDerived,class __TpBase>
inline constexpr __Tmplt<__TpBase>& basePointerCast(__Tmplt<__TpDerived>& data)
{
	static_assert(isBasePointerOf<__TpBase,__TpDerived>(),"not derieved");
	return *reinterpret_cast<__Tmplt<__TpBase>*>(&data);
}
template <template <class >class __Tmplt,class __TpDerived,class __TpBase>
inline constexpr const __Tmplt<__TpBase>& basePointerCast(const __Tmplt<__TpDerived>& data)
{
	static_assert(isBasePointerOf<__TpBase,__TpDerived>(),"not derieved");
	return *reinterpret_cast<const __Tmplt<__TpBase>*>(&data);
}
template <class T>
class Node{
public:
	Node(){}
	Node(const T & t):t(t){} // copy构造函数
	T t;


	// Node<E> e=(Node<E>)nodeT;--> E 是 T的base类型
	template <class E>
	operator Node<E>&() // 除非是指针类型，并且除非是父类型
	{
		return basePointerCast<Node,T,E>(*this);
	}
	template <class E>
	operator const Node<E>&()const // 除非是指针类型，并且除非是父类型
	{
		return basePointerCast<Node,T,E>(*this);
	}
};

int main(int argc,char *argv[])
{
	Node<Bar*> b;
	b.t = new Bar;

	Node<Foo*> n=basePointerCast<Node,Bar*,Foo*>(b); // 强制转换如何只转换成引用？ operator &
	Node<Foo*> n2 = b;
	Node<Foo*> &n3 = b;//重新绑定
	const Node<Foo*> &n4= b;

	b.t->print();
	n.t->print();
	n2.t->print();
	n3.t->print();
	n4.t->print();
	cout << &b << endl;
	cout << &n << endl;
	cout << &n2 << endl;
	cout << &n3 << endl; //同b
	cout << &n4 << endl; //同b

	return 0;
}
