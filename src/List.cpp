
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
data((FullNode*)start),curSize(initSize),len(limit/x2sizeof(FullNode)),
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
//start(-1),limit(0),data(NULL),len(0),curSize(0),lastIndex(0),errhandle(NULL)
//{
//
//
//}


template <class T>
T* SimpleMemoryManager<T>::getNew()
{
	return (T*)this->getNewNode();
}

template <class T>
typename SimpleMemoryManager<T>::FullNode *SimpleMemoryManager<T>::getNewNode()
{
	//Kernel::printer->putsz("in getNewNode\n");
    FullNode *rt=NULL;
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
	FullNode* _t=(FullNode*)t;
    if(_t && _t->isAlloced())
    {
        _t->setAlloced(false); //如果被标记为可用，就用lastIndex指向之
        curSize--;
        lastIndex = (size_t)(((size_t)_t - (size_t)start)/sizeof(FullNode)) % len;
    }
}

template <class T>
void SimpleMemoryManager<T>::withdraw(T *t)
{
	this->withdraw((FullNode*)t);
}


//===========class : ListNode
#if defined(CODE64)
#define __DEF_ALIGNMENT sizeof(size_t)
#include <preprocessor_functions/List.cpp.RAW>
#endif

#if defined(CODE32) ||defined(CODE32USER)|| defined(CODE64)
#define __DEF_ALIGNMENT 4
#include <preprocessor_functions/List.cpp.RAW>
#endif

#if defined(CODE16) || defined(CODE32) ||defined(CODE32USER)|| defined(CODE64)
#define __DEF_ALIGNMENT 2
#include <preprocessor_functions/List.cpp.RAW>
#endif


//===============class : LinkedList
//template<class T,template<class> class _Allocator>
//LinkedList<T,_Allocator >::LinkedList():
//smm(NULL),root(NULL),last(NULL)
//{}

template<class T,template<class> class _Allocator,int __Alignment>
LinkedList<T,_Allocator,__Alignment>::LinkedList(__Allocator *smm):
smm(smm)
{
//	Kernel::printer->putsz("in LinkedList init\n");
//	Kernel::printer->putx("sizeof(ListNode<T>)=",x2sizeof(ListNode<T>));
//	Kernel::getTheKernel()->dumpInfo();
    char temp[sizeof(T)];
    __ListNode *node1=smm->getNew();
//    Kernel::printer->putx("node1=",(int)node1);
//	Kernel::getTheKernel()->dumpInfo();

    __ListNode *node2=smm->getNew();
//    Kernel::printer->putx("node2=",(int)node2);
//	Kernel::getTheKernel()->dumpInfo();

//	Util::insertMark(0x270270);
    this->root = new (node1) __ListNode(*(T*)temp,NULL,NULL);
    this->last = new (node2) __ListNode(*(T*)temp,NULL,NULL);
//	Kernel::printer->putsz("in LinkedList init return\n");
//	Util::jmpDie();
}

template<class T,template<class> class _Allocator,int __Alignment>
LinkedList<T,_Allocator,__Alignment>::~LinkedList()
{
    this->free();
}
template<class T,template<class> class _Allocator,int __Alignment>
void LinkedList<T,_Allocator,__Alignment>::free()
{
    this->smm->withdraw(this->last);

    this->freeNext(this->root);

    this->root=NULL;
    this->last=NULL;

}
template<class T,template<class> class _Allocator,int __Alignment>
void LinkedList<T,_Allocator,__Alignment>::freeNext(__ListNode *t)
{
    if(!t || t==root || t==last)return;
    __ListNode *p=t;
    while(p)
    {
        smm->withdraw(p);
        p=p->getNext();
    }

    t->getPrevious()->setNext(NULL);
    this->last->setNext(t->getPrevious()==root?NULL:t->getPrevious());   

}

template<class T,template<class> class _Allocator,int __Alignment>
void LinkedList<T,_Allocator,__Alignment>::freePrevious(__ListNode *t)
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
        this->last->setNext(NULL);
    }
}   
template<class T,template<class> class _Allocator,int __Alignment>
void    LinkedList<T,_Allocator,__Alignment>::freeNode(__ListNode * node)
{
    if(node && node!=root && node!=last)
    {
        if(node==getLast())
        {
            if(node==getHead())
            {
                last->setNext(NULL);
            }else{
                last->setNext(node->getPrevious());
            }
        }
        node->getPrevious()->removeNext();
        smm->withdraw(node);
    }
}

