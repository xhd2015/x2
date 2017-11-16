
#include <MemoryManager.h>
#include <Kernel.h>
#include <PMLoader.h>

#include <macros/all.h>

#if defined(CODE32)
__asm__(".code32 \n\t");
#endif


#if defined(CODE32)
//============class ProcessManager
ProcessManager::ProcessManager():
maxPID(1),lastValidPID(Process::PID_INVALID),curProcess(NULL),
lksmm(),
tksmm(),
prcsQueue(&this->lksmm),
prcsTree(&this->tksmm)
{
//	Util::printStr("Have I been called?\n"); //Of course you are called
	this->createIdleProcess();

}
ProcessManager::~ProcessManager()
{

}
Process* ProcessManager::createProcess(size_t codeLimit,size_t dataLimit,size_t stackLimit,
		char dpl)
{
	//=========allocate for process
//	//==adjust limit,if it is less than 4KB,then make it equal to 4KB ===== DEPRECATED
//	if(codeLimit < SegmentDescriptor::G_4KB_SCALE)codeLimit=SegmentDescriptor::G_4KB_SCALE;
//	if(dataLimit < SegmentDescriptor::G_4KB_SCALE)dataLimit=SegmentDescriptor::G_4KB_SCALE;
//	if(stackLimit < SegmentDescriptor::G_4KB_SCALE)stackLimit=SegmentDescriptor::G_4KB_SCALE;
	//==find the biggest limit
	size_t maxLimit=codeLimit;
	if(dataLimit>maxLimit)maxLimit=dataLimit;
	if(stackLimit>maxLimit)maxLimit=stackLimit;

	return this->createProcess(
			this->getNewPid(),
			Kernel::getTheKernel()->getProcessMMBase(),(size_t)Kernel::getTheKernel()->mnewProcess(maxLimit),
			codeLimit, dataLimit, stackLimit, dpl);
}

