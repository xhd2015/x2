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
#if defined(CODE64)
#define __DEF_SIZE_TYPE u64_t
#define __DEF_ALIGNMENT sizeof(u64_t)
#include <preprocessor_functions/MemoryManager_macros.h.RAW>
#define __DEF_SIZE_TYPE size_t
#define __DEF_ALIGNMENT sizeof(size_t)
#include <preprocessor_functions/MemoryManager_macros.h.RAW>
#endif

#if defined(CODE32) ||defined(CODE32USER)|| defined(CODE64)
#define __DEF_SIZE_TYPE u32_t
#define __DEF_ALIGNMENT 4
#include <preprocessor_functions/MemoryManager_macros.h.RAW>
#endif

#if defined(CODE16) || defined(CODE32) ||defined(CODE32USER)|| defined(CODE64)
#define __DEF_SIZE_TYPE u16_t
#define __DEF_ALIGNMENT 2
#include <preprocessor_functions/MemoryManager_macros.h.RAW>
#endif

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
    return this->__LinearSourceDescriptor::operator==(b) && this->allocable==b.allocable;

}


template <class __SizeType>
bool MemoryDescriptor<__SizeType>::operator!=(const MemoryDescriptor<__SizeType>& b)const
{
    return ! this->operator==(b);
}

//==============class LinearSourceManager
template <class _LinearSourceDescriptor,template <class> class _NodeAllocator,typename __SizeType,int __Alignment>
const _LinearSourceDescriptor & LinearSourceManager<_LinearSourceDescriptor,_NodeAllocator,__SizeType,__Alignment>::
getSpace()const
{
	return this->space;
}

//============class MemoryManager<_DescriptorAllocator>
template<template<class > class _DescriptorAllocator,typename __SizeType,int __Alignment>
__SizeType MemoryManager<_DescriptorAllocator,__SizeType,__Alignment>::getBase() const {
	return this->root->getData().getStart();
}

template<template<class > class _DescriptorAllocator,typename __SizeType,int __Alignment>
__SizeType MemoryManager<_DescriptorAllocator,__SizeType,__Alignment>::getLimit() const {
	return this->root->getData().getLimit();
}


#endif /* INCLUDE_MACROS_MEMORYMANAGER_MACROS_H_ */
