# 参考
http://www.sourceware.org/binutils/docs-2.12/as.info/   as是binutils的一部分

https://www.cse.unsw.edu.au/~cs3221/labs/assembler-intro.pdf		一份非常简洁但是有效的as参考，本目录下Others/assembler-intro.pdf是其副本

# GNU as汇编语法

# .code16 .code16gcc .code32 .code64
as默认生成32位i386或者64位x86_64的代码，但是也可以生成16位实模式下的代码,添加.code16,code16gcc即可
.code16gcc唯一的不同是生成32位长度的堆栈框架，即使用 'call', 'ret', 'enter',
'leave', 'push', 'pop', 'pusha', 'popa', 'pushf', 和'popf' 指令时，生成的是32位的长度

# 16位和32位的区别 (TODO 测试下面的说法)
8086处理器的通用寄存器的长度是16位
80386处理器的通用寄存器长度是32位

（待测试）如果指定cpu为8086，则不能使用eax寄存器
如果指定cpu为80386，则可以使用eax寄存器

实模式和16位模式是同义词。在实模式下，CPU对一条前缀指令的解释是使用32位操作；在32位模式下，对前缀指令的解释是使用16位操作。 前缀的含义就是切换到与默认模式相反的情况。

或者也有一种可能：8086是默认寄存器长度16位，80386默认寄存器长度32位。

# .arch CPU_TYPE指令
用于告诉as生成特定处理器的代码，部分可选值如下：
'i8086'        'i186'         'i286'         'i386'
'i486'         'i586'         'i686'    'pentiumpro'   'pentiumii'    'pentiumiii'   'pentium4'
 'corei7'  
 
# 局部符号和局部标号
-L --keep-locals		保存局部符号(以.L开头, a.out文件为L开头), 就像一般符号那样
symbol符号  label标号
局部标号和局部符号不同；局部符号的含义是这个符号不像一般符号那样导出
局部标号的意义在于帮助用户使用临时标号而不必考虑这个标号会在别处定义。编译器会为这些标号生成全部不同的符号。
局部标号的形式： N:
如：  1: 
		jmp 1b
可以使用一个后缀(b,f)来指明要使用的标号，比如1b,1f。
局部标号只能引用最近一个定义的。

还有一种特别的标号，N$，比如55$。这里不做说明。


# 命令行传递参数
	--defsym SYM=VAL
	注意，只能传递一个已经计算好的数值而不能传递尚未计算的数值,比如 SYM=8是可以的，但是SYM=8*1 SYM='(8*1)'都是不被允许的
	
	ld也支持该选项
	
	
# 符号的概念
如果一个符号在as汇编阶段找不到，则会等到链接阶段，链接阶段找不到就报错
.	代表当前正在汇编的地址，这个地址是相对于该区起始处的, 对.的赋值等价于.org指令
	
	
# .S文件



# 其他
文档说明了符号是最重要的概念，as使用符号进行汇编，ld使用符号进行链接，gdb使用符号进行调试

# 附录：汇编语法
参见：  Info: (as)i386-Prefixes   说明了lock，rep,repe等前缀
Info: (as)i386-Memory	说明了内存寻址的语法格式

# 附录：特殊指令
参考：http://www.delorie.com/gnu/docs/binutils/as_68.html  快速一览表
.print "string"		打印信息	,注意,必须使用""将字符串括住
.linkonce [type]	使链接器丢弃重复的分区
.fail expression	当expression在数值上大于等于500时，发出错误警告
.if absolute expression	非0才执行expression的汇编
.ident				兼容性，无实际作用
.single|.float f1,f2,..		定义浮点数，浮点数的标准由as配置决定
 .include "file"
 .abort				停止编译
 .ascii "strings",...	定义字符串，不会添加0，不会转义
 .asciz				同.ascii，但是添加0
 .string "strings",...	定义字符串，转义其中的符号
 .data	[n]			将下面的数据放置到第n个数据区，数据的顺序不如代码的顺序重要
 .def	... .endef	定义调试符号
 .global symbol, .globl symbol	使该符号对ld可见
 .org new-lc , fill		将当前分区的位置移动到new-lc,注意：不可以减小




# 附录：汇编指令格式一览
ljmp $SEG,$OFF
