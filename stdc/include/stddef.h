
#ifndef stddef_h__
#define stddef_h__

#define NULL ((void*)0)
#define offsetof(type,member_id) ((size_t)&(((type *)0)->member_id))

typedef unsigned int size_t;
typedef signed int ptrdiff_t;
typedef int wchar_t;

//done

#endif //stddef_h__