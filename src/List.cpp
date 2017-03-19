
#include <List.h>
#include <Memory.h>
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
//	template class ListNode<int>;
//	template class ListNode<MemoryDescriptor>;
//	template class LinkedList<int,SimpleMemoryManager>;
//	template class Tree<MemoryDescriptor,SimpleMemoryManager>;
//	template class TreeNode<MemoryDescriptor>;
//	template class SimpleMemoryManager<ListNode<int> >;
//	template class SimpleMemoryManager<TreeNode<MemoryDescriptor> >;
#elif defined(CODE64)
#include <cstdio>
	#include "/home/13774/x2-devel/filesystem/verify-in-cygwin/File.h"
#include "/home/13774/x2-devel/filesystem/verify-in-cygwin/MallocToSimple.h"
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
data((Freeable*)start),len((int)(limit/sizeof(Freeable))),curSize(initSize),
lastIndex(0),
errhandle(errhandle)
{
    if(doInit)
    {

        for(int i=0;i!=len;i++)
        {
           data[i].free();
        }
           
    }
}

template <class T>
SimpleMemoryManager<T>::SimpleMemoryManager():
start(-1),limit(0),data(NULL),len(0),curSize(0),lastIndex(0),errhandle(NULL)
{


}


template <class T>
T* SimpleMemoryManager<T>::getNew()
{
	return (T*)this->getNewNode();
}

template <class T>
typename SimpleMemoryManager<T>::Node *SimpleMemoryManager<T>::getNewNode()
{
    Node *rt=NULL;
    if(!isFull())
    {
        for(int i=0;i!=len;i++)
        {
            if(data[lastIndex].isFree())
            {
                rt=&data[lastIndex];
                rt->unfree();
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
void SimpleMemoryManager<T>::withdraw(SimpleMemoryManager<T>::Node *t)
{
	Node* _t=(Node*)t;
    if(_t && !_t->isFree())
    {
        _t->free(); //如果被标记为可用，就用lastIndex指向之
        curSize--;
        lastIndex = (size_t)(((size_t)_t - (size_t)start)/sizeof(Node)) % len;
    }
}

template <class T>
void SimpleMemoryManager<T>::withdraw(T *t)
{
	this->withdraw((Node*)t);
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
	This::adjustOffset(this->next, diff);
	This::adjustOffset(this->previous, diff);
}
template<class T>
ListNode<T>*   ListNode<T>::getLast()const
{
    ListNode<T>* p=(ListNode<T>*)this;
    while(p->hasNext())
    {
        p=p->getNext();
    }
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
template<class T,template<class> class _Allocator>
LinkedList<T,_Allocator >::LinkedList():
smm(NULL),root(NULL),last(NULL)
{}

template<class T,template<class> class _Allocator>
LinkedList<T,_Allocator >::LinkedList(_Allocator<ListNode<T> > *smm):
smm(smm)
{
    char temp[sizeof(T)];
    this->root = new (smm->getNew()) ListNode<T>(*(T*)temp,NULL,NULL);
    this->last = new (smm->getNew()) ListNode<T>(*(T*)temp,NULL,NULL);
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
size_t   LinkedList<T,_Allocator >::getSize()
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
LocateableLinkedList<_Locateable,_HowAllocated,_Allocator>::LocateableLinkedList()
{

}
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

template<class T>
void TreeNode<T>::insertSon(TreeNode<T>* son) {
	if(son!=NULL)
	{
#if defined(CODE64)
//	printf("insertSon 0\n");
#endif
	this->getSon();
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
	Father::adjustOffset(this->father,diff);
	Father::adjustOffset(this->son,diff);
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
Tree<T,_Allocator>::Tree()
{
}
template<class T,template <class> class _Allocator>
Tree<T,_Allocator>::Tree(_Allocator<TreeNode<T> >* smm,TreeNode<T>* root):
smm(smm)
{
	this->root=root==NULL?smm->getNew():root;
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

template<class T,template <class> class _Allocator>
Tree<T,_Allocator>::~Tree() {
}

template<class T,template <class> class _Allocator>
void         Tree<T,_Allocator>::free(TreeNode<T> *root)
{
  if(root)
  {
     TreeNode<T>* p=root->getSon();//先把所有子类free
    while(p)
    {
        this->free(p);
        p =(TreeNode<T>*) p->getNext();
    }//OK,all the sons are free
    smm->withdraw(root);
  }
}
template<class T,template <class> class _Allocator>
TreeNode<T>* Tree<T,_Allocator>::getHead()const {
	return root->getSon();
}

template<class T,template <class> class _Allocator>
void  Tree<T,_Allocator>::setHead(TreeNode<T> *head)
 {
#if defined(CODE64)
	//printf("root : %x  , head : %x\n",root,head);
	//head->setFather(root);
	//head->setSon(root);
	//printf("head data : %x \n",head->getDirectFather());
#endif
 	root->setSon(head);//wrong
#if defined(CODE64)
 	//printf("root->setSon : %x\n",root->getSon());
#endif
 }
