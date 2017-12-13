/*
 * effctivec++.h
 *
 *  Created on: Dec 6, 2017
 *      Author: 13774
 */

#ifndef INCLUDE_CONCEPTUAL_EFFCTIVEC___H_
#define INCLUDE_CONCEPTUAL_EFFCTIVEC___H_


// 条款4： 1.确定对象使用前已被初始化，即使这个使用指的是operator=
//		2.non-local static对象的初始化顺序使用函数替代
//

// 条款5：了解编译器自动生成的构造函数和赋值函数：default, 拷贝构造,拷贝赋值操作符, 移动构造，移动赋值操作符


// 条款6：若不想使用编译器自动生成的函数，就应该明确拒绝
// 备注：编译器会自动生成拷贝构造，拷贝赋值，但是如果条件不满足：有const，有reference，有private父类，则不生成
// 备注：现代c++程序可以使用delete，以书中的ios_base为例，现代c++标准库的源码如下：
//		#if __cplusplus < 201103L
//		  // _GLIBCXX_RESOLVE_LIB_DEFECTS
//		  // 50.  Copy constructor and assignment operator of ios_base
//		  private:
//			ios_base(const ios_base&);
//
//			ios_base&
//			operator=(const ios_base&);
//		#else
//		  public:
//			ios_base(const ios_base&) = delete;
//
//			ios_base&
//			operator=(const ios_base&) = delete;
//  可见使用了新的明确拒绝机制
//  备注：继承可能带来运行时开销，现代c++程序应当使用=delete.来表示拒绝。
/**
 * 根据Effective C++
 */
class Uncopyable{
protected:
	Uncopyable();
	~Uncopyable();

#if __cplusplus >= 201103L
public:
	Uncopyable & operator=(const Uncopyable &)=delete;
	Uncopyable(Uncopyable &)=delete;
#else
private:
	Uncopyable & operator=(const Uncopyable &);
	Uncopyable(Uncopyable &);
#endif
};

// 条款7：为多态基类生成虚析构函数。
// 备注：如果class不含有虚函数，说明它不会用于基类，因此不需要声明虚析构函数
// 备注：书中说c++没有阻止继承的年代已经过去。

// 条款8：别让异常逃离析构函数
// c++不鼓励析构函数抛出异常
// 处理异常的方式：使用abort,直接退出； 或者忽略异常，继续执行；或者，在执行可能抛出异常的动作时，先将这些动作转发给用户，如果用户选择不执行，那就只能使用前两种方法。

// 条款9：不再构造和析构函数中调用virtual函数
//  因为c++中在构造函数和析构函数期间调用的任何virtual函数，实际上都不是virtual的
//    他不会去查指针，而是直接调用自己的实现
//   "在base class构造期间，virtual函数不是virtual函数"
//  因为基类先于子类构造。如果此时调用子类的函数，子类由于成员未构造，其行为不可预测。
//   而析构函数也是同样的道理，当析构函数执行到父类时，子类已经析构完毕。
//  更深层地说，所有构造/析构期间的函数：要么其自身不调用析构函数，要么其调用的函数不调用析构函数。

// 条款10：令operator=返回reference to *this
//  这只是一份协议，大家都在遵守

// 条款11：operator=中处理自我赋值
//  比如a[i]=a[j], a[i],a[j]可能是同一个对象
//  良好的operator=使用copy and swap技术
//  Widget &operator=(const Widget & rhs)
//	{
//		Widget temp(rhs);//copy
//      swap(temp); //and swap
//      return *this;
//	}
// 还可以更简洁
//		operator=(Widget rhs) //编译器可能将copy动作生成得更高效
//		{
//			swap(rhs);
//			return *this;
//		}

//  条款12：operator=,copy构造函数应当递归调用


//  条款13：将资源放在类中进行管理
//    借由c++析构函数自动调用机制确保资源被回收。RAII：资源取得时，资源就应当被初始化


#endif /* INCLUDE_CONCEPTUAL_EFFCTIVEC___H_ */
