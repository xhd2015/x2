#if defined(CODE16)
//do nothing
__asm__(".code16gcc \n\t");
#elif defined(CODE32)
__asm__(".code32 \n\t");
#endif

#include <MemoryManager.h>
#include <List.h>
#include <libx2.h>
#include <def.h>

#include <macros/all.h>

#if defined(CODE32)||defined(CODE16)
#include <test.h>
#endif

//=============template ininstantiate
#if defined(CODE32)
	template class MemoryManager<SimpleMemoryManager,u32_t>;
	template class MemoryManager<KernelSmmWrapper,u32_t>;
#elif defined(CODE64)

#include <cstdio>
#include <cstring>
#include <64/MallocToSimple.h>
#include <EnvInterface64Impl.h>
#include <File.h>
	template class MemoryManager<MallocToSimple64Impl,size_t>;
	template class MemoryManager<X2fsUtil<EnvInterface64Impl,size_t>::PartialMallocToSimple,size_t>;
	template class MemoryManager<X2fsUtil<StdEnv64Impl, size_t>::PartialMallocToSimple, size_t>;

	template class LinearSourceManager<LinearSourceDescriptor<size_t>, MallocToSimple64Impl,size_t>;
	template class LinearSourceManager<LinearSourceDescriptor<size_t>, X2fsUtil<EnvInterface64Impl,size_t>::PartialMallocToSimple,size_t>;
	template class LinearSourceManager<LinearSourceDescriptor<size_t>, X2fsUtil<StdEnv64Impl,size_t>::PartialMallocToSimple,size_t>;
#endif
//
//#if defined(CODE32)
////全局方法: placement new和placement delete
//// Default placement versions of operator new.
//void* operator new(size_t, void* __p)
//{ return __p; }
//void* operator new[](size_t, void* __p)
//{ return __p; }
//
//// Default placement versions of operator delete.
//void operator delete  (void*, void*) { }
//void operator delete[](void*, void*) { }
//#endif

//============class : MemoryManager
template<template <class> class _DescriptorAllocator,typename __SizeType,int __Alignment>
MemoryManager<_DescriptorAllocator,__SizeType,__Alignment>::
MemoryManager(__Allocator *smm)
:
Tree<MemoryDescriptor<__SizeType>,_DescriptorAllocator>(smm) //调用父类的构造函数
{

}
template<template <class> class _DescriptorAllocator,typename __SizeType,int __Alignment>
MemoryManager<_DescriptorAllocator,__SizeType,__Alignment>::MemoryManager(
		__Allocator *smm,__SizeType start,__SizeType len,bool fatherAllocable)
:MemoryManager(smm)
//:dbg1("MemoryManager 1\n")
{
#if defined(CODE64)
	//printf("set Head\n");
#endif
	// root->son = new_node, 也就是head， 但是head不指向root，也就是说指针时单向的
	//Kernel::printer->move(-40);


	__TreeNode *head=smm->getNew();

	new (head) __TreeNode(__MemoryDescriptor(start,len,fatherAllocable));

	this->setHead(head);

	//===分配内存


#if defined(CODE64)
    //printf("in constructor : ");
    //getchar();
    //printf("%x ~ %x\n",this->getHead()->getData().getStart(),this->getHead()->getData().getLimit());
#endif
}
template<template <class> class _DescriptorAllocator,typename __SizeType,int __Alignment>
MemoryManager<_DescriptorAllocator,__SizeType,__Alignment>::
MemoryManager(__Allocator *smm,__SizeType start,__SizeType len,
		__SizeType usedList[][2],__SizeType usedLen,bool fatherAllocable):MemoryManager(smm,start,len,fatherAllocable)
{
	for(size_t i=0;i<usedLen;i++)
		mnew(usedList[i][0], usedList[i][1]);
}

template<template <class> class _DescriptorAllocator,typename __SizeType,int __Alignment>
MemoryManager<_DescriptorAllocator,__SizeType,__Alignment>::~MemoryManager()
{
    //这里不进行真正的撤销，只是把管理器所使用的节点撤销
    if(this->getHead())
    {
        this->getHead()->setFather(NULL);
    }
    this->smm->withdraw(this->root);
}

