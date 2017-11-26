/*
 * VirtualMemory.cpp
 *
 *  Created on: 2017年3月24日
 *      Author: 13774
 */
#if defined(CODE32)
__asm__(".code32 \n\t");
#endif


#include <VirtualMemory.h>
#include <Kernel.h>

#include <macros/VirtualMemory_macros.h>
#include <macros/Kernel_macros.h>
#include <macros/AssociatedMemoryManager_macros.h>

#include <macros/all.h>


#if defined(CODE32)

CR3::CR3(int base, int pwt, int pcd):
		R0(0),
PWT(pwt),
PCD(pcd),
R1(0),
PDE_BASE(base)
{
}

PDE::PDE(int base, char pwt, char pcd, char rw, char us, char present, char a) :
P(present),
RW(rw),
US(us),
PWT(pwt),
PCD(pcd),
A(a),
R0(0),
R1(0),
R2(0),
PTE_BASE(base)
{
}

PTE::PTE(int base, char pwt, char pcd, char rw, char us, char global, char pat,
		char dirty, char present, char a):
P(present),
RW(rw),
US(us),
PWT(pwt),
PCD(pcd),
A(a),
D(dirty),
PAT(pat),
G(global),
R0(0),
PAGE_BASE(base)
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
	//==ask for a PTE in an existing PDE
	if(size==0 || segman.isEmpty())return -1;

	// DEBUG
	Kernel::printer->putsz("in prepareVisit\n");

	PTE *pte_p1=NULL;
	PDE *pde_p0=NULL;
	bool pde_written=false;

	/**
	 * 确定所需的pte数量
	 */
	size_t nptes=size/(4*1024);
	size_t nbytes=size%(4*1024);
	if(nbytes>0)nptes++;

	// DEBUG
	Kernel::printer->putx("npte = ",nptes);
//	Kernel::printer->putx("pde man len=",len);
//	Kernel::printer->putx("ptemans[0]=",ptemans[0]);
	Kernel::printer->putx("ptemans[1]=",ptemans[1]);
//	Kernel::printer->putx("ptemans[3]=",ptemans[3]);
//	Kernel::printer->putx("narr[0].isFree()",narr[0].isFree());
	Kernel::printer->putx("narr[1].isFree()",narr[1].isFree());
//	Kernel::printer->putx("narr[3].isFree()",narr[3].isFree());



	for(size_t i=0;i<len;i++)//find for existing pdes with enough ptes
	{
		if(i<=3)
		{
			Kernel::printer->putx("i=",i,",");
			Kernel::printer->putx("ptemans[i]=",ptemans[i],",");
			Kernel::printer->putx("left=",ptemans[i]->getLeft(),",");
			Kernel::printer->putx("alloced=",narr[i].isAlloced()," \n");
		}

		if(!narr[i].isAlloced() && ptemans[i]!=NULL)//exist a PDE
		{
//			Kernel::printer->putx("i=",i," ");
//			Kernel::printer->putx("left=",ptemans[i]->getLeft()," \n");
			if(ptemans[i]->getLeft()>=nptes)
			{
				int istart=ptemans[i]->allocContinuousFree(nptes);

				Kernel::printer->putx("istart=",istart);
				if(istart!=-1)//found
				{
					pde_p0=getTarget(i);
					pte_p1=ptemans[i]->getTarget(istart);
					pde_written=true;//如果一个PTEManager不为NULL，那么肯定保证了它的PDE已经指向了第一个PTE
					break;
				}
			}
		}
	}
	Kernel::printer->putx("find pde==NULL?", pde_p0==NULL);

	// TODO 调试下面这段代码，确保正确性
	if(pde_p0==NULL)//not find such pde,then new one for it
	{
		int index=-1;
		pde_p0=this->getNew(index);
		if(index!=-1)
		{
			size_t ptenstart=(size_t)Kernel::getTheKernel()->mnewKernel(nptes  * x2sizeof(PTEManager::NodeType));
			size_t ptetstart=(size_t)Kernel::getTheKernel()->mnewKernelAlign(nptes  * x2sizeof(PTEManager::TargetType),4);
			this->ptemans[index] = (PTEManager*)
					Kernel::getTheKernel()->mnewKernel(x2sizeof(PTEManager));
			if(this->ptemans[index]!=NULL && ptenstart!=0 && ptetstart!=0)
			{
				new (this->ptemans[index]) PTEManager(ptenstart,ptetstart,nptes);
				pte_p1=(PTE*)ptetstart;
			}
		}

	}