void	ProcessManager::setFatherProcess(TreeNode<Process*> *p,TreeNode<Process*> *father)
{
	if(p && father)
	{
		father->addSon(p);
	}
}
void	ProcessManager::swithcNextProcess()
{
	char saver[10];
	__asm__("cli \n\t");
	ListNode<TreeNode<Process*>* >* lnode;
	if(this->curProcess==NULL)
	{
		if(this->prcsQueue.isEmpty())
		{
			Util::insertMark(0x2333);  //this is tested
			this->invokeProcess(idleProcess);
		}else{
			/**
			 *  remove head,get pointer,withdraw node
			 *
			 *  idle-->process1
			 */
			lnode= this->prcsQueue.removeHead();
//			Util::printStr("current is null,remove head from process Queue\n");
//			Util::printStr("process queue size is ");Util::digitToStr(saver, 10, this->prcsQueue.getSize());
//			Util::printStr(saver);
//			Util::printStr("\n");

			this->curProcess = lnode->getData();
			this->curProcess->getData()->setStatus(Process::STATUS_READY);
			this->prcsQueue.getMemoryManager()->withdraw(lnode);


			this->invokeProcess(this->curProcess->getData());
		}
	}else{
		if(!this->prcsQueue.isEmpty())
		{
			this->curProcess->getData()->setStatus(Process::STATUS_READY);
			this->prcsQueue.append(this->curProcess);

//			Util::printStr("current is appended,head is removed from process Queue\n");
//			Util::printStr("current pid is ");Util::digitToStr(saver, 10, this->curProcess->getData()->getPid());
//			Util::printStr(saver);Util::printStr("process queue size is ");Util::digitToStr(saver, 10, this->prcsQueue.getSize());
//			Util::printStr(saver);
//			Util::printStr("\n");


			lnode= this->prcsQueue.removeHead();
			this->curProcess = lnode->getData();
			this->curProcess->getData()->setStatus(Process::STATUS_READY);
//			Util::printStr("new process id is ");Util::digitToStr(saver, 10, this->curProcess->getData()->getPid());
//			Util::printStr(saver);Util::printStr("\n");
			this->prcsQueue.getMemoryManager()->withdraw(lnode);

			this->invokeProcess(this->curProcess->getData());
		}else{
			//do not need to change the process
		}
	}
//	__asm__("sti \n\t");

}
TreeNode<Process*>* ProcessManager::addNewProcess(size_t codeLimit, size_t dataLimit,
		size_t stackLimit, char dpl)
{
	Process *p=this->createProcess(codeLimit, dataLimit, stackLimit, dpl);
	if(p)
	{
		TreeNode<Process*> *newprcs=this->createProcessWrapper(p);
		bool tEmp=this->prcsTree.isEmpty();
		bool cNull=(this->curProcess==NULL);
		if(!cNull)
		{
			this->curProcess->addSon(newprcs);
			if(tEmp) //empty,current is not in tree,add it
			{
				this->prcsTree.addRoot(this->curProcess);
			}
		}else{  //current is NULL,add to root
			this->prcsTree.addRoot(newprcs);
		}
//		Util::printStr("before append\n");
		this->prcsQueue.append(newprcs);
//		char saver[10];
//		Util::digitToStr(saver, 10, this->prcsQueue.getSize());
//		Util::printStr("size now is ");Util::printStr(saver);Util::printStr("\n");
//		Util::printStr("after append\n");
		return newprcs;
	}
	return NULL;
}
//bool ProcessManager::pidComparator(unsigned int p1,unsigned int p2)
//{
//	return p1==p2;
//}
unsigned int ProcessManager::getNewPid()
{
	unsigned int pid;
	if(this->lastValidPID==Process::PID_INVALID)
	{
		pid=++this->maxPID;

//		Util::printStr("new from maxPID+1  ");
	}else{//If the initial lastValidPID is bigger than maxPID,then maxPID should be updated
		pid=lastValidPID;
		lastValidPID=Process::PID_INVALID;
//		Util::printStr("new from lastValid  ");
	}
//	char saver[10];
//	Util::digitToStr(saver, 10, pid);
//	Util::printStr("return new pid is ");Util::printStr(saver);Util::printChar('\n');
	return pid;
}
void ProcessManager::releasePid(unsigned int pid)
{
	if(pid<2 || pid >this->maxPID)return;
	if(pid==this->maxPID)
	{
		this->maxPID--;
	}else if(pid <  this->maxPID && pid!=Process::PID_INVALID){
		this->lastValidPID=pid;
	}
}
Process* ProcessManager::createProcess(unsigned int pid,size_t prcBase,size_t prcStart,size_t codeLimit,size_t dataLimit,size_t stackLimit,
		char dpl)
{
	Kernel *k=Kernel::getTheKernel();

	//=========allocate for tss & ldt
	size_t	ldtsize = Kernel::SegManager::getEachSize() * LDT_ITEMS;
	size_t	ldtnstart=(size_t)k->mnewKernel(ldtsize);
	size_t  ldttstart=ldtnstart + sizeof(Kernel::SegManager::NodeType) * LDT_ITEMS;
	TSS	*tss=(TSS*)k->mnewKernel(sizeof(TSS));
//	char saver[10];
//	Util::digitToHex(saver, 10, (size_t)tss);
//	Util::printStr("tss allocated is ");Util::printStr(saver);Util::printStr("\n"); //This is ok
	Process *process=(Process*)k->mnewKernel(sizeof(Process));


	//==========install ldt & tss into GDT   INCOMPLETE
	int tssIndex=k->newgdt((char*)tss, sizeof(TSS)-1, SegmentDescriptor::G_1B, SegmentDescriptor::TYPE_S_TSS_32_AVL, dpl, SegmentDescriptor::S_SYSTEM,
				SegmentDescriptor::RESERVED, SegmentDescriptor::P_PRESENT);
	int ldtIndex=k->newgdt((char*)ldttstart, ldtsize - 1, SegmentDescriptor::G_1B,SegmentDescriptor::TYPE_S_LDT, dpl,SegmentDescriptor::S_SYSTEM,
				SegmentDescriptor::RESERVED,SegmentDescriptor::P_PRESENT);

	//==========init Process
	new (process) Process(
			pid,
			tss,tssIndex,
			ldtnstart,ldttstart, LDT_ITEMS, ldtIndex,
			prcBase,prcStart,stackLimit,codeLimit,dataLimit,stackLimit,
			dpl
	);
	process->setStatus(Process::STATUS_READY);
	return process;
}
void	ProcessManager::createIdleProcess()
{
	this->idleProcess=this->createProcess(Process::PID_IDLE,Kernel::getTheKernel()->getKernelMMBase(),0,PMLoader::CODE_LIMIT,PMLoader::END_OF_WHOLE_KERNEL, PMLoader::STACK_SIZE, SegmentDescriptor::DPL_0);
	this->idleProcess->setStack0(PMLoader::STACK_SIZE);
	this->idleProcess->setCodeStart((size_t)idle);
	this->idleProcess->setStatus(Process::STAUTS_RUNNING);
	Util::ltr(this->idleProcess->getTSSSel());
	Util::lldt(this->idleProcess->getLDTSsel());

}

