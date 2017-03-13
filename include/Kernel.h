
#ifndef Kernel_h
#define Kernel_h

#include <Memory.h>
#include <List.h>	//SimpleMemoryManager
#include <Process.h>
#include <Interrupts.h>

/**
*	A kernel is logically a universal computer resource manager
*	This kernel is designed to be very basic,meaning that it will only contain the minimal collection of interfaces.
*/
class Kernel{
protected:
	~Kernel(); // not allowed building up a kernel in stack
public:
	Kernel();
	Kernel();

	//related to memory allocation
	void* mnew(unsigned int mm_size);//进程本身必须有一个用于储存已经有分配的节点的空间，回收的时候，进程只回收已经分配的空间。 这个空间只能够用于kernel访问
	void  mdelete(void *p,unsigned int mm_size);

	//related to process management
	int createProcess();
	void suspendProcess(int i);
	void resumeProcess(int i);
	void killProcess(int i);

protected:
	MemoryManager mm;
	SimpleMemoryManager<MemoryDescriptor> smm;
	InterruptsManager im;


};


#endif //Kernel_h
