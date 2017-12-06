# 此文件
此文件对g++编译器的总体进行描述，常见错误放在分册GNU_cc_errors.md中，优化部分放到GNU_cc_optimize.md中

# How g++ works?

# 编译选项说明
参见gcc/g++  x86 Options一节的信息
Info: (gcc)x86 Options, 1174 lines --92%

-m32	为32位环境生成代码，目标CPU为i386.定义int,long,指针的长度为32位
-m64	为64位环境生成汇编代码，int长度32位，long,指针均为64位
-m16	同-m32,只是会在文件的首部添加.code16gcc，因此生成的是类似.code16的代码，只是堆栈框架是32位的
-march=CPU_TYPE	生成指定处理器的代码
	CPU_TYPE取值 native 本机
			i386		i486	i686等
			注意，CPU和32位是两个维度，更先进的CPU也能运行16位的代码


# template实例化和ld的问题
g++对template的代码生成属于复制型，所以如果一个泛型没有被引用过，则它不会生成任何一份代码。
g++需要具体的类型来计算空间，生成代码。
template class Foo<Bar>;  对Foo<Bar>这个实例化模板生成代码，也就是说，着条语句实际上是在指示g++：将模板的 代码防止到该处。

一种很常见的错误是，没有实例化某个类，因此ld过程中出现undefined reference错误，这时，在任意一个仅编译一次的源文件（而不是头文件）中添加实例化语句即可。
顺序和位置没有关系。如果错误过多，逐条分析，逐个定义，最终肯定会定义完。

对于编译64位目标机器上的程序，不要单独使用ld。


# 16位和32位的区别
对同一条指令 mov $34,%eax   由于这是一条32位指令，16位代码会生成额外的前缀；32位不会
CPU刚上电时是16位模式，有ax寄存器但是没有eax寄存器
只有当切换到保护模式之后，才能使用eax寄存器

# 内联汇编标号的使用
在汇编代码中生成的标号必须以数组形式引用，g++支持extern声明数组的长度：
extern "C" size_t bootCodeInfo[2];
__asm__(
	"_bootCodeInfo:\n\t"
	".int 0,0 \n\t"
	);
通过数组就可以实现对该处值的引用。这可以用来解决as中不能交叉定义分区，存放数据；通过在.text区声明一个标号，然后extern外部c引用即可。
# 语言部分
偏特化：c++的类支持偏特化
模板和静态类：类如果具有模板，静态函数也具有模板，则两者不能相同，否则提示：declaration of template parameter 'T' shadows template parameter。可以通过下面的方式调用：Foo<int>::bar<char>();其中Foo是类，bar是具有模板的静态函数或者成员方法。
  如果需要在外部定义，则类模板先写，函数模板再写
```c++
template <class T>
class V{
public:
  template <class M>
  void foo2()
  {
    cout << "foo2"<<endl;
  }
  template <class M>
  static void foo();

};

template<class T>
template <class M>
inline void V<T>::foo() {
  cout <<typeid(T).name()<<endl;
  cout <<typeid(M).name()<<endl;

  cout <<"foo"<<endl;
}

int main(int argc,char *argv[])
{
  V<short>::foo<int>();
  V<short> v;
  v.foo2<int>();
  cout << " "<<endl;
  return 0;
}
```

对齐的概念：一个结构体自身的对齐alignof是其内部字节最大者，以及系统的最大值决定的。对齐还受pack的影响。

gcc声明的always_inline的函数,还需要加上inline声明。函数的定义体只要在同一编译过程中出现即可。

using声明
  using具有两方面的作用并且具有两种不同的形式，第一种形式是using =,也就是定义别名； 第二种不含等号，这种情况下，如果使用using一个命名空间，意味着可以不用使用命名空间限定符(std::),如果using一个类，则这个类必须是该类的基类，using可用于引入静态函数；如果是private继承，可以更改访问权限。

# 语法层面上的空结构与运行时开销
```c++
//空结构
class int2type{
  
}

void test_int2type(int i,int2type,int j)
{
  cout << ((char*)&j - (char*)&i) << endl;
}
void test_int2type(int i,int j)
{
  cout << ((char*)&j-(char*)&i)<<endl;
}
```
两个函数的结果分别是：16,8。这就意味着在64位机器上无论传入什么参数，总是按照最长位数一次压入的，这也比较容易理解：因为寄存器的长度就是这么长。
这个测试对于那些使用分发技术的函数而言，可能会稍微增加一点运行时开销（或者编译器可以直接优化为仅仅将栈指针增加而不压入数，因为这个变量没有被引用），但是这种开销其实算不了什么。

