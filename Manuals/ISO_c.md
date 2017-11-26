# 此文件
此文件对c进行 说明

# printf函数的实现

#include <cstdio>
#include <cstdarg>
int printf(const char *fmt,...)
{
    va_list ap;
    va_start(ap,fmt);
    vfprintf(stdout,fmt,ap);
    va_end(ap);
}