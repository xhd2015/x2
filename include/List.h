
#ifndef List_h__
#define List_h__

#include <def.h>
#include <loki/Int2Type.h>
#include <Locator.h>

class SimpleMemoryNode{
public:
    AS_MACRO SimpleMemoryNode(bool NO=false);//done
 
    AS_MACRO bool getNO();//done
    AS_MACRO void setNO(bool NO);//done
    AS_MACRO bool isFree();//done
    AS_MACRO void free();//done
    AS_MACRO void unfree();//done
    
    
protected:
    /**
    *NO=false,then not using
    */
    bool NO;
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
    SimpleMemoryManager()=default;//default constructor that has nothing
    //~SimpleMemoryManager(); //the only way to free all list is a call to free
public:
	struct Freeable:public T,public SimpleMemoryNode{

	};
	typedef struct Freeable Node;
	typedef void (*ERROR_HANDLER)(SimpleMemoryManager *smm,int errcode);
	enum{
		ERR_NO_ERROR=0,
		ERR_SPACE_IS_FULL,
		ERR_NODE_NOT_INTERNAL,//NULL is treated not internal but also not external
		ERR_GENERAL /*an error not currently defined*/
	};/*when it receives an error,it will call the errhandle,after which it will continue normally,but if error condition is
	not cleared,it will repeatly call errhandle.That means the error is not correctly corrected.
	We  should define a max-repeating error , if the same error process repeated for times such like that,we should abort/destroy the process
	*/
public:
    SimpleMemoryManager(size_t start,size_t limit,bool doInit=true,size_t initSize=0,ERROR_HANDLER errhandler=NULL);//done
    
    /**
     * The following methods may throw exception/may call error handler,after which it executes normally
     */
    T* getNew();//done
    Node *getNewNode();//done
    void withdraw(Node *t);//done
    void withdraw(T *t);//single free,done


    AS_MACRO bool isFull()const;//done
    AS_MACRO size_t getLen()const;//done
    AS_MACRO size_t getCurSize()const;//done
    AS_MACRO size_t getStart()const;//done
    AS_MACRO size_t getLimit()const;//done
    AS_MACRO static size_t getNodeSize();//done
    AS_MACRO ERROR_HANDLER getErrHandler();
    AS_MACRO void			setErrHandler(ERROR_HANDLER errhandle);
protected:
    AS_MACRO bool	checkIsInternal(Node *t);
    size_t start;
    size_t limit;
    
    Freeable *data;
    size_t curSize,len;
    
    size_t lastIndex;
    ERROR_HANDLER errhandle;
};

template<class T>
class ListNode{
public:
	typedef ListNode<T> This;
public:
    ListNode(const T& data,ListNode<T>* next=NULL,ListNode<T>* previous=NULL);
    ~ListNode();
    
    AS_MACRO const T& getData()const;
    AS_MACRO T& getData();
    AS_MACRO void setData(const T& data);
    AS_MACRO ListNode<T>* getNext()const;
    AS_MACRO ListNode<T>* getPrevious()const;
    AS_MACRO void setNext(ListNode<T>* next);
    AS_MACRO void  setPrevious(ListNode<T>* previous);
    ListNode<T>* removeNext();
    ListNode<T>* removePrevious();
    void    insertNext(ListNode<T>* next);
    void    insertPrevious(ListNode<T>* previous);
    AS_MACRO int  hasNext()const;
    AS_MACRO int  hasPrevious()const;//done
    /**
     * @new method since 2017-03-18 21:23:10
     */
    void		adjustOffset(ptrdiff_t diff);


    ListNode<T>*    getLast()const;//done
    ListNode<T>*    getFirst()const;//done
    DEPRECATED AS_MACRO static void adjustOffset(char **p,ptrdiff_t off);
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
template<class T,template <class> class _Allocator >
class LinkedList{
public:
	LinkedList()=default;
public:
    LinkedList(  _Allocator<ListNode<T> > *smm);
    ~LinkedList();
    
    AS_MACRO ListNode<T>* getHead()const;//done
    AS_MACRO _Allocator<ListNode<T> > *getMemoryManager()const;//done


