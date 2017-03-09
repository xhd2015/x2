

#include "File.h"
#include <cstdlib>
#include <cstdio>


#define HDD_FILE "hdd.img"
#define IMG_SIZE 100*X2fsFileUtil::SecSize
int main()
{
	char *buf=(char*)malloc(IMG_SIZE);
	X2fsFileUtil::mockMkfsX2fs(buf,100);
	FILE *fp=fopen(HDD_FILE,"w+");
	fwrite(buf,IMG_SIZE,sizeof(char),fp);
	fflush(fp);
	fclose(fp);

	free(buf);
}
