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
#include <regex>


class EnvInterface64Impl
#if defined(IDE_MODE)
	:public EnvInterface
#endif
{
protected:
	const char *file;
	static EnvInterface64Impl * env;
	EnvInterface64Impl(const char *file);
public:

	static EnvInterface64Impl *getInstance(const char *file);

	EnvInterface64Impl(const EnvInterface64Impl &rhs )=delete;


		enum{
		/**
		 * 必须根据磁盘文件的第一个active分区的起始地址设定
		 */
		LBABASE = 0x3000,
	};
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
	using string=std::string;

	template <class T,class A>
		using vector=typename std::vector<T,A>;

	template <class T>
	using allocator=std::allocator<T>;

	std::vector<std::string> regexSplit(const std::regex& re, const std::string& s);
	std::vector<std::string> spaceSplit(const std::string& s);

public:
	static StdEnv64Impl * getInstance(const char *file);

protected:
	static StdEnv64Impl * env;

	StdEnv64Impl(const char *file);
};

// ======= template declaration
template <class T>
using MallocToSimple64Impl = MallocToSimple<T,EnvInterface64Impl>;



#endif /* ENVINTERFACE64IMPL_H_ */
