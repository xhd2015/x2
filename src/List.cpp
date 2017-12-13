
#include <List.h>
#include <MemoryManager.h>
#include <conceptual/ExtFunctional.h>
#include <utility>
#include <conceptual/ResourceProtocal.h>


#if defined(CODE32)
	__asm__(".code32 \n\t");
#endif

//==========实例化模板
////===========模板声明区
//template class ListNode<int>;
//template class LinkedList<int>;
//template class ListNode<MemoryDescriptor>;
//template class Tree<MemoryDescriptor>;
//template class TreeNode<MemoryDescriptor>;
//template class SimpleMemoryManager<ListNode<int> >;
//template class SimpleMemoryManager<TreeNode<MemoryDescriptor> >;
#ifdef CODE32
#include <Kernel.h>
	template class ListNode<MemoryDescriptor<u32_t>>;
	template class TreeNode<MemoryDescriptor<u32_t>>;
	template class SimpleMemoryManager<ListNode<MemoryDescriptor<u32_t>> >;
	template class SimpleMemoryManager<TreeNode<MemoryDescriptor<u32_t>> >;
	template class Tree<MemoryDescriptor<u32_t>,SimpleMemoryManager>;
	template class ListNode<TreeNode<Process*>* >;

	template class ListNode<Process*>;
	template class TreeNode<Process*>;
	template class Tree<Process*,KernelSmmWrapper>;
	template class LinkedList<TreeNode<Process*>*,KernelSmmWrapper>;
	template class Tree<MemoryDescriptor<u32_t>,KernelSmmWrapper>;
#elif defined(CODE64)



#include <cstdio>
#include <EnvInterface64Impl.h>
#include <File.h>
#include <64/MallocToSimple.h>

//	template class TreeNode<FileDescriptor<size_t,sizeof(size_t)>,sizeof(size_t)>;
//	template class SimpleMemoryManager<TreeNode<FileDescriptor<size_t,sizeof(size_t)>,sizeof(size_t)> >;
//	template class TreeNode<int,sizeof(size_t)>;
//	template class SimpleMemoryManager<TreeNode<int,sizeof(size_t)>>;
//	template class TreeNode<MemoryDescriptor<size_t>,sizeof(size_t)>;
//	template class Tree<FileDescriptor<size_t,sizeof(size_t)> ,SimpleMemoryManager>;
//	template class Tree<MemoryDescriptor<size_t> , MallocToSimple64Impl>;
//	template class Tree<MemoryDescriptor<size_t>, X2fsUtil<StdEnv64Impl, FsEnv64>::PartialMallocToSimple>;
//	template class Tree<MemoryDescriptor<size_t>, X2fsUtil<EnvInterface64Impl,FsEnv64>::PartialMallocToSimple>;
//
//	template class ListNode<LinearSourceDescriptor<size_t,sizeof(size_t)>,sizeof(size_t)>;
//	template class ListNode<FileDescriptor<size_t,sizeof(size_t)>,sizeof(size_t)>;
//	template class ListNode<MemoryDescriptor<size_t>,sizeof(size_t)>;
//
//	template class LinkedList<LinearSourceDescriptor<size_t,sizeof(size_t)> , MallocToSimple64Impl,sizeof(size_t)>;
//	template class LinkedList<LinearSourceDescriptor<size_t,sizeof(size_t)>, X2fsUtil<StdEnv64Impl,FsEnv64>::PartialMallocToSimple,sizeof(size_t)>;
//	template class LinkedList<LinearSourceDescriptor<size_t,sizeof(size_t)> , X2fsUtil<EnvInterface64Impl,FsEnv64>::PartialMallocToSimple,sizeof(size_t)>;
//
//	template class LocateableLinkedList<LinearSourceDescriptor<size_t,sizeof(size_t)> ,
//		Locator<LinearSourceDescriptor<size_t,sizeof(size_t)> >::KEEP, MallocToSimple64Impl,size_t,sizeof(size_t)>;
//	template class LocateableLinkedList<LinearSourceDescriptor<size_t,sizeof(size_t)> ,
//			Locator<LinearSourceDescriptor<size_t,sizeof(size_t)> >::DISCARD, MallocToSimple64Impl,size_t,sizeof(size_t)>;
//	template class LocateableLinkedList<LinearSourceDescriptor<size_t,sizeof(size_t)> ,
//			Locator<LinearSourceDescriptor<size_t,sizeof(size_t)> >::DISCARD, X2fsUtil<EnvInterface64Impl,FsEnv64>::PartialMallocToSimple,size_t,sizeof(size_t)>;
//	template class LocateableLinkedList<LinearSourceDescriptor<size_t,sizeof(size_t)>,
//	Locator<LinearSourceDescriptor<size_t,sizeof(size_t)> >::DISCARD,
//			X2fsUtil<StdEnv64Impl, FsEnv64>::PartialMallocToSimple, size_t,sizeof(size_t)>;
#endif


//====================class :SimpleMemoryNode



//===================class: SimpleMemoryManager

template <class T>
SimpleMemoryManager<T>::SimpleMemoryManager(size_t start,size_t limit,bool doInit,size_t initSize,SimpleMemoryManager<T>::ERROR_HANDLER errhandle):
start(start),limit(limit),
data(reinterpret_cast<FullNode*>(start)),curSize(initSize),len(limit/x2sizeof(FullNode)),
lastIndex(0),
errhandle(errhandle)
{
#if defined(CODE32)
	Kernel::printer->puti("len=",len);
#endif
    if(doInit)
    {

        for(size_t i=0;i!=len;i++)
        {
//        	Kernel::printer->puti("i=",i);
           data[i].SimpleMemoryNode::setAlloced(false);
        }
    }
//    Kernel::printer->putsz("return smm init\n");
}

