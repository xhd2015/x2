/*
 * AssociatedMemoryManager.h
 *
 *  Created on: 2017年3月19日
 *      Author: 13774
 */

#ifndef INCLUDE_ASSOCIATEDMEMORYMANAGER_H_
#define INCLUDE_ASSOCIATEDMEMORYMANAGER_H_
#include <List.h>


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

	void			setMan(size_t index,size_t nstart,size_t tstart,size_t len,bool doinit=true,int *usedList=NULL,size_t usedLen=0);


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
 * partial
 */
template <class T>
class AssociatedMemoryManager<T,1>{
public:
	typedef SimpleMemoryNode 		NodeType;
	typedef T						TargetType;
	typedef	AssociatedMemoryManager<T,1> This;
public:
	AssociatedMemoryManager();
	AssociatedMemoryManager(size_t nstart,size_t tstart,size_t len,bool doinit=true,int *usedList=NULL,size_t usedLen=0);
	~AssociatedMemoryManager();

    TargetType* getNew();
    /**
     * if not found,index is -1
     */
	TargetType* getNew(int &index);
    void withdraw(TargetType *t);
    int findContinuousFree(size_t n)const;


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
	AS_MACRO	void		freeNode(size_t index);
	AS_MACRO	void		unfreeNode(size_t index);
    AS_MACRO	size_t		getTargetIndex(TargetType* t)const;
	AS_MACRO	size_t		getNodeIndex(NodeType* n)const;
	AS_MACRO	static	size_t getEachSize();
protected:
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
	size_t lastIndex,curSize;//Synchronised
protected:
	/**
	 * Layout:
	 *   ___  --> start
	 *  |	|
	 *  |	|
	 *  |---| --> for nodes
	 *  |	|
	 *  |	|
	 *  |	|
	 *  |	|
	 *  |___| --> for targets
	 */

};

#endif //CODE32 || CODE64






#endif /* INCLUDE_ASSOCIATEDMEMORYMANAGER_H_ */
