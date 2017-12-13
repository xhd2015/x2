/*
 * EnvInterface.h
 *
 *  Created on: Nov 25, 2017
 *      Author: 13774
 */

#ifndef ENVINTERFACE_H_
#define ENVINTERFACE_H_

#include <def.h>
#if defined(CODE64)
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
#include <regex>
#endif


#define ABORT_PTR_nullptr "pointer is nullptr"
#define ABORT_PTR_nullptr_CODE -1


//这是一个当前主机的主机环境，所有需要跨平台的类，函数都应当使用这个namespace中的定义
namespace HostEnv{
	enum{CUR_SEG = 0x10000u }; //用于段读写
#if defined(CODE64)
	using size_t = ::size_t; //定义size_t类型

	/**
	 * 文件映射到驱动器的一部分，从第二个参数开始
	 */
	std::vector<std::pair<std::string,u32_t>> files;

	// c库基本函数
	using ::memcpy;
	using ::memmove;
	using ::memset;
	using ::malloc;
	using ::free;

	using ::strcpy;
	using ::strncpy;
	using ::strncmp;
	using ::strlen;
	using ::memset;
	using ::memcpy;
	using ::atoi;

	using ::operator new;

	using String =std::string;
	template <class T>
		 using Allocator =typename std::template allocator<T>;
	template <class T>
		using Vector = typename std::template vector<T,Allocator<T>>;

	using std::cout;
	using std::cin;
	using std::endl;
	using std::flush;

	void *checkOnNullThrows(void *ptr);
	/**
	 * 如果不成功，抛出异常
	 * 用于需要确保对象被正确初始化，保证不变式被建立
	 */
	void *mallocThrows(size_t size);

	// 不能使用
	int writeSectors(u32_t srcSeg,const u8_t* srcOff,u8_t driver,u32_t LBAlow,u32_t num,u32_t LBAhigh);
	int readSectors(u32_t dstSeg,u8_t* dstOff,u8_t driver,u32_t LBAlow,u32_t num,u32_t LBAhigh);

	/**
	 * 这是一个简单版本的printf，有下面的实现要求：
	 * 		不支持除%d以外的其他任何格式化参数
	 * 		不要使用%s,%x,%p等，所以 "s=%s,p=%p"不能够接受
	 * 		最多支持三个参数，所以 "a=%d,b=%d,c=%d,d=%d\n"不能够接受，当然，参数个数超出范围，编译器会报错。
	 * @param fmt 格式化字符串
	 * @param arg0
	 * @param arg1
	 * @param arg2
	 */
//	 __attribute__ ((format (printf, 1, 2)))
	int printf_simple(const char *fmt,int arg0=0,int arg1=0,int arg2=0);
	/**
	 * 打印s的至多n个字符
	 * @param s 要打印的字符串
	 * @param n 打印的个数
	 * @return 返回打印的字符个数
	 */
	int printf_sn(const char *s,size_t n);


	/**
	 * 系统终止函数，这应当改变程序的流程
	 */
	void systemAbort(const char *msg,int code);
	/**
	 * 将所有的输出立即写出
	 * 用于系统崩溃时，确保用户看到信息
	 */
	void flushOutputs();

	/**
	 * atoi对String类型的包装
	 */
	int atoi(const String &s)
	{
		return ::atoi(s.c_str());
	}


	std::vector<std::string> regexSplit(const std::regex& re, const std::string& s);
	std::vector<std::string> spaceSplit(const std::string& s);
	std::vector<std::string> pathSplit(const std::string& s);
	std::vector<std::string> cmdSplit(const std::string& s);

	u8_t getFileDriver(const std::string & file)
	{
		for(size_t i=0;i!=files.size();++i)
			if(files[i].first == file)
				return i;
		return 0xff;
	}
	const std::string & getDriverFile(u8_t driver)
	{
		static const std::string nullptrstr="";
		if(driver < files.size())
			return files.at(driver).first;
		return nullptrstr;
	}

	u8_t addFile(const std::string & file,u32_t lbaBase)
	{
		u8_t driver;
		if( (driver=getFileDriver(file))!=0xff)return driver;
		driver =files.size();
		if(driver!=0xff)
		{
			files.push_back(std::make_pair(file,lbaBase));
		}
		return driver;
	}


