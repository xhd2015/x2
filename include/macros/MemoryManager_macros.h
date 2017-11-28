/*
 * Memory_macros.h
 *
 *  Created on: 2017年3月24日
 *      Author: 13774
 */

#ifndef INCLUDE_MACROS_MEMORYMANAGER_MACROS_H_
#define INCLUDE_MACROS_MEMORYMANAGER_MACROS_H_

#include <MemoryManager.h>


//========Function Macro
//===class: LinearSourceDescriptor
template <class __SizeType>
LinearSourceDescriptor<__SizeType>::LinearSourceDescriptor(SizeType start,SizeType limit):
 start(start),limit(limit)
 {

 }

 template <class __SizeType>
LinearSourceDescriptor<__SizeType>::~LinearSourceDescriptor() {
 }

 template <class __SizeType>
 typename LinearSourceDescriptor<__SizeType>::SizeType LinearSourceDescriptor<__SizeType>::getStart()const
 {
    return start;
 }
template <class __SizeType>
typename LinearSourceDescriptor<__SizeType>::SizeType LinearSourceDescriptor<__SizeType>::getLimit()const
 {
    return limit;
 }
template <class __SizeType>
void LinearSourceDescriptor<__SizeType>::setStart(SizeType start)
 {
    this->start=start;
 }
 template <class __SizeType>
 void LinearSourceDescriptor<__SizeType>::setLimit(SizeType limit)
 {
    this->limit=limit;
 }

 template <class __SizeType>
 bool LinearSourceDescriptor<__SizeType>::contains(const LinearSourceDescriptor& b)const
{
	return contains(b.getStart(),b.getLimit());
}
template <class __SizeType>
bool LinearSourceDescriptor<__SizeType>::contains(SizeType start,SizeType limit)const
{
#if defined(CODE64)
//	printf("this->start-start>=limit-this->limit   : (%d >= %d = %d)\n",this->start-start,limit-this->limit,(int)(this->start-start)>=(int)(limit-this->limit));
#endif
	return (this->start<=start)&&( limit<=this->limit  && (start - this->start)<=(this->limit - limit));

}
template <class __SizeType>
bool LinearSourceDescriptor<__SizeType>::operator==(const LinearSourceDescriptor& b)const
{

   return this->getStart()==b.getStart() && this->getLimit()==b.getLimit();
}

template <class __SizeType>
bool LinearSourceDescriptor<__SizeType>::operator!=(const LinearSourceDescriptor& b)const
{
    return ! this->operator==(b);
}
template <class __SizeType>
bool LinearSourceDescriptor<__SizeType>::isAllocable()const
{
    return true;
}

 //==========class: MemoryDescriptor
// TODO 检查下面的声明有什么错误
template <class __SizeType>
MemoryDescriptor<__SizeType>::MemoryDescriptor(__SizeType start,__SizeType limit,bool allocable):
LinearSourceDescriptor<__SizeType>(start,limit),allocable(allocable)
{

}




template <class __SizeType>
 MemoryDescriptor<__SizeType>::~MemoryDescriptor() {
 }
template <class __SizeType>
 void MemoryDescriptor<__SizeType>::setAllocable(bool allocable)
{
    this->allocable=allocable;
}

template <class __SizeType>
bool MemoryDescriptor<__SizeType>::isAllocable()const{
    return allocable;
}

template <class __SizeType>
 bool MemoryDescriptor<__SizeType>::operator==(const MemoryDescriptor<__SizeType>& b)const
{
    return this->LinearSourceDescriptor<__SizeType>::operator==(b) && this->allocable==b.allocable;

}


template <class __SizeType>
bool MemoryDescriptor<__SizeType>::operator!=(const MemoryDescriptor<__SizeType>& b)const
{
    return ! this->operator==(b);
}

//==============class LinearSourceManager
template <class _LinearSourceDescriptor,template <class> class _NodeAllocator,typename __SizeType>
const _LinearSourceDescriptor & LinearSourceManager<_LinearSourceDescriptor,_NodeAllocator,__SizeType>::getSpace()const
{
	return this->space;
}

//============class MemoryManager<_DescriptorAllocator>
template<template<class > class _DescriptorAllocator,typename __SizeType>
__SizeType MemoryManager<_DescriptorAllocator,__SizeType>::getBase() const {
	return this->root->getData().getStart();
}

template<template<class > class _DescriptorAllocator,typename __SizeType>
__SizeType MemoryManager<_DescriptorAllocator,__SizeType>::getLimit() const {
	return this->root->getData().getLimit();
}


#endif /* INCLUDE_MACROS_MEMORYMANAGER_MACROS_H_ */