template<template <class> class _DescriptorAllocator,typename __SizeType,int __Alignment>
void MemoryManager<_DescriptorAllocator,__SizeType,__Alignment>::withdrawToParent()
{
    //回收后进行两点之间的检查，如果能够合并就进行合并
    __TreeNode *head=this->getHead();
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

template<template <class> class _DescriptorAllocator,typename __SizeType,int __Alignment>
typename MemoryManager<_DescriptorAllocator,__SizeType,__Alignment>::__TreeNode*
MemoryManager<_DescriptorAllocator,__SizeType,__Alignment>::allocOutNode(__TreeNode *avlNode,__SizeType start,__SizeType len)
{

//	Util::printf("in mm allocOut for %x,%x\n",start,len);
    // Test::dumpMemoryData(avlNode->getData());
    __TreeNode *newnode=NULL;
    if(avlNode)
    {
        __SizeType len1=(__SizeType)(start-avlNode->getData().getStart());
        __SizeType len2=(__SizeType)(avlNode->getData().getLimit() - len - len1);
#if defined(CODE64)
//      printf("len1=%x,len2=%x\n",len1,len2);
#endif

        /*
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
        */

        if(len1>0)//前面有剩余,需要插入新的点
        {
            avlNode->getData().setLimit(len1);
            newnode = this->smm->getNew();
            newnode->initToNull();
             new (newnode) __TreeNode(__MemoryDescriptor(start,len,false));//新建一个node，不可用于分配
                                            //将这个节点加入以这个点为根的树中
            avlNode->insertNext(newnode);//中间的节点，已经分配
        }else{//直接取代前面的点
            newnode=avlNode;
            newnode->getData().setStart(start);
            newnode->getData().setLimit(len);
            newnode->getData().setAllocable(false);
#if defined(CODE64)
//            printf("newnode is %x,%x,%d\n",newnode->getData().getStart(),newnode->getData().getLimit(),newnode->getData().isAllocable());
#endif
        }
        if(len2>0)//后面有剩余
        {
//        	Util::printf("before smm new\n");
        	__TreeNode *newnodeEnd=this->smm->getNew();
        	newnodeEnd->initToNull();

//        	Util::printf("after smm new \n");
            new (newnodeEnd) __TreeNode(__MemoryDescriptor(start+len,len2));
//            Util::printf("newnodeend is %x,%x,%d\n",newnodeEnd->getData().getStart(),newnodeEnd->getData().getLimit(),newnodeEnd->getData().isAllocable());

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

template<template <class> class _DescriptorAllocator,typename __SizeType,int __Alignment>
void MemoryManager<_DescriptorAllocator,__SizeType,__Alignment>::withdrawNode(__TreeNode *exactNode)
{
    //先释放其所有子节点
    __TreeNode *p=exactNode->getSon();
    while(p)
    {
        this->free(p);
        p=(__TreeNode*)p->getNext();
    }
//    Util::printf("in mm,withdrawNode \n");
    exactNode->setSon(NULL);//free完毕

    //开始合并
    __TreeNode *prev=(__TreeNode*)exactNode->getPrevious();
    if(prev && prev->getData().isAllocable() && exactNode->getData().getStart() - prev->getData().getStart() == prev->getData().getLimit() )
    {
    //	Util::printStr("combine..");
        prev->getData().setLimit(prev->getData().getLimit() + exactNode->getData().getLimit() );
        prev->removeNext();//移除冗余节点
        this->smm->withdraw(exactNode);
    }else{
        prev=exactNode;
        prev->getData().setAllocable(1);
    }//OK,the previous node cheking is done

    __TreeNode *nxt=(__TreeNode*)prev->getNext();
    if(nxt && nxt->getData().isAllocable() && nxt->getData().getStart() - prev->getData().getStart() == prev->getData().getLimit() )
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
template<template<class > class _DescriptorAllocator,typename __SizeType,int __Alignment>
u8_t MemoryManager<_DescriptorAllocator,__SizeType,__Alignment>::findExtend(__SizeType start,
		__SizeType size, __SizeType extsize,__TreeNode * &rtnode) const
{
//	Util::printf("in findExtend,start=%x,size=%x,extsize=%d\n",start,size,extsize);
	if(extsize==0)return false;
	__TreeNode* found=This::findFirstStart(this->getHead(), start + size, extsize);/*starts at start or upper,hold size or more*/
	if(found && (found->getData().getStart() - start == size))//exactly starts at start + size
	{
		rtnode=found;
//		Util::printf("in findExtend,find at tail,start=%x,size=%x,extsize=%d\n",start,size,extsize);
		return 1;
	}else{//NULL or not extensible
		found=This::findFirstLen(this->getHead(),size+extsize);
		if(found)
		{
			rtnode=found;
//			Util::printf("in findExtend,find for new len %x,found at %x,%x\n",size+extsize,found->getData().getStart(),found->getData().getLimit());
			return 2;
		}else{
			return 0;
		}
	}

}

DEVEL_UNTESTED(Douglas_Fulton_Shaw)
template<template <class> class _DescriptorAllocator,typename __SizeType,int __Alignment>
MemoryManager<_DescriptorAllocator,__SizeType,__Alignment>
MemoryManager<_DescriptorAllocator,__SizeType,__Alignment>::allocFreeStart(__SizeType start,__SizeType len) {
    // Util::printStr("Enter allocFreeStart: ");
    
    MemoryManager<_DescriptorAllocator,__SizeType>          spaces(this->smm);
    if(len<=0 || this->isNullManager() )
    {
        spaces.setNull();//ok
    }else{
        this->copyOnAllocation(this->getHead());//保证复制了父节点(当父节点可用于分配但是子节点中没有任何一个节点时，调用此方法）
        __TreeNode *firstNode=MemoryManager<_DescriptorAllocator,__SizeType,__Alignment>::findFirstStart(this->getHead(),start,len);//ok,the information of head is ignored,it's full information is stored in it's sons
        spaces.setHead(this->allocOutNode(firstNode,start,len));//either not found or found,set the new manager
    }
    return spaces;
}

template<template <class> class _DescriptorAllocator,typename __SizeType,int __Alignment>
MemoryManager<_DescriptorAllocator,__SizeType,__Alignment>
MemoryManager<_DescriptorAllocator,__SizeType,__Alignment>::
allocFree(__SizeType len) {
    
    MemoryManager<_DescriptorAllocator,__SizeType>          spaces(this->smm);
    if(len<=0 || this->isNullManager() )
    {
        spaces.setNull();//ok
    }else{
        this->copyOnAllocation(this->getHead());//保证复制了父节点
        __TreeNode *firstNode=MemoryManager<_DescriptorAllocator,__SizeType,__Alignment>::findFirstLen(this->getHead(),len);//ok,the information of head is ignored,it's full information is stored in it's sons
        spaces.setHead(allocOutNode(firstNode,firstNode->getData().getStart(),len));//either not found or found,set the new manager
    }
    return spaces;
}

template<template <class> class _DescriptorAllocator,typename __SizeType,int __Alignment>
void* MemoryManager<_DescriptorAllocator,__SizeType,__Alignment>::
mnew(__SizeType start,__SizeType size)
{

    this->copyOnAllocation(this->getHead());//保证复制了父节点
    __TreeNode *found=MemoryManager<_DescriptorAllocator,__SizeType,__Alignment>::findFirstStart(this->getHead(),start,size);
#if defined(CODE64)
//    printf("MemoryManager mnew\n");
//    if(found==NULL)
//    {
//    	printf("found NULL\n");
//    }else{
//    	printf("found is %x,%x\n",found->getData().getStart(),found->getData().getLimit());
//    }
#endif
    if(found)
    {
        __TreeNode *alloced = allocOutNode(found,start,size);
        if(alloced)
        {
            return (void*)(alloced->getData().getStart());
        }
    }
    return NULL;    
}

template<template <class> class _DescriptorAllocator,typename __SizeType,int __Alignment>
void* MemoryManager<_DescriptorAllocator,__SizeType,__Alignment>::mnew(__SizeType size) {

    this->copyOnAllocation(this->getHead());//保证复制了父节点
    __TreeNode *found=MemoryManager<_DescriptorAllocator,__SizeType,__Alignment>::findFirstLen(this->getHead(),size);

    if(found)
    {
//    	Util::printf("found is ok.\n");
        __TreeNode *alloced = allocOutNode(found,found->getData().getStart(),size);
        if(alloced)
        {
            return (void*)(alloced->getData().getStart());
        }
    }
    return NULL;
}
template<template <class> class _DescriptorAllocator,typename __SizeType,int __Alignment>
void* MemoryManager<_DescriptorAllocator,__SizeType,__Alignment>::mnewAlign(__SizeType size,__SizeType alignment) {

    this->copyOnAllocation(this->getHead());//保证复制了父节点
    size_t extra;
    __TreeNode *found=MemoryManager<_DescriptorAllocator,__SizeType,__Alignment>::findFirstLenAlign(this->getHead(),size,extra,alignment);

    if(found)
    {
//    	Util::printf("found is ok.\n");
        __TreeNode *alloced = allocOutNode(found,found->getData().getStart()+extra,size);
        if(alloced)
        {
            return (void*)(alloced->getData().getStart());
        }
    }
    return NULL;
}
template<template <class> class _DescriptorAllocator,typename __SizeType,int __Alignment>
void*   MemoryManager<_DescriptorAllocator,__SizeType,__Alignment>::extend(__SizeType start,__SizeType size,int extsize,char *realBase,bool moveData)
{
//	Util::printf("extend arg: start,size,extsize = %d,%d,%d\n",start,size,extsize);
	if(extsize==0)return (char*)start;
    this->copyOnAllocation(this->getHead());//保证复制了父节点
    __TreeNode *found;
    if(extsize < 0)
    {
    	found=This::locateForDelete(this->getHead(), start, size, false);
    	if(!found)
    	{
    		return NULL;//can not find the node
    	}else{
    		if(size + extsize == 0)
    		{
    			this->withdrawNode(found);
    		}else{
        		found->getData().setLimit(size + extsize);
    		}
			return (char*)start;
    	}
    }
    char flag=this->findExtend(start, size, extsize, found);
    switch(flag)
    {
    	case 0:
//    			Util::printf("find extend returned 0\n");
    			return NULL;
			break;
		case 1:
//				Util::printf("find extend returned 1\n");
				this->allocOutNode(found, start + size, extsize);
				return (char*)start;
			break;
		case 2:
//				Util::printf("find extend returned 2\n");
				NodeType *todeleteOri=This::locateForDelete(this->getHead(), start, size,false);
				if(todeleteOri)
				{
					if(moveData)
					{
#if defined(CODE64) /*use memcopy*/
					memcpy(realBase + found->getData().getStart(),realBase + start,size);
#elif defined(CODE32)
					Util::memcopy(Util::SEG_CURRENT, (int)(size_t)(realBase + start),
							Util::SEG_CURRENT, (int)(size_t)(realBase + found->getData().getStart()), size);
#endif
					}
//					Util::printf("before withdrawn \n");
					this->withdrawNode(todeleteOri);
//					Util::printf("after withdrawn \n");
					this->allocOutNode(found, found->getData().getStart(), size + extsize);
					return (char*)found->getData().getStart();
				}else{
					return NULL;/*cannot locate the original node to delete*/
				}
			break;
    }

    // TODO 检查下面这个返回是否正确
    return NULL;

}
/**
*   Following:
*       find the exact node by required arguments with {starting with p, limit is size,not allocable}
*       if found,withdraw it to parent
*
*/

template<template <class> class _DescriptorAllocator,typename __SizeType,int __Alignment>
void MemoryManager<_DescriptorAllocator,__SizeType,__Alignment>::mdelete(void* p, __SizeType size) {
#if defined(CODE64)
//	printf("in mdelete,request for %x,%x\n",p,size);
#endif
    __TreeNode* toDeleteNode=This::locateForDelete(this->getHead(),(__SizeType)p,size,0);
#if defined(CODE64)
//    if(toDeleteNode==NULL)
//    {
//    	printf("found NULL \n");
//    }else{
//    	printf("found is  %x,%x\n",toDeleteNode->getData().getStart(),toDeleteNode->getData().getLimit());
//    }
#endif
    if(toDeleteNode)//if found it
    {
        //Util::printStr("Found delete.   ");
        this->withdrawNode(toDeleteNode);
    }
}

template<template <class> class _DescriptorAllocator,typename __SizeType,int __Alignment>
void MemoryManager<_DescriptorAllocator,__SizeType,__Alignment>::mdelete(void *p)
{
    __TreeNode* toDeleteNode=MemoryManager<_DescriptorAllocator,__SizeType,__Alignment>::locateForDeleteStart(this->getHead(),(__SizeType)p,0);
    if(toDeleteNode)//if found it
    {
        //Util::printStr("Found delete.   ");
        this->withdrawNode(toDeleteNode);
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

template<template <class> class _DescriptorAllocator,typename __SizeType,int __Alignment>
typename MemoryManager<_DescriptorAllocator,__SizeType,__Alignment>::__TreeNode *
MemoryManager<_DescriptorAllocator,__SizeType,__Alignment>::findFirstStart(
		__TreeNode* loc, __SizeType start,__SizeType len)
{
	__TreeNode* p=loc->getSon();
  
    // if(p)
    // {
    //     Test::dumpMemoryData(loc->getData());
    //     Test::dumpMemoryData(p->getData());
    // }else{
    //     Util::printStr("p is NULL \n");
    // }
	/*
	char saver[50];
	Util::printStr("in find...");
	Util::digitToStr(saver, 50, p->getData().getStart());
	Util::printStr(saver);Util::printStr("..");
	Util::digitToStr(saver, 50, start);
	Util::printStr(saver);Util::printStr("\n");
	*/
	if(p && !p->getData().isAllocable())
	{
		p=This::nextAllocable(p);
	}
	while(p && start > p->getData().getStart())
	{
		if(p->getData().contains(start,len))
		{
			break;
		}
        p=This::nextAllocable(p);
	}
	while(p && p->getData().getLimit() - len < start - p->getData().getStart() )
	{
        p=This::nextAllocable(p);
	}
	return p; //NULL or first valid section
}

template<template <class> class _DescriptorAllocator,typename __SizeType,int __Alignment>
typename MemoryManager<_DescriptorAllocator,__SizeType,__Alignment>::__TreeNode *
MemoryManager<_DescriptorAllocator,__SizeType,__Alignment>::findFirstLen(
		__TreeNode* loc, __SizeType len) {
	__TreeNode *p=loc->getSon();
	if(p && p->getData().isAllocable()==false)
	{
		p=This::nextAllocable(p);
	}
	while(p && p->getData().getLimit() < len )
    {
        p=This::nextAllocable(p);
    }
	return p;
}
/**
 * find one such has an alignment and enough space
 */
template<template <class> class _DescriptorAllocator,typename __SizeType,int __Alignment>
typename MemoryManager<_DescriptorAllocator,__SizeType,__Alignment>::__TreeNode *
 MemoryManager<_DescriptorAllocator,__SizeType,__Alignment>::findFirstLenAlign(
		__TreeNode* loc, __SizeType len,__SizeType &extra,__SizeType alignment) {
	if(alignment==0)return NULL;
	__TreeNode *p=loc->getSon();
	if(p && p->getData().isAllocable()==false)
	{
		p=This::nextAllocable(p);
	}
	while(p )
    {
		size_t left= p->getData().getStart()%alignment;
		if(left>0)
		{
			left=alignment - left;
		}
		if( p->getData().getLimit() >= len + left)
		{
			extra=left;
			return p;
		}
        p=This::nextAllocable(p);
    }
	return NULL;
}
template<template <class> class _DescriptorAllocator,typename __SizeType,int __Alignment>
int MemoryManager<_DescriptorAllocator,__SizeType,__Alignment>::isNullManager() {
	return this->getHead()==NULL;
}

template<template <class> class _DescriptorAllocator,typename __SizeType,int __Alignment>
void  MemoryManager<_DescriptorAllocator,__SizeType,__Alignment>::setNull()
{
    this->setHead(NULL);
}
#if defined(CODE32)
template<template <class> class _DescriptorAllocator,typename __SizeType,int __Alignment>
void MemoryManager<_DescriptorAllocator,__SizeType,__Alignment>::dumpInfo(Printer *p)const
{
	if(p!=NULL)
	{
		p->putsz("MemoryManager{");
		p->putsz("super:");Father::dumpInfo(p);p->putsz(", ");
		p->putx("base:",getBase(),", ");
		p->putx("limit:",getLimit(),", ");
		p->putsz("alloc_info:[");
		NodeType *node=Father::getHead()->getSon();
		while(node!=NULL)
		{
			p->putsz("(");
			p->putx("",node->getData().getStart(),",");
			p->putx("",node->getData().getLimit(),",");
			p->putx("",node->getData().isAllocable(),"), ");
			node=node->getNext();
		}
		p->putsz("]");
		p->putsz("}");
	}
}
#endif

//确保这条线段是位于两个分割点的缝隙之间，如果不是，返回NULL
template<template <class> class _DescriptorAllocator,typename __SizeType,int __Alignment>
typename MemoryManager<_DescriptorAllocator,__SizeType,__Alignment>::__TreeNode *
MemoryManager<_DescriptorAllocator,__SizeType,__Alignment>::locateForInsertation(
		__TreeNode* loc, __TreeNode* son) {
    if( loc==NULL || son==NULL)return NULL;
    __TreeNode* p=loc;
    __SizeType start=son->getData().getStart();
   __SizeType len=son->getData().getLimit();
    
	while(p && start - p->getData().getStart() < p->getData().getLimit() )
	{
		p=(__TreeNode*)p->getNext();
	}
	if(p)
    {
        if(p->getNext())
        {
            __TreeNode *forward=(__TreeNode*)p->getNext();
            
            // size_t - int = size_t
            if( (__SizeType)(forward->getData().getStart() - start) >= len)
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
template<template <class> class _DescriptorAllocator,typename __SizeType,int __Alignment>
typename MemoryManager<_DescriptorAllocator,__SizeType,__Alignment>::__TreeNode *
 MemoryManager<_DescriptorAllocator,__SizeType,__Alignment>::locateForDelete(__TreeNode* loc,__SizeType start,__SizeType len,bool allocable)
{
    if(loc==NULL||len==0)return NULL;
    __TreeNode* p=loc->getSon();

    while(p && p->getData().getStart() < start)
            p=(__TreeNode*)p->getNext();
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
template<template <class> class _DescriptorAllocator,typename __SizeType,int __Alignment>
typename MemoryManager<_DescriptorAllocator,__SizeType,__Alignment>::__TreeNode *
 MemoryManager<_DescriptorAllocator,__SizeType,__Alignment>::locateForDeleteStart(__TreeNode* loc,__SizeType start,bool allocable)
{
    if(loc==NULL)return NULL;
    __TreeNode* p=loc->getSon();

    while(p && p->getData().getStart() < start)
            p=(__TreeNode*)p->getNext();
    if(p && p->getData().getStart() == start && p->getData().isAllocable()==allocable)
    {
        return p;
    }else{
        return NULL;
    }

}



template<template <class> class _DescriptorAllocator,typename __SizeType,int __Alignment>
int MemoryManager<_DescriptorAllocator,__SizeType,__Alignment>::addToTree(__TreeNode* root,
		__TreeNode* son) {
            __TreeNode *location=MemoryManager<_DescriptorAllocator,__SizeType,__Alignment>::locateForInsertation(root,son);
            if(location)
            {
                
            }
            // TODO 完成这个函数
            return 0;
}
/**
* head mustn't be NULL!!
*/
template<template <class> class _DescriptorAllocator,typename __SizeType,int __Alignment>
typename MemoryManager<_DescriptorAllocator,__SizeType,__Alignment>::__TreeNode *
MemoryManager<_DescriptorAllocator,__SizeType,__Alignment>::copyOnAllocation(__TreeNode *head)
{
    if(!head->getSon())
    {
        const __MemoryDescriptor &data=head->getData();

        //*****
        //Util::printStr("copyOnAllocation -- ");
        //**********

        __TreeNode *newnode=this->smm->getNew();
        newnode->initToNull();
        new (newnode) __TreeNode(__MemoryDescriptor(data.getStart(),data.getLimit(),!data.isAllocable()));

        newnode->setFather(head);
        head->setSon(newnode);
        return newnode;
    }else{
        return head->getSon();    
    }
    

}

DEVEL_UNTESTED(Douglas_Fulton_Shaw)
DEVEL_AUTHOR(Douglas_Fulton_Shaw)
template<template <class> class _DescriptorAllocator,typename __SizeType,int __Alignment>
typename MemoryManager<_DescriptorAllocator,__SizeType,__Alignment>::__TreeNode *
MemoryManager<_DescriptorAllocator,__SizeType,__Alignment>::nextAllocable(
		__TreeNode* node) {
        if(node)
        {
            do{
                node=(__TreeNode*)node->getNext();
            }while( node && (node->getData().isAllocable()==false) );
        }
        return node;
}

//==========class:LinearSourceManager
template <class _LinearSourceDescriptor,template <class> class _NodeAllocator,typename __SizeType,int __Alignment>
LinearSourceManager<_LinearSourceDescriptor,_NodeAllocator ,__SizeType,__Alignment>::LinearSourceManager()
{
}

template <class _LinearSourceDescriptor,template <class> class _NodeAllocator,typename __SizeType,int __Alignment>
LinearSourceManager<_LinearSourceDescriptor,_NodeAllocator ,__SizeType,__Alignment>::LinearSourceManager(__Allocator *smm,
    __SizeType start,__SizeType size):
LocateableLinkedList<_LinearSourceDescriptor,Locator<_LinearSourceDescriptor>::DISCARD, _NodeAllocator,__SizeType>(smm),
space(_LinearSourceDescriptor(start,size))
{
	auto node=smm->getNew();
	node->initToNull();
	this->appendHead( new(node) __ListNode(space));

}

template <class _LinearSourceDescriptor,template <class> class _NodeAllocator,typename __SizeType,int __Alignment>
LinearSourceManager<_LinearSourceDescriptor,_NodeAllocator,__SizeType,__Alignment>::~LinearSourceManager()
{

}

template <class _LinearSourceDescriptor,template <class> class _NodeAllocator,typename __SizeType,int __Alignment>
void* LinearSourceManager<_LinearSourceDescriptor,_NodeAllocator ,__SizeType,__Alignment>::mnew(__SizeType start,__SizeType size)
{
    if(!this->checkRange(start,size))return NULL;
#if defined(CODE64)
//    printf("not null,request for (%x,%x)\n",start,size);
#endif
    __ListNode *found=Super::findFirstStartLen(this->getHead(),start,size);
#if defined(CODE64)
//    if(found)
//    {
//    	ListNode<LinearSourceDescriptor> *foundp=(ListNode<LinearSourceDescriptor>*)found;
//    	printf("found is (%x,%x)\n",foundp->getData().getStart(),foundp->getData().getLimit());
//    }else{
//    	printf("found is NULL\n");
//    }
#endif
    if(found)
    {
        _LinearSourceDescriptor alloced = this->allocOutNode(found,start,size);
        if(alloced.getLimit()>0)
        {
            return (void*)(alloced.getStart());
        }
    }
    return NULL;  
}
 
template <class _LinearSourceDescriptor,template <class> class _NodeAllocator,typename __SizeType,int __Alignment>
void* LinearSourceManager<_LinearSourceDescriptor,_NodeAllocator,__SizeType,__Alignment>::mnew(__SizeType size)
{
    __ListNode *found=Super::findFirstLen(this->getHead(),size);
    Util::printf("in lm,mnew for len %d\n",size);
    if(found)
    {
    	Util::printf("found is %d,%d\n",found->getData().getStart(),found->getData().getLimit());
        _LinearSourceDescriptor alloced = allocOutNode(found,found->getData().getStart(),size);
        if(alloced.getLimit())
        {
            return (void*)(alloced.getStart());
        }
    }
    Util::printf("found is NULL\n");
    return NULL;
}
template <class _LinearSourceDescriptor,template <class> class _NodeAllocator,typename __SizeType,int __Alignment>
void* LinearSourceManager<_LinearSourceDescriptor,_NodeAllocator,__SizeType,__Alignment>::extend(
		__SizeType start,__SizeType size,bool addOrReduce,__SizeType extsize,char *realBase,bool moveData)
{

	if(extsize == 0)return (char*)start;
    if(!this->checkRange(start,size))return NULL;//检查start,size是否是已经分配的内存区域，不能让错误扩散
    if(addOrReduce==false)//reduce
    {
    	if(extsize>size)extsize=size; //如果回收的长度超过所需，就直接回收全部就可以了
    	this->mdelete((char*)(start+size-extsize), extsize);
    	return (char*)start;
    }

    // 下面开始处理真正的扩展类型
    NodeType *found=Super::findFirstStartLen(this->getHead(),start+size,extsize);
    if(found && found->getData().getStart()==start + size)
    {
    		this->allocOutNode(found, start+size, extsize);
    		return (char*)start;
    }else{
    	found = Super::findFirstLen(this->getHead(), size + extsize);
    	if(found)
    	{
    		if(moveData)
    		{
#if defined(CODE64)
    		memcpy(realBase + found->getData().getStart(),realBase+start,size);
#elif defined(CODE32)
    		Util::memcopy(Util::SEG_CURRENT, (__SizeType)realBase + start, Util::SEG_CURRENT,(__SizeType)realBase + found->getData().getStart(),size);
#endif
    		}
		   this->mdelete((char*)start,size);
    		this->allocOutNode(found, found->getData().getStart(), size+extsize);
    		return (char*)found->getData().getStart();
    	}else{
    		return NULL;
    	}

    }
}

    
template <class _LinearSourceDescriptor,template <class> class _NodeAllocator,typename __SizeType,int __Alignment>
void LinearSourceManager<_LinearSourceDescriptor,_NodeAllocator ,__SizeType,__Alignment>::mdelete(void* p,__SizeType size)
{
    if(!this->checkRange((__SizeType)p,size))return;
    __ListNode *found=Super::findFirstStartForInsert(this->getHead(),(__SizeType)p);
    if(found)
    {
        int diff=found->getData().getStart()-(__SizeType)p;
        if(diff==0 || (diff>0 && !( This::checkPrevious(found->getPrevious(),(__SizeType)p) && This::checkNext(found,(__SizeType)p,size) ) ) ||
                      (diff<0 && !(This::checkPrevious(found,(__SizeType)p) && This::checkNext(found->getNext(),(__SizeType)p,size) )  )
                      )
        {
            //impossible to delete this memory
            return;
        }else{
            if(diff>0)
            {
                found->insertPrevious(new (this->smm->getNew()) __ListNode(_LinearSourceDescriptor((__SizeType)p,size)) );
            }else{
                found->insertNext(new (this->smm->getNew()) __ListNode(_LinearSourceDescriptor((__SizeType)p,size)) );
            }
        }
    }else{//empty list
        this->appendHead(_LinearSourceDescriptor((__SizeType)p,size));
    }

}
template <class _LinearSourceDescriptor,template <class> class _NodeAllocator,typename __SizeType,int __Alignment>
 bool LinearSourceManager<_LinearSourceDescriptor,_NodeAllocator ,__SizeType,__Alignment>::mnewLinked(__SizeType size,
		 __LinkedList&list,__SizeType eachSectionExtraSize)
{
//	printf("in mnewlinked,size is %d,this space is %d,%d\n",size,this->space.getStart(),this->space.getLimit());
	NodeType * p=this->getHead(),*lastAvl=NULL;
	if(p==NULL || size == 0)return false; //head is null or size is 0,no thing to look up.
	__SizeType leftSize=size;
	__SizeType nodesNum=0;
	__SizeType extraNeeded=0;
	//Do check first
	while(p)
	{
//		printf("leftSize is %d,current node is %d,%d\n",leftSize,  p->getData().getStart(),p->getData().getLimit());
		leftSize += eachSectionExtraSize;
		++nodesNum;
		if(leftSize > p->getData().getLimit())
		{
			leftSize  -=  p->getData().getLimit();
			lastAvl = p;
			p = p->getNext();
		}else{
			extraNeeded = leftSize;
			leftSize=0;
			lastAvl = p;
			break;
		}
	}
	if(leftSize>0)
	{
		return false;//space not enough
	}

	//===OK,we have enough space
	if(extraNeeded > 0)//not perfect,do need additional node,cannot just cut
	{// |leftSize| is the left to be kept in the original.
//		printf("avl has left,left is %d\n",leftSize);
		__SizeType orilimit=lastAvl->getData().getLimit();
		lastAvl->getData().setLimit(  extraNeeded );
		NodeType * newnode=new (this->smm->getNew()) NodeType(_LinearSourceDescriptor(
				lastAvl->getData().getStart() + lastAvl->getData().getLimit(),
				orilimit - extraNeeded
		));
		this->insertNext(lastAvl, newnode);
//		printf("avl = %d,%d  avl.next = %d,%d\n",lastAvl->getData().getStart(),lastAvl->getData().getLimit(),
//				lastAvl->getNext()->getData().getStart(),lastAvl->getNext()->getData().getLimit());
	}
	list.appendHead(this->getHead());
//	printf("list.head is %d,%d\n",list.getHead()->getData().getStart(),list.getHead()->getData().getLimit());
	this->root->setNext(NULL);
	this->last->setNext(NULL);
	this->appendHead(lastAvl->getNext());
	lastAvl->setNext(NULL);

//	printf("list.head is %d,%d\n",list.getHead()->getData().getStart(),list.getHead()->getData().getLimit());
	return true;

}




template <class _LinearSourceDescriptor,template <class> class _NodeAllocator,typename __SizeType,int __Alignment>
void  LinearSourceManager<_LinearSourceDescriptor,_NodeAllocator ,__SizeType,__Alignment>::
mdeleteLinked(__LinkedList& list)
{
	NodeType *p=list.getHead();
	while(p)
	{
		this->mdelete((char*)p->getData().getStart(),p->getData().getLimit());
		p=p->getNext();
	}
}

template <class _LinearSourceDescriptor,template <class> class _NodeAllocator,typename __SizeType,int __Alignment>
 bool LinearSourceManager<_LinearSourceDescriptor,_NodeAllocator ,__SizeType,__Alignment>::checkRange(__SizeType start,__SizeType size)
 {
    return (this->space.getStart() <= start) && (start-this->space.getStart() <= this->space.getLimit() - size );
 }
template <class _LinearSourceDescriptor,template <class> class _NodeAllocator,typename __SizeType,int __Alignment>
 bool LinearSourceManager<_LinearSourceDescriptor,_NodeAllocator ,__SizeType,__Alignment>::checkRange(__SizeType start)
 {
    return this->space.getStart() <= start;
 }

template <class _LinearSourceDescriptor,template <class> class _NodeAllocator,typename __SizeType,int __Alignment>
bool LinearSourceManager<_LinearSourceDescriptor,_NodeAllocator,__SizeType,__Alignment>::checkPrevious(__ListNode *prev,__SizeType start)
{
    return !prev || (start - prev->getData().getStart() >= prev->getData().getLimit());
}

template <class _LinearSourceDescriptor,template <class> class _NodeAllocator,typename __SizeType,int __Alignment>
bool LinearSourceManager<_LinearSourceDescriptor,_NodeAllocator ,__SizeType,__Alignment>::checkNext(__ListNode *nxt,__SizeType start,__SizeType len)
{
    return !nxt || (nxt->getData().getStart() - start >= len );
}
/**
 *  start & len should reside in avlNode
 *  then this will always return true.
 *
 *  But currently we don't have that promise,So check the returned node if it havs a positive limit
 */
template <class _LinearSourceDescriptor,template <class> class _NodeAllocator,typename __SizeType,int __Alignment>
_LinearSourceDescriptor LinearSourceManager<_LinearSourceDescriptor,_NodeAllocator ,__SizeType,__Alignment>::allocOutNode(__ListNode *avlNode,__SizeType start,__SizeType len)
{
	_LinearSourceDescriptor newnode(start,len);
    if(avlNode)
    {
        int len1=start - avlNode->getData().getStart();
        int len2=avlNode->getData().getLimit() - len - len1;
#if defined(CODE64)
        //printf("len1=%x,len2=%x\n",len1,len2);
#endif
        if(len1<0 || len2 < 0)newnode.setLimit(0);
        else if(len1==0 && len2==0)//前后都没有剩余
        {
#if defined(CODE64)
//        	printf("remove whole node\n");
#endif
            this->remove(avlNode);
        }else if(len1==0 && len2 > 0){//后面有剩余
            avlNode->getData().setStart(start+len);
            avlNode->getData().setLimit(len2);
#if defined(CODE64)
//            printf("reset avlnode,no adding or removing\n");
#endif
        }else if(len1 > 0 && len2==0){//前面有剩余
            avlNode->getData().setLimit(len1);
        }else{//前后都有剩余
            avlNode->getData().setLimit(len1);
            this->insertNext(avlNode, new (this->smm->getNew()) __ListNode(_LinearSourceDescriptor(start+len,len2)) );

        }
    }
    return newnode;
}
    

