
#include <Kernel.h>
#include <Process.h>
#include <AssociatedMemoryManager.h>

#include <macros/all.h>

#if defined(CODE32)
__asm__(".code32 \n\t");
#endif

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
		size_t linearBase,size_t processBase/*whole RAM!!*/,size_t codeStart,size_t codeLimit,size_t dataLimit,size_t stackLimit,
		char dpl
):
pid(pid),
ErrorSaver(This::ERROR_NO_ERROR),
ldtm(ldtNStart,ldtTStart,ldtNItems,true),
ptss(ptss),
status(This::STATUS_READY),
linearBase(linearBase),
processBase(processBase)
{
		//==============init pid & ldt & tss selector
		this->pid = pid;
		this->ldtSel = Util::makeSel(ldtIndex, dpl, 0);
		this->tssSel = Util::makeSel(tssIndex, dpl, 0);

		char *pbase=(char*)(linearBase+processBase);
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
		ptss->CR3 = 0;

}


