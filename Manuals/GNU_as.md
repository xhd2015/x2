# 参考
http://www.sourceware.org/binutils/docs-2.12/as.info/   as是binutils的一部分

https://www.cse.unsw.edu.au/~cs3221/labs/assembler-intro.pdf		一份非常简洁但是有效的as参考，本目录下Others/assembler-intro.pdf是其副本

# GNU as汇编语法


# 命令行传递参数
	--defsym SYM=VAL
	注意，只能传递一个已经计算好的数值而不能传递尚未计算的数值,比如 SYM=8是可以的，但是SYM=8*1 SYM='(8*1)'都是不被允许的
	
	ld也支持该选项
# 符号的概念
如果一个符号在as汇编阶段找不到，则会等到链接阶段，链接阶段找不到就报错
	
	
# .S文件

# 其他
文档说明了符号是最重要的概念，as使用符号进行汇编，ld使用符号进行链接，gdb使用符号进行调试

