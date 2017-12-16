
#ifndef List_h__
#define List_h__

#include <def.h>
#include <conceptual/loki/Int2Type.h>
#include <Locator.h>
#include <libx2.h>
#include <conceptual/Serialize.h>
#include <conceptual/ExtFunctional.h>

//可以当做基本类型来处理
/**
 *  is_pod<SimpleMemoryNode> == true.
 */
class SimpleMemoryNode:public SerializationInterface{
public:
    AS_MACRO SimpleMemoryNode(bool alloced=false);//done
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
    void withdraw(FullNode *_t);//done
    // 不正确的实现
    DEPRECATED void withdraw(T *t);//single free,done


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
	ListNode();
	/**
	 * @brief 初始化一个空的TreeNode
	 * 空的TreeNode是允许存在的，因此节点的目的其一是存储数据信息，其二是存储链接信息。可以允许只存储链接信息，比如作为链表的头部。
	 */
    ListNode(const T& data,__ListNode* next=nullptr,__ListNode* previous=nullptr);
    template <typename ... Args> // construct T from Args
    ListNode(__ListNode *next,__ListNode *previous,Args&&...args);
    ListNode(const __ListNode &)=default;
    __ListNode & operator=(const __ListNode &)=default;
    ~ListNode();

    // UNTESTED
    /**
     * @brief 将ListNode<Apple*>&转换成ListNode<Fruit*>&
     * 前置条件： T,__PTDerived必须是指针类型且具有继承关系
     */
    template <class __PTDerived>
    operator ListNode<__PTDerived>&()
	{
    	return basePointerCast<ListNode,__PTDerived,T>(*this);
	}
    template <class __PTDerived>
    operator const ListNode<__PTDerived>&()const
	{
    	return basePointerCast<ListNode,__PTDerived,T>(*this); // 将ListNode<Apple*>&转换成ListNode<Fruit*>&
	}


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
    void		initToNull();


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
*  类的不变式：
*   初始化时：
*  	初始化后：
*
*/
/**
 * 一个链表实现
 * @param T 存储的类型
 * @param _Allocator 分配ListNode<T>的分配器
 */
template<class T,template <class> class _Allocator>
class LinkedList : public SerializationInterface
{
public:
	using This = LinkedList<T,_Allocator>;
	using __LinkedList = This;
	using __ListNode = ListNode<T>;
	using __Allocator = _Allocator<__ListNode>;
public:
	//初始化必须指定引用smm,否则后面的工作不能正常进行
	// TODO 总结一条关于使用引用的合适时机， 引用显然是为了共享，
	// 引用具有以下性质：共享性  初始化后不可变性（除非使用"重构"， 即replacement new)
	LinkedList()=delete;

public:
	LinkedList(const std::shared_ptr<__Allocator>& smm);
	LinkedList(std::shared_ptr<__Allocator>&& smm);
    LinkedList( __Allocator *smm);// willbe DEPRECATED
private:
    void initRooLast();
public:
    LinkedList(const __LinkedList&)=default;
    __LinkedList & operator=(const __LinkedList&)=default;
    ~LinkedList();
    
    AS_MACRO __ListNode* getHead()const;//done
    DEPRECATED AS_MACRO _Allocator<__ListNode > &getMemoryManager()const;//done


    AS_MACRO __ListNode*    getLast()const;//done
    __ListNode*    append(const T &t);//done
    template <class ... Args>
    This&	    append(Args &&...args);

    // TODO 修改返回值为This&
    /**
     * 同样可以在没有setHead的情况下调用
     */
    __ListNode*    append(__ListNode* p);//done
    /**
     * 在头部插入，可以在没有setHead的情况下调用
     */
    __ListNode*    appendHead(__ListNode* p);//done
    __ListNode*    appendHead(const T &t)=delete;//done
    /**
     * @param TArgs  仅仅用于构造T的参数，其他指针默认为nullptr
     */
    template <class ... TArgs>
    This&	    appendHead(TArgs &&...args);
    // UNTESTED 含义不明
     __ListNode*    remove();//done
    /**
     * 移除头部，但是保留头部之后的链接
     */
    __ListNode*    removeHead();//done
    /**
     * 移除头部后面所有的链表，清空root和last
     * @return 移除后的头部，形成一个链表
     */
    __ListNode*	   removeAllAfterHead();
    void            remove(__ListNode* p);//done
    void			insertNext(__ListNode* where,__ListNode* p);//done
    template <class ... Args>
    AS_MACRO void			insertNext(__ListNode *where,Args &&...args);
    void			insertPrevious(__ListNode* where,__ListNode* p);//done
    template <class ... Args>
    AS_MACRO void			insertPrevious(__ListNode *where,Args &&...args);
    size_t 			getSize()const;//done
    AS_MACRO 		bool			isEmpty()const;


