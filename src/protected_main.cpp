#ifdef CODE32 //we are now at Protected Mode
__asm__(".code32 \n\t");




#include <libx2.h>
#include <Descriptor.h>
#include <TSS.h>
#include <interrupts.h>
#include <def.h>
#include <IOProgramer.h>
#include <test.h>
#include <PMLoader.h>
#include <Kernel.h>

extern "C" {
	void extraVboxTest();
    void protectedEntryHolder();
    void afterCPL3();    
    void forTss1();
}
__asm__(
".text \n\t"
//		"jmp .\n\t"  //vbox ok
"movw $0b11000,%ax \n\t" //ds选择子，
"movw %ax,%ds \n\t"
"mov  %ax,%es \n\t"
"mov %ax,%gs \n\t"
"mov %ax,%fs \n\t"
"mov $0b100000,%ax \n\t"
"movw %ax,%ss \n\t" //ss选择子
"mov  $512*4,%esp \n\t" 
"call _extraVboxTest\n\t"
"call _protectedEntryHolder \n\t"
"DIE: \n\t"
"jmp DIE \n\t"
);

 void extraVboxTest()
{
//	 __asm__(
//	"mov $0x8,%ax \n\t"
//	"mov %ax,%ds\n\t"
//	"movb $120,0\n\t" //print 'x' in the screen,this is OK
//	 );
//	 Util::jmpDie();
}

