#if defined(CODE16)
//do nothing
__asm__(".code16gcc \n\t");
#elif defined(CODE32)
__asm__(".code32 \n\t");
#endif

#include <Memory.h>
#include <List.h>
#include <libx2.h>
#include <def.h>
#include <test.h>
//=============template ininstantiate
#if defined(CODE32)
	template class MemoryManager<SimpleMemoryManager>;
#endif

#if !defined(CODE64)
//全局方法: placement new和placement delete
// Default placement versions of operator new.
void* operator new(size_t, void* __p)
{ return __p; }
void* operator new[](size_t, void* __p)
{ return __p; }

// Default placement versions of operator delete.
void operator delete  (void*, void*) { }
void operator delete[](void*, void*) { }
#endif

//============class : MemoryManager
template<template <class> class _DescriptorAllocator>
MemoryManager<_DescriptorAllocator>::MemoryManager(_DescriptorAllocator<TreeNode<MemoryDescriptor> > *smm):
Tree<MemoryDescriptor,_DescriptorAllocator>(smm) //调用父类的构造函数
{

}
template<template <class> class _DescriptorAllocator>
MemoryManager<_DescriptorAllocator>::MemoryManager(_DescriptorAllocator<TreeNode<MemoryDescriptor> > *smm,size_t start,size_t len,bool fatherAllocable):
MemoryManager(smm)
{
    setHead( new (smm->getNew()) TreeNode<MemoryDescriptor>(MemoryDescriptor(start,len,fatherAllocable)));
}

template<template <class> class _DescriptorAllocator>
MemoryManager<_DescriptorAllocator>::~MemoryManager()
{
    //这里不进行真正的撤销，只是把管理器所使用的节点撤销
    if(this->getHead())
    {
        this->getHead()->setFather(NULL);
    }
    this->smm->withdraw(this->root);
}

template<template <class> class _DescriptorAllocator>
void MemoryManager<_DescriptorAllocator>::withdrawToParent()
{
    //回收后进行两点之间的检查，如果能够合并就进行合并
    TreeNode<MemoryDescriptor> *head=this->getHead();
    if(head)
    {
        //顶级管理器和非顶级管理器操作相同
        this->withdrawNode(head);
        //但是如果是顶级管理器，father为NULL，所以需要将其从smm中撤销
        if(!head->getParent())//顶级管理器
        {
            this->smm->withdraw(head);
            this->setHead(NULL);
        }
    }
}
/**
*   for nodes found available for allocation,here will spilt it out
*   it will:
*       adjust the node before and after the desired area
*       return a node denoting the desired area
*   accept:
*       avlNode = NULL
*   do not accept:
*       the area start and len denoted is not logically inside avlNode
*       means avlNode,start,len should be derived from the inner method
*/

