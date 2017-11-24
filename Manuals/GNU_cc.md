# 此文件


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
 /* Rotating bits example */
asm("mov %[result], %[value], ror #1" : [result] "=r" (y) : [value] "r" (x));

To load the interrupt descriptor table register:
    void set_idt (idt_pointer_t *ptr) {
        __asm__ __volatile__ (
        "lidt %0 \n" : : "m"(ptr) ); //使用内存
    }
    
    注意：如果想要传递m，只需传递参数名称即可，不必传递地址
    要记住：内联参数时模板，是语法性的
    记住：使用"m",则意味着引用时可以看成这个参数的地址
    
To set the kernel code segment: //使用立即数
    void set_kcs () {
        __asm__ __volatile__ (
        "ljmp %0, $farjmp \n"
        "farjmp: \n"
        "nop \n"
        : "i"(KERNEL_SEG_CODE) );
       
 


# 注意
直接使用g++生成object文件会包含__exit等注册类函数，在主机上最好先生成汇编代码，然后使用as编译后再生成目标文件，这样就不会含有不必要的注册函数。

# C++ 特殊语法
extern inline		---

# 能够动态设置段超越前缀吗？
默认情况下所有的数据都是通过ds来访问的，有没有办法让g++将段超越前缀修改成es?
# \_\_attribute\_\_属性集合
参考：https://gcc.gnu.org/onlinedocs/gcc/Attribute-Syntax.html
参考：Info: (gcc)Common Function Attributes, 979 lines
语法 : __attribute__ ((attribute-list))
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
          extern void *
          my_memcpy (void *dest, const void *src, size_t len)
                  __attribute__((nonnull (1, 2)));
		下标从1开始，如果没有提供列表，则所有参数不为NULL
noreturn 标注一个函数从不会返回，据此g++可以生成更好的代码

``` c++
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
			int square (int) __attribute__ ((pure));

returns_nonnull	函数不会返回NULL
used		标注一个函数会被使用，所以它的代码一定会被生成而不是优化掉
malloc    表明这是一个类似于malloc的函数
#下面是x86专用的
cdel  假设调用一个函数时，函数内部会将堆栈平衡
fastcall  将ecx,edx作为参数传递的寄存器，被调用函数会平衡堆栈；可变参数函数的所有参数被push到栈上
naked   表明函数体不需要任何序言和离开动作（即push/pop堆栈），生成纯粹的汇编代码  -- 经测试，改属性被忽略
stdcall 对于固定参数，自动平衡堆栈；对于可变参数，不平衡堆栈
