# 此文件
此文件描述了通过一些特别的手段来实现各种比较特殊的要求，其中一些可能十分有技术含量，另一些却看起来平淡无奇。
但是，无论如何这些技巧都最大化遵循最佳实践原则，并且随着时间会进行改进。

# 实现结构体按不同字节对齐以及C++代码生成技术
代码生成很重要，不可否认。受boost preprocessor的启发，我对此问题的最新的最优雅的解决方法是：
```c++

template <typename __DEF_SIZE_TYPE,int __DEF_ALIGNMENT>
class LinearSourceDescriptor{} ;//模板

#define __DEF_SIZE_TYPE u32_t
#define __DEF_ALIGNMENT 4
#include "foo.cpp.RAW"

#define __DEF_SIZE_TYPE u64_t
#define __DEF_ALIGNMENT 8
#include "foo.cpp.RAW"

int main(int argc,char *argv[])
{
    LinearSourceDescriptor<u32_t,4> l1(0,0);
    LinearSourceDescriptor<u64_t,8> l2(0,0);
    cout << alignof(l1)<<endl;
    cout << alignof(l2)<<endl;
    cout << " "<<endl;
    return 0;
}
```
上面的文件通过每次在include 下面的RAW文件之前，定义一系列的宏参数来生成代码。这十分巧妙。
```c++
// 文件foo.cpp.RAW, 相当于一个宏函数，接受参数__DEF_SIZE_TYPE,__DEF_ALIGNMENT
// 然后通过#include 循环调用来生成多份代码

//#define __DEF_SIZE_TYPE u32_t
//#define __DEF_ALIGNMENT 4
#if !defined(__DEF_SIZE_TYPE) || !defined(__DEF_ALIGNMENT)
#error "please define __DEF_SIZE_TYPE and/or __DEF_ALIGNMENT"
#endif

#pragma pack(push,__DEF_ALIGNMENT)

template <>
class LinearSourceDescriptor<__DEF_SIZE_TYPE,__DEF_ALIGNMENT>{
public:
    using __SizeType = __DEF_SIZE_TYPE;
    enum{__Alignment=__DEF_ALIGNMENT};
public:
    AS_MACRO LinearSourceDescriptor()=default;
public:
    AS_MACRO LinearSourceDescriptor(__SizeType start,__SizeType limit){} //done
    AS_MACRO ~LinearSourceDescriptor()=default;//done
    AS_MACRO __SizeType getStart() const ;//done
    AS_MACRO __SizeType getLimit() const ;//done
    AS_MACRO bool isAllocable() const;//done,always return true;
    AS_MACRO void setStart(__SizeType start);//done
    AS_MACRO void setLimit(__SizeType limit);//done
    AS_MACRO bool contains(const LinearSourceDescriptor& b)const;//done
    AS_MACRO bool contains(__SizeType start,__SizeType limit)const;//done
    /**
    * 逻辑相等而非全等
    */
    AS_MACRO    bool operator==(const LinearSourceDescriptor& b)const;//done
    AS_MACRO    bool operator!=(const LinearSourceDescriptor& b)const;//done
public:
    char ch;
    /**
     * 描述对象的起始地址
     */
    __SizeType start;
    /**
     * 描述对象的所占用的长度
     */
    __SizeType limit;
};//8字节对齐24,1字节对齐17
#pragma pack(pop)

#undef __DEF_SIZE_TYPE
#undef __DEF_ALIGNMENT
```

# 掌握预处理器
注：关于宏的测试可以使用eclipse cdt进行，鼠标放在最后的宏上面就能生成替换。
提示： .在宏处理中由特殊含义
```c++
#define __STR(s) #s
#define STR(s) __STR(s)
#define CONH(A,B,C) A##B##C.h

#define h PAPA
#include STR(CONH(dio,h,op))
```
请问include最后生成了什么？（答案：#include "diohop.PAPA"
TODO：解释
```c++
#define __STR(s) #s
#define STR(s) __STR(s)
#define CONH(A,B,C) A##B##C.h

#define INC(A,B,C) STR(CONH(A,B,C))
#define FOO foo2
#include INC(dio,FOO,op)
```
请问include最后生成了什么？（答案：#include "diofoo2op.h" TODO:解释

# 实现结构体按不同字节对齐的版本（过时，请看最新版）
现在需要在64位下，同时有一个class的3份定义，它们都是重复的，唯一的不同是它们的对齐方式：这些结构体会被存入文件中，并可能在32位机器上读取，因此必须使结构体的每个域在64位和32位机器上具有相同的偏移。
C++不支持在类实例化时指定对齐：
```c++
template class Node<u64_t> __attribute__((aligned(8)));
template class Node<u32_t> __attribute__((aligned(4)));
```

为了实现这个需求，只能使用
```c++
#pragma pack(push,N)
/*类定义*/
#pragma pack(pop)
```

这样，需要在源文件中产生多份同一个类的定义，破坏了“单源”原则。
这里使用的解决方式是宏生成，通过使用一个额外的静态友类来编写类的成员函数，而通过一个宏来定义类的结构体。
原始类的所有函数，包括构造函数，都已AS_MACRO方式声明
```c++
/**
 * 此文件测试了通过一个宏来定义一个class版本的多个范例
 */

#include <iostream>

using namespace std;

#define AS_MACRO __attribute__((always_inline)) // 所有方法都用inline方式，节省开销
using u64_t = unsigned long long;
using u32_t = unsigned int;

template <typename __SizeType,int __AlignType>
class Node{}; //声明一个一般性的结构，但是从来不使用它，而只使用偏化的版本

template <class __Node>
class NodeUtil{
public:
    static void foo(__Node *node,int i)
    {
        cout << "foo("<<i<<")"<<endl;
        cout << "node->a="<<node->a<<endl;
    }
};



#define DEF_CLASS_NODE(__Type,__Num)                                                    \
    template <>                                                                         \
    class Node<__Type,__Num>{                                                           \
        friend class NodeUtil<Node<__Type,__Num>>;                                      \
        using __I_SizeType = __Type;                                                    \
        enum {__I_Num=(__Num) };                                                        \
    public:                                                                             \
        using This=Node<__I_SizeType,__I_Num>;                                          \
        using __NodeUtil = NodeUtil<This>;                                              \
    public:                                                                             \
        AS_MACRO void foo(int i){__NodeUtil::foo(this,i);}                              \
    private:                                                                            \
        __I_SizeType a=123;/*私有属性*/                                                             \
    }

#pragma pack(push,8)
DEF_CLASS_NODE(u64_t,8);
#pragma pack(pop)

#pragma pack(push,4)
DEF_CLASS_NODE(u32_t,4);
#pragma pack(pop)


int main(int argc,char *argv[])
{
    Node<u64_t,8> n1;
    Node<u32_t,4> n2;

    n1.foo(8); //正常访问
    n2.foo(7); // 正常访问

    cout << " "<<endl;
    return 0;
}
```

这个更加简单的方式是定义一个模板，使用python来输出之。