/*
 * CMDUtil.h
 *
 *  Created on: Dec 1, 2017
 *      Author: 13774
 */

#ifndef INCLUDE_64_CMDUTIL_H_
#define INCLUDE_64_CMDUTIL_H_

#include <File.h>
#include <EnvInterface64Impl.h>

#if defined(CODE64)
#include <string>
struct ParamRwfile{
	// 所有要设置的变量
	enum{
		READ,WRITE
	};
	int mode=READ;
	std::string hddfile{};
	size_t x2offset=0;
	size_t fsoffset=0;
	size_t length=0;
	std::string fsfile{};
	std::string x2file{};
	std::string cdpath{};
	u32_t lbalow{0};
	u8_t  basicSize=sizeof(size_t);
};
/**
 * 为mkfs.x2fs所用的参数
 */
struct ParamMkfs{
	u8_t  basicSize=sizeof(size_t);
	u32_t lbaLow{};
	u32_t lbaHigh=0;
	std::string imgFile{};
	size_t wholeSecNum{};
	size_t reserved { X2fsMetaInfo::SECNUM_RESERVED_CONST};
	size_t meta{ X2fsMetaInfo:: SECNUM_META_CONST };
	bool wholeSecNumSet=false;
	bool lbaLowSet=false;
};

struct ParamMain{
public:
	u8_t  basicSize=sizeof(size_t);
	const std::string spiltor=";";
	std::string imgFile{};
	std::string cmds{};
	std::string cdpath{};
	u32_t lbalow=0;

};
#endif



#endif /* INCLUDE_64_CMDUTIL_H_ */
