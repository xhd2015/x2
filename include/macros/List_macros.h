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
#define __DEF_Template_ListNode template<class T>
#define __DEF_ListNode ListNode<T>

__DEF_Template_ListNode
typename __DEF_ListNode::__ListNode* __DEF_ListNode::getNext()const
{
    return next;
}

__DEF_Template_ListNode
typename __DEF_ListNode::__ListNode* __DEF_ListNode::getPrevious()const
{
    return previous;
}
__DEF_Template_ListNode
void __DEF_ListNode::setNext(__ListNode* next)
{
    this->next = next;
}

__DEF_Template_ListNode
void  __DEF_ListNode::setPrevious(__ListNode* previous)
{
    this->previous = previous;
}
__DEF_Template_ListNode
int  __DEF_ListNode::hasPrevious()const
{
    return (this->previous!=NULL);
}

__DEF_Template_ListNode
int  __DEF_ListNode::hasNext()const
{
    return (this->next!=NULL);
}

__DEF_Template_ListNode
const T& __DEF_ListNode::getData()const
{
    return data;
}
__DEF_Template_ListNode
T& __DEF_ListNode::getData()
{
    return data;
}
__DEF_Template_ListNode
void __DEF_ListNode::setData(const T& data)
{
    this->data=data;
}
#undef __DEF_Template_ListNode
#undef __DEF_ListNode



//=============class:LinkedList
#define __DEF_Template_LinkedList template <class T,template <class> class _Allocator>
#define __DEF_LinkedList LinkedList<T,_Allocator>
__DEF_Template_LinkedList
typename __DEF_LinkedList::__ListNode*
__DEF_LinkedList::getHead()const
{
    return root->getNext();
}
__DEF_Template_LinkedList
typename __DEF_LinkedList::__ListNode*
__DEF_LinkedList::getLast()const
{
    return last->getNext();
}
__DEF_Template_LinkedList
bool			__DEF_LinkedList::isEmpty()const
{
	return this->getHead()==NULL;
}
__DEF_Template_LinkedList
_Allocator<typename __DEF_LinkedList::__ListNode>
*__DEF_LinkedList::getMemoryManager()const
{
    return smm;
}
#undef __DEF_Template_LinkedList
#undef __DEF_LinkedList


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
#define __DEF_Template_TreeNode template<class T>
#define __DEF_TreeNode TreeNode<T>

__DEF_Template_TreeNode
typename __DEF_TreeNode::__TreeNode* __DEF_TreeNode::setSon(__TreeNode* son)
  {
#if defined(CODE64)
	//printf("setSon is : %x \n",son);
#endif
  	this->son=son;
  	return this;
  }
__DEF_Template_TreeNode
typename __DEF_TreeNode::__TreeNode* __DEF_TreeNode::setFather(__TreeNode* father) {
    this->father=father;
    return this;
}

//#if ! defined(CODE64)
__DEF_Template_TreeNode
typename __DEF_TreeNode::__TreeNode* __DEF_TreeNode::getSon() const{
//#if defined(CODE64)
//	printf("gettSon \n");
//#endif
	return son;
}
//#endif


__DEF_Template_TreeNode
typename __DEF_TreeNode::__TreeNode* __DEF_TreeNode::getNext() const{
	__TreeNode* next=(__TreeNode*)this->__ListNode::getNext();//这种情况下的强制转换一定是正确的，因为TreeNode中只存储TreeNode，而不会存储ListNode
	return next;
}

__DEF_Template_TreeNode
typename __DEF_TreeNode::__TreeNode* __DEF_TreeNode::getPrevious() const{
	__TreeNode* previous=(__TreeNode*)this->__ListNode::getPrevious();
	return previous;
}


__DEF_Template_TreeNode
typename __DEF_TreeNode::__TreeNode* __DEF_TreeNode::getDirectFather()const {//direct father
#if defined(CODE64)
//	printf("call direct,this is %x,father is %x\n",this,this->father);
#endif
    return father;
}

__DEF_Template_TreeNode
bool		 __DEF_TreeNode::hasSon()const
{
	return this->son!=NULL;
}
__DEF_Template_TreeNode
bool 		 __DEF_TreeNode::hasFather()const
{
	return this->father!=NULL;
}


#undef __DEF_Template_TreeNode
#undef __DEF_TreeNode



//======class Tree
#define __DEF_Template_Tree template<class T,template <class> class _Allocator>
#define __DEF_Tree Tree<T,_Allocator>
__DEF_Template_Tree
typename __DEF_Tree::__TreeNode* __DEF_Tree::getHead()const {
#ifdef CODE64
//	std::cout << "tree getHead()"<<std::endl;
#endif
	return root->getSon();
}

__DEF_Template_Tree
void  __DEF_Tree::setHead(__TreeNode *head)
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

__DEF_Template_Tree
void		__DEF_Tree::addRoot(__TreeNode* node)
{
	this->root->addSon(node);
}
__DEF_Template_Tree
bool		__DEF_Tree::isEmpty()const
{
	return !(this->root->hasSon());
}
__DEF_Template_Tree
typename __DEF_Tree::__Allocator *__DEF_Tree::getSmm()const
{
	return this->smm;
}

#undef __DEF_Template_Tree
#undef __DEF_Tree


#endif /* INCLUDE_MACROS_LIST_MACROS_H_ */
