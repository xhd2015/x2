
#ifndef List_h__
#define List_h__

#include <def.h>

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
    void withdraw(T *t);//single free
    void freeNext(T *t);//forward list free
    void freePrevious(T *t);//backward list free
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
    ListNode(const T& data,ListNode<T>* next=NULL,ListNode<T>* previous=NULL);
    ListNode<T>* init(const T& data,ListNode<T>* next=NULL,ListNode<T>* previous=NULL);//构造函数,这是这种初始化在堆中的类的统一要求
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
    AS_MACRO int  hasPrevious();//done
    ListNode<T>*    getLast();//done
    ListNode<T>*    getFirst();//done
    //指向构造函数的地址
    //用 new (void*p) 构造函数,俗称placement new
protected:
    T   data;//for storage
    ListNode<T> *next,*previous;
    
};

/**
*这个类内容是彻底位于FREE_HEAP上的/这样的类最好将其析构函数设为protected
*
*   但是如果想要copy一个链表，可以直接使用operator=
*   除了size
*/
template<class T>
class LinkedList{
public:
    LinkedList(  SimpleMemoryManager<ListNode<T> > *smm);
    LinkedList<T>* init(SimpleMemoryManager<ListNode<T> > *smm);
    ~LinkedList();
    
    AS_MACRO ListNode<T>* getFirst();
    ListNode<T>* getLast();
    ListNode<T>*    append(const T &t);
    ListNode<T>*   appendHead(const T &t);
    ListNode<T>*    remove();
    ListNode<T>*    removeHead();
    void refresh();//如果从外部改变了数据，就要在此处刷新
    
    AS_MACRO unsigned int getSize();
    
    void free();
    
    

protected:
    SimpleMemoryManager<ListNode<T> > *smm; //空间分配代理器
    ListNode<T>* root;
    ListNode<T>* last; //next指向最后一个
    unsigned int size;
    
    
};

//===============TreeNode and Tree
//	uses "Tree.cpp"
template <class T>
class TreeNode:public ListNode<T>{
public:
    TreeNode(const T& data,TreeNode<T>* father=NULL,TreeNode<T>* son=NULL,TreeNode<T>* next=NULL,TreeNode<T>* previous=NULL);
    TreeNode<T>* init(const T& data,TreeNode<T>* father=NULL,TreeNode<T>* son=NULL,TreeNode<T>* next=NULL,TreeNode<T>* previous=NULL);
    ~TreeNode();

    TreeNode<T>* setSon(TreeNode<T>* son);//done
    TreeNode<T>* setFather(TreeNode<T>* father);//done
    TreeNode<T>* getSon(); //done
    TreeNode<T>* getDirectFather();//direct father,done


    
    TreeNode<T>* getParent();//往previous一直遍历，直到是根，然后返回根的father,done
    
protected:
    TreeNode<T> *son,*father;
    
};

template <class T>
class Tree{
public:
    Tree(SimpleMemoryManager<TreeNode<T> > *smm);
    ~Tree();
    
    TreeNode<T> *getHead();//done
    Tree<T>     *setHead(TreeNode<T> *head);  //返回其自身,done
    void         free(TreeNode<T> *root);//将root自身和所有子节点都释放掉，== withdraw all nodes recursively  done

protected:
    SimpleMemoryManager<TreeNode<T> > *smm;
    // 0
    // 1 
    // 2
    // *
    // |
    // *->*->*
    // |  |  |
    // |  *  *
    // |
    // *->*->*
    //father 是最左边的节点的father
    TreeNode<T> *root;//有唯一的son，此节点不用于存储。root->son = head，此节点为头节点。
    
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
//=============class:LinkedList
template<class T>
ListNode<T>* LinkedList<T>::getFirst()
{
    return root->getNext();
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
}///////////



#endif //List_h__
