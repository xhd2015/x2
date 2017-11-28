# 此文件
对CMake工具进行说明

# CMake脚本文件参考
命令行：cmake 根目录 -G"类型"， 其中类型可由cmake -h得到
project(HELLO)  #自动引入PROJECT_SRC_DIR和PROJECT_BINARY_DIR
变量的语法:${变量名}

message(...)       #输出信息
set             设置变量
add_executable   添加一个二进制目标
add_library      添加一个库

下面是一个简单的例子：
```cmake
project(HELLO)
set(SRC_LIST main.c hello.c)
add_executable(hello ${SRC_LIST})
```


注：内置关键字不区分大小写，但是变量名区分