//template <class T>
//SimpleMemoryManager<T>::SimpleMemoryManager():
//start(-1),limit(0),data(nullptr),len(0),curSize(0),lastIndex(0),errhandle(nullptr)
//{
//
//
//}


template <class T>
T* SimpleMemoryManager<T>::getNew()
{
	return static_cast<T*>(this->getNewNode());
}

template <class T>
typename SimpleMemoryManager<T>::FullNode *SimpleMemoryManager<T>::getNewNode()
{
	//Kernel::printer->putsz("in getNewNode\n");
    FullNode *rt=nullptr;
    if(!isFull())
    {
        for(size_t i=0;i!=len;i++)
        {
            if(data[lastIndex].isAlloced()==false)
            {
                rt=&data[lastIndex];
                rt->setAlloced(true);
                curSize++;
                lastIndex = (lastIndex + 1 ) % len;
                break;
            }
            lastIndex = (lastIndex + 1 ) % len;
        }
    }
#if defined(CODE64)
//    printf("returned\n");
#endif
    return rt;
}
template <class T>
void SimpleMemoryManager<T>::withdraw(SimpleMemoryManager<T>::FullNode *t)
{
	FullNode* _t=reinterpret_cast<FullNode*>(t);
    if(_t && _t->isAlloced())
    {
        _t->setAlloced(false); //如果被标记为可用，就用lastIndex指向之
        curSize--;
        lastIndex = ((_t - start)/sizeof(FullNode)) % len;
    }
}

template <class T>
void SimpleMemoryManager<T>::withdraw(T *t)
{
	this->withdraw(reinterpret_cast<FullNode*>(t));
}


//===========class : ListNode
#define __DEF_Template_ListNode template<class T>
#define __DEF_ListNode ListNode<T>

__DEF_Template_ListNode
__DEF_ListNode::ListNode():
data(),
next(nullptr),
previous(nullptr)
{
}
__DEF_Template_ListNode
__DEF_ListNode::ListNode(const T& data,__ListNode* next,__ListNode* previous):
data(data),
next(next),
previous(previous)
{
}
__DEF_Template_ListNode
__DEF_ListNode::~ListNode()
{

}

__DEF_Template_ListNode
typename __DEF_ListNode::__ListNode* __DEF_ListNode::removeNext()
{
    __ListNode* rt=this->getNext();
    if(!rt)return nullptr;

	this->setNext(rt->getNext());
	if(rt->hasNext())
	{
		rt->getNext()->setPrevious(this);
	}

	// 清除rt的链接信息，保留其数据
	rt->setPrevious(nullptr);
	rt->setNext(nullptr);

    return rt;
}

__DEF_Template_ListNode
typename __DEF_ListNode::__ListNode* __DEF_ListNode::removePrevious()
{
    __ListNode* rt=this->getPrevious();
    if(!rt) return nullptr;

	this->setPrevious(rt->getPrevious());
	if(rt->hasPrevious())
	{
		rt->getPrevious()->setNext(this);
	}

	rt->setPrevious(nullptr);
	rt->setNext(nullptr);

    return rt;
}


__DEF_Template_ListNode
void    __DEF_ListNode::insertNext(__ListNode* next)
{
    if(next)
    {
        __ListNode* temp1=this->getNext();
        if(temp1)
        {
            temp1->setPrevious(next);
        }
        next->setPrevious(this);
        next->setNext(temp1);
        this->setNext(next);
    }


}

__DEF_Template_ListNode
void    __DEF_ListNode::insertPrevious(__ListNode* previous)
{
    if(previous)
    {
        __ListNode* prev=this->getPrevious();
        if(prev)
        {
            prev->setNext(previous);
        }
        previous->setNext(this);
        previous->setPrevious(prev);
        this->setPrevious(previous);
    }
}
__DEF_Template_ListNode
void   __DEF_ListNode::adjustOffset(ptrdiff_t diff)
{
	if(this->next!=nullptr)
		this->next = reinterpret_cast<__ListNode*>(this->next + diff);
	if(this->previous!=nullptr)
		this->previous = reinterpret_cast<__ListNode*>(this->previous + diff);
}
__DEF_Template_ListNode
void   __DEF_ListNode::initToNull()
{
	next = previous = nullptr;
}
__DEF_Template_ListNode
typename __DEF_ListNode::__ListNode*   __DEF_ListNode::getLast()const
{
//	Util::printStr("in ListNode getLast\n");
    __ListNode* p= static_cast<__ListNode*>(this);
    while(p->hasNext())
    {
        p=p->getNext();
    }
//    Util::printStr("in getLast returning \n");
    return p;
}
__DEF_Template_ListNode
typename __DEF_ListNode::__ListNode*    __DEF_ListNode::getFirst()const
{
    __ListNode *p=reinterpret_cast<__ListNode*>(this);
    while(p->hasPrevious())
    {
        p=p->getPrevious();
    }
    return p;
}

#undef __DEF_Template_ListNode
#undef __DEF_ListNode


//===============class : LinkedList
#define __DEF_Template_LinkedList template<class T,template<class> class _Allocator>
#define __DEF_LinkedList LinkedList<T,_Allocator>

__DEF_Template_LinkedList
__DEF_LinkedList::LinkedList(const std::shared_ptr<__Allocator>& smm):
smm(),root(newOneNodeThrows()),last(newOneNodeThrows())
{
    this->smm = smm; //必须使用赋值来设置
}



