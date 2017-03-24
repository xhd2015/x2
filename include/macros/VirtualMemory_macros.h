/*
 * VirtualMemory_macors.h
 *
 *  Created on: 2017年3月24日
 *      Author: 13774
 */

#ifndef INCLUDE_MACROS_VIRTUALMEMORY_MACROS_H_
#define INCLUDE_MACROS_VIRTUALMEMORY_MACROS_H_

#include <VirtualMemory.h>

//=============function macros
CR3::CR3(u32_t cr3)
{
	*(u32_t*)this=cr3;
}

PDE::PDE(u32_t pde)
{
	*(u32_t*)this=pde;
}

PTE::PTE(u32_t pte)
{
	*(u32_t*)this=pte;
}

//===class VirtualManager
u32_t VirtualManager::getIndex(u32_t phyaddr, u32_t reg) {
	return ((phyaddr - (reg & 0xfffff000))>>2);
}

u32_t VirtualManager::getHighBase(u32_t phyaddr) {
	return (phyaddr & 0xfffff000);
}

CR3 VirtualManager::getCr3() {
	int temp;
	__asm__ __volatile__(
		"mov %%cr3,%%eax \n\t"
		:"=a"(temp)
		:
		:
		);
	return temp;
}

void VirtualManager::writeCr3(const CR3& cr3) {
	__asm__ __volatile__(
			"mov %%eax,%%cr3 \n\t"
			:
			:"a"(cr3)
			 :
			);
}


void VirtualManager::enablePaging()
{
	__asm__(
		"mov %cr0,%eax \n\t"
		"or $0x80000000,%eax \n\t"
		"mov %eax,%cr0 \n\t"
	);
}



#endif /* INCLUDE_MACROS_VIRTUALMEMORY_MACROS_H_ */
