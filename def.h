
#ifndef __DEF__
#define __DEF__

//默认检查所有的宏定义
//定义 NO_CHECK_MACROS 来取消此检查
#ifndef NO_CHECK_MACROS
#warning "Checking macros."
#if ! ( (defined IDT_START) &&\
        (defined IDT_SIZE) &&\
        (defined GDT_START) &&\
        (defined GDT_SIZE)\
      )
      #warning "Missing MACROS:IDT or GDT related."
      #error
#endif
#if ! ( (defined CODE16) || (defined CODE32))
    #warning "None of CODE16 or CODE32 defined."
    #error

#endif

#ifdef CODE16
#if ! ( (defined DRIVER) &&\
        (defined SECSTART) &&\
        (defined SECNUM) &&\
        (defined CODESEG) &&\
        (defined CODEOFF) &&\
        (defined SEG_CURRENT)\
      )
    #warning "Missing MACROS:Protected Loader related."
    #error
    
#endif
#endif 

#ifdef CODE32
#if ! ((defined TSS_MIN_SIZE) &&\
        (defined TSS_AREA_START) &&\
        (defined TSS_AREA_SIZE))
    #warning "Missing MACROS:TSS related."
    #error
#endif

#endif

#endif //check macros

//====字符串宏
#define __STR(x) #x
#define STR(x) __STR(x)

//extern inline 宏
//除非特别短的函数 或者必须作为宏来实现的函数
//否则这样做会增加代码长度
#define AS_MACRO inline __attribute__((always_inline))

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
#define CLI()   __asm__("cli \n\t")
#define STI()   __asm__("sti \n\t")




//===================设置ds,es的上下文环境====================
/**
*涉及堆栈平衡，不可能由非内联函数函数来实现。
*/
#define ENTER_DS(seg,saver) \
    int saver;\
    if(seg!=SEG_CURRENT){\
    __asm__ __volatile__(\
    "mov %%ds,%%ebx\n\t"\
    "movw %%ax,%%ds \n\t"\
    :"=b"(saver)\
    :"a"(seg)\
    :\
    );\
    }
#define LEAVE_DS(seg,saver) ({\
    if(seg!=SEG_CURRENT){\
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
    if(seg==SEG_CURRENT){\
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