template<template <class> class _DescriptorAllocator>
TreeNode<MemoryDescriptor> * MemoryManager<_DescriptorAllocator>::allocOutNode(TreeNode<MemoryDescriptor> *avlNode,size_t start,size_t len)
{

    // Test::dumpMemoryData(avlNode->getData());
    TreeNode<MemoryDescriptor> *newnode=NULL;
    if(avlNode)
    {
        size_t len1=(size_t)(start-avlNode->getData().getStart());
        size_t len2=(size_t)(avlNode->getData().getLimit() - len - len1);
        char saver[10];

        Util::digitToStr(saver, 10, avlNode->getData().getStart());
        Util::printStr(saver);Util::printStr("..");
        Util::digitToStr(saver, 10, avlNode->getData().getLimit());
        Util::printStr(saver);Util::printStr("..");
        Util::digitToStr(saver, 10, start);
        Util::printStr(saver);Util::printStr("..");
        Util::digitToStr(saver, 10, len);
        Util::printStr(saver);Util::printStr("..");
        Util::digitToStr(saver,10,len1);
        Util::printStr(saver);Util::printStr("..");
        Util::digitToStr(saver, 10, len2);
        Util::printStr(saver);Util::printStr("\n");

        if(len1>0)//前面有剩余,需要插入新的点
        {
            avlNode->getData().setLimit(len1);
            newnode= new (this->smm->getNew()) TreeNode<MemoryDescriptor>(MemoryDescriptor(start,len,false));//新建一个node，不可用于分配
                                            //将这个节点加入以这个点为根的树中
            avlNode->insertNext(newnode);//中间的节点，已经分配
        }else{//直接取代前面的点
            newnode=avlNode;
            newnode->getData().setStart(start);
            newnode->getData().setLimit(len);
            newnode->getData().setAllocable(false);
        }
        if(len2>0)//后面有剩余
        {
            TreeNode<MemoryDescriptor> *newnodeEnd= new (this->smm->getNew()) TreeNode<MemoryDescriptor>(MemoryDescriptor(start+len,len2));
            newnode->insertNext(newnodeEnd);
        }else{//没有就不进行任何操作

        }
    }
    return newnode;
}
/**
*  BUG:
*       may not properly combine the son nodes.@BUG1    --  but those nodes are allocable,meaning they should have no sons.
*                                                            in another words, a node is consistence only when isAllocable()=(getSon()==NULL)
* do not accept:
*       exactNode==NULL
*/

template<template <class> class _DescriptorAllocator>
void MemoryManager<_DescriptorAllocator>::withdrawNode(TreeNode<MemoryDescriptor> *exactNode)
{
    //先释放其所有子节点
    TreeNode<MemoryDescriptor> *p=exactNode->getSon();
    while(p)
    {
        this->free(p);
        p=p->getNext();
    }
    exactNode->setSon(NULL);//free完毕

    //开始合并
    TreeNode<MemoryDescriptor> *prev=exactNode->getPrevious();
    if(prev && prev->getData().isAllocable() && exactNode->getData().getStart() - prev->getData().getStart() == (int)prev->getData().getLimit() )
    {
        prev->getData().setLimit(prev->getData().getLimit() + exactNode->getData().getLimit() );
        prev->removeNext();//移除冗余节点
        this->smm->withdraw(exactNode);
    }else{
        prev=exactNode;
        prev->getData().setAllocable(1);
    }//OK,the previous node cheking is done

    TreeNode<MemoryDescriptor> *nxt=prev->getNext();
    if(nxt && nxt->getData().isAllocable() && nxt->getData().getStart() - prev->getData().getStart() == (int)prev->getData().getLimit() )
    {
        prev->getData().setLimit(prev->getData().getLimit() + nxt->getData().getLimit() );
        // //将next的子节点移动到此处
        // //BUG1:
        // TreeNode<MemoryDescriptor> *prevson=prev->getSon(),nxtson=nxt->getSon();
        // if(prevson)
        // {
        //     prevson->getLast()->insertNext(nxtson);
        // }else{
        //     prev->setSon(nxtson);
        //     nxtson->setFather(prev);
        // }
        // if(prev->getSon())
        // {

        // }
        prev->removeNext();
        this->smm->withdraw(nxt);
    }else{//do nothing

    }

}

DEVEL_UNTESTED(Douglas_Fulton_Shaw)
template<template <class> class _DescriptorAllocator>
MemoryManager<_DescriptorAllocator> MemoryManager<_DescriptorAllocator>::allocFreeStart(size_t start,size_t len) {
    // Util::printStr("Enter allocFreeStart: ");
    
    MemoryManager<_DescriptorAllocator>          spaces(this->smm);
    if(len<=0 || this->isNullManager() )
    {
        spaces.setNull();//ok
    }else{
        copyOnAllocation(getHead());//保证复制了父节点(当父节点可用于分配但是子节点中没有任何一个节点时，调用此方法）
        TreeNode<MemoryDescriptor> *firstNode=MemoryManager<_DescriptorAllocator>::findFirstStart(getHead(),start,len);//ok,the information of head is ignored,it's full information is stored in it's sons
        spaces.setHead(allocOutNode(firstNode,start,len));//either not found or found,set the new manager
    }
    return spaces;
}