	int writeSectors(u32_t srcSeg,const u8_t* srcOff,u8_t driver,u32_t LBAlow,u32_t num,u32_t LBAhigh)
	{
		const std::string &file=getDriverFile(driver);
		if(file!="")
		{
			u32_t lbaBase = files[driver].second;
			FILE *fp=fopen(file.c_str(),"rb+");
			if(fp==nullptr)
				fp=fopen(file.c_str(),"wb+");
			fseek(fp,(LBAlow - lbaBase)*CONST_SECSIZE,SEEK_SET);
			size_t n=fwrite(srcOff,CONST_SECSIZE,num,fp);
			fclose(fp);
			return n;
		}else{
			return 0;
		}

	}
	int readSectors(u32_t dstSeg,u8_t* dstOff,u8_t driver,u32_t LBAlow,u32_t num,u32_t LBAhigh)
	{
		const std::string &file=getDriverFile(driver);
		if(file!="")
		{
			u32_t lbaBase = files[driver].second;
			FILE *fp=fopen(file.c_str(),"rb+");
				if(fp==nullptr)
					fp=fopen(file.c_str(),"wb+");
			//	fseek(fp,0,SEEK_END);
			//	printf_simple("fp size=%d\n",ftell(fp));
				fseek(fp,(LBAlow - lbaBase)*CONST_SECSIZE,SEEK_SET); // 如果已有文件不够大，会返回错误

			//	size_t n=fread(dstOff,CONST_SECSIZE,num,fp);
				fread(dstOff,CONST_SECSIZE,num,fp); //可能返回0
				fclose(fp);
				return num;
		}else{
			return 0;
		}

	}
	int printf_simple(const char *fmt,int arg0,int arg1,int arg2)
	{
	//	va_list ap;
	//	va_start(ap,fmt);
	//	vfprintf(stdout,fmt,ap);
	//	va_end(ap);
		::printf(fmt,arg0,arg1,arg2);
		flushOutputs();
		return 0;

	}
	int printf_sn(const char *s,size_t n)
	{
	#define MAX_SPACE 40
		if(n<MAX_SPACE)
		{
			char buffer[MAX_SPACE];
			for(size_t i=0;i<n;i++)
				buffer[i]=s[i];
			buffer[n]='\0';
			printf_simple(buffer);
		}else{
			printf_sn(s,MAX_SPACE-1);
			printf_sn(s+MAX_SPACE-1, n - MAX_SPACE + 1);
		}
		return 0;
	#undef MAX_SPACE
	}


		void systemAbort(const char *msg,int code)
		{
			::printf("--ABORT-- code=%d,msg=\"%s\"",code,msg);
			flushOutputs();
			::abort();
		}
		void flushOutputs()
		{
			::fflush(stdout);
		}




		//================ class StdEnv64Impl
		std::vector<std::string> regexSplit(const std::regex& re, const std::string& s) {
			const std::string::const_iterator begin = s.cbegin();
			auto itBeg = begin;
			std::vector<std::string> res;
			std::smatch allmatch;

			while (itBeg != s.end() && std::regex_search(itBeg, s.cend(), allmatch, re)) {
				// pos,len 每次迭代时，当还有时,应将beg~pos之间保留，然后beg变换到length之后
				res.push_back(s.substr(itBeg - begin, allmatch.position()));
				auto len = allmatch.length() + allmatch.position();
				if (s.cend() - itBeg <= len) //超出范围
					break;
				itBeg += len;
			}
			if(itBeg!=s.end())
			{
				res.push_back(s.substr(itBeg - begin));
				itBeg = s.end();
			}

			return std::move(res);
		}

		std::vector<std::string> spaceSplit(const std::string& s) //static函数是不可继承的
			{
				return std::move(regexSplit(std::regex("\\s+"), s));
			}
		std::vector<std::string> pathSplit(const std::string& s) //static函数是不可继承的
			{
				return std::move(regexSplit(std::regex("/+"), s));
			}
		std::vector<std::string> cmdSplit(const std::string& s)
			{
				return std::move(regexSplit(std::regex(";+"), s));
			}

		void *checkOnNullThrows(void *ptr)
		{
			if(!ptr)
				HostEnv::systemAbort("nullpointer?", -2);
			return ptr;
		}

		void *mallocThrows(size_t size)
		{
			return checkOnNullThrows(malloc(size));
		}
#elif defined(CODE32)

#elif defined(CODE32USER)

#elif defined(CODE16)

#else
	//什么都不提供
#endif


};

using HostEnv::operator new; // HostEnv重新定义new





//size_t EnvInterface::strlen(const char* s) //应当报错
//{
//	if(s==nullptr)
//		systemAbort(ABORT_PTR_nullptr,ABORT_PTR_nullptr_CODE);
//	size_t l=0;
//	while(*s++!=0)l++;
//	return l;
//}
//
//size_t EnvInterface::strncpy(char *p,const char *from,size_t len)
//{
//	if(p==nullptr || from==nullptr)
//		systemAbort(ABORT_PTR_nullptr,ABORT_PTR_nullptr_CODE);
//	size_t left=len;
//	while( (left-- > 0) && *p++=*from++);
//	return len-left;
//}



#endif /* FILESYSTEM_VERIFY_IN_CYGWIN_ENVINTERFACE_H_ */
