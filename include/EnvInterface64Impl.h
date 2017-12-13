/*
 * EnvInterface64Impl.h
 *
 *  Created on: Nov 25, 2017
 *      Author: 13774
 */

#ifndef ENVINTERFACE64IMPL_H_
#define ENVINTERFACE64IMPL_H_

#include <64/MallocToSimple.h>
#include <EnvInterface.h>
#include <string>
#include <vector>
#include <utility>
#include <regex>



class EnvInterface64Impl
{
private:

public:
	using SizeType = size_t;
	enum{Alignment = PREFERED_ALIGNMENT};

	/**
	 * @return 添加文件，返回其驱动器号
	 */
	u8_t addFile(const std::string & file,u32_t lbaBase);
	/**
	 * @return 0xff表明文件不存在
	 */
	u8_t getFileDriver(const std::string & file)const;

	/**
	 * @return ""没有查找到
	 */
	const std::string & getDriverFile(u8_t driver)const;

	EnvInterface64Impl(const EnvInterface64Impl &rhs )=delete;





	/**
	 * @param dstSeg	总是被忽略
	 * @param LBAhigh  总是0
	 * @return 写入的扇区总数
	 */
	int writeSectors(u32_t srcSeg,const u8_t* srcOff,u8_t driver,u32_t LBAlow,u32_t num,u32_t LBAhigh);
	/**
	 * 注：在64位机器上使用fread实现时，由于文件本身的长度有限，可能读到末尾后返回0.这种情况下，应当返回num值以模拟磁盘容量无限的情况。
	 * @param dstSeg	总是被忽略
	 * @param LBAhigh  总是0
	 * @return 读取的扇区总数
	 */
	int readSectors(u32_t dstSeg,u8_t* dstOff,u8_t driver,u32_t LBAlow,u32_t num,u32_t LBAhigh);
	int printf_simple(const char *fmt,int arg0=0,int arg1=0,int arg2=0);
	int printf_sn(const char *s,size_t n);
	u8_t* malloc(size_t size);
	void  free(u8_t* p);


	/**
	 * this can be ignored if there should nothing happens
	 */
	void systemAbort(const char *msg,int code);
	void flushOutputs();


	// 与c标准库协同一致
	char *strcpy(char *s,const char *ct);//ct-->s and return s
	char *strncpy(char *s,const char *ct,size_t n);
	int strncmp(const char *cs,const char *ct,size_t n);
	size_t strlen(const char *cs);
	void *memset(char *s,int c,size_t n);
	void *memcpy(char *s,const char *ct,size_t n);

};


class StdEnv64Impl:
		public EnvInterface64Impl
	{
public:
	using String=std::string;
	template <class T>
	using Allocator=std::allocator<T>;

	template <class T,class A=Allocator<T>>
		using Vector=typename std::vector<T,A>;





public:
	StdEnv64Impl()=default;
};


//===class FsEnv
template <class __SizeType,int __Alignment>
class FsEnv{
public:
	using SizeType = __SizeType;
	enum{Alignment = __Alignment};
};


//== EnvTransfer
namespace{ // 文件局部的namespace，替代c语言的static
namespace Local{ // 真正的文件局部命名空间
template <size_t __TargetBit,class __T>
struct __EnvTransfer
{
	enum{Size=sizeof(__T)};//默认情况下主机长度就是原始长度
};
#if defined(CODE16) //暂时未定义

#elif defined(CODE32USER) ||defined(CODE32)
template <>
	struct __EnvTransfer<64,void*>
	{
		enum{Size=8};//必须写成8而不是sizeof(void*),因为在32位机器上这样的实际结果就是4
	};
	template <>
	struct __EnvTransfer<64,int>
	{
		enum{Size=4};
	};
	template <>
	struct __EnvTransfer<64,size_t> // BUG ??? size_t只是一个别名
	{
		enum{Size=8};
	};
#elif defined(CODE64) //64位机器上对其他机器的类型表现长度
	template <class _T>
	struct __EnvTransfer<32,_T*>
	{
		enum{Size=4};
	};
	template <>
	struct __EnvTransfer<32,int>
	{
		enum{Size=4};
	};
	template <>
	struct __EnvTransfer<32,size_t>
	{
		enum{Size=4};
	};
	template <>
	struct __EnvTransfer<32,long>{ enum{Size=4};};
	template <>
		struct __EnvTransfer<16,void*>
		{
			enum{Size=4};
		};
		template <>
		struct __EnvTransfer<16,int>
		{
			enum{Size=4};
		};
		template <>
		struct __EnvTransfer<16,size_t>
		{
			enum{Size=4};
		};
#endif
}
}
//== 环境转化器：将某一字面量类型（即书写出来的样子）映射到不同的平台上，计算出它的实际大小
//比如 void*在64位机器上是8字节，在32位机器上是4字节。
/**
 * 注意：
 */
template <size_t __TargetBit = HOST_BIT>
struct EnvTransfer{

//	using PtrBaseGetterType = std::function<ptrdiff_t()>;

	/**
	 * 序列化指针时采用的两种不同方案：POLICY_PTR_VALUE表示存储指针相对于一个基地址的偏移值,  POLICY_PTR_OBJECT表示序列化指向的对象
	 */
	enum PtrPolicy{POLICY_PTR_VALUE,POLICY_PTR_OBJECT,POLICY_PTR_NOT_ALLOWED};
	template <class __T> struct SizeofHostType{ //把类当做处理模板的函数
		enum{Size=Local::__EnvTransfer<__TargetBit,__T>::Size };
	};
	template <class __T>
	constexpr static size_t sizeofHostType()
	{
		return Local::__EnvTransfer<__TargetBit,__T>::Size;
	}//把重写放到外部，这里来处理

	/**
	 * 继承的类可以重写这个静态函数来动态配置自己的policy
	 */
	constexpr static PtrPolicy ptrPolicy(){return POLICY_PTR_NOT_ALLOWED;} //默认情况下存储指针值
	AS_MACRO static ptrdiff_t ptrBase(){  //!!!!DEPRECATED注意这里返回的是一个获取函数而不是值
//		return [](){return static_cast<ptrdiff_t>(nullptr);};//默认情况下指针的基地址是0
		return static_cast<ptrdiff_t>(nullptr);
	}
};
///**
// * 此类用于局部对象
// */
//template <size_t __TargetBit>
//struct LocalEnvTransfer:public EnvTransfer<__TargetBit>
//{
//	LocalEnvTransfer():baseAddr(0){}
//	AS_MACRO LocalEnvTransfer(ptrdiff_t addr):baseAddr(addr) //直接返回一个局部值
//	{}
//	ptrdiff_t operator()()
//	{
//		return baseAddr;
//	}
//	AS_MACRO LocalEnvTransfer<__TargetBit> &operator=(ptrdiff_t addr){
//		baseAddr=addr;
//		return *this;
//	}
//private:
//	ptrdiff_t baseAddr;
//};


// DEPRECATED
//// ======= template declaration
//template <class T>
//using MallocToSimple64Impl = MallocToSimple<T,EnvInterface64Impl>;
//using FsEnv16 = FsEnv<u16_t,2>;
//using FsEnv32 = FsEnv<u32_t,4>;
//using FsEnv64 = FsEnv<size_t,PREFERED_ALIGNMENT>;


#endif /* ENVINTERFACE64IMPL_H_ */
