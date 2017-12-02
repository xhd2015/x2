/*
 * Cache.h
 *
 *  Created on: 2017年3月21日
 *      Author: 13774
 */

#ifndef INCLUDE_CACHE_H_
#define INCLUDE_CACHE_H_
#include <def.h>

// TODO 解封下面结构，在64位下也能够验证
#if defined(CODE32)||defined(CODE32USER)
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
#endif // CODE32*



#endif /* INCLUDE_CACHE_H_ */
