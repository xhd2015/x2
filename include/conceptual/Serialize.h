/*
 * Serialize.h
 *
 *  Created on: Dec 3, 2017
 *      Author: 13774
 */

#ifndef INCLUDE_CONCEPTUAL_SERIALIZE_H_
#define INCLUDE_CONCEPTUAL_SERIALIZE_H_


#include <def.h>


//===Byte2Type:将字节数目映射到类型
template <size_t __N>
class Byte2Type{
public: //未定义
};

template <>
class Byte2Type<1>{
public:
	using Type=u8_t;
};

template <>
class Byte2Type<2>{
public:
	using Type=u16_t;
};

template <>
class Byte2Type<4>{
public:
	using Type=u32_t;
};

template <>
class Byte2Type<8>{
public:
	using Type=u64_t; // size_t 长度为8
};

//template <>
//class Byte2Type<sizeof(size_t)>{
//public:
//	using Type=size_t;
//};

/**
 * 要求被序列化的类提供： size_t serialize()const函数,返回值用于确定占据的空间，deserialize()函数同理
 *
 * 对一般的内置类型提供内置的序列化操作：int, const char[],以及指针。注意指针和数组的区别。
 */
template <class __EnvTransfer>
class SerializerPtr{
public:
	using This = SerializerPtr<__EnvTransfer>;
	using __SerializerPtr = This;
    public:
		AS_MACRO SerializerPtr(void *p);
        AS_MACRO void *getPtr()const;
        AS_MACRO __SerializerPtr & operator=(const __SerializerPtr &rhs);
        AS_MACRO operator bool()const;
        AS_MACRO operator void*()const;
        /**
         * 如果指针为nullptr，则仍然返回nullptr
         */
        AS_MACRO __SerializerPtr  operator+(ptrdiff_t pdiff)const;
        /**
         * 如果指针为nullptr，则仍然返回nullptr
         */
        AS_MACRO __SerializerPtr  operator-(ptrdiff_t pdiff)const;
        AS_MACRO __SerializerPtr&  operator+=(ptrdiff_t pdiff);
        AS_MACRO __SerializerPtr&  operator-=(ptrdiff_t pdiff);


        //=========serialize核心实现
        template <class __BasicType,size_t __N,bool __SafeAssign=(sizeof(__BasicType)<=__N)>
        AS_MACRO void serializeByType(__BasicType data);
        template <class __BasicType,size_t __N,bool __SafeAssign=(sizeof(__BasicType)<=__N)>
        AS_MACRO void deserializeByType(__BasicType& data);
private:
	   /**
	    * 一般性实现, __BasicType的尺寸少于__N，直接复制
	    */
        template <class __BasicType,size_t __N>
        AS_MACRO void __serializeByType(__BasicType data,Int2Type<true>);

        /**
         * 不安全版本， __BasicType需要截断，取其低__N位
         */
        template <class __BasicType,size_t __N>
        AS_MACRO void
			__serializeByType(__BasicType data,Int2Type<false>) ;// 复制N个字节的数据，一般情况

        // __N大
         template <class __BasicType,size_t __N>
         AS_MACRO void __deserializeByType(__BasicType& data,Int2Type<true>);

         	// __BasicType大
         template <class __BasicType,size_t __N>
         AS_MACRO void
		 	 __deserializeByType(__BasicType& data,Int2Type<false>); // 复制N个字节的数据，一般情况

public:
        template <class __BasicType>
         AS_MACRO     __SerializerPtr & operator<<(__BasicType s);//基本类型
        template <class __BasicType>
          AS_MACRO    __SerializerPtr & operator>>(__BasicType& s);//基本类型

private:
        u8_t *ptr;
};

/**
 * 一个接口规范
 */
class SerializationInterface{
public:
#if defined(IDE_MODE) //为了防止无意中使用虚指针
	/**
	 * @param __EnvTransfer  提供从主机环境到目标环境的类型转换。参见EnvTransfer
	 *
	 */
	template <class __EnvTransfer>
		SerializerPtr<__EnvTransfer>& serialize(SerializerPtr<__EnvTransfer> &ptr)const;
	/**
	 * @param __EnvTransfer 提供从目标环境到主机环境的类型转换
	 */
	template <class __EnvTransfer>
		SerializerPtr<__EnvTransfer>& deserialize(SerializerPtr<__EnvTransfer> &ptr);
#endif
};


//====两个全局的 >>表示序列化语义函数
///**
// * @param s  序列化对象
// * @param p  序列化指针地址
// * @return 返回下一个可用的地址
// */
//template <class __S,class __EnvTransfer>
//AS_MACRO SerializerPtr<__EnvTransfer>& operator<<(SerializerPtr<__EnvTransfer>& p,const __S &s);
///**
// * @param s  反序列化对象
// * @param p  序列化指针地址
// * @return 返回下一个可用的地址
// */
//template <class __S,class __EnvTransfer>
//AS_MACRO  SerializerPtr<__EnvTransfer>& operator>>(SerializerPtr<__EnvTransfer>& p,__S &s);


#endif /* INCLUDE_CONCEPTUAL_SERIALIZE_H_ */
