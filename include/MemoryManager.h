#ifndef MemoryManager_h
#define MemoryManager_h

#include <List.h>
#include <Locator.h>
#include <def.h>
#include <conceptual/Serialize.h>
//#include <Kernel.h>

#if defined(CODE32)
//new & delete
AS_MACRO void*	operator new(size_t size) throw() {return nullptr;}
AS_MACRO void	operator delete(void *p){}

//全局方法: placement new和placement delete
// Default placement versions of operator new.
AS_MACRO void* operator new(size_t, void* __p){ return __p; };
AS_MACRO void* operator new[](size_t, void* __p){ return __p; };

// Default placement versions of operator delete.
AS_MACRO void operator delete  (void*, void*){};
AS_MACRO void operator delete[](void*, void*){};


#elif defined(CODE64)
		#include <new>
		#include <cstdio>
#endif



//===class LinearSourceDescriptor
/**
*   This is simple enough,and should not  be modified any longer.
*
*/
class LinearSourceDescriptor:public SerializationInterface
{
public:
	//==这是唯一的不同
	using __SizeType = size_t;
	//=========
	using This = LinearSourceDescriptor;
	using __LinearSourceDescriptor=This;

public:
	AS_MACRO LinearSourceDescriptor()=default;
public:
    AS_MACRO LinearSourceDescriptor(__SizeType start,__SizeType limit); //done

    AS_MACRO ~LinearSourceDescriptor();//done
    AS_MACRO __SizeType getStart() const ;//done
    AS_MACRO __SizeType getLimit() const ;//done
    AS_MACRO bool isAllocable() const;//done,always return true;
    AS_MACRO void setStart(__SizeType start);//done
    AS_MACRO void setLimit(__SizeType limit);//done
    AS_MACRO bool contains(const LinearSourceDescriptor& b)const;//done
    AS_MACRO bool contains(__SizeType start,__SizeType limit)const;//done
    /**
    * 逻辑相等而非全等
    */
    AS_MACRO	bool operator==(const __LinearSourceDescriptor& b)const;//done
    AS_MACRO    bool operator!=(const __LinearSourceDescriptor& b)const;//done

    template <class __EnvTransfer>
    AS_MACRO SerializerPtr<__EnvTransfer>& serialize(SerializerPtr<__EnvTransfer> &ptr)const;
	template <class __EnvTransfer>
	AS_MACRO SerializerPtr<__EnvTransfer>& deserialize(SerializerPtr<__EnvTransfer> &ptr);
	template <class __EnvTransfer>
	AS_MACRO static constexpr size_t getSerializitionSize();
protected:
    /**
     * 描述对象的起始地址
     */
    __SizeType start {0} ;
    /**
     * 描述对象的所占用的长度
     */
    __SizeType limit {0} ;
};

//====class MemoryDescriptor
class MemoryDescriptor:public LinearSourceDescriptor{
public:
	using This = MemoryDescriptor;
	using Super  = LinearSourceDescriptor;
	using __LinearSourceDescriptor  = Super;
	using __SizeType = size_t;
	using __MemoryDescriptor = This;

    AS_MACRO MemoryDescriptor(__SizeType start,__SizeType limit,bool allocable=true);//done

    AS_MACRO ~MemoryDescriptor();//done
    AS_MACRO bool isAllocable()const; //此方法仅对同层以及上层的节点有意义  done
    AS_MACRO void setAllocable(bool allocable);//这是指是否用于父类的分配，还是用于自己的分配  done


    AS_MACRO bool operator==(const __MemoryDescriptor& b)const;//done
    AS_MACRO bool operator!=(const __MemoryDescriptor& b)const;//done
    //const static MemoryDescriptor nullptr_DESCRIPTOR;
protected:
    bool allocable;
};


