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



#if defined(CODE32)||defined(CODE16)
#include <test.h>
#endif

//=============template ininstantiate
#if defined(CODE32)
	template class MemoryManager<SimpleMemoryManager,u32_t>;
	template class MemoryManager<KernelSmmWrapper,u32_t>;
#elif defined(CODE64)
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
#define __DEF_Template_MemoryManager template<template <class> class _DescriptorAllocator>
#define __DEF_MemoryManager MemoryManager<_DescriptorAllocator>
__DEF_Template_MemoryManager
__DEF_MemoryManager::
MemoryManager(__Allocator &smm)
:Super(smm) //调用父类的构造函数
{

}
__DEF_Template_MemoryManager
__DEF_MemoryManager::MemoryManager(
		__Allocator &smm,__SizeType start,__SizeType len,bool fatherAllocable)
:Super(smm)
{
	__TreeNode *head=this->newOneNode();
	if(!head)
		HostEnv::systemAbort("init MemoryManager,head returned nullptr", -2);
	new (head) __TreeNode(__MemoryDescriptor(start,len,fatherAllocable));
	this->setHead(head);
}
__DEF_Template_MemoryManager
__DEF_MemoryManager::
MemoryManager(__Allocator &smm,__SizeType start,__SizeType len,
		__SizeType usedList[][2],__SizeType usedLen,bool fatherAllocable):MemoryManager(smm,start,len,fatherAllocable)
{
	for(size_t i=0;i<usedLen;i++)
		mnew(usedList[i][0], usedList[i][1]);
}

__DEF_Template_MemoryManager
__DEF_MemoryManager::~MemoryManager()
{
	// 没有任何事情要做，所有的节点会被父类撤销

}

__DEF_Template_MemoryManager
void __DEF_MemoryManager::withdrawToParent()
{
    //回收后进行两点之间的检查，如果能够合并就进行合并
    __TreeNode *head=this->getHead();
    if(head)
    {
        //顶级管理器和非顶级管理器操作相同
        this->withdrawNode(head);
        //但是如果是顶级管理器，father为nullptr，所以需要将其从smm中撤销
        if(!head->getParent())//顶级管理器
        {
            this->smm.withdraw(head);
            this->setHead(nullptr);
        }
    }
}
/**
*   for nodes found available for allocation,here will spilt it out
*   it will:
*       adjust the node before and after the desired area
*       return a node denoting the desired area
*   accept:
*       avlNode = nullptr
*   do not accept:
*       the area start and len denoted is not logically inside avlNode
*       means avlNode,start,len should be derived from the inner method
*/

