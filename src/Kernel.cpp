
#include <MemoryManager.h>
#include <Kernel.h>
#include <PMLoader.h>
#include <IOProgramer.h>
#include <KernelMemoryConfig.h>

#include <macros/all.h>

#if defined(CODE32)
__asm__(".code32 \n\t");
#endif

#if defined(CODE32)
 template class KernelSmmWrapper<TreeNode<MemoryDescriptor> >;
#endif


#if defined(CODE32)
//============class ProcessManager
ProcessManager::ProcessManager():
		lksmm(),
		tksmm(),

		prcsQueue(&this->lksmm),
		prcsTree(&this->tksmm),
curProcess(NULL),
lastValidPID(Process::PID_INVALID),
maxPID(1)
{
//	Kernel::printer->putsz("in ProcessManager init\n\t");
//	Util::printStr("Have I been called?\n"); //Of course you are called

	// TODO 探讨下面这行代码是否有必要
//	this->createIdleProcess();

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

//	Kernel::printer->putsz("before alloc space\n");
//	Kernel::getTheKernel()->dumpInfo();
	size_t prcMMBase = Kernel::getTheKernel()->getProcessMMBase();
	size_t allocedProcessSpace=(size_t)Kernel::getTheKernel()->mnewProcess(maxLimit+1) - prcMMBase;
//	Kernel::printer->putx("processMMBase=",Kernel::getTheKernel()->getProcessMMBase(),", ");
//	Kernel::printer->putx("allocedProcessSpace=",allocedProcessSpace,"\n");
	return this->createProcess(
			this->getNewPid(),
			prcMMBase,
			allocedProcessSpace,
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
	Util::cli();
	ListNode<TreeNode<Process*>* >* lnode;
	if(this->curProcess==NULL)
	{
		Kernel::printer->putsz("curProcess is NULL\n");
		if(this->prcsQueue.isEmpty())
		{

			Kernel::printer->putsz("processQueue is empty\n");
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
		bool curNull=(this->curProcess==NULL);
		if(!curNull)
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
	}else{
		return NULL;
	}
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
	size_t	ldttstart=(size_t)k->mnewKernelAlign(x2sizeof(SegmentDescriptor) * LDT_ITEMS,x2sizeof(SegmentDescriptor)); //必须是8的倍数
	size_t  ldtnstart=(size_t)k->mnewKernel( x2sizeof(Kernel::SegManager::NodeType) * LDT_ITEMS );
	TSS	*tss=(TSS*)k->mnewKernel(x2sizeof(TSS));
//	char saver[10];
//	Util::digitToHex(saver, 10, (size_t)tss);
//	Util::printStr("tss allocated is ");Util::printStr(saver);Util::printStr("\n"); //This is ok

	//在内核中先申请一个Process结构
	Process *process=(Process*)k->mnewKernel(x2sizeof(Process));


	//==========install ldt & tss into GDT   INCOMPLETE
	//在内核GDT表中申请两项，一项用于tss，一项用于ldt
	int tssSz=x2sizeof(TSS)-1;
	int tssIndex=k->newgdt((char*)tss, tssSz, SegmentDescriptor::G_1B, SegmentDescriptor::TYPE_S_TSS_32_AVL, dpl, SegmentDescriptor::S_SYSTEM,
				SegmentDescriptor::RESERVED, SegmentDescriptor::P_PRESENT);
	int ldtIndex=k->newgdt((char*)ldttstart, x2sizeof(SegmentDescriptor) * LDT_ITEMS - 1, SegmentDescriptor::G_1B,SegmentDescriptor::TYPE_S_LDT, dpl,SegmentDescriptor::S_SYSTEM,
				SegmentDescriptor::RESERVED,SegmentDescriptor::P_PRESENT);
	Kernel::printer->putx("process id=",pid);
	Kernel::printer->putx("process tss index=", tssIndex);
	Kernel::printer->putx("process ldt index=", ldtIndex);
	Kernel::getTheKernel()->dumpInfo();

	//==========init Process
	// EFF 为了更加确定地表现每个参数的作用
	size_t processBodySize = dataLimit + 1;
	size_t processCodeStart = stackLimit + 1;
	Util::insertMark(0x225225);
	new (process) Process(
			pid,
			tss,tssIndex,
			ldtnstart,ldttstart, LDT_ITEMS, ldtIndex,
			prcBase,prcStart,processCodeStart,processBodySize,
			codeLimit,dataLimit,stackLimit,
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
	Util::printStr("in invoke ");
	if(!p){
		Util::printStr("p is NULL  ");
		return;
	}
	if(p->getStatus()==Process::STATUS_READY) //use long jmp
	{
//		Util::printStr("before ljmp  ");
		Kernel::printer->putsz("before jmp\n");
		p->setStatus(Process::STAUTS_RUNNING);
		p->dump(Kernel::printer);

		Util::insertMark(0xe249e249);
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
Printer* 	Kernel::printer=NULL;

Kernel::Kernel(
		size_t smmStart,size_t smmLimit,
		size_t kmmStart,size_t kmmSize,size_t usedList[][2],size_t usedLen,
		size_t pmmStart,size_t pmmSize,
		size_t pde0_start,size_t pde0_size,
		size_t pte0_start,size_t pte_size,
		size_t	gdtnstart,size_t gdttstart,size_t gdtitems,int *gusedList,size_t gusedLen,
		size_t	idtnstart,size_t idttstart,size_t idtitems,int *iusedList,size_t iusedLen
		)
:
smm(smmStart,smmLimit),
kernelMM(&smm,kmmStart,kmmSize,usedList,usedLen,false),
processMM(&smm,pmmStart,pmmSize,false),
gdtm(gdtnstart,gdttstart,gdtitems,true,gusedList,gusedLen),
idtm(idtnstart,idttstart,idtitems,true,iusedList,iusedLen),
processMan(),
cr3(makeCR3(pde0_start))
{
	// 主要做的事情：初始化PDE管理器
	//=============[init PDE]=================
//    size_t npdes = pde0_size >> 2;
//
//    size_t nptes0= pte_size >> 2;
	printer->putsz("start init \n");
	dumpInfo();

//	kernelMM.dumpInfo(printer);printer->putsz("\n");
    size_t assocNodeStart = (size_t)this->mnewKernel(pde0_size * x2sizeof(PDEManager::NodeType));
//    printer->putsz("init 1\n");
//	kernelMM.dumpInfo(printer);printer->putsz("\n");

    size_t asscoNodeStartForPTEman0 = (size_t)this->mnewKernel(pte_size * x2sizeof(PTEManager::NodeType));
//    printer->putsz("init 2\n");
//    kernelMM.dumpInfo(printer);printer->putsz("\n");

    size_t asscoNodeStartForPTEman1 = (size_t)this->mnewKernel(KernelMemoryConfig::PTE_1_NUM * x2sizeof(PTEManager::NodeType));
//    printer->putsz("init 3\n");
//    kernelMM.dumpInfo(printer);printer->putsz("\n");

    // 初始化PTEManager[]数组
    size_t ptemstart = (size_t)this->mnewKernel(2 * x2sizeof(PTEManager));// 0 1
    //PTEManager的二级指针
    size_t pptem = (size_t)this->mnewKernel(pde0_size * x2sizeof(PTEManager*));

//    printer->putsz("alloced\n");
    // TODO 增加pde1的参数传递


    // TODO 必须检查PTE
    // TODO 使内核分配足够多的PTEManager，现在仅仅一个
    //内核分配 第3项PTEManager不为空
//    size_t npte3_0 = 20;//分配20个PTE给PDE3,PTE0
//    size_t addedIndex = 3;
//    size_t pte3_0start = (size_t)this->mnewKernelAlign(npte3_0 * x2sizeof(PTE),x2sizeof(PTE));//pte3_0的起始地址
//    size_t assoscNodeStartPTE3_0 = (size_t)this->mnewKernel(npte3_0 * x2sizeof(PTEManager::NodeType)) ;
//    new ((PTEManager*)ptemstart+addedIndex) PTEManager(assoscNodeStartPTE3_0,pte3_0start,npte3_0,true);//全部都未使用
//    *((PDE*)PMLoader::PDE0_START + addedIndex) = Kernel::makePDE(pte3_0start); //向PDE3写入内容

    //内核最初仅仅初始化了一个PTEManager,并且全部的项都是已经使用了的。
    new ((PTEManager*)ptemstart) PTEManager(asscoNodeStartForPTEman0,pte0_start,pte_size,true);
    new ((PTEManager*)ptemstart+1) PTEManager(asscoNodeStartForPTEman1,(size_t)KernelMemoryConfig::mmPTE_1,KernelMemoryConfig::PTE_1_NUM,true);
    for(size_t i=0;i<pte_size;i++) //set PTE managers [0] all used.
    {
    	((PTEManager*)ptemstart)[0].allocNode(i);
    }
    int usedPDEs[]={0}; //System PDE
    new (&pdeman) PDEManager(assocNodeStart,pde0_start,pptem,pde0_size,true,usedPDEs,arrsizeof(usedPDEs));

    // 写入PTE地址到PDE1
    *((int*)KernelMemoryConfig::mmPDE+1)=Kernel::makePDE((int)KernelMemoryConfig::mmPTE_1);

//    printer->putsz("before set ref\n");
    // set pointers
    pdeman.setPTEManagerRef(0, (PTEManager*)ptemstart);
    pdeman.setPTEManagerRef(1, (PTEManager*)ptemstart+1);
}

//decltype(sizeof(0)) get()
//		{
//			return sizeof(0);
//		}
//
//void set(decltype(sizeof(0)) x)
//{
//
//}
//void use()
//{
//	set(0);
//}
size_t	 Kernel::getKernelMMBase()const
{
	return 0;
}
size_t Kernel:: getProcessMMBase()const
{
	return CONFIG_KERNEL_CODE_SIZE + CONFIG_KERNEL_FREE_MEM_SIZE;
}


int Kernel::newgdt(char* baseaddr, int limit, char g,char type, char dpl, char s,
		char b, char p)
{
	int index;
	SegManager::TargetType* pmm = gdtm.getNew(index);

	if(pmm)
	{
		new (pmm) SegmentDescriptor(baseaddr,limit,g,
					type,dpl,s,b,p);
	}
	return index;
}
int	Kernel::getChar()
{
	if(inputBuffer.isEmpty())return EOF;

	InputBufferDataType data=inputBuffer.remove();
	return Keyboard::interpretCharData(data);
}
int Kernel::getRawChar()
{
	if(inputBuffer.isEmpty())return EOF;
	return inputBuffer.remove();
}
void Kernel::dumpInfoInner()const
{
	printer->putsz("Kernel{");
	kernelMM.dumpInfo(printer);
	printer->putsz("}");
}
void Kernel::dumpInfo()const
{
	dumpInfoInner();
	printer->putsz("\n");
}

void Kernel::initTheKernel(Kernel* theKernel)
{
	if(theKernel!=NULL && This::theKernel==NULL)
	{
		This::theKernel=theKernel;
	}
}

#endif
