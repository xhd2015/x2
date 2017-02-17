
#include "List.h"

//====================模板实例化区域
//===========模板声明区
template class SimpleMemoryManager<ListNode<int> >;

//====================class :SimpleMemoryNode
SimpleMemoryNode::SimpleMemoryNode(int NO):
NO(NO)
{

}
SimpleMemoryNode::~SimpleMemoryNode()
{
    
}


//===================class: SimpleMemoryManager

//初始化列表的作用就是在生成代码时直接生成mov的形式
template <class T>
SimpleMemoryManager<T>::SimpleMemoryManager(int start,unsigned int limit):
start(start),limit(limit),
data((T*)start),len((int)(limit/sizeof(T))),curSize(0),
lastIndex(0)
{
    for(int i=0;i!=len;i++)
    {
        data[i].free();
    }
}

template <class T>
SimpleMemoryManager<T>::~SimpleMemoryManager()
{
    
}


template <class T>
T* SimpleMemoryManager<T>::getNew()
{
    T *rt=NULL;
    if(!isFull())
    {
        for(int i=0;i!=len;i++)
        {
            if(data[lastIndex].isFree())
            {
                rt=&data[lastIndex];
                rt->unfree();
                curSize++;
                lastIndex = (lastIndex + 1 ) % len;
                break;
            }
            lastIndex = (lastIndex + 1 ) % len;
        }
    }
    return rt;
}

template <class T>
void SimpleMemoryManager<T>::withdraw(T *t)
{
    if(!t->isFree())
    {
        t->free();
    }
}