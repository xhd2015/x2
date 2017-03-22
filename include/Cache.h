/*
 * Cache.h
 *
 *  Created on: 2017年3月21日
 *      Author: 13774
 */

#ifndef INCLUDE_CACHE_H_
#define INCLUDE_CACHE_H_
#include <def.h>

/**
 * V is likely to be a pointer and
 * K is likely to be a simple type
 */
template <class K,class V>
class Cache {
public:
	typedef Cache<K,V>	This;
	typedef K KeyType;
	typedef V ValueType;
	typedef bool (*COMPARATOR)(KeyType k1,KeyType k2);
	typedef ValueType (*DEFAULT_GETTER)(KeyType k);
public:
	Cache(size_t capacity,DEFAULT_GETTER getter,COMPARATOR cmp=NULL);
	AS_MACRO ~Cache();

	ValueType	get(KeyType k);
	AS_MACRO size_t		getAccessTimes()const;
	AS_MACRO size_t		getHitTimes()const;

	AS_MACRO void	setCompartor(COMPARATOR cmp);
	AS_MACRO COMPARATOR	getComparator()const;
	AS_MACRO void	setGetter(DEFAULT_GETTER getter);
	AS_MACRO DEFAULT_GETTER	getGetter()const;
protected:

	COMPARATOR cmp;
	DEFAULT_GETTER	getter;
	size_t		capacity;
	KeyType		*karr;
	ValueType	*varr;
	size_t		accessTimes,hitTimes;

};


//===========function macros
//========class Cache
template<class K, class V>
Cache<K, V>::~Cache() {
}
template<class K, class V>
size_t Cache<K, V>::getAccessTimes() const
{
	return this->accessTimes;
}

template<class K, class V>
size_t Cache<K, V>::getHitTimes() const
{
	return this->hitTimes;
}

template <class K,class V>
void	Cache<K,V>::setCompartor(COMPARATOR cmp)
{
	this->cmp=cmp;
}




template <class K,class V>
typename Cache<K,V>::COMPARATOR Cache<K,V>::getComparator()const
{
	return this->cmp;
}

template<class K, class V>
void Cache<K, V>::setGetter(
		DEFAULT_GETTER getter)
{
	this->getter=getter;
}



template<class K, class V>
typename Cache<K,V>::DEFAULT_GETTER Cache<K, V>::getGetter() const
{
	return this->getter;
}

#endif /* INCLUDE_CACHE_H_ */
