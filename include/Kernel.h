
#ifndef Kernel_h
#define Kernel_h

#include <def.h>
#include <libx2.h>
#include <List.h>	//SimpleMemoryManager
#include <Interrupts.h>
#include <loki/Int2Type.h>
#include <Descriptor.h>
#include <AssociatedMemoryManager.h>

#if defined(CODE32)||defined(CODE64)
/**
 * Problem1:
 * 	How to generate a process ID?
 * 		algorithm 1: sort & find the smallest
 * 		algorithm 2: keep an ordered linked list (space wasted)
 * 		algorithm 3: assume & verify & loop until found O(n^2)
 * 		algorithm 4: lastValid recorded.
 * 			in 	get		If lastValidPID not found,the lastValidPID=maxPID + 1
 * 			in	assign	try
 * 			in	withdraw	record it to the lastValidPID
 *
 */
template <class T>
class KernelSmmWrapper{
protected:
	friend class Kernel;

public:
	AS_MACRO KernelSmmWrapper();
	AS_MACRO ~KernelSmmWrapper();
    AS_MACRO T* getNew();
    AS_MACRO void withdraw(T *t);
};


#include <Process.h> // implementation here

class ProcessManager{
public:
	enum{
		LDT_ITEMS=10
	};
public:
	ProcessManager();
	~ProcessManager();
	Process *createProcess(size_t codeLimit,size_t dataLimit,size_t stackLimit,
			char dpl=SegmentDescriptor::DPL_3);//It will allocate : a TSS area,
							// It will ask for the kernel to allocate a GDT entry for process LDT,
							// assign the
	AS_MACRO TreeNode<Process*>*	createProcessWrapper(Process* p);
	void	setFatherProcess(TreeNode<Process*> *p,TreeNode<Process*> *father);
	AS_MACRO TreeNode<Process*> *	getFatherProcess(TreeNode<Process*> *p);
	TreeNode<Process*>*	getCurrentProcess()const;
	void				swithcNextProcess();
	TreeNode<Process*>*	addNewProcess(size_t codeLimit,size_t dataLimit,size_t stackLimit,
			char dpl=SegmentDescriptor::DPL_3);
	/**
	 * It is not safe
	 */
	DEPRECATED AS_MACRO Process*			getIdelProcess()const;

	/**
	 *  implement '==' as functions is too slow,use '==' instead(in Cache)
	 */
	DEPRECATED static bool pidComparator(unsigned int p1,unsigned int p2);

protected:
	/**
	 * from 2 to INF
	 * after this process,lastValidPID=PID_INVALID
	 */
	unsigned int getNewPid();
	void		releasePid(unsigned int pid);
	Process*	createProcess(unsigned int pid,size_t prcBase,size_t prcStart,size_t codeLimit,size_t dataLimit,size_t stackLimit,
			char dpl=SegmentDescriptor::DPL_3);
	void		createIdleProcess();
	void	invokeProcess(Process* p);
	TreeNode<Process*>*		getByPid(unsigned int pid);

	/**
	 * point to the tree
	 */
	KernelSmmWrapper<ListNode<TreeNode<Process*>* > >		lksmm;

	KernelSmmWrapper<TreeNode<Process*> >					tksmm;
	LinkedList<TreeNode<Process*>*,KernelSmmWrapper>  		prcsQueue;//for schedule
	Tree<Process*,KernelSmmWrapper> 						prcsTree;
	Process													 *idleProcess;//The special one to ensure that at least one process is running but when there is alive process ,this process
						//should never be run
					//as it's name indicated,only when CPU gets idle,this process is called.
	TreeNode<Process*>										*curProcess;
	unsigned int lastValidPID;
	/**
	 * max pid of currently allocated
	 */
	unsigned int maxPID;
};

