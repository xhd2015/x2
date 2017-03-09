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

extern "C" {
    void protectedEntryHolder();
    void afterCPL3();    
    void forTss1();
}
__asm__(
".text \n\t"
"movw $0b11000,%ax \n\t" //ds选择子，
"movw %ax,%ds \n\t"
"mov  %ax,%es \n\t"
"mov %ax,%gs \n\t"
"mov %ax,%fs \n\t"
"mov $0b100000,%ax \n\t"
"movw %ax,%ss \n\t" //ss选择子
"mov  $512*4,%esp \n\t" 
"call _protectedEntryHolder \n\t"
"DIE: \n\t"
"jmp DIE \n\t"
);

void protectedEntryHolder() //0x2016
{      
    //=====================清除屏幕，初始化调试信息打印器区域
    Util::clr();
    Printer stdp(3,30,6,20,Util::MODE_COMMON);//系统的标准打印器
    stdp.clr();
    stdp.putsz("Entered Protected Mode.\n");
    //===================从这里插入test的hook
    stdp.putsz("Running Test.\n");
    Test test;
    test.run();
    
    
    //====================tss0 & 描述符
    TSS tss0;//
    
    *(short*)tss0.SS0 = Util::makeSel(4);
    *(int*)tss0.ESP0 = 3*512 - 4;
    tss0.writeToMemory(Util::SEG_CURRENT,PMLoader::TSS_AREA_START);
    //SS0:ESP0之后会被int用到，发生到高特权级的中断会切换堆栈
    
    stdp.putsz("tss0 written\n");
    SegmentDescriptor tss0_descr(PMLoader::TSS_AREA_START,PMLoader::TSS_MIN_SIZE-1,SegmentDescriptor::TYPE_S_TSS_32_AVL,0,0,0);
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
    p1.sendOCW1(0,0xfc);//屏蔽一些中断
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
    TSS tss1;
    *(short*)tss1.CS=Util::makeSel(6,0x3);
    *(int*)tss1.EIP=forTss1;
    *(short*)tss1.SS = Util::makeSel(8,0x3);
    *(int*)tss1.ESP=512*2-4;
    *(short*)tss1.SS0 = Util::makeSel(4);
    *(int*)tss1.ESP0 = 512 - 4;
    *(int*)tss1.EFLAGS =0x202 ;//| 0x100;
    *(short*)tss1.DS = 0x3b;
    tss1.writeToMemory(Util::SEG_CURRENT,PMLoader::TSS_AREA_START+PMLoader::TSS_MIN_SIZE);
    SegmentDescriptor tss1_sel(PMLoader::TSS_AREA_START+PMLoader::TSS_MIN_SIZE,PMLoader::TSS_MIN_SIZE-1,SegmentDescriptor::TYPE_S_TSS_32_AVL,0,0,0);
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
