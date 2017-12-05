
#ifndef assert_h__
#define assert_h__

#include <stdio.h>
//void assert will test exp,if it is 0 then call abort
//it will print __FILE__ and __LINE__
#define __STR(x) #x
#define STR(x) __STR(x)

#if defined NDEBUG
#	define assert(ignore) ((void)0)
#else
#	define assert(expr)							\
  ({										\
  ( (expr)									\
   ? 0						\
   : printf("assertation failed@%s:%d -- \"%s\" \n",__FILE__,__LINE__,STR(expr)) );\
  abort(); \
  (expr);\
})

#endif


//assert should abort the program
 //done


#endif //assert_h__