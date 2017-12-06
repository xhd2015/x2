# 此文件
此文件对g++的标准库源码进行解读


# bits/c++config.h
该文件副本在Others目录下
宏
__GLIBCXX__ 20170704    定义版本号

命名空间概览：最新请参照https://gcc.gnu.org/onlinedocs/libstdc++/latest-doxygen/namespaces.html
```c++
namespace std
  {
    namespace __debug { }
    namespace __parallel { }
    namespace __profile { }
    namespace __cxx1998 { }

    namespace __detail { }

    namespace rel_ops { }

    namespace tr1
    {
      namespace placeholders { }
      namespace regex_constants { }
      namespace __detail { }
    }

    namespace tr2 { }
    
    namespace decimal { }

    namespace chrono { }
    namespace placeholders { }
    namespace regex_constants { }
    namespace this_thread { }
    inline namespace literals {
      inline namespace chrono_literals { }
      inline namespace complex_literals { }
      inline namespace string_literals { }
    }
  }

  namespace abi { }

  namespace __gnu_cxx
  {
    namespace __detail { }
  }
```
  接着定义了size_t ptrdiff_t nullptr_t
```c++
  typedef __SIZE_TYPE__   size_t;
  typedef __PTRDIFF_TYPE__  ptrdiff_t;

#if __cplusplus >= 201103L
  typedef decltype(nullptr) nullptr_t;
#endif
```
紧接着又 包含了os_defines和cpu_defines(见后面的节)
```c++

// This marks string literals in header files to be extracted for eventual
// translation.  It is primarily used for messages in thrown exceptions; see
// src/functexcept.cc.  We use __N because the more traditional _N is used
// for something else under certain OSes (see BADNAMES).
#define __N(msgid)     (msgid)

// For example, <windows.h> is known to #define min and max as macros...
#undef min
#undef max
```


下面是一系列被注释掉的定义
```c++
/* The size of `char', as computed by sizeof. */
/* #undef SIZEOF_CHAR */

/* The size of `int', as computed by sizeof. */
/* #undef SIZEOF_INT */

/* The size of `long', as computed by sizeof. */
/* #undef SIZEOF_LONG */

/* The size of `short', as computed by sizeof. */
/* #undef SIZEOF_SHORT */

/* The size of `void *', as computed by sizeof. */
/* #undef SIZEOF_VOID_P */
```

下面的宏STDC_HEADERS,在有标准c头文件的情况下定义。
```c++
/* Define to 1 if you have the ANSI C header files. */
#define STDC_HEADERS 1
```

throw的定义，指向语言的，或者内置的
```c++
#ifndef _GLIBCXX_THROW_OR_ABORT
# if __cpp_exceptions
#  define _GLIBCXX_THROW_OR_ABORT(_EXC) (throw (_EXC))
# else
#  define _GLIBCXX_THROW_OR_ABORT(_EXC) (__builtin_abort())
# endif
#endif
```

# bits/os_defines.h
该文件借助__CYGWIN__变量定义了两个关键的宏
```c++
// See libstdc++/20806.
#define _GLIBCXX_HAVE_DOS_BASED_FILESYSTEM 1

// Enable use of GetModuleHandleEx (requires Windows XP/2003) in
// __cxa_thread_atexit to prevent modules from being unloaded before
// their dtors are called
#define _GLIBCXX_THREAD_ATEXIT_WIN32 1
```
第一个说明了是否具有DOS文件系统，第二说了明多线程特性。
由此可见，文件系统和多线程是不能在os之间移植的。

# bits/cpu_defines.h
该文件什么都没做

# vector
```c++
#pragma GCC system_header

#include <bits/stl_algobase.h>
#include <bits/allocator.h>
#include <bits/stl_construct.h>
#include <bits/stl_uninitialized.h>
#include <bits/stl_vector.h>
#include <bits/stl_bvector.h> 
#include <bits/range_access.h>

#ifndef _GLIBCXX_EXPORT_TEMPLATE
# include <bits/vector.tcc>
#endif

#ifdef _GLIBCXX_DEBUG
# include <debug/vector>
#endif

#ifdef _GLIBCXX_PROFILE
# include <profile/vector>
#endif
```
# initializer_list
定义了初始化列表，其实十分简单。
该初始化列表的构造器是private的，但是编译器可以调用这个构造器。
可以看到reference,const_reference其实都是const的，也就是说初始化列表无法被访问，无法通过构造函数构建。
而且由于其是constexpr函数，所以实际上在编译期就可以完成。这个只需要编译器支持，而无需操作系统的支持。
```c++
 /// initializer_list
  template<class _E>
    class initializer_list
    {
    public:
      typedef _E        value_type;
      typedef const _E&     reference;
      typedef const _E&     const_reference;
      typedef size_t        size_type;
      typedef const _E*     iterator;
      typedef const _E*     const_iterator;

    private:
      iterator          _M_array;
      size_type         _M_len;

      // The compiler can call a private constructor.
      constexpr initializer_list(const_iterator __a, size_type __l)
      : _M_array(__a), _M_len(__l) { }

    public:
      constexpr initializer_list() noexcept
      : _M_array(0), _M_len(0) { }

      // Number of elements.
      constexpr size_type
      size() const noexcept { return _M_len; }

      // First element.
      constexpr const_iterator
      begin() const noexcept { return _M_array; }

      // One past the last element.
      constexpr const_iterator
      end() const noexcept { return begin() + size(); }
    };

  /**
   *  @brief  Return an iterator pointing to the first element of
   *          the initializer_list.
   *  @param  __ils  Initializer list.
   */
  template<class _Tp>
    constexpr const _Tp*
    begin(initializer_list<_Tp> __ils) noexcept
    { return __ils.begin(); }

  /**
   *  @brief  Return an iterator pointing to one past the last element
   *          of the initializer_list.
   *  @param  __ils  Initializer list.
   */
  template<class _Tp>
    constexpr const _Tp*
    end(initializer_list<_Tp> __ils) noexcept
    { return __ils.end(); }
```

# new
定义了bad_alloc虚异常，bad_array_new_length继承上面的异常。定义了一个空结构题no_throw_t,以及一个 外部链接符号nothrow,需要注意的是该符号没有定义
```c++
    /*...namespace std...*/
  class bad_alloc : public exception
  {
  public:
    bad_alloc() throw() { }
    virtual ~bad_alloc() throw();
    virtual const char* what() const throw();
  };

#if __cplusplus >= 201103L
  class bad_array_new_length : public bad_alloc /*......*/{}
#endif

  struct nothrow_t
  {
#if __cplusplus >= 201103L
    explicit nothrow_t() = default;
#endif
  };
  extern const nothrow_t nothrow;

```
下面就是一些需要系统定义的函数,new_handler,
```c++
  typedef void (*new_handler)();
  new_handler set_new_handler(new_handler) throw();

#if __cplusplus >= 201103L
  new_handler get_new_handler() noexcept;
#endif
```
后面是一堆声明没有定义的new函数,注，这些函数的不在std中，而且声明extern "C++"链接。
这些函数是可以被替代的。注意宏__cpp_sized_deallocation,其实就是系统是否采用地址+大小的方式来分配和回收空间。
__attribute__((__externally_visible__))示意其他链接器，该函数可外部链接。对ld默认开启的。
```c++
void* operator new(std::size_t) _GLIBCXX_THROW (std::bad_alloc)
  __attribute__((__externally_visible__));
void* operator new[](std::size_t) _GLIBCXX_THROW (std::bad_alloc)
  __attribute__((__externally_visible__));
void operator delete(void*) _GLIBCXX_USE_NOEXCEPT
  __attribute__((__externally_visible__));
void operator delete[](void*) _GLIBCXX_USE_NOEXCEPT
  __attribute__((__externally_visible__));
#if __cpp_sized_deallocation
void operator delete(void*, std::size_t) _GLIBCXX_USE_NOEXCEPT
  __attribute__((__externally_visible__));
void operator delete[](void*, std::size_t) _GLIBCXX_USE_NOEXCEPT
  __attribute__((__externally_visible__));
#endif
void* operator new(std::size_t, const std::nothrow_t&) _GLIBCXX_USE_NOEXCEPT
  __attribute__((__externally_visible__));
void* operator new[](std::size_t, const std::nothrow_t&) _GLIBCXX_USE_NOEXCEPT
  __attribute__((__externally_visible__));
void operator delete(void*, const std::nothrow_t&) _GLIBCXX_USE_NOEXCEPT
  __attribute__((__externally_visible__));
void operator delete[](void*, const std::nothrow_t&) _GLIBCXX_USE_NOEXCEPT
  __attribute__((__externally_visible__));
#if __cpp_sized_deallocation
void operator delete(void*, std::size_t, const std::nothrow_t&) _GLIBCXX_USE_NOEXCEPT
  __attribute__((__externally_visible__));
