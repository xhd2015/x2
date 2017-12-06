
#ifndef CPPConfig_h
#define CPPConfig_h

// Macro for noexcept, to support in mixed 03/0x mode.
#ifndef _NOEXCEPT
# if __cplusplus >= 201103L //since c++11, noexcept(expr) will tell the compiler if a method will throw an exception or not.It's designed to replace throw()
#  define _NOEXCEPT noexcept
#  define _USE_NOEXCEPT noexcept
#  define _THROW(_EXC)
# else
#  define _NOEXCEPT
#  define _USE_NOEXCEPT throw()
#  define _THROW(_EXC) throw(_EXC)
# endif
#endif


namespace std
{
	typedef __SIZE_TYPE__ size_t;	
	typedef __PTRDIFF_TYPE__	ptrdiff_t;


}


#endif // CPPConfig_h
