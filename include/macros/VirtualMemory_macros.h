/*
 * VirtualMemory_macors.h
 *
 *  Created on: 2017年3月24日
 *      Author: 13774
 */

#ifndef INCLUDE_MACROS_VIRTUALMEMORY_MACROS_H_
#define INCLUDE_MACROS_VIRTUALMEMORY_MACROS_H_

#include <VirtualMemory.h>

#if defined(CODE32)
//=============function macros
CR3::CR3(u32_t cr3)
{
	*(u32_t*)this=cr3;
}

PDE::PDE(u32_t pde)
{
	*(u32_t*)this=pde;
}

PTEManager*	PDEManager::getPTEManagerRef(int i)
{
	return ptemans[i];
}
void	PDEManager::setPTEManagerRef(int i,PTEManager * pteman)
{
	if(i>=0 && ((size_t)i) < len)
	{
		ptemans[i]=pteman;
	}
}

PTE::PTE(u32_t pte)
{
	*(u32_t*)this=pte;
}

//===class VirtualManager
 int VirtualManager::getL3(int targetPhyAddr)
 {
	 return targetPhyAddr & 0xfff;
 }
 int VirtualManager::getL2(int ptePhyAddr)
 {
	 return (ptePhyAddr & 0xfff) >> 2;
 }
 int VirtualManager::getL1(int pdePhyAddr)
 {
	 return (pdePhyAddr & 0xfff) >> 2;
 }
 int VirtualManager::getLinearAddress(int pdePhyAddr,int ptePhyAddr,int targetPhyAddr)
 {
	 int l1 = getL1(pdePhyAddr) << 22;
	 int l2 = getL2(ptePhyAddr) << 12;
	 int l3 = getL3(targetPhyAddr);

//	 Kernel::printer->putx("pdePhyAddr=", pdePhyAddr);
//	 Kernel::printer->putx("l1=", l1);
//	 Kernel::printer->putx("ptePhyAddr=", ptePhyAddr);
//	 Kernel::printer->putx("l2=", l2);
//	 Kernel::printer->putx("targetPhyAddr=", targetPhyAddr);
//	 Kernel::printer->putx("l3=", l3);

	 return l1 | l2 | l3;
 }
 void VirtualManager::setVirtualAddress(int pdePhyAddr,int ptePhyAddr,int targetPhyAddr)
 {
	 //set CR3
	 //writeCr3(Kernel::makeCR3(pdePhyAddr));
	 *(int*)pdePhyAddr = Kernel::makePDE(ptePhyAddr);
	 *(int*)ptePhyAddr = Kernel::makePTE(targetPhyAddr);
 }
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

#endif //CODE32 CODE64

#endif /* INCLUDE_MACROS_VIRTUALMEMORY_MACROS_H_ */
