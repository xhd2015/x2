/*
 * AssociatedMemoryManager_macros.h
 *
 *  Created on: 2017年3月24日
 *      Author: 13774
 */

#ifndef INCLUDE_MACROS_ASSOCIATEDMEMORYMANAGER_MACROS_H_
#define INCLUDE_MACROS_ASSOCIATEDMEMORYMANAGER_MACROS_H_

#include <AssociatedMemoryManager.h>

//===========function macros
#if defined(CODE32)||defined(CODE64)
//=====class AssociatedMemoryManager<T,MaxArrNum>
template<class T,size_t MaxArrNum>
size_t	AssociatedMemoryManager<T,MaxArrNum>::getArrNum()
{
	return MaxArrNum;
}

//===============class AssociatedMemoryManager<T,1>
template<class T>
bool AssociatedMemoryManager<T,1>::isFull()const
{
    return this->curSize==this->len;
}
template<class T>
bool AssociatedMemoryManager<T,1>::isEmpty()const
{
    return this->curSize==0;
}
template<class T>
size_t AssociatedMemoryManager<T,1>::getLen()const
{
    return this->len;
}
template<class T>
size_t AssociatedMemoryManager<T,1>::getLeft()const
{
	return this->len - this->curSize;
}
template<class T>
size_t AssociatedMemoryManager<T,1>::getCurSize()const
{
    return this->curSize;
}

template<class T>
typename AssociatedMemoryManager<T, 1>::TargetType* AssociatedMemoryManager<T, 1>::getTarget(size_t index)
{
	return (index<this->len)?this->tarr + index:NULL;
}

template<class T>
void AssociatedMemoryManager<T, 1>::freeNode(size_t index)
{
	This::NodeType*	p;
	if( (p=this->getNode(index))!=NULL && !p->isFree())
	{
		p->free();
		this->curSize--;
	}
}
template<class T>
void AssociatedMemoryManager<T, 1>::unfreeNode(size_t index)
{
	This::NodeType *p;
	if( (p=this->getNode(index))!=NULL && p->isFree())
	{
		p->unfree();
		this->curSize++;
	}
}


template<class T>
typename AssociatedMemoryManager<T, 1>::NodeType* AssociatedMemoryManager<T, 1>::getNode(size_t index)
{
	return (index<this->len)?this->narr + index:NULL;
}
/**
 * return len+1 meaning invalid
 * NULL,<,>
 */
template<class T>
size_t AssociatedMemoryManager<T, 1>::getTargetIndex(TargetType* t)const
{
//	ptrdiff_t diff=((char*)t - (char*)this->tarr)/sizeof(*t);
	ptrdiff_t diff=t-this->tarr;
	return (t==NULL || diff<0||diff >= this->len) ?(this->len +1 ):(size_t)diff;

}
template<class T>
size_t		AssociatedMemoryManager<T, 1>::getNodeIndex(NodeType* n)const
{
//	ptrdiff_t diff=((char*)n - (char*)this->narr)/sizeof(*n);
	ptrdiff_t diff=n - this->narr;
	return (n==NULL||diff<0||diff >= this->len) ?(this->len +1 ):(size_t)diff;
}
template<class T>
size_t		AssociatedMemoryManager<T, 1>::getEachSize()
{
	return sizeof(TargetType)+sizeof(NodeType);
}
#endif //CODE32 | CODE64




#endif /* INCLUDE_MACROS_ASSOCIATEDMEMORYMANAGER_MACROS_H_ */