__DEF_Template_LinkedList
__DEF_LinkedList::LinkedList(std::shared_ptr<__Allocator>&& smm):
smm(std::move(smm)),root(newOneNodeThrows()),last(newOneNodeThrows())
{

}
__DEF_Template_LinkedList
__DEF_LinkedList::LinkedList(__Allocator *smm):
smm(smm),root(newOneNodeThrows()),last(newOneNodeThrows())
{
}

__DEF_Template_LinkedList
__DEF_LinkedList::~LinkedList()
{
    this->free();
}
__DEF_Template_LinkedList
void __DEF_LinkedList::free()
{
	if(root)
		this->freeNext(root->getNext());

	this->smm->withdraw(this->root);
    this->smm->withdraw(this->last);

    this->root=nullptr;
    this->last=nullptr;

}
__DEF_Template_LinkedList
void __DEF_LinkedList::freeNext(__ListNode *t)
{
    if(!t || t==root || t==last)return;
    __ListNode *p=t;
    __ListNode *prev=t->getPrevious();
    while(p)
    {
        smm->withdraw(p);
        p=p->getNext();
    }
    if(prev)
    	prev->setNext(nullptr);
    if(last)
    	last->setNext(prev==root? nullptr : prev);

}

__DEF_Template_LinkedList
void __DEF_LinkedList::freePrevious(__ListNode *t)
{
    if(!t || t==root || t==last)return;
    __ListNode *p=t;
    while(p!=root)
    {
        smm->withdraw(p);
        p=p->getPrevious();
    }
    root->insertNext(t->getNext());
    if(t==getLast())
    {
        this->last->setNext(nullptr);
    }
}   
__DEF_Template_LinkedList
void    __DEF_LinkedList::freeNode(__ListNode * node)
{
    if(node && node!=root && node!=last)
    {
        if(node==getLast())
        {
            if(node==getHead())
            {
                last->setNext(nullptr);
            }else{
                last->setNext(node->getPrevious());
            }
        }
        node->getPrevious()->removeNext();
        smm->withdraw(node);
    }
}

__DEF_Template_LinkedList
typename __DEF_LinkedList::__ListNode*  __DEF_LinkedList::
	append(const T& t)
{
    return append(new (smm->getNew()) __ListNode(t));
}
__DEF_Template_LinkedList
typename __DEF_LinkedList::__ListNode*  __DEF_LinkedList::
		append(__ListNode* p)
{
    if(!p)return nullptr;
    __ListNode* rlast=getLast();
    if(rlast==nullptr)
    {
        rlast=this->root;
    }
    rlast->insertNext(p);
    last->setNext(p);

    return p;
}
__DEF_Template_LinkedList
template <class ... Args>
typename __DEF_LinkedList::__ListNode*	    __DEF_LinkedList::append(Args &&...args)
{
	this->append(getNew(*smm,std::forward<Args>(args)...));
}
__DEF_Template_LinkedList
typename __DEF_LinkedList::__ListNode*  __DEF_LinkedList::
		appendHead(const T& t)
{
    return appendHead(new (smm->getNew()) __ListNode(t));
}

__DEF_Template_LinkedList
typename __DEF_LinkedList::__ListNode*  __DEF_LinkedList::
		appendHead(__ListNode* p)
{
    if(!p)return nullptr;
    root->insertNext(p);
    if(getLast()==nullptr)
    {
        last->setNext(p);
    }
    return p;
}
__DEF_Template_LinkedList
typename __DEF_LinkedList::__ListNode*    __DEF_LinkedList::
		remove()
{
   __ListNode* plast=getLast();
   if(plast)
   {
    plast->getPrevious()->setNext(nullptr);
    if(root->getNext() == last->getNext() )
    {
        last->setNext(nullptr);
    } else{
        last->setNext(plast->getPrevious());
    }
   }
   return plast;
   
}
__DEF_Template_LinkedList
template <class ... Args>
typename __DEF_LinkedList::__ListNode*	    __DEF_LinkedList::appendHead(Args &&...args)
{
	this->appendHead(getNew(*smm,std::forward<Args>(args)...));
}

__DEF_Template_LinkedList
void    __DEF_LinkedList::remove(__ListNode* p)
{
#if defined(CODE64)
//    	printf("p->previous=%x,root=%x\n",p->getPrevious(),this->root);
#endif
    if(!p || p==root || p==last)return;
    if(p==this->getLast())
    {
        remove();
    }else{
#if defined(CODE64)
//    	printf("p->previous=%x,root=%x\n",p->getPrevious(),this->root);
#endif
        p->getPrevious()->removeNext();    
    }
}

