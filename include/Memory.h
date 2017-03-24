#ifndef MemoryManager_h
#define MemoryManager_h

#include <List.h>
#include <Locator.h>
#include <def.h>
//#include <Kernel.h>

#if defined(CODE32)
//new & delete
AS_MACRO void*	operator new(size_t size){return NULL;}
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
/**
*   This is simple enough,and should not  be modified any longer.
*/
class LinearSourceDescriptor{
public:
	AS_MACRO LinearSourceDescriptor();
public:
    AS_MACRO LinearSourceDescriptor(size_t start,size_t limit); //done
    AS_MACRO ~LinearSourceDescriptor();//done
    AS_MACRO size_t getStart() const ;//done
    AS_MACRO size_t getLimit() const ;//done
    AS_MACRO bool isAllocable() const;//done,always return true;
    AS_MACRO void setStart(size_t start);//done
    AS_MACRO void setLimit(size_t limit);//done
    AS_MACRO bool contains(const LinearSourceDescriptor& b)const;//done
    AS_MACRO bool contains(size_t start,size_t limit)const;//done
    /**
    * 逻辑相等而非全等
    */
    AS_MACRO	bool operator==(const LinearSourceDescriptor& b)const;//done
    AS_MACRO    bool operator!=(const LinearSourceDescriptor& b)const;//done
protected:
    size_t start;
    size_t limit;
};



class MemoryDescriptor:public LinearSourceDescriptor{
public:
    AS_MACRO MemoryDescriptor(size_t start,size_t limit,bool allocable=true);//done
    AS_MACRO ~MemoryDescriptor();//done
    AS_MACRO bool isAllocable()const; //此方法仅对同层以及上层的节点有意义  done
    AS_MACRO void setAllocable(bool allocable);//这是指是否用于父类的分配，还是用于自己的分配  done


    AS_MACRO bool operator==(const MemoryDescriptor& b)const;//done
    AS_MACRO bool operator!=(const MemoryDescriptor& b)const;//done
    //const static MemoryDescriptor NULL_DESCRIPTOR;
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
class LinearSourceManager:public LocateableLinkedList<_LinearSourceDescriptor,Locator<_LinearSourceDescriptor>::DISCARD,_NodeAllocator >{
public:
	typedef LinearSourceManager<_LinearSourceDescriptor,_NodeAllocator> This;
    typedef LocateableLinkedList<_LinearSourceDescriptor,Locator<_LinearSourceDescriptor>::DISCARD,_NodeAllocator > Father;
	typedef ListNode<_LinearSourceDescriptor> NodeType;
	LinearSourceManager();
public:
    LinearSourceManager(_NodeAllocator< ListNode<_LinearSourceDescriptor> >*smm,size_t start,size_t size);//done
    ~LinearSourceManager();//done
    
    AS_MACRO const _LinearSourceDescriptor & getSpace()const;

    //These are for continuous memory allocation
    void* mnew(size_t start,size_t size);//done
    void* mnew(size_t size);//done
    void* extend(size_t start,size_t size,int extsize,char *realBase=NULL,bool moveData=false);
    void mdelete(void* p,size_t size);//done

    /**
    * Currently,this manager does not support withdrawing a pointer without size,so this is deprecated or incomplete
    */
    DEPRECATED void mdelete(void *p);//done 

    //These are for linked memory allocation
    /**
     * The 'eachSectionExtraSize' is the extra size for each section.
     */
    bool mnewLinked(size_t size,LinkedList<LinearSourceDescriptor,_NodeAllocator> &list,size_t eachSectionExtraSize=0);//list must be empty
    void												mdeleteLinked(LinkedList<LinearSourceDescriptor,_NodeAllocator> &ist);


protected:
    _LinearSourceDescriptor  allocOutNode(ListNode<_LinearSourceDescriptor> *avlNode,size_t start,size_t len);//done
    /**
    * This method is not needed
    */
    DEPRECATED void withdrawNode(ListNode<_LinearSourceDescriptor> *exactNode);//done
    