template<template <class> class _DescriptorAllocator>
MemoryManager<_DescriptorAllocator> MemoryManager<_DescriptorAllocator>::allocFree(size_t len) {
    
    MemoryManager<_DescriptorAllocator>          spaces(this->smm);
    if(len<=0 || this->isNullManager() )
    {
        spaces.setNull();//ok
    }else{
        copyOnAllocation(getHead());//保证复制了父节点
        TreeNode<MemoryDescriptor> *firstNode=MemoryManager<_DescriptorAllocator>::findFirstLen(getHead(),len);//ok,the information of head is ignored,it's full information is stored in it's sons
        spaces.setHead(allocOutNode(firstNode,firstNode->getData().getStart(),len));//either not found or found,set the new manager
    }
    return spaces;
}

template<template <class> class _DescriptorAllocator>
void* MemoryManager<_DescriptorAllocator>::mnew(size_t start,size_t size)
{
    TreeNode<MemoryDescriptor> *found=MemoryManager<_DescriptorAllocator>::findFirstStart(getHead(),start,size);
    if(found)
    {
        TreeNode<MemoryDescriptor> *alloced = allocOutNode(found,found->getData().getStart(),size);
        if(alloced)
        {
            return (void*)(alloced->getData().getStart());
        }
    }
    return NULL;    
}

template<template <class> class _DescriptorAllocator>
void* MemoryManager<_DescriptorAllocator>::mnew(unsigned int size) {
    TreeNode<MemoryDescriptor> *found=MemoryManager<_DescriptorAllocator>::findFirstLen(getHead(),size);
    if(found)
    {
        TreeNode<MemoryDescriptor> *alloced = allocOutNode(found,found->getData().getStart(),size);
        if(alloced)
        {
            return (void*)(alloced->getData().getStart());
        }
    }
    return NULL;
}
/**
*   Following:
*       find the exact node by required arguments with {starting with p, limit is size,not allocable}
*       if found,withdraw it to parent
*
*/

template<template <class> class _DescriptorAllocator>
void MemoryManager<_DescriptorAllocator>::mdelete(void* p, unsigned int size) {
    TreeNode<MemoryDescriptor>* toDeleteNode=MemoryManager<_DescriptorAllocator>::locateForDelete(getHead(),(int)p,size,0);
    if(toDeleteNode)//if found it
    {
        //Util::printStr("Found delete.   ");
        withdrawNode(toDeleteNode);
    }
}

template<template <class> class _DescriptorAllocator>
void MemoryManager<_DescriptorAllocator>::mdelete(void *p)
{
    TreeNode<MemoryDescriptor>* toDeleteNode=MemoryManager<_DescriptorAllocator>::locateForDeleteStart(getHead(),(int)p,0);
    if(toDeleteNode)//if found it
    {
        //Util::printStr("Found delete.   ");
        withdrawNode(toDeleteNode);
    }
}

/**
*find the first node from loc's son nodes that is:
*   allocable
*   starts at start or upper
*   has the limit not less than len
*
*/
DEVEL_UNTESTED(Douglas_Fulton_Shaw) DEVEL_COMPLETED(Douglas_Fulton_Shaw) DEVEL_LAST(Douglas_Fulton_Shaw,2017-02-21 23:27:31) DEVEL_AUTHOR(Douglas_Fulton_Shaw) DEVEL_DEP(MemoryManager::getData,MemoryDescriptor::getStart)

