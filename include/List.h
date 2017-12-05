
#ifndef List_h__
#define List_h__

#include <def.h>
#include <loki/Int2Type.h>
#include <Locator.h>
#include <libx2.h>
#include <conceptual/Serialize.h>

//可以当做基本类型来处理
/**
 *  is_pod<SimpleMemoryNode> == true.
 */
class SimpleMemoryNode:public SerializationInterface{
public:
    AS_MACRO SimpleMemoryNode(bool NO=false);//done
    AS_MACRO bool isAlloced();
    AS_MACRO void setAlloced(bool alloced);

    template <class __EnvTransfer>
    AS_MACRO SerializerPtr<__EnvTransfer>& serialize(SerializerPtr<__EnvTransfer> &ptr)const
		{	return ptr << alloced;}
	template <class __EnvTransfer>
	AS_MACRO SerializerPtr<__EnvTransfer>& deserialize(SerializerPtr<__EnvTransfer> &ptr)
		{ return ptr >> alloced;}
	template <class __EnvTransfer>
	AS_MACRO constexpr size_t getSerializitionSize()
		{return __EnvTransfer::template sizeofHostType<decltype(alloced)>();}
private:
    /**
    *  alloced=true  		已分配
    *		   false		未分配
    */
    bool alloced;
};
/**
 * DEPRECATED 此类已经过时，请使用关联内存管理
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
*   实际上是std::allocator<T>的非标准实现，该类可以由AssociatedMemoryManager替代，因为该类对被管理对象进行了一次耦合，导致实现不“干净”
*/
template <class T>
class SimpleMemoryManager{
public:
    DEPRECATED SimpleMemoryManager()=default;//default constructor that has nothing
    //~SimpleMemoryManager(); //the only way to free all list is a call to free
public:
    // DEPRECATED 改善其设计
    /**
     * 将标记放到待存储结构的末尾
     *
     * 希望借此隐藏标记的细节，从而只需关心数据本身，而不需关心数据怎么被附加信息存储
     *
     * 这里必须注意一点：只能组合两个类，并且标记类应当放置在末尾。
     * 这种组合类使用限制：当你只使用T部分时，T的地址本身也是整个结构体的地址。这使指针可以正常运作
     */
	struct Freeable:public T,public SimpleMemoryNode{

	};
	typedef struct Freeable FullNode;
	typedef T DataPart;


	typedef void (*ERROR_HANDLER)(SimpleMemoryManager *smm,int errcode);
	enum{
		ERR_NO_ERROR=0,
		ERR_SPACE_IS_FULL,
		ERR_NODE_NOT_INTERNAL,//nullptr is treated not internal but also not external
		ERR_GENERAL /*an error not currently defined*/
	};/*when it receives an error,it will call the errhandle,after which it will continue normally,but if error condition is
	not cleared,it will repeatly call errhandle.That means the error is not correctly corrected.
	We  should define a max-repeating error , if the same error process repeated for times such like that,we should abort/destroy the process
	*/
public:
	/**
	 * @param start		起始地址
	 * @param limit		长度限制，注意这里的limit语义不同，它不是最后一个可以访问的字节，而是总得内存长度
	 * @param initSize  already used nodes
	 */
	DEPRECATED SimpleMemoryManager(size_t start,size_t limit,bool doInit=true,size_t initSize=0,ERROR_HANDLER errhandler=nullptr);//done
    
    /**
     * The following methods may throw exception/may call error handler,after which it executes normally
     *
     * @return 必须对返回的node实行初始化函数
     */
    T* getNew();//done
    FullNode *getNewNode();//done
    void withdraw(FullNode *t);//done
    void withdraw(T *t);//single free,done


    AS_MACRO bool isFull()const;//done
    AS_MACRO size_t getLen()const;//done
    AS_MACRO size_t getCurSize()const;//done
    AS_MACRO size_t getStart()const;//done
    AS_MACRO size_t getLimit()const;//done
    AS_MACRO static size_t getNodeSize();//done
    AS_MACRO ERROR_HANDLER getErrHandler();
    AS_MACRO void			setErrHandler(ERROR_HANDLER errhandle);
private:
    /**
     * 检查节点是否在范围内
     */
    AS_MACRO bool	checkIsInternal(FullNode *t);
    size_t start;
    size_t limit;
    
    Freeable *data;
    size_t curSize,len;
    
    size_t lastIndex;
    ERROR_HANDLER errhandle;
};

//===ListNode的定义
template<class T>
class ListNode:public SerializationInterface
{
public:
	using This = ListNode<T>;
	using __ListNode = This;
public:
    ListNode(const T& data,__ListNode* next=nullptr,__ListNode* previous=nullptr);
    ListNode(const __ListNode &)=default;
    __ListNode & operator=(const __ListNode &)=default;
    ~ListNode();