template<class T,template<class> class _Allocator,int __Alignment>
typename LinkedList<T,_Allocator,__Alignment>::__ListNode*  LinkedList<T,_Allocator,__Alignment>::
	append(const T& t)
{
    return append(new (smm->getNew()) __ListNode(t));
}
template<class T,template<class> class _Allocator,int __Alignment>
typename LinkedList<T,_Allocator,__Alignment>::__ListNode*  LinkedList<T,_Allocator,__Alignment>::
		append(__ListNode* p)
{
    if(!p)return NULL;
    __ListNode* rlast=getLast();
    if(rlast==NULL)
    {
        rlast=this->root;
    }
    rlast->insertNext(p);
    last->setNext(p);

    return p;
}

template<class T,template<class> class _Allocator,int __Alignment>
typename LinkedList<T,_Allocator,__Alignment>::__ListNode*  LinkedList<T,_Allocator,__Alignment>::
		appendHead(const T& t)
{
    return appendHead(new (smm->getNew()) __ListNode(t));
}

template<class T,template<class> class _Allocator,int __Alignment>
typename LinkedList<T,_Allocator,__Alignment>::__ListNode*  LinkedList<T,_Allocator,__Alignment>::
		appendHead(__ListNode* p)
{
    if(!p)return NULL;
    root->insertNext(p);
    if(getLast()==NULL)
    {
        last->setNext(p);
    }
    return p;
}
template<class T,template<class> class _Allocator,int __Alignment>
typename LinkedList<T,_Allocator,__Alignment>::__ListNode*    LinkedList<T,_Allocator,__Alignment>::
		remove()
{
   __ListNode* plast=getLast();
   if(plast)
   {
    plast->getPrevious()->setNext(NULL);
    if(root->getNext() == last->getNext() )
    {
        last->setNext(NULL);
    } else{
        last->setNext(plast->getPrevious());
    }
   }
   return plast;
   
}


template<class T,template<class> class _Allocator,int __Alignment>
void    LinkedList<T,_Allocator,__Alignment>::remove(__ListNode* p)
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