    bool checkRange(size_t start,size_t size);//done
    bool checkRange(size_t start);//done
    static bool checkPrevious(ListNode<_LinearSourceDescriptor> *prev, size_t start);//done
    static bool checkNext(ListNode<_LinearSourceDescriptor>* nxt, size_t start,size_t len);//done

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
*/

template <template <class> class _DescriptorAllocator>
class MemoryManager:public Tree<MemoryDescriptor,_DescriptorAllocator>{
public:
	typedef MemoryManager<_DescriptorAllocator> This;
	typedef TreeNode<MemoryDescriptor>			NodeType;
public:
    MemoryManager(_DescriptorAllocator<TreeNode<MemoryDescriptor> > *smm);//done
    MemoryManager(_DescriptorAllocator<TreeNode<MemoryDescriptor> > *smm,size_t start,size_t len,bool fatherAllocable=1);
    //以典型的内存描述建立管理器,但这不是唯一的初始化方式，因为开始和结束可以由内部节点指定，实际上开始和结束可以完全没有必要在初始化中指定
    //done
    ~MemoryManager(); 
    
    //注意：不能在父类管理器中
    MemoryManager<_DescriptorAllocator> allocFreeStart(size_t start,size_t len); //从父级管理器衍生,done
    MemoryManager<_DescriptorAllocator> allocFree(size_t len);//done
    
    TreeNode<MemoryDescriptor> *copyOnAllocation(TreeNode<MemoryDescriptor> *head);//复制后的allocable标志位与父节点相反，这从根本上保证了内存的一致性 done
    
    //operator new and delete
    void* mnew(size_t start,size_t size);//done
    void* mnew(size_t size);//done
    void* mnewAlign(size_t size,size_t alignment);
    /*
     * if returned true,then the it worked
     * else not worked,nothing effected
     *
     * Note: if extsize = 0,do nothing
     * 		else if extsize < 0,trim the original allocated space,if extsize+size=0,then delete the original memory
     * 		else realloc new space.
     * Note: if realBase=0,it still works.The realBase is used to memory move.
     */
    void*  extend(size_t start,size_t size,int extsize,char *realBase=NULL,bool moveData=false);//similar to realloc

    void mdelete(void* p,size_t size);//查找p开始的连续个大小，看是否能满足要求,使用locateForDelete,withdrawNode协同完成，done
    void mdelete(void *p);//done

    void withdrawToParent();                    //回收到父级管理器,当其撤销的时候，必须将子类移动到父类的子类中,done

    //=========getter & setter
    AS_MACRO size_t	getBase()const;
    AS_MACRO size_t getLimit()const;

    //===support for List
    static TreeNode<MemoryDescriptor> *findFirstStart(TreeNode<MemoryDescriptor>* loc,size_t start,size_t len);//done
    static TreeNode<MemoryDescriptor> *findFirstLen(TreeNode<MemoryDescriptor>* loc,size_t len);//done
    static TreeNode<MemoryDescriptor>*findFirstLenAlign(TreeNode<MemoryDescriptor>* loc, size_t len,size_t &extra,size_t alignment);
    static TreeNode<MemoryDescriptor> *locateForInsertation(TreeNode<MemoryDescriptor>* loc,TreeNode<MemoryDescriptor> *son);
    static TreeNode<MemoryDescriptor> *locateForDelete(TreeNode<MemoryDescriptor>* loc,size_t start,size_t len,bool allocable);//done
    static TreeNode<MemoryDescriptor>* locateForDeleteStart(TreeNode<MemoryDescriptor>* loc,size_t start,bool allocable);//done

    /**
     * 1	success
     * 0	failed
     */
    static int addToTree(TreeNode<MemoryDescriptor> *root,TreeNode<MemoryDescriptor> *son);
    static TreeNode<MemoryDescriptor> *nextAllocable(TreeNode<MemoryDescriptor> *node);//done


    int isNullManager();//done
    void setNull();//done
protected:
    TreeNode<MemoryDescriptor> * allocOutNode(TreeNode<MemoryDescriptor> *avlNode,size_t start,size_t len);//done
    void withdrawNode(TreeNode<MemoryDescriptor> *exactNode);//done
    /**
     * Note: extsize is size_t,it cannot be less than 0.if it is 0,then returned false.
     * if not found,return false
     * 	if found at original,return true
     * 	if found at somewhere not corrupted with the original,return true+1
     */
    char findExtend(size_t start,size_t size,size_t extsize,TreeNode<MemoryDescriptor> * &rtnode)const;
    
protected:
    //SimpleMemoryManager<TreeNode<MemoryDescriptor> > *smm;  //the base class already has one
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
