#ifdef CODE16
__asm__(
".text \n\t"
".code16gcc \n\t"
"STARTSEG = 0x7c0 \n\t"
"STACKSIZE = 512*2"
);
#include "libx2.h"
#include "PMLoader.h"
#include "Descriptor.h"
#include "def.h"
//开始引导
__asm__(
"ljmp $STARTSEG,$HERE \n\t"
"HERE: \n\t"
"cli \n\t"
"mov $STARTSEG,%ax \n\t"
"mov %ax,%ds \n\t"
"mov %ax,%ss \n\t"
"mov %ax,%es \n\t"
"mov $STACKSIZE,%sp \n\t"
"#mov %ax,%sp \n\t"
"call _readLaterSectors\n\t"
"call __Z8theEntryv \n\t" //不能使用main，gcc对main有特殊处理
"DIE:\n\t"
"jmp DIE \n\t"
);

//突破1扇区的限制先
extern "C" void readLaterSectors()
{
    __asm__(
        "READLEN =  16-2\n\t"
        "push %es\n\t"
        "mov $STARTSEG,%ax \n\t"
        "mov %ax,%es\n\t"
        "mov $STACKSIZE,%bx\n\t" //cx=start-sector -->es:bx+READLEN
        "xor %dx,%dx \n\t"
        "mov $0x0003,%cx \n\t"
        "mov $0x200+READLEN,%ax \n\t"
        "int $0x13 \n\t"
        "pop %es \n\t"
    );
}

__attribute__((section(".test_section"))) int theEntry() //this is placed in .test_section,which is placed at 0x7c0:0x400
{
    //===========Class Test Start============
//    Test t;//c++的默认构造函数不能加括号，否则可能被看成是函数声明
    Util::printStr("Hello World!");//测试默认参数
    //堆栈不足以支持这么多函数，因此需要适时扩张堆栈
    
    //测试类的构造、析构、成员函数
    Util t;
    t.test();
    //===========Class Test End============
    
    //===========Util Test Start============
    Util::memcopy(0x7c0,512,0x7c0,0,512);//将第一个扇区清空
    Util::insertMark(0x555);
    if(Util::readSectors(0x7c0,0,0,0,1))
    {
        Util::printStr("Load Tested.\n");
    }
    SegmentDescriptor sd1(0x7c00,1024);
    char saver[8];
    sd1.writeToMemory(0x10000,saver);
    SegmentDescriptor sd2;
    SegmentDescriptor::fromMemory(&sd2,0x10000,saver);
    char saver2[8];
    sd2.writeToMemory(0x10000,saver2);
    if(sd1.equals(sd2))
    {
        Util::printStr("SegmentDescriptor Right!!!\n");
    }
    Util::printStr("Util The End.\n");
    //===========Util Test End============
    
    PMLoader pmldr(DRIVER,SECSTART,SECNUM,CODESEG,CODEOFF);
    //多容纳N(比如20)个扇区
    pmldr.mainProcess(IDT_START,IDT_SIZE,GDT_START,GDT_SIZE,CODESEG << 4,0xfffff,512*4);

}

__asm__(
".section .last_section \n\t"
".org 2 \n\t"
".word 0xaa55 \n\t"
);

#endif