
#include <conceptual/Serialize.h>
#include <type_traits>


//==class SerializerPtr
#define __DEF_Template_SerializerPtr template <class __EnvTransfer>
#define __DEF_SerializerPtr SerializerPtr<__EnvTransfer>

__DEF_Template_SerializerPtr
__DEF_SerializerPtr::SerializerPtr(void *p):ptr(static_cast<u8_t*>(p))
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
typename __DEF_SerializerPtr::__SerializerPtr & __DEF_SerializerPtr::operator=(void *p)
{
	this->ptr = static_cast<u8_t*>(p);
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
__DEF_Template_SerializerPtr
__DEF_SerializerPtr::operator void*()
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
template <class __BasicType>
void __DEF_SerializerPtr::serializeBasicType(__BasicType data)
{
	static_assert(std::is_pod<__BasicType>(),"must be called with pod/basic/primitive types");
	__serializeByType<__BasicType,hostTypeSize<__BasicType>()>
			(data,Int2Type<bscTpSrlzPolicy<__BasicType>()>());
}
__DEF_Template_SerializerPtr
template <class __BasicType>
void __DEF_SerializerPtr::deserializeBasicType(__BasicType& data)
{
	static_assert(std::is_pod<__BasicType>(),"must be called with pod/basic/primitive types");
	__deserializeByType<__BasicType,hostTypeSize<__BasicType>()>
			(data,Int2Type<bscTpDesrlzPolicy<__BasicType>()>());
}

//__DEF_Template_SerializerPtr
// void __DEF_SerializerPtr::serializeBasicType(/*const*/ void* data,ptrdiff_t diff)
//{
//	static_assert( __EnvTransfer::ptrPolicy()!=__EnvTransfer::POLICY_PTR_OBJECT, // TODO 现在不支持序列化对象，因为还没有论证清除
//			"ptr object policy not supported yet");
//	__serializeByType<const void *,hostTypeSize<const void*>()>(
//			static_cast<const char*>(data) - diff, // 减去偏移
//			Int2Type<bscTpSrlzPolicy<const char *>()>());
//}
//__DEF_Template_SerializerPtr
//	void __DEF_SerializerPtr::deserializeBasicType(void* & data,ptrdiff_t diff)
//{
//	static_assert( __EnvTransfer::ptrPolicy()!=__EnvTransfer::POLICY_PTR_OBJECT, // TODO 现在不支持序列化对象，因为还没有论证清除
//			"ptr object policy not supported yet");
//	__deserializeByType<void *,hostTypeSize<void*>()>(
//			data,
//			Int2Type<bscTpDesrlzPolicy<void*>()>());
//	static_cast<char*&>(data) += diff;//恢复偏移
//}

__DEF_Template_SerializerPtr
template <class __BasicType>
void __DEF_SerializerPtr::serializeBasicType(const __BasicType *data,size_t len)
{
	static_assert(std::is_pod<__BasicType>(),"must be called with pod/basic/primitive types");
	for(size_t i=0;i!=len;++i)
		__serializeByType<__BasicType,hostTypeSize<__BasicType>()>(data[i],Int2Type<bscTpSrlzPolicy<__BasicType>()>());
}

__DEF_Template_SerializerPtr
template <class __BasicType>
void __DEF_SerializerPtr::deserializeBasicType(__BasicType* data,size_t len)
{
	static_assert(std::is_pod<__BasicType>(),"must be called with pod/basic/primitive types");
	for(size_t i=0;i!=len;++i)
		__deserializeByType<__BasicType,hostTypeSize<__BasicType>()>(data[i],Int2Type<bscTpDesrlzPolicy<__BasicType>()>());
}


// 指针走这里
__DEF_Template_SerializerPtr
template <class __BasicType,int __N>
void __DEF_SerializerPtr::__serializeByType(__BasicType data,Int2Type<TYPE_BASIC_SAFE>)
{
	//可以安全写入
//	std::cout << "__N" << __N << endl;
	*reinterpret_cast<__BasicType*>(ptr)=data;
	ptr+=__N;
}
__DEF_Template_SerializerPtr
template <class __BasicType,int __N>
void __DEF_SerializerPtr::__serializeByType(__BasicType data,Int2Type<TYPE_BASIC_TRUNCATE>)
{
	// 截断
	using __Type = typename Byte2Type<__N>::Type;
//	std::cout << "__N" << __N << endl;
	*reinterpret_cast<__Type*>(ptr)=static_cast<__Type>(data);
	ptr+=__N;
}

__DEF_Template_SerializerPtr
template <class __BasicType,int __N>
void __DEF_SerializerPtr::__serializeByType(__BasicType data,Int2Type<TYPE_POINTER_SAFE>) // 复制N个字节的数据，一般情况
{
	static_assert( __EnvTransfer::ptrPolicy() != __EnvTransfer::POLICY_PTR_NOT_ALLOWED,
			"ptr not allowed");
	static_assert( __EnvTransfer::ptrPolicy()!=__EnvTransfer::POLICY_PTR_OBJECT, // TODO 现在不支持序列化对象，因为还没有论证清除
			"ptr object policy not supported yet");
	// DEBUG
//	std::cout << "__N=" << __N << endl;
//	std::cout << reinterpret_cast<size_t>(reinterpret_cast<char*>(data)) << std::endl;
//	std::cout << __EnvTransfer::ptrBase() << std::endl;
	char *p=reinterpret_cast<char*>(data);
	*reinterpret_cast<char* *>(ptr) = ( p==nullptr ?
										nullptr :
										(p - __EnvTransfer::ptrBase())
						) ;
	ptr+=__N;
}

__DEF_Template_SerializerPtr
template <class __BasicType,int __N>
void __DEF_SerializerPtr::__serializeByType(__BasicType data,Int2Type<TYPE_POINTER_TRUNCATE>) // 复制N个字节的数据，一般情况
{
	static_assert( __EnvTransfer::ptrPolicy() != __EnvTransfer::POLICY_PTR_NOT_ALLOWED,
			"ptr not allowed");
	static_assert( __EnvTransfer::ptrPolicy()!=__EnvTransfer::POLICY_PTR_OBJECT, // TODO 现在不支持序列化对象，因为还没有论证清除
			"ptr object policy not supported yet");
//	std::cout << "__N" << __N << endl;
	using __Type = typename Byte2Type<__N>::Type;
	const char *p=reinterpret_cast<const char*>(data);
	*reinterpret_cast<__Type*>(ptr)=static_cast<__Type>(reinterpret_cast<size_t>(
				p==nullptr?nullptr:(p - __EnvTransfer::ptrBase()))  ) ;
//	const char *p= reinterpret_cast<const char*>(data) - __EnvTransfer::ptrBase();
//	cout <<static_cast<int>(reinterpret_cast<size_t>(p));
//	cout << p;
	ptr+=__N;
}

__DEF_Template_SerializerPtr
template <class __BasicType,int __N>
void __DEF_SerializerPtr::__deserializeByType(__BasicType& data,Int2Type<TYPE_BASIC_SAFE>)
{
	//可以安全写入
	using __Type = typename Byte2Type<__N>::Type;
	data = *reinterpret_cast<__Type*>(ptr);
	ptr+=__N;
}
__DEF_Template_SerializerPtr
template <class __BasicType,int __N>
void __DEF_SerializerPtr::__deserializeByType(__BasicType& data,Int2Type<TYPE_BASIC_TRUNCATE>) // 复制N个字节的数据，一般情况
{
	using __Type = typename Byte2Type<__N>::Type;
	data = static_cast<__BasicType>(*reinterpret_cast<__Type*>(ptr));// TODO 调用std::copy实现，同类方法亦然
	ptr+=__N;
}

// UNTESTED
__DEF_Template_SerializerPtr
template <class __BasicType,int __N>
void __DEF_SerializerPtr::__deserializeByType(__BasicType& data,Int2Type<TYPE_POINTER_SAFE>)
{
	static_assert( __EnvTransfer::ptrPolicy() != __EnvTransfer::POLICY_PTR_NOT_ALLOWED,
			"ptr not allowed");
	static_assert( __EnvTransfer::ptrPolicy()!=__EnvTransfer::POLICY_PTR_OBJECT, // TODO 现在不支持序列化对象，因为还没有论证清除
			"ptr object policy not supported yet");

	// DEBUG
//	std::cout << "__N="<<__N<<std::endl;
//	std::cout << reinterpret_cast<size_t>(*reinterpret_cast<char **>(ptr)) << std::endl;
//	std::cout << __EnvTransfer::ptrBase() << std::endl;
	using __Type = typename Byte2Type<__N>::Type;
	char *p=reinterpret_cast<char*>(*reinterpret_cast<__Type*>(ptr));
	data = reinterpret_cast<__BasicType>(
			(p==nullptr?nullptr:(p + __EnvTransfer::ptrBase()))
			);
	ptr+=__N;
}
// UNTESTED
__DEF_Template_SerializerPtr
template <class __BasicType,int __N>
void __DEF_SerializerPtr::__deserializeByType(__BasicType& data,Int2Type<TYPE_POINTER_TRUNCATE>) // 复制N个字节的数据，一般情况
{
	static_assert( __EnvTransfer::ptrPolicy() != __EnvTransfer::POLICY_PTR_NOT_ALLOWED,
			"ptr not allowed");
	static_assert( __EnvTransfer::ptrPolicy()!=__EnvTransfer::POLICY_PTR_OBJECT, // TODO 现在不支持序列化对象，因为还没有论证清除
			"ptr object policy not supported yet");
	using __Type = typename Byte2Type<__N>::Type;
	char *p=reinterpret_cast<char*>(static_cast<size_t>((*reinterpret_cast<__Type*>(ptr))));
	data = reinterpret_cast<__BasicType>(
			( p==nullptr?nullptr:(p + __EnvTransfer::ptrBase())));
	ptr+=__N;
}


#undef __DEF_Template_SerializerPtr
#undef __DEF_SerializerPtr
//***********SerializePtr定义完成===