    /**
     * @brief 返回一个空的node或者nullptr
     */
    template <class ... Args>
    AS_MACRO __ListNode*		newOneNode(Args &&...args)noexcept;
    /**
     * 仅仅初始化data部分，其他部分为nullptr
     */
    template <class ... Args>
    AS_MACRO __ListNode*		newOneNodeOnlyData(Args &&...args)noexcept;
    template <class ... Args>
    AS_MACRO __ListNode*		newOneNodeThrows(Args &&...args);
    template <class ... Args>
    AS_MACRO __ListNode*		newOneNodeOnlyDataThrows(Args &&...args);
   AS_MACRO void				freeOneNode(__ListNode *node);

    void freeNode(__ListNode * node);//done
    void free();//free this list,(equals to destruct) that means free all,then set root&last as nullptr.   done
    void freeNext(__ListNode *t);//forward list free,begin with this                 done
    void freePrevious(__ListNode *t);//backward list free,begin with This            done
    

    // smm不会被序列化，所以你必须自己指定smm的值，而root,last将会由smm分配
    // 在反序列化之前，你必须首先已经指定smm，因为涉及空间分配
	template <class __EnvTransfer>
		SerializerPtr<__EnvTransfer>& serialize(SerializerPtr<__EnvTransfer> &ptr)const
		{
			SerializerPtr<__EnvTransfer> ptrStart=ptr;
			size_t n=0;
			ptr << n; //写入0，后面会更正过来
			for(__ListNode *p=root->getNext();p;p=p->getNext(),++n)
						ptr << p->getData(); //仅仅写入数据
			ptrStart << n; //写入数目
			return ptr;
		}
	template <class __EnvTransfer>
		SerializerPtr<__EnvTransfer>& deserialize(SerializerPtr<__EnvTransfer> &ptr)
		{
			size_t n=0;
			ptr >> n;
			for(size_t i=0;i!=n;++i)
			{
				__ListNode *p=newOneNode();
				ptr >> p->getData();//写入数据
				this->append(p);
			}
			return ptr;
		}

	/**
	 * 提供序列化所需的空间大小.
	 * constexpr是可选的
	 */
	template <class __EnvTransfer>
		size_t getSerializitionSize()
	{
		return __EnvTransfer::template sizeofHostType<decltype(root->getData())>() * getSize();
	}
private:
	AS_MACRO void setIfNoLast(__ListNode * p);
private:
    std::shared_ptr<__Allocator> smm; //共享空间分配代理器

    // TODO 使用更简洁的设计：将last放到root的previous域
    /**
    *Designing them as pointer is the best choice I've ever made.
    */
    __ListNode* root; //root存在的意义不是
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
	 LocateableLinkedList()=delete;//done
public:
	using Super::LinkedList; // 构造方法使用父类的
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
	TreeNode();
	 template <typename ... Args> // construct T from Args
	TreeNode(__TreeNode* father,
			__TreeNode* son,
			__TreeNode* next,
			__TreeNode* previous,Args &&...args);
	TreeNode(const __TreeNode&)=default;
	__TreeNode & operator=(const __TreeNode&)=default;


    TreeNode(const T& data,
    		__TreeNode* father=nullptr,
			__TreeNode* son=nullptr,
			__TreeNode* next=nullptr,
			__TreeNode* previous=nullptr);
    ~TreeNode();
    /**
     * @brief 将TreeNode<Apple*>&转换成TreeNode<Fruit*>&
     */
    template <class __PTDerived>
    operator TreeNode<__PTDerived>&()
	{
    	return basePointerCast<TreeNode,__PTDerived,T>(*this);
	}
    template <class __PTDerived>
    operator const TreeNode<__PTDerived>&()const
	{
    	return basePointerCast<TreeNode,__PTDerived,T>(*this);
	}


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