__DEF_Template_LinkedList
void	 __DEF_LinkedList::insertNext(__ListNode* where,__ListNode* p)
{
	if(where==nullptr||p==nullptr)return;
	if(where==this->root)
	{
		this->appendHead(p);
	}else if(where==this->getLast())
	{
		this->append(p);
	}else{
		where->insertNext(p);
	}
}
__DEF_Template_LinkedList
template <class ... Args>
void			__DEF_LinkedList::insertNext(__ListNode *where,Args &&...args)
{
	this->insertNext(where,newOneNodeThrows(std::forward<Args>(args)...));
}
__DEF_Template_LinkedList
void	 __DEF_LinkedList::insertPrevious(__ListNode* where,__ListNode* p)
{
	if(where==nullptr||where==this->root||p==nullptr)return;
	if(root->getNext()==where)
	{
		this->appendHead(p);
	}else{
		where->insertPrevious(p);
	}

}
__DEF_Template_LinkedList
template <class ... Args>
void			__DEF_LinkedList::insertPrevious(__ListNode *where,Args &&...args)
{
	this->insertPrevious(where,newOneNodeThrows(std::forward<Args>(args)...));
}
__DEF_Template_LinkedList
size_t   __DEF_LinkedList::getSize()const
{
	size_t size=0;
	__ListNode* p=root;
	while(p->hasNext())
	{
		size++;
		p=p->getNext();
	}
	return size;
}
__DEF_Template_LinkedList
template <class ... Args>
typename __DEF_LinkedList::__ListNode*
__DEF_LinkedList::newOneNode(Args &&...args)noexcept
{
	return getNew(*this->smm,std::forward<Args>(args)...);
}
__DEF_Template_LinkedList
template <class ... Args>
typename __DEF_LinkedList::__ListNode*
__DEF_LinkedList::newOneNodeThrows(Args &&...args)
{
	return getNewThrows(*this->smm,std::forward<Args>(args)...);
}
__DEF_Template_LinkedList
void __DEF_LinkedList::freeOneNode(__ListNode *node)
{
	smm->withdraw(node);
}
__DEF_Template_LinkedList
typename __DEF_LinkedList::__ListNode*    __DEF_LinkedList::
		removeHead()
{
    __ListNode* p=root->removeNext();
    if(!p)return nullptr;//empty
    if(p==getLast())
    {
        last->setNext(nullptr);
    }
    return p;
   
}
__DEF_Template_LinkedList
typename __DEF_LinkedList::__ListNode*
	__DEF_LinkedList::removeAllAfterHead()
{
	__ListNode *p=root->getNext();
	if(!p) return nullptr;
	p->setPrevious(nullptr);
	root->setNext(nullptr);
	last->setNext(nullptr);
}
#undef __DEF_Template_LinkedList
#undef __DEF_LinkedList




//=============class : LocateableLinkedList
#define __DEF_Template_LocateableLinkedList template<class _Locateable,int _HowAllocated,template <class> class _Allocator>
#define __DEF_LocateableLinkedList LocateableLinkedList<_Locateable,_HowAllocated,_Allocator>

__DEF_Template_LocateableLinkedList
__DEF_LocateableLinkedList::~LocateableLinkedList()
{

}
/**
* Do I work on a KEEP-ALLOCATED or DISCARD-ALLOCATED list?
*
*  Find  a node that is less than or equal to start,and can contain it
*   The 'template argument' combination technique is(maybe that I now say 'often' appears too early) used in an extension system.
*   The template arguments will cover all the nodes from base to the deepest derived class.
*/
__DEF_Template_LocateableLinkedList
typename __DEF_LocateableLinkedList::__ListNode*__DEF_LocateableLinkedList::
findFirstStartLen(__ListNode* startNode,__SizeType start,__SizeType len)
{
    if(!startNode||len==0)return nullptr;
#if defined(CODE64)
//    printf("findFirstStartLen for (%x,%x)\n",start,len);
#endif
    __ListNode* p=startNode;
    _Locateable tloc(start,len);

     // start要小于，长度忽略,可分配性忽略
    // 即p.start < tloc.start 其他忽略
    // (x,y)  (a0,b0)-->(a1,b1)-->(a2,b2)-->nullptr
    // 先找到(x,y)所在的合适区间，即x最接近的那个ai,x>ai,x==ai均可，所以当x<ai时，应当跳过
//    SourceLocator<_Locateable,Locator<_Locateable>::LESS,Locator<_Locateable>::IGNORE,Locator<_Locateable>::IGNORE> lessLocator(tloc);
#if defined(CODE64)
//    	printf("1 : p is(%x - %x) ,tloc is (%x - %x)\n ",p->getData().getStart(),p->getData().getStart()+p->getData().getLimit(),
//    			tloc.getStart(),
//				tloc.getStart()+tloc.getLimit()
//    			);
#endif
    // TODO 将这个定位器提取出来
    using   TEMP_METHOD= SourceLocator<_Locateable,Locator<_Locateable>::LESS,Locator<_Locateable>::IGNORE,Locator<_Locateable>::IGNORE>;

    while(p && TEMP_METHOD::meeted(TEMP_METHOD::RELATION_LS_EQ,TEMP_METHOD::RELATION_IGNORE, TEMP_METHOD::RELATION_IGNORE,
    		p->getData(),tloc) ) //p<=tloc,p<tloc,p==tloc
    	{
#if defined(CODE64)
//    	printf("2 : p is(%x - %x) ,tloc is (%x - %x)\n ",p->getData().getStart(),p->getData().getStart()+p->getData().getLimit(),
//    			tloc.getStart(),
//				tloc.getStart()+tloc.getLimit()
//    			);
#endif
    		if(p->getData().contains(tloc)) //当可以包含时，就选择
    		{
    			break;
    		}else{
    			p=This::nextAllocable(p);
    		}
    	}
#if defined(CODE64)
//    	printf("3 : p is(%x - %x) ,tloc is (%x - %x)\n ",p->getData().getStart(),p->getData().getStart()+p->getData().getLimit(),
//    			tloc.getStart(),
//				tloc.getStart()+tloc.getLimit()
//    			);
#endif
   while(p && !p->getData().contains(tloc))
    {
#if defined(CODE64)
//    	printf("4 : p is(%x - %x) ,tloc is (%x - %x)\n ",p->getData().getStart(),p->getData().getStart()+p->getData().getLimit(),
//    			tloc.getStart(),
//				tloc.getStart()+tloc.getLimit()
//    			);
//    	printf("p contains tloc ? %d \n",p->getData().contains(tloc));
#endif
    	p=This::nextAllocable(p);
    }
#if defined(CODE64)
//    	printf("5 : p is(%x - %x) ,tloc is (%x - %x)\n ",p->getData().getStart(),p->getData().getStart()+p->getData().getLimit(),
//    			tloc.getStart(),
//				tloc.getStart()+tloc.getLimit()
//    			);
#endif
#if defined(CODE64)
//    printf("end of findFirstStartLen,result is ");
//    if(p==nullptr)
//    {
//    	printf("nullptr\n");
//    }else{
//    	printf("(%x,%x) \n",p->getData().getStart(),p->getData().getLimit());
//    }
#endif
    return p;
}