void operator delete[](void*, std::size_t, const std::nothrow_t&) _GLIBCXX_USE_NOEXCEPT
  __attribute__((__externally_visible__));
#endif
```


placement版本的new/delete,注意，用户最好不要重定义这个版本的new/delete.
```c++
/*
 *  Placement new and delete signatures (take a memory address argument,
 *  does nothing) may not be replaced by a user's program.
 */
// Default placement versions of operator new.
inline void* operator new(std::size_t, void* __p) _GLIBCXX_USE_NOEXCEPT
{ return __p; }
inline void* operator new[](std::size_t, void* __p) _GLIBCXX_USE_NOEXCEPT
{ return __p; }

// Default placement versions of operator delete.
inline void operator delete  (void*, void*) _GLIBCXX_USE_NOEXCEPT { }
inline void operator delete[](void*, void*) _GLIBCXX_USE_NOEXCEPT { }
```

# memory
```c++
#include <bits/stl_algobase.h>
#include <bits/allocator.h>
#include <bits/stl_construct.h>
#include <bits/stl_uninitialized.h>
#include <bits/stl_tempbuf.h>
#include <bits/stl_raw_storage_iter.h>
#  include <exception>            // std::exception
#  include <typeinfo>             // std::type_info in get_deleter
#  include <iosfwd>               // std::basic_ostream
#  include <ext/atomicity.h>
#  include <ext/concurrence.h>
#  include <bits/functexcept.h>
#  include <bits/stl_function.h>  // std::less
#  include <bits/uses_allocator.h>
#  include <type_traits>
#  include <functional>
#  include <debug/debug.h>
#  include <bits/unique_ptr.h>
#  include <bits/shared_ptr.h>
#  include <bits/shared_ptr_atomic.h>
```

```c++
inline void*
align(size_t __align, size_t __size, void*& __ptr, size_t& __space) noexcept;
```
# bits/vector.tcc
该文件没有任何引用
因为它只是一个stl_vectors.h的方法实现文件，它最终被vector引入。
g++不提供export template机制（该机制在将来废弃），因此直接通过引入的方式来实例化模板。
# cxxabi.h
# bits/range_access.h
```c++
#include <initializer_list>
```
定义了一系列的[c][r]begin|end函数，默认就是调用容器本身的begin,end函数，data函数用于获取容器的指针。也就是所为的underlying data.还有其他的size,empty
data有针对数组，初始化列表的特化方法。初始化列表就是返回一个数据指针。
```c++
 /**
   *  @brief  Return the data pointer of a container.
   *  @param  __cont  Container.
   */
  template <typename _Container>
    constexpr auto
    data(_Container& __cont) -> decltype(__cont.data())
    { return __cont.data(); }

  /**
   *  @brief  Return the data pointer of a const container.
   *  @param  __cont  Container.
   */
  template <typename _Container>
    constexpr auto
    data(const _Container& __cont) -> decltype(__cont.data())
    { return __cont.data(); }

  /**
   *  @brief  Return the data pointer of an array.
   *  @param  __array  Array.
   */
  template <typename _Tp, size_t _Nm>
    constexpr _Tp*
    data(_Tp (&__array)[_Nm]) noexcept
    { return __array; }

  /**
   *  @brief  Return the data pointer of an initializer list.
   *  @param  __il  Initializer list.
   */
  template <typename _Tp>
    constexpr const _Tp*
    data(initializer_list<_Tp> __il) noexcept
    { return __il.begin(); }
```
# bits/stl_vector.h
```c++
#include <bits/stl_iterator_base_funcs.h>
#include <bits/functexcept.h>
#include <bits/concept_check.h>
#include <initializer_list>
```
和stl_deque很相似，同样定义了base,base iterator,以及vector
注意，对insert,emplace_back,_M_range_insert等函数，是在bits/vector.tcc中实现的。
# bits/stl_bvector.h
```c++
#include <initializer_list>
#include <bits/stl_vector.h>
```
该文件专门为vector<bool,Alloc>定义了专用的操作
首先定义了_Bit_iterator_base,Bit_iterator,即所谓的位迭代器,实际上实现了标准的iterator随机迭代器接口
operator*的实现实际上就是_Bit_reference的返回值，也就是operator bool()，实际上，该函数通过两次逻辑非来获得原始值的bool类型。我想，这也是大多数bool操作符的正确实现方式，即一次逻辑非将其转换为bool值，一次逻辑非获得其原始值。
```c++
 struct _Bit_iterator_base
  : public std::iterator<std::random_access_iterator_tag, bool>
  {
    /*......*/
 }
  struct _Bit_reference
  {
    /*......*/
        operator bool() const _GLIBCXX_NOEXCEPT
    { return !!(*_M_p & _M_mask); }
 }
  struct _Bit_iterator : public _Bit_iterator_base
  {
    typedef _Bit_reference  reference;
     reference
    operator*() const
    { return reference(_M_p, 1UL << _M_offset); }
    /*......*/
  }
```
# bits/stl_deque.h
```c++
#include <bits/concept_check.h>
#include <bits/stl_iterator_base_types.h>
#include <bits/stl_iterator_base_funcs.h>
#include <initializer_list>
```
定义了_Deque_iterator,_Deque_Base,deque三种类型
deque的大多数功能实际是通过_Deque_iterator完成的
deque的默认分配器是allocator<Tp>,也就是new_allocator.
# bits/stl_construct.h
头文件部分
```c++
#include <new>
#include <bits/move.h>
#include <ext/alloc_traits.h>
```
定义了_Construct(Ptr,Args..)的通用构造函数，其实调用的是placement new
还有_Destroy的三种形式，除普通的调用析构函数的形式外，还有按迭代器范围销毁，以及按迭代器范围和分配器销毁。

```c++
  template<typename _T1, typename... _Args>
    inline void
    _Construct(_T1* __p, _Args&&... __args)
    { ::new(static_cast<void*>(__p)) _T1(std::forward<_Args>(__args)...); }

      /**
   * Destroy the object pointed to by a pointer type.
   */
  template<typename _Tp>
    inline void
    _Destroy(_Tp* __pointer)
    { __pointer->~_Tp(); }

      template<typename _ForwardIterator>
    inline void
    _Destroy(_ForwardIterator __first, _ForwardIterator __last)
    {
      typedef typename iterator_traits<_ForwardIterator>::value_type
                       _Value_type;
      std::_Destroy_aux<__has_trivial_destructor(_Value_type)>::
    __destroy(__first, __last);
    }

      template<typename _ForwardIterator, typename _Allocator>
    void
    _Destroy(_ForwardIterator __first, _ForwardIterator __last,
         _Allocator& __alloc)
    {
      typedef __gnu_cxx::__alloc_traits<_Allocator> __traits;
      for (; __first != __last; ++__first)
    __traits::destroy(__alloc, std::__addressof(*__first));
    }
```




# bits/stl_uninitialized.h
无任何头文件引用
定义了函数uninitialized_copy,uninitialized_fill,uninitialized_fill_n,uninitialized_copy_n
正如其注释而言：Like copy(), but does not require an initialized output range. 和std::copy是差不多的，但是不需要对输出进行初始化
注意，使用了编译器宏函数：__is_trivial，如果是这种类型（原始可直接赋值类型），则直接赋值。
```c++
 /**
   *  @brief Copies the range [first,last) into result.
   *  @param  __first  An input iterator.
   *  @param  __last   An input iterator.
   *  @param  __result An output iterator.
   *  @return   __result + (__first - __last)
   *
   *  Like copy(), but does not require an initialized output range.
  */
  template<typename _InputIterator, typename _ForwardIterator>
    inline _ForwardIterator
    uninitialized_copy(_InputIterator __first, _InputIterator __last,
               _ForwardIterator __result)
               {
                      typedef typename iterator_traits<_InputIterator>::value_type
    _ValueType1;
      typedef typename iterator_traits<_ForwardIterator>::value_type
    _ValueType2;
#if __cplusplus < 201103L
      const bool __assignable = true;
#else
      // trivial types can have deleted assignment
      typedef typename iterator_traits<_InputIterator>::reference _RefType1;
      typedef typename iterator_traits<_ForwardIterator>::reference _RefType2;
      const bool __assignable = is_assignable<_RefType2, _RefType1>::value;
#endif

      return std::__uninitialized_copy<__is_trivial(_ValueType1)
                       && __is_trivial(_ValueType2)
                       && __assignable>::
    __uninit_copy(__first, __last, __result);
               }
```
copy的核心实现,如果是基本类型，调用std::copy,否则，使用迭代。
```c++
 template<bool _TrivialValueTypes>
    struct __uninitialized_copy
    {
      template<typename _InputIterator, typename _ForwardIterator>
        static _ForwardIterator
        __uninit_copy(_InputIterator __first, _InputIterator __last,
              _ForwardIterator __result)
        {
      _ForwardIterator __cur = __result;
      __try
        {
          for (; __first != __last; ++__first, (void)++__cur)
        std::_Construct(std::__addressof(*__cur), *__first);
          return __cur;
        }
      __catch(...)
        {
          std::_Destroy(__result, __cur);
          __throw_exception_again;
        }
    }
    };

  template<>
    struct __uninitialized_copy<true>
    {
      template<typename _InputIterator, typename _ForwardIterator>
        static _ForwardIterator
        __uninit_copy(_InputIterator __first, _InputIterator __last,
              _ForwardIterator __result)
        { return std::copy(__first, __last, __result); }
    };
