

#include "File.h"

#if defined(CODE64)
	#include <cstdlib>
	#include <cstdio>
#endif

#include <List.h>

#if defined(CODE64)

#define HDD_FILE "hdd.img"
#define SECNUM 100
#define IMG_SIZE SECNUM*X2fsUtil::SecSize
/**
 * 开辟一个内存块，格式化，然后将其保存到文件中作为磁盘。
 */
int main()
{
	char *buf=(char*)malloc(IMG_SIZE);
	printf("dir node size:%d\n",sizeof(SimpleMemoryManager<TreeNode<FileDescriptor> >::Node));
	printf("file : %s \nfile size:%x\n",HDD_FILE,IMG_SIZE);
	printf("Sections:\n");
		printf("\treserved:%x ~ %x\n",0,X2fsUtil::FileNameSection);
		printf("\tfile name section:%x ~ %x\n",X2fsUtil::FileNameSection, X2fsUtil::FileNameSectionLen+X2fsUtil::FileNameSection);//+ X2fsUtil::FileNameSectionLen);
		printf("\tdir section:%x ~ %x\n",X2fsUtil::DirSection, X2fsUtil::DirSectionLen+X2fsUtil::DirSection);//+ X2fsUtil::FileNameSectionLen);
		printf("\tfree space section:%x ~ %x\n",X2fsUtil::FreeSpaceSection, X2fsUtil::FreeSpaceSection+X2fsUtil::FreeSpaceSectionLen);//+ X2fsUtil::FileNameSectionLen);
		printf("\tfile allocation section:%x ~ %x\n",X2fsUtil::FreeSpaceSection+X2fsUtil::FreeSpaceSectionLen, IMG_SIZE);//+ X2fsUtil::FileNameSectionLen);
	X2fsUtil::mockMkfsX2fs(buf,SECNUM);
	FILE *fp=fopen(HDD_FILE,"w+");
	fwrite(buf,IMG_SIZE,sizeof(char),fp);
	fflush(fp);
	fclose(fp);

	free(buf);
}

#endif