void protectedEntryHolder()
{      
//	Util::printStr("a function call\n");
//	Util::jmpDie(); //vbox OK
    //=====================清除屏幕，初始化调试信息打印器区域
    Util::clr();
//    Util::jmpDie();  //vbox wrong
    Printer stdp(3,30,15,40,Util::MODE_COMMON);//系统的标准打印器
//    Util::jmpDie(); //vbox wrong
    stdp.clr();
//    Util::jmpDie(); //vbox wrong
    stdp.putsz("Entered Protected Mode.\n");
    //=======================读取剩余的扇区
    stdp.putsz("Reading left sectors...\n");
//    Util::jmpDie(); //vbox wrong
    int nleft=*(int*)PMLoader::FREE_HEAP_START;
    char buf[10];
    Util::digitToStr(buf, arrsizeof(buf), nleft);
    stdp.putsz("Left sector number is :");stdp.putsz(buf);stdp.putsz("\n");
    if(nleft > 0)
    {
    	IO_HDD iohd(0,(unsigned char)(PMLoader::REAL_SECNUMS + PMLoader::PROTECTED_SECNUMS - nleft),(size_t)nleft,Util::SEG_CURRENT,(size_t)PMLoader::TEMP_SEG*16);
    	iohd.read();
    }
    //===================从这里插入test的hook
    stdp.putsz("Running Test.\n");
    Test test;
    test.run();
    
    //==================初始化内核，这里可以明显看到内核的概念：资源管理器的集合
    Kernel *pkernel=(Kernel*)PMLoader::KERNEL_START;
    new (pkernel) Kernel(


    );//初始化一个新的kernel

    Kernel::initTheKernel(pkernel);

    //do some adjustment so that the allocated space will not be corrupted
    Kernel::getTheKernel()->mnew(0,0);

    Kernel::getTheKernel()->createTheIdlePreocess();//or created by the constructor
    						//idle process is useful because when treating the kernel as a process too,we can benefit from the existing
    						//handles.
    Kernel::getTheKernel()->createProcess();//task 1,create a process,but do not run it.
    Kernel::getTheKernel()->createProcess();//task 2




    
    //====================tss0 & 描述符
//    TSS tss0;//
    TSS *ptss=(TSS*)PMLoader::TSS_AREA_START;
    
    ptss[0].SS0 = Util::makeSel(4);
    ptss[0].ESP0 = 3*512 - 4;
//    tss0.writeToMemory(Util::SEG_CURRENT,PMLoader::TSS_AREA_START);
    //SS0:ESP0之后会被int用到，发生到高特权级的中断会切换堆栈
    
    stdp.putsz("tss0 written\n");
    SegmentDescriptor tss0_descr((char*)PMLoader::TSS_AREA_START,PMLoader::TSS_MIN_SIZE-1,SegmentDescriptor::TYPE_S_TSS_32_AVL,0,0,0);
    tss0_descr.writeToMemory(Util::SEG_CURRENT,(char*)PMLoader::GDT_START+5*8);//TSS0描述符所处的位置
    Util::ltr(Util::makeSel(5));// load task register
    stdp.putsz("Had ltr done.\n");
    
    //======== 循环设置所有中断===
    SelectorDescriptor reuse_sel;
    reuse_sel.init(0x10,(int)intDefault,SelectorDescriptor::TYPE_INT,SegmentDescriptor::DPL_3);
    for(int i=0;i!=intLen;i++)//根据已经定义的中断表长度设置中断
    {
        reuse_sel.init(0x10,intAddresses[i],SelectorDescriptor::TYPE_INT,SegmentDescriptor::DPL_3);
        reuse_sel.writeToMemory(Util::SEG_CURRENT,PMLoader::IDT_START+8*i);
    }
    reuse_sel.init(0x10,(int)&int0x20,SelectorDescriptor::TYPE_INT,SegmentDescriptor::DPL_3);//重新设置int0x20
    reuse_sel.writeToMemory(Util::SEG_CURRENT,PMLoader::IDT_START+0x20*8);
    reuse_sel.init(0x10,(int)&int0x21,SelectorDescriptor::TYPE_INT,SegmentDescriptor::DPL_3);//重新设置int0x20
    reuse_sel.writeToMemory(Util::SEG_CURRENT,PMLoader::IDT_START+0x21*8);
    
    Util::insertMark(0x12345);
    CALL_INT_3(0x24,c,Util::SEG_CURRENT,b,"int 0x24 by CPL0.\n",d,Util::MODE_COMMON);
    
    //===========对8259A两片外部芯片接口编程
    IO_8259A p1;
    p1.sendICW1(0,0,0,1);
    p1.sendICW1(1,0,0,1);
    p1.sendICW2(0,0x20);
    p1.sendICW2(1,0x28);
    p1.sendICW3(0,0x4);
    p1.sendICW3(1,0x2);
    p1.sendICW4(0,0,0,0,1);
    p1.sendICW4(1,0,0,0,1); //普通全嵌套，非缓冲，非自动结束，用于80x86
    p1.sendOCW1(0,0xfc);//屏蔽一些中断,允许定时中断，键盘中断
    p1.sendOCW1(1,0xff);
    
    //对8253编程
    IO_8253 p2;//间隔10ms都很难等待
    p2.setTimeMicro(0,1);//设置通道0，间隔：n微秒
    
    //===============设置CPL=3的描述符
    SegmentDescriptor cs3(0,0xfffff,SegmentDescriptor::TYPE_U_CODE_CONFORMING,0);
    SegmentDescriptor ds3(0,0xffff,SegmentDescriptor::TYPE_U_DATA,3);
    SegmentDescriptor ss3(0,4*512,SegmentDescriptor::TYPE_U_STACK,3);
    
    cs3.writeToMemory(Util::SEG_CURRENT,(char*)PMLoader::GDT_START+6*8);
    ds3.writeToMemory(Util::SEG_CURRENT,(char*)PMLoader::GDT_START+7*8);
    ss3.writeToMemory(Util::SEG_CURRENT,(char*)PMLoader::GDT_START+8*8);
    
    
    //=====================一个闲置任务tss1
//    TSS tss1;
    ptss[1].CS=Util::makeSel(6,0x3);
    ptss[1].EIP=(int)forTss1;
    ptss[1].SS = Util::makeSel(8,0x3);
    ptss[1].ESP=512*2-4;
    ptss[1].SS0 = Util::makeSel(4);
    ptss[1].ESP0 = 512 - 4;
    ptss[1].EFLAGS =0x202 ;//| 0x100;
    ptss[1].DS = 0x3b;
//    tss1.writeToMemory(Util::SEG_CURRENT,PMLoader::TSS_AREA_START+PMLoader::TSS_MIN_SIZE);
    SegmentDescriptor tss1_sel((char*)PMLoader::TSS_AREA_START+PMLoader::TSS_MIN_SIZE,PMLoader::TSS_MIN_SIZE-1,SegmentDescriptor::TYPE_S_TSS_32_AVL,0,0,0);
    tss1_sel.writeToMemory(Util::SEG_CURRENT,(char*)PMLoader::GDT_START+9*8);
    
    
    //允许中断
    Util::sti();
    //========================利用iret切换到特权级3，此后此任务运行在特权级3
    stdp.putsz("Changing CPL to 3.\n");
    Util::changeCPL((int)afterCPL3,0x33,Util::getEflags(),4*512-4,0x43);
    
    
}

void afterCPL3() //tss0的CPL=3主要代码
{  
    __asm__(
    "pushw $0x3b \n\t" //数据段ds
    "popw %ds \n\t"
    );
    CALL_INT_3(0x24,c,Util::SEG_CURRENT,b,"int 0x24 by CPL3.\n",d,Util::MODE_COMMON);//int n
    Util::insertMark(0x55678);
    SimpleCharRotator scr(0,40);//一个简单的task
    scr.run();   
}
void forTss1() //tss1的主要代码
{
    SimpleCharRotator scr(0,50,Util::MODE_COMMON|Util::MODE_FL_ON|Util::MODE_BG_BLUE);
    scr.run();
}
#endif