```
# ext/alloc_traits.h
```c++
# include <bits/move.h>
# include <bits/alloc_traits.h>
```
该文件仅仅定义了__gnu_cxx命名空间的一个__alloc_traits，是对std::allocator_traits的继承
```c++
/**
 * @brief  Uniform interface to C++98 and C++11 allocators.
 * @ingroup allocators
*/
template<typename _Alloc>
  struct __alloc_traits
#if __cplusplus >= 201103L
  : std::allocator_traits<_Alloc>
#endif
  {
    typedef _Alloc allocator_type;
#if __cplusplus >= 201103L
    typedef std::allocator_traits<_Alloc>           _Base_type;
    typedef typename _Base_type::value_type         value_type;
    typedef typename _Base_type::pointer            pointer;
    typedef typename _Base_type::const_pointer      const_pointer;
    typedef typename _Base_type::size_type          size_type;
    typedef typename _Base_type::difference_type    difference_type;
    // C++11 allocators do not define reference or const_reference
    typedef value_type&                             reference;
    typedef const value_type&                       const_reference;
    using _Base_type::allocate;
    using _Base_type::deallocate;
    using _Base_type::construct;
    using _Base_type::destroy;
    using _Base_type::max_size;

  private:
    template<typename _Ptr>
      using __is_custom_pointer
    = std::__and_<std::is_same<pointer, _Ptr>,
              std::__not_<std::is_pointer<_Ptr>>>;

  public:
    // overload construct for non-standard pointer types
    template<typename _Ptr, typename... _Args>
      static typename std::enable_if<__is_custom_pointer<_Ptr>::value>::type
      construct(_Alloc& __a, _Ptr __p, _Args&&... __args)
      {
    _Base_type::construct(__a, std::addressof(*__p),
                  std::forward<_Args>(__args)...);
      }

    // overload destroy for non-standard pointer types
    template<typename _Ptr>
      static typename std::enable_if<__is_custom_pointer<_Ptr>::value>::type
      destroy(_Alloc& __a, _Ptr __p)
      { _Base_type::destroy(__a, std::addressof(*__p)); }

    static _Alloc _S_select_on_copy(const _Alloc& __a)
    { return _Base_type::select_on_container_copy_construction(__a); }

    static void _S_on_swap(_Alloc& __a, _Alloc& __b)
    { std::__alloc_on_swap(__a, __b); }

    static constexpr bool _S_propagate_on_copy_assign()
    { return _Base_type::propagate_on_container_copy_assignment::value; }

    static constexpr bool _S_propagate_on_move_assign()
    { return _Base_type::propagate_on_container_move_assignment::value; }

    static constexpr bool _S_propagate_on_swap()
    { return _Base_type::propagate_on_container_swap::value; }

    static constexpr bool _S_always_equal()
    { return _Base_type::is_always_equal::value; }

    static constexpr bool _S_nothrow_move()
    { return _S_propagate_on_move_assign() || _S_always_equal(); }

    template<typename _Tp>
      struct rebind
      { typedef typename _Base_type::template rebind_alloc<_Tp> other; };
#else

    typedef typename _Alloc::pointer                pointer;
    typedef typename _Alloc::const_pointer          const_pointer;
    typedef typename _Alloc::value_type             value_type;
    typedef typename _Alloc::reference              reference;
    typedef typename _Alloc::const_reference        const_reference;
    typedef typename _Alloc::size_type              size_type;
    typedef typename _Alloc::difference_type        difference_type;

    static pointer
    allocate(_Alloc& __a, size_type __n)
    { return __a.allocate(__n); }

    static void deallocate(_Alloc& __a, pointer __p, size_type __n)
    { __a.deallocate(__p, __n); }

    template<typename _Tp>
      static void construct(_Alloc& __a, pointer __p, const _Tp& __arg)
      { __a.construct(__p, __arg); }

    static void destroy(_Alloc& __a, pointer __p)
    { __a.destroy(__p); }

    static size_type max_size(const _Alloc& __a)
    { return __a.max_size(); }

    static const _Alloc& _S_select_on_copy(const _Alloc& __a) { return __a; }

    static void _S_on_swap(_Alloc& __a, _Alloc& __b)
    {
      // _GLIBCXX_RESOLVE_LIB_DEFECTS
      // 431. Swapping containers with unequal allocators.
      std::__alloc_swap<_Alloc>::_S_do_it(__a, __b);
    }

    template<typename _Tp>
      struct rebind
      { typedef typename _Alloc::template rebind<_Tp>::other other; };
#endif
  };
```
# bits/alloc_traits.h
```c++
#include <bits/memoryfwd.h>
#include <bits/ptr_traits.h>
#include <ext/numeric_traits.h>
```
提供对allocator的抽象。
首先定义了一个基类，其他类从此类衍生：
```c++
struct __allocator_traits_base
  {
    template<typename _Tp, typename _Up, typename = void>
      struct __rebind : __replace_first_arg<_Tp, _Up> { };

    template<typename _Tp, typename _Up>
      struct __rebind<_Tp, _Up,
              __void_t<typename _Tp::template rebind<_Up>::other>>
      { using type = typename _Tp::template rebind<_Up>::other; };

  protected:
    template<typename _Tp>
      using __pointer = typename _Tp::pointer;
    template<typename _Tp>
      using __c_pointer = typename _Tp::const_pointer;
    template<typename _Tp>
      using __v_pointer = typename _Tp::void_pointer;
    template<typename _Tp>
      using __cv_pointer = typename _Tp::const_void_pointer;
    template<typename _Tp>
      using __pocca = typename _Tp::propagate_on_container_copy_assignment;
    template<typename _Tp>
      using __pocma = typename _Tp::propagate_on_container_move_assignment;
    template<typename _Tp>
      using __pocs = typename _Tp::propagate_on_container_swap;
    template<typename _Tp>
      using __equal = typename _Tp::is_always_equal;
  };
