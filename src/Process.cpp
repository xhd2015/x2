
#include <Kernel.h>
#include <AssociatedMemoryManager.h>
#include <MemoryManager.h>
#include <List.h>
#include <libx2.h>
#include <PMLoader.h>

#include <macros/all.h>

#if defined(CODE32)
__asm__(".code32 \n\t");
#endif



#if defined(CODE32)
//========
#define SELECT_SCALE(LIMIT,GSEL) ({\
	(GSEL)=SegmentDescriptor::G_1B;\
	if( (LIMIT)>SegmentDescriptor::G_4KB_SCALE){\
		(LIMIT)/=SegmentDescriptor::G_4KB_SCALE;\
		(GSEL)=SegmentDescriptor::G_4KB;\
	}\
})

Process::Process() {
}

/**
 * stack0
 * stack3
 * 	each one has half of the size
 */
Process::Process(
		unsigned int pid,
		TSS*	ptss,int tssIndex,
		size_t ldtNStart,size_t ldtTStart,size_t ldtNItems,int ldtIndex,
		size_t absBase,size_t thisPrcBase/*whole RAM!!*/,size_t codeStart,size_t bodySize,
		size_t codeLimit,size_t dataLimit,size_t stackLimit,
		char dpl
):
		ErrorSaver(This::ERROR_NO_ERROR),
		pid(pid),
