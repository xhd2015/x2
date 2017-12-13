
#include "precompiled_most.cpp"

#if defined(INCLUDE_CONCEPTUAL_PRECOMPILED_MOST_H_D_)
//defined
#else

//#error "not defined"
#endif

#if defined(CODE64)
//====处理动态引入
#if defined(IDE_MODE)
#define CMDUTIL main.cpp //样例
#endif
#if !defined(CMDUTIL)
#error "Please define CMDUTIL!"
#endif
#if defined(CONH) || defined(INC2)

#error
#endif
#define CONH__STR(x) #x
#define CONH_STR(x) CONH__STR(x)
#define CONH(A) ../64/CMDUtil_##A

#define INC(A) CONH_STR(CONH(A))
#include INC(CMDUTIL)
#undef INC
#undef CONH
#undef CMDUTIL
#undef CONH__STR
#undef CONH_STR
//******===动态引入结束


#elif defined(CODE32)

#elif defined(CODE32USER)

#elif defined(CODE16)


#else // do nothing
#warning "You do not defined any code compile patter."
#endif
