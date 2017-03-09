
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

#define IMG_SIZE 100*X2fsFileUtil::SecSize

int main()
{
	char *filename_section=(char*)malloc(X2fsFileUtil::FileNameSectionLen+1);
	char *dir_section=(char*)malloc(X2fsFileUtil::DirSectionLen+1);
	char *free_section=(char*)malloc(X2fsFileUtil::FreeSpaceSectionLen+1);
	FILE *img=fopen(HDD_FILE,"r+");

	assert(img!=NULL);
	assert(filename_section!=NULL);
	assert(dir_section!=NULL);

	fseek(img,X2fsFileUtil::FileNameSection,SEEK_SET);
	fread(filename_section,X2fsFileUtil::FileNameSectionLen,sizeof(char),img);
	fread(dir_section,X2fsFileUtil::DirSectionLen,sizeof(char),img);
	fread(free_section,X2fsFileUtil::FreeSpaceSectionLen,sizeof(char),img);


	//start build the list of filenames
	//to retrieve this information,enought linkage information from the original is needed.
	MallocToSimple< TreeNode<MemoryDescriptor> > *smm=new MallocToSimple< TreeNode<MemoryDescriptor> >();
	MemoryManager<MallocToSimple> mm(smm,(size_t)filename_section,(size_t)X2fsFileUtil::FileNameSectionLen,false);
	const char *p=filename_section;
	int lastStart=0;
	const char *lastp=p;
	unsigned char len;
	
	while(p-filename_section <X2fsFileUtil::FileNameSectionLen)
	{
		len=*(unsigned char*)p;
		if(len==0)
		{
			mm.mnew(lastStart,(size_t)(p-lastp));
			while(*(++p)==0);
			lastStart=(size_t)p-(size_t)filename_section;
			lastp=p;
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

	TreeNode<FileDescriptor> *nodebuffer=(TreeNode<FileDescriptor>*)dir_section;
	for(int i=0;i*sizeof(TreeNode<FileDescriptor>) <X2fsFileUtil::DirSectionLen ; i++ )
	{
		nodebuffer[i].setFather((TreeNode<FileDescriptor>*)
				(nodebuffer[i].getDirectFather()==NULL?((size_t)nodebuffer[i].getDirectFather() + (size_t)dir_section ):NULL));
		nodebuffer[i].setNext(
				(TreeNode<FileDescriptor>*)
				(nodebuffer[i].getNext()==NULL?((size_t)nodebuffer[i].getNext() + (size_t)dir_section):NULL) );
		nodebuffer[i].setPrevious(
				(TreeNode<FileDescriptor>*)
				(nodebuffer[i].getPrevious()==NULL?((size_t)nodebuffer[i].getPrevious() + (size_t)dir_section):NULL ) );
		nodebuffer[i].setSon(
				(TreeNode<FileDescriptor>*)
				(nodebuffer[i].getSon()==NULL?((size_t)nodebuffer[i].getSon() + (size_t)dir_section):NULL) );
	}
	SimpleMemoryManager<TreeNode<FileDescriptor> > dirSectionManager((size_t)dir_section,X2fsFileUtil::DirSectionLen);
	
	//FileTree 		-- extends Tree
	//set root as nodebuffer[0];
	//the FileTree is done
	SimpleMemoryManager<TreeNode<FileDescriptor> > fileSmm(X2fsFileUtil::DirSection,X2fsFileUtil::DirSectionLen);
	Tree<FileDescriptor,SimpleMemoryManager> fileTree(&fileSmm,(TreeNode<FileDescriptor>*)X2fsFileUtil::DirSection);
	//This had been done

	//start build the free space LinkedList
	LinearSourceDescriptor *lsbarr=(LinearSourceDescriptor*)free_section;
	MallocToSimple<ListNode<LinearSourceDescriptor> > lsdsmm;
	LinearSourceManager<LinearSourceDescriptor,MallocToSimple> fillAllocs(&lsdsmm,lsbarr[0].getStart(),lsbarr[0].getLimit());
	if(lsbarr[1].getStart() > lsbarr[0].getStart() && lsbarr[1].getLimit()!=0)
	{
		fillAllocs.mnew(lsbarr[0].getStart(),lsbarr[1].getStart()-lsbarr[0].getStart());
	}
	if(lsbarr[1].getLimit()!=0)
	{
		for(int i=2;i*sizeof(LinearSourceDescriptor) < X2fsFileUtil::FreeSpaceSectionLen && lsbarr[i].getLimit()>0;i++)
		{
			fillAllocs.mnew(lsbarr[i-1].getStart()+lsbarr[i-1].getLimit(),lsbarr[i].getStart()-lsbarr[i-1].getStart()-lsbarr[i-1].getLimit());
		}
	}
	//***********ALL DONE*********//

	//create a file under root
	const char *fname="first.first.second";
	char *fdst=(char*)mm.mnew(strlen(fname));
	*(unsigned char*)((size_t)filename_section+(size_t)fdst)=strlen(fname);
	strncpy((char*)((size_t)filename_section+(size_t)fdst+1),fname,strlen(fname));
	size_t fspan=2;//2 sectors

	size_t fsecStart=(size_t)fillAllocs.mnew(fspan*X2fsFileUtil::SecSize);

	TreeNode<FileDescriptor> *fnode=new (fileSmm.getNew()) TreeNode<FileDescriptor>(
			FileDescriptor(
					FileDescriptor::TYPE_FILE,
					fsecStart,fspan,fsecStart,0,
					(size_t)fdst,
					0,0
			)
	);
	fileTree.getHead()->insertNext(fnode);





	//list all directories
	TreeNode<FileDescriptor>* rootfs=fileTree.getHead();
	if(rootfs)
	{
		FileDescriptor fdroot=rootfs->getData();
		char *p=(char*)(fdroot.getNameOffset()+filename_section);
		char saver[20];
		int n=*p;
		for(int i=0;i!=n;i++)
		{
			putchar(*(p+i+1));
		}
		putchar('\n');
	}
	



	for(int i=0;i*sizeof(TreeNode<FileDescriptor>) <X2fsFileUtil::DirSectionLen ; i++ )
	{
		nodebuffer[i].setFather(
				(TreeNode<FileDescriptor>*)
				((nodebuffer[i].getDirectFather())==NULL?((size_t)nodebuffer[i].getDirectFather() - (size_t)dir_section ):NULL) );
		nodebuffer[i].setNext((TreeNode<FileDescriptor>*)(nodebuffer[i].getNext()==NULL?((size_t)nodebuffer[i].getNext() - (size_t)dir_section):NULL) );
		nodebuffer[i].setPrevious((TreeNode<FileDescriptor>*)
				(nodebuffer[i].getPrevious()==NULL?((size_t)nodebuffer[i].getPrevious() - (size_t)dir_section):NULL ));
		nodebuffer[i].setSon(
				(TreeNode<FileDescriptor>*)
				(nodebuffer[i].getSon()==NULL?((size_t)nodebuffer[i].getSon() - (size_t)dir_section):NULL ) );
	}

	//write the buffer back to the image
	fseek(img,X2fsFileUtil::FileNameSection,SEEK_SET);
	fwrite(filename_section,X2fsFileUtil::FileNameSectionLen,sizeof(char),img);
	fwrite(dir_section,X2fsFileUtil::DirSectionLen,sizeof(char),img);
	fwrite(free_section,X2fsFileUtil::FreeSpaceSectionLen,sizeof(char),img);

	//exit program
	fclose(img);
	free(dir_section);
	free(filename_section);
	free(free_section);
	return 0;


}