/**
*   What this manager manages must provide a way to get start and limit.
*       There are two types of LinearSourceManager
*       1.All nodes inside are equal to each other .
*           If the allocated nodes have specific use,they are different from each other
*       2.
*   It does not assume the managed node is a subclass of a certain class or not.It just assume it provides some methods that is required by it.
*   Remember that if the structure of a class is not really necessary,do not use extend.
*   
*   _NodeAllocator must provide a function for condition that space is not enough
*
*/

template <class _LinearSourceDescriptor,template <class> class _NodeAllocator>
class LinearSourceManager:
		public
		LocateableLinkedList<_LinearSourceDescriptor,Locator<_LinearSourceDescriptor>::DISCARD,_NodeAllocator>
		{
public:
	using This = LinearSourceManager<_LinearSourceDescriptor,_NodeAllocator>;
	using __LinearSourceManager = This;
	using Super = LocateableLinkedList<_LinearSourceDescriptor,
			Locator<_LinearSourceDescriptor>::DISCARD,_NodeAllocator>;
    using __ListNode = typename Super::__ListNode;
    using NodeType = __ListNode;
    using __Allocator = _NodeAllocator<__ListNode>;
    using __LinkedList =  LinkedList<_LinearSourceDescriptor,_NodeAllocator>;
    using __SizeType = size_t;

	LinearSourceManager()=delete;
public:

	/**
	 * @param start应当不等于0，否则可能返回错误值
	 */
    LinearSourceManager(__Allocator &smm,__SizeType start,__SizeType size);//done
    LinearSourceManager(__Allocator &smm);//done
    ~LinearSourceManager();//done
    
    AS_MACRO const _LinearSourceDescriptor & getSpace()const;

    //These are for continuous memory allocation
    /**
     * @param start  从start处开始分配
     * @param size   分配size长度
     * @return 实际为__SizeType类型，返回start
     */
    void* mnew(__SizeType start,__SizeType size);//done
    /**
     * 分配size大小的空间
     * @return nullptr 意味着分配失败，其他成功
     */
    void* mnew(__SizeType size);//done
    /**
     *  TODO 去掉moveData，以realBase是否为nullptr判断
     *  增加或减少某个已分配指针的长度
     * @param start	已经分配的相对开始地址
     * @param size		分配的指针的长度
     * @param addOrReduce  增加还是减少
     * @param extsize  	调整的数量
     * @param realBase  用于和moveData配合使用，指定基指针，realBase+start就是数据的真实地址
     * @param moveData	是否移动数据
     *
     * @return nullptr 失败；其他则是寻常指针，可安全转换为__SizeType类型
     * 			如果成功，并且内存位置发生改变，原来已申请的数据自动失效
     * 			注意，返回的指针是基指针，而不是扩展指针
     */
    void* extend(__SizeType start,__SizeType size,bool addOrReduce,__SizeType extsize,char *realBase=nullptr,bool moveData=false);
    void mdelete(void* p,__SizeType size);//done

    /**
    * Currently,this manager does not support withdrawing a pointer without size,so this is deprecated or incomplete
    */
    DEPRECATED void mdelete(void *p);//done 

    /**
     * 分配不连续的扇区，以便其数量足够
     * @param size   待分配的数量（以管理的对象为单位）
     * @param list		返回的链表，初始必须为空
     * @param eachSectionExtraSize  每个分配的分区需要额外增加的容量
     * @return 如果空间足够，则一定保证分配成功，list指向分配的所有节点；否则失败，list保持不变
     */
    bool mnewLinked(__SizeType size,
    		__LinkedList &list,__SizeType eachSectionExtraSize=0);


    /**
     * 删除一个链表中的已经分配了的节点
     * 前置条件：list不为空，list中的节点之前已经分配过
     * @param list 节点列表
     */
    void				mdeleteLinked(__LinkedList &list);

	/**
	 * @param __EnvTransfer  提供从主机环境到目标环境的类型转换。参见EnvTransfer
	 *
	 */
	template <class __EnvTransfer>
		SerializerPtr<__EnvTransfer>& serialize(SerializerPtr<__EnvTransfer> &ptr)const
		{
			ptr << space;
			return Super::serialize(ptr);
		}
	/**
	 * @param __EnvTransfer 提供从目标环境到主机环境的类型转换
	 */
	template <class __EnvTransfer>
		SerializerPtr<__EnvTransfer>& deserialize(SerializerPtr<__EnvTransfer> &ptr)
		{
			ptr >> space;
			return Super::deserialize(ptr);
		}

	/**
	 * 提供序列化所需的空间大小.
	 * constexpr是可选的
	 */
	template <class __EnvTransfer>
		size_t getSerializitionSize()
	{
		return __EnvTransfer::template sizeofHostType<decltype(space)>() + Super::getSerializitionSize();
	}

protected:
    _LinearSourceDescriptor  allocOutNode(__ListNode *avlNode,__SizeType start,__SizeType len);//done
    /**
    * This method is not needed
    */
    DEPRECATED void withdrawNode(__ListNode *exactNode);//done
    

    bool checkRange(__SizeType start,__SizeType size);//done
    bool checkRange(__SizeType start);//done
    static bool checkPrevious(__ListNode *prev, __SizeType start);//done
    static bool checkNext(__ListNode* nxt, __SizeType start,__SizeType len);//done

protected:
    _LinearSourceDescriptor space;
};


