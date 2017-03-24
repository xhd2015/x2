/*
 * Memory_macros.h
 *
 *  Created on: 2017年3月24日
 *      Author: 13774
 */

#ifndef INCLUDE_MACROS_MEMORY_MACROS_H_
#define INCLUDE_MACROS_MEMORY_MACROS_H_

#include <Memory.h>


//========Function Macro
//===class: LinearSourceDescriptor
LinearSourceDescriptor::LinearSourceDescriptor()
{

}
 LinearSourceDescriptor::LinearSourceDescriptor(size_t start,size_t limit):
 start(start),limit(limit)
 {

 }
 LinearSourceDescriptor::~LinearSourceDescriptor() {
 }
 size_t  LinearSourceDescriptor::getStart()const
 {
    return start;
 }
 size_t LinearSourceDescriptor::getLimit()const
 {
    return limit;
 }
 void  LinearSourceDescriptor::setStart(size_t start)
 {
    this->start=start;
 }
 void  LinearSourceDescriptor::setLimit(size_t limit)
 {
    this->limit=limit;
 }

bool LinearSourceDescriptor::contains(const LinearSourceDescriptor& b)const
{
	return this->contains(b.getStart(),b.getLimit());
}
bool LinearSourceDescriptor::contains(size_t start,size_t limit)const
{
#if defined(CODE64)
//	printf("this->start-start>=limit-this->limit   : (%d >= %d = %d)\n",this->start-start,limit-this->limit,(int)(this->start-start)>=(int)(limit-this->limit));
#endif
	return (this->start<=start)&&((int)(this->start-start)>=(int)(limit-this->limit));

}
bool LinearSourceDescriptor::operator==(const LinearSourceDescriptor& b)const
{

   return this->getStart()==b.getStart() && this->getLimit()==b.getLimit();
}


bool LinearSourceDescriptor::operator!=(const LinearSourceDescriptor& b)const
{
    return ! this->operator==(b);
}
bool LinearSourceDescriptor::isAllocable()const
{
    return true;
}

 //==========class: MemoryDescriptor
 MemoryDescriptor::MemoryDescriptor(size_t start,size_t limit,bool allocable):
LinearSourceDescriptor(start,limit),allocable(allocable)
{

}

 MemoryDescriptor::~MemoryDescriptor() {
 }
void MemoryDescriptor::setAllocable(bool allocable)
{
    this->allocable=allocable;
}

bool MemoryDescriptor::isAllocable()const{
    return allocable;
}

bool MemoryDescriptor::operator==(const MemoryDescriptor& b)const
{
    return this->LinearSourceDescriptor::operator==(b) && this->allocable==b.allocable;

}


bool MemoryDescriptor::operator!=(const MemoryDescriptor& b)const
{
    return ! this->operator==(b);
}

//==============class LinearSourceManager
template <class _LinearSourceDescriptor,template <class> class _NodeAllocator>
const _LinearSourceDescriptor & LinearSourceManager<_LinearSourceDescriptor,_NodeAllocator>::getSpace()const
{
	return this->space;
}

//============class MemoryManager<_DescriptorAllocator>
template<template<class > class _DescriptorAllocator>
size_t MemoryManager<_DescriptorAllocator>::getBase() const {
	return this->root->getData().getStart();
}

template<template<class > class _DescriptorAllocator>
size_t MemoryManager<_DescriptorAllocator>::getLimit() const {
	return this->root->getData().getLimit();
}


#endif /* INCLUDE_MACROS_MEMORY_MACROS_H_ */
