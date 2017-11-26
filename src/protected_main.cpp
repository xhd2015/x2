#include <Kernel.h>
#include <libx2.h>
#include <Descriptor.h>
#include <TSS.h>
#include <interrupts.h>
#include <def.h>
#include <IOProgramer.h>
#include <KernelMemoryConfig.h>
#include <test.h>
#include <PMLoader.h>
#include <VirtualMemory.h>

#include <macros/all.h>

#if defined(CODE32) //we are now at Protected Mode
__asm__(".code32 \n\t");
#endif

__asm__(
".text \n\t"		// 将跳转代码临时放到栈区，栈至少是N个扇区大小，用于跳转到开始处的代码
//		"jmp .\n\t"  //vbox ok
		"// .global _extraVboxTest \n\t"
		"// .global _protectedEntryHolder \n\t"
"movw $0b11000,%ax \n\t" //ds选择子，
"movw %ax,%ds \n\t"
"mov  %ax,%es \n\t"
"mov %ax,%gs \n\t"
"mov %ax,%fs \n\t"
"mov $0b100000,%ax \n\t"
"movw %ax,%ss \n\t" //ss选择子
"mov  $CONFIG_INIT_STACK_SIZE - 1,%esp \n\t"
"call _extraVboxTest\n\t"
"call _protectedEntryHolder \n\t"
"jmp 1f \n\t"
"1:\n\t"
); //注意，至多有两个扇区大小

#if defined(CODE32)

extern "C" {
	void extraVboxTest();
    void protectedEntryHolder();
    void afterCPL3();    
    void forTss1();
}

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
    //=======================读取剩余的扇区
//    stdp.putsz("Reading left sectors...\n");
//    Util::jmpDie(); //vbox wrong
//    size_t nleft=*(unsigned short*)PMLoader::FREE_HEAP_START;//2个字节

//    stdp.puti("Left sector number is :",nleft);

	int secEach = 250;
	int read = CONFIG_REAL_LOAD_PROTECTED_SECNUM ;
	int left = CONFIG_PROTECTED_SECNUMS + CONFIG_USER_PROCESS_SECNUMS - read;
	while(left > 0)
	{
		int thisRead = left>secEach?secEach:left;
		IO_HDD iohd(0,
				CONFIG_REAL_SECNUMS  + read,
				thisRead,
				Util::getCurrentDs(),
				CONFIG_PREFIX_SIZE + read*CONST_SECSIZE
		);
		left -= thisRead;
		iohd.read();
		IO_BLOCK();
	}
//		Util::jmpDie();

	//=================设置PDE0，PTE， 进入虚拟内存管理模式
	//Util::printStr("in protectedEntryHolder");
//	*(int*)PMLoader::PDE0_START= Kernel::makePDE(0x1000,0b11011);
	int *PDE_USED_ON_ENABLING_CR3=(int*)( (int)KernelMemoryConfig::mmPDE & 0xfffff000 ); //当虚拟内存开启之后，是物理地址等于线性地址的方法
															//mmPDE表示当前PDE应当设置的位置，注意mmPDE的范围应当在栈内


	// TODO 完成TLD后将下面的数字修改回开始
	int *PTE_USED_ON_ENABLING_CR3=(int*)(CONFIG_KERNEL_CODE_SIZE * 3);//指向未分配的内存区域，用来建立所有的PDE

	*PDE_USED_ON_ENABLING_CR3 =  Kernel::makePDE((int)PTE_USED_ON_ENABLING_CR3);
	for(int i=0;i<CONFIG_KERNEL_PTE_0_NUM;++i)
		PTE_USED_ON_ENABLING_CR3[i]=Kernel::makePTE(i*4*1024);


	*(int*)KernelMemoryConfig::mmPDE = Kernel::makePDE((int)KernelMemoryConfig::mmPTE_0);

//	int *pte=(int*)PMLoader::PTE0_START;
	int *pte=(int*)KernelMemoryConfig::mmPTE_0;

//	size_t n=(PMLoader::DATA_LIMIT+1)/4096;
	//0: Global,not dirty,
	//1~3:not global,dirty
	//4~6(IDT,GDT):global,dirty
	//set all just global,not dirty
	for(size_t i=0;i<KernelMemoryConfig::PTE_0_NUM;i++)
	{
		pte[i] = Kernel::makePTE(i*4*1024); //每4KB一个,0xb8000，即视频缓冲区就在0xb8项
	}
