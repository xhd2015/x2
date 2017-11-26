/*
 * EnvInterface.h
 *
 *  Created on: Nov 25, 2017
 *      Author: 13774
 */

#ifndef ENVINTERFACE_H_
#define ENVINTERFACE_H_

#include <def.h>

#define ABORT_PTR_NULL "pointer is NULL"
#define ABORT_PTR_NULL_CODE -1
/**
 * 定义所有文件系统需要用到的操作系统功能
 */
class EnvInterface{
private:
		EnvInterface()=default;
		virtual ~EnvInterface()=default;
public:
	enum{
		/**
		 * 默认使用当前段
		 */
		CUR_SEG = 0x10000u,
	};

	 // NOTE 检查下面的=0在没有virtual的情况下能否用，IDE没有报错
	// 不能使用
	int writeSectors(u32_t srcSeg,const u8_t* srcOff,u8_t driver,u32_t LBAlow,u32_t num,u32_t LBAhigh);
	int readSectors(u32_t dstSeg,u8_t* dstOff,u8_t driver,u32_t LBAlow,u32_t num,u32_t LBAhigh);
	/**
	 * 不支持除%d以外的其他任何格式化参数
	 * 不要使用%s,%x,%p等
	 */
//	 __attribute__ ((format (printf, 1, 2)))
	int printf_simple(const char *fmt,int arg0=0,int arg1=0,int arg2=0);
	int printf_sn(const char *s,size_t n);
	u8_t* malloc(size_t size);
	void  free(u8_t* p);


	/**
	 * this can be ignored if there should nothing happens
	 */
	void systemAbort(const char *msg,int code);
	/**
	 * 将所有的输出立即写出
	 * 用于系统崩溃时，确保用户看到信息
	 */
	void flushOutputs();


	// 与c标准库协同一致
	char *strcpy(char *s,const char *ct);//ct-->s and return s
	char *strncpy(char *s,const char *ct,size_t n);
	int strncmp(const char *cs,const char *ct,size_t n);
	size_t strlen(const char *cs);
	void *memset(char *s,int c,size_t n);
	void *memcpy(char *,const char *ct,size_t n);

};



//size_t EnvInterface::strlen(const char* s) //应当报错
//{
//	if(s==NULL)
//		systemAbort(ABORT_PTR_NULL,ABORT_PTR_NULL_CODE);
//	size_t l=0;
//	while(*s++!=0)l++;
//	return l;
//}
//
//size_t EnvInterface::strncpy(char *p,const char *from,size_t len)
//{
//	if(p==NULL || from==NULL)
//		systemAbort(ABORT_PTR_NULL,ABORT_PTR_NULL_CODE);
//	size_t left=len;
//	while( (left-- > 0) && *p++=*from++);
//	return len-left;
//}



#endif /* FILESYSTEM_VERIFY_IN_CYGWIN_ENVINTERFACE_H_ */
