
#ifndef NEW_h
#define  NEW_h
#include <c++config> //for size_t

//<p comment="copied from the c++ part of gcc and modified">
namespace std{

struct nothrow_t { };
extern const nothrow_t nothrow;

void* operator new(std::size_t);
void* operator new[](std::size_t);
void operator delete(void*);
void operator delete[](void*);
void* operator new(std::size_t, const std::nothrow_t&i);
void* operator new[](std::size_t, const std::nothrow_t&);
void operator delete(void*, const std::nothrow_t&);
void operator delete[](void*, const std::nothrow_t&);

// Default placement versions of operator new.
inline void* operator new(std::size_t, void* __p)
{ return __p; }
inline void* operator new[](std::size_t, void* __p)
{ return __p; }

// Default placement versions of operator delete.
inline void operator delete  (void*, void*) { }
inline void operator delete[](void*, void*) { }
}//namespace std
//</p>
#endif
