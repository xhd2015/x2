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
//==class LinearSourceDescriptor
#define __DEF_Template_LinearSourceDescriptor
#define __DEF_LinearSourceDescriptor LinearSourceDescriptor

__DEF_Template_LinearSourceDescriptor
__DEF_LinearSourceDescriptor::LinearSourceDescriptor(__SizeType start,__SizeType limit):
 start(start),limit(limit)
 {

 }

__DEF_LinearSourceDescriptor::~LinearSourceDescriptor() {
 }

 typename __DEF_LinearSourceDescriptor::__SizeType
 __DEF_LinearSourceDescriptor::getStart()const
 {
    return start;
 }

 typename  __DEF_LinearSourceDescriptor::__SizeType
 __DEF_LinearSourceDescriptor::getLimit()const
 {
    return limit;
 }

 void  __DEF_LinearSourceDescriptor::setStart(__SizeType start)
 {
    this->start=start;
 }
void  __DEF_LinearSourceDescriptor::setLimit(__SizeType limit)
 {
    this->limit=limit;
 }

bool  __DEF_LinearSourceDescriptor::contains(const LinearSourceDescriptor& b)const
{
	return contains(b.getStart(),b.getLimit());
}

bool  __DEF_LinearSourceDescriptor::contains(__SizeType start,__SizeType limit)const
{
#if defined(CODE64)
//	printf("this->start-start>=limit-this->limit   : (%d >= %d = %d)\n",this->start-start,limit-this->limit,(int)(this->start-start)>=(int)(limit-this->limit));
#endif
	return (this->start<=start)&&( limit<=this->limit  && (start - this->start)<=(this->limit - limit));
}
bool  __DEF_LinearSourceDescriptor::operator==(const __LinearSourceDescriptor& b)const
{

   return this->getStart()==b.getStart() && this->getLimit()==b.getLimit();
}
bool  __DEF_LinearSourceDescriptor::operator!=(const __LinearSourceDescriptor& b)const
{
    return ! this->operator==(b);
}
template <class __EnvTransfer>
SerializerPtr<__EnvTransfer>& __DEF_LinearSourceDescriptor::serialize(SerializerPtr<__EnvTransfer> &ptr)const
{
	return ptr << start << limit;
}
template <class __EnvTransfer>
SerializerPtr<__EnvTransfer>& __DEF_LinearSourceDescriptor::deserialize(SerializerPtr<__EnvTransfer> &ptr)
{
	return ptr >> start >> limit;
}
template <class __EnvTransfer>
constexpr size_t __DEF_LinearSourceDescriptor::getSerializitionSize()
{
	return __EnvTransfer::template sizeofHostType<decltype(reinterpret_cast<This*>(nullptr)->start)>()+
			__EnvTransfer::template sizeofHostType<decltype(reinterpret_cast<This*>(nullptr)->limit)>();
}
bool  __DEF_LinearSourceDescriptor::isAllocable()const
{
    return true;
}

#undef __DEF_Template_LinearSourceDescriptor
#undef __DEF_LinearSourceDescriptor




 //==========class: MemoryDescriptor
// TODO 检查下面的声明有什么错误
#define __DEF_Template_MemoryDescriptor
#define __DEF_MemoryDescriptor MemoryDescriptor

__DEF_Template_MemoryDescriptor
__DEF_MemoryDescriptor::MemoryDescriptor(__SizeType start,__SizeType limit,bool allocable):
Super(start,limit),allocable(allocable)
{

}




__DEF_Template_MemoryDescriptor
 __DEF_MemoryDescriptor::~MemoryDescriptor() {
 }
__DEF_Template_MemoryDescriptor
 void __DEF_MemoryDescriptor::setAllocable(bool allocable)
{
    this->allocable=allocable;
}

__DEF_Template_MemoryDescriptor
bool __DEF_MemoryDescriptor::isAllocable()const{
    return allocable;
}

__DEF_Template_MemoryDescriptor
 bool __DEF_MemoryDescriptor::operator==(const __MemoryDescriptor& b)const
{
    return this->__LinearSourceDescriptor::operator==(b) && this->allocable==b.allocable;

}


__DEF_Template_MemoryDescriptor
bool __DEF_MemoryDescriptor::operator!=(const __MemoryDescriptor& b)const
{
    return ! this->operator==(b);
}

#undef __DEF_Template_MemoryDescriptor
#undef __DEF_MemoryDescriptor

//==============class LinearSourceManager
#define __DEF_Template_LinearSourceManager template <class _LinearSourceDescriptor,template <class> class _NodeAllocator>
#define __DEF_LinearSourceManager LinearSourceManager<_LinearSourceDescriptor,_NodeAllocator>
__DEF_Template_LinearSourceManager
const _LinearSourceDescriptor & __DEF_LinearSourceManager::getSpace()const
{
	return this->space;
}
#undef __DEF_Template_LinearSourceManager
#undef __DEF_LinearSourceManager

//============class MemoryManager<_DescriptorAllocator>
#define __DEF_Template_MemoryManager template<template<class > class _DescriptorAllocator>
#define __DEF_MemeoryManager MemoryManager<_DescriptorAllocator>
__DEF_Template_MemoryManager
typename __DEF_MemeoryManager::__SizeType __DEF_MemeoryManager::getBase() const {
	return this->root->getData().getStart();
}

__DEF_Template_MemoryManager
typename __DEF_MemeoryManager::__SizeType __DEF_MemeoryManager::getLimit() const {
	return this->root->getData().getLimit();
}
#undef __DEF_Template_MemoryManager
#undef __DEF_MemeoryManager

#endif /* INCLUDE_MACROS_MEMORYMANAGER_MACROS_H_ */
