#ifndef MemoryManager_h
#define MemoryManager_h
#include "List.h"

class MemoryDescriptor{
public:
    MemoryDescriptor(int start,unsigned int limit,int allocable=1);//done
    ~MemoryDescriptor();//done
    MemoryDescriptor* init(int start,unsigned int limit,int allocable=1);//done

    /**
    * 逻辑相等而非全等
    */
    int operator==(const MemoryDescriptor& b);//done
    int operator!=(const MemoryDescriptor& b);//done

    int getStart();//done
    unsigned int getLimit();//done

    int isAllocable(); //此方法仅对同层以及上层的节点有意义  done
    MemoryDescriptor* setAllocable(int allocable);//这是指是否用于父类的分配，还是用于自己的分配  done
    void setLimit(unsigned int limit);//done
    void setStart(int start);//done

    //const static MemoryDescriptor NULL_DESCRIPTOR;
protected:
    int start;
    unsigned int limit;
    int allocable;
    
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
class MemoryManager:public Tree<MemoryDescriptor>{
public:
    MemoryManager(SimpleMemoryManager<TreeNode<MemoryDescriptor> > *smm);//done
    MemoryManager(SimpleMemoryManager<TreeNode<MemoryDescriptor> > *smm,int start,unsigned int len,int fatherAllocable=1);
    //以典型的内存描述建立管理器,但这不是唯一的初始化方式，因为开始和结束可以由内部节点指定，实际上开始和结束可以完全没有必要在初始化中指定
    //done
    ~MemoryManager(); 
    
    //注意：不能在父类管理器中
    MemoryManager allocFreeStart(int start,unsigned int len); //从父级管理器衍生,done
    MemoryManager allocFree(unsigned int len);
    
    TreeNode<MemoryDescriptor> *copyOnAllocation(TreeNode<MemoryDescriptor> *head);//复制后的allocable标志位与父节点相反，这从根本上保证了内存的一致性 done
    
    //operator new and delete
    void* mnew(unsigned int size);//done
    void mdelete(void* p,unsigned int size);//查找p开始的连续个大小，看是否能满足要求,使用locateForDelete,withdrawNode协同完成，done


    void free();                                //全部撤销
    int withDrawToParent();                    //回收到父级管理器,当其撤销的时候，必须将子类移动到父类的子类中

    int getBase();
    int getFirstAVL();

    //===support for List
    static TreeNode<MemoryDescriptor> *findFirstStart(TreeNode<MemoryDescriptor>* loc,int start,unsigned int len);//done
    static TreeNode<MemoryDescriptor> *findFirstLen(TreeNode<MemoryDescriptor>* loc,unsigned int len);//done
    static TreeNode<MemoryDescriptor> *locateForInsertation(TreeNode<MemoryDescriptor>* loc,TreeNode<MemoryDescriptor> *son);
    static TreeNode<MemoryDescriptor> *locateForDelete(TreeNode<MemoryDescriptor>* loc,int start,unsigned int len,int allocable);//done

    /**
     * 1	success
     * 0	failed
     */
    static int addToTree(TreeNode<MemoryDescriptor> *root,TreeNode<MemoryDescriptor> *son);
    static TreeNode<MemoryDescriptor> *nextAllocable(TreeNode<MemoryDescriptor> *node);


    int isNullManager();//done
    void setNull();//done
protected:
    TreeNode<MemoryDescriptor> * allocOutNode(TreeNode<MemoryDescriptor> *avlNode,int start,unsigned int len);//done
    void withdrawNode(TreeNode<MemoryDescriptor> *exactNode);//done
    
protected:
    //SimpleMemoryManager<TreeNode<MemoryDescriptor> > *smm;  //the base class already has one
private:

};
#endif
