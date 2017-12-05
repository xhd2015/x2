#ifndef __checkMacros__
#define __checkMacros__
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

#endif