```
紧接着就是此文件中最重要的allocator_traits。值得注意的是，construct,destroy,max_size,select_on_container_copy_constructionallocate,deallocate都是静态函数
```c++

  /**
   * @brief  Uniform interface to all allocator types.
   * @ingroup allocators
  */
  template<typename _Alloc>
    struct allocator_traits : __allocator_traits_base
    {
      /// The allocator type
      typedef _Alloc allocator_type;
      /// The allocated type
      typedef typename _Alloc::value_type value_type;

      /**
       * @brief   The allocator's pointer type.
       *
       * @c Alloc::pointer if that type exists, otherwise @c value_type*
      */
      using pointer = __detected_or_t<value_type*, __pointer, _Alloc>;

    private:
      // Select _Func<_Alloc> or pointer_traits<pointer>::rebind<_Tp>
      template<template<typename> class _Func, typename _Tp, typename = void>
    struct _Ptr
    {
      using type = typename pointer_traits<pointer>::template rebind<_Tp>;
    };

      template<template<typename> class _Func, typename _Tp>
    struct _Ptr<_Func, _Tp, __void_t<_Func<_Alloc>>>
    {
      using type = _Func<_Alloc>;
    };

      // Select _A2::difference_type or pointer_traits<_Ptr>::difference_type
      template<typename _A2, typename _PtrT, typename = void>
    struct _Diff
    { using type = typename pointer_traits<_PtrT>::difference_type; };

      template<typename _A2, typename _PtrT>
    struct _Diff<_A2, _PtrT, __void_t<typename _A2::difference_type>>
    { using type = typename _A2::difference_type; };

      // Select _A2::size_type or make_unsigned<_DiffT>::type
      template<typename _A2, typename _DiffT, typename = void>
    struct _Size : make_unsigned<_DiffT> { };

      template<typename _A2, typename _DiffT>
    struct _Size<_A2, _DiffT, __void_t<typename _A2::size_type>>
    { using type = typename _A2::size_type; };

    public:
      /**
       * @brief   The allocator's const pointer type.
       *
       * @c Alloc::const_pointer if that type exists, otherwise
       * <tt> pointer_traits<pointer>::rebind<const value_type> </tt>
      */
      using const_pointer = typename _Ptr<__c_pointer, const value_type>::type;

      /**
       * @brief   The allocator's void pointer type.
       *
       * @c Alloc::void_pointer if that type exists, otherwise
       * <tt> pointer_traits<pointer>::rebind<void> </tt>
      */
      using void_pointer = typename _Ptr<__v_pointer, void>::type;

      /**
       * @brief   The allocator's const void pointer type.
       *
       * @c Alloc::const_void_pointer if that type exists, otherwise
       * <tt> pointer_traits<pointer>::rebind<const void> </tt>
      */
      using const_void_pointer = typename _Ptr<__cv_pointer, const void>::type;

      /**
       * @brief   The allocator's difference type
       *
       * @c Alloc::difference_type if that type exists, otherwise
       * <tt> pointer_traits<pointer>::difference_type </tt>
      */
      using difference_type = typename _Diff<_Alloc, pointer>::type;

      /**
       * @brief   The allocator's size type
       *
       * @c Alloc::size_type if that type exists, otherwise
       * <tt> make_unsigned<difference_type>::type </tt>
      */
      using size_type = typename _Size<_Alloc, difference_type>::type;

      /**
       * @brief   How the allocator is propagated on copy assignment
       *
       * @c Alloc::propagate_on_container_copy_assignment if that type exists,
       * otherwise @c false_type
      */
      using propagate_on_container_copy_assignment
    = __detected_or_t<false_type, __pocca, _Alloc>;

      /**
       * @brief   How the allocator is propagated on move assignment
       *
       * @c Alloc::propagate_on_container_move_assignment if that type exists,
       * otherwise @c false_type
      */
      using propagate_on_container_move_assignment
    = __detected_or_t<false_type, __pocma, _Alloc>;

      /**
       * @brief   How the allocator is propagated on swap
       *
       * @c Alloc::propagate_on_container_swap if that type exists,
       * otherwise @c false_type
      */
      using propagate_on_container_swap
    = __detected_or_t<false_type, __pocs, _Alloc>;

      /**
       * @brief   Whether all instances of the allocator type compare equal.
       *
       * @c Alloc::is_always_equal if that type exists,
       * otherwise @c is_empty<Alloc>::type
      */
      using is_always_equal
    = __detected_or_t<typename is_empty<_Alloc>::type, __equal, _Alloc>;

      template<typename _Tp>
    using rebind_alloc = __alloc_rebind<_Alloc, _Tp>;
      template<typename _Tp>
    using rebind_traits = allocator_traits<rebind_alloc<_Tp>>;

    private:
      template<typename _Alloc2>
    static auto
    _S_allocate(_Alloc2& __a, size_type __n, const_void_pointer __hint, int)
    -> decltype(__a.allocate(__n, __hint))
    { return __a.allocate(__n, __hint); }

      template<typename _Alloc2>
    static pointer
    _S_allocate(_Alloc2& __a, size_type __n, const_void_pointer, ...)
    { return __a.allocate(__n); }

      template<typename _Tp, typename... _Args>
    struct __construct_helper
    {
      template<typename _Alloc2,
        typename = decltype(std::declval<_Alloc2*>()->construct(
          std::declval<_Tp*>(), std::declval<_Args>()...))>
        static true_type __test(int);

      template<typename>
        static false_type __test(...);

      using type = decltype(__test<_Alloc>(0));
    };

      template<typename _Tp, typename... _Args>
    using __has_construct
      = typename __construct_helper<_Tp, _Args...>::type;

      template<typename _Tp, typename... _Args>
    static _Require<__has_construct<_Tp, _Args...>>
    _S_construct(_Alloc& __a, _Tp* __p, _Args&&... __args)
    { __a.construct(__p, std::forward<_Args>(__args)...); }

      template<typename _Tp, typename... _Args>
    static
    _Require<__and_<__not_<__has_construct<_Tp, _Args...>>,
                   is_constructible<_Tp, _Args...>>>
    _S_construct(_Alloc&, _Tp* __p, _Args&&... __args)
    { ::new((void*)__p) _Tp(std::forward<_Args>(__args)...); }

      template<typename _Alloc2, typename _Tp>
    static auto
    _S_destroy(_Alloc2& __a, _Tp* __p, int)
    -> decltype(__a.destroy(__p))
    { __a.destroy(__p); }

      template<typename _Alloc2, typename _Tp>
    static void
    _S_destroy(_Alloc2&, _Tp* __p, ...)
    { __p->~_Tp(); }

      template<typename _Alloc2>
    static auto
    _S_max_size(_Alloc2& __a, int)
    -> decltype(__a.max_size())
    { return __a.max_size(); }

      template<typename _Alloc2>
    static size_type
    _S_max_size(_Alloc2&, ...)
    {
      // _GLIBCXX_RESOLVE_LIB_DEFECTS
      // 2466. allocator_traits::max_size() default behavior is incorrect
      return __gnu_cxx::__numeric_traits<size_type>::__max
        / sizeof(value_type);
    }

      template<typename _Alloc2>
    static auto
    _S_select(_Alloc2& __a, int)
    -> decltype(__a.select_on_container_copy_construction())
    { return __a.select_on_container_copy_construction(); }

      template<typename _Alloc2>
    static _Alloc2
    _S_select(_Alloc2& __a, ...)
    { return __a; }

    public:

      /**
       *  @brief  Allocate memory.
       *  @param  __a  An allocator.
       *  @param  __n  The number of objects to allocate space for.
       *
       *  Calls @c a.allocate(n)
      */
      static pointer
      allocate(_Alloc& __a, size_type __n)
      { return __a.allocate(__n); }

      /**
       *  @brief  Allocate memory.
       *  @param  __a  An allocator.
       *  @param  __n  The number of objects to allocate space for.
       *  @param  __hint Aid to locality.
       *  @return Memory of suitable size and alignment for @a n objects
       *          of type @c value_type
       *
       *  Returns <tt> a.allocate(n, hint) </tt> if that expression is
       *  well-formed, otherwise returns @c a.allocate(n)
      */
      static pointer
      allocate(_Alloc& __a, size_type __n, const_void_pointer __hint)
      { return _S_allocate(__a, __n, __hint, 0); }

      /**
       *  @brief  Deallocate memory.
       *  @param  __a  An allocator.
       *  @param  __p  Pointer to the memory to deallocate.
       *  @param  __n  The number of objects space was allocated for.
       *
       *  Calls <tt> a.deallocate(p, n) </tt>
      */
      static void
      deallocate(_Alloc& __a, pointer __p, size_type __n)
      { __a.deallocate(__p, __n); }

      /**
       *  @brief  Construct an object of type @a _Tp
       *  @param  __a  An allocator.
       *  @param  __p  Pointer to memory of suitable size and alignment for Tp
       *  @param  __args Constructor arguments.
       *
       *  Calls <tt> __a.construct(__p, std::forward<Args>(__args)...) </tt>
       *  if that expression is well-formed, otherwise uses placement-new
       *  to construct an object of type @a _Tp at location @a __p from the
       *  arguments @a __args...
      */
      template<typename _Tp, typename... _Args>
    static auto construct(_Alloc& __a, _Tp* __p, _Args&&... __args)
    -> decltype(_S_construct(__a, __p, std::forward<_Args>(__args)...))
    { _S_construct(__a, __p, std::forward<_Args>(__args)...); }

      /**
       *  @brief  Destroy an object of type @a _Tp
       *  @param  __a  An allocator.
       *  @param  __p  Pointer to the object to destroy
       *
       *  Calls @c __a.destroy(__p) if that expression is well-formed,
       *  otherwise calls @c __p->~_Tp()
      */
      template<typename _Tp>
    static void destroy(_Alloc& __a, _Tp* __p)
    { _S_destroy(__a, __p, 0); }

      /**
       *  @brief  The maximum supported allocation size
       *  @param  __a  An allocator.
       *  @return @c __a.max_size() or @c numeric_limits<size_type>::max()
       *
       *  Returns @c __a.max_size() if that expression is well-formed,
       *  otherwise returns @c numeric_limits<size_type>::max()
      */
      static size_type max_size(const _Alloc& __a) noexcept
      { return _S_max_size(__a, 0); }

      /**
       *  @brief  Obtain an allocator to use when copying a container.
       *  @param  __rhs  An allocator.
       *  @return @c __rhs.select_on_container_copy_construction() or @a __rhs
       *
       *  Returns @c __rhs.select_on_container_copy_construction() if that
       *  expression is well-formed, otherwise returns @a __rhs
      */
      static _Alloc
      select_on_container_copy_construction(const _Alloc& __rhs)
      { return _S_select(__rhs, 0); }
    };
```
# bits/ptr_traits.h
```c++
#include <bits/move.h>
```
声明了一个class __undefined,恰如其言，没有任何定义。因此任何引用都会引发编译错误。
同时也定义了辅助函数__get_first_arg用于操作可变实参：
```c++
 class __undefined;

  // Given Template<T, ...> return T, otherwise invalid.
  template<typename _Tp>
    struct __get_first_arg
    { using type = __undefined; };

  template<template<typename, typename...> class _Template, typename _Tp,
           typename... _Types>
    struct __get_first_arg<_Template<_Tp, _Types...>>
    { using type = _Tp; };

  template<typename _Tp>
    using __get_first_arg_t = typename __get_first_arg<_Tp>::type;
