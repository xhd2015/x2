
#include <conceptual/Serialize.h>


//==class SerializerPtr
#define __DEF_Template_SerializerPtr template <class __EnvTransfer>
#define __DEF_SerializerPtr SerializerPtr<__EnvTransfer>

__DEF_Template_SerializerPtr
__DEF_SerializerPtr::SerializerPtr(void *p):ptr((u8_t*)p)
{}
__DEF_Template_SerializerPtr
void *__DEF_SerializerPtr::getPtr()const
{
	return ptr;
}
__DEF_Template_SerializerPtr
typename __DEF_SerializerPtr::__SerializerPtr &
__DEF_SerializerPtr::operator=(const SerializerPtr &rhs)
{
	this->ptr=rhs.ptr;
	return *this;
}
__DEF_Template_SerializerPtr
__DEF_SerializerPtr::operator bool()const
{
	return (ptr!=nullptr);
}
__DEF_Template_SerializerPtr
__DEF_SerializerPtr::operator void*()const
{
	return ptr;
}

/**
 * 如果指针为nullptr，则仍然返回nullptr
 */
__DEF_Template_SerializerPtr
typename __DEF_SerializerPtr::__SerializerPtr  __DEF_SerializerPtr::operator+(ptrdiff_t pdiff)const
{
	if(*this)
		return SerializerPtr(ptr+pdiff);
	else
		return SerializerPtr(nullptr);
}
/**
 * 如果指针为nullptr，则仍然返回nullptr
 */
__DEF_Template_SerializerPtr
typename __DEF_SerializerPtr::__SerializerPtr  __DEF_SerializerPtr::operator-(ptrdiff_t pdiff)const
{
	if(*this)
		return SerializerPtr(ptr-pdiff);
	else
		return SerializerPtr(nullptr);
}
__DEF_Template_SerializerPtr
typename __DEF_SerializerPtr::__SerializerPtr&  __DEF_SerializerPtr::
	operator+=(ptrdiff_t pdiff)
{
	if(ptr)
		ptr+=pdiff;
	return *this;
}
__DEF_Template_SerializerPtr
typename __DEF_SerializerPtr::__SerializerPtr&  __DEF_SerializerPtr::
	operator-=(ptrdiff_t pdiff)
{
	if(ptr)
		ptr-=pdiff;
	return *this;
}

__DEF_Template_SerializerPtr
template <class __BasicType,size_t __N,bool __SafeAssign>
void __DEF_SerializerPtr::serializeByType(__BasicType data)
{
	__serializeByType<__BasicType,__N>(data,Int2Type<__SafeAssign>());
}
__DEF_Template_SerializerPtr
template <class __BasicType,size_t __N,bool __SafeAssign>
void __DEF_SerializerPtr::deserializeByType(__BasicType& data)
{
	__deserializeByType<__BasicType,__N>(data,Int2Type<__SafeAssign>());
}


__DEF_Template_SerializerPtr
template <class __BasicType,size_t __N>
void __DEF_SerializerPtr::__serializeByType(__BasicType data,Int2Type<true>)
{
	//可以安全写入
	*(__BasicType*)ptr=data;
	ptr+=__N;
}

__DEF_Template_SerializerPtr
template <class __BasicType,size_t __N>
void __DEF_SerializerPtr::__serializeByType(__BasicType data,Int2Type<false>) // 复制N个字节的数据，一般情况
{
	using __Type = typename Byte2Type<__N>::Type;
	*(__Type*)ptr=(__Type)data;
	ptr+=__N;
}
__DEF_Template_SerializerPtr
template <class __BasicType,size_t __N>
void __DEF_SerializerPtr::__deserializeByType(__BasicType& data,Int2Type<true>)
{
	//可以安全写入
	data = *(__BasicType*)ptr;
	ptr+=__N;
}
__DEF_Template_SerializerPtr
template <class __BasicType,size_t __N>
void __DEF_SerializerPtr::__deserializeByType(__BasicType& data,Int2Type<false>) // 复制N个字节的数据，一般情况
{
	using __Type = typename Byte2Type<__N>::Type;
	data = *(__Type*)ptr;
	ptr+=__N;
}

__DEF_Template_SerializerPtr
template <class __BasicType>
typename __DEF_SerializerPtr::__SerializerPtr &__DEF_SerializerPtr::
	operator<<(__BasicType s)
{
	using SizeHolder = typename __EnvTransfer::template SizeofHostType<__BasicType>;
	serializeByType<__BasicType,SizeHolder::Size>(s);
	return *this;
}
__DEF_Template_SerializerPtr
template <class __BasicType>
typename __DEF_SerializerPtr::__SerializerPtr &__DEF_SerializerPtr::
	operator>>(__BasicType& s)
{
	using SizeHolder = typename __EnvTransfer::template SizeofHostType<__BasicType>;
	deserializeByType<__BasicType,SizeHolder::Size>(s);
	return *this;
}

#undef __DEF_Template_SerializerPtr
#undef __DEF_SerializerPtr
//***********SerializePtr定义完成===




//==globale operator>> & operator<<, semantically
//template <class __S,class __EnvTransfer>
//SerializerPtr<__EnvTransfer>& operator<<(SerializerPtr<__EnvTransfer>& p,const __S &s)
//{
//	return s.serialize(p);
//}
//template <class __S,class __EnvTransfer>
//SerializerPtr<__EnvTransfer>& operator>>(SerializerPtr<__EnvTransfer>& p,__S &s)
//{
//	return s.deserialize(p);
//}


