/*
 * KernelMemoryConfig.h
 *
 *  Created on: Nov 22, 2017
 *      Author: 13774
 */

#ifndef INCLUDE_KERNELMEMORYCONFIG_H_
#define INCLUDE_KERNELMEMORYCONFIG_H_



// 此文件作为protected_main的资源文件引入，主要包括了各个内核数据结构的定义
// 此文件决定了内核的结构
// 该文件中不得包含任何代码，必须全部为数据
// 所有的变量以mm开头，表示这是分配给它的空间

#include <Kernel.h>
#include <def.h>



#if defined(CODE32)

/**
 * 保护模式下需要使用GDT，IDT表的位置，所以这两个表必须位于确定的位置
 * 实际上，GDT表和IDT表是紧挨着存放的，因此只需要直到GDT表的位置即可
 * 由于内存0处的开始被视为栈的内容，栈的大小决定了GDT表的位置为此，只要栈的大小为8的整数倍，则GDT放在栈之后，一定能够是8的整数倍
 * 因此，实际上GDT表的位置在数值上可以设置成栈的大小，由此解决了32位和16位GDT数据共享的问题
 */
namespace KernelMemoryConfig{
	enum{
		INIT_STACK_SZIE =  CONFIG_INIT_STACK_SIZE,
		PDE_NUM = CONFIG_KERNEL_PDE_NUM,
		PTE_0_NUM = CONFIG_KERNEL_PTE_0_NUM,
		PTE_1_NUM = CONFIG_KERNEL_PTE_1_NUM,
		GDT_LEN = CONFIG_GDT_ITEM_NUM,
		IDT_LEN = CONFIG_IDT_ITEM_NUM,
		MMNODE_NUM = CONFIG_KERNEL_MMNODE_NUM,
		INPUT_BUFFER_LEN = CONFIG_INPUT_BUFFER_SIZE
	};
	extern char mmInitStack[];
	extern char mmKernel[];
	extern char mmPDE[] ;
	extern char mmPTE_0[] ;
	extern char mmPTE_1[] ;
	extern char mmGDT[];
	extern char mmIDT[];
	extern char mmGDTAssocNode[];
	extern char	mmIDTAssocNode[];
	extern char mmKernelMMNodes[];
	extern char mmInputBuffer[];
};
#endif //CODE32




#endif /* INCLUDE_KERNELMEMORYCONFIG_H_ */