//    Util::digitToStr(buf, arrsizeof(buf), (size_t)pde_p0);
//    Util::printStr("pde_p0 is  :");Util::printStr(buf);Util::printStr(" ");
//    Util::digitToHex(buf, 10, (size_t)pte_p1);
//    Util::printStr("pte_p1 is  :");Util::printStr(buf);Util::printStr("\n");
	if(!pde_written) //write pde
	{
		/**
		 * bug : PTE does not align with multiple of 4
		 */
//		new (pde_p0) PDE(  ((((int)pte_p1)&0xfffff000)>>12),PageAttributes::PWT_ALWAYS_UPDATE );//100ebb
		*(int*)pde_p0 = Kernel::makePDE((int)pte_p1);
		pde_written=true;
	}

	//write pte
	for(size_t i=0;i<nptes;i++)
	{
//		 new (pte_p1 + i) PTE(phybase + i,PageAttributes::PWT_ALWAYS_UPDATE);
		*((u32_t*)pte_p1+i) = Kernel::makePTE(phyaddr + i*4*1024);
	}

	if(pte_p1!=NULL && pde_p0!=NULL) //they are all fine
	{
		u32_t lineAddr = VirtualManager::getLinearAddress((int)pde_p0, (int)pte_p1, phyaddr);
		int	 	selIndex;
		SegmentDescriptor *descr=segman.getNew(selIndex);//there is enough for one selector
		if(selIndex != -1)
		{
			new (descr) SegmentDescriptor((char*)lineAddr,size - 1,
					SegmentDescriptor::G_1B,SegmentDescriptor::TYPE_U_DATA,0);//for dpl=0 only
			Kernel::printer->putsz("return from good\n");
		}



//		CR3 curCr3=VirtualManager::getCr3();
//		u32_t icr3=*(u32_t*)&curCr3;
//		size_t pde_index = (((int)pde_p0) -	((icr3 & 0xfffff000) ))>>2;
//		size_t pte0_index = (((int)pte_p1)&0xfff)>>2;
//
//		size_t offset = phyaddr & 0xfff;
//
//		u32_t lbaseaddr= (pde_index << 22)|(pte0_index<<12)|offset;
//		int	 	selIndex;
//		SegmentDescriptor *descr=segman.getNew(selIndex);//there is enough for one selector
//		new (descr) SegmentDescriptor((char*)lbaseaddr,size - 1,
//				SegmentDescriptor::G_1B,SegmentDescriptor::TYPE_U_DATA,0);//for dpl=0 only


		return selIndex;
	}
	return -1;
}


int	PDEManager::allocPDE(size_t n_pte)
{
	if(curAllocedSize == len || ptemans == NULL )return -1;
	int index;
	PDEManager::TargetType* targetPDE=getNew(index);//alloced

	if(index!=-1) // alloc ptes
	{
		PTEManager *pteman =(PTEManager *) Kernel::getTheKernel()->mnewKernel(x2sizeof(PTEManager));
		// EFF 4*1024,这个要求似乎有点高
		PTE*		ptes = (PTE*)Kernel::getTheKernel()->mnewKernelAlign(x2sizeof(PTE)*n_pte, 4*1024); //对齐到4KB区开始
		PTEManager::NodeType*	ptesAssocNodes =(PTEManager::NodeType*) Kernel::getTheKernel()->mnewKernel(x2sizeof(PTEManager::NodeType) * n_pte);
		if(pteman == NULL || ptes == NULL || ptesAssocNodes==NULL)
			goto Failed;

		new (pteman) PTEManager((int)ptesAssocNodes,(int)ptes, n_pte);

		setPTEManagerRef(index, pteman); //设置相应的指针
		return index;

		Failed:
			withdraw(targetPDE);
			if(pteman!=NULL) Kernel::getTheKernel()->mdeleteKernel(pteman, x2sizeof(pteman));
			if(ptes != NULL) Kernel::getTheKernel()->mdeleteKernel(ptes,x2sizeof(PTE)*n_pte);
			if(ptesAssocNodes == NULL) Kernel::getTheKernel()->mdeleteKernel(ptesAssocNodes,x2sizeof(PTEManager::NodeType)*n_pte);
			return -1;
	}else
		return -1;
}


void PDEManager::withdrawPDE(size_t i)
{
	if(curAllocedSize==0 || i>=len || getPTEManagerRef(i)==NULL)return;

	PTEManager *pteman=getPTEManagerRef(i);

	size_t n=pteman->getLen();
	if(n==0)return;
	PTEManager::NodeType* allocedNodes=pteman->getNodeAddress();
	PTEManager::TargetType* allocedTargets=pteman->getTarget(0);
	Kernel::getTheKernel()->mdeleteKernel(allocedTargets, n*x2sizeof(PTEManager::TargetType));
	Kernel::getTheKernel()->mdeleteKernel(allocedNodes, n*x2sizeof(PTEManager::NodeType));
	Kernel::getTheKernel()->mdeleteKernel(pteman, x2sizeof(PTEManager));
}

#endif