```
还有replace_first_arg的定义。
下面是pointer_traits,用于提供对指针的抽象:
```c++
/**
   * @brief  Uniform interface to all pointer-like types
   * @ingroup pointer_abstractions
  */
  template<typename _Ptr>
    struct pointer_traits
    {
    private:
      template<typename _Tp>
    using __element_type = typename _Tp::element_type;

      template<typename _Tp>
    using __difference_type = typename _Tp::difference_type;

      template<typename _Tp, typename _Up, typename = void>
    struct __rebind : __replace_first_arg<_Tp, _Up> { };

      template<typename _Tp, typename _Up>
    struct __rebind<_Tp, _Up, __void_t<typename _Tp::template rebind<_Up>>>
    { using type = typename _Tp::template rebind<_Up>; };

    public:
      /// The pointer type.
      using pointer = _Ptr;

      /// The type pointed to.
      using element_type
    = __detected_or_t<__get_first_arg_t<_Ptr>, __element_type, _Ptr>;

      /// The type used to represent the difference between two pointers.
      using difference_type
    = __detected_or_t<ptrdiff_t, __difference_type, _Ptr>;

      /// A pointer to a different type.
      template<typename _Up>
        using rebind = typename __rebind<_Ptr, _Up>::type;

      static _Ptr
      pointer_to(__make_not_void<element_type>& __e)
      { return _Ptr::pointer_to(__e); }

      static_assert(!is_same<element_type, __undefined>::value,
      "pointer type defines element_type or is like SomePointer<T, Args>");
    };
```
内置指针的pointer_traits:
```c++
 template<typename _Tp>
    struct pointer_traits<_Tp*>
    {
      /// The pointer type
      typedef _Tp* pointer;
      /// The type pointed to
      typedef _Tp  element_type;
      /// Type used to represent the difference between two pointers
      typedef ptrdiff_t difference_type;

      template<typename _Up>
        using rebind = _Up*;

      /**
       *  @brief  Obtain a pointer to an object
       *  @param  __r  A reference to an object of type @c element_type
       *  @return @c addressof(__r)
      */
      static pointer
      pointer_to(__make_not_void<element_type>& __r) noexcept
      { return std::addressof(__r); }
    };
```
# bits/allocator.h
对allocator<T>的定义。
allocator<void>没有任何实际定义，其他的allocator<T>继承自__allocator_base<T>,也就是new_allocator<T>,默认所有的空间分配从::new得到。
同样，这是一个allocator的接口规范。
注意，using同样是可以取消定义的，这里取消了前面对__allocator_base的using定义，使用#undef
```c++
  */
  template<typename _Tp>
    class allocator: public __allocator_base<_Tp>
    {
   public:
      typedef size_t     size_type;
      typedef ptrdiff_t  difference_type;
      typedef _Tp*       pointer;
      typedef const _Tp* const_pointer;
      typedef _Tp&       reference;
      typedef const _Tp& const_reference;
      typedef _Tp        value_type;

      template<typename _Tp1>
        struct rebind
        { typedef allocator<_Tp1> other; };

#if __cplusplus >= 201103L
      // _GLIBCXX_RESOLVE_LIB_DEFECTS
      // 2103. std::allocator propagate_on_container_move_assignment
      typedef true_type propagate_on_container_move_assignment;

      typedef true_type is_always_equal;
#endif

      allocator() throw() { }

      allocator(const allocator& __a) throw()
      : __allocator_base<_Tp>(__a) { }

      template<typename _Tp1>
        allocator(const allocator<_Tp1>&) throw() { }

      ~allocator() throw() { }

      // Inherit everything else.
    };
      // Undefine.
#undef __allocator_base
```
声明外部特化其中的两个类，也就是说：不要在这里特化我。
```c++
  extern template class allocator<char>;
  extern template class allocator<wchar_t>;
```
# bits/memoryfwd.h
声明了allocator<T>的泛型，其中allocator<void>泛型单独定义，没有allocate,deallocate两个方法，你确实不能对void分配空间。
这些模板的定义随后在bits/allocator.h中找到。
```c++
/*...std...*/
 template<typename>
    class allocator;

  template<>
    class allocator<void>;

  /// Declare uses_allocator so it can be specialized in \<queue\> etc.
  template<typename, typename>
    struct uses_allocator;
```
# bits/c++allocator.h
仅仅是对ext/new_allocator.h的重新引用
```c++
namespace std{
  template<typename _Tp>
    using __allocator_base = __gnu_cxx::new_allocator<_Tp>;
}
```
# ext/concurrence.h
```c++
#pragma GCC system_header

#include <exception>
#include <bits/gthr.h> 
#include <bits/functexcept.h>
#include <bits/cpp_type_traits.h>
#include <ext/type_traits.h>
```

# bits/gthr.h
通过__GTHREADS来定义是否支持线程
```c++
#define __GTHREADS 1
```
该文件大部分是注释，默认引入了bits/gthr-default.h文件
线程支持相关的接口：
```c
     int __gthread_once (__gthread_once_t *once, void (*func) ())

     int __gthread_key_create (__gthread_key_t *keyp, void (*dtor) (void *))
     int __gthread_key_delete (__gthread_key_t key)

     void *__gthread_getspecific (__gthread_key_t key)
     int __gthread_setspecific (__gthread_key_t key, const void *ptr)
     /*......*/
```
# bits/gthr-default.h
```c++
/* POSIX threads specific definitions.
   Easy, since the interface is just one-to-one mapping.  */
```
用于定义POSIX线程标准特别规范
注意：这个文件只是默认实现，在各个系统上不同，比如下面的pthread.h unistd.h都是类unix系统的标准文件，win32不支持。
```c++
#define __GTHREADS 1
#define __GTHREADS_CXX0X 1
#include <pthread.h>
# include <unistd.h>
typedef pthread_t __gthread_t;
typedef pthread_key_t __gthread_key_t;
typedef pthread_once_t __gthread_once_t;
typedef pthread_mutex_t __gthread_mutex_t;
typedef pthread_mutex_t __gthread_recursive_mutex_t;
typedef pthread_cond_t __gthread_cond_t;
typedef struct timespec __gthread_time_t;
```

# ext/new_allocator.h
该文件定义了一个位于命名空间__gnu_cxx中的类：new_allocator,顾名思义，就是纯粹使用全局new函数(::new,::delete)，delete函数作为分配策略的分配器。
同样，这里也有一个通用的 allocator_traits概念。construct/destroy其实就是placement new/delete的直接调用。
注意construct的特殊写法， Con(forward(args)...),
max_size默认返回size_t(-1)/sizeof(_Tp),也就是说new的分配空间其实就是全局分配空间，系统的地址线有多宽new就有多大。
```c++
 /**
   *  @brief  An allocator that uses global new, as per [20.4].
   *  @ingroup allocators
   *
   *  This is precisely the allocator defined in the C++ Standard. 
   *    - all allocation calls operator new
   *    - all deallocation calls operator delete
   *
   *  @tparam  _Tp  Type of allocated object.
   */
  template<typename _Tp>
    class new_allocator
    {
    public:
      typedef size_t     size_type;
      typedef ptrdiff_t  difference_type;
      typedef _Tp*       pointer;
      typedef const _Tp* const_pointer;
      typedef _Tp&       reference;
      typedef const _Tp& const_reference;
      typedef _Tp        value_type;

      template<typename _Tp1>
        struct rebind
        { typedef new_allocator<_Tp1> other; };

#if __cplusplus >= 201103L
      // _GLIBCXX_RESOLVE_LIB_DEFECTS
      // 2103. propagate_on_container_move_assignment
      typedef std::true_type propagate_on_container_move_assignment;
#endif

      new_allocator() _GLIBCXX_USE_NOEXCEPT { }

      new_allocator(const new_allocator&) _GLIBCXX_USE_NOEXCEPT { }

      template<typename _Tp1>
        new_allocator(const new_allocator<_Tp1>&) _GLIBCXX_USE_NOEXCEPT { }

      ~new_allocator() _GLIBCXX_USE_NOEXCEPT { }

      pointer
      address(reference __x) const _GLIBCXX_NOEXCEPT
      { return std::__addressof(__x); }

      const_pointer
      address(const_reference __x) const _GLIBCXX_NOEXCEPT
      { return std::__addressof(__x); }

      // NB: __n is permitted to be 0.  The C++ standard says nothing
      // about what the return value is when __n == 0.
      pointer
      allocate(size_type __n, const void* = 0)
      { 
    if (__n > this->max_size())
      std::__throw_bad_alloc();

    return static_cast<_Tp*>(::operator new(__n * sizeof(_Tp)));
      }

      // __p is not permitted to be a null pointer.
      void
      deallocate(pointer __p, size_type)
      { ::operator delete(__p); }

      size_type
      max_size() const _GLIBCXX_USE_NOEXCEPT
      { return size_t(-1) / sizeof(_Tp); }


#if __cplusplus >= 201103L
      template<typename _Up, typename... _Args>
        void
        construct(_Up* __p, _Args&&... __args)
    { ::new((void *)__p) _Up(std::forward<_Args>(__args)...); }

      template<typename _Up>
        void 
        destroy(_Up* __p) { __p->~_Up(); }
#else
      // _GLIBCXX_RESOLVE_LIB_DEFECTS
      // 402. wrong new expression in [some_] allocator::construct
      void 
      construct(pointer __p, const _Tp& __val) 
      { ::new((void *)__p) _Tp(__val); }

      void 
      destroy(pointer __p) { __p->~_Tp(); }
#endif
    };

  template<typename _Tp>
    inline bool
    operator==(const new_allocator<_Tp>&, const new_allocator<_Tp>&)
    { return true; }
  
  template<typename _Tp>
    inline bool
    operator!=(const new_allocator<_Tp>&, const new_allocator<_Tp>&)
    { return false; }
