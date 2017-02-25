#ifdef CODE32
__asm__(".code32 \n\t");
#include "Memory.h"
#include "List.h"
#include "libx2.h"
#include "def.h"
#include "test.h"
MemoryDescriptor::MemoryDescriptor(int start,unsigned int limit,int allocable=1):
start(start),limit(limit),allocable(allocable)
{

}
MemoryDescriptor* MemoryDescriptor::init(int start,unsigned int limit,int allocable=1)
{
    this->start=start;
    this->limit=limit;
    this->allocable=allocable;
    return this;

}
MemoryDescriptor::~MemoryDescriptor()
{
}
int MemoryDescriptor::getStart()
{
    return start;
}
MemoryDescriptor* MemoryDescriptor::setAllocable(int allocable)
{
    this->allocable=allocable;
    return this;
}
void MemoryDescriptor::setLimit(unsigned int limit)
{
    this->limit=limit;
}

unsigned int MemoryDescriptor::getLimit(){
    return limit;
}
int MemoryDescriptor::isAllocable(){
    return allocable;
}
void MemoryDescriptor::setStart(int start)
{
    this->start=start;
}


//============class : MemoryManager

MemoryManager::MemoryManager(SimpleMemoryManager<TreeNode<MemoryDescriptor> > *smm):
Tree<MemoryDescriptor>(smm) //调用父类的构造函数
{

}
MemoryManager::MemoryManager(SimpleMemoryManager<TreeNode<MemoryDescriptor> > *smm,int start,unsigned int len,int fatherAllocable):
MemoryManager(smm)
{
    setHead(smm->getNew()->init(MemoryDescriptor(start,len,fatherAllocable)));
}

MemoryManager::~MemoryManager()
{

}

int MemoryManager::withDrawToParent()
{
    //回收后进行两点之间的检查，如果能够合并就进行合并
}
/**
*   for nodes found available for allocation,here will spilt it out
*   it will:
*       adjust the node before and after the desired area
*       return a node denoting the desired area
*   accept:
*       avlNode = NULL
*   do not accept:
*       the area start and len denoted is not logically inside avlNode
*       means avlNode,start,len should be derived from the inner method
*/
TreeNode<MemoryDescriptor> * MemoryManager::allocOutNode(TreeNode<MemoryDescriptor> *avlNode,int start,unsigned int len)
{

    // Test::dumpMemoryData(avlNode->getData());
    
    TreeNode<MemoryDescriptor> *newnode=NULL;
    if(avlNode)
    {
        unsigned int len1=(unsigned int)(start-avlNode->getData().getStart());
        unsigned int len2=(unsigned int)(avlNode->getData().getLimit() - len - len1);
        if(len1>0)//前面有剩余,需要插入新的点
        {
            avlNode->getData().setLimit(len1);
            newnode=smm->getNew()->init(MemoryDescriptor(start,len,0));//新建一个node，不可用于分配
                                            //将这个节点加入以这个点为根的树中
            avlNode->insertNext(newnode);//中间的节点，已经分配
        }else{//直接取代前面的点
            newnode=avlNode;
            newnode->getData().setStart(start);
            newnode->getData().setLimit(len);
            newnode->getData().setAllocable(0);
        }
        if(len2>0)//后面有剩余
        {
            TreeNode<MemoryDescriptor> *newnodeEnd=smm->getNew()->init(MemoryDescriptor(start+len,len2));
            newnode->insertNext(newnodeEnd);
        }else{//没有就不进行任何操作

        }
    }
    return newnode;
}

DEVEL_UNTESTED(Douglas_Fulton_Shaw)
MemoryManager MemoryManager::allocFreeStart(int start, unsigned int len) {
    // Util::printStr("Enter allocFreeStart: ");
    
    MemoryManager          spaces(smm);
    if(len<=0 || this->isNullManager() )
    {
        spaces.setNull();//ok
    }else{
        copyOnAllocation(getHead());//保证复制了父节点
        TreeNode<MemoryDescriptor> *firstNode=MemoryManager::findFirstStart(getHead(),start,len);//ok,the information of head is ignored,it's full information is stored in it's sons 
        spaces.setHead(allocOutNode(firstNode,start,len));//either not found or found,set the new manager
    }
    return spaces;
}

MemoryManager MemoryManager::allocFree(unsigned int len) {

}

void* MemoryManager::mnew(unsigned int size) {
    TreeNode<MemoryDescriptor> *found=MemoryManager::findFirstLen(getHead(),size);
    if(found)
    {
        TreeNode<MemoryDescriptor> *alloced = allocOutNode(found,found->getData().getStart(),size);
        if(alloced)
        {
            return (void*)(alloced->getData().getStart());
        }
    }
    return NULL;
}

