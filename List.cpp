
#include <List.h>
#include <Memory.h>
#include <libx2.h>
#include <test.h>

//==========实例化模板
//===========模板声明区
template class ListNode<int>;
template class LinkedList<int>;
template class ListNode<MemoryDescriptor>;

template<class T>
ListNode<T>::ListNode(const T& data,ListNode<T>* next,ListNode<T>* previous):
data(data),
next(next),
previous(previous)
{
}
template<class T> //right
ListNode<T>* ListNode<T>::init(const T& data,ListNode<T>* next,ListNode<T>* previous)
{
    // Util::printStr("after \n");
    this->data = data;
    this->next = next;
    this->previous = previous;
    // Test::dumpMemoryData(this->data);
    // Util::printStr("init end.\n");
    return this;
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
ListNode<T>*   ListNode<T>::getLast()
{
    ListNode<T>* p=this;
    while(p->hasNext())
    {
        p=p->getNext();
    }
    return p;
}
template<class T>
ListNode<T>*    ListNode<T>::getFirst()
{
    ListNode<T> *p=this;
    while(p->hasPrevious())
    {
        p=p->getPrevious();
    }
    return p;
}

//===============class : LinkedList
template<class T>
LinkedList<T>::LinkedList(SimpleMemoryManager<ListNode<T> > *smm)
{
    init(smm);
}
template<class T>
LinkedList<T>* LinkedList<T>::init(SimpleMemoryManager<ListNode<T> > *smm)
{   
    this->size = 0;
    this->smm = smm;
    this->root= this->smm->getNew();
    this->last= this->smm->getNew();
    
    this->root->init((T)0,NULL,NULL);
    this->last->init((T)0,root,NULL);

}

template<class T>
LinkedList<T>::~LinkedList()
{
    
}
template<class T>
void LinkedList<T>::free()
{
    this->smm->withdraw(this->last);
    this->smm->freeNext(this->root);
    
}
template<class T>
ListNode<T>*  LinkedList<T>::getLast()
{
    return last->getNext();
}

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
template<class T>
ListNode<T>*   LinkedList<T>::append(const T& t)
{
    ListNode<T>* rlast=getLast(),
                *last=smm->getNew();
    last->init(t,rlast->getNext(),rlast);
    rlast->setNext(last);
    this->last->setNext(last);
    size++;

    return last;
}
template<class T>
ListNode<T>* LinkedList<T>::appendHead(const T& t)
{
    ListNode<T> *p=smm->getNew()->init(t,root->getNext(),root);
    root->setNext(p);
    return p;
}
template<class T>
ListNode<T>*    LinkedList<T>::remove()
{
   ListNode<T>* plast=getLast();
   if(plast!=root)
   {
       ListNode<T>* prev=plast->getPrevious();
       this->last->setNext(prev);
       prev->setNext(NULL);
       size--;
       return plast;
   }else{
       return NULL;
   }
   
}
template<class T>
ListNode<T>*    LinkedList<T>::removeHead()
{
    ListNode<T>* p=root->getNext();
    if(p->hasNext())
    {
        p->getNext()->setPrevious(root);
    }
    root->setNext(p->getNext());
    return p;
   
}


