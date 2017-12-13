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
#include <conceptual/loki/Int2Type.h>
#include <conceptual/ExtFunctional.h>

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
 * 	对一般的内置类型提供内置的序列化操作,对于指针，不序列化其值，而是序列化其指向的对象。
 *
 * 	对任何对象：如果序列化所占用的空间为N，则反序列化所使用的空间必然为N。这是最重要的保证。
 */
template <class __EnvTransfer>
class SerializerPtr{
public:
	using This = SerializerPtr<__EnvTransfer>;
	using __SerializerPtr = This;
    public:
		SerializerPtr()=default;
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



        // UPDATE: 不允许序列化指针，因为语义上指针是没有意义的。
        enum Policy{ TYPE_POINTER_SAFE,TYPE_BASIC_SAFE,TYPE_POINTER_TRUNCATE,TYPE_BASIC_TRUNCATE};
        //=========serialize核心实现
        /**
         * @param __BasicType 必须是基本类型，或者至少是pod类型
         * @param __N         目标机器上该类型的长度，由__EnvTransfer的sizeofHostType静态函数决定。
         * 					  该参数被传递到内部__serializeByType实现上
         */
        template <class __BasicType>
        	AS_MACRO void serializeBasicType(__BasicType data);

        template <class __BasicType>
        	AS_MACRO void deserializeBasicType(__BasicType& data);

        // DEBUGGING 下面这两个函数不应当被调用
        // 指针版本，附带偏移参数,忽略环境中指定的参数
        	AS_MACRO DEPRECATED void serializeBasicType(/*const*/ void* data,ptrdiff_t diff);

        	AS_MACRO DEPRECATED void deserializeBasicType(void* & data,ptrdiff_t diff);

        // 数组版本
        template <class __BasicType>
        	AS_MACRO void serializeBasicType(const __BasicType *data,size_t len);

        template <class __BasicType>
        	AS_MACRO void deserializeBasicType(__BasicType *data,size_t len);
private:
        // 注：下面的所有函数参数__N表示序列化过后指针移动的偏移，可正可负
        // Int2Type<int> 用于选择相应的Policy
	   /**
	    * 一般性实现, __BasicType的尺寸少于__N，直接复制
	    */
        template <class __BasicType,int __N>
        AS_MACRO void __serializeByType(__BasicType data,Int2Type<TYPE_BASIC_SAFE>);

        /**
         * 不安全版本， __BasicType需要截断，取其低__N位
         */
        template <class __BasicType,int __N>
        AS_MACRO void
			__serializeByType(__BasicType data,Int2Type<TYPE_BASIC_TRUNCATE>) ;// 复制N个字节的数据，一般情况

        /**
		* 一般性实现, __BasicType的尺寸少于__N，直接复制
		*/
		 template <class __BasicType,int __N>
		 AS_MACRO void __serializeByType(__BasicType data,Int2Type<TYPE_POINTER_SAFE>);

		 /**
		  * 不安全版本， __BasicType需要截断，取其低__N位
		  */
		 template <class __BasicType,int __N>
		 AS_MACRO void
			__serializeByType(__BasicType data,Int2Type<TYPE_POINTER_TRUNCATE>) ;// 复制N个字节的数据，一般情况


        // __N大
         template <class __BasicType,int __N>
         AS_MACRO void __deserializeByType(__BasicType& data,Int2Type<TYPE_BASIC_SAFE>);

         	// __BasicType大
         template <class __BasicType,int __N>
         AS_MACRO void
		 	 __deserializeByType(__BasicType& data,Int2Type<TYPE_BASIC_TRUNCATE>); // 复制N个字节的数据，一般情况
         // __N大
              template <class __BasicType,int __N>
              AS_MACRO void __deserializeByType(__BasicType& data,Int2Type<TYPE_POINTER_SAFE>);

              	// __BasicType大
              template <class __BasicType,int __N>
              AS_MACRO void
     		 	 __deserializeByType(__BasicType& data,Int2Type<TYPE_POINTER_TRUNCATE>); // 复制N个字节的数据，一般情况


