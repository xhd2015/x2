# 1 "new.cpp"
# 1 "<built-in>"
# 1 "<命令行>"
# 1 "new.cpp"
# 1 "/usr/lib/gcc/i686-w64-mingw32/5.4.0/include/c++/new" 1 3
# 37 "/usr/lib/gcc/i686-w64-mingw32/5.4.0/include/c++/new" 3
       
# 38 "/usr/lib/gcc/i686-w64-mingw32/5.4.0/include/c++/new" 3

# 1 "/usr/lib/gcc/i686-w64-mingw32/5.4.0/include/c++/i686-w64-mingw32/bits/c++config.h" 1 3
# 194 "/usr/lib/gcc/i686-w64-mingw32/5.4.0/include/c++/i686-w64-mingw32/bits/c++config.h" 3

# 194 "/usr/lib/gcc/i686-w64-mingw32/5.4.0/include/c++/i686-w64-mingw32/bits/c++config.h" 3
namespace std
{
  typedef unsigned int size_t;
  typedef int ptrdiff_t;




}
# 216 "/usr/lib/gcc/i686-w64-mingw32/5.4.0/include/c++/i686-w64-mingw32/bits/c++config.h" 3
namespace std
{
  inline namespace __cxx11 __attribute__((__abi_tag__ ("cxx11"))) { }
}
namespace __gnu_cxx
{
  inline namespace __cxx11 __attribute__((__abi_tag__ ("cxx11"))) { }
}
# 482 "/usr/lib/gcc/i686-w64-mingw32/5.4.0/include/c++/i686-w64-mingw32/bits/c++config.h" 3
# 1 "/usr/lib/gcc/i686-w64-mingw32/5.4.0/include/c++/i686-w64-mingw32/bits/os_defines.h" 1 3
# 483 "/usr/lib/gcc/i686-w64-mingw32/5.4.0/include/c++/i686-w64-mingw32/bits/c++config.h" 2 3


# 1 "/usr/lib/gcc/i686-w64-mingw32/5.4.0/include/c++/i686-w64-mingw32/bits/cpu_defines.h" 1 3
# 486 "/usr/lib/gcc/i686-w64-mingw32/5.4.0/include/c++/i686-w64-mingw32/bits/c++config.h" 2 3
# 40 "/usr/lib/gcc/i686-w64-mingw32/5.4.0/include/c++/new" 2 3
# 1 "/usr/lib/gcc/i686-w64-mingw32/5.4.0/include/c++/exception" 1 3
# 33 "/usr/lib/gcc/i686-w64-mingw32/5.4.0/include/c++/exception" 3
       
# 34 "/usr/lib/gcc/i686-w64-mingw32/5.4.0/include/c++/exception" 3

#pragma GCC visibility push(default)


# 1 "/usr/lib/gcc/i686-w64-mingw32/5.4.0/include/c++/bits/atomic_lockfree_defines.h" 1 3
# 33 "/usr/lib/gcc/i686-w64-mingw32/5.4.0/include/c++/bits/atomic_lockfree_defines.h" 3
       
# 34 "/usr/lib/gcc/i686-w64-mingw32/5.4.0/include/c++/bits/atomic_lockfree_defines.h" 3
# 39 "/usr/lib/gcc/i686-w64-mingw32/5.4.0/include/c++/exception" 2 3

extern "C++" {

namespace std
{
# 60 "/usr/lib/gcc/i686-w64-mingw32/5.4.0/include/c++/exception" 3
  class exception
  {
  public:
    exception() throw() { }
    virtual ~exception() throw();



    virtual const char* what() const throw();
  };



  class bad_exception : public exception
  {
  public:
    bad_exception() throw() { }



    virtual ~bad_exception() throw();


    virtual const char* what() const throw();
  };


  typedef void (*terminate_handler) ();


  typedef void (*unexpected_handler) ();


  terminate_handler set_terminate(terminate_handler) throw();
# 102 "/usr/lib/gcc/i686-w64-mingw32/5.4.0/include/c++/exception" 3
  void terminate() throw() __attribute__ ((__noreturn__));


  unexpected_handler set_unexpected(unexpected_handler) throw();
# 114 "/usr/lib/gcc/i686-w64-mingw32/5.4.0/include/c++/exception" 3
  void unexpected() __attribute__ ((__noreturn__));
# 127 "/usr/lib/gcc/i686-w64-mingw32/5.4.0/include/c++/exception" 3
  bool uncaught_exception() throw() __attribute__ ((__pure__));


}

namespace __gnu_cxx
{

# 152 "/usr/lib/gcc/i686-w64-mingw32/5.4.0/include/c++/exception" 3
  void __verbose_terminate_handler();


}

}

#pragma GCC visibility pop
# 41 "/usr/lib/gcc/i686-w64-mingw32/5.4.0/include/c++/new" 2 3

#pragma GCC visibility push(default)

extern "C++" {

namespace std
{






  class bad_alloc : public exception
  {
  public:
    bad_alloc() throw() { }



    virtual ~bad_alloc() throw();


    virtual const char* what() const throw();
  };
# 82 "/usr/lib/gcc/i686-w64-mingw32/5.4.0/include/c++/new" 3
  struct nothrow_t { };

  extern const nothrow_t nothrow;



  typedef void (*new_handler)();



  new_handler set_new_handler(new_handler) throw();





}
# 111 "/usr/lib/gcc/i686-w64-mingw32/5.4.0/include/c++/new" 3
void* operator new(std::size_t) throw(std::bad_alloc)
  __attribute__((__externally_visible__));
void* operator new[](std::size_t) throw(std::bad_alloc)
  __attribute__((__externally_visible__));
void operator delete(void*) throw()
  __attribute__((__externally_visible__));
void operator delete[](void*) throw()
  __attribute__((__externally_visible__));
void* operator new(std::size_t, const std::nothrow_t&) throw()
  __attribute__((__externally_visible__));
void* operator new[](std::size_t, const std::nothrow_t&) throw()
  __attribute__((__externally_visible__));
void operator delete(void*, const std::nothrow_t&) throw()
  __attribute__((__externally_visible__));
void operator delete[](void*, const std::nothrow_t&) throw()
  __attribute__((__externally_visible__));


inline void* operator new(std::size_t, void* __p) throw()
{ return __p; }
inline void* operator new[](std::size_t, void* __p) throw()
{ return __p; }


inline void operator delete (void*, void*) throw() { }
inline void operator delete[](void*, void*) throw() { }

}

#pragma GCC visibility pop
# 2 "new.cpp" 2


# 3 "new.cpp"
int main()
{
 int a;
 int *b=new(&a) int(4);

 return 0;
}
