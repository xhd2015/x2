/*
 * AssociatedMemoryManager.cpp
 *
 *  Created on: 2017年3月19日
 *      Author: 13774
 */

#include <AssociatedMemoryManager.h>
#include <MemoryManager.h>

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
	for(int i=0;i<MaxArrNum;i++)
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
	for(int i=0;i<MaxArrNum;i++)
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
nstart(0),tstart(0),len(0),curSize(0),lastIndex(0)
{
}
template<class T>
AssociatedMemoryManager<T, 1>::AssociatedMemoryManager(size_t nstart,size_t tstart,size_t len,bool doinit,int *usedList,size_t usedLen):
nstart(nstart),tstart(tstart),len(len),
curSize(usedLen),lastIndex(0)
{
	if(doinit)
	{
		for(int i=0;i<this->len;i++)
		{
			narr[i].free();
		}
	}
	if(usedList)
	{
		for(size_t i=0;i<usedLen;i++)
		{
			this->narr[usedList[i]].unfree();
		}
	}

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
        for(int i=0;i!=this->len;i++)
        {
            if(this->narr[this->lastIndex].isFree())
            {
                rt=&this->tarr[this->lastIndex];
                (this->narr[this->lastIndex]).unfree();
                this->curSize++;
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
        this->curSize--;
        this->lastIndex = index;
    }
}

template<class T>
int AssociatedMemoryManager<T, 1>::findContinuousFree(size_t n) const
{
	const size_t len=this->len;
	if(len - this->curSize < n)return -1;
	size_t curCon=0;

	for(int i=0;len -i >= (int)n;i++)
	{
		if(this->narr[i].isFree())
		{
			while(len - i >= (int)(n - curCon) && this->narr[i++].isFree())curCon++;
			if(curCon==n)
			{
				return i - curCon;
			}else{
				i--;
				curCon=0;
			}
		}
	}
	return -1;
}
