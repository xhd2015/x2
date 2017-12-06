
#include <List.h>
#include <MemoryManager.h>

#include <macros/all.h>
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
    if(this->hasNext())
    {
        this->setNext(rt->getNext());
        if(rt->hasNext())
        {
            rt->getNext()->setPrevious(this);
        }
    }
    return rt;
}

__DEF_Template_ListNode
typename __DEF_ListNode::__ListNode* __DEF_ListNode::removePrevious()
{
    __ListNode* rt=this->getPrevious();
    if(this->hasPrevious())
    {
        this->setPrevious(rt->getPrevious());
        if(rt->hasPrevious())
        {
            rt->getPrevious()->setNext(this);
        }
    }
    return rt;
}


__DEF_Template_ListNode
void    __DEF_ListNode::insertNext(__ListNode* next)
{
    if(next)
    {
        __ListNode* temp1;
        temp1 = this->getNext();
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
__DEF_LinkedList::LinkedList(__Allocator &smm):
smm(smm),root(nullptr),last(nullptr)
{
//	Kernel::printer->putsz("in LinkedList init\n");
//	Kernel::printer->putx("sizeof(ListNode<T>)=",x2sizeof(ListNode<T>));
//	Kernel::getTheKernel()->dumpInfo();
    char temp[sizeof(T)];
    __ListNode *node1=smm.getNew();
//    Kernel::printer->putx("node1=",(int)node1);
//	Kernel::getTheKernel()->dumpInfo();

    __ListNode *node2=smm.getNew();
//    Kernel::printer->putx("node2=",(int)node2);
//	Kernel::getTheKernel()->dumpInfo();

//	Util::insertMark(0x270270);
    this->root = new (node1) __ListNode(*reinterpret_cast<T*>(temp),nullptr,nullptr);
    this->last = new (node2) __ListNode(*reinterpret_cast<T*>(temp),nullptr,nullptr);
//	Kernel::printer->putsz("in LinkedList init return\n");
//	Util::jmpDie();
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

	this->smm.withdraw(this->root);
    this->smm.withdraw(this->last);

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
        smm.withdraw(p);
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
typename __DEF_LinkedList::__ListNode*  __DEF_LinkedList::
		appendHead(const T& t)
{
    return appendHead(new (smm.getNew()) __ListNode(t));
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
typename __DEF_LinkedList::__ListNode*    __DEF_LinkedList::
		removeHead()
{
    __ListNode* p=root->removeNext();
    if(p==getLast())
    {
        last->setNext(nullptr);
    }
    return p;
   
}
#undef __DEF_Template_LinkedList
#undef __DEF_LinkedList




//=============class : LocateableLinkedList
#define __DEF_Template_LocateableLinkedList template<class _Locateable,int _HowAllocated,template <class> class _Allocator>
#define __DEF_LocateableLinkedList LocateableLinkedList<_Locateable,_HowAllocated,_Allocator>

__DEF_Template_LocateableLinkedList
__DEF_LocateableLinkedList::LocateableLinkedList(__Allocator &smm ):
Super(smm)
{

}
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
__DEF_TreeNode::TreeNode(const T& data,__TreeNode* father,__TreeNode* son,__TreeNode* next,__TreeNode* previous):
__ListNode(data,next,previous),
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
typename __DEF_TreeNode::__TreeNode* __DEF_TreeNode::removeSon() {
	if(this->getSon())
	{
		__TreeNode *son=this->getSon()->getSon();
		this->setSon(son);
		son->setFather(this);
		this->getSon()->setFather(nullptr);
		this->getSon()->setSon(nullptr);

	}
	// TODO 改变返回参数，什么都不返回
	return nullptr;
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
typename __DEF_TreeNode::__TreeNode* __DEF_TreeNode::removeFather() {
	if(this->getDirectFather())
	{
		__TreeNode *father=this->getDirectFather()->getDirectFather();
		this->setFather(father);
		father->setSon(this);
		this->getDirectFather()->setFather(nullptr);
		this->getDirectFather()->setSon(nullptr);
	}
	//TODO 返回void
	return nullptr;
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
__DEF_Template_Tree
__DEF_Tree::Tree(__Allocator& smm,__TreeNode* root):
smm(smm),root(root)
{
#if defined(CODE32)
	Kernel::printer->putsz("in Tree init.");
	Kernel::printer->putsz("in Tree init2");
	Kernel::printer->putsz("in Tree init3");
	Kernel::printer->putsz("\n");
	Kernel::printer->putsz("in Tree init4");
	Util::insertMark(0x785785); // 0013417
#endif

	// TODO 恢复下面的代码
	__TreeNode *node=nullptr;
	if(root==nullptr && (node=smm.getNew())!=nullptr)
	{
		node->initToNull();
		this->root=node;
	}

//	Kernel::getTheKernel()->dumpInfo();
//	__TreeNode *node=reinterpret_cast<__TreeNode*>(Kernel::getTheKernel())->mnewKernel(x2sizeof(__TreeNode));

#if defined(CODE32)
	Kernel::printer->putsz("in Tree init return\n");
#endif
	//char saver[sizeof(T)];
	//new (this->root) __TreeNode(*(T*)saver);//root must be very carefully initiated,but if you don't do that,it is fine.Do be very
	//careful about the actual type at a position.Because that's really important.
	//this->root->setSon(0);
#if defined(CODE64)
//	printf("arg root is : %x,this->root : %x\n",root,this->root);
//	printf("ask you when TreeNode<FileDescriptor>,press y to stop\n");
//	while(getchar()!='\n');
//	int ask=getchar();
//	if(ask=='y')
//	{
//		TreeNode<FileDescriptor> * head=(TreeNode<FileDescriptor>*)this->getHead();
//		printf("call getFathter , %x \n",head->getDirectFather());
//	}
#endif
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
	 // 所有节点应当被撤销
//	free(this->root);

}

__DEF_Template_Tree
void         __DEF_Tree::free(__TreeNode *root)
{
  if(root)
  {
     __TreeNode* p=root->getSon();//先把所有子节点free
    while(p)
    {
    	__TreeNode* next=p->getNext();
        this->free(p);
        p = next;
    }//OK,all the sons are free
    smm.withdraw(root);
  }
}

#undef __DEF_Template_Tree
#undef __DEF_Tree