              template <class __BasicType>
             static constexpr size_t hostTypeSize(){
            	  	 return __EnvTransfer::template sizeofHostType<__BasicType>();
              }
              /**
               * 返回basicType的序列化规则
               */
            template <class __BasicType>
           static constexpr Policy bscTpSrlzPolicy()
            {
            	 return (sizeof(__BasicType)<= hostTypeSize<__BasicType>() ?
            						((std::is_pointer<__BasicType>())?TYPE_POINTER_SAFE:TYPE_BASIC_SAFE):
            						((std::is_pointer<__BasicType>())?TYPE_POINTER_TRUNCATE:TYPE_BASIC_TRUNCATE));
            }
            /**
             * 返回basicType的反序列化规则
             */
            template <class __BasicType>
          static constexpr Policy bscTpDesrlzPolicy()
            {
            	return (sizeof(__BasicType) >= hostTypeSize<__BasicType>() ?
            						((std::is_pointer<__BasicType>())?TYPE_POINTER_SAFE:TYPE_BASIC_SAFE):
            						((std::is_pointer<__BasicType>())?TYPE_POINTER_TRUNCATE:TYPE_BASIC_TRUNCATE));
            }

private:
         /**
          * 保持该类的简洁性，不过，如果添加更多成员参数，则可以实现更好的operator<<语义
          * 比如std::cout << std::endl, std::endl就是一个特殊语义。
          * 不过，我想有一种更好地在二元操作符上传递其他参数的办法，如果placement new那样：
          *  ptr << %<int,bool>(2,3)% mem;  其含义是调用operator<<(ptr,mem,int,bool)， 这样可以实现二元操作符对任意实参的需求
          */
        u8_t *ptr {nullptr };
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
*
* 注：non-virtual
* 因为模板不能virtual
*/
class SerializationInterface{
protected:
	~SerializationInterface()=default;
public:
	enum GlobalCallPolicy{  CALL_BUILTIN, // pod本身
							CALL_CLASS_METHOD,  // 普通的实现类使用，如果不重载默认使用此
							CALL_GLOBAL_HELPER // virtual的类使用,该类只能使用指针吗？非也，至少序列化使用指针是安全的。
	};
//	virtual ~SerializationInterface()=default;
//#if defined(IDE_MODE)
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
		constexpr size_t getSerializitionSize()const;

	// 默认情况下选择成员函数或者内置类型
	// 只有为virtual时选择全局
	static constexpr GlobalCallPolicy callPolicy(){
		return CALL_CLASS_METHOD;
	}
//#endif
};

class DefaultConstructable{}; //一个接口，表明类可以被默认初始化

namespace{  //文件局部帮助函数，用于选择要使用的函数

		//如果是基本类型，就调用SerializePtr内部
#define __DEF_Template_Helper template <class __EnvTransfer,class __S>

		enum OBJ_TYPE{ POINTER,OBJECT };

		// works when std::conditional does not work
		template <class __S,bool __NonPointerPodType> // true pod&not pointer type
		struct __CallPolicyHelper{
			static constexpr SerializationInterface::GlobalCallPolicy
				value = SerializationInterface::CALL_BUILTIN;
		};
		template <class __S>
		struct __CallPolicyHelper<__S,false>{
			static constexpr SerializationInterface::GlobalCallPolicy
				value = __S::callPolicy();
		};
		template <class __S>
		struct __CallPolicyGetter:public __CallPolicyHelper<__S,std::is_pod<__S>::value>{};

		// 最多一级指针
		template <class __S> //==true pod type, including pointer
		struct __PolicyGetter:public PointerAsObject<__S> {
		private:
			template <class __Tp>
				using rp_t = typename std::remove_pointer<__Tp>::type;
			template <class __Tp>
				using is_p_topod = std::is_pod<rp_t<__Tp>>;
			template <SerializationInterface::GlobalCallPolicy __Value>
				using PolicyType2Value = Type2Value<SerializationInterface::GlobalCallPolicy,__Value>;
		public:
			static constexpr bool isPointer = std::is_pointer<__S>::value;
			using ObjectType =typename PointerAsObject<__S>::Object;
			static constexpr SerializationInterface::GlobalCallPolicy
				policy = __CallPolicyGetter<ObjectType>::value;
		};

