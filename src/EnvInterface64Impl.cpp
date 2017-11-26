/*
 * EnvInterface64Impl.cpp
 *
 *  Created on: Nov 25, 2017
 *      Author: 13774
 */

// 64--ONLY

#include <EnvInterface64Impl.h>
#include <cstdlib>
#include <cstdarg>
#include <cstdio>
#include <cstring>

#if defined(CODE64)

EnvInterface64Impl * EnvInterface64Impl::env=NULL;
const char * EnvInterface64Impl::file=NULL;

EnvInterface64Impl *EnvInterface64Impl::getInstance()
{
	if(env==NULL)
		env = new EnvInterface64Impl();
	return env;
}
void			EnvInterface64Impl::setHDDFile(const char *file)
		{
			EnvInterface64Impl::file=file;
		}

int EnvInterface64Impl::writeSectors(u32_t srcSeg,const u8_t* srcOff,u8_t driver,u32_t LBAlow,u32_t num,u32_t LBAhigh)
{
	FILE *fp=fopen(file,"rb+");
	if(fp==NULL)
		fp=fopen(file,"wb+");
	fseek(fp,(LBAlow - LBABASE)*CONST_SECSIZE,SEEK_SET);
	size_t n=fwrite(srcOff,num,CONST_SECSIZE,fp);
	fclose(fp);
	return n;
}
int EnvInterface64Impl::readSectors(u32_t dstSeg,u8_t* dstOff,u8_t driver,u32_t LBAlow,u32_t num,u32_t LBAhigh)
{
	FILE *fp=fopen(file,"rb+");
	if(fp==NULL)
		fp=fopen(file,"wb+");
	fseek(fp,(LBAlow - LBABASE)*CONST_SECSIZE,SEEK_SET);
	size_t n=fread(dstOff,num,CONST_SECSIZE,fp);
	fclose(fp);
	return n;
}
int EnvInterface64Impl::printf_simple(const char *fmt,int arg0,int arg1,int arg2)
{
//	va_list ap;
//	va_start(ap,fmt);
//	vfprintf(stdout,fmt,ap);
//	va_end(ap);
	::printf(fmt,arg0,arg1,arg2);

	return 0;

}
int EnvInterface64Impl::printf_sn(const char *s,size_t n)
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
u8_t* EnvInterface64Impl::malloc(size_t size)
{
	return (u8_t*)::malloc(size);
}


	void  EnvInterface64Impl::free(u8_t* p)
	{
		::free(p);
	}

	void EnvInterface64Impl::systemAbort(const char *msg,int code)
	{
		::printf("--ABORT-- code=%d,msg=\"%s\"",code,msg);
		flushOutputs();
		::abort();
	}
	void EnvInterface64Impl::flushOutputs()
	{
		::fflush(stdout);
	}


	char *EnvInterface64Impl::strcpy(char *s,const char *ct)
	{
		return ::strcpy(s, ct);
	}
	char *EnvInterface64Impl::strncpy(char *s,const char *ct,size_t n)
	{
		return ::strncpy(s,ct,n);
	}
	int EnvInterface64Impl::strncmp(const char *cs,const char *ct,size_t n)
	{
		return ::strncmp(cs,ct,n);
	}
	size_t EnvInterface64Impl::strlen(const char *cs)
	{
		return ::strlen(cs);
	}
	void *EnvInterface64Impl::memset(char *s,int c,size_t n)
	{
		return ::memset(s,c,n);
	}
	void *EnvInterface64Impl::memcpy(char *s,const char *ct,size_t n)
	{
		return ::memcpy(s,ct,n);
	}

#endif