__DEF_Template_LocateableLinkedList
typename __DEF_LocateableLinkedList::__ListNode*__DEF_LocateableLinkedList::findFirstLen(__ListNode* startNode,__SizeType len)
{
    if(!startNode||len==0)return nullptr;
    __ListNode* p=startNode;
    _Locateable tloc(0,len);
    SourceLocator<_Locateable,Locator<_Locateable>::IGNORE,Locator<_Locateable>::EQUAL,Locator<_Locateable>::IGNORE> equLocator(tloc);
    SourceLocator<_Locateable,Locator<_Locateable>::IGNORE,Locator<_Locateable>::BIGGER,Locator<_Locateable>::IGNORE> biggerLocator(tloc);
    while(p && !equLocator.meetedBy(p->getData()) && !biggerLocator.meetedBy(p->getData()))
    {
        p=__DEF_LocateableLinkedList::nextAllocable(p);
    }
    return p;
}

__DEF_Template_LocateableLinkedList
typename __DEF_LocateableLinkedList::__ListNode*__DEF_LocateableLinkedList::findFirstStart(__ListNode* startNode,__SizeType start)
{
    if(!startNode)return nullptr;

    _Locateable tloc(start,0);
    __ListNode* p=__DEF_LocateableLinkedList::findFirstStartForInsert(startNode,start);
    SourceLocator<_Locateable,Locator<_Locateable>::EQUAL,Locator<_Locateable>::IGNORE,Locator<_Locateable>::IGNORE> equLocator(tloc);
    if(p && (equLocator.meetedBy(p->getData()) ))
    {
        return p;
    }else{
        return nullptr;
    }
}
__DEF_Template_LocateableLinkedList
typename __DEF_LocateableLinkedList::__ListNode*__DEF_LocateableLinkedList::findFirstStartForInsert(__ListNode *startNode,__SizeType start)
{
    if(!startNode)return nullptr;
    __ListNode *p=startNode,*last=startNode;
    _Locateable tloc(start,0);
    SourceLocator<_Locateable,Locator<_Locateable>::LESS,Locator<_Locateable>::IGNORE,Locator<_Locateable>::IGNORE> lessLocator(tloc);

    while(p && lessLocator.meetedBy(p->getData()))
        {
            startNode=p;
            p=__DEF_LocateableLinkedList::nextAllocable(p);
        }
    if(p==nullptr)
    {
        return last;
    }
    return p;

}
__DEF_Template_LocateableLinkedList
typename __DEF_LocateableLinkedList::__ListNode* __DEF_LocateableLinkedList::
	nextAllocable(__ListNode* startNode)
{
    return __DEF_LocateableLinkedList::nextAllocable(startNode,Int2Type<_HowAllocated>());
}

__DEF_Template_LocateableLinkedList
typename __DEF_LocateableLinkedList::__ListNode*
	__DEF_LocateableLinkedList::
	nextAllocable(__ListNode* startNode,Int2Type<Locator<_Locateable>::KEEP>)
{
         if(startNode)
        {
            do{
                startNode=startNode->getNext();
            }while( startNode && (! startNode->getData().isAllocable()) );
        }
        return startNode;
}

__DEF_Template_LocateableLinkedList
typename __DEF_LocateableLinkedList::__ListNode* __DEF_LocateableLinkedList::
	nextAllocable(__ListNode* startNode,Int2Type<Locator<_Locateable>::DISCARD>)
{
    return startNode==nullptr?nullptr:startNode->getNext();
}
#undef __DEF_Template_LocateableLinkedList
#undef __DEF_LocateableLinkedList
#undef __DEF_LocateableLinkedList


//============class : TreeNode
#define __DEF_Template_TreeNode template<class T>
#define __DEF_TreeNode TreeNode<T>

__DEF_Template_TreeNode
__DEF_TreeNode::TreeNode():
Super(),
son(nullptr),
father(nullptr)
{

}

__DEF_Template_TreeNode
__DEF_TreeNode::TreeNode(const T& data,__TreeNode* father,__TreeNode* son,__TreeNode* next,__TreeNode* previous):
Super(data,next,previous),
son(son),
father(father)
{

}
__DEF_Template_TreeNode
__DEF_TreeNode::~TreeNode() {
}

//#if defined(CODE64)
//__DEF_Template_TreeNode
//__TreeNode* __DEF_TreeNode::getSon() const{
//#if defined(CODE64)
//	printf("gettSon not macro\n");
//#endif
//	return son;
//}
//#endif


__DEF_Template_TreeNode
void __DEF_TreeNode::addSon(__TreeNode* son)
{
//	Util::printStr("in TreeNode addSon \n");
	__TreeNode*	orison=this->getSon();
	if(orison)
	{
		orison->getLast()->insertNext(son);
	}else{
		this->setSon(son);
	}
}
__DEF_Template_TreeNode
void __DEF_TreeNode::insertSon(__TreeNode* son) {
	if(son!=nullptr)
	{
#if defined(CODE64)
//	printf("insertSon 0\n");
#endif
#if defined(CODE64)
//	printf("getSon return\n");
#endif
		__TreeNode *orison=this->getSon();
#if defined(CODE64)
//	printf("insertSon 1\n");
#endif
		this->setSon(son);
#if defined(CODE64)
//	printf("insertSon 2\n");
#endif
		son->setFather(this);
#if defined(CODE64)
//	printf("insertSon 3\n");
#endif
		son->setSon(orison);
		if(orison)
		{
			orison->setFather(son);
		}
	}
}

