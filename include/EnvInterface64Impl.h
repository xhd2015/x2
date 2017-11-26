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


class EnvInterface64Impl
#if defined(IDE_MODE)
	:public EnvInterface
#endif
{
private:
	static EnvInterface64Impl * env;
	static const char *file;
	EnvInterface64Impl()=default;
public:
	static EnvInterface64Impl *getInstance();
	static void					setHDDFile(const char *file);
		/**
		 * 总是使用一个文件来作为驱动器
		 */
#define DRIVER_TO_FILE  "hdd.img"
		enum{
		/**
		 * 必须根据磁盘文件的第一个active分区的起始地址设定
		 */
		LBABASE = 0x3000,
	};
	/**
	 * @param dstSeg	总是被忽略
	 * @param LBAhigh  总是0
	 */
	int writeSectors(u32_t srcSeg,const u8_t* srcOff,u8_t driver,u32_t LBAlow,u32_t num,u32_t LBAhigh);
	/**
	 * @param dstSeg	总是被忽略
	 * @param LBAhigh  总是0
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

template <class T>
using MallocToSimple64Impl = MallocToSimple<T,EnvInterface64Impl>;



#endif /* ENVINTERFACE64IMPL_H_ */
