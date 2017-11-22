/*
 * KernelMemoryConfig.cpp
 *
 *  Created on: Nov 22, 2017
 *      Author: 13774
 */

#include <KernelMemoryConfig.h>

#if defined(CODE32)
	__asm__(".code32 \n\t"); //在本节不存放代码的情况下没有意义
#endif


#if defined(CODE32)

// NOTE 该文件不能引用CONFIG_PREFIX_SIZE，因为在生成其大小之前还不知道
#undef CONFIG_PREFIX_SIZE

namespace KernelMemoryConfig{

// 0 地址处，这里是栈的位置
char mmInitStack[KernelMemoryConfig::INIT_STACK_SZIE]; // 在进入到内核之后的初始栈，注意，这个栈之后被用于System进程


// 注意GDT表放在STACK之后，地址计算为INIT_STACK_SIZE%8==0?INIT_STACK_SZIE:INIT_STACK_SZIE/8*8+8;
// 对齐到8字节
char mmGDT[x2sizeof(SegmentDescriptor) * KernelMemoryConfig::GDT_LEN] ATTRIBUTE_ALIGNED(8); //GDT表的长度
char mmIDT[x2sizeof(SegmentDescriptor) * KernelMemoryConfig::IDT_LEN] ATTRIBUTE_ALIGNED(8);

char mmGDTAssocNode[GDT_LEN * x2sizeof(Kernel::SegManager::NodeType)];
char mmIDTAssocNode[IDT_LEN * x2sizeof(Kernel::SegManager::NodeType)];


/**
 *    初始化内核的基本结构
 *    原则：	内置结构应当作为内核的成员或者指针
 *    		常见可选结构作为指针，当为NULL时表示内核不使用此功能
 *    		其他非常用可选结构定义在内核的外部
 *
 *      内置：	内核空间内存管理器
 *      		进程空间内存管理器
 *      		进程管理器
 *      		键盘输入缓冲区
 *      		GDT管理器
 *				IDT管理器
 *      		PDE管理器
 *      		文件系统管理器
 *      		IO管理器
 *      常见可选：
 *
 *      此处仅仅简单地分配空间，内核初始化在初始化程序中完成
 *
 *      内核中的结构分为两类：可确定空间的和不定空间的，可定空间的结构以成员方式加载，非可定空间的结构以指针方式加载
 */
char mmKernel[x2sizeof(Kernel)];//一个内核结构



// 对齐到4096字节，然后分配PDE和PTE
//  为了使一个PDE，1024个PTE就能管理4MB空间，参见虚拟内存详解部分
//  内核设计越简单越好
char mmPDE[x2sizeof(PDE) * KernelMemoryConfig::PDE_NUM] ATTRIBUTE_ALIGNED(4); //总PDE的项，PDE0用于内核
char mmPTE_1[x2sizeof(PTE) * KernelMemoryConfig::PTE_1_NUM] ATTRIBUTE_ALIGNED(4); //第1项PDE的PTE项数，用于访问高端内存

char mmKernelMMNodes[x2sizeof(Kernel::FullMMNodeType) * KernelMemoryConfig::MMNODE_NUM];//用于简单内存分配器的项数，至少是100个
char mmInputBuffer[x2sizeof(Kernel::InputBufferDataType) * KernelMemoryConfig::INPUT_BUFFER_LEN];  // 输入缓冲区

char mmPTE_0[x2sizeof(PTE) * KernelMemoryConfig::PTE_0_NUM] ATTRIBUTE_ALIGNED(4096); //第0项PDE的PTE项数,必须能够覆盖所有的内核代码

};

__asm__(
		".data \n\t"
		".align 512\n\t"
		".bss \n\t"
		".align 512 \n\t"
);// 对齐到512的边界

#endif
