/*
 * Cache_macros.h
 *
 *  Created on: 2017年3月24日
 *      Author: 13774
 */

#ifndef INCLUDE_MACROS_CACHE_MACROS_H_
#define INCLUDE_MACROS_CACHE_MACROS_H_


#include <Cache.h>
//========class Cache
#if defined(CODE32)||defined(CODE32USER)
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

#endif // CODE32*

#endif /* INCLUDE_MACROS_CACHE_MACROS_H_ */
