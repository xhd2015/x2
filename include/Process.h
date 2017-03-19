#ifndef Process_h
#define Process_h

#include <Memory.h>
#include <List.h>
#include <TSS.h>
#include <AssociatedMemoryManager.h>
/**
 * What should reside in the kernel area?
 * Everything that need to be managed by the kernel,should always reside in that area
 * Because of course the kernel can access the whole space,but that ability is given only when allocating space for new process
 * So in a common perspective,the kernel can access a limited space only.So any process-related information should not reside in
 * process itself,but in the kernel space.
 */
class Process{


protected:
	unsigned int pid;
	union {char *kernelAccessOnlyAreaStart,*kA;};//or  CPU access only area
	union {char *processAccessAreaStart,*pA;}; //NULL of pA should not be used,thus it is better to be reserved or used as code area
	char *stack0,*stack1,*stack2,*stack3;//for compitable , stack1 and stack2 should always be NULL

	TSS *ptrTss;
	AssociatedMemoryManager<SegmentDescriptor>	ldtm;
};

class ProcessManager{

public:
	Process *createProcess();//It will allocate : a TSS area,
							// It will ask for the kernel to allocate a GDT entry for process LDT,
							// assign the

protected:
	LinkedList<Process*,HighLevelSimpleMemoryManager> prcs;
	Process *idleProcess;//The special one to ensure that at least one process is running but when there is alive process ,this process
						//should never be run
					//as it's name indicated,only when CPU gets idle,this process is called.
};


#endif //Process_h
