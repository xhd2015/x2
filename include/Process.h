#ifndef Process_h
#define Process_h

#include <libx2.h>
#include <Memory.h>
#include <List.h>
#include <TSS.h>
#include <AssociatedMemoryManager.h>
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
			size_t linearBase,size_t processBase/*whole RAM!!*/,size_t codeStart,size_t codeLimit,size_t dataLimit,size_t stackLimit,
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
};



#endif

//==========function macros
#if defined(CODE32)||defined(CODE64)

//=====class:Process
int	Process::getTSSSel()const
{
	return this->tssSel;
}
unsigned int	Process::getPid()const
{
	return this->pid;
}
void Process::setStack0(size_t stack0)
{
	ptss->ESP0 = stack0;
}

void Process::setStack3(size_t stack3)
{
	ptss->ESP = stack3;
}

void Process::setSSSel0(int sel)
{
	ptss->SS0 = sel;
}

void Process::setSSSel3(int sel)
{
	ptss->SS = sel;
}

void Process::setCSSel(int sel)
{
	ptss->CS = sel;
}

void Process::setCodeStart(size_t start)
{
	ptss->EIP = start;
}
size_t	Process::getCodeStart()const
{
	return this->ptss->EIP;
}

int	Process::getLDTSsel()const
{
	return this->ldtSel;
}
int Process::getSatus() const
{
	return this->status;
}

void Process::setStatus(
	int status)
{
	this->status=status;
}
int	Process::getStatus()const
{
	return this->status;
}
size_t Process::getProcessBase()const
{
	return this->processBase;
}

#endif


#endif //Process_h