/**
 * Only work for single-processor
 */
void	ProcessManager::invokeProcess(Process* p)
{
//	Util::printStr("in invoke ");
	if(!p){
//		Util::printStr("p is NULL  ");
		return;
	}
	if(p->getStatus()==Process::STATUS_READY) //use long jmp
	{
//		Util::printStr("before ljmp  ");
		p->setStatus(Process::STAUTS_RUNNING);
		__asm__ __volatile__(
		"#int $0x3\n\t  #this is just normal \n\t"
		"pushw %%cx \n\t"
		"pushl %%edx \n\t"
		"ljmp *(%%esp) \n\t"
		"popl %%edx \n\t"
		"popw	%%cx \n\t"
		:
		:"c"(p->getTSSSel()),"d"(0)
		:
		);
//		Util::printStr("after ljmp   ");
	}else if(p->getStatus()==Process::STAUTS_RUNNING){//use jmp
//		Util::printStr("in jmp  ");
		__asm__ __volatile__(
				"jmp *%%ebx \n\t"
				:
				:"b"(p->getCodeStart())
				:
		);

	}
//	Util::printStr("in return  ");
}
TreeNode<Process*>*		ProcessManager::getByPid(unsigned int pid)
{
	ListNode<TreeNode<Process*>* > *p=this->prcsQueue.getHead();
	while(p)
	{
		TreeNode<Process*>*		wprcs=p->getData();
		Process*				prcs=wprcs->getData();
		if(prcs->getPid()==pid)
		{
			return wprcs;
		}else{
			p = p->getNext();
		}
	}
	return NULL;
}
//================class Kernel
Kernel*		Kernel::theKernel=NULL;

Kernel::Kernel(
		size_t smmStart,size_t smmLimit,
		size_t kmmStart,size_t kmmSize,
		size_t pmmStart,size_t pmmSize,
		size_t pde0_start,size_t pde0_size,
		size_t pte0_start,size_t pte_size,
		size_t	gdtnstart,size_t gdttstart,size_t gdtitems,int *gusedList,size_t gusedLen,
		size_t	idtnstart,size_t idttstart,size_t idtitems,int *iusedList,size_t iusedLen
		):
smm(smmStart,smmLimit),
kernelMM(&this->smm,kmmStart,kmmSize,false),
processMM(&this->smm,pmmStart,pmmSize,false),
gdtm(gdtnstart,gdttstart,gdtitems,true,gusedList,gusedLen),
idtm(idtnstart,idttstart,idtitems,true,iusedList,iusedLen),
cr3(pde0_start>>12,PageAttributes::PWT_ALWAYS_UPDATE,PageAttributes::PCD_CACHE_DISABLE),
processMan()
{
	//=============[init PDE]=================
    size_t npdes=pde0_size >> 2;
    size_t nptes0= pte_size >> 2;
    size_t assocNodeStart = (size_t)this->mnewKernel(npdes * sizeof(PDEManager::NodeType));
    size_t asscoNodeStartForPTEman = (size_t)this->mnewKernel(nptes0 * sizeof(PTEManager::NodeType));
    size_t ptemstart = (size_t)this->mnewKernel(npdes * sizeof(PTEManager) );

    new ((PTEManager*)ptemstart) PTEManager(asscoNodeStartForPTEman,pte0_start,nptes0); //an array of PTE managers
    for(int i=0;i<nptes0;i++) //set PTE managers [0] all used.
    {
    	((PTEManager*)ptemstart)[0].unfreeNode(i);
    }
    int usedPDEs[]={0};
    new (&this->pdeman) PDEManager(assocNodeStart,pde0_start,ptemstart,npdes,true,usedPDEs,arrsizeof(usedPDEs));
    //==========================================
}
size_t	 Kernel::getKernelMMBase()const
{
	return 0;
}
size_t Kernel:: getProcessMMBase()const
{
	return PMLoader::PROCESS_MM_START;
}


int Kernel::newgdt(char* baseaddr, int limit, char g,char type, char dpl, char s,
		char b, char p)
{
	int index;
	SegManager::TargetType* pmm=this->gdtm.getNew(index);
	if(pmm)
	{
		new (pmm) SegmentDescriptor(baseaddr,limit,g,
					type,dpl,s,b,p);
	}
	return index;
}

void Kernel::initTheKernel(Kernel* theKernel)
{
	if(theKernel!=NULL && This::theKernel==NULL)
	{
		This::theKernel=theKernel;
	}
}

#endif