void MemoryManager::mdelete(void* p, unsigned int size) {
}

void MemoryManager::free() {
}


/**
*find the first node from loc's son nodes that is:
*   allocable
*   starts at start or upper
*   has the limit not less than len
*
*/
DEVEL_UNTESTED(Douglas_Fulton_Shaw) DEVEL_COMPLETED(Douglas_Fulton_Shaw) DEVEL_LAST(Douglas_Fulton_Shaw,2017-02-21 23:27:31) DEVEL_AUTHOR(Douglas_Fulton_Shaw) DEVEL_DEP(MemoryManager::getData,MemoryDescriptor::getStart)

TreeNode<MemoryDescriptor>* MemoryManager::findFirstStart(
		TreeNode<MemoryDescriptor>* loc, int start,unsigned int len)
{
	TreeNode<MemoryDescriptor>* p=loc->getSon();
  
    // if(p)
    // {
    //     Test::dumpMemoryData(loc->getData());
    //     Test::dumpMemoryData(p->getData());
    // }else{
    //     Util::printStr("p is NULL \n");
    // }
	while(p && start < p->getData().getStart())
	{
        p=MemoryManager::nextAllocable(p);        
	}
	while(p && (int)(p->getData().getLimit() - len) < start - p->getData().getStart() )
	{
        p=MemoryManager::nextAllocable(p);
	}
	return p; //NULL or first valid section
}

TreeNode<MemoryDescriptor>* MemoryManager::findFirstLen(
		TreeNode<MemoryDescriptor>* loc, unsigned int len) {
	TreeNode<MemoryDescriptor> *p=loc->getSon();
    if(! p->getData().isAllocable() )
    {
        p=MemoryManager::nextAllocable(p);
    }
	while(p && p->getData().getLimit() < len )
    {
        p=MemoryManager::nextAllocable(p);
    }
	return p;
}

int MemoryManager::isNullManager() {
	return getHead()==NULL;
}

    void  MemoryManager::setNull()
    {
        setHead(NULL);
    }

//确保这条线段是位于两个分割点的缝隙之间，如果不是，返回NULL
TreeNode<MemoryDescriptor>* MemoryManager::locateForInsertation(
		TreeNode<MemoryDescriptor>* root, TreeNode<MemoryDescriptor>* son) {
    if( root==NULL || son==NULL)return NULL;
    TreeNode<MemoryDescriptor>* p=root;
    int start=son->getData().getStart();
    unsigned int len=son->getData().getLimit();
    
	while(p && start - p->getData().getStart() < (int)p->getData().getLimit() )
	{
		p=p->getNext();
	}
	if(p)
    {
        if(p->getNext())
        {
            TreeNode<MemoryDescriptor> *forward=p->getNext();
            
            if(forward->getData().getStart() - start >= (int)len)
            {
                return p;   //valid
            }else{
                return NULL; //overlapped with the forward
            }
        }else{
            
            return p;  //need not verify the forward
        }
    }
	return NULL; //until the end,does not find such one
}



int MemoryManager::addToTree(TreeNode<MemoryDescriptor>* root,
		TreeNode<MemoryDescriptor>* son) {
            TreeNode<MemoryDescriptor> *location=MemoryManager::locateForInsertation(root,son);
            if(location)
            {
                
            }
}
/**
* head mustn't be NULL!!
*/
TreeNode<MemoryDescriptor>* MemoryManager::copyOnAllocation(TreeNode<MemoryDescriptor> *head)
{
    if(!head->getSon())
    {
        const MemoryDescriptor &data=head->getData();

        //*****
        //Util::printStr("copyOnAllocation -- ");
        //**********

        TreeNode<MemoryDescriptor> *newnode=smm->getNew()->init(MemoryDescriptor(data.getStart(),data.getLimit(),!data.isAllocable()));

        newnode->setFather(head);
        head->setSon(newnode);
        return newnode;
    }else{
        return head->getSon();    
    }
    

}

DEVEL_UNTESTED(Douglas_Fulton_Shaw)
DEVEL_AUTHOR(Douglas_Fulton_Shaw)
TreeNode<MemoryDescriptor>* MemoryManager::nextAllocable(
		TreeNode<MemoryDescriptor>* node) {
        if(node)
        {
            do{
                node=node->getNext();
            }while( node && (! node->getData().isAllocable()) );
        }
        return node;
}

#endif //CODE32