# sizeof
64位机器上，下面三个是等价的：
```c++
  cout <<sizeof(long)<<endl;
  cout <<sizeof(long int)<<endl;
  cout <<sizeof(long long)<<endl;
```
都是8


# 编译效率和预编译文件（未完成）
使用预编译头部：链接
选项 -Winvalid-pch  开启关于使用预编译头部的警告

生成预编译头部：g++ xx.h
xx.h的要求：存放一些不经常变动的引入。记住，使用预编译头部的作用是为了防止初次编译后再次编译的慢速。如果一个文件经常改动，也就意味着没有初次编译即可用的特性。

预编译头的适用范围是什么？必须放在哪里使用？
不同的编译选项能够产生不同的预编译文件，对某个特定的编译选项，如何指定使用某个特定的预编译版本？（可能通过文件夹的方式区分）

这些有待测试


# 为什么g++要有链接时附加库而不是从源文件直接产生
1. 头文件可以给出模板的声明和定义，可以给出非模板的声明。但是如果一个函数不是模板，就一定要生成代码（无论有没有引用）。如果多个文件分别编译，就会产生多份代码，导致链接时冲突
2. 预先编译好的库可以节省编译时间，因为标准库通常很少变化，一次编译后即可使用
3. 使用这些库来*补偿*编译过程。注意这里说的是补偿，编译过程中可以不使用这个补偿(-nostdlib),代价要么自己加入标准库实现文件一起编译，要么自己手动编写函数，要么接受链接错误
4. 当然，你可以使用自己编写的附加库，只有能够*补偿*编译过程即可。 

# 编译器预定义宏函数和宏常量
_GLIBCXX_EXPORT_TEMPLATE  是否使用export template.通常而言，该值未定义，也就意味着没有提供export关键字的支持
__is_trivial(type) 注意，这是宏函数，因此能够以类型作为参数调用
__is_pod(type)
__builtin_abort()  无参宏函数
# 扩展(动态)内联汇编
快速参考：http://ericw.ca/notes/a-tiny-guide-to-gcc-inline-assembly.html
常用形式：
asm [volatile] ( AssemblerTemplate 
                 : OutputOperands 
                 [ : InputOperands
                 [ : Clobbers ] ])
 InputOperands的形式：[ [asmSymbolicName] ] constraint (cexpression)  多个操作数使用","分隔
 	asmSymbolicName表示定义一个符号，其后在汇编内容中使用%[name]来引用这个输入
 	如果没有定义，使用 %N来引用，N是Output+Input按顺序从0计算的标号
 	constraints：m,r,i,0表示输入参数存储的位置不同
 	m: The operand is stored in memory, at any memory address. (Instructions will operate on the data directly in memory.)
	r: The operand is stored in a general-purpose register. (GCC generates code to transfer the operand to or from memory and the register it chooses.)
	i: The operand is an immediate integer.
	0,…,9: The operand matches the operand with the specified number. (GCC will use the same variable for both operands. The two operands that match must be one input-only operand and one output-only operand.)
 
 	=: Operand is write-only
	+: Operand is both read and written
	&: Operand is clobbered early (i.e., is modified before the instruction is finished using the input operands, meaning it may not lie in a register used as an input operand or any part of memory)
 OutputOperands的形式： 
 	contraint 必须以'='开始，或者'+'开始
 
 例子：
```c++
 /* Rotating bits example */
asm("mov %[result], %[value], ror #1" : [result] "=r" (y) : [value] "r" (x));
```


To load the interrupt descriptor table register:
```c++
    void set_idt (idt_pointer_t *ptr) {
        __asm__ __volatile__ (
        "lidt %0 \n" : : "m"(ptr) ); //使用内存
    }
```
    
   注意：如果想要传递m，只需传递参数名称即可，不必传递地址
  要记住：内联参数时模板，是语法性的
  记住：使用"m",则意味着引用时可以看成这个参数的地址
```c++ 
//To set the kernel code segment: //使用立即数
    void set_kcs () {
        __asm__ __volatile__ (
        "ljmp %0, $farjmp \n"
        "farjmp: \n"
        "nop \n"
        : "i"(KERNEL_SEG_CODE)
        );
      }
```

 

