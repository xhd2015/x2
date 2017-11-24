
#ifndef PMLoder_h__
#define PMLoder_h__

#include <Kernel.h> //for kernel
#include <MemoryManager.h>  //for MemoryManager
#include <List.h>  //for SimpleMemoryManager

//实模式下的 “保护模式加载器”
// 主加载过程：（顺序有严格要求，见mainProcess）
//
//  设置idtr,gdtr以及其中相关的数据。
//  读取保护模式代码
//  启用A20
//  设置 gdtr,idtr
//  进入保护模式

#if defined(CODE16)
	extern "C" void realModeTest();
#endif

class PMLoader{
public:
	enum{
		SAFE_SEG = 0x50,
		SECSIZE = CONST_SECSIZE,
		PDE0_START = 0,
		PDE0_SIZE = 1 * SECSIZE, /* PDE占用1个扇区*/
		STACK_START = PDE0_START + PDE0_SIZE,/*for kernel*/
	   STACK_SIZE = 4 * SECSIZE,
	   IDT_START = STACK_START + STACK_SIZE,
	   IDT_SIZE = 1 * SECSIZE,
	   GDT_START = IDT_START + IDT_SIZE,
	   GDT_SIZE = 2 * SECSIZE,
	   PTE0_START = GDT_START + GDT_SIZE,
	   PTE0_SIZE = 6 * SECSIZE,/*PTE 占用6个扇区*/
	   /**
	    * TSS_AREA_XXX is deprecated because  TSS will be allocated dynamically
	    */
//	   TSS_AREA_SIZE = 2 * SECSIZE,
//	   TSS_AREA_START = GDT_START + GDT_SIZE,

	   /**
	    * memory layout:
	    * 	0	[		]-->PDE0
	    * 	512 [		]
	    * 	...
	    * 512*4	[		]-->stack
	    * 512*5	[		]-->IDT
	    *	...
	    * 512*7	[		]-->GDT
	    * 512*8 [		]-->PTE0
	    * 	...
	    * 512*14[		]-->theKernel,FreeHeap Start
	    * 		[		]-->SMMNode*100 //6个扇区
	    * 		[		]-->GDT Associated Nodes
	    * 		[		]-->IDT Associated Nodes
	    * 	...
	    * 512*32[		]-->Code Start
	    *	...
	    * 0xfffff[		]-->Code End,Global Share Start	-->Kernel MemoryManager
	    *  +2MB[		]-->Global Share End --> End of Whole Kernel
	    *		[		]-->Process MemoryManager
	    *
	    */
	   TSS_MIN_SIZE = 104,
	   FREE_HEAP_SIZE = 18 * SECSIZE,
	   FREE_HEAP_START = PTE0_START + PTE0_SIZE,
	   CODE_START = FREE_HEAP_START + FREE_HEAP_SIZE,
/* CODE_SEG must be 0 ******DEPRECATED****	   CODE_SEG = 0, *******/
	   CODE_LIMIT = 0xfffff,//1MB为代码，2MB为内核空间
	   DATA_LIMIT = 0x2fffff,
	   STACK_LIMIT = IDT_START - 1,/*Limit is the biggest address that can be achieved */
	   CODE_SIZE = CODE_LIMIT - CODE_START + 1,
		JMPSEG = 0x10,
		JMPOFF = CODE_START + 10*SECSIZE,//从某个扇区开始
#if defined(CODE16)
		DRIVER = 0x80,  /*valid only for real mode*/
#endif
		RESERVED_SECNUM = 32,
		REAL_SECNUMS = CONFIG_REAL_SECNUMS,



		PROTECTED_SECNUMS =  CONFIG_PROTECTED_SECNUMS,
				// 132,/*100 for codes,8 for process1 & process2*/
		PROCESS_SECNUMS = CONFIG_USER_PROCESS_SECNUMS,
		PROCESS_EACH_SECNUMS = CONFIG_USER_PROCESS_EACH_SECNUMS,
		TEMP_SEG = 0xa00,
#if defined(CODE32)
		/////////////Kernel arguments

		/**
		 * For theKernel
		 */
		KERNEL_START=FREE_HEAP_START,
		KERNEL_SIZE = x2sizeof(Kernel),


		/**
		 * For theKernel->smm
		 */
		SMM_MEM_START = KERNEL_START + KERNEL_SIZE,
		// NOTICE 不要使用TreeNode<MemoryDescriptor>,之前犯过这样的错误
		SMM_NODE_SIZE = x2sizeof(Kernel::SmmType::FullNode), //32,
		SMM_MAN_INIT_NODES = 100,
		SMM_MEM_SIZE = SMM_NODE_SIZE * SMM_MAN_INIT_NODES,

		/**
		 * for idtm,gdtm
		 * associated nodes
		 */
		GDT_NODE_START = SMM_MEM_START + SMM_MEM_SIZE,
		GDT_NODE_ITEMS = GDT_SIZE / x2sizeof(SegmentDescriptor),
		IDT_NODE_START = GDT_NODE_START +  GDT_NODE_ITEMS*x2sizeof(SegmentDescriptor),
		IDT_NODE_ITEMS = IDT_SIZE / x2sizeof(SegmentDescriptor),
#endif

#if defined(CODE32)||defined(CODE16)
		/**
		 * Global shares
		 */
		GLOBAL_SHARE_START = CODE_LIMIT+1,
		GLOBAL_SHARE_SIZE = 2*1024*2*SECSIZE, //全局共享的库或者数据,2MB
		/**
		 * for theKernel->kernelMM
		 */
		KERNEL_MM_START = GLOBAL_SHARE_START,
		KERNEL_MM_SIZE = GLOBAL_SHARE_SIZE, //point to the end of whole kernel

		END_OF_WHOLE_KERNEL = GLOBAL_SHARE_START + GLOBAL_SHARE_SIZE, //32MB memory,1MB for code,2MB for kernel space



		/**
		 * for theKernel->processMM
		 */
		PROCESS_MM_START = END_OF_WHOLE_KERNEL,
		PROCESS_MM_SIZE = 32*1024*1024 - PROCESS_MM_START,//实际内存的大小
#endif

	};
public:
#if defined(CODE16)
    PMLoader();//指定保护模式的代码区域： 1.磁盘区域:驱动器，逻辑起始地址 2.内存区域 段：偏移
    //一般而言，如果代码在同一个磁盘上，为保护模式预留12~20个扇区是足够测试用的。因此取值可以认为保护模式代码在第16个扇区
    ~PMLoader();
    /**
    *一般而言，计算机的A20是随开机自动启用的，这里仅仅是确保其被开启
    */
    static void enableA20();
    
    /**
    *lidt paddr
    *at paddr: .word(length) .long(baseaddr).  baseaddr在高地址
    *相对于栈来说，较后面的参数在栈高地址
    */
    static void setidtr(int len,int address);
    static void setgdtr(int len,int address);
    /**
    * 必须提供PROTECTED_SEL,PROTECTED_ENTRY的值
    * 或者必须将保护模式代码置于 0b10000:0 处开始
    */
    static void enterProtected();
    /**
    *考虑到中断在0:0处，在int 0x13期间不能被覆盖
    */
    static void adjustProtectedCode();
    /**
    *主要用于指定与代码相关的数据，初始化时指定的是读取相关的数据
    *指定gdt,idt,
    */
    static void mainProcess();

#endif
    
};
//==================宏定义区
#endif //PMLoader_h__
