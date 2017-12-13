/*
 * Cache.cpp
 *
 *  Created on: 2017年3月21日
 *      Author: 13774
 */

#include <Cache.h>
#include <Kernel.h>
#if defined(CODE32)
	__asm__(".code32 \n\t");
#endif


#if defined(CODE32) || defined(CODE32USER)
//=========class Cache<K,V>
template<class K, class V>
Cache<K, V>::Cache(size_t capacity,DEFAULT_GETTER getter,COMPARATOR cmp):
cmp(cmp),capacity(capacity),getter(getter),accessTimes(0),hitTimes(0)
{
	karr=(KeyType*)Kernel::getTheKernel()->mnewKernel((size_t)this->capacity * (sizeof(KeyType) + sizeof(ValueType)));
	varr = karr + this->capacity;
}


template<class K, class V>
typename  Cache<K, V>::ValueType Cache<K, V>::get(KeyType k)
{
	this->accessTimes++;
	int unused=0;
	for(int i=0;i!=this->capacity;i++)
	{
		if(this->varr[i]==nullptr)
		{
			unused=i;
		}else{
			bool bcmp;
			if(this->cmp==nullptr) //select comparator
				bcmp = (k==this->karr[i]);
			else
				bcmp = this->cmp(k,this->karr[i]);

			if(bcmp)
			{
				this->hitTimes++;
				return this->varr[i];
			}
		}
	}
	ValueType v;
	if( (v=this->getter(k))!=nullptr  )//update cache,select unused index else select 0
	{
		this->karr[unused]=v;
		return v;
	}
	return nullptr; //not found both in cache and in original container
}

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