# g++代码生成简述
概念：mangled demangled abi
mangled name是指C++编译一个符号后生成的字符串，比如一个定义的函数：
```c++
vector<int> blah(const vector<int> &);
```
生成的符号是：_Z4blahRSt6vectorIiSaIiEE

# 注意关于中间汇编生成和直接生成
直接使用g++生成object文件会包含__exit等注册类函数，在主机上最好先生成汇编代码，然后使用as编译后再生成目标文件，这样就不会含有不必要的注册函数。

# C++ 特殊语法
注意：一切inline的基础是在编译文件时能够获得函数的代码
extern inline		---  表明这个函数仅仅用于内联，绝对不要保留其代码。可定义成 ONLY_INLINE
static inline   --- inline，如果函数地址没有被引用，则将函数代码删除（即不生成函数体），除非-fkeep-inline-functions。当然，该函数可能inline失败，则保留定义，无任何影响。可定义成PREFER_INLINE

g++/gcc在没有开启优化选项的情况下不会inline任何函数，即使声明为inline.除非使用__attribute((__always_inline__))



# 链接器选项
https://gcc.gnu.org/onlinedocs/gcc/Link-Options.html
```java
-nostartfiles
Do not use the standard system startup files when linking. The standard system libraries are used normally, unless -nostdlib or -nodefaultlibs is used.

-nodefaultlibs
Do not use the standard system libraries when linking. Only the libraries you specify are passed to the linker, and options specifying linkage of the system libraries, such as -static-libgcc or -shared-libgcc, are ignored. The standard startup files are used normally, unless -nostartfiles is used.

The compiler may generate calls to memcmp, memset, memcpy and memmove. These entries are usually resolved by entries in libc. These entry points should be supplied through some other mechanism when this option is specified.

-nostdlib
Do not use the standard system startup files or libraries when linking. No startup files and only the libraries you specify are passed to the linker, and options specifying linkage of the system libraries, such as -static-libgcc or -shared-libgcc, are ignored.

The compiler may generate calls to memcmp, memset, memcpy and memmove. These entries are usually resolved by entries in libc. These entry points should be supplied through some other mechanism when this option is specified.

One of the standard libraries bypassed by -nostdlib and -nodefaultlibs is libgcc.a, a library of internal subroutines which GCC uses to overcome shortcomings of particular machines, or special needs for some languages. (See Interfacing to GCC Output in GNU Compiler Collection (GCC) Internals, for more discussion of libgcc.a.) In most cases, you need libgcc.a even when you want to avoid other standard libraries. In other words, when you specify -nostdlib or -nodefaultlibs you should usually specify -lgcc as well. This ensures that you have no unresolved references to internal GCC library subroutines. (An example of such an internal subroutine is __main, used to ensure C++ constructors are called; see collect2 in GNU Compiler Collection (GCC) Internals.)
```

-nostartfiles
-nodefaultlibs
-nostdlib   等于上面两个一起使用。如果禁用了libc，则编译器生成的对于memcmp, memset, memcpy和memmove的调用必须在其他库中以等价的方式提供。
# 能够动态设置段超越前缀吗？
默认情况下所有的数据都是通过ds来访问的，有没有办法让g++将段超越前缀修改成es?

# 附录：警告选项【Info: (gcc)Option Summary】
注：加上no-前缀就可以取反
'-fmax-errors=N'  遇到N个错误时停止编译；N=0无限制
'-Werror'  使所有的警告信息变成错误信息
'-w'    抑制输出错误信息
'-Wfatal-errors'  遇到第一个错误就停止
'-Wall'   启用所有的编译警告
'-Wcomment'   警告不合法的注释格式
'-Wchkp'    警告指针越界，参考-fcheck-pointer-bounds
'-Wno-cpp'   将#warning产生的警告信息过滤掉
'-Wdouble-promotion' 在一些机器上float是效率最高的浮点类型，但是可能被提升为double，这可能很耗时
'-Wformat'    警告format类型的参数
'-Wnonnull'   和函数的属性nonnull配合使用
'-Wno-deprecated'   不对deprecated函数警告
-Wunused-variable   未使用的变量
-Weffc++           如果违背了Effective C++的准则，就警告
 -Wfloat-equal    浮点数比较是否相等时警告
  -Wignored-qualifiers  类型限定符如果被忽略就警告
  -Winvalid-pch   如果找到预编译文件但是未使用，就警告
   -Wlogical-op  如果该符号不起作用，警告
    -Wlogical-not-parentheses   未加括号
  -Wmisleading-indentation  缩进不正确
  -Wnarrowing  c++统一初始化操作{}中发生向窄转换时
  -Wnon-virtual-dtor  非虚析构函数
  -Wold-style-cast  c强制转换
  -Wold-style-declaration  老式声明
  -Wprotocol   如果继承方法未被实现
  -Wreorder    当代码块被重新安排时




