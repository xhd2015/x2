#ifndef Process_h
#define Process_h

#include <libx2.h>
#include <MemoryManager.h>
#include <List.h>
#include <TSS.h>
#include <AssociatedMemoryManager.h>
#include <VirtualMemory.h>
#include <Descriptor.h>
//#include <PMLoader.h>
#include <after_def.h>
#include <Kernel.h>

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


#if defined(CODE32)
extern "C" {
	void idle();
	void process1();
	void process2();
}

#endif

/**
 * 进程描述体
 *
 * 进程主要包括
 */
//下面CODE64只需要使用enum中的常数，作为调试用，其他不需要
#if defined(CODE32)||defined(CODE64)
	class Process
#endif
#if defined(CODE32)
		:public ErrorSaver
#endif

#if defined(CODE32) || defined(CODE64)
		 {
		 public:
			typedef Process This;
#endif

#if defined(CODE32)
	typedef AssociatedMemoryManager<SegmentDescriptor,1> SegManager;
#endif


#if defined(CODE32)||defined(CODE64)
	enum{
		RESERVED_PDE_START = 0,
		RESERVED_PDE_NUM=10,
		RESERVED_PTE_START = (RESERVED_PDE_NUM*(sizeof(PDEManager::NodeType) + sizeof(PDEManager::TargetType)) + 4)&0xfffffffc,//it must align with 4
		RESERVED_PTE_NUM=(CONST_SECSIZE - RESERVED_PTE_START)/(sizeof(PTEManager::NodeType)+sizeof(PTEManager::TargetType)),
		RESERVED_PTE_MANAGER_START = CONST_SECSIZE,
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


		PDE_NUMS=10,
		PTE0_NUMS=20
	};
#endif

#if defined(CODE32)

public:
	Process();
	/**
	 * 初始化进程
	 *
	 * @param pid				进程id
	 * @param ptss				指向对应于该进程的TSS结构
	 * @param tssIndex			TSS结构在内核管理的TSS数组中的下标
	 * @param ldtNStart			LDT协同管理器的Node数组地址，见 {@link AssociatedMemoryManager}
	 * @param ldtTStart			LDT表的地址
	 * @param ldrNItems			LDT的项数
	 * @param ldtIndex			LDT选择子在GDT中的下标
	 * @param absBase			进程空间的绝对起始地址
	 * @param thisPrcBase		本进程的相对于进程空间的地址。absBase+thisPrcBase 构成了进程的绝对地址
	 * @param codeStart			进程代码的相对起始地址(以进程体开始为0计算), 一般假定stackLimit为codeStart的值，即栈区之后就是代码区
	 * @param bodySize			进程体的整体大小
	 * @param codeLimit			cs段大小
	 * @param dataLimit			ds段大小
	 * @param stackLimit		ss段大小
	 * @param dpl				权限
	 *
	 * 注意：一般认为，processBodySize=codeLimit=dataLimit
	 * 					codeStart=stackLimit
	 *
	 */
	Process(
			unsigned int pid,
			TSS*	ptss,int tssIndex,
			size_t ldtNStart,size_t ldtTStart,size_t ldtNItems,int ldtIndex,
			size_t absBase,size_t thisPrcBase/*whole RAM!!*/,size_t codeStart,size_t bodySize,
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
	void	dump(Printer * printer)const;


protected:
	/**
	 * pid = 0, not valid
	 * pid = 1,idle Process
	 */
	unsigned int pid;
	int			status;
	/**
	 * TSS结构的内存地址
	 */
	TSS 	*ptss;

	/**
	 *  tss选择子
	 */
	int		tssSel;

	/**
	 * ldt选择子
	 */
	int		ldtSel;

	SegManager	ldtm;//size

	/**
	 *  进程空间的绝对起始地址
	 */
	size_t		absBase;
	/**
	 *  该进程相对进程空间的偏移
	 */
	size_t		processBase;

	/**
	 * 用于baseMM的一般内存分配器
	 */
	KernelSmmWrapper<TreeNode<MemoryDescriptor> > baseKsmm;

	/**
	 *
	 */
	MemoryManager<KernelSmmWrapper> baseMM;

	/**
	 * 管理PDE项
	 *
	 * 因为进程有自己的CR3值...
	 */
	PDEManager	pdeman;

	/**
	 * 进程建立过程中设置的线性基地址
	 * 用于调试
	 */
	int			genLinearAddr;
#endif //CODE32

#if defined(CODE32) || defined(CODE64)
};
#endif






#endif //Process_h
