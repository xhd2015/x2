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
//开始引导
__asm__(
"ljmp $STARTSEG,$HERE \n\t"
"HERE: \n\t"
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
        "READLEN = 20 \n\t"
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
    if(Util::readSectors(0x7c0,0,0,0,0,1,1))//重新读取
    {
        Util::printStr("Load Tested.\n");
    }
    SegmentDescriptor sd1(0x7c00,1024);
    char saver[8];
    Util::insertMark(0x1233);
    sd1.writeToMemory(0x10000,saver);
    SegmentDescriptor sd2;
    Util::insertMark(0x1232);
    SegmentDescriptor::fromMemory(&sd2,0x10000,saver);
    char saver2[8];
    sd2.writeToMemory(0x10000,saver2);
    if(sd1.equals(sd2))
    {
        Util::printStr("SegmentDescriptor Right!!!\n");
    }
    Util::printStr("Util The End.\n");
    //===========Util Test End============
    
    //===========PMLoader Start============
    //定义宏 Driver Head Cylinder SecStart SecNum CodeSeg CodeOff
    PMLoader pmldr(Driver,Head,Cylinder,SecStart,SecNum,CodeSeg,CodeOff);
    pmldr.enableA20();
    pmldr.setidtr(50*8,0x400);
    pmldr.setgdtr(100*8,0x400+50*8);
    SegmentDescriptor nullSeg,
                        loaderSegCode(0x7c00,512*20,SegmentDescriptor::TYPE_U_CODE_CONFORMING,0),
                        loaderSegData(0x7c00,512*20,SegmentDescriptor::TYPE_U_DATA,0),
                        loaderSegStack(0x7c00,512*20,SegmentDescriptor::TYPE_U_STACK,0),
                        videoSeg(0xb8000,25*80*2,SegmentDescriptor::TYPE_U_DATA,0);
    Util::insertMark(0x1234);
    nullSeg={0};//not really all zeros.
    nullSeg.writeToMemory(0,0x400+50*8);
    videoSeg.writeToMemory(0,0x400+50*8+1*8);
    loaderSegCode.writeToMemory(0,0x400+50*8+2*8); 
    loaderSegData.writeToMemory(0,0x400+50*8+3*8);
    loaderSegStack.writeToMemory(0,0x400+50*8+4*8);
    pmldr.adjustProtectedCode();
    Util::printStr("Entering Protected Mode.");
    pmldr.enterProtected();
    
    //Util::videoSelector=0b1000; //第1项就是视频缓冲区
    //===========PMLoader End==============
}



__asm__(
".section .last_section \n\t"
".org 2 \n\t"
".word 0xaa55 \n\t"
);

#endif