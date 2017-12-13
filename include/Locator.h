
#ifndef Locator_h__
#define Locator_h__

#include <conceptual/loki/Int2Type.h>
#include <def.h>

template <class T>
class Locator{
public:
	/**
	* If the template argument expected a known constant,then replace 'const static' with enum,which does not need actual space allocation
	*		DISCARD=IGNORE,KEEP=EQUAL
	*/
	/*
	const static int IGNORE,EQUAL,LESS,BIGGER;
	const static int DISCARD,KEEP;
	*/
	enum{IGNORE=-2,LESS=-1,EQUAL=0,BIGGER=1,DISCARD=-2,KEEP=0};
public:
	//can constructor be virtual?But that is not necessary because poli.... can do that

	/**
	*	if 'this'(I mean the pointer this) should be located in somewhere,but the result
	*	will yield until meeting some edge node,then it should return nullptr,
	*	And if that edge node condition has been met,this method should return it.Then the process of locating stopped.
	*
	*/
	//virtual T* locate(const T &t)=0;   //DEPRECATED
	/**
	*	Tell the location of t,is it before p,at p,or after p
	*/
	bool meetedBy(const T &t);//This is non-virtual and not defined=0;

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
	/**
	 * t meets *this
	 * (t,*this)这组关系对是否满足配置的要求
	 */
	bool meetedBy(const _Source &t)const;


	AS_MACRO const _Source* getComparator()const;//return p;

	enum{
		RELATION_EQ,RELATION_LS_EQ,RELATION_LS,RELATION_GT,RELATION_GT_EQ,RELATION_IGNORE
	};
	/**
	 * 判断两个可比较的元素是否满足给定的关系
	 * @param relation  一组位
	 */
	static bool meeted(u8_t startRelation,u8_t limitRelation,u8_t allocReation,const _Source &left,const _Source &right);
protected:
	const _Source* p;
private:
	//two conditions: -IgnoreAllocable=true|false
	bool tellLocation(const _Source& t,Int2Type<Locator<_Source>::EQUAL>)const;
	/**
	 * 判断t和*this是否满足给定的位置关系
	 * @param t
	 * @param IGNORE	表示忽略分配性
	 */
	bool tellLocation(const _Source& t,Int2Type<Locator<_Source>::IGNORE>)const;
};



#endif //Locator_h__