//	Util::jmpDie();
	VirtualManager::writeCr3(Kernel::makeCR3((int)KernelMemoryConfig::mmPDE));
	VirtualManager::enablePaging();

	int dsLineAddr = VirtualManager::getLinearAddress(
			(int)KernelMemoryConfig::mmPDE,
			(int)KernelMemoryConfig::mmPTE_0,
			(int)0);
	// 在gdt中重新构造cs,ds,ss的描述
	SegmentDescriptor* gdttable=(SegmentDescriptor*)KernelMemoryConfig::mmGDT;
	gdttable[2].setBaseAddr(dsLineAddr);//cs
	gdttable[3].setBaseAddr(dsLineAddr);//ds
	gdttable[4].setBaseAddr(dsLineAddr);//ss
	gdttable[1].setBaseAddr(dsLineAddr+0xb8000);////video

	// TODO 将下面的地址正确化，现在似乎还没有这个需求
	gdttable[5].setBaseAddr(dsLineAddr + CONFIG_KERNEL_CODE_SIZE + CONFIG_KERNEL_FREE_MEM_SIZE);//process base,涉及PDE1

	// 重新加载cs,ds,ss ljmp *(%esp)
	Util::setCurrentDs(Util::makeSel(3));
	Util::setCurrentSs(Util::makeSel(4));
	__asm__ __volatile__(
			"pushw %%cx \n\t"
			"push  $AFTER_JMP \n\t"
			"ljmp *(%%esp) \n\t"
			"AFTER_JMP:\n\t"
			:
			:"c"(Util::makeSel(2))
			:
		);

	// TODO 完成下面的功能，刷新缓存
	//重置TLB缓存
//	for(int i=0;i<CONFIG_KERNEL_CODE_SIZE*2;i++)
//	{
//		__asm__ __volatile__(
//				"invlpg (%0)\n\t"
//				:
//				:"r"(i)
//				 :"memory"
//		);
//	}


//	Util::printStr("a function call\n");
//	Util::jmpDie(); //vbox OK
    //=====================清除屏幕，初始化调试信息打印器区域
    Util::clr();
    Util::setStrSel(Util::getCurrentDs());
//    Util::jmpDie();  //vbox wrong
//    Printer stdp(3,30,15,40,Util::MODE_COMMON);//系统的标准打印器
    Printer stdp(0,0,Util::SCREEN_X,Util::SCREEN_Y,Util::MODE_COMMON);//系统的标准打印器
//    Util::jmpDie(); //vbox wrong
    Kernel::printer=&stdp;
//    stdp.clr();
//    Util::jmpDie(); //vbox wrong
    stdp.putsz("Entered Protected Mode.\n");


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
        reuse_sel.writeToMemory(Util::SEG_CURRENT,(size_t)KernelMemoryConfig::mmIDT+8*i);

    }
    reuse_sel.init(0x10,(int)&int0x20,SelectorDescriptor::TYPE_INT,SegmentDescriptor::DPL_3);//重新设置int0x20
    reuse_sel.writeToMemory(Util::SEG_CURRENT,(size_t)KernelMemoryConfig::mmIDT+8*0x20);
    reuse_sel.init(0x10,(int)&int0x21,SelectorDescriptor::TYPE_INT,SegmentDescriptor::DPL_3);//重新设置int0x21
    reuse_sel.writeToMemory(Util::SEG_CURRENT,(size_t)KernelMemoryConfig::mmIDT+8*0x21);
    reuse_sel.init(0x10,(int)&int0x30,SelectorDescriptor::TYPE_INT,SegmentDescriptor::DPL_3);//重新设置int0x30
    reuse_sel.writeToMemory(Util::SEG_CURRENT,(size_t)KernelMemoryConfig::mmIDT+8*0x30);

    
    //==================初始化内核，这里可以明显看到内核的概念：资源管理器的集合
    Kernel *pkernel=(Kernel*)KernelMemoryConfig::mmKernel;
    /**
     * Once I've made a mistake about initiating theKernel
     *
     */
    Kernel::initTheKernel(pkernel);
//    stdp.putsz("after init kernel\n");

