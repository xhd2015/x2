
#include <Locator.h>
#include <libx2.h>
#if defined(CODE32)
	__asm__(".code32 \n\t");
#endif
//=========template instantiate
#ifdef CODE32

#elif defined(CODE64)

#endif


template <class _Source,int _HowStart,int _HowLength,int _HowAllocable>
SourceLocator<_Source,_HowStart,_HowLength,_HowAllocable>::SourceLocator(const _Source& t):
p(&t)
{
}


template <class _Source,int _HowStart,int _HowLength,int _HowAllocable>
bool SourceLocator<_Source,_HowStart,_HowLength,_HowAllocable>::meetedBy(const _Source& t)const
{
	return tellLocation(t,Int2Type<_HowAllocable>());
}

template <class _Source,int _HowStart,int _HowLength,int _HowAllocable>
bool SourceLocator<_Source,_HowStart,_HowLength,_HowAllocable>::meeted(
		u8_t startRelation,u8_t limitRelation,u8_t allocReation,const _Source &left,const _Source &right)
{
	bool resStart=true;
	bool resLimit=true;
	bool resAlloc=true;
	switch(startRelation)
	{
	case RELATION_EQ:
		resStart=(left.getStart()==right.getStart());
		break;

	case RELATION_LS_EQ:
		resStart=left.getStart()<=right.getStart();
		break;

	case RELATION_LS:
		resStart=left.getStart()<right.getStart();
		break;

	case RELATION_GT:
		resStart=left.getStart()>right.getStart();
		break;

	case RELATION_GT_EQ:
		resStart=left.getStart()>=right.getStart();
		break;
	case RELATION_IGNORE:
		break;
	}
	if(resStart==false)return false;

	switch(limitRelation)
	{
	case RELATION_EQ:
		resLimit=(left.getLimit()==right.getLimit());
		break;

	case RELATION_LS_EQ:
		resLimit=left.getLimit()<=right.getLimit();
		break;

	case RELATION_LS:
		resLimit=left.getLimit()<right.getLimit();
		break;

	case RELATION_GT:
		resLimit=left.getLimit()>right.getLimit();
		break;

	case RELATION_GT_EQ:
		resLimit=left.getLimit()>=right.getLimit();
		break;
	case RELATION_IGNORE:
		break;
	}
	if(resLimit==false)return false;

	switch(allocReation)
	{
	case RELATION_EQ:
		resAlloc= (left.isAllocable()==right.isAllocable());
		break;
	case RELATION_IGNORE:
	default:
		break;
	}
	return resAlloc;
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
	if(_HowStart!=Locator<_Source>::IGNORE &&
			(   (_HowStart==Locator<_Source>::EQUAL &&  (t.getStart()!=p->getStart())) ||
				(_HowStart==Locator<_Source>::LESS && (t.getStart() >=p->getStart() )) ||
				(_HowStart==Locator<_Source>::BIGGER && (t.getStart() <= p->getStart()))))return false;
	if(_HowLength!=Locator<_Source>::IGNORE &&
			(   (_HowLength==Locator<_Source>::EQUAL &&  (t.getLimit()!=p->getLimit())) ||
				(_HowLength==Locator<_Source>::LESS && (t.getLimit() >=p->getLimit() )) ||
				(_HowLength==Locator<_Source>::BIGGER && (t.getLimit() <= p->getLimit()))))return false;

	// DEPRECATED
//	if(_HowLength!=Locator<_Source>::IGNORE && Util::sign(t.getLimit() - p->getStart()) != _HowLength)return false;

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


template <class _Source,int _HowStart,int _HowLength,int _HowAllocable>
const _Source* SourceLocator<_Source,_HowStart,_HowLength,_HowAllocable>::getComparator()const
{
	return p;
}