__DEF_Template_TreeNode
void __DEF_TreeNode::insertFather(__TreeNode* father) {
	if(father!=nullptr)
	{
		__TreeNode *orifather=this->getDirectFather();
		this->setFather(father);
		father->setSon(this);
		father->setFather(orifather);
		if(orifather)
		{
			orifather->setSon(father);
		}
	}
}

__DEF_Template_TreeNode
void __DEF_TreeNode::removeSon() {
	if(this->getSon())
	{
		__TreeNode *son=this->getSon()->getSon();
		this->setSon(son);
		son->setFather(this);
		this->getSon()->setFather(nullptr);
		this->getSon()->setSon(nullptr);

	}
}
__DEF_Template_TreeNode
void 			__DEF_TreeNode::adjustOffset(ptrdiff_t diff)
{
	this->Super::adjustOffset(diff);
	if(this->father!=nullptr)
		this->father = reinterpret_cast<__TreeNode*>(this->father + diff);
	if(this->son!=nullptr)
		this->son = reinterpret_cast<__TreeNode*>(this->son + diff);
}
__DEF_Template_TreeNode
void 			__DEF_TreeNode::initToNull()
{
	__ListNode::initToNull();
	father=son=nullptr;
}
__DEF_Template_TreeNode
void 			__DEF_TreeNode::concateSon(__TreeNode *node)
{
	if(this->hasSon() || node==nullptr || node->hasFather())return;//前置条件不满足
	this->setSon(node);
	node->setFather(this);
}
__DEF_Template_TreeNode
void 			__DEF_TreeNode::concateNext(__TreeNode *node)
{
	if(this->hasNext() || node==nullptr || node->hasFather())return;//前置条件不满足
	this->setNext(node);
	node->setPrevious(this);
}

__DEF_Template_TreeNode
void __DEF_TreeNode::removeFather() {
	if(this->getDirectFather())
	{
		__TreeNode *father=this->getDirectFather()->getDirectFather();
		this->setFather(father);
		father->setSon(this);
		this->getDirectFather()->setFather(nullptr);
		this->getDirectFather()->setSon(nullptr);
	}
}

__DEF_Template_TreeNode
typename __DEF_TreeNode::__TreeNode* __DEF_TreeNode::getParent()const {//往previous一直遍历，直到是跟，然后返回跟的father
	__TreeNode *p=reinterpret_cast<__TreeNode*>(this);
	while(p->hasPrevious())
	{
		p=reinterpret_cast<__TreeNode*>(p->getPrevious());
	}
	return p->getDirectFather();
}




#undef __DEF_Template_TreeNode
#undef __DEF_TreeNode



//===============class Tree
#if defined(CODE64)
#include <cstdio>
#endif

#define __DEF_Template_Tree template<class T,template <class> class _Allocator>
#define __DEF_Tree Tree<T,_Allocator>

//__DEF_Template_Tree
//template <template <class> class __SharedPtr>
//__DEF_Tree::Tree(__SharedPtr<__Allocator>&& smm):
//smm(std::forward<__SharedPtr<__Allocator>>(smm)),root(newOneNodeThrows()) // root通过smm->getNew(),也必须被恰当地回收。
//{
//}
__DEF_Template_Tree
__DEF_Tree::Tree(const std::shared_ptr<__Allocator> &smm):
smm(smm),
root(newOneNodeThrows()), // root通过smm->getNew(),也必须被恰当地回收。
curNode(nullptr)
{
}
__DEF_Template_Tree
__DEF_Tree::Tree(std::shared_ptr<__Allocator>&& smm):
smm(std::move(smm)),
root(newOneNodeThrows()), // root通过smm->getNew(),也必须被恰当地回收。
curNode(nullptr)
{
}

__DEF_Template_Tree
__DEF_Tree::Tree(__Tree && tree):
smm(std::move(tree.smm)),
root(tree.root),
curNode(nullptr)
{
	// NOTE 下面的语句必须，而且必须配合析构函数进行使用：移动过后，就好像该类已经被析构了一样，但是它所指的资源并没有相应关闭
	tree.root=nullptr;
	tree.curNode=nullptr;
}
__DEF_Template_Tree
typename __DEF_Tree::__Tree __DEF_Tree::operator=(__Tree && tree)
{
	this->smm = std::move(tree.smm);
	this->root = tree.root;
	this->curNode = nullptr;
	tree.root=nullptr;
	tree.curNode=nullptr;
}
__DEF_Template_Tree
typename __DEF_Tree::__Tree __DEF_Tree::makeSmmSharedTree()
{
  return std::move(__Tree{this->smm});
}

#if defined(CODE32)
__DEF_Template_Tree
void __DEF_Tree::dumpInfo(Printer* p)const
{
	if(p!=nullptr)
	{
		p->putsz("Tree{");

		p->putsz("}");
	}
}
#endif

__DEF_Template_Tree
__DEF_Tree::~Tree() {
	// DONE 证明正确性
	// 考虑可重入性
	// 是的，现在析构函数的语义应当是： 销毁所有未被关闭，以及未被移动的资源。 考虑移动构造函数的影响。
	if(this->root) // root仅可能通过移动进行改变。
		freeAll(this->root);
}

