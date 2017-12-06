

#include <PMLoader.h>
#include <libx2.h>
#include <Descriptor.h>
#include <IOProgramer.h> //for IO_HDD
#include <def.h>

#include <macros/all.h>

#ifdef CODE16
__asm__(".code16gcc \n\t");
#elif defined(CODE32)
__asm__(".code32 \n\t");
#endif


//#define CODE16
#if defined(CODE16)

void realModeTest() //this is placed in .test_section,which is placed at 0x7c0:0x400
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
//    int readBase=PMLoader::TEMP_SEG*16;
//    Util::memcopy(PMLoader::TEMP_SEG,512,PMLoader::TEMP_SEG,0,512);//将第一个扇区清空
//    if(Util::readSectors(PMLoader::TEMP_SEG,0,0x80,0,1))//at lower is ok
//    {
//        Util::printStr("Load Tested.\n");
//    }
//    SegmentDescriptor sd1((char*)readBase,1024);
//    char saver[8];
//    sd1.writeToMemory(Util::SEG_CURRENT,saver);
//    SegmentDescriptor sd2;
//    SegmentDescriptor::fromMemory(&sd2,Util::SEG_CURRENT,saver);
//    char saver2[8];
//    sd2.writeToMemory(Util::SEG_CURRENT,saver2);
//    if(sd1.equals(sd2))
//    {
//        Util::printStr("SegmentDescriptor Right!!!\n");
//    }
    Util::printStr("Util The End.\n");
//    Util::jmpDie();

    //===========Util Test End============

//    Util::jmpDie();
    //使用PMLoader的主过程加载
    //加载配置在编译期已经配置好
    PMLoader::mainProcess();

}

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

// 注意：此函数依赖堆栈框架，所以请不要将其作为宏实现
//	一旦作为宏，堆栈的假设就不成立，即len的位置不在address之前，就错误
void PMLoader::setidtr(int len,int address)
{
	// NOTE 当使用宏实现时，不能依赖于栈参数
	// EFF 探讨是否可以不用复制两个字节
    __asm__ __volatile__(
        "movw 4+4*1(%%ebp),%%ax \n\t" //len参数前两字节
        "movw %%ax,4+4*1+2(%%ebp) \n\t" //len参数的高两字节
        "lidt 4+4*1+2(%%ebp) \n\t"
    		:
    		:
			:
    );
	// 按照32位堆栈传递时，内存如下
	// [address] 4字节
	// [len]2字节  [未设置]2字节
	// 这是为了32位对齐
	// 操作时，先将len往高位上复制两个字节，然后载入那个地址的内容
//	    __asm__ __volatile__(
//	    		"lea %[idtr_addr_high],%%eax \n\t"
//	    		"sub  $2,%%eax \n\t"
//	    		"movw %%ss:-2(%%eax), %%bx \n\t"
//	    		"movw %%bx,%%ss:(%%eax) \n\t"
//	    		"lidt %%ss:(%%eax) \n\t"
//	    		:
//	    		:[idtr_addr_high]"m"(address) //address的地址就是idtr_addr的地址+2
//				:"ebx"
//	    );
}
void PMLoader::setgdtr(int len,int address)
{
    __asm__ __volatile__(
        "movw 4+4*1(%%ebp),%%ax \n\t"
        "movw %%ax,4+4*1+2(%%ebp) \n\t"
        "lgdt 4+4*1+2(%%ebp) \n\t"
    		:
    		:
			:
    );
//	// 参见setidtr
//    __asm__ __volatile__(
//    		"lea %[ldtr_addr_high],%%eax \n\t"
//    		"sub  $2,%%eax \n\t"
//    		"movw %%ss:-2(%%eax), %%bx \n\t"
//    		"movw %%bx,%%ss:(%%eax) \n\t"
//    		"lidt %%ss:(%%eax) \n\t"
//    		:
//    		:[ldtr_addr_high]"m"(address) //address的地址就是idtr_addr的地址+2
//			:"ebx"
//    );
}
void PMLoader::enterProtected()
{
    __asm__ __volatile__(
    "mov %%cr0,%%eax \n\t" //100b
    "or $0x1,%%eax \n\t"
    "mov %%eax,%%cr0 \n\t"
    "pushw %%cx \n\t"  //JMPSEG:CODE_START
    "pushw %%bx \n\t"
    "ljmp *(%%esp) \n\t"
	:
	:"c"(PMLoader::JMPSEG),"b"(CONFIG_PREFIX_SIZE)
	 :
    );
}
// NOTE DEPRECATED  下面的说明是针对老代码的
//UNTESTED
//保护模式代码，前面32个扇区是不用读取的,CODE_START正好指向有效数据的开始，0x4000
//0xa000正好有80个扇区
//由于BIOS有数据，0x500开始处才能写内存数据,0x500只有2.5个扇区
//如果32个扇区
//当然，一般情况下保护模式需要读入的代码都在0x500之后(都要多于2.5个扇区)
//此次能读入的是 32到80之间的扇区，也就是80-32=48个

