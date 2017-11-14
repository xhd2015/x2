
#include <Locator.h>
#include <libx2.h>
#if defined(CODE32)
	__asm__(".code32 \n\t");
#endif
//=========template instantiate
#ifdef CODE32

#elif defined(CODE64)
#include <cstdio>
#include <List.h>
#include <Memory.h>
	template class SourceLocator<LinearSourceDescriptor,Locator<LinearSourceDescriptor>::LESS,
			Locator<LinearSourceDescriptor>::IGNORE,Locator<LinearSourceDescriptor>::IGNORE>;

	template class SourceLocator<LinearSourceDescriptor,Locator<LinearSourceDescriptor>::EQUAL,
			Locator<LinearSourceDescriptor>::EQUAL,Locator<LinearSourceDescriptor>::IGNORE>;

	template class SourceLocator<LinearSourceDescriptor,Locator<LinearSourceDescriptor>::EQUAL,
			Locator<LinearSourceDescriptor>::BIGGER,Locator<LinearSourceDescriptor>::IGNORE>;

	template class SourceLocator<LinearSourceDescriptor,Locator<LinearSourceDescriptor>::IGNORE,
			Locator<LinearSourceDescriptor>::EQUAL,Locator<LinearSourceDescriptor>::IGNORE>;

	template class SourceLocator<LinearSourceDescriptor,Locator<LinearSourceDescriptor>::IGNORE,
			Locator<LinearSourceDescriptor>::BIGGER,Locator<LinearSourceDescriptor>::IGNORE>;

	template class SourceLocator<LinearSourceDescriptor,Locator<LinearSourceDescriptor>::EQUAL,
			Locator<LinearSourceDescriptor>::IGNORE,Locator<LinearSourceDescriptor>::IGNORE>;

#endif

#include <macros/all.h>

template <class _Source,int _HowStart,int _HowLength,int _HowAllocable>
SourceLocator<_Source,_HowStart,_HowLength,_HowAllocable>::SourceLocator(const _Source& t):
p(&t)
{
}


template <class _Source,int _HowStart,int _HowLength,int _HowAllocable>
bool SourceLocator<_Source,_HowStart,_HowLength,_HowAllocable>::tellLocation(const _Source& t)const
{
	return this->tellLocation(t,Int2Type<_HowAllocable>());
}


template <class _Source,int _HowStart,int _HowLength,int _HowAllocable>
bool SourceLocator<_Source,_HowStart,_HowLength,_HowAllocable>::tellLocation(const _Source& t,Int2Type<Locator<_Source>::IGNORE>)const
{
#if defined(CODE64)
//	printf("in tellLocation(ignore allocable),_HowStart==%d  _HowLength=%d sign(start diff(%x-%x))=%d  sign(limit diff(%x-%x))=%d\n",
//			_HowStart,_HowLength,
//			t.getStart(),
//			this->p->getStart(),
//			Util::sign(t.getStart() - this->p->getStart()),
//			t.getLimit(),
//			this->p->getLimit(),
//			Util::sign(t.getLimit() - this->p->getStart())
//	);
#endif
	if(_HowStart!=Locator<_Source>::IGNORE && Util::sign(t.getStart() - this->p->getStart()) != _HowStart)return false;
	if(_HowLength!=Locator<_Source>::IGNORE && Util::sign(t.getLimit() - this->p->getStart()) != _HowLength)return false;
#if defined(CODE64)
//	printf("return true\n");
#endif
	return true;
}

template <class _Source,int _HowStart,int _HowLength,int _HowAllocable>
bool SourceLocator<_Source,_HowStart,_HowLength,_HowAllocable>::tellLocation(const _Source& t,Int2Type<Locator<_Source>::EQUAL>)const
{
	if(this->p->isAllocable()!=t.isAllocable())return false;
	return this->tellLocation(t,Int2Type<Locator<_Source>::IGNORE>());
	
}
