#ifdef CODE32 //we are now at Protected Mode
__asm__(".code32 \n\t");
#endif




#include <Kernel.h>
#include <libx2.h>
#include <Descriptor.h>
#include <TSS.h>
#include <interrupts.h>
#include <def.h>
#include <IOProgramer.h>
#include <test.h>
#include <PMLoader.h>
#include <VirtualMemory.h>


#include <macros/all.h>

#if defined(CODE32)

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
"mov  $512*5 - 1,%esp \n\t"
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
	//=================设置PDE0，PTE， 进入虚拟内存管理模式
	*(int*)PMLoader::PDE0_START= ((0x1u<<12)|0b11011);
	int *pte=(int*)PMLoader::PTE0_START;
	size_t n=(PMLoader::DATA_LIMIT+1)/4096;
	//0: Global,not dirty,
	//1~3:not global,dirty
	//4~6(IDT,GDT):global,dirty
	//set all just global,not dirty
	for(size_t i=0;i<n;i++)
	{
		pte[i]= (i<<12)|0b100011011;
	}
	VirtualManager::writeCr3(CR3(0,PageAttributes::PWT_ALWAYS_UPDATE,PageAttributes::PCD_CACHE_DISABLE));
	VirtualManager::enablePaging();
//	__asm__ __volatile__(
//		"mov $0x18,%%eax \n\t"
//		"mov %%eax,%%cr3\n\t" //--> physical 0
//		"mov %%cr0,%%eax \n\t"
//		"or  $0x80000000,%%eax \n\t"
//		"mov %%eax,%%cr0 \n\t"
//	:
//	:
//	:"eax"
//	);


//	Util::printStr("a function call\n");
//	Util::jmpDie(); //vbox OK
    //=====================清除屏幕，初始化调试信息打印器区域
    Util::clr();
    Util::setStrSel(Util::getCurrentDs());
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
    	IO_HDD iohd(0,(unsigned char)(PMLoader::REAL_SECNUMS + PMLoader::PROTECTED_SECNUMS - nleft),(size_t)nleft,Util::getCurrentDs(),(size_t)PMLoader::TEMP_SEG*16);
    	iohd.read();
    }

    //===================从这里插入test的hook
    stdp.putsz("Running Test.\n");
    Test test;
    test.run();
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
    reuse_sel.init(0x10,(int)&int0x21,SelectorDescriptor::TYPE_INT,SegmentDescriptor::DPL_3);//重新设置int0x21
    reuse_sel.writeToMemory(Util::SEG_CURRENT,PMLoader::IDT_START+0x21*8);
    reuse_sel.init(0x10,(int)&int0x30,SelectorDescriptor::TYPE_INT,SegmentDescriptor::DPL_3);//重新设置int0x21
    reuse_sel.writeToMemory(Util::SEG_CURRENT,PMLoader::IDT_START+0x30*8);

    
    //==================初始化内核，这里可以明显看到内核的概念：资源管理器的集合
    Kernel *pkernel=(Kernel*)PMLoader::KERNEL_START;
    /**
     * Once I've made a mistake about initiating theKernel
     *
     */
    Kernel::initTheKernel(pkernel);
    stdp.putsz("after init kernel\n");
    int gused[]={0,1,2,3,4,5};
    new (pkernel) Kernel(
    		PMLoader::SMM_MEM_START,PMLoader::SMM_MEM_SIZE,
			PMLoader::KERNEL_MM_START,PMLoader::KERNEL_MM_SIZE,
			/*PMLoader::PROCESS_MM_START*/0,PMLoader::PROCESS_MM_SIZE,
			PMLoader::PDE0_START,PMLoader::PDE0_SIZE,
			PMLoader::PTE0_START,PMLoader::PTE0_SIZE,
			PMLoader::GDT_NODE_START,PMLoader::GDT_START,PMLoader::GDT_NODE_ITEMS,gused,arrsizeof(gused),
			PMLoader::IDT_NODE_START,PMLoader::IDT_SIZE,PMLoader::IDT_NODE_ITEMS,NULL,0
    );//初始化一个新的kernel
