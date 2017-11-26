/*
 * SecondaryLoader.cpp
 *
 *  Created on: Nov 25, 2017
 *      Author: 13774
 */

#include <def.h>
#include <libx2.h>
#include <Filesystem.h>

//第一：选择实模式还是保护模式
// 当然是保护模式，不开启虚拟内存

void secondaryLoaderMain()
{
	//启用A20数据线

	// 禁止中断

	//初始化GDT表，几个段以0作为起始地址

	//初始化GDTR,LDTR寄存器

	//进入保护模式开始代码


	//加载内核

	//配置允许键盘中断

	//加载文件系统（可配置为只读文件系统）

	//加载配置文件

	//查找kernel所在的位置

	//进入控制台接受用户输入

	//禁止中断

	//载入内核并移交控制权，GDT表，LDT表等都是可以被覆盖的，只需要保留极小一部分在末尾处可用的代码即可，最后使用jmp跳转

	//内核启动后，重置esp指针，开始设置自己的gdt，idt表，重新载入lgdtr,lidtr

	//开始进行自己的大部分初始化工作，完成后就接受用户调度（以任何方式）
}


