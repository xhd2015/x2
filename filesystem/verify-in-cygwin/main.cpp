
//compile: gcc -I ../include --static main.cpp -o main.out
#include <List.h> //for linear space manager:SimpleMemoryManager
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cstdlib>

//suppose the disk image is :
//		hdd.img
#define HDD_FILE "hdd.img"

#define KiB 1024
#define MiB 1024*KiB
#define IMG_SIZE 100*MiB

#define SEC_SIZE 512
#define FILENAME_SECTION 2*SEC_SIZE
#define FILENAME_SECTION_LEN 4*SEC_SIZE

#define DIR_SECTION 5*SEC_SIZE
#define DIR_SECTION_LEN 15*SEC_SIZE

int main()
{
	char *filename_section=(char*)malloc(FILENAME_SECTION_LEN+1);
	char *dir_section=(char*)malloc(DIR_SECTION_LEN+1);
	FILE *img=fopen(HDD_FILE,"r+");

	assert(img!=NULL);
	assert(filename_section!=NULL);
	assert(dir_section!=NULL);

	fseek(img,FILENAME_SECTION,SEEK_SET);
	fread(filename_section,FILENAME_SECTION_LEN,sizeof(char),img);
	fread(dir_section,DIR_SECTION_LEN,sizeof(char),img);


	//start build the list of filenames
	//to retrieve this information,enought linkage information from the original is needed.
	// (长度,名称)(长度，名称) 长度占用1个字节，因此最长名称有256个字符
	//由此构建一个剩余空间链表,可以构造一个复杂tree结构的memorymanager，这也是可行的，虽然很占用空间
	MemoryManager mm((int)filename_section,FILENAME_SECTION_LEN);
	const char *p=filename_section;
	while(p-filename_section <FILENAME_SECTION_LEN)
	{
		unsigned char len=0;
		while(*(p+len)==0)len++;

		//set node (p,len) as a free one

		p+=len;

	}




	//start build the tree of directories


	//list all directories

	fclose(img);
	free(dir_section);
	free(filename_section);
	return 0;


}