# 附录：pragma指令
'#pragma GCC target ("STRING"...)'
  指定目标架构，同__attribute__((target("STRING"))).目前实现的由x86,PowerPC和Nios II.
'#pragma GCC optimize ("STRING"...)' 指定优化选项，参见属性
'#pragma GCC push_options'
'#pragma GCC pop_options'  把当前选项压入栈
'#pragma GCC reset_options'  重置由target,optimize指定的选项，恢复命令行选项

'#pragma GCC system_header'
所谓System Header指定是，操作系统和运行时库的代码通常不能用一致(conforming)的C语言写出来，因此在g++中可能出现warning。 g++给与这些文件特殊对待，所有warning信息（除了#warning)会被屏蔽掉。
通常, -isystem -idirafter  以及上面的#pragma指令都会令一个文件成为System Header.

# 附录：\_\_attribute\_\_属性集合
参考：https://gcc.gnu.org/onlinedocs/gcc/Attribute-Syntax.html
参考：Info: (gcc)Common Function Attributes, 979 lines
语法 : \_\_attribute\_\_ ((attribute-list))
对于任何attribute属性，都可以添加__来防止与已定义的符号冲突，比如noreturn可以写成__noreturn__
##存储
aligned (alignment)   设置存储对齐，最大值为__BIGGEST_ALIGNMENT__
warn_if_not_aligned (alignment)   如果一个内容的地址没有对齐相应的值
common
nocommon  common和nocommon使gcc将一个变量放在"common"存储区
packed  使结构体尽量占用更小的空间，实际上就是#pragma pack(1)
vector_size (bytes)   设置变量的
##用于变量

##struct或者union


##下面用于函数
section("name")	放到某个区
\_\_always_inline\_\_ 总是内联汇编，保证不会生成单独的函数体。如果不能则产生编译错误
cold			声明一个函数很少使用，优化主要针对大小而不是速度；所有的cold函数都会被放在一起，以便其他函数之间地址相近
deprecated ("MSG")	MSG是可选的，用于警告使用一个已经过时的函数
hot				标记一个函数经常被调用，所以需要尽量优化它
interrupt, interrupt_handler	标记一个函数是中断处理，生成不一样的进入代码
noinline		不要内联
nonnull (ARG-INDEX,...)		标记一个函数的参数不能为null，如果编译器检测到null，配合-Wnonnull,就会发出警告
```c++
          extern void *
          my_memcpy (void *dest, const void *src, size_t len)
                  __attribute__((nonnull (1, 2)));
```
		下标从1开始，如果没有提供列表，则所有参数不为NULL
noreturn 标注一个函数从不会返回，据此g++可以生成更好的代码

```c++
          void fatal () __attribute__ ((noreturn));

          void
          fatal (/* ... */)
          {
            /* ... */ /* Print error message. */ /* ... */
            exit (1);
          }
```
nothrow		不抛出异常，大多数c函数都不抛出异常
pure		函数没有副作用，仅仅使用输入参数，仅仅返回数值，没有其他影响。这样的函数可以像操作符一样优化
```c++
			int square (int) __attribute__ ((pure));
```