		// == 前置函数声明
//		__DEF_Template_Helper
//				AS_MACRO SerializerPtr<__EnvTransfer>&
//					__serializeHelperGlobalHelper(SerializerPtr<__EnvTransfer>& p,const __S& s,Int2Type<true>);
//		__DEF_Template_Helper
//				AS_MACRO SerializerPtr<__EnvTransfer>&
//					__serializeHelperGlobalHelper(SerializerPtr<__EnvTransfer>& p,const __S& s,Int2Type<false>);
//		__DEF_Template_Helper
//				AS_MACRO SerializerPtr<__EnvTransfer>&
//					__deserializeHelperGlobalHelper(SerializerPtr<__EnvTransfer>& p,__S& s,Int2Type<true>);
//		__DEF_Template_Helper
//				AS_MACRO SerializerPtr<__EnvTransfer>&
//					__deserializeHelperGlobalHelper(SerializerPtr<__EnvTransfer>& p,__S& s,Int2Type<false>);
//		__DEF_Template_Helper
//			AS_MACRO SerializerPtr<__EnvTransfer>&
//				__serializeHelper(SerializerPtr<__EnvTransfer>& p,const __S &s,
//						Int2Type<SerializationInterface::CALL_CLASS_METHOD>);
//		__DEF_Template_Helper
//			AS_MACRO SerializerPtr<__EnvTransfer>&
//				__deserializeHelper(SerializerPtr<__EnvTransfer>& p,const __S &s,
//						Int2Type<SerializationInterface::CALL_CLASS_METHOD>);
//		__DEF_Template_Helper
//		AS_MACRO size_t
//			__getSizeHelperGlobalHelper(const __S &s,Int2Type<true>);
//		__DEF_Template_Helper
//		AS_MACRO size_t
//			__getSizeHelperGlobalHelper(const __S &s,Int2Type<false>);
//		__DEF_Template_Helper
//		AS_MACRO size_t
//			__getSizeHelper(const __S &s,Int2Type<SerializationInterface::CALL_CLASS_METHOD>);




			__DEF_Template_Helper //true goes here
			AS_MACRO SerializerPtr<__EnvTransfer>&
			__serializeHelper(SerializerPtr<__EnvTransfer>& p,const __S &s,
						Int2Type<SerializationInterface::CALL_BUILTIN>)
			{
				p.serializeBasicType(__PolicyGetter<__S>::defference(s));
				return p;
			}

		__DEF_Template_Helper
		AS_MACRO SerializerPtr<__EnvTransfer>&
			__serializeHelper(SerializerPtr<__EnvTransfer>& p,const __S &s,
					Int2Type<SerializationInterface::CALL_CLASS_METHOD>)
		{
			return 	__PolicyGetter<__S>::defference(s).serialize(p);
		}
		__DEF_Template_Helper
		AS_MACRO SerializerPtr<__EnvTransfer>&
			__serializeHelperGlobalHelper(SerializerPtr<__EnvTransfer>& p,const __S& s,Int2Type<true>) //isPointer
			{
				return serialize(p,__PolicyGetter<__S>::address(s));
			}
		__DEF_Template_Helper
		AS_MACRO SerializerPtr<__EnvTransfer>&
			__serializeHelperGlobalHelper(SerializerPtr<__EnvTransfer>& p,const __S& s,Int2Type<false>) //not Pointer
			{
				return __serializeHelper(p, s,Int2Type<SerializationInterface::CALL_CLASS_METHOD>());
			}

		// 对于指针，我们希望的是其指向的对象不可变
		// 对于对象引用，我们希望的是其对象不变
		__DEF_Template_Helper
		AS_MACRO SerializerPtr<__EnvTransfer>&
		__serializeHelper(SerializerPtr<__EnvTransfer>& p,const __S& s,
					Int2Type<SerializationInterface::CALL_GLOBAL_HELPER>)
		{
				return __serializeHelperGlobalHelper(p, s, Int2Type<__PolicyGetter<__S>::isPointer>());
		}


