/*
 * CMDUtil.h
 *
 *  Created on: Dec 1, 2017
 *      Author: 13774
 */

#ifndef INCLUDE_64_CMDUTIL_H_
#define INCLUDE_64_CMDUTIL_H_

#include <File.h>

#if defined(CODE64)
#include <string>
struct Param{
	// 所有要设置的变量
	enum{
		READ,WRITE
	};
	int mode=READ;
	std::string hddfile;
	size_t x2offset=0;
	size_t fsoffset=0;
	size_t length=0;
	std::string fsfile;
	std::string x2file;
	std::string cdpath;
};
/**
 * 为mkfs.x2fs所用的参数
 */
struct ParamMkfs{
	u8_t  basicSize=sizeof(size_t);
	u32_t lbaLow;
	u32_t lbaHigh=0;
	std::string imgFile;
	size_t wholeSecNum;
	bool wholeSecNumSet=false;
	bool lbaLowSet=false;

	size_t secSpaces[4]={
			X2fsUtil<EnvInterface64Impl,size_t>::FileNameSectionLen/CONST_SECSIZE,
			X2fsUtil<EnvInterface64Impl,size_t>::DirSectionLen/CONST_SECSIZE,
			X2fsUtil<EnvInterface64Impl,size_t>::FreeSpaceSectionLen/CONST_SECSIZE,
			X2fsUtil<EnvInterface64Impl,size_t>::LinkedInfoSectionLen/CONST_SECSIZE,
	};
	size_t optional[1]={0};

};
#endif



#endif /* INCLUDE_64_CMDUTIL_H_ */