returns_nonnull	函数不会返回NULL
used		标注一个函数会被使用，所以它的代码一定会被生成而不是优化掉
malloc    表明这是一个类似于malloc的函数
optimize  指定对该函数的优化或者其他选项，如果参数是数字A，等价于-O A；如果参数是字符串，且以O开头，则等价于其自身；其他的，考虑为-f开头。可以使用#pragma GCC optimize来优化多个函数
externally_visible 该类函数不会成为static函数。默认情况下所有函数都具有此属性，但是对于不同的链接器，一个显示的该声明是必须的
```
'-fwhole-program'
     Assume that the current compilation unit represents the whole
     program being compiled.  All public functions and variables with
     the exception of 'main' and those merged by attribute
     'externally_visible' become static functions and in effect are
     optimized more aggressively by interprocedural optimizers.

     This option should not be used in combination with '-flto'.
     Instead relying on a linker plugin should provide safer and more
     precise information.

...
'externally_visible'
     This attribute, attached to a global variable or function,
     nullifies the effect of the '-fwhole-program' command-line option,
     so the object remains visible outside the current compilation unit.

     If '-fwhole-program' is used together with '-flto' and 'gold' is
     used as the linker plugin, 'externally_visible' attributes are
     automatically added to functions (not variable yet due to a current
     'gold' issue) that are accessed outside of LTO objects according to
     resolution file produced by 'gold'.  For other linkers that cannot
     generate resolution file, explicit 'externally_visible' attributes
     are still necessary.
```

# 下面是x86专用的
cdel  假设调用一个函数时，函数内部会将堆栈平衡
fastcall  将ecx,edx作为参数传递的寄存器，被调用函数会平衡堆栈；可变参数函数的所有参数被push到栈上
naked   表明函数体不需要任何序言和离开动作（即push/pop堆栈），生成纯粹的汇编代码  -- 经测试，改属性被忽略,该属性应当是ARM等其他架构的，x86不支持
stdcall 对于固定参数，自动平衡堆栈；对于可变参数，不平衡堆栈

# 附录：预处理器选项
          -AQUESTION=ANSWER
          -A-QUESTION[=ANSWER]
          -C  -dD  -dI  -dM  -dN
          -DMACRO[=DEFN]  -E  -H
          -idirafter DIR
          -include FILE  -imacros FILE
          -iprefix FILE  -iwithprefix DIR
          -iwithprefixbefore DIR  -isystem DIR
          -imultilib DIR -isysroot DIR
          -M  -MM  -MF  -MG  -MP  -MQ  -MT  -nostdinc
          -P  -fdebug-cpp -ftrack-macro-expansion -fworking-directory
          -remap -trigraphs  -undef  -UMACRO
          -Wp,OPTION -Xpreprocessor OPTION -no-integrated-cpp
'-imacros FILE'
      同-include，但是只会保留宏定义。所有的-imacros在-iinclude之前处理
'-idirafter DIR' 将DIR加入include搜索路径，但是出于系统路径和-I指定的路径之后
'-fdollars-in-identifiers'  允许美元符号出现在标识符中
'-fextended-identifiers'  允许任意字符（如果python）用作标识符，默认启用
'-fpreprocessed' 暗示输入文件已经预处理，因此编译器不再执行宏展开等众多指令。如果文件本身具有.i,.ii,.mi结尾，那么这个选项默认启用。
'-fdebug-cpp'   显示CPP的调试信息

# 附录：-O优化选项
'-O0'  减少编译所需的时间。默认选项
'-O'或者'-O1'  编译器尝试减少代码的数量和执行时间，但是不优化编译所需的时间.'-O'开启了下面这些选项：
          -fauto-inc-dec
          -fbranch-count-reg
          -fcombine-stack-adjustments
          -fcompare-elim
          -fcprop-registers
          -fdce
          -fdefer-pop
          -fdelayed-branch
          -fdse
          -fforward-propagate
          -fguess-branch-probability
          -fif-conversion2
          -fif-conversion
          ....
          -ftree-ter
          -funit-at-a-time
'-O2'  在'-O1'的基础上开启
-finline-small-functions
 -fexpensive-optimizations
 -foptimize-strlen
 -fpartial-inlining
 ...

'-O3' 在'-O2'的基础上开启
'-finline-functions',
     '-funswitch-loops', '-fpredictive-commoning',
     '-fgcse-after-reload', '-ftree-loop-vectorize'
     ...
     '-fipa-cp-clone'
'-Os'  优化代码的体积,该选项开启'-O2'中那些不会明显增加代码体积的优化，同时禁用那些增加体积的优化
'-Og'  优化调试体验。启用所有的不影响调试的优化选项。这应当是'edit-compile-debug'循环的最佳选项


