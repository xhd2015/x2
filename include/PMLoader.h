
#ifndef PMLoder_h__
#define PMLoder_h__

#include <Kernel.h> //for kernel
#include <Memory.h>  //for MemoryManager
#include <List.h>  //for SimpleMemoryManager

//实模式下的 “保护模式加载器”
// 主加载过程：（顺序有严格要求，见mainProcess）
//
//  设置idtr,gdtr以及其中相关的数据。
//  读取保护模式代码
//  启用A20
//  设置 gdtr,idtr
//  进入保护模式

class PMLoader{
public:
	enum{
		SAFE_SEG = 0x50,
		SECSIZE = 512,
		STACK_START = 0,/*for kernel*/
	   STACK_SIZE = 4 * SECSIZE,
	   IDT_START = STACK_START + STACK_SIZE,
	   IDT_SIZE = 1 * SECSIZE,
	   GDT_START = IDT_START + IDT_SIZE,
	   GDT_SIZE = 2 * SECSIZE,
	   TSS_AREA_SIZE = 2 * SECSIZE,
	   TSS_AREA_START = GDT_START + GDT_SIZE,
	   TSS_MIN_SIZE = 104,
	   FREE_HEAP_SIZE = 5 * SECSIZE,
	   FREE_HEAP_START = TSS_AREA_START + TSS_AREA_SIZE,
	   CODE_START = FREE_HEAP_START + FREE_HEAP_SIZE,
/* CODE_SEG must be 0 ******DEPRECATED****	   CODE_SEG = 0, *******/
	   CODE_LIMIT = 0xfffff,
		JMPSEG = 0x10,
#if defined(CODE16)
		DRIVER = 0x80,  /*valid only for real mode*/
#endif
		REAL_SECNUMS = 25,
		PROTECTED_SECNUMS = 100,
		TEMP_SEG = 0xa00
#if defined(CODE32) //
		/////////////Kernel arguments
		,
		KERNEL_START,
		KERNEL_LENGTH = sizeof(Kernel),
		MEMMAN_START,
		MEMMAN_LENGTH = sizeof(MemoryManager),
		SMM_MEM_START,
		SMM_MEM_LENGTH = sizeof(SimpleMemoryManager<TreeNode<MemoryDescriptor> >),
		SMM_MAN_INIT_NODES = 100,
		SMM_MAN_AREA_START,
		SMM_MAN_AREA_LENGTH = sizeof(TreeNode<MemoryDescriptor>) *SMM_MAN_INIT_NODES,
		END_OF_WHOLE_KERNEL,
		GLOBAL_SHARE_START,
		GLOBAL_SHARE_LENGH, //全局共享的库或者数据
		PROCESS_SPECIAL_START,
		PROCESS_SPECIAL_LENGTH
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
    static void setidtr(short len,int address);
    static void setgdtr(short len,int address);
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