    /**
     * NOTE 注意，这些方法要求给定的参数son/father只能是单个节点，不能含有任何其他附属节点
     * 前置条件：son->{next,previous,son,father} 全部为空
     */
    void		insertSon(__TreeNode* son);
    void		insertFather(__TreeNode* father);
    void		removeSon();
	void		removeFather();
	void 			adjustOffset(ptrdiff_t diff);
	void			initToNull();

	/**
	 * @brief 与节点按父子关系链接起来
	 * 前置条件： this->son=nullptr, node=nullptr else node->father=nullptr.
	 * 在恢复序列化节点时特别有用
	 */
	void		concateSon(__TreeNode *node);
	/**
	 * @brief 与节点按前后关系链接起来
	 * 前置条件：this->next=nullptr, node=nullptr else node->previous=nullptr.
	 */
	void		concateNext(__TreeNode *node);


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
 *	不变式：
 *		该类一旦初始化：root不为nullptr, smm有引用存在。 如果构造时违反，就抛出异常
 *		只能通过setHead, append,appendHead来初始化头部
 *	含状态的不变式：
 *		初始态：root不为nullptr
 *		被移动的状态：root为nullptr
 *		析构态：
 *
 *
 *	一般而言，希望该结构能够做出更强的限制条件：不暴露任何节点。
 *	满足更强的不变式：不能够直接依赖root直接创建一棵新的树。因为序列化能够完成得更好。
 *
 *	@param T			节点存储的数据类型
 *	@param _Allocator  分配TreeNode的分配器类型
 */
template <class T,template <class> class _Allocator>
class Tree : public SerializationInterface{
public:
	using This = Tree<T,_Allocator>;
	using __Tree = This;
	using __TreeNode=TreeNode<T>;
	using __Allocator = _Allocator<__TreeNode>;
public:
//	Tree()=default;
	Tree()=delete;
public:
	// 并非异常安全
	/**
	 * @brief 初始化树并分配root节点
	 * @param smm
	 * @param root  在有些情况下，root节点可以代表一棵已经分配好的树
	 */
//	template <template <class> class __SharedPtr>
//    explicit Tree(__SharedPtr<__Allocator>&& smm);//If give root=nullptr,then assign root by smm,else by root.
    explicit Tree(const std::shared_ptr<__Allocator>& smm);
    explicit Tree(std::shared_ptr<__Allocator> && smm);

	// TODO 允许下面的两条
    Tree(const __Tree & )=delete;
    __Tree &operator=(const __Tree & )=delete;

    // 移动构造，赋值
    Tree(__Tree && tree);
    __Tree operator=(__Tree && tree);
    /**
     * @brief 构造一棵使用相同的节点管理器的Tree
     */
    __Tree makeSmmSharedTree();

    ~Tree();
    
    AS_MACRO __TreeNode *getHead()const;//done
    AS_MACRO void 		setHead(__TreeNode *head);  //返回其自身,done
    template <typename ...Args>
    AS_MACRO void		setHead(Args&& ... args);
    AS_MACRO void		addRoot(__TreeNode* node);
    AS_MACRO bool		isEmpty()const;

    template <typename ...Args>
    AS_MACRO This& insertNext(Args&& ... args);
    template <typename ...Args>
    AS_MACRO This& insertPrevious(Args&& ... args);
    template <typename ...Args>
    AS_MACRO This& insertSon(Args&& ... args);
    template <typename ...Args>
    AS_MACRO This& insertFather( Args&& ... args);

    // walker
//	tree.startWalk();
//	tree.gotoNext();
//	tree.gotoPrevious();
//	tree.atNull();
//	tree.gotoFather();
//	tree.atHead();
//	tree.gotoSon();
//	tree.endWalk()
    This& startWalk()
    {
    	if(curNode!=nullptr)
    		HostEnv::systemAbort("in tree startWalk,there is unfinished walking", -2);
    	curNode = root->getSon();
    	return *this;
    }
    This& gotoNext() noexcept
	{
    	if(curNode->getNext())curNode=curNode->getNext();
    	return *this;
	}
    This& gotoPrevious()
    {
    	if(curNode->hasPrevious())curNode=curNode->getPrevious();
    	return *this;
    }
    This& gotoFather()
    {
    	if(curNode->hasFather() && curNode->getDirectFather()!=root)
    		curNode=curNode->getDirectFather();
    	return *this;
    }
    This& gotoSon()
    {
    	if(curNode->hasSon())
    		curNode = curNode->getSon();
    	return *this;
    }
    This& endWalk()
    {
    	curNode=nullptr;
    	return *this;
    }