//    pkernel->markGdtUsed(0);
//    pkernel->markGdtUsed(1);
//    pkernel->markGdtUsed(2);
//    pkernel->markGdtUsed(3);
//    pkernel->markGdtUsed(4); //They should be marked in use at first time,but unfortunately,they are not.
    stdp.putsz("after kernel done\n");

    int viIndex=pkernel->preparePhysicalMap(4*1024*1024, 4*1024);
//    Util::insertMark(0x23339);
//    Util::digitToStr(buf, arrsizeof(buf), viIndex);
//    stdp.putsz("Gdt index is :");stdp.putsz(buf);stdp.putsz("\n");
    Util::setl(Util::makeSel(viIndex, 0, 0), 0, 0xaa55);

    //=========================test using virtual memory to build new process
    //===test visiting (1MB,4096B)
    //need 1 PTE
    //LinearAddress [0][767][0]=5MB
    //save PTE[676],set,visit,save back
    Util::insertMark(0x2333b);
    int pte_index=767;
    int pde_index=0;
    int savedPTE=pte[pte_index];
    pte[pte_index]=(1*1024*1024 & 0x3ff000)|0b100011011;
    int byte_index=(1*1024*1024) & 0xfff;

    char *target_addr=(char*) ((pde_index<<22)|(pte_index<<12)|byte_index); //没有超过当前ds的限制
    Util::insertMark(0x2333d);
    target_addr[0]='x';
    target_addr[1]='h';
    target_addr[2]='d';
    target_addr[3]=0;
    stdp.putsz(target_addr);

    pte[767]=savedPTE;
    Util::jmpDie();//wait to see output after paging enabled. OK.

//    //do some adjustment so that the allocated space will not be corrupted
//
//    Kernel::getTheKernel()->createTheIdlePreocess();//or created by the constructor
//    						//idle process is useful because when treating the kernel as a process too,we can benefit from the existing
//    						//handles.
//    Kernel::getTheKernel()->createProcess();//task 1,create a process,but do not run it.
//    Kernel::getTheKernel()->createProcess();//task 2


    //=============after inited kernel,create the first process & make it await
    //...i am doing this,but need to test functions above work normally.It's time goto :bed:.
    /**
     * Let's try to invoke idle process
     */
//    Util::ltr(Util::makeSel(5, 0, 0));
//    Util::lldt(Util::makeSel(6, 0, 0));

//    Util::printStr("ltr & ldtr before switch succeed\n");
//    __asm__ __volatile__(
//    		"jmp *%%edx \n\t"
//    		:
//    		:"d"(idle)
//			:
//    );
//    pkernel->switchNextProcess();

    /**
     * Let's try to create a new process
     * 	I know process1 is in(memory address) (100+14 (protected sector number + reserved sector number),4) and another one is the next 4 sectors
     * 	next to it.
     */
    TreeNode<Process*>* wp=pkernel->addNewProcess(24*512, 24*512,4*512, 3);
    Process *proc1=wp->getData();
    //根据proc1.LBase 构造一个新的ds选择子，基地址指向proc1的基地址
    int pdeIndex_proc1=1;
    int *newpte0=(int*)pkernel->mnewKernel(3*sizeof(int));//24个扇区，共需3个PTE项
    int newpte0Index=((size_t)newpte0) >> 12;
    ((int*)(PMLoader::PDE0_START))[1]=0;

    //copy code&data the process space
    Util::insertMark(0x23336);
    Util::memcopy(Util::getCurrentDs(),132*512,Util::makeSel(5, 0, 0),proc1->getProcessBase()+proc1->getCodeStart(),16*512);/*copy code to allocated process space*/
    TreeNode<Process*>*	wp2=pkernel->addNewProcess(24*512,24*512, 4*512, 3);
    Process *proc2=wp2->getData();
    Util::memcopy(Util::getCurrentDs(),148*512,Util::makeSel(5, 0, 0), proc2->getProcessBase()+proc2->getCodeStart(),16*512);
    //    pkernel->switchNextProcess();//jump to the target

//    TSS *ptss=(TSS*)Kernel::getTheKernel()->mnewKernel(PMLoader::TSS_MIN_SIZE*2);
//    stdp.putsz("after new tss\n");//this is never reached

    
    //====================tss0 & 描述符
