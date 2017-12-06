/*
 * Serialize.h
 *
 *  Created on: Dec 3, 2017
 *      Author: 13774
 */

#ifndef INCLUDE_CONCEPTUAL_SERIALIZE_H_
#define INCLUDE_CONCEPTUAL_SERIALIZE_H_


#include <def.h>
#include <type_traits>
#include <EnvInterface.h>

//===Byte2Type:将字节数目映射到类型
template <size_t __N>
struct Byte2Type{
	//未定义
};
template <>
struct Byte2Type<1>{
	using Type=u8_t;
};

template <>
struct Byte2Type<2>{
	using Type=u16_t;
};

template <>
struct Byte2Type<4>{
	using Type=u32_t;
};

#if defined(CODE64)
template <>
struct Byte2Type<8>{
	using Type=u64_t; // size_t 长度为8
};
template <>
struct Byte2Type<16>{
	using Type=long long;
};
#endif

//template <>
//class Byte2Type<sizeof(size_t)>{
//public:
//	using Type=size_t;
//};

/**
 *  定义一个序列化指针，保证一般的指针，但是围绕此类建立一个概念体系concepts
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
        AS_MACRO __SerializerPtr & operator=(void *p);
        AS_MACRO operator bool()const;
        AS_MACRO operator void*()const;
        AS_MACRO operator void*();
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



        enum{ TYPE_POINTER_SAFE,TYPE_BASIC_SAFE,TYPE_POINTER_TRUNCATE,TYPE_BASIC_TRUNCATE};
        //=========serialize核心实现
        /**
         * @param __BasicType 必须是基本类型，或者至少是pod类型
         * @param __N         目标机器上该类型的长度，由__EnvTransfer的sizeofHostType静态函数决定。
         * 					  该参数被传递到内部__serializeByType实现上
         */
        template <class __BasicType,size_t __N=__EnvTransfer::template sizeofHostType<__BasicType>(),
        		int __AssignType=( sizeof(__BasicType)<=__N ?
        							((std::is_pointer<__BasicType>())?TYPE_POINTER_SAFE:TYPE_BASIC_SAFE):
									((std::is_pointer<__BasicType>())?TYPE_POINTER_TRUNCATE:TYPE_BASIC_TRUNCATE))
									>
        	AS_MACRO void serializeBasicType(__BasicType data);

        template <class __BasicType,size_t __N=__EnvTransfer::template sizeofHostType<__BasicType>(),
        		int __AssignType=( sizeof(__BasicType)>=__N ?
						((std::is_pointer<__BasicType>())?TYPE_POINTER_SAFE:TYPE_BASIC_SAFE):
						((std::is_pointer<__BasicType>())?TYPE_POINTER_TRUNCATE:TYPE_BASIC_TRUNCATE))>
        	AS_MACRO void deserializeBasicType(__BasicType& data);

        // 指针版本，附带偏移参数,忽略环境中指定的参数
        template <size_t __N=__EnvTransfer::template sizeofHostType<const void*>(),
        		int __AssignType=(sizeof(const void*)<=__N)>
        	AS_MACRO void serializeBasicType(/*const*/ void* data,ptrdiff_t diff);

        template <size_t __N=__EnvTransfer::template sizeofHostType<void*>(),
        		int __AssignType=(sizeof(void*)<=__N)>
        	AS_MACRO void deserializeBasicType(void* & data,ptrdiff_t diff);

        // 数组版本
        template <class __BasicType,size_t __N=__EnvTransfer::template sizeofHostType<__BasicType>(),
			int __AssignType=( sizeof(__BasicType)<=__N ?
					((std::is_pointer<__BasicType>())?TYPE_POINTER_SAFE:TYPE_BASIC_SAFE):
					((std::is_pointer<__BasicType>())?TYPE_POINTER_TRUNCATE:TYPE_BASIC_TRUNCATE))>
        	AS_MACRO void serializeBasicType(const __BasicType *data,size_t len);

        template <class __BasicType,size_t __N=__EnvTransfer::template sizeofHostType<__BasicType>(),
			int __AssignType=( sizeof(__BasicType) >= __N ?
					((std::is_pointer<__BasicType>())?TYPE_POINTER_SAFE:TYPE_BASIC_SAFE):
					((std::is_pointer<__BasicType>())?TYPE_POINTER_TRUNCATE:TYPE_BASIC_TRUNCATE))>
        	AS_MACRO void deserializeBasicType(__BasicType *data,size_t len);
private:
	   /**
	    * 一般性实现, __BasicType的尺寸少于__N，直接复制
	    */
        template <class __BasicType,size_t __N>
        AS_MACRO void __serializeByType(__BasicType data,Int2Type<TYPE_BASIC_SAFE>);

        /**
         * 不安全版本， __BasicType需要截断，取其低__N位
         */
        template <class __BasicType,size_t __N>
        AS_MACRO void
			__serializeByType(__BasicType data,Int2Type<TYPE_BASIC_TRUNCATE>) ;// 复制N个字节的数据，一般情况

        /**
		* 一般性实现, __BasicType的尺寸少于__N，直接复制
		*/
		 template <class __BasicType,size_t __N>
		 AS_MACRO void __serializeByType(__BasicType data,Int2Type<TYPE_POINTER_SAFE>);

		 /**
		  * 不安全版本， __BasicType需要截断，取其低__N位
		  */
		 template <class __BasicType,size_t __N>
		 AS_MACRO void
			__serializeByType(__BasicType data,Int2Type<TYPE_POINTER_TRUNCATE>) ;// 复制N个字节的数据，一般情况


        // __N大
         template <class __BasicType,size_t __N>
         AS_MACRO void __deserializeByType(__BasicType& data,Int2Type<TYPE_BASIC_SAFE>);

         	// __BasicType大
         template <class __BasicType,size_t __N>
         AS_MACRO void
		 	 __deserializeByType(__BasicType& data,Int2Type<TYPE_BASIC_TRUNCATE>); // 复制N个字节的数据，一般情况
         // __N大
              template <class __BasicType,size_t __N>
              AS_MACRO void __deserializeByType(__BasicType& data,Int2Type<TYPE_POINTER_SAFE>);

              	// __BasicType大
              template <class __BasicType,size_t __N>
              AS_MACRO void
     		 	 __deserializeByType(__BasicType& data,Int2Type<TYPE_POINTER_TRUNCATE>); // 复制N个字节的数据，一般情况