ldtm(ldtNStart,ldtTStart,ldtNItems,true),
ptss(ptss),
status(This::STATUS_READY),
absBase(absBase),
processBase(thisPrcBase),
baseKsmm(),
// TODO 恢复下面注释的代码
//baseMM(&this->baseKsmm,absBase+processBase,bodySize,false) ,//用于管理 linearBase+processBase的起始地址
baseMM(),
genLinearAddr(0)
{
		Kernel::printer->clr();
		Kernel::printer->putsz("in porcess init\n");
//		char *absPhyStartAddr =
		char *absPhyStartAddr=(char*)(absBase+processBase);
		if((int)absPhyStartAddr % 4 !=0)
		{
			Kernel::printer->putsz("Sorry,you do no have a 4-byte-alignment process.Kernel Panic\n");
			Util::jmpDie();
		}else{
			Kernel::printer->putsz("Process address align to 4\n");
		}

		//===============init memory manager for the process body(starts from physical base)

		//==============设置PDE PTE CR3
		Kernel *k=Kernel::getTheKernel();
//		int kindex=k->preparePhysicalMap((size_t)pbase,dataLimit + 1);//dataLimit shoud be the biggest
//		int ksel = Util::makeSel(kindex, SegmentDescriptor::DPL_0,0);
		//new (&this->pdeman) ((size_t)pbase,This:：RESERVED_PDE_NUM);//这样做对于内核有什么意义呢？因为毫无疑问只有内核会访问进程中这些区域的数据
		//什么时候需要这些数据？
		//1.任何时候当进程访问（包括执行代码）进程体中的数据时
		//2.当进程申请新的内存时
		//    进程通过某个数据段自己实现这些PDE的修改？
		//	内核在进程空间分配一段物理空间
		//   然后为了进程实现对这些物理地址的访问，进程首先申请一系列连续的PTE，足以访问这些物理地址（连续性访问）
		//	 然后设置PTE的值为物理地址首地址
		//
		//	如果不需要分配新的PDE，则由于当前的PDE中已经足够容纳，所以PDE，PTE都是进程可直接访问的，所以可以无需内核参与即可完成（亦即可以在非中断模式下完成，不需要任何Kernel的数据）
		//  如果需要分配新的PDE，则需要从内核申请一个不在当前进程空间的PTE Manager

		//一个问题是，PDEManager以及PTEManager中指针值该怎么设置？
		//	1.物理地址  -- 则进程不可以访问这些数据
		//  2. tarr为虚假数组，从不访问其内容（全是指针）  narr为真实的内容，在进程的可访问范围内。则此种情况下偏移不重要。

		//如果现在不考虑进程会申请新的内存，只要能够正常访问内存即可


		//==============init pid & ldt & tss selector
		this->pid = pid;
		this->ldtSel = Util::makeSel(ldtIndex, dpl, 0);
		this->tssSel = Util::makeSel(tssIndex, dpl, 0);

		//==============init LDT====
		/**
		 *  0		1 		2 		3		4			5
		 *  NULL	code	data	stack	sysStack	kernelds
		 */
		ldtm.allocNode(0);//---> 0 is not used also
		ldtm.allocNode(1);
		ldtm.allocNode(2);
		ldtm.allocNode(3);
		ldtm.allocNode(4);
		ldtm.allocNode(5);


		int pdePhyAddr=(int)absPhyStartAddr;//
		int pte1PhyAddr=pdePhyAddr + PDE_NUMS * x2sizeof(PDE);
		int startLineAddrOfProcess=VirtualManager::getLinearAddress(pdePhyAddr+x2sizeof(PDE),
				pte1PhyAddr, (int)absPhyStartAddr);


		//set the value of pde0 to point to system pde0.pte0

		Kernel::printer->putsz("setting process pde&pte data\n");
		Kernel::printer->putx("lineAddr=",startLineAddrOfProcess);
//		Kernel::printer->putx("stackLimit=",stackLimit);
//		int temp;

//		Util::enterDs(Util::makeSel(5, 0,0), temp);
		bool needExtraVisit= ( (size_t)absPhyStartAddr >= PMLoader::CODE_LIMIT );
		int selIndex = -1;
		int madeSeg;
		if(needExtraVisit)
		{
			// TODO 修正prepare这个函数
			selIndex= k->preparePhysicalMap((size_t)absPhyStartAddr, 512);
//			selIndex = 5;
			if(selIndex == -1)
			{
				Kernel::printer->putsz("prepare visiting failed.Kernel Panic\n");
				Util::jmpDie();
			}
			madeSeg = Util::makeSel(selIndex, 0, 0);
			Kernel::printer->putx("made sel inex=",selIndex);
		}

		if(needExtraVisit)
		{
			int data=*(int*)0;
			Util::insertMark(0xe138e138);
			Util::setl(madeSeg,0,data);
		}else
			*(int*)pdePhyAddr = *(int*)0; //从系统的pde0复制
//		Util::leaveDs(0, temp);

		ptss->CR3 = Kernel::makeCR3(pdePhyAddr);


		//设置PDE1

		int madePDE1=Kernel::makePDE(pte1PhyAddr);
		if (dpl == 3)
			madePDE1 |= 0b100;
		if(needExtraVisit)
		{
			Util::insertMark(0xe154e154);
			Util::setl(madeSeg,1*x2sizeof(PDE), madePDE1);
			Util::insertMark(0xe156e156);
		}else
			*((int*)pdePhyAddr+1) = madePDE1;

		//设置PDE1. PTE[0~2]
		for(int i=0;i<3;++i)
		{
			int madePte= Kernel::makePTE((int)absPhyStartAddr + i*4*1024);
			if(dpl==3)
				madePte |= 0b100;
			if(needExtraVisit)
			{
				Util::setl(madeSeg,PDE_NUMS*x2sizeof(PDE)+ x2sizeof(PTE)*i, madePte);
			}else
				*((int*)pte1PhyAddr+i)=madePte;
		}
		Kernel::printer->putsz("setting end\n");

		// TODO param 2 也许是错误的，要设置pte的值，但我不知道怎么验证
		int startLineAddrOfKernel = VirtualManager::getLinearAddress(pdePhyAddr,*(int*)0 , 0);

		char GSEL;

		//创建各个LDT项
		SELECT_SCALE(codeLimit,GSEL);
		new (this->ldtm.getTarget(1)) SegmentDescriptor((char*)startLineAddrOfProcess,codeLimit, GSEL,
				SegmentDescriptor::TYPE_U_CODE_NONCONFORMING,
				dpl,
				SegmentDescriptor::S_USER,
				SegmentDescriptor::B_UPPER_BOUND32,
				SegmentDescriptor::P_PRESENT
		);
		SELECT_SCALE(dataLimit,GSEL);
		new (this->ldtm.getTarget(2)) SegmentDescriptor((char*)startLineAddrOfProcess,dataLimit, GSEL,
				SegmentDescriptor::TYPE_U_DATA,
				dpl,
				SegmentDescriptor::S_USER,
				SegmentDescriptor::B_UPPER_BOUND32,
				SegmentDescriptor::P_PRESENT
		);
		SELECT_SCALE(stackLimit,GSEL);
		new (this->ldtm.getTarget(3)) SegmentDescriptor((char*)startLineAddrOfProcess,stackLimit, GSEL,
				SegmentDescriptor::TYPE_U_STACK,
				dpl,
				SegmentDescriptor::S_USER,
				SegmentDescriptor::D_OPSIZE32,
				SegmentDescriptor::P_PRESENT
		);
		size_t sysStackLimit=stackLimit/2;
		SELECT_SCALE(sysStackLimit,GSEL);

		new (this->ldtm.getTarget(4)) SegmentDescriptor((char*)startLineAddrOfProcess,sysStackLimit, GSEL,
				SegmentDescriptor::TYPE_U_STACK,
				0,
				SegmentDescriptor::S_USER,
				SegmentDescriptor::D_OPSIZE32,
				SegmentDescriptor::P_PRESENT
		);

		size_t kerSpaceLimit = PMLoader::CODE_LIMIT;
		SELECT_SCALE(kerSpaceLimit,GSEL);
		new (this->ldtm.getTarget(5)) SegmentDescriptor((char*)startLineAddrOfKernel,kerSpaceLimit, GSEL,
				SegmentDescriptor::TYPE_U_DATA,
				0,
				SegmentDescriptor::S_USER,
				SegmentDescriptor::B_UPPER_BOUND32,
				SegmentDescriptor::P_PRESENT
		);

		genLinearAddr = startLineAddrOfProcess;

		//=================init TSS
		ptss->CS = Util::makeSel(1, /*SegmentDescriptor::DPL_3*/dpl,1);
		ptss->EIP = codeStart;
		ptss->DS = Util::makeSel(2,/* SegmentDescriptor::DPL_3*/dpl, 1);
		ptss->SS = Util::makeSel(3, /*SegmentDescriptor::DPL_3*/dpl, 1);
		ptss->SS0 = Util::makeSel(4, /*SegmentDescriptor::DPL_3*/0, 1);
		ptss->ESP = stackLimit;
		ptss->ESP0 = sysStackLimit ;
		ptss->LDT = this->ldtSel;
		ptss->EFLAGS = 0x246 & 0xfffffdff;//eflags[9]=IF=0

//		dump(Kernel::printer);
//		Util::jmpDie();

}

void	Process::dump(Printer * printer)const
{
	printer->putsz("Process{");
	this->ptss->dumpInfo(printer);
	printer->putsz(",");
	printer->putx("genLineAddr:",genLinearAddr,",");
	printer->putsz("}");

}

#endif