    AS_MACRO ListNode<T>*    getLast()const;//done
    ListNode<T>*    append(const T &t);//done
    ListNode<T>*    append(ListNode<T>* p);//done
    ListNode<T>*    appendHead(ListNode<T>* p);//done
    ListNode<T>*    appendHead(const T &t);//done
    ListNode<T>*    remove();//done
    ListNode<T>*    removeHead();//done
    void            remove(ListNode<T>* p);//done
    void			insertNext(ListNode<T>* where,ListNode<T>* p);//done
    void			insertPrevious(ListNode<T>* where,ListNode<T>* p);//done
    size_t 			getSize()const;//done
    AS_MACRO 		bool			isEmpty()const;


    void freeNode(ListNode<T> * node);//done
    void free();//free this list,(equals to destruct) that means free all,then set root&last as NULL.   done
    void freeNext(ListNode<T> *t);//forward list free,begin with this                 done
    void freePrevious(ListNode<T> *t);//backward list free,begin with This            done
    

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
class LocateableLinkedList:public LinkedList<_Locateable,_Allocator >
{
public:
	 LocateableLinkedList()=default;//done
public:
	typedef LocateableLinkedList<_Locateable,_HowAllocated,_Allocator> This;
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
    static ListNode<_Locateable>* nextAllocable(ListNode<_Locateable>* startNode,Int2Type<Locator<_Locateable>::KEEP>);//done
    static ListNode<_Locateable>* nextAllocable(ListNode<_Locateable>* startNode,Int2Type<Locator<_Locateable>::DISCARD>);//done
};


//===============TreeNode and Tree
//	uses "Tree.cpp"
template <class T>
class TreeNode:public ListNode<T>{
public:
	typedef ListNode<T> Father;
public:
	TreeNode()=default;
    TreeNode(const T& data,TreeNode<T>* father=NULL,TreeNode<T>* son=NULL,TreeNode<T>* next=NULL,TreeNode<T>* previous=NULL);
    ~TreeNode();

    AS_MACRO TreeNode<T>* setSon(TreeNode<T>* son);//done
    AS_MACRO TreeNode<T>* setFather(TreeNode<T>* father);//done
    AS_MACRO TreeNode<T>* getSon()const; //done
    AS_MACRO TreeNode<T>* getDirectFather()const;//direct father,done
    		void		addSon(TreeNode<T>* son);
    AS_MACRO bool		hasSon()const;
    AS_MACRO bool 		hasFather()const;

    void		insertSon(TreeNode<T>* son);
    void		insertFather(TreeNode<T>* father);
    TreeNode<T>*	removeSon();
	TreeNode<T>*	removeFather();
	void 			adjustOffset(ptrdiff_t diff);


    TreeNode<T>* getParent()const;//往previous一直遍历，直到是根，然后返回根的father,done
    
protected:
    
    TreeNode<T> *son,*father;
    
};

//============class Tree
template <class T,template <class> class _Allocator>
class Tree{
public:
	Tree()=default;
public:
    Tree(_Allocator<TreeNode<T> > *smm,TreeNode<T>* root=NULL);//If give root=NULL,then assign root by smm,else by root.
    ~Tree();
    