    AS_MACRO const T& getData()const;
    AS_MACRO T& getData();
    AS_MACRO void setData(const T& data);
    AS_MACRO __ListNode* getNext()const;
    AS_MACRO __ListNode* getPrevious()const;
    AS_MACRO void setNext(__ListNode* next);
    AS_MACRO void  setPrevious(__ListNode* previous);
    __ListNode* removeNext();
    __ListNode* removePrevious();
    void    insertNext(__ListNode* next);
    void    insertPrevious(__ListNode* previous);
    AS_MACRO int  hasNext()const;
    AS_MACRO int  hasPrevious()const;//done
    /**
     * @new method since 2017-03-18 21:23:10
     */
    void		adjustOffset(ptrdiff_t diff);
    void		initTonullptr();


    __ListNode*    getLast()const;//done
    __ListNode*    getFirst()const;//done
    DEPRECATED AS_MACRO static void adjustOffset(char **p,ptrdiff_t off);
    //指向构造函数的地址
    //用 new (void*p) 构造函数,俗称placement new

    /**
     * 由环境决定采用哪种序列化指针方案：
     * 		POLICY_PTR_VALUE,POLICY_PTR_OBJECT
     */
    template <class __EnvTransfer>
    AS_MACRO SerializerPtr<__EnvTransfer>& serialize(SerializerPtr<__EnvTransfer> &ptr)const;
	template <class __EnvTransfer>
	AS_MACRO SerializerPtr<__EnvTransfer>& deserialize(SerializerPtr<__EnvTransfer> &ptr);
	/**
	 * 要求 T类型也要支持序列化，提供方法getSerializitionSize()
	 */
	template <class __EnvTransfer>
	AS_MACRO size_t getSerializitionSize();
protected:
    T   data;//for storage
    __ListNode *next;
    __ListNode *previous;

};
//*****=========ListNode定义完毕

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
*
*
*/
/**
 * 一个链表实现
 * @param T 存储的类型
 * @param _Allocator 分配ListNode<T>的分配器
 */
template<class T,template <class> class _Allocator>
class LinkedList{
public:
	using This = LinkedList<T,_Allocator>;
	using __LinkedList = This;
	using __ListNode = ListNode<T>;
	using __Allocator = _Allocator<__ListNode>;
public:
	LinkedList()=default;

public:
    LinkedList(  __Allocator *smm);
    LinkedList(const __LinkedList&)=default;
    __LinkedList & operator=(const __LinkedList&)=default;
    ~LinkedList();
    
    AS_MACRO __ListNode* getHead()const;//done
    AS_MACRO _Allocator<__ListNode > *getMemoryManager()const;//done


    AS_MACRO __ListNode*    getLast()const;//done
    __ListNode*    append(const T &t);//done
    __ListNode*    append(__ListNode* p);//done
    __ListNode*    appendHead(__ListNode* p);//done
    __ListNode*    appendHead(const T &t);//done
    __ListNode*    remove();//done
    __ListNode*    removeHead();//done
    void            remove(__ListNode* p);//done
    void			insertNext(__ListNode* where,__ListNode* p);//done
    void			insertPrevious(__ListNode* where,__ListNode* p);//done
    size_t 			getSize()const;//done
    AS_MACRO 		bool			isEmpty()const;


    void freeNode(__ListNode * node);//done
    void free();//free this list,(equals to destruct) that means free all,then set root&last as nullptr.   done
    void freeNext(__ListNode *t);//forward list free,begin with this                 done
    void freePrevious(__ListNode *t);//backward list free,begin with This            done
    

protected:
    _Allocator<__ListNode > *smm; //空间分配代理器

    /**
    *Designing them as pointer is the best choice I've ever made.
    */
    __ListNode* root;
    __ListNode* last; //next指向最后一个
    
    
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
*   @param _Locateable  具有start,limit的对象
*   @param _HowAllocated 分配策略：丢弃或者保留
*   @param _Allocator	分配器
*/
template<class _Locateable,int _HowAllocated,
		template <class> class _Allocator>
class LocateableLinkedList:public LinkedList<_Locateable,_Allocator>
{
public:
	using This =  LocateableLinkedList<_Locateable,_HowAllocated,_Allocator>;
	using Super = LinkedList<_Locateable,_Allocator>;
	using __LocateableLinkedList = This;
	using __LinkedList = Super;
	using __ListNode = typename Super::__ListNode;
	using __Allocator = _Allocator<__ListNode>;
	using __SizeType = size_t;
public:
	 LocateableLinkedList()=default;//done
public:
	/**
	 * @param smm   一个能否分配器ListNode<_Locateable>类型的分配器
	 */
    LocateableLinkedList( __Allocator *smm );//done
    ~LocateableLinkedList();//done
    /**
    * What should they return?The location,or a near location that can be later used to insert a node?
    */
    /**
     * 找到第一个满足要求start相等,len
     * @param startNode 查找的节点
     * @param start		开始地址
     * @param len		长度
     */
    static __ListNode *findFirstStartLen(__ListNode* startNode,__SizeType start,__SizeType len);//done
    static __ListNode *findFirstLen(__ListNode* startNode,__SizeType len);//done
    static __ListNode *findFirstStart(__ListNode* startNode,__SizeType start);//done
    /**
    * return the first node whose start equals with or is bigger that argument start.
    *  If there is no such node(e.g. the above returns nullptr),then return the last one who is less.
    *  If the above two process get nullptr,then return nullptr,meaning the list is empty.
    */
    static __ListNode *findFirstStartForInsert(__ListNode *startNode,__SizeType start);//done


