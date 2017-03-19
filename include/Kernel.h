
#ifndef Kernel_h
#define Kernel_h

#include <Memory.h>
#include <List.h>	//SimpleMemoryManager
#include <Process.h>
#include <Interrupts.h>
#include <loki/Int2Type.h>

/**
*	A kernel is logically a universal computer resource manager
*	This kernel is designed to be very basic,meaning that it will only contain the minimal collection of interfaces.
*/
class Kernel{
protected://static statement
	//reserve a space for theKernel
	static Kernel *theKernel;
public:
	static void initTheKernel(Kernel *theKernel);
	static Kernel* getTheKernel();

protected:
	~Kernel(); // not allowed building up a kernel in stack
public:

	Kernel();
	Kernel(size_t smmStart,size_t smmLimit);//只需要指定内存管理特性

	//related to memory allocation
	void* mnew(size_t mmStart,size_t mmSize);
	void* mnew(unsigned int mm_size);//进程本身必须有一个用于储存已经有分配的节点的空间，回收的时候，进程只回收已经分配的空间。 这个空间只能够用于kernel访问
	void  mdelete(void *p,unsigned int mm_size);

	//related to process management
	int createProcess();
	int createTheIdlePreocess();//If it is created,do not create it again.The PID must be 0.
	void suspendProcess(int i);
	void resumeProcess(int i);
	void killProcess(int i);

protected:
	MemoryManager<NullType> mm;
	/**
	 * This should be deprecated/obsolete, AssociatedMemoryManager is better
	 */
	SimpleMemoryManager<TreeNode<MemoryDescriptor> > smm;
	InterruptsManager intm;
	AssociatedMemoryManager<SegmentDescriptor> gdtm;
	AssociatedMemoryManager<SegmentDescriptor> idtm;

};



#endif //Kernel_h