		__DEF_Template_Helper
		AS_MACRO SerializerPtr<__EnvTransfer>&
			__deserializeHelper(SerializerPtr<__EnvTransfer>& p,__S &s,
					Int2Type<SerializationInterface::CALL_BUILTIN>)
		{
			p.deserializeBasicType(__PolicyGetter<__S>::defference(s));
			return p;
		}
		__DEF_Template_Helper
		AS_MACRO SerializerPtr<__EnvTransfer>&
			__deserializeHelper(SerializerPtr<__EnvTransfer>& p,__S &s,
					Int2Type<SerializationInterface::CALL_CLASS_METHOD>)
		{
			return 	__PolicyGetter<__S>::defference(s).deserialize(p);
		}
		__DEF_Template_Helper
		AS_MACRO SerializerPtr<__EnvTransfer>&
			__deserializeHelperGlobalHelper(SerializerPtr<__EnvTransfer>& p,__S& s,Int2Type<true>) //isPointer
			{
				return deserialize(p,__PolicyGetter<__S>::address(s));
			}
		__DEF_Template_Helper
		AS_MACRO SerializerPtr<__EnvTransfer>&
			__deserializeHelperGlobalHelper(SerializerPtr<__EnvTransfer>& p,__S& s,Int2Type<false>) //not Pointer
			{
				return __deserializeHelper(p, s,Int2Type<SerializationInterface::CALL_CLASS_METHOD>());
			}
		__DEF_Template_Helper
		SerializerPtr<__EnvTransfer>&
			__deserializeHelper(SerializerPtr<__EnvTransfer>& p,__S &s,
					Int2Type<SerializationInterface::CALL_GLOBAL_HELPER>)
		{
//			static_assert(__PolicyGetter<__S>::isPointer,"cannot deserialize virtual type directly");
			return __deserializeHelperGlobalHelper(p,s,Int2Type<__PolicyGetter<__S>::isPointer>());
		}


		__DEF_Template_Helper //true goes here
		AS_MACRO size_t
			__getSizeHelper(const __S &s,Int2Type<SerializationInterface::CALL_BUILTIN>)
		{
			return __EnvTransfer::template sizeofHostType<typename
						__PolicyGetter<__S>::ObjectType>();
		}

		__DEF_Template_Helper
		AS_MACRO size_t
			__getSizeHelper(const __S &s,Int2Type<SerializationInterface::CALL_CLASS_METHOD>) // false goes here
		{
			return __PolicyGetter<__S>::defference(s).template getSerializitionSize<__EnvTransfer>();
		}
		__DEF_Template_Helper
		AS_MACRO size_t
			__getSizeHelperGlobalHelper(const __S &s,Int2Type<true>)
		{
			return getSerializitionSize(__PolicyGetter<__S>::address(s));//函数调用
		}
		__DEF_Template_Helper
		AS_MACRO size_t
			__getSizeHelperGlobalHelper(const __S &s,Int2Type<false>)
		{
			return __getSizeHelper(s, Int2Type<SerializationInterface::CALL_CLASS_METHOD>());//函数调用
		}
		__DEF_Template_Helper
		AS_MACRO size_t
			__getSizeHelper(const __S &s,Int2Type<SerializationInterface::CALL_GLOBAL_HELPER>)
		{
			return __getSizeHelperGlobalHelper(s,Int2Type<__PolicyGetter<__S>::isPointer>());
		}