__DEF_Template_MemoryManager
typename __DEF_MemoryManager::__TreeNode*
__DEF_MemoryManager::allocOutNode(__TreeNode *avlNode,__SizeType start,__SizeType len)
{

//	Util::printf("in mm allocOut for %x,%x\n",start,len);
    // Test::dumpMemoryData(avlNode->getData());
    __TreeNode *newnode=nullptr;
    if(avlNode)
    {
        __SizeType len1= reinterpret_cast<__SizeType>(start-avlNode->getData().getStart());
        __SizeType len2= reinterpret_cast<__SizeType>(avlNode->getData().getLimit() - len - len1);
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
            newnode = this->newOneNode();
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
        	__TreeNode *newnodeEnd=this->newOneNode();
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
*                                                            in another words, a node is consistence only when isAllocable()=(getSon()==nullptr)
* do not accept:
*       exactNode==nullptr
*/

__DEF_Template_MemoryManager
void __DEF_MemoryManager::withdrawNode(__TreeNode *exactNode)
{
	if(!exactNode)return;
    //先释放其所有子节点
    this->freeAll(exactNode->getSon());
//    Util::printf("in mm,withdrawNode \n");
    exactNode->setSon(nullptr);//free完毕

    //开始合并左右节点
    __TreeNode *prev=exactNode->getPrevious();
    if(prev && prev->getData().isAllocable() &&
    		exactNode->getData().getStart() - prev->getData().getStart() == prev->getData().getLimit() )
    {
    //	Util::printStr("combine..");
        prev->getData().setLimit(prev->getData().getLimit() + exactNode->getData().getLimit() );
        prev->removeNext();//移除冗余节点
        this->withdrawNode(exactNode);
    }else{
        prev=exactNode;
        prev->getData().setAllocable(true);
    }//OK,the previous node cheking is done

    __TreeNode *nxt=prev->getNext();
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
        this->freeOneNode(nxt);
    }else{//do nothing

    }

}
__DEF_Template_MemoryManager
u8_t __DEF_MemoryManager::findExtend(__SizeType start,
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
	}else{//nullptr or not extensible
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
__DEF_Template_MemoryManager
typename __DEF_MemoryManager::__MemoryManager
__DEF_MemoryManager::allocFreeStart(__SizeType start,__SizeType len) {
    // Util::printStr("Enter allocFreeStart: ");
    
    __MemoryManager         spaces(this->smm);
    if(len<=0 || this->isnullptrManager() )
    {
        spaces.setnullptr();//ok
    }else{
        this->copyOnAllocation(this->getHead());//保证复制了父节点(当父节点可用于分配但是子节点中没有任何一个节点时，调用此方法）
        __TreeNode *firstNode=__MemoryManager::findFirstStart(this->getHead(),start,len);//ok,the information of head is ignored,it's full information is stored in it's sons
        spaces.setHead(this->allocOutNode(firstNode,start,len));//either not found or found,set the new manager
    }
    return spaces;
}

__DEF_Template_MemoryManager
typename __DEF_MemoryManager::__MemoryManager
__DEF_MemoryManager::
allocFree(__SizeType len) {
    
    __MemoryManager         spaces(this->smm);
    if(len<=0 || this->isnullptrManager() )
    {
        spaces.setnullptr();//ok
    }else{
        this->copyOnAllocation(this->getHead());//保证复制了父节点
        __TreeNode *firstNode=This::findFirstLen(this->getHead(),len);//ok,the information of head is ignored,it's full information is stored in it's sons
        spaces.setHead(allocOutNode(firstNode,firstNode->getData().getStart(),len));//either not found or found,set the new manager
    }
    return spaces;
}

__DEF_Template_MemoryManager
void* __DEF_MemoryManager::
mnew(__SizeType start,__SizeType size)
{

    this->copyOnAllocation(this->getHead());//保证复制了父节点
    __TreeNode *found=__DEF_MemoryManager::findFirstStart(this->getHead(),start,size);
#if defined(CODE64)
//    printf("MemoryManager mnew\n");
//    if(found==nullptr)
//    {
//    	printf("found nullptr\n");
//    }else{
//    	printf("found is %x,%x\n",found->getData().getStart(),found->getData().getLimit());
//    }
#endif
    if(found)
    {
        __TreeNode *alloced = allocOutNode(found,start,size);
        if(alloced)
        {
            return reinterpret_cast<void*>((alloced->getData()).getStart());
        }
    }
    return nullptr;
}

__DEF_Template_MemoryManager
void* __DEF_MemoryManager::mnew(__SizeType size) {

    this->copyOnAllocation(this->getHead());//保证复制了父节点
    __TreeNode *found=__DEF_MemoryManager::findFirstLen(this->getHead(),size);

    if(found)
    {
//    	Util::printf("found is ok.\n");
        __TreeNode *alloced = allocOutNode(found,found->getData().getStart(),size);
        if(alloced)
        {
            return reinterpret_cast<void*>((alloced->getData()).getStart());
        }
    }
    return nullptr;
}
__DEF_Template_MemoryManager
void* __DEF_MemoryManager::mnewAlign(__SizeType size,__SizeType alignment) {

    this->copyOnAllocation(this->getHead());//保证复制了父节点
    size_t extra;
    __TreeNode *found=__DEF_MemoryManager::findFirstLenAlign(this->getHead(),size,extra,alignment);

    if(found)
    {
//    	Util::printf("found is ok.\n");
        __TreeNode *alloced = allocOutNode(found,found->getData().getStart()+extra,size);
        if(alloced)
        {
            return reinterpret_cast<void*>((alloced->getData()).getStart());
        }
    }
    return nullptr;
}
__DEF_Template_MemoryManager
void*   __DEF_MemoryManager::extend(__SizeType start,__SizeType size,int extsize,char *realBase,bool moveData)
{
//	Util::printf("extend arg: start,size,extsize = %d,%d,%d\n",start,size,extsize);
	if(extsize==0)return reinterpret_cast<char*>(start);
    this->copyOnAllocation(this->getHead());//保证复制了父节点
    __TreeNode *found;
    if(extsize < 0)
    {
    	found=This::locateForDelete(this->getHead(), start, size, false);
    	if(!found)
    	{
    		return nullptr;//can not find the node
    	}else{
    		if(size + extsize == 0)
    		{
    			this->withdrawNode(found);
    		}else{
        		found->getData().setLimit(size + extsize);
    		}
			return reinterpret_cast<char*>(start);
    	}
    }
    char flag=this->findExtend(start, size, extsize, found);
    switch(flag)
    {
    	case 0:
//    			Util::printf("find extend returned 0\n");
    			return nullptr;
			break;
		case 1:
//				Util::printf("find extend returned 1\n");
				this->allocOutNode(found, start + size, extsize);
				return reinterpret_cast<char*>(start);
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
							Util::SEG_CURRENT, reinterpret_cast<int>((size_t))(realBase + found->getData().getStart()), size);
#endif
					}
//					Util::printf("before withdrawn \n");
					this->withdrawNode(todeleteOri);
//					Util::printf("after withdrawn \n");
					this->allocOutNode(found, found->getData().getStart(), size + extsize);
					return reinterpret_cast<char*>(found->getData().getStart());
				}else{
					return nullptr;/*cannot locate the original node to delete*/
				}
			break;
    }

    // TODO 检查下面这个返回是否正确
    return nullptr;

}
/**
*   Following:
*       find the exact node by required arguments with {starting with p, limit is size,not allocable}
*       if found,withdraw it to parent
*
*/

