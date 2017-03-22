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
		if(this->varr[i]==NULL)
		{
			unused=i;
		}else{
			bool bcmp;
			if(this->cmp==NULL) //select comparator
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
	if( (v=this->getter(k))!=NULL  )//update cache,select unused index else select 0
	{
		this->karr[unused]=v;
		return v;
	}
	return NULL; //not found both in cache and in original container
}
