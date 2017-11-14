

#define HDD_FILE "hdd.img"

#include <cstdio>
#include <cassert>
int main()
{
	FILE *fp=fopen(HDD_FILE,"r+");
	assert(fp!=NULL);
	fseek(fp,512*2,SEEK_SET);
	fprintf(fp,"<I write at here>");
	fflush(fp);
	fclose(fp);
	return 0;
}
