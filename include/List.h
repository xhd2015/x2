
#ifndef List_h__
#define List_h__

#include <def.h>

class SimpleMemoryNode{
public:
    AS_MACRO SimpleMemoryNode(int NO=-1);//done
 
    AS_MACRO int getNO();//done
    AS_MACRO void setNO(int NO);//done
    AS_MACRO int isFree();//done
    AS_MACRO void free();//done
    AS_MACRO void unfree();//done
    
    
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
*
*   This is a template for Allocator that will alloc out T
*/
template <class T>
class SimpleMemoryManager{
public:
    SimpleMemoryManager(size_t start,size_t limit,bool doInit=true);//done
    //~SimpleMemoryManager(); //the only way to free all list is a call to free
    
    T* getNew();//done
    void withdraw(T *t);//single free,done
    AS_MACRO bool isFull();//done
    AS_MACRO size_t getLen();//done
    AS_MACRO size_t getCurSize();//done
    AS_MACRO size_t getStart();//done
    AS_MACRO size_t getLimit();//done
protected:
    size_t start;
    size_t limit;
    
    T *data;
    size_t curSize,len;
    
    size_t lastIndex;
};

template<class T>
class ListNode{
public:
    ListNode(const T& data,ListNode<T>* next=NULL,ListNode<T>* previous=NULL);
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
*
*   Requires:
*      void _Allocator<T>::withdraw(T*);
*       T*  _Allocator<T>::getNew(size_t size);
*
*/
template<class T,template <class>class _Allocator >
class LinkedList{
public:
    LinkedList(  _Allocator<ListNode<T> > *smm);
    ~LinkedList();
    
    AS_MACRO ListNode<T>* getHead();//done
    AS_MACRO _Allocator<ListNode<T> > *getMemoryManager();//done


    AS_MACRO ListNode<T>*    getLast();//done
    ListNode<T>*    append(const T &t);//done
    ListNode<T>*    append(ListNode<T>* p);//done
    ListNode<T>*    appendHead(ListNode<T>* p);//done
    ListNode<T>*   appendHead(const T &t);//done
    ListNode<T>*    remove();//done
    ListNode<T>*    removeHead();//done
    void            remove(ListNode<T>* p);//done


    void freeNode(ListNode<T> * node);//done
    void free();//free this list,but not destruct,that means not including root & last              done
    void freeNext(T *t);//forward list free,begin with this                 done
    void freePrevious(T *t);//backward list free,begin with This            done
    

protected:
    _Allocator<ListNode<T> > *smm; //空间分配代理器

    /**
    *Designing them as pointer is the best choice I've ever made.
    */
    ListNode<T>* root;
    ListNode<T>* last; //next指向最后一个
    
    
};
/**
*It provides extra functions for location
*To use this LocateableLinkedList,you must extends your class with Locateable,as for the method,you do not have to provide but if it is invalid the compiler will 
*complain for that.
*
*   Require:
*       Locateable::getStart()
*                   setStart()
*                   getLimit()
*                   setLimit()
*       Locateable::isAllocable()
*                   setAllocable()
*/
//============for LinkedList<LinearSource>,there is some difference,you can invoke find/locate on this kind of list
/**
*   Extension or combination with template argument?
*       Extension will cause longer class name
*       template argument will interfer the orginal class
*/
template<class _Locateable,int _HowAllocated,template <class> class _Allocator >
class LocateableLinkedList:public LinkedList<Locateable,Allocator<Locateable> >
{
public:
    LocateableLinkedList( _Allocator<ListNode<_Locateable> > *smm );//done
    ~LocateableLinkedList();//done
    /**
    * What should they return?The location,or a near location that can be later used to insert a node?
    */
    static ListNode<_Locateable> *findFirstStartLen(ListNode<_Locateable>* startNode,size_t start,size_t len);//done
    static ListNode<_Locateable> *findFirstLen(ListNode<_Locateable>* startNode,size_t len);//done
    static ListNode<_Locateable> *findFirstStart(ListNode<_Locateable>* startNode,size_t start);//done
    /**
    * return the first node whose start equals with or is bigger that argument start.
    *  If there is no such node(e.g. the above returns NULL),then return the last one who is less.
    *  If the above two process get NULL,then return NULL,meaning the list is empty.
    */
    static ListNode<_Locateable> *findFirstStartForInsert(ListNode<_Locateable> *startNode,size_t start);//done