```

# bits/stl_alogbase.h
定义了一系列函数
```c++
 template<typename _ForwardIterator1, typename _ForwardIterator2>
    inline void
    iter_swap(_ForwardIterator1 __a, _ForwardIterator2 __b){
        swap(*__a, *__b);
    }
```
该函数用于交换两个迭代器的内容。
其他如swap_ranges,min
```c++
  template<typename _Tp>
    _GLIBCXX14_CONSTEXPR
    inline const _Tp&
    min(const _Tp& __a, const _Tp& __b)
    {
      // concept requirements
      __glibcxx_function_requires(_LessThanComparableConcept<_Tp>)
      //return __b < __a ? __b : __a;
      if (__b < __a)
    return __b;
      return __a;
    }
```
max,自定义比较器的min,max
然后定义了__copy_move系列结构，含有唯一静态函数：__copy_m,根据不同的需求，要么使用循环复制移动，要么调用内置的__builtin_memmove函数
这些函数是move(itbeg,itend,result)的辅助函数。_a后缀的意思是auxilury.
还有其他的比如fill，fill_n,equal,mismatch等
```c++
  template<>
    struct __copy_move<false, false, random_access_iterator_tag>
    {
      template<typename _II, typename _OI>
        static _OI
        __copy_m(_II __first, _II __last, _OI __result)
        { 
      typedef typename iterator_traits<_II>::difference_type _Distance;
      for(_Distance __n = __last - __first; __n > 0; --__n)
        {
          *__result = *__first;
          ++__first;
          ++__result;
        }
      return __result;
    }
    };//一般性实现
template<bool _IsMove>
    struct __copy_move<_IsMove, true, random_access_iterator_tag>
    {
      template<typename _Tp>
        static _Tp*
        __copy_m(const _Tp* __first, const _Tp* __last, _Tp* __result)
        {
#if __cplusplus >= 201103L
      using __assignable = conditional<_IsMove,
                       is_move_assignable<_Tp>,
                       is_copy_assignable<_Tp>>;
      // trivial types can have deleted assignment
      static_assert( __assignable::type::value, "type is not assignable" );
#endif
      const ptrdiff_t _Num = __last - __first;
      if (_Num)
        __builtin_memmove(__result, __first, sizeof(_Tp) * _Num);
      return __result + _Num;
    }
    };
```
注意:__builton_memmove并没有实现。
# bits/stl_iterator.h
先定义reverse_iterator,它和原来的iterator满足下面的恒等式：
```c++
&*(reverse_iterator(i)) == &*(i - 1)
```
因此下面的定义产生了：
```c++

  protected:
      _Iterator current;
      /*......*/
    reference
      operator*() const
      {
    _Iterator __tmp = current;
    return *--__tmp;
      }
  reverse_iterator&
      operator++()
      {
    --current;
    return *this;
      }
```
可见它其实就是封装了某些操作，改变了操作的语义而已。current变量其实就是当前元素的下一个指针。
定义back_insert_iterator和配对的back_inserter函数：
```c++
 template<typename _Container>
    class back_insert_iterator
    : public iterator<output_iterator_tag, void, void, void, void>
    {
    protected:
      _Container* container;
    public:
        //唯一创建的方法
      explicit
      back_insert_iterator(_Container& __x)
      : container(std::__addressof(__x)) { }

    inline back_insert_iterator<_Container>
    back_inserter(_Container& __x)
    { return back_insert_iterator<_Container>(__x); }

    // = 操作，其实就是调用容器的push_back操作
          back_insert_iterator&
      operator=(const typename _Container::value_type& __value)
      {
    container->push_back(__value);
    return *this;
      }

    ///返回迭代器本身，注意，这说明插入迭代器不能用于获取值，只能用于设置值
      back_insert_iterator&
      operator*()
      { return *this; }

      /// ++操作，但是指针实际上不移动，因为调用的永远是容器的push_back(其他容器可能会重新定义自己的iterator)
      back_insert_iterator&
      operator++()
      { return *this; }
  }
```
至于front_insert_iterator,insert_iterator都是同样的手法。


# bits/stl_iterator_base_types.h
首先定义__iterator_traits。很显然，任何具有下面定义类型的都能叫做iterator
```c++
  template<typename _Iterator, typename = __void_t<>>
    struct __iterator_traits { };

  template<typename _Iterator>
    struct __iterator_traits<_Iterator,
                 __void_t<typename _Iterator::iterator_category,
                      typename _Iterator::value_type,
                      typename _Iterator::difference_type,
                      typename _Iterator::pointer,
                      typename _Iterator::reference>>
    {
      typedef typename _Iterator::iterator_category iterator_category;
      typedef typename _Iterator::value_type        value_type;
      typedef typename _Iterator::difference_type   difference_type;
      typedef typename _Iterator::pointer           pointer;
      typedef typename _Iterator::reference         reference;
    };
```

然后iterator_traits继承之，但是没有任何其他改动
```c++
  template<typename _Iterator>
    struct iterator_traits
    : public __iterator_traits<_Iterator> { };
```
然后是iterator接口：
```c++
  template<typename _Category, typename _Tp, typename _Distance = ptrdiff_t,
           typename _Pointer = _Tp*, typename _Reference = _Tp&>
    struct iterator
    {
      /// One of the @link iterator_tags tag types@endlink.
      typedef _Category  iterator_category;
      /// The type "pointed to" by the iterator.
      typedef _Tp        value_type;
      /// Distance between iterators is represented as this type.
      typedef _Distance  difference_type;
      /// This type represents a pointer-to-value_type.
      typedef _Pointer   pointer;
      /// This type represents a reference-to-value_type.
      typedef _Reference reference;
    };
```
# bits/stl_iterator_base_funcs.h
```c++
#include <bits/concept_check.h>
#include <debug/assertions.h>
```
定义了__distance用于计算两个迭代器的距离，distance用于选择不同的__distance进行调用
这里tag是一个空的结构体，用于多种函数编译时选择
其他如advance,next,prev实现对迭代器的位置修改操作
```c++
  struct input_iterator_tag { };
  struct output_iterator_tag { };

   __distance(_InputIterator __first, _InputIterator __last,
               input_iterator_tag){
   while (__first != __last)
    {
      ++__first;
      ++__n;
    }
      return __n;
  }
  // 特化的针对随机迭代器的版本
    template<typename _RandomAccessIterator>
    inline typename iterator_traits<_RandomAccessIterator>::difference_type
    __distance(_RandomAccessIterator __first, _RandomAccessIterator __last,
               random_access_iterator_tag)
    {
      // concept requirements
      __glibcxx_function_requires(_RandomAccessIteratorConcept<
                  _RandomAccessIterator>)
      return __last - __first;
    }

    // 通用函数
      template<typename _InputIterator>
    inline typename iterator_traits<_InputIterator>::difference_type
    distance(_InputIterator __first, _InputIterator __last)
    {
      // concept requirements -- taken care of in __distance
      return std::__distance(__first, __last,
                 std::__iterator_category(__first));
    }
```
# bits/stl_pair.h
包含pair的核心实现：
```c++
 template<typename _T1, typename _T2>
    struct pair
    {
      typedef _T1 first_type;    /// @c first_type is the first bound type
      typedef _T2 second_type;   /// @c second_type is the second bound type

      _T1 first;                 /// @c first is a copy of the first object
      _T2 second;               
      /*......*/
  }
```
还有swap,make_pair等。

# bits/move.h
引入了bits/concept_check.h,但是该文件实际使用的是boost库，而我们的系统又没有，所以默认没有任何作用

定义了__addressof函数,同std::addressof,用于获取一个引用的地址，特别适用于operator&被重载的情况，具体实现：
```c++
  template<typename _Tp>
    inline _Tp*
    __addressof(_Tp& __r) _GLIBCXX_NOEXCEPT
    {
      return reinterpret_cast<_Tp*>
    (&const_cast<char&>(reinterpret_cast<const volatile char&>(__r)));
    }
