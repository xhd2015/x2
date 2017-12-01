/*
 * List_macros.h
 *
 *  Created on: 2017年3月24日
 *      Author: 13774
 */

#ifndef INCLUDE_MACROS_LIST_MACROS_H_
#define INCLUDE_MACROS_LIST_MACROS_H_

#include <List.h>

#if defined(CODE64)
#include <iostream>
#endif

//============函数宏区
//=========class : ListNode
#if defined(CODE64)
#define __DEF_ALIGNMENT sizeof(size_t)
#include <preprocessor_functions/List_macros.h.RAW>
#endif

#if defined(CODE32) ||defined(CODE32USER)|| defined(CODE64)
#define __DEF_ALIGNMENT 4
#include <preprocessor_functions/List_macros.h.RAW>
#endif

#if defined(CODE16) || defined(CODE32) ||defined(CODE32USER)|| defined(CODE64)
#define __DEF_ALIGNMENT 2
#include <preprocessor_functions/List_macros.h.RAW>
#endif



//=============class:LinkedList
template <class T,template <class> class _Allocator,int __Alignment>
typename LinkedList<T,_Allocator,__Alignment>::__ListNode*
LinkedList<T,_Allocator,__Alignment>::getHead()const
{
    return root->getNext();
}
template <class T,template <class> class _Allocator,int __Alignment>
typename LinkedList<T,_Allocator,__Alignment>::__ListNode*
LinkedList<T,_Allocator,__Alignment>::getLast()const
{
    return last->getNext();
}
template <class T,template <class> class _Allocator,int __Alignment>
bool			LinkedList<T,_Allocator,__Alignment>::isEmpty()const
{
	return this->getHead()==NULL;
}
template <class T,template <class> class _Allocator,int __Alignment>
_Allocator<typename LinkedList<T,_Allocator,__Alignment>::__ListNode>
*LinkedList<T,_Allocator,__Alignment>::getMemoryManager()const
{
    return smm;
}

//=====class: SimpleMemoryNode
SimpleMemoryNode::SimpleMemoryNode(bool NO):
alloced(NO)
{

}
bool SimpleMemoryNode::getNO()
{
    return this->alloced;
}
bool SimpleMemoryNode::isFree()
{
    return this->alloced==false;
}
bool SimpleMemoryNode::isAlloced()
{
	return alloced;
}
void SimpleMemoryNode::setAlloced(bool alloced)
{
	this->alloced=alloced;
}
void SimpleMemoryNode::free()
{
    this->alloced=false;
}
void SimpleMemoryNode::unfree()
{
//	printf("offset of No is %x\n",(char*)&(this->NO)-(char*)this);
    this->alloced=true;
}
void SimpleMemoryNode::setNO(bool NO)
{
    this->alloced = NO;
}

//=====class:SimpleMemoryManager
template<class T>
bool SimpleMemoryManager<T>::isFull()const
{
    return this->curSize==this->len;
}
template<class T>
size_t SimpleMemoryManager<T>::getLen()const
{
    return this->len;
}
template<class T>
size_t SimpleMemoryManager<T>::getCurSize()const
{
    return this->curSize;
}
template<class T>
size_t SimpleMemoryManager<T>::getStart()const
{
    return this->start;
}
template<class T>
size_t SimpleMemoryManager<T>::getLimit()const
{
    return this->limit;
}    ///////////

template<class T>
size_t  SimpleMemoryManager<T>::getNodeSize()
{
	return sizeof(FullNode);
}

template<class T>
typename SimpleMemoryManager<T>::ERROR_HANDLER SimpleMemoryManager<T>::getErrHandler()
{
	return this->errhandle;
}
template<class T>
void			SimpleMemoryManager<T>::setErrHandler(SimpleMemoryManager<T>::ERROR_HANDLER errhandle)
{
	this->errhandle= errhandle;
}
template<class T>
bool			SimpleMemoryManager<T>::checkIsInternal(FullNode *t)
{
	return this->start <= (size_t)t && (size_t)t - (size_t)this->start <= this->limit ;
}
//===========class TreeNode
#if defined(CODE64)
#define __DEF_ALIGNMENT sizeof(size_t)
#include <preprocessor_functions/List_TreeNode_macros.h.RAW>
#endif

#if defined(CODE32) ||defined(CODE32USER)|| defined(CODE64)
#define __DEF_ALIGNMENT 4
#include <preprocessor_functions/List_TreeNode_macros.h.RAW>
#endif

#if defined(CODE16) || defined(CODE32) ||defined(CODE32USER)|| defined(CODE64)
#define __DEF_ALIGNMENT 2
#include <preprocessor_functions/List_TreeNode_macros.h.RAW>
#endif



//======class Tree
template<class T,template <class> class _Allocator,int __Alignment>
typename Tree<T,_Allocator,__Alignment>::__TreeNode* Tree<T,_Allocator,__Alignment>::getHead()const {
#ifdef CODE64
//	std::cout << "tree getHead()"<<std::endl;
#endif
	return root->getSon();
}

template<class T,template <class> class _Allocator,int __Alignment>
void  Tree<T,_Allocator,__Alignment>::setHead(__TreeNode *head)
 {
#if defined(CODE64)
	//printf("root : %x  , head : %x\n",root,head);
	//head->setFather(root);
	//head->setSon(root);
	//printf("head data : %x \n",head->getDirectFather());
#endif
 	root->setSon(head);
#if defined(CODE64)
 	//printf("root->setSon : %x\n",root->getSon());
#endif
 }

template<class T,template <class> class _Allocator,int __Alignment>
void		Tree<T,_Allocator,__Alignment>::addRoot(__TreeNode* node)
{
	this->root->addSon(node);
}
template<class T,template <class> class _Allocator,int __Alignment>
bool		Tree<T,_Allocator,__Alignment>::isEmpty()const
{
	return !(this->root->hasSon());
}
template<class T,template <class> class _Allocator,int __Alignment>
typename Tree<T,_Allocator,__Alignment>::__Allocator *Tree<T,_Allocator,__Alignment>::getSmm()const
{
	return this->smm;
}



#endif /* INCLUDE_MACROS_LIST_MACROS_H_ */