template<template <class> class _DescriptorAllocator>
TreeNode<MemoryDescriptor>* MemoryManager<_DescriptorAllocator>::findFirstStart(
		TreeNode<MemoryDescriptor>* loc, size_t start,size_t len)
{
	TreeNode<MemoryDescriptor>* p=loc->getSon();
  
    // if(p)
    // {
    //     Test::dumpMemoryData(loc->getData());
    //     Test::dumpMemoryData(p->getData());
    // }else{
    //     Util::printStr("p is NULL \n");
    // }

	char saver[50];

	Util::printStr("in find...");
	Util::digitToStr(saver, 50, p->getData().getStart());
	Util::printStr(saver);Util::printStr("..");
	/*
	Util::digitToStr(saver, 50, start);
	Util::printStr(saver);Util::printStr("\n");
	*/

	while(p && start < p->getData().getStart())
	{
		Util::printStr("go next...");
        p=MemoryManager<_DescriptorAllocator>::nextAllocable(p);
	}
	while(p && (int)(p->getData().getLimit() - len) < start - p->getData().getStart() )
	{
        p=MemoryManager<_DescriptorAllocator>::nextAllocable(p);
	}
	return p; //NULL or first valid section
}

template<template <class> class _DescriptorAllocator>
TreeNode<MemoryDescriptor>* MemoryManager<_DescriptorAllocator>::findFirstLen(
		TreeNode<MemoryDescriptor>* loc, unsigned int len) {
	TreeNode<MemoryDescriptor> *p=loc->getSon();
    if(! p->getData().isAllocable() )
    {
        p=MemoryManager<_DescriptorAllocator>::nextAllocable(p);
    }
	while(p && p->getData().getLimit() < len )
    {
        p=MemoryManager<_DescriptorAllocator>::nextAllocable(p);
    }
	return p;
}

template<template <class> class _DescriptorAllocator>
int MemoryManager<_DescriptorAllocator>::isNullManager() {
	return getHead()==NULL;
}

template<template <class> class _DescriptorAllocator>
void  MemoryManager<_DescriptorAllocator>::setNull()
{
    setHead(NULL);
}

//确保这条线段是位于两个分割点的缝隙之间，如果不是，返回NULL
template<template <class> class _DescriptorAllocator>
TreeNode<MemoryDescriptor>* MemoryManager<_DescriptorAllocator>::locateForInsertation(
		TreeNode<MemoryDescriptor>* loc, TreeNode<MemoryDescriptor>* son) {
    if( loc==NULL || son==NULL)return NULL;
    TreeNode<MemoryDescriptor>* p=loc;
    int start=son->getData().getStart();
    unsigned int len=son->getData().getLimit();
    
	while(p && start - p->getData().getStart() < (int)p->getData().getLimit() )
	{
		p=p->getNext();
	}
	if(p)
    {
        if(p->getNext())
        {
            TreeNode<MemoryDescriptor> *forward=p->getNext();
            
            if(forward->getData().getStart() - start >= (int)len)
            {
                return p;   //valid
            }else{
                return NULL; //overlapped with the forward
            }
        }else{
            
            return p;  //need not verify the forward
        }
    }
	return NULL; //until the end,does not find such one
}
/**
* find for its sons which is exactly the same with passed arguments.
*/
template<template <class> class _DescriptorAllocator>
TreeNode<MemoryDescriptor>* MemoryManager<_DescriptorAllocator>::locateForDelete(TreeNode<MemoryDescriptor>* loc,size_t start,size_t len,bool allocable)
{
    if(loc==NULL||len==0)return NULL;
    TreeNode<MemoryDescriptor>* p=loc->getSon();

    while(p && p->getData().getStart() < start)
            p=p->getNext();
    if(p && p->getData().getStart() == start && p->getData().getLimit()==len && p->getData().isAllocable()==allocable)
    {
        return p;
    }else{
        return NULL;
    }

}

/**
* find for its sons which is exactly the same with passed arguments.
*/
template<template <class> class _DescriptorAllocator>
TreeNode<MemoryDescriptor>* MemoryManager<_DescriptorAllocator>::locateForDeleteStart(TreeNode<MemoryDescriptor>* loc,size_t start,bool allocable)
{
    if(loc==NULL)return NULL;
    TreeNode<MemoryDescriptor>* p=loc->getSon();

    while(p && p->getData().getStart() < start)
            p=p->getNext();
    if(p && p->getData().getStart() == start && p->getData().isAllocable()==allocable)
    {
        return p;
    }else{
        return NULL;
    }

}



