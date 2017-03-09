

#include "File.h"
#include <cstdlib>
#include <cstdio>
#include <List.h>


#define HDD_FILE "hdd.img"
#define IMG_SIZE 100*X2fsUtil::SecSize
int main()
{
	char *buf=(char*)malloc(IMG_SIZE);
	printf("dir node size:%d\n",sizeof(TreeNode<FileDescriptor>));
	printf("file : %s \nfile size:%x\n",HDD_FILE,IMG_SIZE);
	printf("Sections:\n");
		printf("\treserved:%x ~ %x\n",0,X2fsUtil::FileNameSection);
		printf("\tfile name section:%x ~ %x\n",X2fsUtil::FileNameSection, X2fsUtil::FileNameSectionLen+X2fsUtil::FileNameSection);//+ X2fsUtil::FileNameSectionLen);
		printf("\tdir section:%x ~ %x\n",X2fsUtil::DirSection, X2fsUtil::DirSectionLen+X2fsUtil::DirSection);//+ X2fsUtil::FileNameSectionLen);
		printf("\tfree space section:%x ~ %x\n",X2fsUtil::FreeSpaceSection, X2fsUtil::FreeSpaceSection+X2fsUtil::FreeSpaceSectionLen);//+ X2fsUtil::FileNameSectionLen);
		printf("\tfile allocation section:%x ~ %x\n",X2fsUtil::FreeSpaceSection+X2fsUtil::FreeSpaceSectionLen, IMG_SIZE);//+ X2fsUtil::FileNameSectionLen);
	X2fsUtil::mockMkfsX2fs(buf,100);
	FILE *fp=fopen(HDD_FILE,"w+");
	fwrite(buf,IMG_SIZE,sizeof(char),fp);
	fflush(fp);
	fclose(fp);

	free(buf);
}