//    Kernel::printer->clr();
    Kernel::printer->putsz("by kernel printer\n");

    int gused[]={0,1,2,3,4,5};
    Util::insertMark(0xe181e181);
    size_t mmUsedList[][2]={
    		{0,CONFIG_KERNEL_CODE_SIZE},
    };
   stdp.putx("config_code_size=",CONFIG_KERNEL_CODE_SIZE);
   stdp.putx("config_mem_size=",CONFIG_KERNEL_FREE_MEM_SIZE);
    new (pkernel) Kernel(
    		(int)KernelMemoryConfig::mmKernelMMNodes,KernelMemoryConfig::MMNODE_NUM*x2sizeof(Kernel::FullMMNodeType),
			CONFIG_KERNEL_CODE_SIZE	,								CONFIG_KERNEL_FREE_MEM_SIZE, mmUsedList,1,
			CONFIG_KERNEL_CODE_SIZE + CONFIG_KERNEL_FREE_MEM_SIZE,	CONFIG_PROCESS_MEM_SIZE,
			(int)KernelMemoryConfig::mmPDE,		KernelMemoryConfig::PDE_NUM,
			(int)KernelMemoryConfig::mmPTE_0,	KernelMemoryConfig::PTE_0_NUM,
			(int)KernelMemoryConfig::mmGDTAssocNode,(int)KernelMemoryConfig::mmGDT,KernelMemoryConfig::GDT_LEN,gused,arrsizeof(gused),
			(int)KernelMemoryConfig::mmIDTAssocNode,(int)KernelMemoryConfig::mmIDT,KernelMemoryConfig::IDT_LEN,NULL,0
    );//初始化一个新的kernel
    pkernel->setInputBuffer((Kernel::InputBufferDataType*)KernelMemoryConfig::mmInputBuffer, KernelMemoryConfig::INPUT_BUFFER_LEN);
    stdp.putsz("after kernel done\n");
//    Util::jmpDie(); //GOOD



    //访问绝对地址4MB处的4个字节，该怎么做？
    //在gdt中先新建一项选择子，这个选择子指向了实际地址，并有长度限制
    Kernel::printer->clr();
    int viIndex=pkernel->preparePhysicalMap(4*1024*1024, 4*1024);//need 1,I give you three
    pkernel->printer->puti("viIndex=", viIndex);

    Util::setl(Util::makeSel(viIndex, 0, 0), 0, 0xaa55);//正确实现
//    Util::jmpDie();


    //=========================test using virtual memory to build new process
    //===test visiting (1MB,4096B)
    //need 1 PTE
    //LinearAddress [0][767][0]=5MB
    //save PTE[676],set,visit,save back


    /**
     * 手动设置线性地址
     */
//    int pte_index=767;
//    int pde_index=0;
//    int savedPTE=pte[pte_index];
//    pte[pte_index]=(1*1024*1024 & 0x3ff000)|0b100011011;
//    int byte_index=(1*1024*1024) & 0xfff;
//
//    char *target_addr=(char*) ((pde_index<<22)|(pte_index<<12)|byte_index); //没有超过当前ds的限制
//    target_addr[0]='x';
//    target_addr[1]='h';
//    target_addr[2]='d';
//    target_addr[3]=0;
//    stdp.putsz(target_addr);
//
//    pte[767]=savedPTE;//恢复之前的设置


//  Util::jmpDie();//wait to see output after paging enabled. OK.

//    //do some adjustment so that the allocated space will not be corrupted
//
//    Kernel::getTheKernel()->createTheIdlePreocess();//or created by the constructor
//    						//idle process is useful because when treating the kernel as a process too,we can benefit from the existing
//    						//handles.
//    Kernel::getTheKernel()->createProcess();//task 1,create a process,but do not run it.
//    Kernel::getTheKernel()->createProcess();//task 2



    /**
     * Let's try to create a new process
     */
    //Process的地址 :
    //	PMLoader::PROTECTED_SECNUMS + PMLoader::REAL_SECNUMS
    //	大小:16
    //	布局：0~4:  其他内容+栈（1扇区）
    //		  4~16: 代码

    // TODO 解封下面代码
//    新建一个dpl=3的进程,申请24*512大小的空间
    TreeNode<Process*>* wp=pkernel->addNewProcess(24*512 - 1, 24*512 - 1,4*512 - 1, 3);
    pkernel->printer->putx("new process is ", (int)wp);

    Process *proc1=wp->getData();
    //根据proc1的线性地址构造一个新的ds选择子，基地址指向proc1的基地址


    // NOTE 这里一定要使用Align版本的new，因为pte，pde都必须是4的倍数
//      int  pdeIndex = pkernel->
      PTE *newpte0=(PTE*)pkernel->mnewKernelAlign(3*x2sizeof(PTE),4);//24个扇区，共需3个PTE项
      stdp.putx("newpte 0 address=",(int)newpte0);
      ((int*)(KernelMemoryConfig::mmPDE))[2] = Kernel::makePDE((int)newpte0);
      newpte0[0] = Kernel::makePTE(CONFIG_KERNEL_CODE_SIZE + CONFIG_KERNEL_FREE_MEM_SIZE);
      newpte0[1] = Kernel::makePTE(CONFIG_KERNEL_CODE_SIZE + CONFIG_KERNEL_FREE_MEM_SIZE+4*1024);
      newpte0[2] = Kernel::makePTE(CONFIG_KERNEL_CODE_SIZE + CONFIG_KERNEL_FREE_MEM_SIZE+8*1024);
      int lineAddr = VirtualManager::getLinearAddress((int) KernelMemoryConfig::mmPDE + 2*x2sizeof(int), (int)newpte0, CONFIG_KERNEL_CODE_SIZE + CONFIG_KERNEL_FREE_MEM_SIZE);
      stdp.putx("lineAddr=",lineAddr);
      int limit = 24*512-1;//24个扇区

      int gdtAllocIndex =
      		pkernel->newgdt(
      				(char*)lineAddr,
      				limit/SegmentDescriptor::G_4KB_SCALE,
      				SegmentDescriptor::G_4KB,
      				SegmentDescriptor::TYPE_U_DATA,
      				0);

      pkernel->printer->puti("gdtAllocIndex=",gdtAllocIndex);