//    TSS tss0;//
//    TSS *ptss=(TSS*)PMLoader::TSS_AREA_START;
    
//    ptss[0].SS0 = Util::makeSel(4);
//    ptss[0].ESP0 = 3*512 - 4;
//    tss0.writeToMemory(Util::SEG_CURRENT,PMLoader::TSS_AREA_START);
    //SS0:ESP0之后会被int用到，发生到高特权级的中断会切换堆栈
//
//    int n=Kernel::getTheKernel()->newgdt((char*)ptss,PMLoader::TSS_MIN_SIZE-1, SegmentDescriptor::G_1B,
//    				SegmentDescriptor::TYPE_S_TSS_32_AVL, 0, 0, 0, 1);
//    if(n==-1)
//    {
//        stdp.putsz("tss0 written failed,dying the machine\n");
//        Util::jmpDie();
//    }

//	stdp.putsz("tss0 written succeed\n");
//	Util::ltr(Util::makeSel(n, 0));//lowest allowed CPL=0
//	stdp.putsz("Had ltr done.\n");


//    SegmentDescriptor tss0_descr((char*)ptss,PMLoader::TSS_MIN_SIZE-1,SegmentDescriptor::G_1B,SegmentDescriptor::TYPE_S_TSS_32_AVL,0,0,0);
//    tss0_descr.writeToMemory(Util::SEG_CURRENT,(char*)PMLoader::GDT_START+5*8);//TSS0描述符所处的位置
//    Util::ltr(Util::makeSel(5));// load task register
    
    
    Util::insertMark(0x12345);
    CALL_INT_3(0x24,c,Util::getCurrentDs(),b,"int 0x24 by CPL0.\n",d,Util::MODE_COMMON);
    
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
    p2.setTimeMicro(0,10);//设置通道0，间隔：n微秒
    
//    //===============设置CPL=3的描述符
//    SegmentDescriptor cs3(0,0xfffff,SegmentDescriptor::G_1B,SegmentDescriptor::TYPE_U_CODE_CONFORMING,0);
//    SegmentDescriptor ds3(0,0xffff,SegmentDescriptor::G_1B,SegmentDescriptor::TYPE_U_DATA,3);
//    SegmentDescriptor ss3(0,4*512,SegmentDescriptor::G_1B,SegmentDescriptor::TYPE_U_STACK,3);
//
//    cs3.writeToMemory(Util::SEG_CURRENT,(char*)PMLoader::GDT_START+6*8);
//    ds3.writeToMemory(Util::SEG_CURRENT,(char*)PMLoader::GDT_START+7*8);
//    ss3.writeToMemory(Util::SEG_CURRENT,(char*)PMLoader::GDT_START+8*8);
//
    
    //=====================一个闲置任务tss1
//    TSS tss1;
//    ptss[1].CS=Util::makeSel(6,0x3);
//    ptss[1].EIP=(int)forTss1;
//    ptss[1].SS = Util::makeSel(8,0x3);
//    ptss[1].ESP=512*2-4;
//    ptss[1].SS0 = Util::makeSel(4);
//    ptss[1].ESP0 = 512 - 4;
//    ptss[1].EFLAGS =0x202 ;//| 0x100;
//    ptss[1].DS = 0x3b;
//    tss1.writeToMemory(Util::SEG_CURRENT,PMLoader::TSS_AREA_START+PMLoader::TSS_MIN_SIZE);
//    SegmentDescriptor tss1_sel((char*)(ptss+1),PMLoader::TSS_MIN_SIZE-1,SegmentDescriptor::G_1B,SegmentDescriptor::TYPE_S_TSS_32_AVL,0,0,0);
//    tss1_sel.writeToMemory(Util::SEG_CURRENT,(char*)PMLoader::GDT_START+9*8);
    
    
    //允许中断
    Util::insertMark(0x2333a);
    Util::sti();
    //========================利用iret切换到特权级3，此后此任务运行在特权级3
//    stdp.putsz("Changing CPL to 3.\n");
//    Util::changeCPL((int)afterCPL3,0x33,Util::getEflags(),4*512-4,0x43);
    Util::jmpDie();//wait until time interrupts
    
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
