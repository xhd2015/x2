
#ifndef __config_h__
#define __config_h__

extern int STACK_START,
           STACK_SIZE,
           IDT_START,
           IDT_SIZE,
           GDT_START,
           GDT_SIZE,
           TSS_AREA_SIZE,
           TSS_AREA_START,
           TSS_MIN_SIZE,
           FREE_HEAP_SIZE,
           FREE_HEAP_START,
           CODE_START
           ;
           //从这个版本开始，空的扇区不再占用空间，但是偏移将继续保持正确
//预留前面的个扇区
__asm__(    
".global _STACK_START,_STACK_SIZE,_IDT_START,_IDT_SIZE,_GDT_START,_GDT_SIZE,"
"        _TSS_AREA_SIZE,_TSS_AREA_START,_TSS_MIN_SIZE,_FREE_HEAP_SIZE,_FREE_HEAP_START ,_CODE_START\n\t"
"_STACK_START = 0 \n\t"
"_STACK_SIZE = 512*4 \n\t"

"_IDT_START = _STACK_START + _STACK_SIZE \n\t"
"_IDT_SIZE = 512 \n\t"

"_GDT_START = _IDT_START + _IDT_SIZE \n\t"
"_GDT_SIZE = 512*2 \n\t"

"_TSS_MIN_SIZE = 104 \n\t"
"_TSS_AREA_START = _GDT_START + _GDT_SIZE\n\t"
"_TSS_AREA_SIZE = 512*2 \n\t"


"_FREE_HEAP_START = _TSS_AREA_START + _TSS_AREA_SIZE \n\t"
"_FREE_HEAP_SIZE = 512*5\n\t"

"_CODE_START = _FREE_HEAP_START + _FREE_HEAP_SIZE \n\t"

);


#ifdef CODE16

extern int JMPSEG,
            JMPOFF,
            DRIVER,
            REAL_SECNUMS,
            PROTECTED_SECNUMS,
            TEMP_SEG;
__asm__(
".global _JMPSEG,_JMPOFF,_DRIVER,_REAL_SECNUMS,_PROTECTED_SECNUMS,_TEMP_SEG \n\t"
"_JMPSEG = 0x10 \n\t"
"_JMPOFF = _CODE_START \n\t"
"_DRIVER = 0 \n\t"
"_REAL_SECNUMS = 16 \n\t"
"_PROTECTED_SECNUMS = 60 \n\t"
"_TEMP_SEG = 0xa00 \n\t"
);
#endif //CODE16

#endif  //header