```
先将原类型按地址转化为const volatile char引用类型，然后去掉const，获得指针。对于operator&,char类型没有重载。

定义了一些constexpr函数：forward，用于对右值函数参数类型进行合适的转发，右值参数T &&t可以接受lvalue和rvalue，而std::forward用于保留这种调用时信息。非constexpr的函数在C++14中移除了，剩下的都是constexpr的函数。


std::move的实现，就是将一个类型转换成右值引用类型，然后将一个值转换为这种类型
```c++
  template<typename _Tp>
    constexpr typename std::remove_reference<_Tp>::type&&
    move(_Tp&& __t) noexcept
    { return static_cast<typename std::remove_reference<_Tp>::type&&>(__t); }
```

swap的实现，使用move语义：
```c++
    // #if __cplusplus >= 201103L
  template<typename _Tp>
    inline
    typename enable_if<__and_<is_move_constructible<_Tp>,
                  is_move_assignable<_Tp>>::value>::type
    swap(_Tp& __a, _Tp& __b)
    noexcept(__and_<is_nothrow_move_constructible<_Tp>,
                is_nothrow_move_assignable<_Tp>>::value)
#endif
    {
      // concept requirements
      __glibcxx_function_requires(_SGIAssignableConcept<_Tp>)

      _Tp __tmp = std::move(__a);
      __a = std::move(__b);
      __b = std::move(__tmp);
    }

    //函数类型
    {
      for (size_t __n = 0; __n < _Nm; ++__n)
        swap(__a[__n], __b[__n]);
    }
```
# type_traits
remove_reference泛型,通过模板特化去除左值引用，右值引用，剩下纯粹的类型信息。
用于获取纯粹的类型。
```c++
 /// remove_reference
  template<typename _Tp>
    struct remove_reference
    { typedef _Tp   type; };

  template<typename _Tp>
    struct remove_reference<_Tp&>
    { typedef _Tp   type; };

  template<typename _Tp>
    struct remove_reference<_Tp&&>
    { typedef _Tp   type; };
    /*......*/
      /// Alias template for remove_reference
  template<typename _Tp>
    using remove_reference_t = typename remove_reference<_Tp>::type;
```
通过编译器内置实现的内联表达式：
__is_enum,__is_union,__is_class
```c++
 /// is_enum
  template<typename _Tp>
    struct is_enum
    : public integral_constant<bool, __is_enum(_Tp)>
    { };
    /*......*/
```
is_function的实现,基本上囊括了所有函数可能出现的形式，注意其中6个省略号的含义，等价于_Res(_ArgTypes..., ...)
```c++
/// is_function
  template<typename>
    struct is_function
    : public false_type { };

  template<typename _Res, typename... _ArgTypes>
    struct is_function<_Res(_ArgTypes...)>
    : public true_type { };

  template<typename _Res, typename... _ArgTypes>
    struct is_function<_Res(_ArgTypes...) &>
    : public true_type { };

  template<typename _Res, typename... _ArgTypes>
    struct is_function<_Res(_ArgTypes...) &&>
    : public true_type { };

  template<typename _Res, typename... _ArgTypes>
    struct is_function<_Res(_ArgTypes......)>
    : public true_type { };

  template<typename _Res, typename... _ArgTypes>
    struct is_function<_Res(_ArgTypes......) &>
    : public true_type { };

  template<typename _Res, typename... _ArgTypes>
    struct is_function<_Res(_ArgTypes......) &&>
    : public true_type { };

  template<typename _Res, typename... _ArgTypes>
    struct is_function<_Res(_ArgTypes...) const>
    : public true_type { };

  template<typename _Res, typename... _ArgTypes>
    struct is_function<_Res(_ArgTypes...) const &>
    : public true_type { };

  template<typename _Res, typename... _ArgTypes>
    struct is_function<_Res(_ArgTypes...) const &&>
    : public true_type { };

  template<typename _Res, typename... _ArgTypes>
    struct is_function<_Res(_ArgTypes......) const>
    : public true_type { };

  template<typename _Res, typename... _ArgTypes>
    struct is_function<_Res(_ArgTypes......) const &>
    : public true_type { };

  template<typename _Res, typename... _ArgTypes>
    struct is_function<_Res(_ArgTypes......) const &&>
    : public true_type { };

  template<typename _Res, typename... _ArgTypes>
    struct is_function<_Res(_ArgTypes...) volatile>
    : public true_type { };

  template<typename _Res, typename... _ArgTypes>
    struct is_function<_Res(_ArgTypes...) volatile &>
    : public true_type { };

  template<typename _Res, typename... _ArgTypes>
    struct is_function<_Res(_ArgTypes...) volatile &&>
    : public true_type { };

  template<typename _Res, typename... _ArgTypes>
    struct is_function<_Res(_ArgTypes......) volatile>
    : public true_type { };

  template<typename _Res, typename... _ArgTypes>
    struct is_function<_Res(_ArgTypes......) volatile &>
    : public true_type { };

  template<typename _Res, typename... _ArgTypes>
    struct is_function<_Res(_ArgTypes......) volatile &&>
    : public true_type { };

  template<typename _Res, typename... _ArgTypes>
    struct is_function<_Res(_ArgTypes...) const volatile>
    : public true_type { };

  template<typename _Res, typename... _ArgTypes>
    struct is_function<_Res(_ArgTypes...) const volatile &>
    : public true_type { };

  template<typename _Res, typename... _ArgTypes>
    struct is_function<_Res(_ArgTypes...) const volatile &&>
    : public true_type { };

  template<typename _Res, typename... _ArgTypes>
    struct is_function<_Res(_ArgTypes......) const volatile>
    : public true_type { };

  template<typename _Res, typename... _ArgTypes>
    struct is_function<_Res(_ArgTypes......) const volatile &>
    : public true_type { };

  template<typename _Res, typename... _ArgTypes>
    struct is_function<_Res(_ArgTypes......) const volatile &&>
    : public true_type { };
```

remove_volatile remove_const remove_cv ...
```c++
 /// remove_const
  template<typename _Tp>
    struct remove_const
    { typedef _Tp     type; };

  template<typename _Tp>
    struct remove_const<_Tp const>
    { typedef _Tp     type; };
  
  /// remove_volatile
  template<typename _Tp>
    struct remove_volatile
    { typedef _Tp     type; };

  template<typename _Tp>
    struct remove_volatile<_Tp volatile>
    { typedef _Tp     type; };
  
  /// remove_cv
  template<typename _Tp>
    struct remove_cv
    {
      typedef typename
      remove_const<typename remove_volatile<_Tp>::type>::type     type;
    };
```

make_signed,获取相应的unsigned类型，bool类型没有signed：
```c++
 // Integral, but don't define.
  template<>
    struct make_unsigned<bool>;

  // Utility for finding the signed versions of unsigned integral types.
  template<typename _Tp>
    struct __make_signed
    { typedef _Tp __type; };
```

remove_extent和remove_all_extents，取得数组的基本类型
```c++

  /// remove_extent
  template<typename _Tp>
    struct remove_extent
    { typedef _Tp     type; };

  template<typename _Tp, std::size_t _Size>
    struct remove_extent<_Tp[_Size]>
    { typedef _Tp     type; };

  template<typename _Tp>
    struct remove_extent<_Tp[]>
    { typedef _Tp     type; };

  /// remove_all_extents
  template<typename _Tp>
    struct remove_all_extents
    { typedef _Tp     type; };

  template<typename _Tp, std::size_t _Size>
    struct remove_all_extents<_Tp[_Size]>
    { typedef typename remove_all_extents<_Tp>::type     type; };

  template<typename _Tp>
    struct remove_all_extents<_Tp[]>
    { typedef typename remove_all_extents<_Tp>::type     type; };
```

conditional的实现
```c++
  // Primary template.
  /// Define a member typedef @c type to one of two argument types.
  template<bool _Cond, typename _Iftrue, typename _Iffalse>
    struct conditional
    { typedef _Iftrue type; };

  // Partial specialization for false.
  template<typename _Iftrue, typename _Iffalse>
    struct conditional<false, _Iftrue, _Iffalse>
    { typedef _Iffalse type; };
```

# bits/cpp_type_traits
被type_traits包含，定义了__true_type,__false_type,__is_integer~__is_byte(char有符号和无符号，但是bool不是byte)等基本类型函数。

# bits/ptr_traits.h
定义了一个概念：pointer_traits,两种模板：
pointer_traits<_Ptr>,pointer_traits<_Tp*>, traits中包含如下内容：
pointer,element_type,difference_type,rebind<U*>(任意转换为另一种指针),pointer_to(element_type&)取指针函数。
注意：这种概念是相当宽泛的，任何具有上面说的元素的都能够称为指针类型。
也就是说,pointer_traits是一种概念，它和实现之间的唯一联系就是要求实现提供最少的类型和函数集合。

# ext/type_traits.h
包含cpp_type_traits.h
enable_if的实现,就是让定义出现与否。
```c++

  // Define a nested type if some predicate holds.
  template<bool, typename>
    struct __enable_if 
    { };

  template<typename _Tp>
    struct __enable_if<true, _Tp>
    { typedef _Tp __type; };