/**
 *
 * Design Spirit： Everything done in the kernel and everything in the kernel
*	A kernel is logically a universal computer resource manager
*	This kernel is designed to be very basic,meaning that it will only contain the minimal collection of interfaces.
*/
class Kernel{
public:
	typedef	Kernel											This;
	typedef TreeNode<MemoryDescriptor> 						MmNodeType;
	typedef SimpleMemoryManager<MmNodeType>					SmmType;
	typedef MemoryManager<SimpleMemoryManager>		 		MmType;
	typedef AssociatedMemoryManager<SegmentDescriptor,1>    SegManager;
	enum{
		LDT_ITEMS=10,
		VIDEO_SEL=0x8,
		KERNEL_CS=0x10,
		KERNEL_DS=0x18,
		KERNEL_SS=0x20
	};
	enum{
		GPUI_MEM=0,
		GPUI_PRINT=1
	};
	enum{
		GPUI_MEM_NEW=0,
		GPUI_MEM_DELETE=1
	};
protected://static statement
	//reserve a space for theKernel
	static Kernel *theKernel;

public:
	static Printer *printer;
	static void initTheKernel(Kernel *theKernel);
	AS_MACRO static Kernel* getTheKernel();

protected:
	~Kernel(); // not allowed building up a kernel in stack
public:

	Kernel();
	Kernel(size_t smmStart,size_t smmLimit,
			size_t kmmStart,size_t kmmSize,
			size_t pmmStart,size_t pmmSize,
			size_t pde0_start,size_t pde0_size,
			size_t pte0_start,size_t pte_size,
			size_t	gdtnstart,size_t gdttstart,size_t gdtitems,int *gusedList,size_t gusedLen,
			size_t	idtnstart,size_t idttstart,size_t idtitems,int *iusedList,size_t iusedLen
			);//只需要指定内存管理特性

	//related to memory allocation
	AS_MACRO void* mnewKernel(size_t mmStart,size_t mmSize);
	AS_MACRO void* mnewKernel(size_t mmSize);//进程本身必须有一个用于储存已经有分配的节点的空间，回收的时候，进程只回收已经分配的空间。 这个空间只能够用于kernel访问
	AS_MACRO void* mnewKernelAlign(size_t mmSize,size_t alignment=1);
	AS_MACRO void  mdeleteKernel(void *p,size_t mmSize);
	AS_MACRO void mdeleteKernel(void* p);

	AS_MACRO void* mnewProcess(size_t mmStart,size_t mmSize);
	AS_MACRO void* mnewProcess(size_t mmSize);
	AS_MACRO void* mnewProcessAlign(size_t mmSize,size_t alignment=1);
	AS_MACRO void mdeleteProcess(void *p,size_t mmSize);
	AS_MACRO void mdeleteProcess(void *p);




	//related to process management
	AS_MACRO void	switchNextProcess();
	AS_MACRO TreeNode<Process*>* addNewProcess(size_t codeLimit,size_t dataLimit,size_t stackLimit,
			char dpl=SegmentDescriptor::DPL_3);
	void suspendProcess(TreeNode<Process*>* wp);
	void resumeProcess(TreeNode<Process*>* wp);
	void killProcess(TreeNode<Process*>* wp);

	//==========get arguments
	size_t	getKernelMMBase()const;
	size_t getProcessMMBase()const;

	//===========
	/**
	 * -1 means no free space
	 */
	int newgdt(char* baseaddr=0,int limit=0,char g=SegmentDescriptor::G_1B,char type=SegmentDescriptor::TYPE_U_DATA,char dpl=SegmentDescriptor::DPL_0,
				char s=SegmentDescriptor::S_SYSTEM,char b=SegmentDescriptor::B_UPPER_BOUND32,char p=SegmentDescriptor::P_PRESENT);
	AS_MACRO void markGdtUsed(int index);
	AS_MACRO void markGdtUnused(int index);
	AS_MACRO void markIdtUsed(int index);
	AS_MACRO void markIdtUnused(int index);
	AS_MACRO SegManager& getGdtm();
	AS_MACRO SegManager& getIdtm();
	int newidt();

	//=============virtual memory
	/**
	 * prepare to visit physical address,that is absolute address
	 *
	 * @param  physical
	 * @param  size
	 */
	AS_MACRO int preparePhysicalMap(size_t physical,size_t size);
	INCOMPLETE void destroyPhysicalMap();


//protected:
public:
	/**
	 * This should be deprecated/obsolete, AssociatedMemoryManager is better
	 *
	 * Must be defined first,cause it will be used later
	 */
	SmmType smm; // size = ptr

	MmType			kernelMM;//size = ptr
	MmType			processMM;// size = ptr
	InterruptsManager intm;
	SegManager gdtm; //size = ptr
	SegManager idtm;// size =ptr

	ProcessManager	processMan;//this one relies on gdtm,kernelMM,processMM

	CR3 cr3;
	PDEManager	pdeman; //PDE manager




};

#endif


#endif //Kernel_h
