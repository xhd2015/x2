
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
	template class ListNode<MemoryDescriptor>;
	template class TreeNode<MemoryDescriptor>;
	template class SimpleMemoryManager<ListNode<MemoryDescriptor> >;
	template class SimpleMemoryManager<TreeNode<MemoryDescriptor> >;
	template class Tree<MemoryDescriptor,SimpleMemoryManager>;
	template class ListNode<TreeNode<Process*>* >;

	template class ListNode<Process*>;
	template class TreeNode<Process*>;
	template class Tree<Process*,KernelSmmWrapper>;
	template class LinkedList<TreeNode<Process*>*,KernelSmmWrapper>;
	template class Tree<MemoryDescriptor,KernelSmmWrapper>;
#elif defined(CODE64)
#include <cstdio>
#include "filesystem/verify-in-cygwin/File.h"
#include <64/MallocToSimple.h>
	template class TreeNode<FileDescriptor>;
	template class SimpleMemoryManager<TreeNode<FileDescriptor> >;
	template class TreeNode<int>;
	template class SimpleMemoryManager<TreeNode<int> >;
	template class TreeNode<MemoryDescriptor>;
	template class Tree<FileDescriptor,SimpleMemoryManager>;
	template class Tree<MemoryDescriptor, MallocToSimple>;
	template class ListNode<LinearSourceDescriptor>;
	template class ListNode<FileDescriptor>;
	template class ListNode<MemoryDescriptor>;
	template class LinkedList<LinearSourceDescriptor, MallocToSimple>;
	template class LocateableLinkedList<LinearSourceDescriptor, Locator<LinearSourceDescriptor>::KEEP, MallocToSimple>;
	template class LocateableLinkedList<LinearSourceDescriptor, Locator<LinearSourceDescriptor>::DISCARD, MallocToSimple>;
#endif


//====================class :SimpleMemoryNode



//===================class: SimpleMemoryManager

