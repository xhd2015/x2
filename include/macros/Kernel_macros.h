/*
 * Kernel_macros.h
 *
 *  Created on: 2017年3月24日
 *      Author: 13774
 */

#ifndef INCLUDE_MACROS_KERNEL_MACROS_H_
#define INCLUDE_MACROS_KERNEL_MACROS_H_

#include <Kernel.h>

//===============function macros
#if defined(CODE32)||defined(CODE64)
//====class : KernelSmmWrapper
template <class T>
KernelSmmWrapper<T>::KernelSmmWrapper()
{}
template <class T>
KernelSmmWrapper<T>::~KernelSmmWrapper()
{}
template <class T>
T* KernelSmmWrapper<T>::getNew()
{
	return (T*)Kernel::getTheKernel()->mnewKernel(sizeof(T));
}
template <class T>
void KernelSmmWrapper<T>::withdraw(T *t)
{
	Kernel::getTheKernel()->mdeleteKernel(t, sizeof(T));
}
//====class:ProcessManager
TreeNode<Process*>*	ProcessManager::createProcessWrapper(Process* p)
{
	return new (this->prcsTree.getSmm()->getNew()) TreeNode<Process*>(p);
}
TreeNode<Process*>*	ProcessManager::getFatherProcess(TreeNode<Process*> *p)
{
	TreeNode<Process*> *pyield;
	return p?
			((pyield=p->getParent())==this->prcsTree.getHead()?NULL:pyield):
			NULL;
}
//Process*	ProcessManager::getIdelProcess()const
//{
//	return this->idleProcess;
//}

//=======class Kernel
Kernel* Kernel::getTheKernel()
{
	return This::theKernel;
}
void* Kernel::mnewKernel(size_t mmStart, size_t mmSize)
{
	return this->kernelMM.mnew(mmStart, mmSize);
}

void* Kernel::mnewKernel(size_t mmSize)
{
//	Util::printf("OK\n");
	return this->kernelMM.mnew(mmSize);
}
void* Kernel::mnewKernelAlign(size_t mmSize,size_t alignment)
{
	return this->kernelMM.mnewAlign(mmSize, alignment);
}

void Kernel::mdeleteKernel(void* p, size_t mmSize)
{
	this->kernelMM.mdelete(p, mmSize);
}
void Kernel::mdeleteKernel(void *p)
{
	this->kernelMM.mdelete(p);
}
void* Kernel::mnewProcess(size_t mmStart, size_t mmSize)
{
	return this->processMM.mnew(mmStart, mmSize);
}

void* Kernel::mnewProcess(size_t mmSize)
{
	return this->processMM.mnew(mmSize);
}
void* Kernel::mnewProcessAlign(size_t mmSize,size_t alignment)
{
	return this->processMM.mnewAlign(mmSize, alignment);
}


void Kernel::mdeleteProcess(void* p, size_t mmSize)
{
	this->processMM.mdelete(p,mmSize);
}
void Kernel::mdeleteProcess(void *p)
{
	this->processMM.mdelete(p);
}
void	Kernel::switchNextProcess()
{
	this->processMan.swithcNextProcess();
}
TreeNode<Process*>* Kernel::addNewProcess(
		size_t codeLimit, size_t dataLimit, size_t stackLimit, char dpl)
{
	return this->processMan.addNewProcess(codeLimit, dataLimit, stackLimit, dpl);
}



void Kernel::markGdtUsed(int index)
{
	this->gdtm.unfreeNode(index);
}
void Kernel::markGdtUnused(int index)
{
	this->gdtm.freeNode(index);
}
void Kernel::markIdtUsed(int index)
{
	this->idtm.unfreeNode(index);
}

void Kernel::markIdtUnused(int index)
{
	this->idtm.freeNode(index);
}

SegManager& Kernel::getGdtm()
{
	return this->gdtm;
}
SegManager& Kernel::getIdtm()
{
	return this->idtm;
}

#endif //CODE32 || CODE64




#endif /* INCLUDE_MACROS_KERNEL_MACROS_H_ */
