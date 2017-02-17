
#ifndef List_h__
#define List_h__

#include "def.h"

class SimpleMemoryNode{
public:
    SimpleMemoryNode(int NO=-1);
    ~SimpleMemoryNode();

    AS_MACRO int getNO();
    AS_MACRO void setNO(int NO);
    AS_MACRO int isFree();
    AS_MACRO void free();
    AS_MACRO void unfree();
    
    
protected:
    /**
    *NO=-1,then not using
    */
    int NO;
};

/**
*此管理器管理一个连续的区域，然后每次分配固定大小的内存
*为链表等结构提供支持
*
* usage:
*       SimpleMemoryManager<ListNode<int>> smm(0,20*512);
*       ListNode<int>& p=smm.get();
*                       smm.withdraw(p);
*   此实例化类型必须从可管理的对象衍生 T extends SimpleMemoryNode==TRUE
*   但是由于T的size未知，所以必须采用模板辅以继承的方法
*
*   注意，此管理器不能管理int等类型，除了继承自SimpleMemoryNode的class类型，他别无他能
*/
template <class T>
class SimpleMemoryManager{
public:
    SimpleMemoryManager(int start,unsigned int limit);
    ~SimpleMemoryManager();
    
    T* getNew();
    void withdraw(T *t);
    AS_MACRO int isFull();
    AS_MACRO unsigned int getLen();
    AS_MACRO unsigned int getCurSize();
    AS_MACRO int getStart();
    AS_MACRO unsigned int getLimit();
protected:
    int start;
    unsigned int limit;
    
    T *data;
    unsigned int curSize,len;
    
    unsigned int lastIndex;
    
    


};

template<class T>
class ListNode : public SimpleMemoryNode{
public:
    ListNode(T data,ListNode<T>* next,ListNode<T>* previous=NULL);
    ~ListNode();
    
    
    AS_MACRO const T& getData();
    AS_MACRO void setData(const T& data);
    AS_MACRO ListNode<T>* getNext();
    AS_MACRO ListNode<T>* getPrevious();
    AS_MACRO void setNext(ListNode<T>* next);
    AS_MACRO void  setPrevious(ListNode<T>* previous);
    ListNode<T>* removeNext();
    ListNode<T>* removePrevious();
    void    insertNext(ListNode<T>* next);
    void    insertPrevious(ListNode<T>* previous);
    AS_MACRO int  hasNext();
    AS_MACRO int  hasPrevious();
protected:
    T   data;//for storage
    ListNode<T> *next,*previous;
    
};

template<class T>
class LinkedList{
public:
    LinkedList();
    ~LinkedList();
    
    AS_MACRO ListNode<T>* getFirst();
    AS_MACRO void setFirst(ListNode<T>* first);
    ListNode<T>* getLast();
    void    append(ListNode<T>* last);
    ListNode<T>*    remove();
    void refresh();//如果从外部改变了数据，就要在此处刷新
    
    AS_MACRO unsigned int getSize();

protected:
    ListNode<T> root;
    ListNode<T> last; //next指向最后一个
    unsigned int size;
    
    
};

//============函数宏区
template<class T>
ListNode<T>* ListNode<T>::getNext()
{
    return next;
}

template<class T>
ListNode<T>* ListNode<T>::getPrevious()
{
    return previous;
}
template<class T>
void ListNode<T>::setNext(ListNode<T>* next)
{
    this->next = next;
}

template<class T>
void  ListNode<T>::setPrevious(ListNode<T>* previous)
{
    this->previous = previous;
}
template<class T>
int  ListNode<T>::hasPrevious()
{
    return (this->previous!=NULL);
}
template<class T>
int  ListNode<T>::hasNext()
{
    return (this->next!=NULL);
}

template<class T>
const T& ListNode<T>::getData()
{
    return data;
}
template<class T>
void ListNode<T>::setData(const T& data)
{
    this->data=data;
}
//class:LinkedList
template<class T>
ListNode<T>* LinkedList<T>::getFirst()
{
    return root.getNext();
}

template<class T>
void LinkedList<T>::setFirst(ListNode<T>* first)
{
    root.setNext(first);
}
template<class T>
unsigned int LinkedList<T>::getSize()
{
    return size;
}

//                              class: SimpleMemoryNode
int SimpleMemoryNode::getNO()
{
    return this->NO;
}
int SimpleMemoryNode::isFree()
{
    return this->NO==-1;
}
void SimpleMemoryNode::free()
{
    this->NO=-1;
}
void SimpleMemoryNode::unfree()
{
    this->NO=0;
}
void SimpleMemoryNode::setNO(int NO)
{
    this->NO = NO;
}

//                              class:SimpleMemoryManager
template<class T>
int SimpleMemoryManager<T>::isFull()
{
    return this->curSize==this->len;
}
template<class T>
unsigned int SimpleMemoryManager<T>::getLen()
{
    return this->len;
}
template<class T>
unsigned int SimpleMemoryManager<T>::getCurSize()
{
    return this->curSize;
}
template<class T>
int SimpleMemoryManager<T>::getStart()
{
    return this->start;
}
template<class T>
unsigned int SimpleMemoryManager<T>::getLimit()
{
    return this->limit;
}


#endif //List_h__