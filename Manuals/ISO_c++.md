# 此文件
此文件对标准c++进行介绍

# 参考和资源链接
http://www.stroustrup.com  stroustrup的个人网站
https://gcc.gnu.org/onlinedocs/libstdc++/latest-doxygen/  g++的在线文档

# 何时使用virtual
virtual的实现方式导致其运行效率较低，并不是任何需要接口的地方都可以使用virtual。

首先明白一点：virtual的作用有两个
1、在编写代码时提供接口规范
2、运行时同一个父类有多个子类实例

如果不满足其中任何一点，不要使用virtual；如果考虑效率，不要使用virtual。

特别需要注意第二点，运行时多个子类实例。在操作系统这样的环境中，一个Environment就只有一个单独的实例，所以即使看上去应该用virtual接口来规范所有的Environment，也不应该这样做，因为这样会降低运行时效率。

替代virtual的方案是使用template参数，将有多个实现的父类用template参数封装进来，并且在文档中说明规范，最好伴随一个普通接口类类用作语法检查。然后一个typedef 指向参数或者接口类
定义宏IDE_MODE，在编写程序时指向接口类
在编译时，指向参数类

<!-- 当然，这样做之后，你就不能定义静态函数以及其他变量。 【正确吗？】-->

```c++
    class Env{ //仅仅是语法上的声明，没有任何实现，在编译时不应当产生任何引用，除了常数
        public:
            void printOutput(const char* s);
    };
    class EnvLinux  //仅仅通过名称弱相关
    #if defined(IDE_MODE)
        :public Env
    #endif
    {
        public:
            void printOutput(const char *s);
    };

    template <typename __EnvInterface>
    class FileSystem{
        public:
#if defined(IDE_MODE)
        typedef Env _EnvInterface;
#else
        typedef __EnvInterface _EnvInterface;
#endif
        public:
        FileSystem(_EnvInterface *env);
        /*...*/
    };

```

# template相关
声明模板参数和实例化参数的个数必须相同
# 标准c++各个头文件和常用的函数，类等对应关系
<memory> 用于动态内存管理 
        unique_ptr,shared_ptr,weak_ptr,auto_ptr(until c++17)
        allocator, allocator_traits
        uninitialized_copy(move,fill)等
        pointer_traits,addressof,align,to_address
<filesystem>  c++17,用于支持文件系统
        path类，
        absolute,copy_file,exists等
<utility>   一般性的语言实用工具    
        swap,exchange,forward,move,move_if_noexcept
        类tuple,pair,initializer_list
<initializer_list> 


# using的用法
http://en.cppreference.com/w/cpp/language/type_alias
有 template using和普通using两种，可以赋予新名称。
using identifier attr(optional) = type-id ; (1) 
template < template-parameter-list >
using identifier attr(optional) = type-id ;

(2) 

# virtual语法和=0
=0必须与virtual联用。
# 取析构函数地址：taking address of destructor 'Bar::~Bar'
类似的错误还有：
taking address of constructor 'Bar::Bar'
取成员函数地址是可行的，但是析构函数和构造函数不行。
成员函数通常调用时使用的语法是：bar->*fun()..
bar在调用时已经构造完成，不存在让其再被构造一次的做法。

C++ standard says :
$12.1/10: “The address of a constructor shall not be taken.”.

而且，手动调用析构函数的唯一时机，应当是使用placement new的时候。这个时候对对象进行重构可以使用。

为了在shared_ptr中传入栈上的指针并且使用其析构函数，下面的函数应当为我们所用：
```
# 析构函数
```c++

class Foo{
public:
    ~Foo()
    {
        cout << "~Foo"<<endl;
    }
};
class Foo2{
protected:
    ~Foo2(){
        cout << "~Foo2"<<endl;
    }
};
class Widget{
public:
    ~Widget(){
        cout << "~Widget" << endl;
    }
};
class Widget2{
public:
    ~Widget2(){
        cout <<"~Widget2"<<endl;
    }
};

class Bar : public Foo,public Foo2{
public:
    ~Bar(){
        cout << "~Bar" << endl;
    }
    Widget w;
    Widget2 w2;
};
int main(int argc,char *argv[])
{
    Bar b;
    b.~Bar();
}
```
顺序：
```c++
~Bar
~Widget2
~Widget
~Foo2
~Foo
```
继承：如果一个类含有private的析构函数，则这个类不能用作基类
成员：如果一个类含有private,protected的析构函数，则不能用作成员
顺序：多重继承中，析构顺序是1.子类的析构函数体，2.子类非引用、非基本类型成员按倒序析构 3.继承的基类按声明倒序析构

# 联合中的初始化
```c++
#define DEFUN(name) name(){cout << #name << endl;}
class Bar{
public:
    DEFUN(Bar);
    DEFUN(~Bar);
};
class Widget{
public:
    DEFUN(Widget);
    DEFUN(~Widget);
};
class Foo{
public:
    DEFUN(Foo);
    DEFUN(~Foo);
    union{ // 即使注释掉b，编译器仍然不能自动生成，提示为ill-formed
        Bar b;
        Widget w;
    };
};
```
对Foo进行初始化:
```c++
Foo f;
```
则因为联合的初始化是编译器不能决定的，如果没有定义Foo(),~Foo(),编译器由于不能生成正确的函数，所以默认不生成。
这种情况下，必须自己定义初始化函数和析构函数。
注意：如果union是一个单纯的简单结构，也就是说union不含任何class对象，则编译器可以处理。但是只要含有一个类对象，编译器都拒绝自动生成。
# shared_ptr和unique_ptr
shared_ptr默认使用delete p;来删除所管理的对象。但是也能传递额外的参数让其在资源引用为0时进行删除。

std::default_delete<_Tp>
std::default_delete<_Tp[]> 可以用来生成默认的删除函数

但是没有std::default_destruct<_Tp>

# 右值引用
```c++

