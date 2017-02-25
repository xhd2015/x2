#ifdef CODE16
__asm__(".code16gcc \n\t");
#elif defined(CODE32)
__asm__(".code32 \n\t");
#endif

#include "PMLoader.h"
#include "libx2.h"
#include "Descriptor.h"

const int PMLoader::SAFE_SEG=0x100;
const int PMLoader::SECSIZE=512;
const int PMLoader::STACK_START=0,
           PMLoader::STACK_SIZE=PMLoader::SECSIZE*4,
           PMLoader::IDT_START=PMLoader::STACK_START+PMLoader::STACK_SIZE,
           PMLoader::IDT_SIZE=PMLoader::SECSIZE*1,
           PMLoader::GDT_START=PMLoader::IDT_START+PMLoader::IDT_SIZE,
           PMLoader::GDT_SIZE=PMLoader::SECSIZE*2,
           PMLoader::TSS_AREA_SIZE=PMLoader::SECSIZE*2,
           PMLoader::TSS_AREA_START=PMLoader::GDT_START+PMLoader::GDT_SIZE,
           PMLoader::TSS_MIN_SIZE=104,
           PMLoader::FREE_HEAP_SIZE=PMLoader::SECSIZE*5,
           PMLoader::FREE_HEAP_START=PMLoader::TSS_AREA_START+PMLoader::TSS_AREA_SIZE,
           PMLoader::CODE_START=PMLoader::FREE_HEAP_START+PMLoader::FREE_HEAP_SIZE,
           PMLoader::CODE_SEG = 0,
           PMLoader::CODE_LIMIT = 0xfffff;
const int   PMLoader::JMPSEG = 0x10,
            PMLoader::DRIVER=0,
            PMLoader::REAL_SECNUMS=16,
            PMLoader::PROTECTED_SECNUMS=60,
            PMLoader::TEMP_SEG=0xa00;
#ifdef CODE16
PMLoader::PMLoader()
{
    
}

PMLoader::~PMLoader()
{

}

/**
*还有其他启用A20的方式（基于键盘），但是那些都是old-A20,而这里采用的是Fast A20.
*如果想要reboot，也是直接从该端口写入0(保证位0是0)，位0被称作INIT_NOW
*/
void PMLoader::enableA20()
{
    __asm__(
       "inb $0x92,%al \n\t" //读取0x92端口，置位1为1，重新写入
       "orb $0b00000010,%al \n\t"
       "outb %al,$0x92 \n\t"
    );
}
void PMLoader::setidtr(short len,int address)
{

    __asm__(
        "movw 4+4*1(%ebp),%ax \n\t"
        "movw %ax,4+4*1+2(%ebp) \n\t"
        "lidt 4+4*1+2(%ebp) \n\t"
    );
}
void PMLoader::setgdtr(short len,int address)
{
    __asm__(
        "movw 4+4*1(%ebp),%ax \n\t"
        "movw %ax,4+4*1+2(%ebp) \n\t"
        "lgdt 4+4*1+2(%ebp) \n\t"
    );
}
void PMLoader::enterProtected()
{
    __asm__(
    "mov %cr0,%eax \n\t" //100b
    "or $0x1,%eax \n\t"
    "mov %eax,%cr0 \n\t"
    "movw __ZN8PMLoader6JMPSEGE,%ax \n\t"
    "movw __ZN8PMLoader10CODE_STARTE,%bx \n\t"
    "pushw %ax \n\t"
    "pushw %bx \n\t"
    "ljmp *(%esp) \n\t"
    );
}
void PMLoader::adjustProtectedCode()
{
    if(PMLoader::CODE_SEG*16+PMLoader::CODE_START < PMLoader::SAFE_SEG*16) //maybe wrong
    {
        if(PMLoader::SAFE_SEG*16 + PMLoader::PROTECTED_SECNUMS*PMLoader::SECSIZE >= PMLoader::TEMP_SEG*16)//this will overlap the current code,you should stop this behavior and go back to trim the size of your code
        {
            __asm__("#Please go back to reduce the size of your code \n\t");
        }else{
          Util::readSectors(PMLoader::SAFE_SEG,0,PMLoader::DRIVER,PMLoader::REAL_SECNUMS,PMLoader::PROTECTED_SECNUMS);
          Util::memcopy(PMLoader::SAFE_SEG,0,PMLoader::CODE_SEG,PMLoader::CODE_START,PMLoader::PROTECTED_SECNUMS * PMLoader::SECSIZE);
        }

    }else{
        Util::readSectors(PMLoader::CODE_SEG,PMLoader::CODE_START,PMLoader::DRIVER,PMLoader::REAL_SECNUMS,PMLoader::PROTECTED_SECNUMS);
    }

}
void PMLoader::mainProcess() //仅16位
{
    //===========PMLoader Start==========
    //1.读取指定起始扇区、指定数目的扇区到指定的段、偏移
    PMLoader::adjustProtectedCode();
    
    SegmentDescriptor nullSeg,
                        loaderSegCode(0,PMLoader::CODE_LIMIT,SegmentDescriptor::TYPE_U_CODE_NONCONFORMING,0),
                        loaderSegData(0,PMLoader::CODE_LIMIT,SegmentDescriptor::TYPE_U_DATA,0),
                        loaderSegStack(0,PMLoader::STACK_SIZE,SegmentDescriptor::TYPE_U_STACK,0),
                        videoSeg(0xb8000,25*80*2,SegmentDescriptor::TYPE_U_DATA,0);
    nullSeg={0};//not really all zeros.
 
    //2.初始化GDT表
    nullSeg.writeToMemory(0,PMLoader::GDT_START);      
    videoSeg.writeToMemory(0,PMLoader::GDT_START+1*8);
    loaderSegCode.writeToMemory(0,PMLoader::GDT_START+2*8); 
    loaderSegData.writeToMemory(0,PMLoader::GDT_START+3*8);
    loaderSegStack.writeToMemory(0,PMLoader::GDT_START+4*8);//B set 4GB 

    //3.启用A20
   PMLoader::enableA20();
    //===BUG with int 0x13
    
    //4.设置idt，gdt表
    PMLoader::setidtr(PMLoader::IDT_SIZE-1,PMLoader::IDT_START);
    //===BUG
    PMLoader::setgdtr(PMLoader::GDT_SIZE-1,PMLoader::GDT_START);
    //===BUG
    
    //5.设置cr0，进入保护模式
   PMLoader::enterProtected();
    
    //===========PMLoader End==============
}

#endif //CODE16