/**
*类的实现：
*   大量使用链表这种结构
*   也使用树这种结构
*       资源的分配很适合使用树来描述
*
        MemoryManager mm(34*512,0xffff);
        MemoryManager mmIDT,mmGDT;
        mmIDT=mm.allocFree(0,50*8); //base作为零基址
        mmGDT=mm.allocFree(50*8,100*8);
*
*   从哪个管理器上分配的空间，就由哪个管理器负责，以体现层级关系
*       本质上，所有的管理器都是共用一棵树
*
*   change log：
*       2017-02-26 03:11:12： 分配的管理器只有在其上调用了alloc/new函数之后，才会向下复制自己并把alloc标志位置为1，在此基础上进行分配。下级的节点不关心上级的状态。因此添加“分配时复制”函数
*
*  @param _DescriptorAllocator  节点分配器，必须提供下面的方法
*  			T*	getNew()	用于分配
* 		 	void withdraw(T *) 用于回收
*
* 	对于某一层来说 ，    head						head存储原始的base,limit
* 						|
* 						|
* 					  son-->next-->next---> ....  此层就是所有的分配节点信息
*/

template <template <class> class _DescriptorAllocator>
class MemoryManager:public Tree<MemoryDescriptor,_DescriptorAllocator>{
public:
	using This = MemoryManager<_DescriptorAllocator>;
	using Super = Tree<MemoryDescriptor,_DescriptorAllocator>;

	using __SizeType = size_t;
	using __MemoryDescriptor=MemoryDescriptor;
	using __MemoryManager = This;
	using __TreeNode = typename Super::__TreeNode;
	using NodeType = __TreeNode;

	using SimpleAllocator = SimpleMemoryManager<NodeType>;
	using __Allocator = _DescriptorAllocator<__TreeNode>;

public:
	MemoryManager()=default;
    MemoryManager(__Allocator &smm);//done
    /**
     * 初始化一个带有待管理区间的内存管理器，区间范围是[start,start+len)
     * @param smm				节点分配器
     * @param start				开始地址
     * @param len				总长度
     * @param fatherAllocable	- // TODO 完善参数含义注释
     *
     */
    MemoryManager(__Allocator &smm,__SizeType start,__SizeType len,bool fatherAllocable=true);
    //以典型的内存描述建立管理器,但这不是唯一的初始化方式，因为开始和结束可以由内部节点指定，实际上开始和结束可以完全没有必要在初始化中指定