template<template <class> class _DescriptorAllocator>
int MemoryManager<_DescriptorAllocator>::addToTree(TreeNode<MemoryDescriptor>* root,
		TreeNode<MemoryDescriptor>* son) {
            TreeNode<MemoryDescriptor> *location=MemoryManager<_DescriptorAllocator>::locateForInsertation(root,son);
            if(location)
            {
                
            }
}
/**
* head mustn't be NULL!!
*/
template<template <class> class _DescriptorAllocator>
TreeNode<MemoryDescriptor>* MemoryManager<_DescriptorAllocator>::copyOnAllocation(TreeNode<MemoryDescriptor> *head)
{
    if(!head->getSon())
    {
        const MemoryDescriptor &data=head->getData();

        //*****
        //Util::printStr("copyOnAllocation -- ");
        //**********

        TreeNode<MemoryDescriptor> *newnode=new (this->smm->getNew()) TreeNode<MemoryDescriptor>(MemoryDescriptor(data.getStart(),data.getLimit(),!data.isAllocable()));

        newnode->setFather(head);
        head->setSon(newnode);
        return newnode;
    }else{
        return head->getSon();    
    }
    

}

DEVEL_UNTESTED(Douglas_Fulton_Shaw)
DEVEL_AUTHOR(Douglas_Fulton_Shaw)
template<template <class> class _DescriptorAllocator>
TreeNode<MemoryDescriptor>* MemoryManager<_DescriptorAllocator>::nextAllocable(
		TreeNode<MemoryDescriptor>* node) {
        if(node)
        {
            do{
                node=node->getNext();
            }while( node && (node->getData().isAllocable()==false) );
        }
        return node;
}

//==========class:LinearSourceManager
template <class _LinearSourceDescriptor,template <class> class _NodeAllocator>
LinearSourceManager<_LinearSourceDescriptor,_NodeAllocator >::LinearSourceManager(_NodeAllocator<ListNode<_LinearSourceDescriptor> > *smm,
    size_t start,size_t size):
LocateableLinkedList<_LinearSourceDescriptor,Locator<_LinearSourceDescriptor>::DISCARD, _NodeAllocator >(smm),
space(_LinearSourceDescriptor(start,size))
{
}
template <class _LinearSourceDescriptor,template <class> class _NodeAllocator>
LinearSourceManager<_LinearSourceDescriptor,_NodeAllocator >::~LinearSourceManager()
{

}

template <class _LinearSourceDescriptor,template <class> class _NodeAllocator>
void* LinearSourceManager<_LinearSourceDescriptor,_NodeAllocator >::mnew(size_t start,size_t size)
{
    if(!checkRange(start,size))return NULL;
    ListNode<_LinearSourceDescriptor> *found=Father::findFirstStartLen(getHead(),start,size);
    if(found)
    {
        _LinearSourceDescriptor alloced = allocOutNode(found,found->getData().getStart(),size);
        if(alloced.getLimit())
        {
            return (void*)(alloced.getStart());
        }
    }
    return NULL;  
}
 
