# 此文件


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

# using的用法
http://en.cppreference.com/w/cpp/language/type_alias
有 template using和普通using两种，可以赋予新名称。
using identifier attr(optional) = type-id ; (1) 
template < template-parameter-list >
using identifier attr(optional) = type-id ;

(2) 

# virtual语法和=0
=0必须与virtual联用。