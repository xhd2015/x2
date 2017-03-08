
#include <List.h>
#include <Memory.h>
#include <libx2.h>
#include <test.h>
#include <Locator.h>

//==========实例化模板
////===========模板声明区
//template class ListNode<int>;
//template class LinkedList<int>;
//template class ListNode<MemoryDescriptor>;
//template class Tree<MemoryDescriptor>;
//template class TreeNode<MemoryDescriptor>;
//template class SimpleMemoryManager<ListNode<int> >;
//template class SimpleMemoryManager<TreeNode<MemoryDescriptor> >;


//====================class :SimpleMemoryNode



//===================class: SimpleMemoryManager

template <class T>
SimpleMemoryManager<T>::SimpleMemoryManager(size_t start,size_t limit,bool doInit):
start(start),limit(limit),
data((T*)start),len((int)(limit/sizeof(T))),curSize(0),
lastIndex(0)
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
start(-1),limit(0),data(NULL),len(0),curSize(0),lastIndex(0)
{


}


template <class T>
T* SimpleMemoryManager<T>::getNew()
{
    T *rt=NULL;
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
    return rt;
}

template <class T>
void SimpleMemoryManager<T>::withdraw(T *t)
{
    if(t && !t->isFree())
    {
        t->free(); //如果被标记为可用，就用lastIndex指向之
        curSize--;
        lastIndex = (unsigned int)(((int)t - (int)start)/sizeof(T));
    }
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
ListNode<T>*   ListNode<T>::getLast()const
{
    ListNode<T>* p=this;
    while(p->hasNext())
    {
        p=p->getNext();
    }
    return p;
}
template<class T>
ListNode<T>*    ListNode<T>::getFirst()const
{
    ListNode<T> *p=this;
    while(p->hasPrevious())
    {
        p=p->getPrevious();
    }
    return p;
}

//===============class : LinkedList
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
    
}
template<class T,template<class> class _Allocator>
void LinkedList<T,_Allocator >::free()
{
    this->smm->withdraw(this->last);

    this->freeNext(this->root);

    this->root->setNext(NULL);
    this->last->setNext(NULL);

}
template<class T,template<class> class _Allocator>
void LinkedList<T,_Allocator >::freeNext(T *t)
{
    if(!t || t==root || t==last)return;
    T *p=t;
    while(p)
    {
        smm->withdraw(p);
        p=p->getNext();
    }

    t->getPrevious()->setNext(NULL);
    this->last->setNext(t->getPrevious()==root?NULL:t->getPrevious());   

}

