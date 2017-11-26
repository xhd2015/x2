
#ifndef Kernel_h
#define Kernel_h

#include <def.h>
#include <libx2.h>
#include <List.h>	//SimpleMemoryManager
#include <Interrupts.h>
#include <loki/Int2Type.h>
#include <Descriptor.h>
#include <AssociatedMemoryManager.h>

#if defined(CODE32)
/**
 * 一个符合内存分配器标准的分配器，只能用于内核。
 *
 * 它是对内核内存管理函数的包装，主要满足的是Tree等结构对内存分配器的要求
 *
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
	/**
	 * 根据进程的大小建立进程
	 *
	 * @param codeLimit
	 * @param dataLimit
	 * @param stackLimit
	 * @param dpl
	 *
	 * 进程空间会被分配，各个内核相关的管理项会被建立，如TSS，LDT，GDT等
	 */
	Process *createProcess(size_t codeLimit,size_t dataLimit,size_t stackLimit,
			char dpl=SegmentDescriptor::DPL_3);//It will allocate : a TSS area,
							// It will ask for the kernel to allocate a GDT entry for process LDT,
							// assign the
	/**
	 * 建立一个指向Process*的TreeNode<Process*>
	 */
	AS_MACRO TreeNode<Process*>*	createProcessWrapper(Process* p);
	void	setFatherProcess(TreeNode<Process*> *p,TreeNode<Process*> *father);
	AS_MACRO TreeNode<Process*> *	getFatherProcess(TreeNode<Process*> *p);
	TreeNode<Process*>*	getCurrentProcess()const;
	void				swithcNextProcess();
	/**
	 * 分配进程结构并且将其加入进程树和进程调度队列
	 */
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
	/**
	 * 根据参数建立进程
	 *
	 * @param pid			进程的pid
	 * @param prcBase		进程空间的起始地址
	 * @param prcStart		此次分配的进程应当开始的相对地址，prcStart+prcBase构成了进程的决定地址
	 * @param codeLimit		cs段的大小
	 * @param dataLimit		ds段的大小
	 * @param stackLimit	ss段的大小
	 * @param dpl			级别，默认是3，也就是用户空间
	 *
	 *
	 * 建立进程后，进程处于就绪状态
	 */
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
*
*	内核将内存看成两个部分：
*		内核空间和进程空间
*	内核空间用于内核的各种数据结构存储和分配
*	进程空间用于载入进程
*
*	内核应当仅仅包含那些最基础最常用的结构或功能，其他的以模块的形式提供
*	凡是最基础最常用的结构或功能，必须放到内核中
*/
class Kernel{
public:
	typedef	Kernel											This;
	typedef TreeNode<MemoryDescriptor> 						MmNodeType;
	typedef SimpleMemoryManager<MmNodeType>					SmmType;
	typedef SmmType::FullNode								FullMMNodeType; //使用这个结构来计算占用空间的大小
	typedef MemoryManager<SimpleMemoryManager>		 		MmType;
	typedef AssociatedMemoryManager<SegmentDescriptor,1>    SegManager;
	/**
	 * 键盘缓冲区的存储数据类型
	 * 低8位为键盘的输入码，高8位的信息参见IOProgrammer::Keyboard的定义和说明
	 */
	typedef u16_t											InputBufferDataType;
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
	enum{
		EOF=0xffffffff,/*8位，16位通用的EOF*/
	};
protected://static statement
	//reserve a space for theKernel
	static Kernel *theKernel;

public:
	static Printer *printer;
	static void initTheKernel(Kernel *theKernel);
	AS_MACRO static Kernel* getTheKernel();
	AS_MACRO static int		makeCR3(int pdePhyAddr,int controlWord_L12=0b11000);
	/**
	 * @param pteLineAddr		pte线性地址
	 * @param controlWord_L12	控制字的低12位
	 */
	AS_MACRO static int		makePDE(int ptePhyAddr,int controlWord_L12=0b11011);

	/**
	 *
	 */
	AS_MACRO static int		makePTE(int targetPhyAddr,int controlWord_L12=0b100011011);

protected:
	~Kernel(); // not allowed building up a kernel in stack
public:

	Kernel();
	/**
	 *
	 * @param pde0_start	PDE0的起始地址
	 * @param pde0_size		PDE的项数
	 */
	Kernel(size_t smmStart,size_t smmLimit,
			size_t kmmStart,size_t kmmSize,size_t usedList[][2],size_t usedLen,
			size_t pmmStart,size_t pmmSize,
			size_t pde0_start,size_t pde0_size,
			size_t pte0_start,size_t pte_size,
			size_t	gdtnstart,size_t gdttstart,size_t gdtitems,int *gusedList,size_t gusedLen,
			size_t	idtnstart,size_t idttstart,size_t idtitems,int *iusedList,size_t iusedLen
			);//只需要指定内存管理特性

	//related to memory allocation
	/**
	 * 在内核空间分配内存
	 */
	AS_MACRO void* mnewKernel(size_t mmStart,size_t mmSize);
	/**
	 * 在内核空间分配内存
	 */
	AS_MACRO void* mnewKernel(size_t mmSize);//进程本身必须有一个用于储存已经有分配的节点的空间，回收的时候，进程只回收已经分配的空间。 这个空间只能够用于kernel访问
	/**
	 * 在内核空间分配内存，按参数对齐
	 */
	AS_MACRO void* mnewKernelAlign(size_t mmSize,size_t alignment=1);
	AS_MACRO void  mdeleteKernel(void *p,size_t mmSize);
	AS_MACRO void mdeleteKernel(void* p);

	AS_MACRO void* mnewProcess(size_t mmStart,size_t mmSize);
	/**
	 * 在进程空间分配内存
	 */
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
	/**
	 *  内核空间的起始地址，一般是0
	 */
	size_t	getKernelMMBase()const;
	/**
	 * 	进程空间的起始地址，一般在内核结束处
	 */
	size_t getProcessMMBase()const;

	//===========
	/**
	 * -1 means no free space
	 *
	 *
	 */
	int newgdt(
				char* baseaddr=0,
				int limit=0,
				char g=SegmentDescriptor::G_1B,
				char type=SegmentDescriptor::TYPE_U_DATA,
				char dpl=SegmentDescriptor::DPL_0,
				char s=SegmentDescriptor::S_USER,char b=SegmentDescriptor::B_UPPER_BOUND32,char p=SegmentDescriptor::P_PRESENT);
	AS_MACRO void markGdtUsed(int index);
	AS_MACRO void markGdtUnused(int index);
	AS_MACRO void markIdtUsed(int index);
	AS_MACRO void markIdtUnused(int index);
	AS_MACRO SegManager& getGdtm();
	AS_MACRO SegManager& getIdtm();
	AS_MACRO int		getCR3();
	int newidt();
	AS_MACRO int	allocPDE(size_t n_pte);
	/**
	 * @param i 下标，如果是系统下标则不回收(比如0);
	 */
	AS_MACRO void  withdrawPDE(size_t i);

	//=============virtual memory
	/**
	 * prepare to visit physical address,that is absolute address
	 *
	 * @param  physical
	 * @param  size
	 */
	AS_MACRO int preparePhysicalMap(size_t physical,size_t size);

	// TODO 完成这个函数，与preparePhysicalMap配合使用
	INCOMPLETE void destroyPhysicalMap();

	AS_MACRO void setInputBuffer(InputBufferDataType *p,size_t len);
	AS_MACRO Queue<InputBufferDataType>& getInputBuffer();
	/**
	 * 从缓冲区读取一个字符，非阻塞状态；
	 * 当缓冲区没有内容时，返回一个EOF
	 */
	int	getChar();

	/**
	 * 返回一个未经解释的原始输入char类型
	 */
	int getRawChar();

	void dumpInfoInner()const;
	void dumpInfo()const;
protected:
//public:
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

	CR3			 cr3;
	PDEManager	pdeman; //PDE manager

	//输入缓冲区
	Queue<InputBufferDataType> inputBuffer;
};

#endif


#endif //Kernel_h
