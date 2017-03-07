
#ifndef Locator_h__
#define Locator_h__

#include <List.h>
#include <loki/Int2Type.h>

template <class T>
class Locator{
public:
	/**
	* If the template argument expected a known constant,then replace 'const static' with enum,which does not need actual space allocation
	*		DISCARD=IGNORE,KEEP=EQUAL
	*/
	const static int IGNORE,EQUAL,LESS,BIGGER;
	const static int DISCARD,KEEP;
public:
	//can constructor be virtual?But that is not necessary because poli.... can do that

	/**
	*	if 'this'(I mean the pointer this) should be located in somewhere,but the result will yield until meet some edge node,then it shoud return NULL,
	*	And if that edge node condition has been met,this method should return it.Then the process of locating stopped.
	*
	*/
	//virtual T* locate(const T &t)=0;   //DEPRECATED
	/**
	*	Tell the location of t,is it before p,at p,or after p
	*/
	virtual bool tellLocation(const T &t)=0;
};


/**
*	_Source should be any of LinearSourceDescriptor or MemoryDescriptor or that provide compitable methods that can satisfy this class
*      _HowXXX < 0  , t.XXX < this->p->XXX
*/
template <class _Source,int _HowStart,int _HowLength,int _HowAllocable>
class SourceLocator:public Locator<_Source>
{
public:
	SourceLocator(const _Source& t);//a copy constructor
	virtual bool tellLocation(const T &t);
	AS_MACRO const _Source* getComparator();//return p;
protected:
	const _Source* p;
private:
	//two conditions: -IgnoreAllocable=true|false
	bool tellLocation(const _Source& t,Int2Type<Locator::EQUAL>);
	bool tellLocation(const _Source& t,Int2Type<Locator::IGNORE>);
};

//============Function Macros
//=====class SourceLocator
template <class _Source,int _HowStart,int _HowLength,int _HowAllocable>
const _Source* SourceLocator<_Source,_HowStart,_HowLength,_HowAllocable>::getComparator()
{
	return p;
}



#endif //Locator_h__