__DEF_Template_Tree
void         __DEF_Tree::freeAll(__TreeNode *node)
{
  if(node)
  {
	  this->freeAll(node->getSon());
	  this->freeAll(node->getNext());
	  smm->withdraw(node);
  }
}
__DEF_Template_Tree
size_t		__DEF_Tree::getSize()const
{
	size_t size=0;
	dumpInfo([&size](const T& t){++size;},
			doNothing<void>, doNothing<void>, doNothing<void>, doNothing<void>);
	return size;
}

//__DEF_Template_Tree
//template <class __SerializerPtr>
//__SerializerPtr* __DEF_Tree::ptrNewest=nullptr;

__DEF_Template_Tree
template <class __EnvTransfer>
		size_t __DEF_Tree::__serializeHelper(SerializerPtr<__EnvTransfer> &ptr,__TreeNode *node)const
		{
			if(node)
			{
				size_t n_son;
				size_t n_next; // 不赋初值，减少初始化开销，因为只要进入node!=nullptr的区域，它们一定会被赋值；而不进入则没必要赋值
				ptr << node->getData();
				SerializerPtr<__EnvTransfer> ptrLast = ptr;//指向写n_last的地方
				ptr << size_t(0) << size_t(0); //跳到下一个节点的起始处

				// BUG 下面的两句，如果用在一起，不能保证谁先发生，即可能先序列化son，也可能先序列化next。
				//   观察到的实际结果是先序列化next,然后是son。显然需要分开来做。
				ptrLast <<(n_son = __serializeHelper<__EnvTransfer>(ptr,node->getSon()));
				ptrLast	<<(n_next = __serializeHelper<__EnvTransfer>(ptr,node->getNext()));
//				HostEnv::printf_simple("data=%d,n_son=%d, n_next=%d\n",node->getData(),n_son,n_next);
				return (n_son + n_next + 1);
			}else
				return (0);
		}
__DEF_Template_Tree
template <class __EnvTransfer>
typename __DEF_Tree::__TreeNode *	__DEF_Tree::
		__deserializeHelper(SerializerPtr<__EnvTransfer> &ptr,size_t n)
		{
			if(n==0)return (nullptr);
			__TreeNode *node = this->newOneNode();
			size_t n_son;
			size_t n_next;

			ptr	>> node->getData()
			    >> n_son
			    >> n_next;
//			HostEnv::printf_simple("data=%d,n_son=%d, n_next=%d\n",node->getData(),n_son,n_next);

			node->concateSon(__deserializeHelper<__EnvTransfer>(ptr,n_son));
			node->concateNext(__deserializeHelper<__EnvTransfer>(ptr,n_next));
//			HostEnv::printf_simple("data=%d,n_son=%d, n_next=%d\n",node->getData(),n_son,n_next);
			return node;
		}
__DEF_Template_Tree
template <class __EnvTransfer>
	SerializerPtr<__EnvTransfer>& __DEF_Tree::serialize(SerializerPtr<__EnvTransfer> &ptr)const
	{
		SerializerPtr<__EnvTransfer> headPtr = ptr;
		ptr << size_t(0); //先移动到下一个开始处
		size_t sum = __serializeHelper<__EnvTransfer>(ptr,this->getHead());
		headPtr << sum; // 回写
//		HostEnv::printf_simple("write sum =%d\n",sum);
		return ptr;
	}
__DEF_Template_Tree
template <class __EnvTransfer>
	SerializerPtr<__EnvTransfer>& __DEF_Tree::deserialize(SerializerPtr<__EnvTransfer> &ptr)
	{
		size_t sum;
		ptr >> sum;
		this->setHead(__deserializeHelper<__EnvTransfer>(ptr,sum));
//		HostEnv::printf_simple("read sum =%d\n",sum);
		return ptr;
	}
__DEF_Template_Tree
template <class __EnvTransfer>
	 size_t __DEF_Tree::getSerializitionSize() // 每一个不一定都是定长的
{
	return  __EnvTransfer::template sizeofHostType<size_t>()+
			getSize() *(
			::getSerializitionSize<T,__EnvTransfer>()+__EnvTransfer::template sizeofHostType<size_t>()*2) ;
}

