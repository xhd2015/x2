/*
 * AssociatedMemoryManager.h
 *
 *  Created on: 2017年3月19日
 *      Author: 13774
 */

#ifndef INCLUDE_ASSOCIATEDMEMORYMANAGER_H_
#define INCLUDE_ASSOCIATEDMEMORYMANAGER_H_
#include <List.h>
#include <def.h>




#if defined(CODE32)||defined(CODE64)
/**
 * Like SimpleMemoryManager
 */
template <class T,size_t MaxArrNum=10>
class AssociatedMemoryManager {
public:
	typedef SimpleMemoryNode 		NodeType;
	typedef T						TargetType;
public:
	AssociatedMemoryManager();
	~AssociatedMemoryManager();


	TargetType*	getNew();
	void withraw(TargetType *t);

	void			setMan(size_t index,size_t nstart,size_t tstart,size_t len,bool doinit=true,int *usedList=nullptr,size_t usedLen=0);


	/**
	 * return MaxArrNum
	 */
	AS_MACRO		size_t	getArrNum();

protected:
	/**
	 * For MaxArrNum > 1, these methods are deprecated
	 */
	DEPRECATED AS_MACRO TargetType* getTarget(size_t index);//find first non-empty list,record the last non-empty list number
	DEPRECATED AS_MACRO NodeType*	 getNode(size_t index);
	DEPRECATED AS_MACRO	size_t		getTargetIndex(TargetType* t);
	DEPRECATED AS_MACRO	size_t		getNodeIndex(NodeType* n);

	AssociatedMemoryManager<T,1> manArrs[MaxArrNum];
	size_t lastMan;
};

/**
 * 关联内存管理
 *
 * @param T 要管理的类型
 *
 * 很多情况下，我们需要对一些固定的数组进行管理，但是在原数组的基础上又不能进行任何操作
 * 关联管理的思想是，再新建一个同样大小的以SimpleMemoryNode来标记的数组，通过管理这个简单的数组来间接
 * 管理目标数组
 * 这里指出Node和Target的概念：Node是指SimpleMemoryNode， Target是指要管理的目标类型
 * 可以认为，管理器中包括两个数组：Node数组和Target数组
 *
 * Update 2017年12月5日16:28:51：实际上，应当在任何情况下都采用关联管理的思想。
 */
template <class T>
class AssociatedMemoryManager<T,1>{
public:
	typedef SimpleMemoryNode 		NodeType;
	typedef T						TargetType;
	typedef	AssociatedMemoryManager<T,1> This;
public:
	AssociatedMemoryManager();
	/**
	 *
	 * @param nstart	Node的开始地址
	 * @param tstart	Target的开始地址
	 * @param len		总数组长度
	 * @param nodeArrInit	是否对Node数组进行初始化
	 * @param usedList		用于单独确定哪些已经被使用
	 * @param usedLen		usedList的长度
	 */
	AssociatedMemoryManager(size_t nstart,size_t tstart,size_t len,bool nodeArrInit=true,int *usedList=nullptr,size_t usedLen=0);
	~AssociatedMemoryManager();

    TargetType* getNew();
    /**
     * if not found,index is -1
     */
	TargetType* getNew(int &index);
    void withdraw(TargetType *t);
    /**
     * 查找连续n个free的节点
     * @param n 目标长度
     * @return 找到返回起始下标
     * 			没有找到返回-1
     */
    int allocContinuousFree(size_t n);

    AS_MACRO bool isFull()const;
    AS_MACRO bool isEmpty()const;
    AS_MACRO size_t getLen()const;
    AS_MACRO size_t getLeft()const;
    AS_MACRO size_t getCurSize()const;
    /**
     * There will be no error handler any more,we can add it by ourself,not internally.
     *
     * AS_MACRO ERROR_HANDLER getErrHandler();
     * AS_MACRO void			setErrHandler(ERROR_HANDLER errhandle);
     */
	AS_MACRO	TargetType*	getTarget(size_t index);
    AS_MACRO	size_t		getTargetIndex(TargetType* t)const;
	AS_MACRO	size_t		getNodeIndex(NodeType* n)const;
	AS_MACRO	constexpr static	size_t getEachSize();
	AS_MACRO	NodeType*	getNodeAddress();
private:
	void		allocNode(size_t index);
	void		withdrawNode(size_t index);
	AS_MACRO	NodeType*	getNode(size_t index);
	union{
		size_t nstart;
		NodeType *narr;
	};
	union{
		size_t tstart;
		TargetType *tarr;
	};

	size_t len;

	//最后一个被分配的下标
	size_t lastIndex;

	//当前已分配的节点数
	size_t curAllocedSize;//Synchronized
protected:
	/**
	 * Layout:
	 *   ___  --> start
	 *  |	|
	 *  |	|
	 *  |___| --> for nodes
	 *
	 *   ___  --> start_2
	 *  |	|
	 *  |	|
	 *  |	|
	 *  |	|
	 *  |___| --> for targets
	 */

};

#endif //CODE32 || CODE64




#endif /* INCLUDE_ASSOCIATEDMEMORYMANAGER_H_ */