    /**
    * The two locateForDeleteXXX methods are deprecated because now we have _HowAllocated.
    */
    DEPRECATED static __ListNode *locateForDelete(__ListNode* startNode,__SizeType start,__SizeType len,bool allocable);//done
    DEPRECATED static __ListNode* locateForDeleteStart(__ListNode* startNode,__SizeType start,bool allocable);//done



    static __ListNode* nextAllocable(__ListNode* startNode);//done
protected:
    static __ListNode* nextAllocable(__ListNode* startNode,Int2Type<Locator<_Locateable>::KEEP>);//done
    static __ListNode* nextAllocable(__ListNode* startNode,Int2Type<Locator<_Locateable>::DISCARD>);//done
};


//===============class TreeNode
template <class T>
class TreeNode:public ListNode<T>{
public:
	using This = TreeNode<T>;
	using Super = ListNode<T>;
	using __ListNode = Super;
	using __TreeNode = This;
public:
	TreeNode()=default;
	TreeNode(const __TreeNode&)=default;
	__TreeNode & operator=(const __TreeNode&)=default;


    TreeNode(const T& data,__TreeNode* father=nullptr,__TreeNode* son=nullptr,__TreeNode* next=nullptr,__TreeNode* previous=nullptr);
    ~TreeNode();

    AS_MACRO __TreeNode* setSon(__TreeNode* son);//done
    AS_MACRO __TreeNode* setFather(__TreeNode* father);//done

//#if defined(CODE64)
//    __TreeNode* getSon()const;
//#else
    AS_MACRO __TreeNode* getSon()const; //done
//#endif
    AS_MACRO __TreeNode* getNext()const;
    AS_MACRO __TreeNode* getPrevious()const;

    AS_MACRO __TreeNode* getDirectFather()const;//direct father,done
    		void		addSon(__TreeNode* son);
    AS_MACRO bool		hasSon()const;
    AS_MACRO bool 		hasFather()const;

    void		insertSon(__TreeNode* son);
    void		insertFather(__TreeNode* father);
    __TreeNode*	removeSon();
	__TreeNode*	removeFather();
	void 			adjustOffset(ptrdiff_t diff);
	void			initTonullptr();


    __TreeNode* getParent()const;//往previous一直遍历，直到是根，然后返回根的father,done

    template <class __EnvTransfer>
    AS_MACRO SerializerPtr<__EnvTransfer>& serialize(SerializerPtr<__EnvTransfer> &ptr)const;
	template <class __EnvTransfer>
	AS_MACRO SerializerPtr<__EnvTransfer>& deserialize(SerializerPtr<__EnvTransfer> &ptr);
	/**
	 * 要求 T类型也要支持序列化，提供方法getSerializitionSize()
	 */
	template <class __EnvTransfer>
	AS_MACRO size_t getSerializitionSize();

protected:

    __TreeNode *son;
    __TreeNode *father;

};


//============class Tree
/**
 * 树的结构：  root
 * 			head
 * 			...
 * 	树节点是TreeNode，意味着允许其往四个方向扩展。需要注意的一点是，树的root节点为冗余节点，这是为了支持对head节点的删除操作。root节点永不删除。
 *	树的所占用的空间仅仅包含两个指针：root指针，smm指针
 *
 *	@param T			节点存储的数据类型
 *	@param _Allocator  分配TreeNode的分配器类型
 */
template <class T,template <class> class _Allocator>
class Tree{
public:
	using This = Tree<T,_Allocator>;
	using __Tree = This;
	using __TreeNode=TreeNode<T>;
	using __Allocator = _Allocator<__TreeNode>;
public:
//	Tree()=default;
	Tree();
public:
    Tree(__Allocator *smm,__TreeNode* root=nullptr);//If give root=nullptr,then assign root by smm,else by root.
    Tree(const __Tree & )=default;
    __Tree &operator=(const __Tree & )=default;

    ~Tree();
    
    AS_MACRO __TreeNode *getHead()const;//done
    AS_MACRO void 		setHead(__TreeNode *head);  //返回其自身,done
    AS_MACRO void		addRoot(__TreeNode* node);
    AS_MACRO bool		isEmpty()const;
    AS_MACRO	__Allocator*	getSmm()const;
    void         free(__TreeNode *root);//将root自身和所有子节点都释放掉，== withdraw all nodes recursively  done

#if defined(CODE32)
    void		dumpInfo(Printer* p)const;
#endif
protected:
    __Allocator *smm;
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
    __TreeNode *root;//有唯一的son，此节点不用于存储。root->son = head，此节点为头节点。
    
};

/*These can be used in SimpleMemoryManager*/
//template<class T>
//class SimpleListNode:public ListNode<T>,public SimpleMemoryNode{
//
//};
//template<class T>
//class SimpleTreeNode:public __TreeNode,public SimpleMemoryNode{
//
//};


#endif //List_h__
