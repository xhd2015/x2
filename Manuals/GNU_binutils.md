# 此文件
此文件对binutils作整体介绍
# 列出所有的工具
info '(binutils)Top'

# LICENSE
GNU Free Documentation License

# 版本
本手册描述的binutils工具是1.3版

# 概念
object文件    也就是包含重定位信息、符号表和二进制代码的文件，通常由gcc/as编译生成
symbols       符号，表示一个地址或者数据
section       用于存放数据或者代码的一段内存空间
ELF             一种object文件的格式
# 目录

* ar::                          创建、修改和读取归档文件
* nm::                          列出object文件中的所有的Symbols
* objcopy::                     复制或者转换object文件
* objdump::                     显示object文件的信息
* ranlib::                      对归档文件的内容进行索引，产生index
* size::                        列出所有section大小和总大小
* strings::                     从一般文件中列出字符串
* strip::                       剔除（object文件）中的symbols
* c++filt::                     Filter to demangle encoded C++ symbols
* cxxfilt: c++filt.             MS-DOS name for c++filt
* addr2line::                   将地址转换成file:line，也就是说对生成该条语句的源文件位置进行还原
* nlmconv::                     Converts object code into an NLM
* windmc::                      Generator for Windows message resources
* windres::                     Manipulate Windows resources
* dlltool::                     Create files needed to build and use DLLs
* readelf::                     显示ELF格式的文件
* elfedit::                     更新ELF文件的文件头(header)
* Common Options::              Command-line options for all utilities
* Selecting the Target System:: How these utilities determine the target
* Reporting Bugs::              Reporting Bugs
* GNU Free Documentation License::  GNU Free Documentation License
* Binutils Index::              Binutils Index
