# 此文件
此文件记录了g++的意想不到的错误

# char类型和0x80比较
参见问题：https://stackoverflow.com/questions/47475630/g-generate-logically-wrong-assembly-code
有下面的函数：
```c++
    //文件名: test.cpp
    __asm__(".code16gcc \n\t");
    int equals0(char i)
    {
        return i==0x80;
    }
    int equals1(char i)
    {
        return i==0x10;
    }
    int equals2(int i)
    {
        return i==0x80;
    }
```

不启用任何优化选项编译，g++版本号：g++ (GCC) 6.4.0
编译选项：g++ -S test.cpp -o test.s -m32 
注：这个选项也是编译x2内核所使用的选项
查看test.s文件
```js
    // ... 省略掉一些不必要的信息
    .code16gcc 
    
    .text
    ...
__Z7equals0c://equals0函数
    pushl   %ebp
    movl    %esp, %ebp
    subl    $4, %esp
    movl    8(%ebp), %eax
    movb    %al, -4(%ebp)
    movl    $0, %eax   //---总是返回0
    leave
    ret
    ...
__Z7equals1c://equals1函数
    pushl   %ebp
    movl    %esp, %ebp
    subl    $4, %esp
    movl    8(%ebp), %eax
    movb    %al, -4(%ebp)
    cmpb    $16, -4(%ebp)  // -- 有比较的代码
    sete    %al
    movzbl  %al, %eax
    leave
    ret
    ...
__Z7equals2i://equals2函数
    pushl   %ebp
    movl    %esp, %ebp
    cmpl    $128, 8(%ebp) //有比较的代码
    sete    %al
    movzbl  %al, %eax
    popl    %ebp
    ret
```

从上面的生成文件中，可以看出，无论是否开启优化，g++总会认为所有的char类型与一个最高位是1的char型数比较返回假，其中的原因则不太清楚。

注：任何时候，比较char类型时，使用unsigned转换成无符号数。  提倡使用unsigned char,因为与立即数总是被认为是unsigned char类,立即数而后缀必须也加上u
注：此问题曾经出现过很多次

# 环形依赖
这个问题经常出现但是又经常被忽略，直到最后才能发现问题。

这是个问题：IDE不能判断出环形依赖所在，所以这个问题在编辑早期不能被发现。

这个问题会导致：引用在定义之前出现；
编译器发出： was not declared in this scope 的错误信息

但是编译器与此相同发出错误信息的还有其他类型的错误，一种就是不经意间在class内部引入了头文件：
```c++
class Wrapper{
public:
    /*...*/
#if defined(CODE64)
#include <EnvInterface64Impl.h>
  void dumpInfo(EnvInterface64Impl *env);
#endif
};
```

这种做法常常导致不知名的错误，虽然看起来整个文件被引入了，但是却改变了所属的命名空间。

最佳实践：不要在头部之外使用#include


# printf打印结果出错
printf的每个参数都有相应的长度要求，比如，在64位系统上，%d表示需要一个32位长度的数字。
这就意味着需要小心翼翼地平衡所有的堆栈，因此，在要求严格的系统上，弃用printf，使用更严格的printf实现，比如只接受int参数的printf，接受有限int参数的printf。

安全的printf实现如下：
    int printf_simple(const char *fmt,int arg0=0,int arg1=0,int arg2=0);


# 文件读写问题
http://en.cppreference.com/w/cpp/io/c/fopen
注意，"w"会将文件清空。
使用"r+

filename    -   file name to associate the file stream to
mode    -   null-terminated character string determining file access mode
File access 
mode string Meaning Explanation Action if file 
already exists  Action if file 
does not exist
"r" read    Open a file for reading read from start failure to open
"w" write   Create a file for writing   destroy contents    create new
"a" append  Append to a file    write to end    create new
"r+"    read extended   Open a file for read/write  read from start error
"w+"    write extended  Create a file for read/write    destroy contents    create new
"a+"    append extended Open a file for read/write  write to end    create new
File access mode flag "b" can optionally be specified to open a file in binary mode. This flag has no effect on POSIX systems, but on Windows, for example, it disables special handling of '\n' and '\x1A'. 
On the append file access modes, data is written to the end of the file regardless of the current position of the file position indicator.
File access mode flag "x" can optionally be appended to "w" or "w+" specifiers. This flag forces the function to fail if the file exists, instead of overwriting it. (C++17)
The behavior is undefined if the mode is not one of the strings listed above. Some implementations define additional supported modes (e.g. Windows).

为了读写一个已经存的文件，并且与平台无关，正确的方式是：
    FILE *fp=fopen(file,"rb+"); // 读写模式打开
    if(fp==NULL) // 文件不存在
    {
        fp=fopen(file,"wb+");// 使用w创建
    }

使用fstream的方式：
    std::fstream fs(sysFile,std::fstream::in|std::fstream::out);//如果文件不存在，打开空的
    if(!fs.is_open()) // 文件不存在
        fs.open(sysFile, std::fstream::out);
注意，如果不检测文件是否已经关联(is_open)，则如果文件不存在，根本就不会创建。只有out模式才能使其存在

# malloc/free
注意：如果你遇到了malloc/free带来的错误，那么检查以下几点
1.malloc的实际申请的内存大于返回的内存，因此如果你写超过自己申请的大小，系统不会报错。但是由于在额外的内存区域存放一些管理信息，因此free时会报错。
检查你的代码有没有这种类型的潜在错误。

# 模板和静态函数
如何在模板类中定义带有模板的静态函数？如何调用这个函数

# 函数定义
如果函数声明中已经有了默认参数，函数定义中不能出现默认参数。否则就是重定义。