//      pkernel->printer->puti("seg address=",(int)pseg);
//      pkernel->printer->puti("sizeof(SegmentDescriptor)=",x2sizeof(SegmentDescriptor));

      //copy code&data the process space
      //将进程的所有扇区复制到
  //    short sel=Util::makeSel(pkernel->preparePhysicalMap(PMLoader::PROCESS_MM_START, PMLoader::PROCESS_EACH_SECNUMS*512), 0, 0);

     short sel=Util::makeSel(gdtAllocIndex, 0, 0);

    pkernel->printer->putsz("before memcopy\n");
    int processCodeImgAddress = CONFIG_PROTECTED_SECNUMS*PMLoader::SECSIZE + CONFIG_PREFIX_SIZE;
    Util::insertMark(0xDEDEDE);
    Util::memcopy(Util::getCurrentDs(),processCodeImgAddress,
    		sel,
			proc1->getProcessBase()+proc1->getCodeStart(),//进程空间+代码起始
			CONFIG_USER_PROCESS_EACH_SECNUMS*512);/*copy code to allocated process space*/
    pkernel->printer->putsz("process1 copied\n");

//    CALL_INT_3(0x24,c,Util::getCurrentDs(),b,"int 0x24 by CPL0.\n",d,Util::MODE_COMMON);
//    pkernel->switchNextProcess();
//    Util::jmpDie();

//    TreeNode<Process*>*	wp2=pkernel->addNewProcess(24*512 - 1,24*512 - 1, 4*512 - 1, SegmentDescriptor::DPL_3);
//    Process *proc2=wp2->getData();
//    Util::memcopy(Util::getCurrentDs(),
//    		((PMLoader::PROTECTED_SECNUMS+PMLoader::REAL_SECNUMS+PMLoader::PROCESS_EACH_SECNUMS))*512,
//			Util::makeSel(5, 0, 0),
//			proc2->getProcessBase()+proc2->getCodeStart(),
//			PMLoader::PROCESS_EACH_SECNUMS*512);
//    pkernel->switchNextProcess();//jump to the target
//    Util::jmpDie();
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
    

//    CALL_INT_3(0x24,c,Util::getCurrentDs(),b,"int 0x24 by CPL0.\n",d,Util::MODE_COMMON);
    
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

    p1.sendOCW1(0, 0xfd);//仅仅允许键盘中断响应
    // TODO 去掉注释，定时中断
//    p1.sendOCW1(0,0xfc);//屏蔽一些中断,允许 定时中断，键盘中断

    p1.sendOCW1(1,0xff);
    
    //对8253编程
    
    // TODO 去掉下面的注释，以允许定时中断
//    IO_8253 p2;//间隔10ms都很难等待
//    p2.setTimeMicro(0,10);//设置通道0，间隔：n微秒

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
    
    
    Kernel::printer->putsz("before sti\n");
    Kernel::printer->clr();
    //允许中断
    Util::sti();
    //========================利用iret切换到特权级3，此后此任务运行在特权级3
//    stdp.putsz("Changing CPL to 3.\n");
//    Util::changeCPL((int)afterCPL3,0x33,Util::getEflags(),4*512-4,0x43);
    while(true)
    {
    	u32_t readChar=(u32_t)pkernel->getChar();
    	if(readChar!=Kernel::EOF)
    	{
    		pkernel->printer->putc(readChar);
    	}
    }
    Util::jmpDie();//wait until time interrupts
    
}

void afterCPL3() //tss0的CPL=3主要代码
{  
    __asm__(
    "pushw $0x3b \n\t" //数据段ds
    "popw %ds \n\t"
    );
    CALL_INT_3(0x24,c,Util::SEG_CURRENT,b,"int 0x24 by CPL3.\n",d,Util::MODE_COMMON);//int n
    SimpleCharRotator scr(0,40);//一个简单的task
    scr.run();   
}
void forTss1() //tss1的主要代码
{
    SimpleCharRotator scr(0,50,Util::MODE_COMMON|Util::MODE_FL_ON|Util::MODE_BG_BLUE);
    scr.run();
}

#endif