private:
         /**
          * 保持该类的简洁性，不过，如果添加更多成员参数，则可以实现更好的operator<<语义
          * 比如std::cout << std::endl, std::endl就是一个特殊语义。
          * 不过，我想有一种更好地在二元操作符上传递其他参数的办法，如果placement new那样：
          *  ptr << %<int,bool>(2,3)% mem;  其含义是调用operator<<(ptr,mem,int,bool)， 这样可以实现二元操作符对任意实参的需求
          */
        u8_t *ptr;
};
/**
 * 一个接口规范
* 默认情况下，所有其他类型调用 ptr<<otherTypes， 都会被转发到这里，但是此处使用的实现对于非pod类型会报编译错误，
* 	因此对于自己定义的可序列化对象，最好实现SerializationInterface接口的方法并通过重载operator>>,operator<<来完成
* 	当然，严格意义上来说只要重载了operator<<,operator>>即可.
*
*
* 实现该接口的原因是为了避免重写地将operatr<<,operator>>声明为
* 类的友元
*/
class SerializationInterface{
public:
#if defined(IDE_MODE) //为了防止无意中使用虚指针或者继承
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

	/**
	 * 提供序列化所需的空间大小.
	 * constexpr是可选的
	 */
	template <class __EnvTransfer>
		constexpr size_t getSerializitionSize();
#endif
};

namespace{  //文件局部帮助函数，用于选择要使用的函数
		//如果是基本类型，就调用SerializePtr内部

		template <class __S,class __EnvTransfer> //true goes here
		AS_MACRO SerializerPtr<__EnvTransfer>&
			__serializeHelper(SerializerPtr<__EnvTransfer>& p,const __S &s,Int2Type<true>)
		{
			p.serializeBasicType(s);
			return p;
		}

		template <class __S,class __EnvTransfer>
		AS_MACRO SerializerPtr<__EnvTransfer>&
			__serializeHelper(SerializerPtr<__EnvTransfer>& p,const __S &s,Int2Type<false>) // false goes here
		{
			return s.serialize(p);
		}

		template <class __S,class __EnvTransfer> //true goes here
		AS_MACRO SerializerPtr<__EnvTransfer>&
			__deserializeHelper(SerializerPtr<__EnvTransfer>& p,__S &s,Int2Type<true>)
		{
			p.deserializeBasicType(s);
			return p;
		}

		template <class __S,class __EnvTransfer>
		AS_MACRO SerializerPtr<__EnvTransfer>&
			__deserializeHelper(SerializerPtr<__EnvTransfer>& p,__S &s,Int2Type<false>) // false goes here
		{
			return s.deserialize(p);
		}


}
//====两个全局的 >>表示序列化语义函数,与SerializationInterface配合使用
// 对于基本类型，调用SerializePtr的内部操作；
// 对于其他复杂/自定义类型,调用其接口实现
/**
 * @param s  序列化对象
 * @param p  序列化指针地址
 * @return 返回下一个可用的地址
 */
template <class __S,class __EnvTransfer>
AS_MACRO SerializerPtr<__EnvTransfer>& operator<<(SerializerPtr<__EnvTransfer>& p,const __S &s)
{
	// 通过is_pod做出转发选择
	return __serializeHelper<__S,__EnvTransfer>(p, s,Int2Type<std::is_pod<__S>::value>());
}
/**
 * @param s  反序列化对象
 * @param p  序列化指针地址
 * @return 返回下一个可用的地址
 */
template <class __S,class __EnvTransfer>
AS_MACRO  SerializerPtr<__EnvTransfer>& operator>>(SerializerPtr<__EnvTransfer>& p,__S &s)
{
	return __deserializeHelper<__S,__EnvTransfer>(p, s,Int2Type<std::is_pod<__S>::value>());
}

#if defined(CODE64)
//对系统级Vector,String等的特化，实际上可以选择使用迭代器
template <class __T,class __EnvTransfer>
AS_MACRO SerializerPtr<__EnvTransfer>& operator<<(SerializerPtr<__EnvTransfer>& p, HostEnv::Vector<__T> &s)
{
	p << s.size();
	for(auto & i : s)
		p << i;
	return p;
}
template <class __T,class __EnvTransfer>
AS_MACRO  SerializerPtr<__EnvTransfer>& operator>>(SerializerPtr<__EnvTransfer>& p,HostEnv::Vector<__T> &s)
{
	decltype(s.size()) size=0;
	p >> size;
	s.resize(size); //TODO 测试resize是否成功
	for(decltype(size) i=0;i!=size;++i)
		p >> s[i];
	return p;
}
#endif


#endif /* INCLUDE_CONCEPTUAL_SERIALIZE_H_ */
