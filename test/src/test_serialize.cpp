/**
 * Dec 3, 2017 by 13774
 *
 */
#include <typeinfo>
#include <cstring>
#include <cstdlib>
#include <cstddef>
#include <cstdio>
#include <regex>
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <new>
#include <memory>

using u64_t = unsigned long long;
using u32_t = unsigned int;
using u16_t = unsigned short;
using u8_t = unsigned char;
#define AS_MACRO __attribute__((always_inline)) inline
//#define AS_MACRO

using namespace std;

class Foo{
public:
	static constexpr int serailizeSize()
	{
		return sizeof(Foo);
	}

	size_t i1;
	size_t i2;
};

class SerializerPtr{
    public:
        SerializerPtr(void *p):ptr((u8_t*)p)
    	{}

        void *getPtr()
        {
        	return ptr;
        }
        SerializerPtr & operator=(const SerializerPtr &rhs)
        {
        	this->ptr=rhs.ptr;
        	return *this;
        }
        operator bool()const
		{
        	return (ptr!=nullptr);
		}
        operator void*()const
		{
        	return ptr;
		}

        /**
         * 如果指针为nullptr，则仍然返回nullptr
         */
        SerializerPtr  operator+(ptrdiff_t pdiff)const
        {
        	if(*this)
        		return SerializerPtr(ptr+pdiff);
        	else
        		return SerializerPtr(nullptr);
        }
        /**
         * 如果指针为nullptr，则仍然返回nullptr
         */
        SerializerPtr  operator-(ptrdiff_t pdiff)const
        {
        	if(*this)
        		return SerializerPtr(ptr-pdiff);
        	else
        		return SerializerPtr(nullptr);
        }

        SerializerPtr&  operator+=(ptrdiff_t pdiff)
        {
        	if(ptr)
        		ptr+=pdiff;
        	return *this;
        }

        u8_t *ptr;
};

// 支持++操作

// 应当返回下一个可以开始序列化指针的位置, 如果为nullptr则失败
// 自动移到末尾处
template <class __S>
AS_MACRO SerializerPtr& operator>>(const __S &s,SerializerPtr& p)
{
	p+=__S::serailizeSize();
	return p;
}
template <class __S>
AS_MACRO  SerializerPtr& operator<<(__S &s,SerializerPtr& p)
{

	p+=__S::serailizeSize();
	return p;
}

// const expr




int main(int argc,char *argv[])
{
	Foo foo;
	SerializerPtr p((void*)5);

	int i=5;
	while( i-- )
	{
		p = foo >> p;
		cout << (size_t)p.ptr << endl;
		cout << "goood"<<endl;
	}

	cout << "END."<<endl;
	return 0;
}