#if defined(CODE64)
__DEF_Template_Tree
void 		__DEF_Tree::dumpInfo(
		std::function<void(const T& t)>   consumer,
		std::function<void()>   beforeSon,
		std::function<void()>   afterSon,
		std::function<void()>   beforeNext,
		std::function<void()>   afterNext,
		__TreeNode *node)const
{
	if(node)
	{
		consumer(node->getData());
		beforeSon();
		dumpInfo(consumer, beforeSon, afterSon, beforeNext, afterNext, node->getSon());
		afterSon();
		beforeNext();
		dumpInfo(consumer, beforeSon, afterSon, beforeNext, afterNext, node->getNext());
		afterNext();
	}
}
__DEF_Template_Tree
void 		__DEF_Tree::dumpInfo(std::function<void(const T& t)>   consumer,		std::function<void()>   beforeSon,
		std::function<void()>   afterSon,
		std::function<void()>   beforeNext,
		std::function<void()>   afterNext)const
{
	dumpInfo(consumer, beforeSon, afterSon, beforeNext, afterNext,this->getHead());
}
#endif

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
template <typename ...Args>
void		__DEF_Tree::setHead(Args&& ... args)
{
	this->setHead(getNewThrows(*smm, std::forward<Args>(args)...));
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
template <typename ...Args>
typename __DEF_Tree::__Tree& __DEF_Tree::insertNext(Args&& ... args)
{
	curNode->insertNext(newOneNodeThrows(std::forward<Args>(args)...));
	return *this;
}

__DEF_Template_Tree
template <typename ...Args>
typename __DEF_Tree::__Tree& __DEF_Tree::insertPrevious(Args&& ... args)
{
	curNode->insertPrevious(newOneNodeThrows(std::forward<Args>(args)...));
	return *this;
}

__DEF_Template_Tree
template <typename ...Args>
typename __DEF_Tree::__Tree& __DEF_Tree::insertSon( Args&& ... args)
{
	curNode->insertSon(newOneNodeThrows(std::forward<Args>(args)...));
	return *this;
}

__DEF_Template_Tree
template <typename ...Args>
typename __DEF_Tree::__Tree& __DEF_Tree::insertFather(Args&& ... args)
{
	curNode->insertFather(newOneNodeThrows(std::forward<Args>(args)...));
	return *this;
}

__DEF_Template_Tree
void		__DEF_Tree::freeOneNode(__TreeNode *node)
{
	// 即使node为nullptr仍然可以安全调用
	smm->withdraw(node);
}
__DEF_Template_Tree
template <class ...Args>
typename __DEF_Tree::__TreeNode*__DEF_Tree::newOneNode(Args&&...args) noexcept
{
	// 即使node为nullptr仍然可以安全调用
	return getNew(*this->smm,std::forward<Args>(args)...);
}
__DEF_Template_Tree
template <class ...Args>
typename __DEF_Tree::__TreeNode*__DEF_Tree::newOneNodeThrows(Args&&...args)
{
	return getNewThrows(*this->smm,std::forward<Args>(args)...);
}
//__DEF_Template_Tree
//typename __DEF_Tree::__Allocator &__DEF_Tree::getSmm()const
//{
//	return this->smm;
//}

#undef __DEF_Template_Tree
#undef __DEF_Tree





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
    return (this->previous!=nullptr);
}

__DEF_Template_ListNode
int  __DEF_ListNode::hasNext()const
{
    return (this->next!=nullptr);
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

__DEF_Template_ListNode
template <class __EnvTransfer>
SerializerPtr<__EnvTransfer>& __DEF_ListNode::serialize(SerializerPtr<__EnvTransfer> &ptr)const
{
	return ptr 	<< data
				<< next
				<< previous;
}

__DEF_Template_ListNode
template <class __EnvTransfer>
SerializerPtr<__EnvTransfer>& __DEF_ListNode::deserialize(SerializerPtr<__EnvTransfer> &ptr)
{
	static_assert( __EnvTransfer::ptrPolicy()!=__EnvTransfer::POLICY_PTR_OBJECT,"ptr object policy not supported yet");
	ptr >> data
			>>next
			>>previous;
	return ptr;
}

__DEF_Template_ListNode
template <class __EnvTransfer>
size_t __DEF_ListNode::getSerializitionSize()
{
	static_assert( __EnvTransfer::ptrPolicy()!=__EnvTransfer::POLICY_PTR_OBJECT,"ptr object policy not supported yet");
	return data.getSerializitionSize<__EnvTransfer>()+
			__EnvTransfer::template sizeofHostType<decltype(this->next)>()+
			__EnvTransfer::template sizeofHostType<decltype(this->previous)>();
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
	return this->getHead()==nullptr;
}

#undef __DEF_Template_LinkedList
#undef __DEF_LinkedList


//=====class: SimpleMemoryNode
SimpleMemoryNode::SimpleMemoryNode(bool alloced):
alloced(alloced)
{
}

bool SimpleMemoryNode::isAlloced()
{
	return alloced;
}
void SimpleMemoryNode::setAlloced(bool alloced)
{
	this->alloced=alloced;
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
	return this->start <= static_cast<size_t>(t) && static_cast<size_t>(t) -
						static_cast<size_t>(this->start) <= this->limit ;
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
	__TreeNode* next=static_cast<__TreeNode*>(this->__ListNode::getNext());//这种情况下的强制转换一定是正确的，因为TreeNode中只存储TreeNode，而不会存储ListNode
	return next;
}

__DEF_Template_TreeNode
typename __DEF_TreeNode::__TreeNode* __DEF_TreeNode::getPrevious() const{
	__TreeNode* previous=static_cast<__TreeNode*>(this->__ListNode::getPrevious());
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
	return this->son!=nullptr;
}
__DEF_Template_TreeNode
bool 		 __DEF_TreeNode::hasFather()const
{
	return this->father!=nullptr;
}
__DEF_Template_TreeNode
template <class __EnvTransfer>
SerializerPtr<__EnvTransfer>& __DEF_TreeNode::serialize(SerializerPtr<__EnvTransfer> &ptr)const
{
	// TODO 修改下面的指针序列化
	// 调用父类的serialize,然后自己的
	this->Super::template serialize<__EnvTransfer>(ptr)
				<<son
				<<father;
	return ptr;
}

__DEF_Template_TreeNode
template <class __EnvTransfer>
SerializerPtr<__EnvTransfer>& __DEF_TreeNode::deserialize(SerializerPtr<__EnvTransfer> &ptr)
{
	this->Super::template deserialize<__EnvTransfer>(ptr)
						>>son
						>>father;
	return ptr;
}

__DEF_Template_TreeNode
template <class __EnvTransfer>
size_t __DEF_TreeNode::getSerializitionSize()
{
	static_assert( __EnvTransfer::ptrPolicy()!=__EnvTransfer::POLICY_PTR_OBJECT,"ptr object policy not supported yet");
	return this->Super::template getSerializitionSize<__EnvTransfer>()+
			__EnvTransfer::template sizeofHostType<decltype(this->son)>()+
			__EnvTransfer::template sizeofHostType<decltype(this->father)>();
}

#undef __DEF_Template_TreeNode
#undef __DEF_TreeNode



//======class Tree