# 附录：其他选项
所有的代码生成相关的选项：
          -fcall-saved-REG  -fcall-used-REG
          -ffixed-REG  -fexceptions
          -fnon-call-exceptions  -fdelete-dead-exceptions  -funwind-tables
          -fasynchronous-unwind-tables
          -fno-gnu-unique
          -finhibit-size-directive  -fno-common  -fno-ident
          -fpcc-struct-return  -fpic  -fPIC -fpie -fPIE -fno-plt
          -fno-jump-tables
          -frecord-gcc-switches
          -freg-struct-return  -fshort-enums  -fshort-wchar
          -fverbose-asm  -fpack-struct[=N]
          -fleading-underscore  -ftls-model=MODEL
          -fstack-reuse=REUSE_LEVEL
          -ftrapv  -fwrapv
          -fvisibility=[default|internal|hidden|protected]
          -fstrict-volatile-bitfields -fsync-libcalls

'-mpic-data-is-text-relative'  设定所有的数据段都是相对于代码段的，因此可以使用相对于PC（程序计数器）的数据操作指令。默认启用
'-mno-sep-data'  生成的文件假定：数据段在代码段之后。默认启用
'-static'  在支持动态链接的系统上，避免使用动态链接；在其他系统上被忽略。
'-shared'   生成可共享的对象文件，同时必须制定-fPIC或者-fpic等选项。因为共享的对象文件必须使用位置无关代码。
'-fpic' 生成位置无关代码。位置无关代码使用GOT(一个记录所有变量的偏移的表)，动态加载器（操作系统软件）先查找GOT表，检查GOT的大小是否超限（x86没有限制），如果超限，需要使用-fPIC。这个选项会定义宏__pic__=1,__PIC__=2
'-fPIC' 生成位置无关的代码，该代码可以动态链接，不限制GOT的大小。由于不同的机器对位置无关代码的支持不同，因此只支持几种机器。这个选项会定义宏__pic__=2,__PIC__=2
'-fpie'
'-fPIE'  与-fpic,-fPIC类似，但是保证代码只被链接到可执行文件（-fpic可以链接到任意文件）

# 语言相关
-fsigned-char|-funsigned-char   设定char类型的默认值。当然，使用char时最好指定前缀类型，没人知道你是什么意思。



# 优化选项
<!-- 注意：不要尝试与-On联合使用，比如-fomit-frame-pointer与-O1就不能真正把堆栈框架取消掉，-O3可以 -->
'-fomit-frame-pointer'  不生成堆栈框架；这个选项在编写中断或者其他程序时非常有用
'-fno-inline'   不要内联任何函数，除了always_inline的函数。当没有开启优化时 ， 此项默认启用
'-finline-functions' 将所有函数看成可以内联的，然后进行内联。如果static函数被内联，则该函数不会产生函数体输出
'-finline-functions-called-once' 将所有static的仅仅调用过一次的函数，即使它没有声明inline，也将其内联
'-fno-zero-initialized-in-bss' g++默认将所有初始化为0的数据放到.bss区，此选项关闭这个行为。默认开启

'-faggressive-loop-optimizations'  对循环进行优化。默认启用

'-funsafe-loop-optimizations'  不安全的循环优化

'-fexpensive-optimizations'  一些次要的但是耗时的优化

'-fcombine-stack-adjustments' 找到pop,push的操作，尝试组合它们。-O1开启

'-fconserve-stack'  减少对栈的使用，即使这会降低程序速度

'-floop-nest-optimize'  实验性质的优化

'-fvariable-expansion-in-unroller'  产生一个变量的多个副本

'-funit-at-a-time'  此命令无影响，兼容性。

'-freorder-blocks-and-partition'  
'-freorder-blocks-algorithm=stc'
'-freorder-blocks’
    当使用-Os时，这些被默认禁用



-ffunction-sections
-fdata-sections
  使用函数或者数据自身的名称作为区名。
# -M系列选项
-M  不生成预处理结果文件，而是生成适合make使用的规则。 -M本身包含-E。
-MM 同-M，但是不包含系统文件
-MF 指定-M系列的输出文件。如果未指定，为标准输出
-MP  为每个头文件生成必要的phony目标，比如
```make
          test.o: test.c test.h

          test.h:
```
'-MT TARGET' 改变规则中的target部分的名称
-MD  =>-M -MF FILE，但是不启用-E，因此-E需要自己开启
-MMD  同-MD但是系统头文件不被含入。
'-fpch-deps'  待注释
'-fpreprocessed'
'-fpch-preprocess'
