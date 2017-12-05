
#include <cstdio>
#include <cstdlib>
int main(int argc,char *argv[])
{
	FILE *fp=fopen(argv[1],"r+");
	int n=atoi(argv[2]);
	fwrite(&n,sizeof(n),1,fp);
	fclose(fp);
}