    /**
     * 建立初始管理器，并确定其中已经被分配的片段
     */
    MemoryManager(__Allocator &smm,__SizeType start,__SizeType len,
    		__SizeType usedList[][2],__SizeType usedLen,bool fatherAllocable=true);

    ~MemoryManager(); 
    
    //注意：不能在父类管理器中
    __MemoryManager allocFreeStart(__SizeType start,__SizeType len); //从父级管理器衍生,done
    __MemoryManager allocFree(__SizeType len);//done
    
    __TreeNode *copyOnAllocation(__TreeNode *head);//复制后的allocable标志位与父节点相反，这从根本上保证了内存的一致性 done
    
    //operator new and delete
    void* mnew(__SizeType start,__SizeType size);//done
    void* mnew(__SizeType size);//done
    void* mnewAlign(__SizeType size,__SizeType alignment);

    // TODO 验证、修改和完成下面的函数
    /*
     * if returned true,then the it worked
     * else not worked,nothing effected
     *
     * Note: if extsize = 0,do nothing
     * 		else if extsize < 0,trim the original allocated space,if extsize+size=0,then delete the original memory
     * 		else realloc new space.
     * Note: if realBase=0,it still works.The realBase is used to memory move.
     */
    void*  extend(__SizeType start,__SizeType size,int extsize,char *realBase=nullptr,bool moveData=false);//similar to realloc

    void mdelete(void* p,__SizeType size);//查找p开始的连续个大小，看是否能满足要求,使用locateForDelete,withdrawNode协同完成，done
    void mdelete(void *p);//done

    void withdrawToParent();                    //回收到父级管理器,当其撤销的时候，必须将子类移动到父类的子类中,done

    //=========getter & setter
    AS_MACRO __SizeType	getBase()const;
    AS_MACRO __SizeType getLimit()const;

    //===support for List
    static __TreeNode *findFirstStart(__TreeNode* loc,__SizeType start,__SizeType len);//done
    static __TreeNode *findFirstLen(__TreeNode* loc,__SizeType len);//done
    /**
     *
     */
    static __TreeNode*findFirstLenAlign(__TreeNode* loc, __SizeType len,__SizeType &extra,__SizeType alignment);
    static __TreeNode *locateForInsertation(__TreeNode* loc,__TreeNode  *son);
    static __TreeNode  *locateForDelete(__TreeNode * loc,__SizeType start,__SizeType len,bool allocable);//done
    static __TreeNode * locateForDeleteStart(__TreeNode * loc,__SizeType start,bool allocable);//done

    /**
     * 1	success
     * 0	failed
     */
    static int addToTree(__TreeNode  *root,__TreeNode  *son);
    static __TreeNode  *nextAllocable(__TreeNode  *node);//done


    int isnullptrManager();//done
    void setnullptr();//done

#if defined(CODE32)
    void dumpInfo(Printer *p)const;
#endif
protected:
    __TreeNode  * allocOutNode(__TreeNode  *avlNode,__SizeType start,__SizeType len);//done
    void withdrawNode(__TreeNode  *exactNode);//done
    /**
     * Note: extsize is __SizeType,it cannot be less than 0.if it is 0,then returned false.
     * if not found,return false
     * 	if found at original,return true
     * 	if found at somewhere not corrupted with the original,return true+1
     *
     * 	@return 根据查找的情况返回值0,1,2
     */
    u8_t findExtend(__SizeType start,__SizeType size,__SizeType extsize,__TreeNode  * &rtnode)const;
    
protected:
    //SimpleMemoryManager<__TreeNode  > *smm;  //the base class already has one

private:

};

//================High Level Memory Allocation====================

/**
 * Just a wrapper of MemoryManager.It directly interact with theKernel,and cast whatever it returns
 */
template <class T>
class HighLevelSimpleMemoryManager{


};


/***************CLASS DEFINITION END***********************/



#endif //Memory_h__
