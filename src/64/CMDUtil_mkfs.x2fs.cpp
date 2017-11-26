
 //CODE64 ONLY
#include <File.h>

#if !defined(CODE64)
#error "CODE64 ONLY"
#endif

#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <string>

#include <List.h>

#if defined(CODE64)

#define SECNUM 100
#define IMG_SIZE SECNUM*X2fsUtil::SecSize
/**
 * 开辟一个内存块，格式化，然后将其保存到文件中作为磁盘。
 */
int main(int argc,char *argv[])
{

	if(argc<2)
	{
		std::string filename;
		std::cout << "please input a file:";
		std::cin >> filename;
		EnvInterface64Impl::setHDDFile(filename.c_str());
	}else{
		EnvInterface64Impl::setHDDFile(argv[1]);
	}

	X2fsMetaInfo metainfo;
	metainfo.lbaStartLow = 0x3000;
	metainfo.lbaStartHigh = 0;
	metainfo.wholeSecnums = 8192;
	metainfo.secnums[X2fsMetaInfo::INDEX_NAME]=X2fsUtil<EnvInterface64Impl>::FileNameSectionLen/CONST_SECSIZE;
	metainfo.secnums[X2fsMetaInfo::INDEX_DIR]=X2fsUtil<EnvInterface64Impl>::DirSectionLen/CONST_SECSIZE;
	metainfo.secnums[X2fsMetaInfo::INDEX_FREE]=X2fsUtil<EnvInterface64Impl>::FreeSpaceSectionLen/CONST_SECSIZE;
	metainfo.secnums[X2fsMetaInfo::INDEX_FILE]=X2fsUtil<EnvInterface64Impl>::FileNameSectionLen/CONST_SECSIZE;
	metainfo.secnums[X2fsMetaInfo::INDEX_LINK]=X2fsUtil<EnvInterface64Impl>::LinkedInfoSectionLen/CONST_SECSIZE;
	metainfo.optional[X2fsMetaInfo::INDEX_OPTIONAL_SECD]=0;

	std::cout << "information about metainfo"<<std::endl;
	metainfo.dumpInfo(EnvInterface64Impl::getInstance());
	std::cout << std::endl;

	if(!X2fsMetaInfo::checkMetainfo(&metainfo))
		printf("cannot validate metainfo\n");
	else
		X2fsUtil<EnvInterface64Impl>::mkfs(EnvInterface64Impl::getInstance(), 0x80, &metainfo);

	printf("re-reading the information to validate....");
	EnvInterface64Impl *env=EnvInterface64Impl::getInstance();
//	X2fsMetaInfo *buf=(X2fsMetaInfo*)env->malloc(sizeof(X2fsMetaInfo));
//	X2fsMetaInfo *buf = new X2fsMetaInfo;
	u8_t *buf = env->malloc(metainfo.metaSec * CONST_SECSIZE);
	X2fsMetaInfo *readMetainfo=(X2fsMetaInfo*)buf;
	env->readSectors(EnvInterface::CUR_SEG, buf,0x80,0x3000+2, 1, 0);
	if(!X2fsMetaInfo::checkMetainfo(readMetainfo))
	{
		printf("validating failed!\n");
	}else{
		printf("validating succeed!\n");
	}
	env->flushOutputs();


	env->free(buf);

	printf("end.\n");
	env->flushOutputs();
}

#endif
