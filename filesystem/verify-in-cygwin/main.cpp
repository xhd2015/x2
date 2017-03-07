
//compile: gcc -I ../include --static main.cpp -o main.out
#include <List.h> //for linear space manager:SimpleMemoryManager, for LocateableLinkedList
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cstdlib>
#include <new>
#include "MallocToSimple.h"
#include "File.h"
#include <Memory.h>

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


//A LinearSourceManager metadata
#define FILESPACE_SECTION 21*SEC_SIZE
#define FILESPACE_SECTION_LEN 5*SEC_SIZE

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
	SimpleMemoryManager< TreeNode<MemoryDescriptor> > *smm=new MallocToSimple();
	MemoryManager mm(smm,(int)filename_section,FILENAME_SECTION_LEN,0);
	const char *p=filename_section;
	int lastStart=0;
	const char *lastp=p;
	unsigned char len;
	
	while(p-filename_section <FILENAME_SECTION_LEN)
	{
		len=*(unsigned char)p;
		if(len==0)
		{
			mm.mnew(lastStart,(unsigned int)(p-lastp));
			while(*(++p)==0);
			lastp=p;
			lastStart=(int)lastp-filename_section;
		}else{
			p+=len;	
		}
	}
	//start build the tree of directories
	//actually,this area is managed by a SimpleMemoryManager,the first node is root.
	//The type of all nodes   is File,Directory or Extended Area Pointer(for filename section extension)
	/***************************************************/
	//char type:0 File,1 Directory,2 EAP
	//size_t section_start
	//size_t file_start
	//size_t file_len
	//size_t span_sectors	//the sectors the file spanned
	//size_t name_start //point to filename_section,can make a real pointer by adding with filename_section
	//unsigned int create_time
	//unsigned int lastmodified_time
	//all pointers are not real pointers,they are relative to the pointer dir_section;

	//对所有的节点的4个指针域加上偏移 dir_section NULL不进行设置
	TreeNode<FileDescriptor> *nodebuffer=(TreeNode<FileDescriptor>*)dir_section;
	for(int i=0;i*sizeof(TreeNode<FileDescriptor>) <DIR_SECTION_LEN ; i++ )
	{
		nodebuffer[i].setFather(nodebuffer[i].getFather()==NULL?(nodebuffer[i].getFather() + dir_section ):NULL);
		nodebuffer[i].setNext(nodebuffer[i].getNext()==NULL?(nodebuffer[i].getNext() + dir_section):NULL );
		nodebuffer[i].setPrevious(nodebuffer[i].getPrevious()==NULL?(nodebuffer[i].getPrevious() + dir_section):NULL );
		nodebuffer[i].setSon(nodebuffer[i].getSon()==NULL?(nodebuffer[i].getPrevious() + dir_section):NULL );
	}
	SimpleMemoryManager<TreeNode<FileDescriptor> > dirSectionManager(dir_section,DIR_SECTION_LEN);
	
	//FileTree 		-- extends Tree
	//set root as nodebuffer[0];
	//the FileTree is done


	//start build the free space LinkedList
	


	//list all directories
	

	


	//对dir_section中的数据，其中的每一个节点减去偏移之后再存储
	for(int i=0;i*sizeof(TreeNode<FileDescriptor>) <DIR_SECTION_LEN ; i++ )
	{
		nodebuffer[i].setFather(nodebuffer[i].getFather()==NULL?(nodebuffer[i].getFather() - dir_section ):NULL);
		nodebuffer[i].setNext(nodebuffer[i].getNext()==NULL?(nodebuffer[i].getNext() - dir_section):NULL );
		nodebuffer[i].setPrevious(nodebuffer[i].getPrevious()==NULL?(nodebuffer[i].getPrevious() - dir_section):NULL );
		nodebuffer[i].setSon(nodebuffer[i].getSon()==NULL?(nodebuffer[i].getPrevious() - dir_section):NULL );
	}

	//write the buffer back to the image
	fseek(img,FILENAME_SECTION,SEEK_SET);
	fwrite(filename_section,FILENAME_SECTION_LEN,sizeof(char),img);
	fwrite(dir_section,DIR_SECTION_LEN,sizeof(char),img);

	//exit program
	fclose(img);
	free(dir_section);
	free(filename_section);
	return 0;


}


//构造一个文件系统，其中的filename_section项为空
//dir_section只有一个root项，即 /,这是没有名称的
//如果试图通过ls /x2 列出目录，先找到/项，然后查找下面每一项的名字，直到与x2相同的名称出现
//注意，最好不要包含重名。然而，重名也是允许的。
//所有的文件独享一个名字空间而非共享。
//这就存在一种潜在的优化措施，所有的文件命名都采用前缀树来管理，-- 当然，这只会优化存储空间（仅当文件系统中有大量重复文件名的时候），因此带来的是查找速度的降低
//

void mkfsX2fs()
{

}