		__DEF_Template_Helper //true goes here
		AS_MACRO size_t __getSizeHelper(Int2Type<SerializationInterface::CALL_BUILTIN>)
		{
			return __EnvTransfer::template sizeofHostType<typename __PolicyGetter<__S>::ObjectType>();
		}
}
//====两个全局的 >>表示序列化语义函数,与SerializationInterface配合使用
// 对于基本类型，调用SerializePtr的内部操作；
// 对于其他复杂/自定义类型,调用其接口实现
/**
 * @brief 全局序列化函数
 * @param s  序列化对象
 * @param p  序列化指针地址
 * @return 返回下一个可用的地址
 *
 * s是一个对象 -- 可行
 * s是一个指针 const F* &s, 应当const F* &s
 */
__DEF_Template_Helper
AS_MACRO SerializerPtr<__EnvTransfer>& operator<<(SerializerPtr<__EnvTransfer>& p,const __S &s)
{
	// __S可取两种状态： const Object &, const Object *
	// 如果是基本类型，还可以区 Object
	// 通过is_pod做出转发选择
	return 	__serializeHelper(p,s,Int2Type<__PolicyGetter<__S>::policy>());
}

/**
 * @param s  反序列化对象
 * @param p  序列化指针地址
 * @return 返回下一个可用的地址
 */
__DEF_Template_Helper
AS_MACRO  SerializerPtr<__EnvTransfer>& operator>>(SerializerPtr<__EnvTransfer>& p,__S &s)
{
	return 	__deserializeHelper(p,s,Int2Type<__PolicyGetter<__S>::policy>());
}
/**
 * 全局getSerializitionSize 函数：动态版本
 */
__DEF_Template_Helper
AS_MACRO  size_t getSerializitionSize(const __S &s)
{
	return __getSizeHelper<__EnvTransfer,__S>(s,Int2Type<__PolicyGetter<__S>::policy>());
}
/**
 * 全局getSerializitionSize函数：静态版本
 */
__DEF_Template_Helper
constexpr size_t getSerializitionSize()
{
	return __getSizeHelper<__EnvTransfer,__S>(Int2Type<__PolicyGetter<__S>::policy>());
}

//====序列化指针为右值的版本
__DEF_Template_Helper
AS_MACRO SerializerPtr<__EnvTransfer>&& operator<<(SerializerPtr<__EnvTransfer>&& p,const __S &s)
{
//	SerializerPtr<__EnvTransfer> myPtr = p;//一个临时对象绑定，把所有的匿名需求转换到这里
//	return std::move(__serializeHelper(p,&s,Int2Type<__getSerializitionPolicy<__S>()>()));//返回同一地址的右值引用
	return std::move( p << s); //调用相应的左值版本
}
__DEF_Template_Helper
AS_MACRO  SerializerPtr<__EnvTransfer>&& operator>>(SerializerPtr<__EnvTransfer>&& p,__S &s)
{
//	SerializerPtr<__EnvTransfer> myPtr=p;
//	return std::move( __deserializeHelper(p,&s,Int2Type<__getSerializitionPolicy<__S>()>()));//返回同一地址的右值引用
	return std::move( p >> s);
}


#undef __DEF_Template_Helper

//===对系统级Vector,String等的特化，实际上可以选择使用迭代器
//==Vector
template <class __EnvTransfer,class __T>
AS_MACRO SerializerPtr<__EnvTransfer>& operator<<(SerializerPtr<__EnvTransfer>& p,const HostEnv::Vector<__T> &s)
{
	p << s.size();
	for(auto & i : s)
		p << i;
	return p;
}

template <class __EnvTransfer,class __T>
AS_MACRO  SerializerPtr<__EnvTransfer>& operator>>(SerializerPtr<__EnvTransfer>& p,HostEnv::Vector<__T> &s)
{
	decltype(s.size()) size=0;
	p >> size;
	s.resize(size); //TODO 测试resize是否成功
	for(decltype(size) i=0;i!=size;++i)
		p >> s[i];
	return p;
}

template <class __EnvTransfer,class __T>
AS_MACRO  size_t getSerializitionSize(const HostEnv::Vector<__T> &s)
{
	size_t size= getSerializitionSize<__EnvTransfer,decltype(s.size())>();
	for(decltype(size) i=0;i!=size;++i)
		size+= getSerializitionSize<__EnvTransfer,__T>(s[i]); //尽量采用指针的方式吗？
	return size;
}

//== const char * , 可以使用String进行反序列化
template <class __EnvTransfer>
SerializerPtr<__EnvTransfer>& operator<<(SerializerPtr<__EnvTransfer>& p, const char* s)
{
	using SizeType =typename  HostEnv::String::size_type;
	p << SizeType(strlen(s));
	while(*s)
		p << *s++;
	return p;
}

template <class __EnvTransfer>
size_t getSerializitionSize(const char *s)
{
	return getSerializitionSize<__EnvTransfer,typename  HostEnv::String::size_type>() +
			strlen(s)*getSerializitionSize<__EnvTransfer,decltype(s[0])>();
}



//==String
template <class __EnvTransfer>
SerializerPtr<__EnvTransfer>& operator<<(SerializerPtr<__EnvTransfer>& p, const HostEnv::String &s)
{
	p << s.size();
	for(auto & i : s)
		p << i;
	return p;
}

template <class __EnvTransfer>
SerializerPtr<__EnvTransfer>& operator>>(SerializerPtr<__EnvTransfer>& p,HostEnv::String &s)
{
	decltype(s.size()) size=0;
	p >> size;
	s.resize(size); //TODO 测试resize是否成功
	for(decltype(size) i=0;i!=size;++i)
		p >> (s[i]);
	return p;
}
template <class __EnvTransfer>
size_t getSerializitionSize(const HostEnv::String &s)
{
	size_t size= getSerializitionSize<__EnvTransfer,decltype(s.size())>();
	for(decltype(size) i=0;i!=s.size();++i)
		size += getSerializitionSize<__EnvTransfer,typename HostEnv::String::value_type>(s[i]);
	return size;
}

#endif /* INCLUDE_CONCEPTUAL_SERIALIZE_H_ */
