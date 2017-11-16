
#include <Kernel.h>
#include <Process.h>
#include <AssociatedMemoryManager.h>
#include <MemoryManager.h>
#include <List.h>

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
		size_t linearBase,size_t processBase/*whole RAM!!*/,size_t codeStart,size_t bodySize,
		size_t codeLimit,size_t dataLimit,size_t stackLimit,
		char dpl
):
pid(pid),
ErrorSaver(This::ERROR_NO_ERROR),
ldtm(ldtNStart,ldtTStart,ldtNItems,true),
ptss(ptss),
status(This::STATUS_READY),
linearBase(linearBase),
processBase(processBase),
baseKsmm(),
baseMM(&this->baseKsmm,linearBase+processBase,bodySize,false)
{


		char *pbase=(char*)(linearBase+processBase);
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

		//==============init LDT
		/**
		 *  1 		2 		3
		 *  code	data	stack
		 */
		this->ldtm.unfreeNode(0); //---> 0 is not used also
		this->ldtm.unfreeNode(1);
		this->ldtm.unfreeNode(2);
		this->ldtm.unfreeNode(3);
		this->ldtm.unfreeNode(4);



		char GSEL;


		SELECT_SCALE(codeLimit,GSEL);
		new (this->ldtm.getTarget(1)) SegmentDescriptor(pbase,codeLimit, GSEL,
				SegmentDescriptor::TYPE_U_CODE_NONCONFORMING,
				/*SegmentDescriptor::DPL_3*/dpl,
				SegmentDescriptor::S_USER,
				SegmentDescriptor::B_UPPER_BOUND32,
				SegmentDescriptor::P_PRESENT
		);
		SELECT_SCALE(dataLimit,GSEL);
		new (this->ldtm.getTarget(2)) SegmentDescriptor(pbase,dataLimit, GSEL,
				SegmentDescriptor::TYPE_U_DATA,
				/*SegmentDescriptor::DPL_3*/dpl,
				SegmentDescriptor::S_USER,
				SegmentDescriptor::B_UPPER_BOUND32,
				SegmentDescriptor::P_PRESENT
		);
		SELECT_SCALE(stackLimit,GSEL);
		new (this->ldtm.getTarget(3)) SegmentDescriptor(pbase,stackLimit, GSEL,
				SegmentDescriptor::TYPE_U_STACK,
				/*SegmentDescriptor::DPL_3*/dpl,
				SegmentDescriptor::S_USER,
				SegmentDescriptor::D_OPSIZE32,
				SegmentDescriptor::P_PRESENT
		);
		size_t sysStack=stackLimit/2;
		SELECT_SCALE(sysStack,GSEL);
		new (this->ldtm.getTarget(4)) SegmentDescriptor(pbase,sysStack, GSEL,
				SegmentDescriptor::TYPE_U_STACK,
				0,
				SegmentDescriptor::S_USER,
				SegmentDescriptor::D_OPSIZE32,
				SegmentDescriptor::P_PRESENT
		);

		//=================init TSS
		ptss->CS = Util::makeSel(1, /*SegmentDescriptor::DPL_3*/dpl,1);
		ptss->EIP = codeStart;
		ptss->DS = Util::makeSel(2,/* SegmentDescriptor::DPL_3*/dpl, 1);
		ptss->SS = Util::makeSel(3, /*SegmentDescriptor::DPL_3*/dpl, 1);
		ptss->SS0 = Util::makeSel(4, /*SegmentDescriptor::DPL_3*/0, 1);
		ptss->ESP = stackLimit - 4;
		ptss->ESP0 = sysStack - 4;
		ptss->LDT = this->ldtSel;
		ptss->EFLAGS = 0x246;//0x246;
		CR3 tempcr3(((int)pbase)>>12,PageAttributes::PWT_ALWAYS_UPDATE);
		ptss->CR3 = *(u32_t*)&tempcr3;

}

#endif
