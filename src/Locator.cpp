
#include <Locator.h>
#include <libx2.h>


template <class _Source,int _HowStart,int _HowLength,int _HowAllocable>
SourceLocator<_Source,_HowStart,_HowLength,_HowAllocable>::SourceLocator(const _Source& t):
p(&t)
{
}


template <class _Source,int _HowStart,int _HowLength,int _HowAllocable>
bool SourceLocator<_Source,_HowStart,_HowLength,_HowAllocable>::tellLocation(const _Source& t)
{
	return this->tellLocation(t,Int2Type<_HowAllocable>());
}


template <class _Source,int _HowStart,int _HowLength,int _HowAllocable>
bool SourceLocator<_Source,_HowStart,_HowLength,_HowAllocable>::tellLocation(const _Source& t,Int2Type<Locator::IGNORE>)
{
	if(_HowStart!=Locator<_Source>::IGNORE && Util::sign(t.getStart() - this->p->getStart()) != _HowStart)return false;
	if(_HowLength!=Locator<_Source>::IGNORE && Util::sign(t.getLimit() - this->p->getStart()) != _HowLength)return false;
	return true;
}

template <class _Source,int _HowStart,int _HowLength,int _HowAllocable>
bool SourceLocator<_Source,_HowStart,_HowLength,_HowAllocable>::tellLocation(const _Source& t,Int2Type<Locator::EQUAL>)
{
	if(this->p->isAllocable()!=t.isAllocable())return false;
	return this->tellLocation(t,Int2Type<Locator::IGNORE>());
	
}
