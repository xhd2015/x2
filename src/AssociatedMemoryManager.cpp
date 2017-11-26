/*
 * AssociatedMemoryManager.cpp
 *
 *  Created on: 2017年3月19日
 *      Author: 13774
 */

#include <AssociatedMemoryManager.h>
#include <MemoryManager.h>
#include <def.h>

#include <macros/all.h>

#if defined(CODE32)
__asm__(".code32 \n\t");
#endif

//===========template instantiation
#if defined(CODE32)
#include <Descriptor.h>
#include <VirtualMemory.h>
	template class AssociatedMemoryManager<SegmentDescriptor,1>;
	template class AssociatedMemoryManager<SegmentDescriptor,10>;
	template class AssociatedMemoryManager<PTE,1>;
	template class AssociatedMemoryManager<PDE,1>;
#endif

//========== class AssociatedMemoryManager<T,MaxArrNum>
template<class T, size_t MaxArrNum>
AssociatedMemoryManager<T,MaxArrNum>::AssociatedMemoryManager():
lastMan(0)
{
}

template<class T, size_t MaxArrNum>
AssociatedMemoryManager<T,MaxArrNum>::~AssociatedMemoryManager() {
}

template<class T, size_t MaxArrNum>
typename AssociatedMemoryManager<T,MaxArrNum>::TargetType* AssociatedMemoryManager<T,MaxArrNum>::getNew()
{
	for(size_t i=0;i<MaxArrNum;i++)
	{
		if(!this->manArrs[this->lastMan].isFull())
		{
			return this->manArrs[this->lastMan].getNew();
		}else{
			this->lastMan = (this->lastMan+1)%MaxArrNum;
		}
	}
	return NULL;
}

template<class T, size_t MaxArrNum>
void AssociatedMemoryManager<T,MaxArrNum>::withraw(TargetType* t)
{
	for(size_t i=0;i<MaxArrNum;i++)
	{
		size_t index=this->manArrs[i].getTargetIndex(t);
		if(index < this->manArrs[i].getLen())
		{
			this->lastMan = i;
			this->manArrs[i].withdraw(t);
			break;
		}
	}
}
template<class T, size_t MaxArrNum>
void			AssociatedMemoryManager<T,MaxArrNum>::setMan(size_t index,size_t nstart,size_t tstart,size_t len,bool doinit,int *usedList,size_t usedLen)
{
	if(index<MaxArrNum)
	{
		new (&this->manArrs[index]) AssociatedMemoryManager<T,1>(nstart,tstart,len,doinit,usedList,usedLen);
	}
}


//============class  AssociatedMemoryManager<T,1>
template<class T>
AssociatedMemoryManager<T, 1>::AssociatedMemoryManager():
nstart(0),tstart(0),len(0),
lastIndex(0),
curAllocedSize(0)
{
}
template<class T>
AssociatedMemoryManager<T, 1>::AssociatedMemoryManager(size_t nstart,size_t tstart,size_t len,bool nodeArrInit,int *usedList,size_t usedLen):
nstart(nstart),
tstart(tstart),
len(len),
lastIndex(0),
curAllocedSize(usedLen)
{
//	Kernel::printer->putsz("in AssociatedMemoryManager init\n");
	if(nodeArrInit)
	{
		for(size_t i=0;i<this->len;i++)
		{
			narr[i].setAlloced(false);
		}
	}
	for(size_t i=0;i<usedLen;i++)
	{
		narr[usedList[i]].setAlloced(true);
	}

//	Kernel::printer->putsz("in AssociatedMemoryManager init return\n");
}
template<class T>
AssociatedMemoryManager<T, 1>::~AssociatedMemoryManager()
{
}
template <class T>
typename AssociatedMemoryManager<T,1>::TargetType *AssociatedMemoryManager<T,1>::getNew()
{
    TargetType *rt=NULL;
    if(!this->isFull())
    {
        for(size_t i=0;i!=this->len;i++)
        {
            if(this->narr[this->lastIndex].isFree())
            {
                rt=&tarr[lastIndex];
                (narr[lastIndex]).unfree();
                this->curAllocedSize++;
                this->lastIndex = (this->lastIndex + 1 ) % this->len;
                break;
            }
            this->lastIndex = (this->lastIndex + 1 ) % this->len;
        }
    }
    return rt;
}

template <class T>
typename AssociatedMemoryManager<T,1>::TargetType *AssociatedMemoryManager<T,1>::getNew(int &index)
{
	index=-1;
	TargetType* rt=this->getNew();
	if(rt)
	{
		index=this->getTargetIndex(rt);
	}
	return rt;
}

template <class T>
void AssociatedMemoryManager<T,1>::withdraw(TargetType *t)
{
	if(this->isEmpty())return;
	size_t index=this->getTargetIndex(t);
	NodeType*	n=NULL;
    if(index < this->len && (n=this->getNode(index))&&!n->isFree())
    {
        n->free(); //如果被标记为可用，就用lastIndex指向之
        this->curAllocedSize--;
        this->lastIndex = index;
    }
}

// EFF 这个算法有重复
template<class T>
int AssociatedMemoryManager<T, 1>::allocContinuousFree(size_t n)
{
	if(len - curAllocedSize < n || n==0 )return -1; //如果剩余数量少于n，直接返回-1

	//从0到 len - n,因为当i=len-n时，剩余恰好n个，再往上查找没有意义
	for(size_t i=0; i<=len-n;i++)
	{
		if(this->narr[i].isFree())
		{
			size_t curCon=0;
			for(size_t j=0;j<n;j++)
			{
				if(narr[i+j].isFree())curCon++;
				else break;
			}
			if(curCon == n)
			{
				for(size_t j=0;j<n;j++)
					allocNode(i+j);
				return i;
			}
		}
	}

	return -1;
}

template<class T>
void AssociatedMemoryManager<T, 1>::allocNode(size_t index)
{
	NodeType *p;
	if( (p=this->getNode(index))!=NULL && !p->isAlloced())
	{
		p->setAlloced(true);
		this->curAllocedSize++;
	}
}
template<class T>
void AssociatedMemoryManager<T, 1>::withdrawNode(size_t index)
{
	NodeType *p;
	if( (p=this->getNode(index))!=NULL && p->isAlloced())
	{
		p->setAlloced(false);
		this->curAllocedSize--;
	}
}