template<class T,template<class> class _Allocator,int __Alignment>
void	 LinkedList<T,_Allocator,__Alignment>::insertNext(__ListNode* where,__ListNode* p)
{
	if(where==NULL||p==NULL)return;
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
template<class T,template<class> class _Allocator,int __Alignment>
void	 LinkedList<T,_Allocator,__Alignment>::insertPrevious(__ListNode* where,__ListNode* p)
{
	if(where==NULL||where==this->root||p==NULL)return;
	if(root->getNext()==where)
	{
		this->appendHead(p);
	}else{
		where->insertPrevious(p);
	}

}
template<class T,template<class> class _Allocator,int __Alignment>
size_t   LinkedList<T,_Allocator,__Alignment>::getSize()const
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
template<class T,template<class> class _Allocator,int __Alignment>
typename LinkedList<T,_Allocator,__Alignment>::__ListNode*    LinkedList<T,_Allocator,__Alignment>::
		removeHead()
{
    __ListNode* p=root->removeNext();
    if(p==getLast())
    {
        last->setNext(NULL);
    }
    return p;
   
}




//=============class : LocateableLinkedList
#define __DEF_LocateableLinkedList LocateableLinkedList<_Locateable,_HowAllocated,_Allocator,__SizeType,__Alignment>

template<class _Locateable,int _HowAllocated,template <class> class _Allocator ,typename __SizeType,int __Alignment>
__DEF_LocateableLinkedList::LocateableLinkedList(__Allocator *smm ):
Super(smm)
{

}
template<class _Locateable,int _HowAllocated,template <class> class _Allocator ,typename __SizeType,int __Alignment>
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
template<class _Locateable,int _HowAllocated,template <class> class _Allocator ,typename __SizeType,int __Alignment>
typename __DEF_LocateableLinkedList::__ListNode*__DEF_LocateableLinkedList::
findFirstStartLen(__ListNode* startNode,__SizeType start,__SizeType len)
{
    if(!startNode||len==0)return NULL;
#if defined(CODE64)
//    printf("findFirstStartLen for (%x,%x)\n",start,len);
#endif
    __ListNode* p=startNode;
    _Locateable tloc(start,len);

     // start要小于，长度忽略,可分配性忽略
    // 即p.start < tloc.start 其他忽略
    // (x,y)  (a0,b0)-->(a1,b1)-->(a2,b2)-->NULL
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
//    if(p==NULL)
//    {
//    	printf("NULL\n");
//    }else{
//    	printf("(%x,%x) \n",p->getData().getStart(),p->getData().getLimit());
//    }
#endif
    return p;
}

template<class _Locateable,int _HowAllocated,template <class> class _Allocator,typename __SizeType,int __Alignment>
typename __DEF_LocateableLinkedList::__ListNode*__DEF_LocateableLinkedList::findFirstLen(__ListNode* startNode,__SizeType len)
{
    if(!startNode||len==0)return NULL;
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

template<class _Locateable,int _HowAllocated,template <class> class _Allocator ,typename __SizeType,int __Alignment>
typename __DEF_LocateableLinkedList::__ListNode*__DEF_LocateableLinkedList::findFirstStart(__ListNode* startNode,__SizeType start)
{
    if(!startNode)return NULL;

    _Locateable tloc(start,0);
    __ListNode* p=__DEF_LocateableLinkedList::findFirstStartForInsert(startNode,start);
    SourceLocator<_Locateable,Locator<_Locateable>::EQUAL,Locator<_Locateable>::IGNORE,Locator<_Locateable>::IGNORE> equLocator(tloc);
    if(p && (equLocator.meetedBy(p->getData()) ))
    {
        return p;
    }else{
        return NULL;
    }
}
template<class _Locateable,int _HowAllocated,template <class> class _Allocator ,typename __SizeType,int __Alignment>
typename __DEF_LocateableLinkedList::__ListNode*__DEF_LocateableLinkedList::findFirstStartForInsert(__ListNode *startNode,__SizeType start)
{
    if(!startNode)return NULL;
    __ListNode *p=startNode,*last=startNode;
    _Locateable tloc(start,0);
    SourceLocator<_Locateable,Locator<_Locateable>::LESS,Locator<_Locateable>::IGNORE,Locator<_Locateable>::IGNORE> lessLocator(tloc);

    while(p && lessLocator.meetedBy(p->getData()))
        {
            startNode=p;
            p=__DEF_LocateableLinkedList::nextAllocable(p);
        }
    if(p==NULL)
    {
        return last;
    }
    return p;

}
template<class _Locateable,int _HowAllocated,template <class> class _Allocator ,typename __SizeType,int __Alignment>
typename __DEF_LocateableLinkedList::__ListNode* __DEF_LocateableLinkedList::
	nextAllocable(__ListNode* startNode)
{
    return __DEF_LocateableLinkedList::nextAllocable(startNode,Int2Type<_HowAllocated>());
}

template<class _Locateable,int _HowAllocated,template <class> class _Allocator ,typename __SizeType,int __Alignment>
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

template<class _Locateable,int _HowAllocated,template <class> class _Allocator ,typename __SizeType,int __Alignment>
typename __DEF_LocateableLinkedList::__ListNode* __DEF_LocateableLinkedList::
	nextAllocable(__ListNode* startNode,Int2Type<Locator<_Locateable>::DISCARD>)
{
    return startNode==NULL?NULL:startNode->getNext();
}
#undef __DEF_LocateableLinkedList


//============class : TreeNode
#if defined(CODE64)
#define __DEF_ALIGNMENT sizeof(size_t)
#include <preprocessor_functions/List_TreeNode.cpp.RAW>
#endif

#if defined(CODE32) ||defined(CODE32USER)|| defined(CODE64)
#define __DEF_ALIGNMENT 4
#include <preprocessor_functions/List_TreeNode.cpp.RAW>
#endif

#if defined(CODE16) || defined(CODE32) ||defined(CODE32USER)|| defined(CODE64)
#define __DEF_ALIGNMENT 2
#include <preprocessor_functions/List_TreeNode.cpp.RAW>
#endif



//===============class Tree
#if defined(CODE64)
#include <cstdio>
#endif
template<class T,template <class> class _Allocator,int __Alignment>
Tree<T,_Allocator,__Alignment>::Tree(__Allocator* smm,__TreeNode* root):
smm(smm)
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
	__TreeNode *node=smm->getNew();
//	Kernel::getTheKernel()->dumpInfo();
//	__TreeNode *node=(__TreeNode*)Kernel::getTheKernel()->mnewKernel(x2sizeof(__TreeNode));
	node->initToNull();
	this->root=(root==NULL?node:root);

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
template<class T,template <class> class _Allocator,int __Alignment>
void Tree<T,_Allocator,__Alignment>::dumpInfo(Printer* p)const
{
	if(p!=NULL)
	{
		p->putsz("Tree{");

		p->putsz("}");
	}
}
#endif

template<class T,template <class> class _Allocator,int __Alignment>
Tree<T,_Allocator,__Alignment>::Tree()
{

}
template<class T,template <class> class _Allocator,int __Alignment>
Tree<T,_Allocator,__Alignment>::~Tree() {
}

template<class T,template <class> class _Allocator,int __Alignment>
void         Tree<T,_Allocator,__Alignment>::free(__TreeNode *root)
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
    smm->withdraw(root);
  }
}