```


# bits/predefined_ops.h
此文件包含一些命名的操作符：比如将迭代器的赋值 *ita=*itb, 定义如下
```c++
  struct _Iter_equal_to_iter
  {
    template<typename _Iterator1, typename _Iterator2>
      bool
      operator()(_Iterator1 __it1, _Iterator2 __it2) const
      { return *__it1 == *__it2; }
  };
```
其他比如<,>等。
# bits/exception_defines.h
该文件对选项-fno-execption进行回应：
```c++
#if ! __cpp_exceptions
// Iff -fno-exceptions, transform error handling code to work without it.
# define __try      if (true)
# define __catch(X) if (false)
# define __throw_exception_again
#else
// Else proceed normally.
# define __try      try
# define __catch(X) catch(X)
# define __throw_exception_again throw
#endif
```

# bits/functexcept.h
该文件定义了一堆用于抛出异常的辅助函数，很显然的一点是，这些函数都没有实际的定义。可能需要操作系统提供相应的abi
注意：实现这些函数时，必须实现noreturn承诺，否则程序继续在原地方继续下去，造成更多的错误。  
```c++
namespace std _GLIBCXX_VISIBILITY(default)
{
_GLIBCXX_BEGIN_NAMESPACE_VERSION

  // Helper for exception objects in <except>
  void
  __throw_bad_exception(void) __attribute__((__noreturn__));
  /*......*/
    // Helpers for exception objects in <functional>
  void
  __throw_bad_function_call() __attribute__((__noreturn__));

_GLIBCXX_END_NAMESPACE_VERSION
} //namespace

```


# exception
定义了exception,bad_exception等两个类
然后就是一些系统相关的函数：
```c++
 /// If you write a replacement %terminate handler, it must be of this type.
  typedef void (*terminate_handler) ();

  /// If you write a replacement %unexpected handler, it must be of this type.
  typedef void (*unexpected_handler) ();

  /// Takes a new handler function as an argument, returns the old function.
  terminate_handler set_terminate(terminate_handler) _GLIBCXX_USE_NOEXCEPT;
   terminate_handler get_terminate() noexcept;

  /** The runtime will call this function if %exception handling must be
   *  abandoned for any reason.  It can also be called by the user.  */
  void terminate() _GLIBCXX_USE_NOEXCEPT __attribute__ ((__noreturn__));

  /// Takes a new handler function as an argument, returns the old function.
  unexpected_handler set_unexpected(unexpected_handler) _GLIBCXX_USE_NOEXCEPT;

#if __cplusplus >= 201103L
  /// Return the current unexpected handler.
  unexpected_handler get_unexpected() noexcept;
#endif

  /** The runtime will call this function if an %exception is thrown which
   *  violates the function's %exception specification.  */
  void unexpected() __attribute__ ((__noreturn__));

  /** [18.6.4]/1:  'Returns true after completing evaluation of a
   *  throw-expression until either completing initialization of the
   *  exception-declaration in the matching handler or entering @c unexpected()
   *  due to the throw; or after entering @c terminate() for any reason
   *  other than an explicit call to @c terminate().  [Note: This includes
   *  stack unwinding [15.2].  end note]'
   *
   *  2: 'When @c uncaught_exception() is true, throwing an
   *  %exception can result in a call of @c terminate()
   *  (15.5.1).'
   */
  bool uncaught_exception() _GLIBCXX_USE_NOEXCEPT __attribute__ ((__pure__));

#if __cplusplus > 201402L || !defined(__STRICT_ANSI__) // c++1z or gnu++98
#define __cpp_lib_uncaught_exceptions 201411
  /// The number of uncaught exceptions.
  int uncaught_exceptions() _GLIBCXX_USE_NOEXCEPT __attribute__ ((__pure__));
#endif

  // @} group exceptions
} // namespace std

namespace __gnu_cxx
{
_GLIBCXX_BEGIN_NAMESPACE_VERSION

  /**
   *  @brief A replacement for the standard terminate_handler which
   *  prints more information about the terminating exception (if any)
   *  on stderr.
   *
   *  @ingroup exceptions
   *
   *  Call
   *   @code
   *     std::set_terminate(__gnu_cxx::__verbose_terminate_handler)
   *   @endcode
   *  to use.  For more info, see
   *  http://gcc.gnu.org/onlinedocs/libstdc++/manual/bk01pt02ch06s02.html
   *
   *  In 3.4 and later, this is on by default.
   */
  void __verbose_terminate_handler();
}
```
末尾则引入了两个文件：
```c++
#include <bits/exception_ptr.h>
#include <bits/nested_exception.h>
```
都定义了一些需要系统本身实现的函数。不过，对于操作系统而言，使用-fno-exception(s)即可

# bits/atomic_lockfree_defines.h
该文件为exception引入，用于配置某些值。
lockfree指的是无需通过加锁即能实现安全共享。针对的是基本类型的读写，如BOOL,CHAR等。注意，这些定义其实指向了编译器给定的定义。
```c++
/**
 * Lock-free property.
 *
 * 0 indicates that the types are never lock-free.
 * 1 indicates that the types are sometimes lock-free.
 * 2 indicates that the types are always lock-free.
 */
 #if __cplusplus >= 201103L
#define ATOMIC_BOOL_LOCK_FREE       __GCC_ATOMIC_BOOL_LOCK_FREE
#define ATOMIC_CHAR_LOCK_FREE       __GCC_ATOMIC_CHAR_LOCK_FREE
#define ATOMIC_WCHAR_T_LOCK_FREE    __GCC_ATOMIC_WCHAR_T_LOCK_FREE
#define ATOMIC_CHAR16_T_LOCK_FREE   __GCC_ATOMIC_CHAR16_T_LOCK_FREE
#define ATOMIC_CHAR32_T_LOCK_FREE   __GCC_ATOMIC_CHAR32_T_LOCK_FREE
#define ATOMIC_SHORT_LOCK_FREE      __GCC_ATOMIC_SHORT_LOCK_FREE
#define ATOMIC_INT_LOCK_FREE        __GCC_ATOMIC_INT_LOCK_FREE
#define ATOMIC_LONG_LOCK_FREE       __GCC_ATOMIC_LONG_LOCK_FREE
#define ATOMIC_LLONG_LOCK_FREE      __GCC_ATOMIC_LLONG_LOCK_FREE
#define ATOMIC_POINTER_LOCK_FREE    __GCC_ATOMIC_POINTER_LOCK_FREE
#endif
```

# debug/assertions
在定义了_GLIBCXX_DEBUG的情况下，使用编译器宏__glibcxx_assert,如果开启_GLIBCXX_DEBUG_PEDANTIC选项，则是大写形式_GLIBCXX_DEBUG_ASSERT
否则就是空语句
```c++
#ifndef _GLIBCXX_DEBUG

# define _GLIBCXX_DEBUG_ASSERT(_Condition)
# define _GLIBCXX_DEBUG_PEDASSERT(_Condition)
# define _GLIBCXX_DEBUG_ONLY(_Statement) ;

#else

#define _GLIBCXX_DEBUG_ASSERT(_Condition) __glibcxx_assert(_Condition)

#ifdef _GLIBCXX_DEBUG_PEDANTIC
# define _GLIBCXX_DEBUG_PEDASSERT(_Condition) _GLIBCXX_DEBUG_ASSERT(_Condition)
#else
# define _GLIBCXX_DEBUG_PEDASSERT(_Condition)
#endif

# define _GLIBCXX_DEBUG_ONLY(_Statement) _Statement

#endif
```

# bits/concept_check.h
该文件其实使用的是boost_concept_check.h文件，但是默认没有开启
在c++11中，concept还没有纳入提案
```c++
#if !defined(_GLIBCXX_CONCEPT_CHECKS) || !_GLIBCXX_HOSTED

#define __glibcxx_function_requires(...)
#define __glibcxx_class_requires(_a,_b)
#define __glibcxx_class_requires2(_a,_b,_c)
#define __glibcxx_class_requires3(_a,_b,_c,_d)
#define __glibcxx_class_requires4(_a,_b,_c,_d,_e)

#else // the checks are on

#include <bits/boost_concept_check.h>
#endif // enable/disable
```

# ext/atomic_word.h
定义了一个原子类型，以及两个原语
```c++

typedef int _Atomic_word;


// This is a memory order acquire fence.
#define _GLIBCXX_READ_MEM_BARRIER __atomic_thread_fence (__ATOMIC_ACQUIRE)
// This is a memory order release fence.
#define _GLIBCXX_WRITE_MEM_BARRIER __atomic_thread_fence (__ATOMIC_RELEASE)
```
# *END* *END* *END*