__DEF_Template_MemoryManager
void __DEF_MemoryManager::mdelete(void* p, __SizeType size) {
#if defined(CODE64)
//	printf("in mdelete,request for %x,%x\n",p,size);
#endif
    __TreeNode* toDeleteNode=This::locateForDelete(this->getHead(), reinterpret_cast<__SizeType>(p),size,0);
#if defined(CODE64)
//    if(toDeleteNode==nullptr)
//    {
//    	printf("found nullptr \n");
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

__DEF_Template_MemoryManager
void __DEF_MemoryManager::mdelete(void *p)
{
    __TreeNode* toDeleteNode=__DEF_MemoryManager::locateForDeleteStart(this->getHead(),reinterpret_cast<__SizeType>(p),0);
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

__DEF_Template_MemoryManager
typename __DEF_MemoryManager::__TreeNode *
__DEF_MemoryManager::findFirstStart(
		__TreeNode* loc, __SizeType start,__SizeType len)
{
	__TreeNode* p=loc->getSon();
  
    // if(p)
    // {
    //     Test::dumpMemoryData(loc->getData());
    //     Test::dumpMemoryData(p->getData());
    // }else{
    //     Util::printStr("p is nullptr \n");
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
	return p; //nullptr or first valid section
}

__DEF_Template_MemoryManager
typename __DEF_MemoryManager::__TreeNode *
__DEF_MemoryManager::findFirstLen(
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
__DEF_Template_MemoryManager
typename __DEF_MemoryManager::__TreeNode *
 __DEF_MemoryManager::findFirstLenAlign(
		__TreeNode* loc, __SizeType len,__SizeType &extra,__SizeType alignment) {
	if(alignment==0)return nullptr;
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
	return nullptr;
}
__DEF_Template_MemoryManager
int __DEF_MemoryManager::isnullptrManager() {
	return this->getHead()==nullptr;
}

__DEF_Template_MemoryManager
void  __DEF_MemoryManager::setnullptr()
{
    this->setHead(nullptr);
}
#if defined(CODE32)
__DEF_Template_MemoryManager
void __DEF_MemoryManager::dumpInfo(Printer *p)const
{
	if(p!=nullptr)
	{
		p->putsz("MemoryManager{");
		p->putsz("super:");Father::dumpInfo(p);p->putsz(", ");
		p->putx("base:",getBase(),", ");
		p->putx("limit:",getLimit(),", ");
		p->putsz("alloc_info:[");
		NodeType *node=Father::getHead()->getSon();
		while(node!=nullptr)
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

//确保这条线段是位于两个分割点的缝隙之间，如果不是，返回nullptr
__DEF_Template_MemoryManager
typename __DEF_MemoryManager::__TreeNode *
__DEF_MemoryManager::locateForInsertation(
		__TreeNode* loc, __TreeNode* son) {
    if( loc==nullptr || son==nullptr)return nullptr;
    __TreeNode* p=loc;
    __SizeType start=son->getData().getStart();
   __SizeType len=son->getData().getLimit();
    
	while(p && start - p->getData().getStart() < p->getData().getLimit() )
	{
		p=reinterpret_cast<__TreeNode*>(p->getNext());
	}
	if(p)
    {
        if(p->getNext())
        {
            __TreeNode *forward=reinterpret_cast<__TreeNode*>(p->getNext());
            
            // size_t - int = size_t
            if(reinterpret_cast<__SizeType>(forward->getData().getStart() - start) >= len)
            {
                return p;   //valid
            }else{
                return nullptr; //overlapped with the forward
            }
        }else{
            
            return p;  //need not verify the forward
        }
    }
	return nullptr; //until the end,does not find such one
}
/**
* find for its sons which is exactly the same with passed arguments.
*/
__DEF_Template_MemoryManager
typename __DEF_MemoryManager::__TreeNode *
 __DEF_MemoryManager::locateForDelete(__TreeNode* loc,__SizeType start,__SizeType len,bool allocable)
{
    if(loc==nullptr||len==0)return nullptr;
    __TreeNode* p=loc->getSon();

    while(p && p->getData().getStart() < start)
            p=reinterpret_cast<__TreeNode*>(p->getNext());
    if(p && p->getData().getStart() == start && p->getData().getLimit()==len && p->getData().isAllocable()==allocable)
    {
        return p;
    }else{
        return nullptr;
    }

}

/**
* find for its sons which is exactly the same with passed arguments.
*/
__DEF_Template_MemoryManager
typename __DEF_MemoryManager::__TreeNode *
 __DEF_MemoryManager::locateForDeleteStart(__TreeNode* loc,__SizeType start,bool allocable)
{
    if(loc==nullptr)return nullptr;
    __TreeNode* p=loc->getSon();

    while(p && p->getData().getStart() < start)
            p=reinterpret_cast<__TreeNode*>(p->getNext());
    if(p && p->getData().getStart() == start && p->getData().isAllocable()==allocable)
    {
        return p;
    }else{
        return nullptr;
    }

}



__DEF_Template_MemoryManager
int __DEF_MemoryManager::addToTree(__TreeNode* root,
		__TreeNode* son) {
            __TreeNode *location=__DEF_MemoryManager::locateForInsertation(root,son);
            if(location)
            {
                
            }
            // TODO 完成这个函数
            return 0;
}
/**
* head mustn't be nullptr!!
*/
__DEF_Template_MemoryManager
typename __DEF_MemoryManager::__TreeNode *
__DEF_MemoryManager::copyOnAllocation(__TreeNode *head)
{
    if(!head->getSon())
    {
        const __MemoryDescriptor &data=head->getData();

        //*****
        //Util::printStr("copyOnAllocation -- ");
        //**********

        __TreeNode *newnode=this->newOneNode();
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
__DEF_Template_MemoryManager
typename __DEF_MemoryManager::__TreeNode *
__DEF_MemoryManager::nextAllocable(
		__TreeNode* node) {
        if(node)
        {
            do{
                node=reinterpret_cast<__TreeNode*>(node->getNext());
            }while( node && (node->getData().isAllocable()==false) );
        }
        return node;
}
#undef __DEF_Template_MemoryManager
#undef __DEF_MemoryManager

//==========class:LinearSourceManager
#define __DEF_Template_LinearSourceManager template <class _LinearSourceDescriptor,template <class> class _NodeAllocator>
#define __DEF_LinearSourceManager LinearSourceManager<_LinearSourceDescriptor,_NodeAllocator>

__DEF_Template_LinearSourceManager
__DEF_LinearSourceManager::LinearSourceManager(const std::shared_ptr<__Allocator> &smm,__SizeType start,__SizeType size):
Super(smm),space(start,size)
{
    this->appendHead(start,size);
}
__DEF_Template_LinearSourceManager
__DEF_LinearSourceManager::LinearSourceManager(std::shared_ptr<__Allocator> &&smm,__SizeType start,__SizeType size):
        Super(std::move(smm)),space(start,size)
{
    this->appendHead(start,size);
}




__DEF_Template_LinearSourceManager
__DEF_LinearSourceManager::~LinearSourceManager()
{

}

__DEF_Template_LinearSourceManager
void* __DEF_LinearSourceManager::mnew(__SizeType start,__SizeType size)
{
    if(!this->checkRange(start,size))return nullptr;
#if defined(CODE64)
//    printf("not nullptr,request for (%x,%x)\n",start,size);
#endif
    __ListNode *found=Super::findFirstStartLen(this->getHead(),start,size);
#if defined(CODE64)
//    if(found)
//    {
//    	ListNode<LinearSourceDescriptor> *foundp=(ListNode<LinearSourceDescriptor>*)found;
//    	printf("found is (%x,%x)\n",foundp->getData().getStart(),foundp->getData().getLimit());
//    }else{
//    	printf("found is nullptr\n");
//    }
#endif
    if(found)
    {
        _LinearSourceDescriptor alloced = this->allocOutNode(found,start,size);
        if(alloced.getLimit()>0)
        {
            return reinterpret_cast<void*>((alloced.getStart()));
        }
    }
    return nullptr;
}
 
__DEF_Template_LinearSourceManager
void* __DEF_LinearSourceManager::mnew(__SizeType size)
{
    __ListNode *found=Super::findFirstLen(this->getHead(),size);
    Util::printf("in lm,mnew for len %d\n",size);
    if(found)
    {
    	Util::printf("found is %d,%d\n",found->getData().getStart(),found->getData().getLimit());
        _LinearSourceDescriptor alloced = allocOutNode(found,found->getData().getStart(),size);
        if(alloced.getLimit())
        {
            return reinterpret_cast<void*>((alloced.getStart()));
        }
    }
    Util::printf("found is nullptr\n");
    return nullptr;
}
__DEF_Template_LinearSourceManager
void* __DEF_LinearSourceManager::extend(
		__SizeType start,__SizeType size,bool addOrReduce,__SizeType extsize,char *realBase,bool moveData)
{

	if(extsize == 0)return reinterpret_cast<char*>(start);
    if(!this->checkRange(start,size))return nullptr;//检查start,size是否是已经分配的内存区域，不能让错误扩散
    if(addOrReduce==false)//reduce
    {
    	if(extsize>size)extsize=size; //如果回收的长度超过所需，就直接回收全部就可以了
    	this->mdelete(reinterpret_cast<char*>((start+size-extsize)), extsize);
    	return reinterpret_cast<char*>(start);
    }

    // 下面开始处理真正的扩展类型
    NodeType *found=Super::findFirstStartLen(this->getHead(),start+size,extsize);
    if(found && found->getData().getStart()==start + size)
    {
    		this->allocOutNode(found, start+size, extsize);
    		return reinterpret_cast<char*>(start);
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
		   this->mdelete(reinterpret_cast<char*>(start),size);
    		this->allocOutNode(found, found->getData().getStart(), size+extsize);
    		return reinterpret_cast<char*>(found->getData().getStart());
    	}else{
    		return nullptr;
    	}

    }
}

    
__DEF_Template_LinearSourceManager
void __DEF_LinearSourceManager::mdelete(void* p,__SizeType size)
{
    if(!this->checkRange(reinterpret_cast<__SizeType>(p),size))return;
    __ListNode *found=Super::findFirstStartForInsert(this->getHead(),reinterpret_cast<__SizeType>(p));
    if(found)
    {
        int diff=found->getData().getStart()-reinterpret_cast<__SizeType>(p);
        if(diff==0 || (diff>0 && !( This::checkPrevious(found->getPrevious(),reinterpret_cast<__SizeType>(p) )&& This::checkNext(found,reinterpret_cast<__SizeType>(p),size) ) ) ||
                      (diff<0 && !(This::checkPrevious(found,reinterpret_cast<__SizeType>(p) )&& This::checkNext(found->getNext(),reinterpret_cast<__SizeType>(p),size) )  )
                      )
        {
            //impossible to delete this memory
            return;
        }else{
            if(diff>0)
            {
                found->insertPrevious(new (this->newOneNode()) __ListNode(_LinearSourceDescriptor(reinterpret_cast<__SizeType>(p),size)) );
            }else{
                found->insertNext(new (this->newOneNode()) __ListNode(_LinearSourceDescriptor(reinterpret_cast<__SizeType>(p),size)) );
            }
        }
    }else{//empty list
        this->appendHead(_LinearSourceDescriptor(reinterpret_cast<__SizeType>(p),size));
    }

}
__DEF_Template_LinearSourceManager
 bool __DEF_LinearSourceManager::mnewLinked(__SizeType size,
		 __LinkedList &  list,__SizeType eachSectionExtraSize)
{
//	printf("in mnewlinked,size is %d,this space is %d,%d\n",size,this->space.getStart(),this->space.getLimit());
	NodeType * p=this->getHead(),*lastAvl=nullptr;
	if(p==nullptr || size == 0)return false; //head is nullptr or size is 0,no thing to look up.
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
		NodeType * newnode=new (this->newOneNode()) NodeType(_LinearSourceDescriptor(
				lastAvl->getData().getStart() + lastAvl->getData().getLimit(),
				orilimit - extraNeeded
		));
		this->insertNext(lastAvl, newnode);
//		printf("avl = %d,%d  avl.next = %d,%d\n",lastAvl->getData().getStart(),lastAvl->getData().getLimit(),
//				lastAvl->getNext()->getData().getStart(),lastAvl->getNext()->getData().getLimit());
	}

//	printf("list.head is %d,%d\n",list.getHead()->getData().getStart(),list.getHead()->getData().getLimit());

	// TODO  测试removeHead替换注释掉的两句是否正确
//	this->root->setNext(nullptr);
//	this->last->setNext(nullptr);
	__ListNode* head=this->removeAllAfterHead();
	list.appendHead(head);

	__ListNode *avlNext = lastAvl->getNext();
	lastAvl->setNext(nullptr);
	avlNext->setPrevious(nullptr); //取消互相指向
	this->appendHead(avlNext);

//	printf("list.head is %d,%d\n",list.getHead()->getData().getStart(),list.getHead()->getData().getLimit());
	return true;

}




__DEF_Template_LinearSourceManager
void  __DEF_LinearSourceManager::
mdeleteLinked(__LinkedList& list)
{
	NodeType *p=list.getHead();
	while(p)
	{
		this->mdelete(reinterpret_cast<char*>(p->getData().getStart()),p->getData().getLimit());
		p=p->getNext();
	}
}

__DEF_Template_LinearSourceManager
 bool __DEF_LinearSourceManager::checkRange(__SizeType start,__SizeType size)
 {
    return (this->space.getStart() <= start) && (start-this->space.getStart() <= this->space.getLimit() - size );
 }
__DEF_Template_LinearSourceManager
 bool __DEF_LinearSourceManager::checkRange(__SizeType start)
 {
    return this->space.getStart() <= start;
 }

__DEF_Template_LinearSourceManager
bool __DEF_LinearSourceManager::checkPrevious(__ListNode *prev,__SizeType start)
{
    return !prev || (start - prev->getData().getStart() >= prev->getData().getLimit());
}

__DEF_Template_LinearSourceManager
bool __DEF_LinearSourceManager::checkNext(__ListNode *nxt,__SizeType start,__SizeType len)
{
    return !nxt || (nxt->getData().getStart() - start >= len );
}
/**
 *  start & len should reside in avlNode
 *  then this will always return true.
 *
 *  But currently we don't have that promise,So check the returned node if it havs a positive limit
 */
__DEF_Template_LinearSourceManager
_LinearSourceDescriptor __DEF_LinearSourceManager::allocOutNode(__ListNode *avlNode,__SizeType start,__SizeType len)
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
            this->insertNext(avlNode, new (this->newOneNode()) __ListNode(_LinearSourceDescriptor(start+len,len2)) );

        }
    }
    return newnode;
}
    
#undef __DEF_Template_LinearSourceManager
#undef __DEF_LinearSourceDescriptor


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
	This *obj = reinterpret_cast<This*>(nullptr);
	return ::getSerializitionSize<__EnvTransfer,decltype(obj->start)>()+
			::getSerializitionSize<__EnvTransfer,decltype(obj->limit)>();
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
