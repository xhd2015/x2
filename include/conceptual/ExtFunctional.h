/*
 * ExtFunctional.h
 *
 *  Created on: Dec 8, 2017
 *      Author: 13774
 */

#ifndef SRC_CONCEPTUAL_EXTFUNCTIONAL_H_
#define SRC_CONCEPTUAL_EXTFUNCTIONAL_H_
#include <def.h>
#include <type_traits>
#include <utility>
//#include <bits/unique_ptr.h>
/**
 * make a function pointer to dtor possible
 */
template <class T>
AS_MACRO void destruct(T *p)
{
	p->~T();
}
/**
 * 例子： deleteArray<char, char (*)[]>, 为什么不采用更简单的方式？比如 deleteArray(__Tp (*p)[]), 因为C++不支持参数指向未知元素个数的数组指针
 * @param __Up 数组元素类型
 * @param __Tp 原始的指针类型
 *
 * @param p  数组的首地址
 * 配合makeSharedArray使用。
 */
template <class __Up,class __Tp>
void deleteArray(__Tp p)
{
	delete [] reinterpret_cast<__Up*>(p);
}
template <class __Tp>
void deleteSingle(__Tp *p)
{
	delete p;
}
/**
 * @param __Tp  真实类型
 */
template <class __Tp>
void deleteSingle(void *p)
{
	delete reinterpret_cast<__Tp>(p);
}

template <class __Tp>
std::shared_ptr<__Tp[]> makeSharedArray(size_t size)
{
	return (std::move(
			std::shared_ptr<__Tp[]>{ reinterpret_cast<__Tp(*)[]>(new __Tp[size]),deleteArray<__Tp,__Tp(*)[]>}
			));
}


template <typename __Rt,typename ...__Args>
__Rt doNothing(__Args...args){} // this function does nothing


/**
 * @brief 判断指针之间是否具有继承关系
 * @param PBase  指针类型，指向基类
 * @param PDerived  指针类型，指向派生类
 */
template <class PBase,class PDerived>
constexpr bool isBasePointerOf()
{
	return std::is_pointer<PBase>() && std::is_pointer<PDerived>() &&
			std::is_base_of<typename std::remove_pointer_t<PBase>,
					typename std::remove_pointer_t<PDerived>>();
}
/// 将Tmplt<__Tp1>转换成Tmplt<__Tp2>, 如果__Tp1,__Tp2具有指针继承关系
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
#if defined(CODE64)
#include <iostream>
using std::cout;
using std::endl;
#endif

namespace{ // 一个演示，演示如何使用basePointerCast. 不需要实例化，因此没有运行时开销。

#if defined(CODE64)
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
template <class T>
class Node{
	public:
		Node():t() {}
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

		void usage()
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
					std::cout << &b << std::endl;
					std::cout << &n << std::endl;
					std::cout << &n2 << std::endl;
					std::cout << &n3 << std::endl; //同b
					std::cout << &n4 << std::endl; //同b
		}
	};

#endif
}


//==class ResourceWatcher
// holds the pointer to them
class ResourceWatcher{
public:
//	using DeleterFunc = std::function<void(void*)>;
	using DeleterFunc = void (*)(void *);

public:
	ResourceWatcher():
		data{},statusGood(true)
	{}
	template <class __T>
	__T* add(__T *obj,DeleterFunc deleter = deleteSingle<__T*>)
	{
		data.push_back(std::make_pair(obj, deleter));
		return obj;
	}

	// never good again
	/**
	 * 前置条件：statusGood=true
	 * fails on expr!=true
	 */
	bool fail(bool expr)
	{
		return !(statusGood=expr);
	}
	bool fail()
	{
		return !(statusGood=false);// yes,it fails
	}
	bool succeed()=delete;
	bool succeed(bool expr)=delete;
	bool good()
	{
		return statusGood;
	}

	~ResourceWatcher()
	{
		if(!statusGood)
			for(auto &pr:data)
				pr.second(pr.first);
	}
private:
	HostEnv::Vector<std::pair<void *,DeleterFunc>> data;
	bool statusGood;
};


// Type2Value
template <class T,T __Value>
struct Type2Value
{
	using type = Type2Value<T,__Value>;
	static constexpr T value = __Value;
};

template <bool __DoDump,class ...Types>
struct DumpTypes{
	DumpTypes(){
		static_assert(__DoDump,"dumptypes");
	}
};

/**
 * @brief 给定一个类型，对齐和其指针类型按函数进行取值和解引用等操作
 * @param __ObjType 需要操作的类型
 */
template <class __ObjType>
struct DefferenceHelper{
	// 命名规则： XXXXYYYY 其中XXXX表示主属性，YYYY修饰。Const属于修饰，不属于主体。
	using Object   =  __ObjType;
	using ConstObject  =  typename std::add_const<Object>::type;//const ObjectType;
	using PointerObject  =  typename std::add_pointer<Object>::type; //ObjectType *;
	using ConstPointerObject = typename std::add_const<PointerObject>::type;
	using PointerConstObject = typename std::add_pointer<ConstObject>::type;
	using ConstPointerConstObject = typename std::add_const<PointerConstObject>::type;// const ObjectType * const

	static constexpr ConstObject& defference(ConstPointerConstObject &s){return (*s);}
	static constexpr ConstObject& defference(PointerConstObject &s){return (*s);}
	static constexpr Object& defference(ConstPointerObject &s){return (*s);}
	static constexpr Object& defference(PointerObject &s){return (*s);}

	static constexpr PointerObject address(Object &s ){ return (std::addressof(s));}
	static constexpr PointerConstObject address(ConstObject &s ){ return (std::addressof(s));}

	static constexpr Object& defference(Object &s){ return (s);}
	static constexpr ConstObject& defference(ConstObject &s){ return (s);}

	static constexpr PointerObject& address(PointerObject &s ){ return (s);}
	static constexpr PointerConstObject& address(PointerConstObject &s ){ return (s);}
	static constexpr ConstPointerObject& address(ConstPointerObject &s ){ return (s);}
	static constexpr ConstPointerConstObject& address(ConstPointerConstObject &s ){ return (s);}
};

template <class __S,bool __isPointer> //pointer=true
	struct __PointerAsObjectHelper : public
		DefferenceHelper<typename std::remove_pointer<__S>::type>{};
template <class __S> // pointer = false
	struct __PointerAsObjectHelper<__S,false>:public
		DefferenceHelper<__S>{};
/**
 * @brief 将指针所指的对象看成最终的目标
 * @param __S 指针或者对象类型
 * 如果__S是指针类型，则*__S就是需要的类型
 * 如果__S是对象类型，则__S就是最终的类型
 *
 */
template <class __S>
	struct PointerAsObject:public
		__PointerAsObjectHelper<__S,std::is_pointer<__S>::value>{};

#endif /* SRC_CONCEPTUAL_EXTFUNCTIONAL_H_ */
