
#include "List.h"

//==========实例化模板
//===========模板声明区
template class ListNode<int>;
template class LinkedList<int>;




template<class T>
ListNode<T>::ListNode(T data,ListNode<T>* next,ListNode<T>* previous):
data(data),next(next),previous(previous)
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

//===============class : LinkedList
template<class T>
LinkedList<T>::LinkedList():
root(ListNode<T>((T)0,NULL,NULL)),
last(ListNode<T>((T)0,&root,NULL)),
size(0)
{
}
template<class T>
LinkedList<T>::~LinkedList()
{
    
}
     
template<class T>
ListNode<T>*  LinkedList<T>::getLast()
{
    return last.getNext();
}
template<class T>
void   LinkedList<T>::append(ListNode<T>* last)
{
    ListNode<T>* rlast=getLast();
    rlast->setNext(last);
    if(rlast->hasNext())
    {
        last->setPrevious(rlast);
        this->last.setNext(last);
        size++;
    }
}
template <class T>
void LinkedList<T>::refresh()
{
    size=0;
    ListNode<T>* p=&root;
    while(p->hasNext())
    {
        p=p->getNext();
        size++;
    }
    this->last.setNext(p);
}
template<class T>
ListNode<T>*    LinkedList<T>::remove()
{
   ListNode<T>* plast=getLast();
   if(plast!=&root)
   {
       ListNode<T>* prev=plast->getPrevious();
       this->last.setNext(prev);
       prev->setNext(NULL);
       size--;
       return plast;
   }else{
       return NULL;
   }
   
}