void PMLoader::adjustProtectedCode()
{
	// NOTE 这是简化设计后的加载代码
	// 硬盘0的某个扇区开始读到0:CONFIG_PREFIX_SIZE处，正好是代码开始
	IO_HDD iohd(0,CONFIG_REAL_SECNUMS,CONFIG_REAL_LOAD_PROTECTED_SECNUM,
			0,CONFIG_PREFIX_SIZE);
	iohd.read();

	// NOTE 下面这些代码全都过时了，因为现在简化了内核的设计，强化了某些限制
//	size_t left;//必须考虑到left必须以4个字节来存放，16位下可能是2个字节。但这无关紧要了。
//
//	//从磁盘的REAL_SECNUMS个扇区处开始读，放到0:CODE_START处，数量待定
//	IO_HDD iohd(0,PMLoader::REAL_SECNUMS,0,0,PMLoader::CODE_START);
//
//
//	size_t alreadyReadSize = PMLoader::CODE_START;
//	size_t wholeNumber = PMLoader::PROTECTED_SECNUMS + PMLoader::PROCESS_SECNUMS;
//	size_t wholeSize= wholeNumber * PMLoader::SECSIZE;
//	size_t mostCanReadSizeThisTime = PMLoader::TEMP_SEG*16 - alreadyReadSize;
//
//
//	left=(wholeSize - mostCanReadSizeThisTime)/PMLoader::SECSIZE;
//	if(left>0)
//	{
////		Util::printStr("Kernel code size exceeds reserved size,the extra sectors will be read after entering protected mode\n");
//	}else{
//		left=0;//enough
//	}
//
//	/*need to set the left sectors unread to FREE_HEAP_START*/
//    if(PMLoader::CODE_START < PMLoader::SAFE_SEG*16) //may overlap the BIOS data or programs
//    {
//    	Util::printStr("Kernel reserved code size too small,make it larger than PMLoader::SAFE_SEG:0\n");
//    	Util::printStr("Kernel shutdown \n");
//    	Util::jmpDie();
//
////    	Util::printStr("Kernel code start at lower than BIOS data segment\n");
//        left += (PMLoader::SAFE_SEG*16 + PMLoader::PROTECTED_SECNUMS*PMLoader::SECSIZE - PMLoader::TEMP_SEG*16)/PMLoader::SECSIZE;
////	    Util::readSectors(PMLoader::SAFE_SEG,0,PMLoader::DRIVER,PMLoader::REAL_SECNUMS,PMLoader::PROTECTED_SECNUMS - left);
//        iohd.setDstSeg(PMLoader::SAFE_SEG);
//        iohd.setDstOff(0);
//        iohd.setSecNumber(PMLoader::PROTECTED_SECNUMS - left);
//        iohd.read();
//	    Util::memcopy(PMLoader::SAFE_SEG,0,0,PMLoader::CODE_START,(PMLoader::PROTECTED_SECNUMS -left) * PMLoader::SECSIZE);
//
//    }else{
////    	char buf[10];
////    	Util::digitToStr(buf,10,left);
////    	Util::printStr("left is :");Util::printStr(buf);Util::printStr("\n");
////        Util::readSectors(0,PMLoader::CODE_START,PMLoader::DRIVER,PMLoader::REAL_SECNUMS,PMLoader::PROTECTED_SECNUMS - left);
//    	iohd.setSecNumber(wholeNumber - left);
//    	iohd.read();
//    }
//
//    Util::printStr("leaving adjust\n");
//    Util::setl(0, PMLoader::FREE_HEAP_START,left);
}
void PMLoader::mainProcess() //仅16位
{
    //===========PMLoader Start==========
    //1.读取指定起始扇区、指定数目的扇区到指定的段、偏移
	//只需要读取 CONFIG_REAL_LOAD_PROTECTED_SECNUM 个扇区就可以，并且保证不会超过限制
    PMLoader::adjustProtectedCode();
    
    //1.5  将栈区结束到prefixsize的地方初始化为0
    //  现在不再需要中断
    Util::insertMark(0x191191);
    short *p=(short*)CONFIG_INIT_STACK_SIZE;
    short *prefixEnd=(short*)(CONFIG_PREFIX_SIZE >= 0x7c00?0x7c00:CONFIG_PREFIX_SIZE); //一定不要超过当前起始处
    int temp;
    Util::enterDs(0x0, temp); //强制使ds为0
    while(p!=prefixEnd)
    	*p++=0;
    Util::leaveDs(0x0, temp);


    //2.初始化GDT表  需要知道具体的GDT，IDE表的绝对位置
    SegmentDescriptor nullptrSeg,
                        loaderSegCode(0,CONFIG_KERNEL_CODE_SIZE - 1,SegmentDescriptor::G_1B,SegmentDescriptor::TYPE_U_CODE_NONCONFORMING,0),
                        loaderSegData(0,(CONFIG_KERNEL_CODE_SIZE + CONFIG_KERNEL_FREE_MEM_SIZE-1)/SegmentDescriptor::G_4KB_SCALE,SegmentDescriptor::G_4KB,SegmentDescriptor::TYPE_U_DATA,0),
                        loaderSegStack(0,CONFIG_INIT_STACK_SIZE - 1,SegmentDescriptor::G_1B,SegmentDescriptor::TYPE_U_STACK,0),
                        videoSeg((char*)0xb8000,
                        		25*80*2-1,
								SegmentDescriptor::G_1B,
								SegmentDescriptor::TYPE_U_DATA,0),
						processSeg((char*)(CONFIG_KERNEL_CODE_SIZE  + CONFIG_KERNEL_FREE_MEM_SIZE),
								(CONFIG_PROCESS_MEM_SIZE-1)/SegmentDescriptor::G_4KB_SCALE,
								SegmentDescriptor::G_4KB,
								SegmentDescriptor::TYPE_U_DATA,0);
    nullptrSeg={0};//not really all zeros.

    int gdtAddr = CONFIG_INIT_STACK_SIZE%8==0?CONFIG_INIT_STACK_SIZE:(CONFIG_INIT_STACK_SIZE/8*8 + 8);//对其到8字节
    int idtAddr = gdtAddr + 8*CONFIG_GDT_ITEM_NUM;
 
//    nullptrSeg.writeToMemory(0,(char*)PMLoader::GDT_START);
//    videoSeg.writeToMemory(0,(char*)PMLoader::GDT_START+1*8);
//    loaderSegCode.writeToMemory(0,(char*)PMLoader::GDT_START+2*8);
//    loaderSegData.writeToMemory(0,(char*)PMLoader::GDT_START+3*8);
//    loaderSegStack.writeToMemory(0,(char*)PMLoader::GDT_START+4*8);//B set 4GB
//    processSeg.writeToMemory(0,(char*)PMLoader::GDT_START + 5*8); // index=5

        nullptrSeg.writeToMemory(0,(char*)gdtAddr);
        videoSeg.writeToMemory(0,(char*)gdtAddr+1*8);
        loaderSegCode.writeToMemory(0,(char*)gdtAddr+2*8);
        loaderSegData.writeToMemory(0,(char*)gdtAddr+3*8);
        loaderSegStack.writeToMemory(0,(char*)gdtAddr+4*8);//B set 4GB
        processSeg.writeToMemory(0,(char*)gdtAddr + 5*8); // index=5



    //3.启用A20
    Util::printStr("enable a20...\n");
   PMLoader::enableA20();
    //===BUG with int 0x13
    
    //4.设置idt，gdt表
    PMLoader::setidtr(CONFIG_IDT_ITEM_NUM*8 - 1,idtAddr);
    //===BUG
    PMLoader::setgdtr(CONFIG_GDT_ITEM_NUM*8 - 1,gdtAddr);
    //===BUG
    
    //5.设置cr0，进入保护模式
    Util::printStr("changing cr0\n");
   PMLoader::enterProtected();
    
    //===========PMLoader End==============
}

#endif //CODE16