class Foo{
public:
    Foo& operator=(const Foo &)  {
        cout << "operator="<<endl;
        return *this;}
    Foo()=default;
    Foo(const Foo &)
{
        cout << "copying" << endl;
}
    Foo(Foo &&){
        cout << "moving"<<endl;
    }
};

Foo foo_copy_move(Foo &&f)
{
    Foo f3=std::move(f);
    cout << "foo_copy_move"<<endl;
    cout << &f << endl;
    return f;
}
Foo&& foo_nothing(Foo &&f)
{
    cout << "foo_nothing" <<endl;
    cout << &f << endl;
    Foo localF=f;
    return std::move(f=localF);//只有operator=发生，而构造函数没有发生，因为函数签名和f的类型匹配。但是在使用过程中f不具有主动成为移动的性质。
}


int main(int argc,char *argv[])
{
    foo_copy_move(foo_copy_move(Foo()));
    foo_nothing(foo_nothing(Foo()));
    cout << "END."<<endl;
    return 0;
}
```
结果：
```c++
moving
foo_copy_move
0xffffcb0d
copying
moving
foo_copy_move
0xffffcb0e
copying
foo_nothing
0xffffcb0f
copying
operator=
foo_nothing
0xffffcb0f
copying
operator=
END.
```
上面的例子我们可以看出，对象地址没有改变，因此我们使用的一直都是同一个临时对象。

# 关于字面量
c++11中有两条关于字面量的语法，从stroustrup的网站上可以找到：
R"(...)" 用于表示字面量，但是其实任何R"----(开头的，只要有)----"结尾即可。

自定义字面量通过重载操作符""来完成
string operator()""s(const char *ch,size_t n){return std::string(ch,n);}
更多例子参见其网站。
注意：不以_开头的后缀可能产生“将来用于标准化”的警告，所以自定义的后缀最好以_开头。

# 类内初始化
类内允许初始化，相当于指定默认值。

# write your own allocator
64位下，当在c++中写下这样的语句时：
```c++
#include <new>
#include <memory>
#include <utility>
#include <cstdlib>

int main()
{
        std::malloc(30);

        new char[30];
}
```
汇编：
`g++ test_new_no_stdlib.cpp -S -o test_new_no_stdlib.s -O0`
汇编实际生成的调用是：
```java
        movl    $30, %ecx
        call    malloc
        movl    $30, %ecx
        call    _Znam
```
也就是说，malloc的链接名称就是malloc,而new(内置类型)的名称则是_Znam.
如果以32位模式编译，
`g++ test_new_no_stdlib.cpp -S -o test_new_no_stdlib.s -O0 -m32`
则是：
```java
        movl    $30, (%esp)
        call    _malloc
        movl    $30, (%esp)
        call    __Znaj
```
不同的编译模式有不同的链接名称。所有的符号都至少生成一个"_",以便使用c语言函数进行链接。
注意：g++的-nostdlib只影响链接阶段
https://gcc.gnu.org/onlinedocs/gcc/Link-Options.html
对于上面的文件，使用-nostdlib可以继续编译成可启动的文件（实际上object文件就够了
`g++ test_new_no_stdlib.cpp -o test_new_no_stdlib.a -O0 -m32 -nostdlib -static -fno-exceptions`
则报错
```java
/tmp/ccjcQpr3.o:test_new_no_stdlib.cpp:(.text+0xa)：对‘__main’未定义的引用
/tmp/ccjcQpr3.o:test_new_no_stdlib.cpp:(.text+0x16)：对‘malloc’未定义的引用
/tmp/ccjcQpr3.o:test_new_no_stdlib.cpp:(.text+0x22)：对‘operator new[](unsigned int)’未定义的引用
```
这说明，其实如果自己的库提供了这些函数，根本就不必再使用标准静态库。而标准库大多数头文件都是可以使用的。

而且用这个方法我们可以检测出大多数需要自己定义的东西。方法是仅仅包含一个头文件，然后编译看看产生了什么错误。
源文件模板如下：
```c++
#include <iostream>
int main()
{

}
```
编译选项如下：
`g++ test_new_no_stdlib.cpp -o test_new_no_stdlib.a -O0 -m32 -nostdlib -static -fno-exceptions`
实例错误如下
```java
/tmp/ccitCK0V.o:test_new_no_stdlib.cpp:(.text+0x7)：对‘__main’未定义的引用
/tmp/ccitCK0V.o:test_new_no_stdlib.cpp:(.text+0x2f)：对‘std::ios_base::Init::Init()’未定义的引用
/tmp/ccitCK0V.o:test_new_no_stdlib.cpp:(.text+0x37)：对‘__dso_handle’未定义的引用
/tmp/ccitCK0V.o:test_new_no_stdlib.cpp:(.text+0x46)：对‘std::ios_base::Init::~Init()’未定义的引用
/tmp/ccitCK0V.o:test_new_no_stdlib.cpp:(.text+0x4b)：对‘__cxa_atexit’未定义的引用
collect2: 错误：ld 返回 1
```
ios_base::Init::Init(), __dso_handle,__cxa_atexit都是未定义的符号

string的错误
        对‘std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string()’未定义的引用
         对‘std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()’未定义的引用
vector的错误
        对‘__wrap__ZdlPv’未定义的引用
regex的错误
        对std::locale::locale()’未定义的引用
        对std::locale::~locale()’未定义的引用