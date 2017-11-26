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
	template class MemoryManager<SimpleMemoryManager>;
	template class MemoryManager<KernelSmmWrapper>;
#elif defined(CODE64)

#include <cstdio>
#include <cstring>
#include <64/MallocToSimple.h>
#include <EnvInterface64Impl.h>
#include <File.h>
	template class MemoryManager<MallocToSimple64Impl>;
	template class MemoryManager<X2fsUtil<EnvInterface64Impl>::PartialMallocToSimple>;
	template class LinearSourceManager<LinearSourceDescriptor, MallocToSimple64Impl>;
	template class LinearSourceManager<LinearSourceDescriptor, X2fsUtil<EnvInterface64Impl>::PartialMallocToSimple>;
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
template<template <class> class _DescriptorAllocator>
MemoryManager<_DescriptorAllocator>::MemoryManager(_DescriptorAllocator<TreeNode<MemoryDescriptor> > *smm)
:
Tree<MemoryDescriptor,_DescriptorAllocator>(smm) //调用父类的构造函数
{

}
template<template <class> class _DescriptorAllocator>
MemoryManager<_DescriptorAllocator>::MemoryManager(_DescriptorAllocator<TreeNode<MemoryDescriptor> > *smm,size_t start,size_t len,bool fatherAllocable)
:MemoryManager(smm)
//:dbg1("MemoryManager 1\n")
{
#if defined(CODE64)
	//printf("set Head\n");
#endif
	// root->son = new_node, 也就是head， 但是head不指向root，也就是说指针时单向的
	//Kernel::printer->move(-40);


	TreeNode<MemoryDescriptor> *head=smm->getNew();

	new (head) TreeNode<MemoryDescriptor>(MemoryDescriptor(start,len,fatherAllocable));

	this->setHead(head);

	//===分配内存


#if defined(CODE64)
    //printf("in constructor : ");
    //getchar();
    //printf("%x ~ %x\n",this->getHead()->getData().getStart(),this->getHead()->getData().getLimit());
#endif
}
template<template <class> class _DescriptorAllocator>
MemoryManager<_DescriptorAllocator>::MemoryManager(_DescriptorAllocator<TreeNode<MemoryDescriptor> > *smm,size_t start,size_t len,
		size_t usedList[][2],size_t usedLen,bool fatherAllocable):MemoryManager(smm,start,len,fatherAllocable)
{
	for(size_t i=0;i<usedLen;i++)
		mnew(usedList[i][0], usedList[i][1]);
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

//	Util::printf("in mm allocOut for %x,%x\n",start,len);
    // Test::dumpMemoryData(avlNode->getData());
    TreeNode<MemoryDescriptor> *newnode=NULL;
    if(avlNode)
    {
        size_t len1=(size_t)(start-avlNode->getData().getStart());
        size_t len2=(size_t)(avlNode->getData().getLimit() - len - len1);
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
             new (newnode) TreeNode<MemoryDescriptor>(MemoryDescriptor(start,len,false));//新建一个node，不可用于分配
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
        	TreeNode<MemoryDescriptor> *newnodeEnd=this->smm->getNew();
        	newnodeEnd->initToNull();

//        	Util::printf("after smm new \n");
            new (newnodeEnd) TreeNode<MemoryDescriptor>(MemoryDescriptor(start+len,len2));
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

template<template <class> class _DescriptorAllocator>
void MemoryManager<_DescriptorAllocator>::withdrawNode(TreeNode<MemoryDescriptor> *exactNode)
{
    //先释放其所有子节点
    TreeNode<MemoryDescriptor> *p=exactNode->getSon();
    while(p)
    {
        this->free(p);
        p=(TreeNode<MemoryDescriptor>*)p->getNext();
    }
//    Util::printf("in mm,withdrawNode \n");
    exactNode->setSon(NULL);//free完毕

    //开始合并
    TreeNode<MemoryDescriptor> *prev=(TreeNode<MemoryDescriptor>*)exactNode->getPrevious();
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

    TreeNode<MemoryDescriptor> *nxt=(TreeNode<MemoryDescriptor>*)prev->getNext();
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
template<template<class > class _DescriptorAllocator>
char MemoryManager<_DescriptorAllocator>::findExtend(size_t start,
		size_t size, size_t extsize,TreeNode<MemoryDescriptor> * &rtnode) const
{
//	Util::printf("in findExtend,start=%x,size=%x,extsize=%d\n",start,size,extsize);
	if(extsize==0)return false;
	TreeNode<MemoryDescriptor>* found=This::findFirstStart(this->getHead(), start + size, extsize);/*starts at start or upper,hold size or more*/
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
template<template <class> class _DescriptorAllocator>
MemoryManager<_DescriptorAllocator> MemoryManager<_DescriptorAllocator>::allocFreeStart(size_t start,size_t len) {
    // Util::printStr("Enter allocFreeStart: ");
    
    MemoryManager<_DescriptorAllocator>          spaces(this->smm);
    if(len<=0 || this->isNullManager() )
    {
        spaces.setNull();//ok
    }else{
        this->copyOnAllocation(this->getHead());//保证复制了父节点(当父节点可用于分配但是子节点中没有任何一个节点时，调用此方法）
        TreeNode<MemoryDescriptor> *firstNode=MemoryManager<_DescriptorAllocator>::findFirstStart(this->getHead(),start,len);//ok,the information of head is ignored,it's full information is stored in it's sons
        spaces.setHead(this->allocOutNode(firstNode,start,len));//either not found or found,set the new manager
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
        this->copyOnAllocation(this->getHead());//保证复制了父节点
        TreeNode<MemoryDescriptor> *firstNode=MemoryManager<_DescriptorAllocator>::findFirstLen(this->getHead(),len);//ok,the information of head is ignored,it's full information is stored in it's sons
        spaces.setHead(allocOutNode(firstNode,firstNode->getData().getStart(),len));//either not found or found,set the new manager
    }
    return spaces;
}

template<template <class> class _DescriptorAllocator>
void* MemoryManager<_DescriptorAllocator>::mnew(size_t start,size_t size)
{

    this->copyOnAllocation(this->getHead());//保证复制了父节点
    TreeNode<MemoryDescriptor> *found=MemoryManager<_DescriptorAllocator>::findFirstStart(this->getHead(),start,size);
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
        TreeNode<MemoryDescriptor> *alloced = allocOutNode(found,start,size);
        if(alloced)
        {
            return (void*)(alloced->getData().getStart());
        }
    }
    return NULL;    
}

template<template <class> class _DescriptorAllocator>
void* MemoryManager<_DescriptorAllocator>::mnew(size_t size) {

    this->copyOnAllocation(this->getHead());//保证复制了父节点
    TreeNode<MemoryDescriptor> *found=MemoryManager<_DescriptorAllocator>::findFirstLen(this->getHead(),size);

    if(found)
    {
//    	Util::printf("found is ok.\n");
        TreeNode<MemoryDescriptor> *alloced = allocOutNode(found,found->getData().getStart(),size);
        if(alloced)
        {
            return (void*)(alloced->getData().getStart());
        }
    }
    return NULL;
}
template<template <class> class _DescriptorAllocator>
void* MemoryManager<_DescriptorAllocator>::mnewAlign(size_t size,size_t alignment) {

    this->copyOnAllocation(this->getHead());//保证复制了父节点
    size_t extra;
    TreeNode<MemoryDescriptor> *found=MemoryManager<_DescriptorAllocator>::findFirstLenAlign(this->getHead(),size,extra,alignment);

    if(found)
    {
//    	Util::printf("found is ok.\n");
        TreeNode<MemoryDescriptor> *alloced = allocOutNode(found,found->getData().getStart()+extra,size);
        if(alloced)
        {
            return (void*)(alloced->getData().getStart());
        }
    }
    return NULL;
}
template<template <class> class _DescriptorAllocator>
void*   MemoryManager<_DescriptorAllocator>::extend(size_t start,size_t size,int extsize,char *realBase,bool moveData)
{
//	Util::printf("extend arg: start,size,extsize = %d,%d,%d\n",start,size,extsize);
	if(extsize==0)return (char*)start;
    this->copyOnAllocation(this->getHead());//保证复制了父节点
    TreeNode<MemoryDescriptor> *found;
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

template<template <class> class _DescriptorAllocator>
void MemoryManager<_DescriptorAllocator>::mdelete(void* p, size_t size) {
#if defined(CODE64)
//	printf("in mdelete,request for %x,%x\n",p,size);
#endif
    TreeNode<MemoryDescriptor>* toDeleteNode=This::locateForDelete(this->getHead(),(size_t)p,size,0);
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

template<template <class> class _DescriptorAllocator>
void MemoryManager<_DescriptorAllocator>::mdelete(void *p)
{
    TreeNode<MemoryDescriptor>* toDeleteNode=MemoryManager<_DescriptorAllocator>::locateForDeleteStart(this->getHead(),(size_t)p,0);
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

template<template <class> class _DescriptorAllocator>
TreeNode<MemoryDescriptor>* MemoryManager<_DescriptorAllocator>::findFirstLen(
		TreeNode<MemoryDescriptor>* loc, size_t len) {
	TreeNode<MemoryDescriptor> *p=loc->getSon();
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
template<template <class> class _DescriptorAllocator>
TreeNode<MemoryDescriptor>* MemoryManager<_DescriptorAllocator>::findFirstLenAlign(
		TreeNode<MemoryDescriptor>* loc, size_t len,size_t &extra,size_t alignment) {
	if(alignment==0)return NULL;
	TreeNode<MemoryDescriptor> *p=loc->getSon();
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
template<template <class> class _DescriptorAllocator>
int MemoryManager<_DescriptorAllocator>::isNullManager() {
	return this->getHead()==NULL;
}

template<template <class> class _DescriptorAllocator>
void  MemoryManager<_DescriptorAllocator>::setNull()
{
    this->setHead(NULL);
}
#if defined(CODE32)
template<template <class> class _DescriptorAllocator>
void MemoryManager<_DescriptorAllocator>::dumpInfo(Printer *p)const
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
template<template <class> class _DescriptorAllocator>
TreeNode<MemoryDescriptor>* MemoryManager<_DescriptorAllocator>::locateForInsertation(
		TreeNode<MemoryDescriptor>* loc, TreeNode<MemoryDescriptor>* son) {
    if( loc==NULL || son==NULL)return NULL;
    TreeNode<MemoryDescriptor>* p=loc;
    int start=son->getData().getStart();
    unsigned int len=son->getData().getLimit();
    
	while(p && start - p->getData().getStart() < p->getData().getLimit() )
	{
		p=(TreeNode<MemoryDescriptor>*)p->getNext();
	}
	if(p)
    {
        if(p->getNext())
        {
            TreeNode<MemoryDescriptor> *forward=(TreeNode<MemoryDescriptor>*)p->getNext();
            
            // size_t - int = size_t
            if(forward->getData().getStart() - start >= len)
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
            p=(TreeNode<MemoryDescriptor>*)p->getNext();
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
            p=(TreeNode<MemoryDescriptor>*)p->getNext();
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
            // TODO 完成这个函数
            return 0;
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

        TreeNode<MemoryDescriptor> *newnode=this->smm->getNew();
        newnode->initToNull();
        new (newnode) TreeNode<MemoryDescriptor>(MemoryDescriptor(data.getStart(),data.getLimit(),!data.isAllocable()));

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
                node=(TreeNode<MemoryDescriptor>*)node->getNext();
            }while( node && (node->getData().isAllocable()==false) );
        }
        return node;
}

//==========class:LinearSourceManager
template <class _LinearSourceDescriptor,template <class> class _NodeAllocator>
LinearSourceManager<_LinearSourceDescriptor,_NodeAllocator >::LinearSourceManager()
{
}

template <class _LinearSourceDescriptor,template <class> class _NodeAllocator>
LinearSourceManager<_LinearSourceDescriptor,_NodeAllocator >::LinearSourceManager(_NodeAllocator<ListNode<_LinearSourceDescriptor> > *smm,
    size_t start,size_t size):
LocateableLinkedList<_LinearSourceDescriptor,Locator<_LinearSourceDescriptor>::DISCARD, _NodeAllocator >(smm),
space(_LinearSourceDescriptor(start,size))
{
	auto node=smm->getNew();
	node->initToNull();
	this->appendHead( new(node) ListNode<_LinearSourceDescriptor>(space));
}

template <class _LinearSourceDescriptor,template <class> class _NodeAllocator>
LinearSourceManager<_LinearSourceDescriptor,_NodeAllocator >::~LinearSourceManager()
{

}

template <class _LinearSourceDescriptor,template <class> class _NodeAllocator>
void* LinearSourceManager<_LinearSourceDescriptor,_NodeAllocator >::mnew(size_t start,size_t size)
{
    if(!this->checkRange(start,size))return NULL;
#if defined(CODE64)
//    printf("not null,request for (%x,%x)\n",start,size);
#endif
    ListNode<_LinearSourceDescriptor> *found=Father::findFirstStartLen(this->getHead(),start,size);
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
 
template <class _LinearSourceDescriptor,template <class> class _NodeAllocator>
void* LinearSourceManager<_LinearSourceDescriptor,_NodeAllocator >::mnew(size_t size)
{
    ListNode<_LinearSourceDescriptor> *found=Father::findFirstLen(this->getHead(),size);
//    Util::printf("in lm,mnew for len %d\n",size);
    if(found)
    {
//    	Util::printf("found is %x,%x\n",found->getData().getStart(),found->getData().getLimit());
        _LinearSourceDescriptor alloced = allocOutNode(found,found->getData().getStart(),size);
        if(alloced.getLimit())
        {
            return (void*)(alloced.getStart());
        }
    }
//    Util::printf("found is NULL\n");
    return NULL;
}
template <class _LinearSourceDescriptor,template <class> class _NodeAllocator>
void* LinearSourceManager<_LinearSourceDescriptor,_NodeAllocator >::extend(size_t start,size_t size,int extsize,char *realBase,bool moveData)
{

	if(extsize == 0)return (char*)start;
    if(!this->checkRange(start,size))return NULL;
    if(extsize<0)
    {
    	this->mdelete((char*)(start+size+extsize),0 - extsize);
    	return (char*)start;
    }
    NodeType *found=Father::findFirstStartLen(this->getHead(),start+size,extsize);
    if(found && found->getData().getStart()==start + size)
    {
    		this->allocOutNode(found, start+size, extsize);
    		return (char*)start;
    }else{
    	found = Father::findFirstLen(this->getHead(), size + extsize);
    	if(found)
    	{
    		if(moveData)
    		{
#if defined(CODE64)
    		memcpy(realBase + found->getData().getStart(),realBase+start,size);
#elif defined(CODE32)
    		Util::memcopy(Util::SEG_CURRENT, (size_t)realBase + start, Util::SEG_CURRENT,(size_t)realBase + found->getData().getStart(),size);
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

    
template <class _LinearSourceDescriptor,template <class> class _NodeAllocator>
void LinearSourceManager<_LinearSourceDescriptor,_NodeAllocator >::mdelete(void* p,size_t size)
{
    if(!this->checkRange((size_t)p,size))return;
    ListNode<_LinearSourceDescriptor> *found=Father::findFirstStartForInsert(this->getHead(),(size_t)p);
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
        this->appendHead(_LinearSourceDescriptor((size_t)p,size));
    }

}
template<class _LinearSourceDescriptor, template<class > class _NodeAllocator>
 bool LinearSourceManager<_LinearSourceDescriptor,_NodeAllocator>::mnewLinked(size_t size,LinkedList<LinearSourceDescriptor, _NodeAllocator> &list,size_t eachSectionExtraSize)
{
//	printf("in mnewlinked,size is %d,this space is %d,%d\n",size,this->space.getStart(),this->space.getLimit());
	NodeType * p=this->getHead(),*lastAvl=NULL;
	if(p==NULL || size == 0)return false; //head is null or size is 0,no thing to look up.
	int leftSize=size;
	//Do check first
	while(p && leftSize > 0)
	{
//		printf("leftSize is %d,current node is %d,%d\n",leftSize,  p->getData().getStart(),p->getData().getLimit());
		leftSize =leftSize + eachSectionExtraSize -  p->getData().getLimit();
		lastAvl = p;
		p = p->getNext();
	}
	if(leftSize>0)
	{
		return false;//space not enough
	}
	//===OK,we have enough space
	if(leftSize < 0)//not perfect,do need additional node,cannot just cut
	{// |leftSize| is the left to be kept in the original.
		leftSize = -leftSize;
//		printf("avl has left,left is %d\n",leftSize);
		size_t orilimit=lastAvl->getData().getLimit();
		lastAvl->getData().setLimit( orilimit  - leftSize );
		NodeType * newnode=new (this->smm->getNew()) NodeType(_LinearSourceDescriptor(
				lastAvl->getData().getStart() + lastAvl->getData().getLimit(),
				leftSize
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




template<class _LinearSourceDescriptor, template<class > class _NodeAllocator>
void  LinearSourceManager<_LinearSourceDescriptor,_NodeAllocator>::mdeleteLinked(LinkedList<LinearSourceDescriptor, _NodeAllocator>& list)
{
	NodeType *p=list.getHead();
	while(p)
	{
		this->mdelete((char*)p->getData().getStart(),p->getData().getLimit());
		p=p->getNext();
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
            this->insertNext(avlNode, new (this->smm->getNew()) ListNode<_LinearSourceDescriptor>(_LinearSourceDescriptor(start+len,len2)) );

        }
    }
    return newnode;
}
    

