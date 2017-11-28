
#include <cstdarg>
#include <cstdio>

int myprintf(const char *fmt,...)
{
	va_list ap;
	va_start(ap,fmt);
	vprintf(fmt,ap);
	va_end(ap);

}

int main()
{
	myprintf("int is %d,str is \"%s\"\n",0,"hello world");

}