template<class T,template<class> class _Allocator>
void LinkedList<T,_Allocator >::freePrevious(T *t)
{
    if(!t || t==root || t==last)return;
    T *p=t;
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
    root->setNext(p);
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
    if(!p || p==root || p==last)return;
    if(p==getLast())
    {
        remove();
    }else{
        p->getPrevious()->removeNext();    
    }
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
LinkedList<_Locateable,_Allocator<_Locateable> >(smm)
{

}
template<class _Locateable,int _HowAllocated,template <class> class _Allocator >
LocateableLinkedList<_Locateable,_HowAllocated,_Allocator>::~LocateableLinkedList()
{

}
/**
* Do I work on a KEEP-ALLOCATED or DISCARD-ALLOCATED list?
*
*   The 'template argument' combination technnique is(maybe that I now say 'often' appears too early) used in an extension system.The template arguments will cover all the nodes from base to the deepest derived class.
*/
template<class _Locateable,int _HowAllocated,template <class> class _Allocator >
ListNode<_Locateable> *LocateableLinkedList<_Locateable,_HowAllocated,_Allocator>::findFirstStartLen(ListNode<_Locateable>* startNode,size_t start,size_t len)
{
    if(!startNode||len==0)return NULL;
    ListNode<_Locateable>* p=startNode;
    _Locateable tloc(start,len);
    SourceLocator<_Locateable,Locator::LESS,Locator::IGNORE,Locator::IGNORE> lessLocator(&tloc);

    while(p && lessLocator.tellLocation(*p))p=LocateableLinkedList<_Locateable,_HowAllocated,_Allocator>::nextAllocable(p);


    SourceLocator<_Locateable,Locator::EQUAL,Locator::EQUAL,Locator::IGNORE> equLocator(&loc);
    SourceLocator<_Locateable,Locator::EQUAL,Locator::BIGGER,Locator::IGNORE> biggerLocator(&loc);
    if(p && (equLocator.tellLocation(*p) || biggerLocator.tellLocation(*p)) )
    {
        return p;
    }else{
        return NULL;
    }
}

template<class _Locateable,int _HowAllocated,template <class> class _Allocator >
ListNode<_Locateable> *LocateableLinkedList<_Locateable,_HowAllocated,_Allocator>::findFirstLen(ListNode<_Locateable>* startNode,size_t len)
{
    if(!startNode||len==0)return NULL;
    ListNode<_Locateable>* p=startNode;
    _Locateable tloc(start,len);
    SourceLocator<_Locateable,Locator::IGNORE,Locator::EQUAL,Locator::IGNORE> equLocator(&loc);
    SourceLocator<_Locateable,Locator::IGNORE,Locator::BIGGER,Locator::IGNORE> biggerLocator(&loc);
    while(p && !equLocator.tellLocation(*p) && !biggerLocator.tellLocation(*p))
    {
        p=LocateableLinkedList<_Locateable,_HowAllocated,_Allocator>::nextAllocable(p);
    }
    return p;
}

template<class _Locateable,int _HowAllocated,template <class> class _Allocator >
ListNode<_Locateable> *LocateableLinkedList<_Locateable,_HowAllocated,_Allocator>::findFirstStart(ListNode<_Locateable>* startNode,size_t start)
{
    if(!startNode||len==0)return NULL;
    ListNode<_Locateable>* p=LocateableLinkedList<_Locateable,_HowAllocated,_Allocator>::findFirstStartForInsert(startNode,start);
    SourceLocator<_Locateable,Locator::EQUAL,Locator::IGNORE,Locator::IGNORE> equLocator(&loc);
    if(p && (equLocator.tellLocation(*p) ))
    {
        return p;
    }else{
        return NULL;
    }
}
template<class _Locateable,int _HowAllocated,template <class> class _Allocator >
ListNode<_Locateable> *LocateableLinkedList<_Locateable,_HowAllocated,_Allocator>::findFirstStartForInsert(ListNode<_Locateable> *startNode,size_t start)
{
    if(!startNode||len==0)return NULL;
    ListNode<_Locateable> *p=startNode,*last=startNode;
    _Locateable tloc(start,len);
    SourceLocator<_Locateable,Locator::LESS,Locator::IGNORE,Locator::IGNORE> lessLocator(&tloc);

    while(p && lessLocator.tellLocation(*p))
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
    return LocateableLinkedList<_Locateable,_HowAllocated,_Allocator>::nextAllocable(start,Int2Type<_HowAllocated>());
}


template<class _Locateable,int _HowAllocated,template <class> class _Allocator >
ListNode<_Locateable>* LocateableLinkedList<_Locateable,_HowAllocated,_Allocator>::nextAllocable(ListNode<_Locateable>* startNode,Int2Type<Locator::KEEP>)
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
ListNode<_Locateable>* LocateableLinkedList<_Locateable,_HowAllocated,_Allocator>::nextAllocable(ListNode<_Locateable>* startNode,Int2Type<Locator::DISCARD>)
{
    return startNoe==NULL?NULL:startNode->getNext();
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
TreeNode<T>* TreeNode<T>::setFather(TreeNode<T>* father) {
    this->father=father;
}

template<class T>
TreeNode<T>* TreeNode<T>::getSon() const{
	return son;
}

template<class T>
TreeNode<T>* TreeNode<T>::getDirectFather()const {//direct father
    return father;
}
template<class T>
  TreeNode<T>* TreeNode<T>::setSon(TreeNode<T>* son)
  {
  	this->son=son;
  }
template<class T>
TreeNode<T>* TreeNode<T>::getParent()const {//往previous一直遍历，直到是跟，然后返回跟的father
	TreeNode<T> *p=this;
	while(p->hasPrevious())
	{
		p=p->getPrevious();
	}
	return p->getDirectFather();
}

//===============class Tree

template<class T,template <class> class _Allocator>
Tree<T,_Allocator>::Tree(_Allocator<TreeNode<T> >* smm,TreeNode<T>* root):
smm(smm)
{
	this->root=root==NULL?smm->getNew():root;
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
        p = p->getNext();
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
 	root->setSon(head);
 }