    /**
     * 因为资源管理器现在集中到基类身上，且为private成员
     * 所以由基类对派生类进行资源管理
     */
    AS_MACRO void		freeOneNode(__TreeNode *node);
    /**
     * @brief 创建TreeNode，初始化为空
     * @returns 一个TreeNode或者nullptr
     */
    template <class ...Args>
    __TreeNode *		 newOneNode(Args&&...args) noexcept;
    template <class ...Args>
    __TreeNode *		 newOneNodeOnlyData(Args&&...args) noexcept;
    /**
     * @brief 创建一个TreeNode，如果为空抛出异常
     * @returns 非空TreeNode，并且已经初始化完毕
     */
    template <class ...Args>
    __TreeNode* 		newOneNodeThrows(Args&&...args);
    template <class ...Args>
    __TreeNode* 		newOneNodeOnlyDataThrows(Args&&...args);

    /**
     * @brief 将节点及其链接的子节点，相邻节点回收到管理器
     * @param node 递归调用freeAll(node->getSon()),freeAll(node->getNext()),然后释放node
     */
    void         freeAll(__TreeNode *node);//将root自身和所有子节点都释放掉，== withdraw all nodes recursively  done

    /**
     * 计算树中节点的个数
     */
    size_t		getSize()const;



    /**
     * 序列化方案概述： Tree的节点结构有自己的特殊性：
     * 			对节点node，如果son节点和next节点已经序列化完毕，则只需要记录son节点的个数，next节点的个数，然后将node节点数据序列化
     * 			则，node节点也序列化完毕。
     * 			可见具有递归的性质。
     * 	序列化每个节点占用的空间布局如下：[T data] [size_t n_son] [size_t n_next]
     * 	n_son/n_next:以son/next为头结点的树的序列化数目
     * 	此方案甚至比直接存储指针要节省两个域的空间。
     *
     */
private:
//    template <class __SerializerPtr>
//    static __SerializerPtr* ptrNewest;//为了防止递归压栈导致的空间开销，将与局部无关的指针提到该处。
    /**
     * 用状态机的观点看待下面的算法：1.正在序列化node  2.正在序列化node的son节点  3.正在序列化node的next节点
     */
    template <class __EnvTransfer>
    		size_t __serializeHelper(SerializerPtr<__EnvTransfer> &ptr,__TreeNode *node)const;
    template <class __EnvTransfer>
       		__TreeNode *	__deserializeHelper(SerializerPtr<__EnvTransfer> &ptr,size_t n);
public:

	template <class __EnvTransfer>
		SerializerPtr<__EnvTransfer>& serialize(SerializerPtr<__EnvTransfer> &ptr)const;
	template <class __EnvTransfer>
		SerializerPtr<__EnvTransfer>& deserialize(SerializerPtr<__EnvTransfer> &ptr);
	template <class __EnvTransfer>
		 size_t getSerializitionSize();
#if defined(CODE32)
    void		dumpInfo(Printer* p)const;
#elif defined(CODE64)
    void		dumpInfo(
    		std::function<void(const T& t)>   consumer,
			std::function<void()>   beforeSon,
			std::function<void()>   afterSon,
			std::function<void()>   beforeNext,
			std::function<void()>   afterNext,
			__TreeNode *node)const;
    void 		dumpInfo(std::function<void(const T& t)>   consumer,
    		std::function<void()>   beforeSon,
    		std::function<void()>   afterSon,
    		std::function<void()>   beforeNext,
    		std::function<void()>   afterNext
    )const;
#endif

private:
    std::shared_ptr<__Allocator> smm;
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
    
    /**
     * @brief Tree Walker Status
     */
    __TreeNode	*curNode;

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
