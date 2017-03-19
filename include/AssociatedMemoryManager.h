/*
 * AssociatedMemoryManager.h
 *
 *  Created on: 2017年3月19日
 *      Author: 13774
 */

#ifndef INCLUDE_ASSOCIATEDMEMORYMANAGER_H_
#define INCLUDE_ASSOCIATEDMEMORYMANAGER_H_
#include <List.h>

/**
 * Like SimpleMemoryManager
 */
template <class T,size_t MaxArrNum=10>
class AssociatedMemoryManager {
public:
	typedef SimpleMemoryNode 		NodeType;
	typedef T						TargetType;
	typedef LinearSourceDescriptor  TargetArrType;
	typedef LinearSourceDescriptor	NodeArrType;
public:
	AssociatedMemoryManager();
	virtual ~AssociatedMemoryManager();

	TargetType*	getNew();
	void withraw(TargetType *t);

	void			setMan(size_t index,size_t nodeStart,size_t nlen,size_t targetStart,size_t len);


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
	typedef LinearSourceDescriptor  TargetArrType;
	typedef LinearSourceDescriptor	NodeArrType;
public:
	AssociatedMemoryManager();
	AssociatedMemoryManager(size_t nstart,size_t tstart,size_t len);


    TargetType* getNew();
    void withdraw(TargetType *t);


    AS_MACRO bool isFull()const;
    AS_MACRO bool isEmpty()const;
    AS_MACRO size_t getLen()const;
    AS_MACRO size_t getCurSize()const;
    AS_MACRO static size_t getNodeSize();//done
    /**
     * There will be no error handler any more,we can add it by ourself,not internally.
     *
     * AS_MACRO ERROR_HANDLER getErrHandler();
     * AS_MACRO void			setErrHandler(ERROR_HANDLER errhandle);
     */

protected:
	AS_MACRO	TargetType*	getTarget(size_t index);
	AS_MACRO	NodeType*	getNode(size_t index);
	AS_MACRO	size_t		getTargetIndex(TargetType* t);
	AS_MACRO	size_t		getNodeIndex(NodeType* n);
	union{
		size_t nstart;
		NodeType narr[];
	};
	union{
		size_t tstart;
		TargetType tarr[];
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


//===========function macros
//=====class AssociatedMemoryManager<T,MaxArrNum>
template<class T,size_t MaxArrNum>
size_t	AssociatedMemoryManager<T,MaxArrNum>::getArrNum()
{
	return MaxArrNum;
}



//===============class AssociatedMemoryManager<T,1>
template<class T>
bool AssociatedMemoryManager<T,1>::isFull()const
{
    return this->curSize==this->len;
}
template<class T>
bool AssociatedMemoryManager<T,1>::isEmpty()const
{
    return this->curSize==0;
}
template<class T>
size_t AssociatedMemoryManager<T,1>::getLen()const
{
    return this->len;
}
template<class T>
size_t AssociatedMemoryManager<T,1>::getCurSize()const
{
    return this->curSize;
}

template<class T>
typename AssociatedMemoryManager<T, 1>::TargetType* AssociatedMemoryManager<T, 1>::getTarget(size_t index)
{
	return (index<this->len)?this->tarr + index:NULL;
}

template<class T>
typename AssociatedMemoryManager<T, 1>::NodeType* AssociatedMemoryManager<T, 1>::getNode(size_t index)
{
	return (index<this->len)?this->narr + index:NULL;
}
/**
 * return len+1 meaning invalid
 * NULL,<,>
 */
template<class T>
size_t AssociatedMemoryManager<T, 1>::getTargetIndex(TargetType* t)
{
	ptrdiff_t diff=(t - this->tarr)/sizeof(*t);
	return (t==NULL || diff<0||diff >= this->len) ?(this->len +1 ):(size_t)diff;

}
template<class T>
size_t		AssociatedMemoryManager<T, 1>::getNodeIndex(NodeType* n)
{
	ptrdiff_t diff=(n - this->narr)/sizeof(*n);
	return (t==NULL||diff<0||diff >= this->len) ?(this->len +1 ):(size_t)diff;
}


#endif /* INCLUDE_ASSOCIATEDMEMORYMANAGER_H_ */