template <class _LinearSourceDescriptor,template <class> class _NodeAllocator>
void* LinearSourceManager<_LinearSourceDescriptor,_NodeAllocator >::mnew(size_t size)
{
    ListNode<_LinearSourceDescriptor> *found=Father::findFirstLen(getHead(),size);
    if(found)
    {
        _LinearSourceDescriptor alloced = allocOutNode(found,found->getData().getStart(),size);
        if(alloced.getLimit())
        {
            return (void*)(alloced.getStart());
        }
    }
    return NULL;
}

    
template <class _LinearSourceDescriptor,template <class> class _NodeAllocator>
void LinearSourceManager<_LinearSourceDescriptor,_NodeAllocator >::mdelete(void* p,size_t size)
{
    if(!checkRange((size_t)p,size))return NULL;
    ListNode<_LinearSourceDescriptor> *found=Father::findFirstForInsert(getHead(),(size_t)p,size);
    if(found)
    {
        int diff=found->getData().getStart()-(size_t)p;
        if(diff==0 || (diff>0 && !( This::checkPrevious(found->getPrevious(),(size_t)p) && This::checkNext(found,(size_t)p,size) ) ) ||
                      (diff<0 && !(This::checkPrevious(found,(size_t)p) && This::checkNext(found->getNext(),(size_t)p,size) )  ) 
                      )
        {
            //impossible to delete this memory
            return;
        }else{
            if(diff>0)
            {
                found->insertPrevious(new (this->smm->getNew()) ListNode<_LinearSourceDescriptor>(_LinearSourceDescriptor((size_t)p,size)) );
            }else{
                found->insertNext(new (this->smm->getNew()) ListNode<_LinearSourceDescriptor>(_LinearSourceDescriptor((size_t)p,size)) );
            }
        }
    }else{//empty list
        appendHead(_LinearSourceDescriptor((size_t)p,size));
    }

}

template <class _LinearSourceDescriptor,template <class> class _NodeAllocator>
 bool LinearSourceManager<_LinearSourceDescriptor,_NodeAllocator >::checkRange(size_t start,size_t size)
 {
    return (this->space.getStart() <= start) && (start-this->space.getStart() <= this->space.getLimit() - size );
 }
template <class _LinearSourceDescriptor,template <class> class _NodeAllocator>
 bool LinearSourceManager<_LinearSourceDescriptor,_NodeAllocator>::checkRange(size_t start)
 {
    return this->space.getStart() <= start;
 }

template <class _LinearSourceDescriptor,template <class> class _NodeAllocator>
bool LinearSourceManager<_LinearSourceDescriptor,_NodeAllocator >::checkPrevious(ListNode<_LinearSourceDescriptor> *prev,size_t start)
{
    return !prev || (start - prev->getData().getStart() >= prev->getData().getLimit());
}

template <class _LinearSourceDescriptor,template <class> class _NodeAllocator>
bool LinearSourceManager<_LinearSourceDescriptor,_NodeAllocator >::checkNext(ListNode<_LinearSourceDescriptor> *nxt,size_t start,size_t len)
{
    return !nxt || (nxt->getData().getStart() - start >= len );
}
/**
 *  start & len should reside in avlNode
 *  then this will always return true.
 *
 *  But currently we don't have that promise,So check the returned node if it havs a positive limit
 */
template <class _LinearSourceDescriptor,template <class> class _NodeAllocator>
_LinearSourceDescriptor LinearSourceManager<_LinearSourceDescriptor,_NodeAllocator >::allocOutNode(ListNode<_LinearSourceDescriptor> *avlNode,size_t start,size_t len)
{
	_LinearSourceDescriptor newnode(start,len);
    if(avlNode)
    {
        int len1=start - avlNode->getData().getStart();
        int len2=avlNode->getData().getLimit() - len - len1;
        if(len1<0 || len2 < 0)newnode.setLimit(0);
        else if(len1==0 && len2==0)//前后都没有剩余
        {
            this->remove(avlNode);
        }else if(len1==0 && len2 > 0){//后面有剩余
            avlNode->setStart(start+len);
            avlNode->setLimit(len2);
        }else if(len1 > 0 && len2==0){//前面有剩余
            avlNode->setLimit(len1);
        }else{//前后都有剩余
            avlNode->setLimit(len1);
            avlNode->insertNext(new (this->smm->getNew()) ListNode<_LinearSourceDescriptor>(_LinearSourceDescriptor(start+len,len2)) );
        }
    }
    return newnode;
}
    

