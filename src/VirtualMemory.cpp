/*
 * VirtualMemory.cpp
 *
 *  Created on: 2017年3月24日
 *      Author: 13774
 */

#include <VirtualMemory.h>
#include <Kernel.h>

#include <macros/VirtualMemory_macros.h>
#include <macros/Kernel_macros.h>
#include <macros/AssociatedMemoryManager_macros.h>

#include <macros/all.h>

#if defined(CODE32)
__asm__(".code32 \n\t");
#endif


CR3::CR3(int base, int pwt, int pcd):
PDE_BASE(base),
PWT(pwt),
PCD(pcd),
R0(0),
R1(0)
{
}

PDE::PDE(int base, char pwt, char pcd, char rw, char us, char present, char a) :
PTE_BASE(base),
PWT(pwt),
PCD(pcd),
RW(rw),
US(us),
P(present),
A(a),
R0(0),
R1(0),
R2(0)
{
}

PTE::PTE(int base, char pwt, char pcd, char rw, char us, char global, char pat,
		char dirty, char present, char a):
PAGE_BASE(base),
PWT(pwt),
PCD(pcd),
PAT(pat),
D(dirty),
RW(rw),
US(us),
G(global),
P(present),
A(a),
R0(0)
{
}


PDEManager::PDEManager() {
}

PDEManager::PDEManager(size_t nstart, size_t tstart, size_t ptemStart,
		size_t len, bool doinit, int* usedList, size_t usedLen):
Father(nstart,tstart,len,doinit,usedList,usedLen),
ptemstart(ptemStart)
{
}

PDEManager::~PDEManager() {
}


/**
 * Suppose in process idle
 */
int PDEManager::prepareVisitPhysical(u32_t phyaddr, size_t size,
		SegManager& segman) {
	char buf[10];
	//==ask for a PTE in an existing PDE
	if(size==0 || segman.isEmpty())return -1;
	PTE *pte_p1=NULL;
	PDE *pde_p0=NULL;
	bool pde_written=false;
	size_t nptes=size/(4*1024);
	size_t nbytes=size%(4*1024);
	if(nbytes>0)nptes++;
    Util::digitToStr(buf, arrsizeof(buf), (size_t)nptes);
//    Util::printStr("pte number is  :");Util::printStr(buf);Util::printStr(" ");

	for(size_t i=0;i<this->len;i++)//find for existing pdes with enough ptes
	{
		if(!this->narr[i].isFree() && this->ptemans[i]!=NULL)//exist a PDE
		{
			if(this->ptemans[i]->getLeft()>=nptes)
			{
				int istart=this->ptemans[i]->findContinuousFree(nptes);
				if(istart!=-1)//found
				{
					pde_p0=this->getTarget(i);
					pte_p1=this->ptemans[i]->getTarget(istart);
					pde_written=true;
				}
			}
		}
	}
	if(pde_p0==NULL)//not find such pde,then new one for it
	{
		int index=-1;
		pde_p0=this->getNew(index);
		if(index!=-1)
		{
			size_t ptenstart=(size_t)Kernel::getTheKernel()->mnewKernel(nptes  * sizeof(PTEManager::NodeType));
			size_t ptetstart=(size_t)Kernel::getTheKernel()->mnewKernelAlign(nptes  * sizeof(PTEManager::TargetType),4);
			this->ptemans[index] = (PTEManager*)
					Kernel::getTheKernel()->mnewKernel(sizeof(PTEManager));
			if(this->ptemans[index]!=NULL && ptenstart!=0 && ptetstart!=0)
			{
				new (this->ptemans[index]) PTEManager(ptenstart,ptetstart,nptes);
				pte_p1=(PTE*)ptetstart;
			}
		}

	}
//    Util::digitToStr(buf, arrsizeof(buf), (size_t)pde_p0);
//    Util::printStr("pde_p0 is  :");Util::printStr(buf);Util::printStr(" ");
    Util::digitToHex(buf, 10, (size_t)pte_p1);
    Util::printStr("pte_p1 is  :");Util::printStr(buf);Util::printStr("\n");
	if(!pde_written) //write pde
	{
		Util::insertMark(0x2333ebb);
		/**
		 * bug : PTE does not align with multiple of 4
		 */
		new (pde_p0) PDE(  ((((int)pte_p1)&0xfffff000)>>12),PageAttributes::PWT_ALWAYS_UPDATE );//100ebb
		pde_written=true;
	}
					//write pte
	int phybase=(phyaddr & 0xfffff000)>>12;
	for(int i=0;i<nptes;i++)
	{
		 new (pte_p1 + i) PTE(phybase + i,PageAttributes::PWT_ALWAYS_UPDATE);
	}

	if(pte_p1!=NULL && pde_p0!=NULL) //they are all fine
	{
		CR3 curCr3=VirtualManager::getCr3();
		u32_t icr3=*(u32_t*)&curCr3;
		size_t pde_index = (((int)pde_p0) -	((icr3 & 0xfffff000) ))>>2;
		size_t pte0_index = (((int)pte_p1)&0xfff)>>2;
		Util::insertMark(0x2333ebd);
		size_t offset = phyaddr & 0xfff;

		u32_t lbaseaddr= (pde_index << 22)|(pte0_index<<12)|offset;
		int	 	selIndex;
		SegmentDescriptor *descr=segman.getNew(selIndex);//there is enough for one selector
		new (descr) SegmentDescriptor((char*)lbaseaddr,size - 1,
				SegmentDescriptor::G_1B,SegmentDescriptor::TYPE_U_DATA,0);//for dpl=0 only

		return selIndex;
	}
	return -1;
}

