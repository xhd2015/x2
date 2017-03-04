
#ifndef Kernel_h
#define Kernel_h

#include <MemoryManager.h>
#include <List.h>	//SimpleMemoryManager
#include <Process.h>
#include <Interrupts.h>

/**
*	A kernel is logically a universal computer resource manager
*	This kernel is designed to be very basic,meaning that it will only contain the minimal collection of interfaces.
*/
class Kernel{
public:

	//related to memory allocation
	void* mnew(unsigned int mm_size);
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
	ProcessManager pm;


};


#endif //Kernel_h