template <class T>
SimpleMemoryManager<T>::SimpleMemoryManager(size_t start,size_t limit,bool doInit,size_t initSize,SimpleMemoryManager<T>::ERROR_HANDLER errhandle):
start(start),limit(limit),
data((FullNode*)start),len(limit/x2sizeof(FullNode)),curSize(initSize),
lastIndex(0),
errhandle(errhandle)
{
	Kernel::printer->puti("len=",len);
    if(doInit)
    {

        for(int i=0;i!=len;i++)
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
        for(int i=0;i!=len;i++)
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
    if(_t && !_t->isFree())
    {
        _t->free(); //如果被标记为可用，就用lastIndex指向之
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
template<class T>
ListNode<T>::ListNode(const T& data,ListNode<T>* next,ListNode<T>* previous):
data(data),
next(next),
previous(previous)
{
}
template<class T>
ListNode<T>::~ListNode()
{
    
}
    
template<class T>
ListNode<T>* ListNode<T>::removeNext()
{
    ListNode<T>* rt=this->getNext();
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

template<class T>
ListNode<T>* ListNode<T>::removePrevious()
{
    ListNode<T>* rt=this->getPrevious();
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


template<class T>
void    ListNode<T>::insertNext(ListNode<T>* next)
{
    if(next)
    {
        ListNode<T>* temp1;
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

template<class T>
void    ListNode<T>::insertPrevious(ListNode<T>* previous)
{
    if(previous)
    {
        ListNode<T>* prev=this->getPrevious();
        if(prev)
        {
            prev->setNext(previous);
        }
        previous->setNext(this);
        previous->setPrevious(prev);
        this->setPrevious(previous);
    }
}
template<class T>
void   ListNode<T>::adjustOffset(ptrdiff_t diff)
{
	if(this->next!=NULL)
		this->next = (ListNode<T>*)((char*)this->next + diff);
	if(this->previous!=NULL)
		this->previous = (ListNode<T>*)((char*)this->previous + diff);
}
template<class T>
void   ListNode<T>::initToNull()
{
	next = previous = NULL;
}
template<class T>
ListNode<T>*   ListNode<T>::getLast()const
{
//	Util::printStr("in ListNode getLast\n");
    ListNode<T>* p=(ListNode<T>*)this;
    while(p->hasNext())
    {
        p=p->getNext();
    }
//    Util::printStr("in getLast returning \n");
    return p;
}
template<class T>
ListNode<T>*    ListNode<T>::getFirst()const
{
    ListNode<T> *p=(ListNode<T>*)this;
    while(p->hasPrevious())
    {
        p=p->getPrevious();
    }
    return p;
}

//===============class : LinkedList
//template<class T,template<class> class _Allocator>
//LinkedList<T,_Allocator >::LinkedList():
//smm(NULL),root(NULL),last(NULL)
//{}

template<class T,template<class> class _Allocator>
LinkedList<T,_Allocator >::LinkedList(_Allocator<ListNode<T> > *smm):
smm(smm)
{
//	Kernel::printer->putsz("in LinkedList init\n");
//	Kernel::printer->putx("sizeof(ListNode<T>)=",x2sizeof(ListNode<T>));
//	Kernel::getTheKernel()->dumpInfo();
    char temp[sizeof(T)];
    ListNode<T> *node1=smm->getNew();
//    Kernel::printer->putx("node1=",(int)node1);
//	Kernel::getTheKernel()->dumpInfo();

    ListNode<T> *node2=smm->getNew();
//    Kernel::printer->putx("node2=",(int)node2);
//	Kernel::getTheKernel()->dumpInfo();

//	Util::insertMark(0x270270);
    this->root = new (node1) ListNode<T>(*(T*)temp,NULL,NULL);
    this->last = new (node2) ListNode<T>(*(T*)temp,NULL,NULL);
//	Kernel::printer->putsz("in LinkedList init return\n");
//	Util::jmpDie();
}

template<class T,template<class> class _Allocator>
LinkedList<T,_Allocator >::~LinkedList()
{
    this->free();
}
template<class T,template<class> class _Allocator>
void LinkedList<T,_Allocator >::free()
{
    this->smm->withdraw(this->last);

    this->freeNext(this->root);

    this->root=NULL;
    this->last=NULL;

}
template<class T,template<class> class _Allocator>
void LinkedList<T,_Allocator >::freeNext(ListNode<T> *t)
{
    if(!t || t==root || t==last)return;
    ListNode<T> *p=t;
    while(p)
    {
        smm->withdraw(p);
        p=p->getNext();
    }

    t->getPrevious()->setNext(NULL);
    this->last->setNext(t->getPrevious()==root?NULL:t->getPrevious());   

}

template<class T,template<class> class _Allocator>
void LinkedList<T,_Allocator >::freePrevious(ListNode<T> *t)
{
    if(!t || t==root || t==last)return;
    ListNode<T> *p=t;
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
template<class T,template<class> class _Allocator>
void    LinkedList<T,_Allocator>::freeNode(ListNode<T> * node)
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


/****DEPRECATED
template <class T>
void LinkedList<T>::refresh()
{
    size=0;
    ListNode<T>* p=root;
    while(p->hasNext())
    {
        p=p->getNext();
        size++;
    }
    this->last->setNext(p);
}
*/
template<class T,template<class> class _Allocator>
ListNode<T>*  LinkedList<T,_Allocator >::append(const T& t)
{
    return append(new (smm->getNew()) ListNode<T>(t));
}
template<class T,template<class> class _Allocator>
ListNode<T>*  LinkedList<T,_Allocator >::append(ListNode<T>* p)
{
    if(!p)return NULL;
    ListNode<T>* rlast=getLast();
    if(rlast==NULL)
    {
        rlast=this->root;
    }
    rlast->insertNext(p);
    last->setNext(p);

    return p;
}

template<class T,template<class> class _Allocator>
ListNode<T>* LinkedList<T,_Allocator >::appendHead(const T& t)
{
    return appendHead(new (smm->getNew()) ListNode<T>(t));
}

template<class T,template<class> class _Allocator>
ListNode<T>* LinkedList<T,_Allocator >::appendHead(ListNode<T>* p)
{
    if(!p)return NULL;
    root->insertNext(p);
    if(getLast()==NULL)
    {
        last->setNext(p);
    }
    return p;
}
template<class T,template<class> class _Allocator>
ListNode<T>*    LinkedList<T,_Allocator >::remove()
{
   ListNode<T>* plast=getLast();
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


template<class T,template<class> class _Allocator>
void    LinkedList<T,_Allocator >::remove(ListNode<T>* p)
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

template<class T,template<class> class _Allocator>
void	 LinkedList<T,_Allocator >::insertNext(ListNode<T>* where,ListNode<T>* p)
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
template<class T,template<class> class _Allocator>
void	 LinkedList<T,_Allocator >::insertPrevious(ListNode<T>* where,ListNode<T>* p)
{
	if(where==NULL||where==this->root||p==NULL)return;
	if(root->getNext()==where)
	{
		this->appendHead(p);
	}else{
		where->insertPrevious(p);
	}

}
template<class T,template<class> class _Allocator>
size_t   LinkedList<T,_Allocator >::getSize()const
{
	size_t size=0;
	ListNode<T>* p=root;
	while(p->hasNext())
	{
		size++;
		p=p->getNext();
	}
	return size;
}
template<class T,template<class> class _Allocator>
ListNode<T>*    LinkedList<T,_Allocator >::removeHead()
{
    ListNode<T>* p=root->removeNext();
    if(p==getLast())
    {
        last->setNext(NULL);
    }
    return p;
   
}




//=============class : LocateableLinkedList
template<class _Locateable,int _HowAllocated,template <class> class _Allocator >
LocateableLinkedList<_Locateable,_HowAllocated,_Allocator>::LocateableLinkedList( _Allocator<ListNode<_Locateable> > *smm ):
LinkedList<_Locateable,_Allocator >(smm)
{

}
template<class _Locateable,int _HowAllocated,template <class> class _Allocator >
LocateableLinkedList<_Locateable,_HowAllocated,_Allocator>::~LocateableLinkedList()
{

}
/**
* Do I work on a KEEP-ALLOCATED or DISCARD-ALLOCATED list?
*
*  Find  a node that is less than or equal to start,and can contain it
*   The 'template argument' combination technnique is(maybe that I now say 'often' appears too early) used in an extension system.The template arguments will cover all the nodes from base to the deepest derived class.
*/
template<class _Locateable,int _HowAllocated,template <class> class _Allocator >
ListNode<_Locateable> *LocateableLinkedList<_Locateable,_HowAllocated,_Allocator>::findFirstStartLen(ListNode<_Locateable>* startNode,size_t start,size_t len)
{
    if(!startNode||len==0)return NULL;
#if defined(CODE64)
//    printf("findFirstStartLen for (%x,%x)\n",start,len);
#endif
    ListNode<_Locateable>* p=startNode;
    _Locateable tloc(start,len);
    SourceLocator<_Locateable,Locator<_Locateable>::LESS,Locator<_Locateable>::IGNORE,Locator<_Locateable>::IGNORE> lessLocator(tloc);
#if defined(CODE64)
//    	printf("1 : p is(%x - %x) ,tloc is (%x - %x)\n ",p->getData().getStart(),p->getData().getStart()+p->getData().getLimit(),
//    			tloc.getStart(),
//				tloc.getStart()+tloc.getLimit()
//    			);
#endif
    while(p && lessLocator.tellLocation(p->getData()))
    	{
#if defined(CODE64)
//    	printf("2 : p is(%x - %x) ,tloc is (%x - %x)\n ",p->getData().getStart(),p->getData().getStart()+p->getData().getLimit(),
//    			tloc.getStart(),
//				tloc.getStart()+tloc.getLimit()
//    			);
#endif
    		if(p->getData().contains(tloc))
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

template<class _Locateable,int _HowAllocated,template <class> class _Allocator >
ListNode<_Locateable> *LocateableLinkedList<_Locateable,_HowAllocated,_Allocator>::findFirstLen(ListNode<_Locateable>* startNode,size_t len)
{
    if(!startNode||len==0)return NULL;
    ListNode<_Locateable>* p=startNode;
    _Locateable tloc(0,len);
    SourceLocator<_Locateable,Locator<_Locateable>::IGNORE,Locator<_Locateable>::EQUAL,Locator<_Locateable>::IGNORE> equLocator(tloc);
    SourceLocator<_Locateable,Locator<_Locateable>::IGNORE,Locator<_Locateable>::BIGGER,Locator<_Locateable>::IGNORE> biggerLocator(tloc);
    while(p && !equLocator.tellLocation(p->getData()) && !biggerLocator.tellLocation(p->getData()))
    {
        p=LocateableLinkedList<_Locateable,_HowAllocated,_Allocator>::nextAllocable(p);
    }
    return p;
}

template<class _Locateable,int _HowAllocated,template <class> class _Allocator >
ListNode<_Locateable> *LocateableLinkedList<_Locateable,_HowAllocated,_Allocator>::findFirstStart(ListNode<_Locateable>* startNode,size_t start)
{
    if(!startNode)return NULL;

    _Locateable tloc(start,0);
    ListNode<_Locateable>* p=LocateableLinkedList<_Locateable,_HowAllocated,_Allocator>::findFirstStartForInsert(startNode,start);
    SourceLocator<_Locateable,Locator<_Locateable>::EQUAL,Locator<_Locateable>::IGNORE,Locator<_Locateable>::IGNORE> equLocator(tloc);
    if(p && (equLocator.tellLocation(p->getData()) ))
    {
        return p;
    }else{
        return NULL;
    }
}
template<class _Locateable,int _HowAllocated,template <class> class _Allocator >
ListNode<_Locateable> *LocateableLinkedList<_Locateable,_HowAllocated,_Allocator>::findFirstStartForInsert(ListNode<_Locateable> *startNode,size_t start)
{
    if(!startNode)return NULL;
    ListNode<_Locateable> *p=startNode,*last=startNode;
    _Locateable tloc(start,0);
    SourceLocator<_Locateable,Locator<_Locateable>::LESS,Locator<_Locateable>::IGNORE,Locator<_Locateable>::IGNORE> lessLocator(tloc);

    while(p && lessLocator.tellLocation(p->getData()))
        {
            startNode=p;
            p=LocateableLinkedList<_Locateable,_HowAllocated,_Allocator>::nextAllocable(p);
        }
    if(p==NULL)
    {
        return last;
    }
    return p;

}
template<class _Locateable,int _HowAllocated,template <class> class _Allocator >
ListNode<_Locateable>* LocateableLinkedList<_Locateable,_HowAllocated,_Allocator>::nextAllocable(ListNode<_Locateable>* startNode)
{
    return LocateableLinkedList<_Locateable,_HowAllocated,_Allocator>::nextAllocable(startNode,Int2Type<_HowAllocated>());
}


template<class _Locateable,int _HowAllocated,template <class> class _Allocator >
ListNode<_Locateable>* LocateableLinkedList<_Locateable,_HowAllocated,_Allocator>::nextAllocable(ListNode<_Locateable>* startNode,Int2Type<Locator<_Locateable>::KEEP>)
{
         if(startNode)
        {
            do{
                startNode=startNode->getNext();
            }while( startNode && (! startNode->getData().isAllocable()) );
        }
        return startNode;
}

template<class _Locateable,int _HowAllocated,template <class> class _Allocator >
ListNode<_Locateable>* LocateableLinkedList<_Locateable,_HowAllocated,_Allocator>::nextAllocable(ListNode<_Locateable>* startNode,Int2Type<Locator<_Locateable>::DISCARD>)
{
    return startNode==NULL?NULL:startNode->getNext();
}


//============class : TreeNode
template<class T>
TreeNode<T>::TreeNode(const T& data,TreeNode<T>* father,TreeNode<T>* son,TreeNode<T>* next,TreeNode<T>* previous):
ListNode<T>(data,next,previous),
father(father),
son(son)
{

}
template<class T>
inline TreeNode<T>::~TreeNode() {
}

//#if defined(CODE64)
//template<class T>
//TreeNode<T>* TreeNode<T>::getSon() const{
//#if defined(CODE64)
//	printf("gettSon not macro\n");
//#endif
//	return son;
//}
//#endif


template<class T>
void TreeNode<T>::addSon(TreeNode<T>* son)
{
//	Util::printStr("in TreeNode addSon \n");
	TreeNode<T>*	orison=this->getSon();
	if(orison)
	{
		orison->getLast()->insertNext(son);
	}else{
		this->setSon(son);
	}
}
template<class T>
void TreeNode<T>::insertSon(TreeNode<T>* son) {
	if(son!=NULL)
	{
#if defined(CODE64)
//	printf("insertSon 0\n");
#endif
#if defined(CODE64)
//	printf("getSon return\n");
#endif
		TreeNode<T> *orison=this->getSon();
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

template<class T>
void TreeNode<T>::insertFather(TreeNode<T>* father) {
	if(father!=NULL)
	{
		TreeNode<T> *orifather=this->getDirectFather();
		this->setFather(father);
		father->setSon(this);
		father->setFather(orifather);
		if(orifather)
		{
			orifather->setSon(father);
		}
	}
}

template<class T>
TreeNode<T>* TreeNode<T>::removeSon() {
	if(this->getSon())
	{
		TreeNode<T> *son=this->getSon()->getSon();
		this->setSon(son);
		son->setFather(this);
		this->getSon()->setFather(NULL);
		this->getSon()->setSon(NULL);
	}
}
template<class T>
void 			TreeNode<T>::adjustOffset(ptrdiff_t diff)
{
	this->Father::adjustOffset(diff);
	if(this->father!=NULL)
		this->father = (TreeNode<T>*)((char*)this->father + diff);
	if(this->son!=NULL)
		this->son = (TreeNode<T>*)((char*)this->son + diff);
}
template<class T>
void 			TreeNode<T>::initToNull()
{
	ListNode<T>::initToNull();
	father=son=NULL;
}

template<class T>
TreeNode<T>* TreeNode<T>::removeFather() {
	if(this->getDirectFather())
	{
		TreeNode<T> *father=this->getDirectFather()->getDirectFather();
		this->setFather(father);
		father->setSon(this);
		this->getDirectFather()->setFather(NULL);
		this->getDirectFather()->setSon(NULL);
	}
}

template<class T>
TreeNode<T>* TreeNode<T>::getParent()const {//往previous一直遍历，直到是跟，然后返回跟的father
	TreeNode<T> *p=(TreeNode<T>*)this;
	while(p->hasPrevious())
	{
		p=(TreeNode<T>*)p->getPrevious();
	}
	return p->getDirectFather();
}

//===============class Tree
#if defined(CODE64)
#include <cstdio>
#endif
template<class T,template <class> class _Allocator>
Tree<T,_Allocator>::Tree(_Allocator<TreeNode<T> >* smm,TreeNode<T>* root):
smm(smm)
{

	Kernel::printer->putsz("in Tree init.");
	Kernel::printer->putsz("in Tree init2");
	Kernel::printer->putsz("in Tree init3");
	Kernel::printer->putsz("\n");
	Kernel::printer->putsz("in Tree init4");
	Util::insertMark(0x785785); // 0013417

	// TODO 恢复下面的代码
	TreeNode<T> *node=smm->getNew();
//	Kernel::getTheKernel()->dumpInfo();
//	TreeNode<T> *node=(TreeNode<T>*)Kernel::getTheKernel()->mnewKernel(x2sizeof(TreeNode<T>));
	node->initToNull();
	this->root=(root==NULL?node:root);


	Kernel::printer->putsz("in Tree init return\n");
	//char saver[sizeof(T)];
	//new (this->root) TreeNode<T>(*(T*)saver);//root must be very carefully initiated,but if you don't do that,it is fine.Do be very
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
template<class T,template <class> class _Allocator>
void Tree<T,_Allocator>::dumpInfo(Printer* p)const
{
	if(p!=NULL)
	{
		p->putsz("Tree{");

		p->putsz("}");
	}
}
#endif

template<class T,template <class> class _Allocator>
Tree<T,_Allocator>::Tree()
{

}
template<class T,template <class> class _Allocator>
Tree<T,_Allocator>::~Tree() {
}

template<class T,template <class> class _Allocator>
void         Tree<T,_Allocator>::free(TreeNode<T> *root)
{
  if(root)
  {
     TreeNode<T>* p=root->getSon();//先把所有子节点free
    while(p)
    {
    	TreeNode<T>* next=p->getNext();
        this->free(p);
        p = next;
    }//OK,all the sons are free
    smm->withdraw(root);
  }
}
