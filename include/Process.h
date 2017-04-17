#ifndef Process_h
#define Process_h

#include <libx2.h>
#include <Memory.h>
#include <List.h>
#include <TSS.h>
#include <AssociatedMemoryManager.h>
#include <VirtualMemory.h>
#include <Descriptor.h>

//class Process;
//template <class T> class KernelSmmWrapper;  //incomplete type,could only be referenced by pointer

//extern template class KernelSmmWrapper<ListNode<TreeNode<Process*>* > >;
//extern template class KernelSmmWrapper<TreeNode<Process*> >;


/**
 * What should reside in the kernel area?
 * Everything that need to be managed by the kernel,should always reside in that area
 * Because of course the kernel can access the whole space,but that ability is given only when allocating space for new process
 * So in a common perspective,the kernel can access a limited space only.So any process-related information should not reside in
 * process itself,but in the kernel space.
 *
 * Is a Process the same with a Task defined by Intel?
 * Yes they could be.Different treats make different designate.
 *
 * To create a Process, theKernel will do:
 * 	1.
 *
 * Memory Allocation is done by manager,not by process
 */

#if defined(CODE32)||defined(CODE64)
extern "C" {
	void idle();
	void process1();
	void process2();
}

class Process
		:public ErrorSaver
{
public:
	typedef Process This;
	typedef AssociatedMemoryManager<SegmentDescriptor,1> SegManager;
	enum{
		RESERVED_PDE_START = 0,
		RESERVED_PDE_NUM=10,
		RESERVED_PTE_START = (RESERVED_PDE_NUM*(sizeof(PDEManager::NodeType) + sizeof(PDEManager::TargetType)) + 4)&0xfffffffc,//it must align with 4
		RESERVED_PTE_NUM=(PMLoader::SECSIZE - RESERVED_PTE_START)/(sizeof(PTEManager::NodeType)+sizeof(PTEManager::TargetType)),
		RESERVED_PTE_MANAGER_START = PMLoader::SECSIZE,
		RESERVED_PTE_MANAGER_NUM = RESERVED_PDE_NUM,
		RESERVED_END = RESERVED_PTE_MANAGER_START + RESERVED_PTE_MANAGER_NUM * sizeof(PTEManager*),

		ERROR_NO_ERROR=0,
		ERROR_NO_ENOUGH_PROCESS_SPACE,
		ERROR_GDT_IS_FULL,
		ERROR_IDT_IS_FULL,
		ERROR_GENERAL,
		PID_IDLE=1,
		PID_INVALID=0,
		STAUTS_RUNNING,
		STATUS_READY,
		STATUS_STOPPED,
	};
public:
	Process();
	Process(
			unsigned int pid,
			TSS*	ptss,int tssIndex,
			size_t ldtNStart,size_t ldtTStart,size_t ldtNItems,int ldtIndex,
			size_t linearBase,size_t processBase/*whole RAM!!*/,size_t codeStart,size_t bodySize,
			size_t codeLimit,size_t dataLimit,size_t stackLimit,
			char dpl=SegmentDescriptor::DPL_3
	);
	~Process();

	AS_MACRO unsigned int	getPid()const;
	AS_MACRO void			setStack0(size_t stack0);
	AS_MACRO void			setStack3(size_t stack3);
	AS_MACRO void			setSSSel0(int sel);
	AS_MACRO void			setSSSel3(int sel);
	AS_MACRO void			setCSSel(int sel);
	AS_MACRO void			setCodeStart(size_t start);
	AS_MACRO size_t			getCodeStart()const;
	AS_MACRO size_t getStart()const;
	AS_MACRO size_t getDataLimit()const;
	AS_MACRO size_t getStackLimit()const;
	AS_MACRO size_t getCodeLimit()const;
	AS_MACRO int	getTSSSel()const;
	AS_MACRO int	getLDTSsel()const;
	AS_MACRO int	getSatus()const;
	AS_MACRO void	setStatus(int status);
	AS_MACRO int	getStatus()const;
	AS_MACRO size_t getProcessBase()const;


protected:
	/**
	 * pid = 0, not valid
	 * pid = 1,idle Process
	 */
	unsigned int pid;
	int			status;
	TSS *ptss;
	int		tssSel;
	int		ldtSel;
	SegManager	ldtm;//size
	size_t		linearBase,processBase;
	KernelSmmWrapper<TreeNode<MemoryDescriptor> *> baseKsmm;
	MemoryManager<KernelSmmWrapper> baseMM;

	PDEManager	pdeman;
};



#endif



#endif //Process_h
