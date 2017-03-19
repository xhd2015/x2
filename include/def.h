
#ifndef DEF_h__
#define DEF_h__

//====数据宏
#if !defined(NULL)
#define NULL 0
#endif


#if defined(CODE64)
typedef __PTRDIFF_TYPE__ ptrdiff_t;
typedef __SIZE_TYPE__ size_t;
#elif defined(CODE32)||defined(CODE16)    //in standard host enviornment,do not use these definitions.
			// You must be very careful about typedef
typedef signed int ptrdiff_t;
typedef unsigned int size_t;
#endif


//=====用于开发标记
#define DEVEL_UNTESTED(who) /*0*/
#define DEVEL_UNCOMPLETED(who_made_this) /*1*/
#define DEVEL_COMPLETED(who) /*2*/
#define DEVEL_TESTET(who) /*3*/
#define DEVEL_WAITTO(x) /*wait to date x*/
#define DEVEL_LAST(who,date) /*last modified*/
#define DEVEL_AUTHOR(author...)    /*who is the author*/
#define DEVEL_DEP(deps...)          /*depend on what?*/

//===========数学宏
#define arrsizeof(arr) (sizeof(arr)/sizeof((arr)[0]))


//====字符串宏
#define __STR(x) #x
#define STR(x) __STR(x)

//extern inline 宏
//除非特别短的函数 或者必须作为宏来实现的函数
//否则这样做会增加代码长度
#define AS_MACRO inline __attribute__((always_inline))
#define DEPRECATED __attribute__((deprecated))
#define NORETURN __attribute__((noreturn))


//定义如果一个功能还没有完全实现，就不要使用
#define INCOMPLETE __attribute__((deprecated))
#define UNTESTED __attribute__((deprecated))
#define TEMPORARY	__attribute__((deprecated))  /*TEMPORARY means that a functoin does not complete all functions as its name
	denotes,it's just for test
*/

//==进入死循环
#define JMP_DIE() __asm__("jmp . \n\t")


//=====中断调用
#define CALL_INT_0(number) __asm__ __volatile__(\
        STR(int) " " STR($) STR(number) STR(\n\t) \
        :::\
        )
#define CALL_INT_1(number,r1,v1) __asm__ __volatile__(\
        STR(int) " " STR($) STR(number) STR(\n\t) \
        :\
        :STR(r1)(v1) \
        :\
        )
#define CALL_INT_2(number,r1,v1,r2,v2) __asm__ __volatile__(\
        STR(int) " " STR($) STR(number) STR(\n\t) \
        :\
        :STR(r1)(v1) , STR(r2)(v2) \
        :\
        )
#define CALL_INT_3(number,r1,v1,r2,v2,r3,v3) __asm__ __volatile__(\
        "int $" STR(number) STR(\n\t) \
        :\
        :STR(r1)(v1) , STR(r2)(v2) ,STR(r3)(v3) \
        :\
        )
#define CALL_INT_4(number,r1,v1,r2,v2,r3,v3,r4,v4) __asm__ __volatile__(\
        "int $" STR(number) STR(\n\t) \
        :\
        :STR(r1)(v1) , STR(r2)(v2) ,STR(r3)(v3) ,STR(r4)(v4) \
        :\
        )
        
#define CALL_INT_5(number,r1,v1,r2,v2,r3,v3,r4,v4,r5,v5) __asm__ __volatile__(\
        STR(int) " " STR($) STR(number) STR(\n\t) \
        :\
        :STR(r1)(v1) , STR(r2)(v2) ,STR(r3)(v3) ,STR(r4)(v4) ,STR(r5)(v5) \
        :\
        )
        
//====中断定义结束
#define INTRETURN() __asm__(\
    "leave \n\t"\
    "iret \n\t"\
    );

//======中断保护、恢复现场
//#define CLI()   __asm__("cli \n\t")
//#define STI()   __asm__("sti \n\t")




//===================设置ds,es的上下文环境====================
/**
*涉及堆栈平衡，不可能由非内联函数函数来实现。
*/
#define ENTER_DS(seg,saver) \
    int saver;\
    if(seg!=Util::SEG_CURRENT){\
    __asm__ __volatile__(\
    "mov %%ds,%%ebx\n\t"\
    "movw %%ax,%%ds \n\t"\
    :"=b"(saver)\
    :"a"(seg)\
    :\
    );\
    }
#define LEAVE_DS(seg,saver) ({\
    if(seg!=Util::SEG_CURRENT){\
    __asm__ __volatile__(\
        "mov %%ax,%%ds \n\t"\
        :\
        :"a"(saver)\
        :);\
        }})
#define ENTER_ES(seg,saver)  \
    int saver;\
    ({\
    __asm__ __volatile__(\
    "mov %%es,%%ax \n\t"\
    :"=a"(saver)\
    :\
    :);\
    if(seg==Util::SEG_CURRENT){\
        __asm__(\
        "push %ds \n\t"\
        "pop %es \n\t"\
        );\
    }else{\
        __asm__ __volatile__(\
        "movw %%ax,%%es \n\t"::"a"(seg):\
        );\
    }\
})
#define LEAVE_ES(seg,saver) ({__asm__ __volatile__("mov %%ax,%%es \n\t"::"a"(saver):);})

//=============延时
#define IO_BLOCK() __asm__(\
    "nop \n\t"\
    "nop \n\t"\
    "nop \n\t"\
    "nop \n\t"\
    );


//=============仅32位===========
#ifdef CODE32

#endif
//=============仅16位=============
#ifdef CODE16

#endif


#endif