    AS_MACRO TreeNode<T> *getHead()const;//done
    AS_MACRO void 		setHead(TreeNode<T> *head);  //返回其自身,done
    AS_MACRO void		addRoot(TreeNode<T>* node);
    AS_MACRO bool		isEmpty()const;
    AS_MACRO	_Allocator<TreeNode<T> >*	getSmm()const;
    void         free(TreeNode<T> *root);//将root自身和所有子节点都释放掉，== withdraw all nodes recursively  done

protected:
    _Allocator<TreeNode<T> > *smm;
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
//template<class T>
//class SimpleListNode:public ListNode<T>,public SimpleMemoryNode{
//
//};
//template<class T>
//class SimpleTreeNode:public TreeNode<T>,public SimpleMemoryNode{
//
//};

//============函数宏区
//=========class : ListNode
template<class T>
ListNode<T>* ListNode<T>::getNext()const
{
    return next;
}

template<class T>
ListNode<T>* ListNode<T>::getPrevious()const
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
int  ListNode<T>::hasPrevious()const
{
    return (this->previous!=NULL);
}
//template<class T>
//void ListNode<T>::adjustOffset(char **p,ptrdiff_t diff)
//{
//	if(p!=NULL && *p!=NULL)*p+=diff;
//}
template<class T>
int  ListNode<T>::hasNext()const
{
    return (this->next!=NULL);
}

template<class T>
const T& ListNode<T>::getData()const
{
    return data;
}
template<class T>
T& ListNode<T>::getData()
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
ListNode<T>* LinkedList<T,_Allocator >::getHead()const
{
    return root->getNext();
}
template<class T,template <class> class _Allocator>
ListNode<T>*  LinkedList<T,_Allocator>::getLast()const
{
    return last->getNext();
}
template <class T,template <class> class _Allocator>
bool			LinkedList<T,_Allocator>::isEmpty()const
{
	return this->getHead()==NULL;
}
template <class T,template <class> class _Allocator>
_Allocator<ListNode<T> > *LinkedList<T,_Allocator>::getMemoryManager()const
{
    return smm;
}

//=====class: SimpleMemoryNode
SimpleMemoryNode::SimpleMemoryNode(bool NO):
NO(NO)
{

}
bool SimpleMemoryNode::getNO()
{
    return this->NO;
}
bool SimpleMemoryNode::isFree()
{
    return this->NO==false;
}
void SimpleMemoryNode::free()
{
    this->NO=false;
}
void SimpleMemoryNode::unfree()
{
    this->NO=true;
}
void SimpleMemoryNode::setNO(bool NO)
{
    this->NO = NO;
}

//=====class:SimpleMemoryManager
template<class T>
bool SimpleMemoryManager<T>::isFull()const
{
    return this->curSize==this->len;
}
template<class T>
size_t SimpleMemoryManager<T>::getLen()const
{
    return this->len;
}
template<class T>
size_t SimpleMemoryManager<T>::getCurSize()const
{
    return this->curSize;
}
template<class T>
size_t SimpleMemoryManager<T>::getStart()const
{
    return this->start;
}
template<class T>
size_t SimpleMemoryManager<T>::getLimit()const
{
    return this->limit;
}    ///////////

template<class T>
size_t  SimpleMemoryManager<T>::getNodeSize()
{
	return sizeof(Node);
}

template<class T>
typename SimpleMemoryManager<T>::ERROR_HANDLER SimpleMemoryManager<T>::getErrHandler()
{
	return this->errhandle;
}
template<class T>
void			SimpleMemoryManager<T>::setErrHandler(SimpleMemoryManager<T>::ERROR_HANDLER errhandle)
{
	this->errhandle= errhandle;
}
template<class T>
bool			SimpleMemoryManager<T>::checkIsInternal(Node *t)
{
	return this->start <= (size_t)t && (size_t)t - (size_t)this->start <= this->limit ;
}
//===========class TreeNode

template<class T>
  TreeNode<T>* TreeNode<T>::setSon(TreeNode<T>* son)
  {
#if defined(CODE64)
	//printf("setSon is : %x \n",son);
#endif
  	this->son=son;
  }
template<class T>
TreeNode<T>* TreeNode<T>::setFather(TreeNode<T>* father) {
    this->father=father;
}

template<class T>
TreeNode<T>* TreeNode<T>::getSon() const{
#if defined(CODE64)
//	printf("gettSon \n");
#endif
	return son;
}

template<class T>
TreeNode<T>* TreeNode<T>::getDirectFather()const {//direct father
#if defined(CODE64)
//	printf("call direct,this is %x,father is %x\n",this,this->father);
#endif
    return father;
}

template<class T>
bool		 TreeNode<T>::hasSon()const
{
	return this->son!=NULL;
}
template<class T>
bool 		 TreeNode<T>::hasFather()const
{
	return this->father!=NULL;
}

//======class Tree
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
 	root->setSon(head);
#if defined(CODE64)
 	//printf("root->setSon : %x\n",root->getSon());
#endif
 }

template<class T,template <class> class _Allocator>
void		Tree<T,_Allocator>::addRoot(TreeNode<T>* node)
{
	this->root->addSon(node);
}
template<class T,template <class> class _Allocator>
bool		Tree<T,_Allocator>::isEmpty()const
{
	return !(this->root->hasSon());
}
template<class T,template <class> class _Allocator>
_Allocator<TreeNode<T> >*	Tree<T,_Allocator>::getSmm()const
{
	return this->smm;
}



#endif //List_h__
