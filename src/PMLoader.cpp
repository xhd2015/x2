

#include <PMLoader.h>
#include <libx2.h>
#include <Descriptor.h>
#include <IOProgramer.h> //for IO_HDD
#include <def.h>

#include <macros/IOProgramer_macros.h>

#ifdef CODE16
__asm__(".code16gcc \n\t");
#elif defined(CODE32)
__asm__(".code32 \n\t");
#endif


//#define CODE16
#if defined(CODE16)
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
    __asm__ __volatile__(
    "mov %%cr0,%%eax \n\t" //100b
    "or $0x1,%%eax \n\t"
    "mov %%eax,%%cr0 \n\t"
//    "movw __ZN8PMLoader6JMPSEGE,%cx \n\t"
//    "movw __ZN8PMLoader10CODE_STARTE,%bx \n\t"
    "pushw %%cx \n\t"  //JMPSEG:CODE_START
    "pushw %%bx \n\t"
    "ljmp *(%%esp) \n\t"
	:
	:"c"(PMLoader::JMPSEG),"b"(PMLoader::JMPOFF)
	 :
    );
}
//UNTESTED
//保护模式代码，前面32个扇区是不用读取的,CODE_START正好指向有效数据的开始，0x4000
//0xa000正好有80个扇区
//由于BIOS有数据，0x500开始处才能写内存数据,0x500只有2.5个扇区
//如果32个扇区
//当然，一般情况下保护模式需要读入的代码都在0x500之后(都要多于2.5个扇区)
//此次能读入的是 32到80之间的扇区，也就是80-32=48个
void PMLoader::adjustProtectedCode()
{
	size_t left;//必须考虑到left必须以4个字节来存放，16位下可能是2个字节。但这无关紧要了。

	//从磁盘的REAL_SECNUMS个扇区处开始读，放到0:CODE_START处，数量待定
	IO_HDD iohd(0,PMLoader::REAL_SECNUMS,0,0,PMLoader::CODE_START);


	size_t alreadyReadSize = PMLoader::CODE_START;
	size_t wholeNumber = PMLoader::PROTECTED_SECNUMS + PMLoader::PROCESS_SECNUMS;
	size_t wholeSize= wholeNumber * PMLoader::SECSIZE;
	size_t mostCanReadSizeThisTime = PMLoader::TEMP_SEG*16 - alreadyReadSize;


	left=(wholeSize - mostCanReadSizeThisTime)/PMLoader::SECSIZE;
	if(left>0)
	{
//		Util::printStr("Kernel code size exceeds reserved size,the extra sectors will be read after entering protected mode\n");
	}else{
		left=0;//enough
	}

	/*need to set the left sectors unread to FREE_HEAP_START*/
    if(PMLoader::CODE_START < PMLoader::SAFE_SEG*16) //may overlap the BIOS data or programs
    {
    	Util::printStr("Kernel reserved code size too small,make it larger than PMLoader::SAFE_SEG:0\n");
    	Util::printStr("Kernel shutdown \n");
    	Util::jmpDie();

//    	Util::printStr("Kernel code start at lower than BIOS data segment\n");
        left += (PMLoader::SAFE_SEG*16 + PMLoader::PROTECTED_SECNUMS*PMLoader::SECSIZE - PMLoader::TEMP_SEG*16)/PMLoader::SECSIZE;
//	    Util::readSectors(PMLoader::SAFE_SEG,0,PMLoader::DRIVER,PMLoader::REAL_SECNUMS,PMLoader::PROTECTED_SECNUMS - left);
        iohd.setDstSeg(PMLoader::SAFE_SEG);
        iohd.setDstOff(0);
        iohd.setSecNumber(PMLoader::PROTECTED_SECNUMS - left);
        iohd.read();
	    Util::memcopy(PMLoader::SAFE_SEG,0,0,PMLoader::CODE_START,(PMLoader::PROTECTED_SECNUMS -left) * PMLoader::SECSIZE);

    }else{
//    	char buf[10];
//    	Util::digitToStr(buf,10,left);
//    	Util::printStr("left is :");Util::printStr(buf);Util::printStr("\n");
//        Util::readSectors(0,PMLoader::CODE_START,PMLoader::DRIVER,PMLoader::REAL_SECNUMS,PMLoader::PROTECTED_SECNUMS - left);
    	iohd.setSecNumber(wholeNumber - left);
    	iohd.read();
    }

    Util::printStr("leaving adjust\n");
    Util::setl(0, PMLoader::FREE_HEAP_START,left);
}
void PMLoader::mainProcess() //仅16位
{
    //===========PMLoader Start==========
    //1.读取指定起始扇区、指定数目的扇区到指定的段、偏移
    PMLoader::adjustProtectedCode();
    
    SegmentDescriptor nullSeg,
                        loaderSegCode(0,PMLoader::CODE_LIMIT,SegmentDescriptor::G_1B,SegmentDescriptor::TYPE_U_CODE_NONCONFORMING,0),
                        loaderSegData(0,PMLoader::DATA_LIMIT/SegmentDescriptor::G_4KB_SCALE,SegmentDescriptor::G_4KB,SegmentDescriptor::TYPE_U_DATA,0),
                        loaderSegStack(0,PMLoader::STACK_LIMIT,SegmentDescriptor::G_1B,SegmentDescriptor::TYPE_U_STACK,0),
                        videoSeg((char*)0xb8000,
                        		25*80*2-1,
								SegmentDescriptor::G_1B,
								SegmentDescriptor::TYPE_U_DATA,0),
						processSeg((char*)PMLoader::PROCESS_MM_START,
								(PMLoader::PROCESS_MM_SIZE-1)/SegmentDescriptor::G_4KB_SCALE,
								SegmentDescriptor::G_4KB,
								SegmentDescriptor::TYPE_U_DATA,0);
    nullSeg={0};//not really all zeros.
 
    //2.初始化GDT表
    nullSeg.writeToMemory(0,(char*)PMLoader::GDT_START);
    videoSeg.writeToMemory(0,(char*)PMLoader::GDT_START+1*8);
    loaderSegCode.writeToMemory(0,(char*)PMLoader::GDT_START+2*8);
    loaderSegData.writeToMemory(0,(char*)PMLoader::GDT_START+3*8);
    loaderSegStack.writeToMemory(0,(char*)PMLoader::GDT_START+4*8);//B set 4GB
    processSeg.writeToMemory(0,(char*)PMLoader::GDT_START + 5*8); // index=5

    //3.启用A20
    Util::printStr("enable a20...\n");
   PMLoader::enableA20();
    //===BUG with int 0x13
    
    //4.设置idt，gdt表
    PMLoader::setidtr(PMLoader::IDT_SIZE-1,PMLoader::IDT_START);
    //===BUG
    PMLoader::setgdtr(PMLoader::GDT_SIZE-1,PMLoader::GDT_START);
    //===BUG
    
    //5.设置cr0，进入保护模式
    Util::printStr("changing cr0\n");
   PMLoader::enterProtected();
    
    //===========PMLoader End==============
}

#endif //CODE16