    /**
    * The two locateForDeleteXXX methods are deprecated because now we have _HowAllocated.
    */
    DEPRECATED static ListNode<_Locateable> *locateForDelete(ListNode<_Locateable>* startNode,size_t start,size_t len,bool allocable);//done
    DEPRECATED static ListNode<_Locateable>* locateForDeleteStart(ListNode<_Locateable>* startNode,size_t start,bool allocable);//done



    static ListNode<_Locateable>* nextAllocable(ListNode<_Locateable>* startNode);//done
protected:
    static ListNode<_Locateable>* nextAllocable(ListNode<_Locateable>* startNode,Int2Type<Locator::KEEP>);//done
    static ListNode<_Locateable>* nextAllocable(ListNode<_Locateable>* startNode,Int2Type<Locator::DISCARD>);//done
};


//===============TreeNode and Tree
//	uses "Tree.cpp"
template <class T>
class TreeNode:public ListNode<T>{
public:
    TreeNode(const T& data,TreeNode<T>* father=NULL,TreeNode<T>* son=NULL,TreeNode<T>* next=NULL,TreeNode<T>* previous=NULL);
    ~TreeNode();

    TreeNode<T>* setSon(TreeNode<T>* son);//done
    TreeNode<T>* setFather(TreeNode<T>* father);//done
    TreeNode<T>* getSon(); //done
    TreeNode<T>* getDirectFather();//direct father,done


    
    TreeNode<T>* getParent();//往previous一直遍历，直到是根，然后返回根的father,done
    
protected:
    TreeNode<T> *son,*father;
    
};

template <class T,template <class> class Allocator>
class Tree{
public:
    Tree(Allocator<TreeNode<T> > *smm);
    ~Tree();
    
    TreeNode<T> *getHead();//done
    Tree<T>     *setHead(TreeNode<T> *head);  //返回其自身,done
    void         free(TreeNode<T> *root);//将root自身和所有子节点都释放掉，== withdraw all nodes recursively  done

protected:
    Allocator<TreeNode<T> > *smm;
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

/*These can be used in SimpleMemoryManager*/
template<class T>
class SimpleListNode:public ListNode<T>,public SimpleMemoryNode{

};
template<class T>
class SimpleTreeNode:public TreeNode<T>,public SimpleMemoryNode{

};

//============函数宏区
//=========class : ListNode
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
template <class T,template <class> class _Allocator>
ListNode<T>* LinkedList<T,_Allocator<T> >::getHead()
{
    return root->getNext();
}
template<class T,template <class> class _Allocator>
ListNode<T>*  LinkedList<T,_Allocator<T> >::getLast()
{
    return last->getNext();
}
template <class T,template <class> class _Allocator>
_Allocator<ListNode<T> > *LinkedList<T,_Allocator<T> >::getMemoryManager()
{
    return smm;
}

//=====class: SimpleMemoryNode
SimpleMemoryNode::SimpleMemoryNode(int NO=-1):
NO(NO)
{

}
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

//=====class:SimpleMemoryManager
template<class T>
bool SimpleMemoryManager<T>::isFull()
{
    return this->curSize==this->len;
}
template<class T>
size_t SimpleMemoryManager<T>::getLen()
{
    return this->len;
}
template<class T>
size_t SimpleMemoryManager<T>::getCurSize()
{
    return this->curSize;
}
template<class T>
size_t SimpleMemoryManager<T>::getStart()
{
    return this->start;
}
template<class T>
size_t SimpleMemoryManager<T>::getLimit()
{
    return this->limit;
}///////////



#endif //List_h__
