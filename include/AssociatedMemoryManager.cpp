/*
 * AssociatedMemoryManager.cpp
 *
 *  Created on: 2017年3月19日
 *      Author: 13774
 */

#include <AssociatedMemoryManager.h>

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
AssociatedMemoryManager<T,MaxArrNum>::TargetType* AssociatedMemoryManager<T,MaxArrNum>::getNew()
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
void			AssociatedMemoryManager<T,MaxArrNum>::setMan(size_t index,size_t nodeStart,size_t nlen,size_t targetStart,size_t len)
{
	if(index<MaxArrNum)
	{
		new (&this->manArrs[index]) AssociatedMemoryManager<T,1>(nodeStart,targetStart,len);
	}
}


//============class  AssociatedMemoryManager<T,1>
template<class T>
AssociatedMemoryManager<T, 1>::AssociatedMemoryManager():
nstart(0),tstart(0),len(0),curSize(0),lastIndex(0)
{
}
template<class T>
AssociatedMemoryManager<T, 1>::AssociatedMemoryManager(size_t nstart,size_t tstart,size_t len):
nstart(nstart),tstart(tstart),len(len),
curSize(0),lastIndex(0)
{
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
void AssociatedMemoryManager<T,1>::withdraw(TargetType *t)
{
	size_t index=t-this->getTargetIndex(t);
    if(index < this->len && !t->isFree())
    {
        t->free(); //如果被标记为可用，就用lastIndex指向之
        curSize--;
        lastIndex = index;
    }
}
