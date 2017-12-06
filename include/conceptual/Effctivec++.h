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



#endif /* INCLUDE_CONCEPTUAL_EFFCTIVEC___H_ */
