

//compile: gcc -I ../include --static main.cpp -o main.out
#include <64/MallocToSimple.h>
#include <List.h> //for linear space manager:SimpleMemoryManager, for LocateableLinkedList
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cstdlib>
#include <new>
#include "File.h"
#include <Memory.h>


//suppose the disk image is :
//		hdd.img
#define HDD_FILE "hdd.img"

#define IMG_SIZE 100*X2fsUtil::SecSize
typedef SimpleMemoryManager<TreeNode<FileDescriptor> >::Node FileNode;
int main()
{
	X2fsUtil xfu(HDD_FILE);
//	xfu.createFileInRoot("kill.me", 2);
//	printf("end create file\n");
	xfu.listRoot();
//	printf("end listRoot \n");
//	xfu.flush();
//	printf("end flush \n");

	if(xfu.hasFilename(0,NULL,"new1"))
	{
		printf("find new1\n");
	}else{
		printf("no new1\n");
	}
	if(xfu.hasFilename(0,NULL,"new7"))
	{
		printf("find new7\n");
	}else{
		printf("no new7\n");
	}

	printf("mkdir dira\n");
	const char *diraCreatePath[]={"dira"};
	bool ifmk=xfu.createDir(arrsizeof(diraCreatePath),diraCreatePath);
	if(ifmk)
	{
		printf("mkdir success\n");
		printf("has \"dira\"? %d\n",xfu.hasFilename(0,NULL,"dira"));
	}else{
		printf("mkdir failed\n");
	}

	printf("new file \"x\" in \"dira\"\n");
	const char *paths[]={"dira","x"};

	ifmk=xfu.createFile( arrsizeof(paths), paths, 2);
	printf("create \"x\" in \"dira\" succeeded ? %d\n",ifmk);

	printf("test listNode\n");
	xfu.listNode(1, paths);

	printf("Create a dir \"subdir\" under \"dira\" and a file \"y\" in it.\n");
	const char *paths2[]={"dira","subdir","y"};
	ifmk=xfu.createDir(arrsizeof(paths2)-1, paths2);
	printf("create dir of subdir succeed? %d\n",ifmk);
	ifmk=xfu.createFile(arrsizeof(paths2), paths2, 5);
	printf("create dir of subdir/y succeed? %d\n",ifmk);

	xfu.listNode(1, paths,3);
	printf("test delete /dira/subdir \n");
	xfu.deleteFile(arrsizeof(paths2)-1,paths2);
	xfu.listNode(1, paths, 3);

	printf("recreate subdir and subdir/y \n");
	ifmk=xfu.createDir(arrsizeof(paths2)-1, paths2);
	ifmk=xfu.createFile(arrsizeof(paths2),paths2, 2);
	xfu.listNode(1, paths, 3);

	printf("test write/read file \n");
	const char *content="hello world";
	xfu.writeToFile(content, sizeof(char), strlen(content), arrsizeof(paths2), paths2, 0);
	xfu.flush();
	int buflen = 2*X2fsUtil::SecSize + 40;
	char *buf=(char*)malloc(buflen);
	xfu.readFromFile(buf, sizeof(char), strlen(content),arrsizeof(paths2),paths2, 0);
	printf("content is %s,length is %d, read after write is \"%.*s\"\n",content,strlen(content),strlen(content),buf);

	printf("test modify file name\n");
	xfu.rename(arrsizeof(paths)-1,paths,"newdira");
	xfu.listRoot();
	const char *newpath[]={"newdira"};
	xfu.listNode(arrsizeof(newpath), newpath,3);

	printf("test move file\n");
	const char *y_path[]={"newdira","subdir","y"};
	const char *new_y_path[]={"newdira"};
	xfu.move(arrsizeof(y_path),y_path,arrsizeof(new_y_path),new_y_path,"new_y");
	xfu.listNode(arrsizeof(newpath),newpath,3);

	printf("test big file(file that uses linked sections,not implemented)\n");
	printf("Write huge data to the file more the the original size can hold\n");//suggested strategy is : every time allocate new size that is the
	//same or  a multiples of the original size, or at a fixed number.or equal to the requested size.
	const char *new_y[]={"newdira","new_y"};
	xfu.dumpFileInfo(arrsizeof(new_y),new_y);
	buf[buflen-3]='x';
	buf[buflen-2]='h';
	buf[buflen-1]='d';
	xfu.writeToFile(buf, sizeof(char), buflen, arrsizeof(new_y),new_y,0);
	xfu.dumpFileInfo(arrsizeof(new_y),new_y);

	free(buf);

}

//
//int main_deprecated()
//{
//	char *const allbuf=(char*)malloc(IMG_SIZE);
//	char *const filename_section=allbuf+X2fsUtil::FileNameSection;
//	char *const dir_section=allbuf+X2fsUtil::DirSection;
//	char *const free_section=allbuf+X2fsUtil::FreeSpaceSection;
//	FILE *const img=fopen(HDD_FILE,"r+");
//
//	assert(img!=NULL);
//	assert(allbuf!=NULL);
//
//	fseek(img,X2fsUtil::FileNameSection,SEEK_SET);
//	fread(filename_section,X2fsUtil::FileNameSectionLen,sizeof(char),img);
//	fread(dir_section,X2fsUtil::DirSectionLen,sizeof(char),img);
//	fread(free_section,X2fsUtil::FreeSpaceSectionLen,sizeof(char),img);
//	//printf("here \n"); //good
//
//	//start build the list of filenames
//	//to retrieve this information,enought linkage information from the original is needed.
//	MallocToSimple< TreeNode<MemoryDescriptor> > smm;
//	printf("new MallocToSimple \n");
//	MemoryManager<MallocToSimple> filenamemm(&smm,0,(size_t)X2fsUtil::FileNameSectionLen,false);
//	printf("new mm : %x ~ %x\n",filenamemm.getHead()->getData().getStart(),filenamemm.getHead()->getData().getLimit());
//	const char *p=filename_section;
//	int lastStart=0;
//	const char *lastp=p;
//
//	while(p-filename_section <X2fsUtil::FileNameSectionLen)
//	{
//		if(*p==0)
//		{
//			while(*(++p)==0);
//			filenamemm.mnew(lastStart,(size_t)(p-lastp));
//		}else{
//			p+=*p;
//		}
//		lastStart=(size_t)p-(size_t)filename_section;
//		lastp=p;
//	}
//	printf("dump filename mm\n");
//	TreeNode<MemoryDescriptor> *ptreenode=(TreeNode<MemoryDescriptor>*)filenamemm.getHead();
//	printf("head: %x : %x : %d\n",ptreenode->getData().getStart(),ptreenode->getData().getLimit(),ptreenode->getData().isAllocable());
//	ptreenode=(TreeNode<MemoryDescriptor>*)ptreenode->getSon();
//	while(ptreenode)
//	{
//		printf("%x : %x : %d\n",ptreenode->getData().getStart(),ptreenode->getData().getLimit(),ptreenode->getData().isAllocable());
//		ptreenode=(TreeNode<MemoryDescriptor>*)ptreenode->getNext();
//	}
//	printf("end filename\n");
//	//start build the tree of directories
//	//actually,this area is managed by a SimpleMemoryManager,the first node is root.
//	//The type of all nodes   is File,Directory or Extended Area Pointer(for filename section extension)
//	/***************************************************/
//	//char type:0 File,1 Directory,2 EAP
//	//size_t section_start
//	//size_t file_start
//	//size_t file_len
//	//size_t span_sectors	//the sectors the file spanned
//	//size_t name_start //point to filename_section,can make a real pointer by adding with filename_section
//	//unsigned int create_time
//	//unsigned int lastmodified_time
//	//all pointers are not real pointers,they are relative to the pointer dir_section;
//
//	printf("dump dir_section \n");
//	for(int i=0;i!=X2fsUtil::DirSectionLen;i++)
//	{
//		//printf("%x ",(int)dir_section[i]);
//	}
//	printf("\n");
//	SimpleMemoryManager<TreeNode<FileDescriptor> >::Node *nodebuffer=(SimpleMemoryManager<TreeNode<FileDescriptor> >::Node*)dir_section;
//	printf("before adjust offset,dump node[1]\n");
//	printf("son = %x , offset = %x \n",nodebuffer[1].getSon(),(size_t)nodebuffer[1].getSon()-(size_t)dir_section);
//	for(int i=1;i*SimpleMemoryManager<TreeNode<FileDescriptor> >::getNodeSize() <X2fsUtil::DirSectionLen ; i++ )
//	{
//		if(i==1)
//		{
//			printf("Before adjust,test node[1].getSon()(=%x)==NULL(=%x)? %d\n",nodebuffer[i].getSon(),NULL,nodebuffer[i].getSon()==NULL);
//		}
//		if(!nodebuffer[i].SimpleMemoryNode::isFree())
//		{
//			nodebuffer[i].setFather((FileNode*)
//					(nodebuffer[i].getDirectFather()!=NULL?(FileNode*)((size_t)nodebuffer[i].getDirectFather() + (size_t)dir_section ):(FileNode*)NULL));
//			nodebuffer[i].setNext(
//					(FileNode*)
//					(nodebuffer[i].getNext()!=NULL?(FileNode*)((size_t)nodebuffer[i].getNext() + (size_t)dir_section):(FileNode*)NULL) );
//			nodebuffer[i].setPrevious(
//					(FileNode*)
//					(nodebuffer[i].getPrevious()!=NULL?(FileNode*)((size_t)nodebuffer[i].getPrevious() + (size_t)dir_section):(FileNode*)NULL ) );
//			nodebuffer[i].setSon(
//					(FileNode*)
//					(nodebuffer[i].getSon()!=NULL?(FileNode*)((size_t)nodebuffer[i].getSon() + (size_t)dir_section):(FileNode*)NULL) );
//
//			printf("init pointer %d\n",i);
//		}
//		if(i==1)
//		{
//				printf("dump node[1](the root)\n");
//				printf("son = %x , offset = %x \n",nodebuffer[i].getSon(),(size_t)nodebuffer[i].getSon()-(size_t)dir_section);
//		}else if(i==2)
//		{
//			printf("dump node[2](the head)\n");
//			printf("father = %x , offset = %x \n",nodebuffer[i].getDirectFather(),(size_t)nodebuffer[i].getDirectFather()-(size_t)dir_section);
//		}
//	}
//
//	//printf("init pointer done\n");
//	SimpleMemoryManager<TreeNode<FileDescriptor> > dirsmm((size_t)dir_section,X2fsUtil::DirSectionLen,false,3);//必须使用有效的区作为基指针，而不能
//	//是0，因为内部节点需要使用绝对指针
//
//	//FileTree 		-- extends Tree
//	//set root as nodebuffer[0];
//	//the FileTree is done
//	Tree<FileDescriptor,SimpleMemoryManager> fileTree(&dirsmm,
//			(FileNode*)((size_t)dir_section+sizeof(FileNode) )
//			);//如果是以TreeNode作为基指针
//	printf("dump fileTree : head=%x(relative to dir_section)\n",(size_t)fileTree.getHead() - (size_t)dir_section);
//																							//则必须对其函数使用virtual，因为virtual告知编译器生成不同的偏移
//	//为什么必须使用virtual？因为非virtual函数被不同指针引用时生成的函数名都是相同的（父类中的那一个），然而，由于多继承的存在，
//	//一个类可能组合了不同的基类，它的类成员地址偏移是不一样的（因为不会为类成员生成符号，类可以多次实例化，所以其符号显然不能只有一个，因而也就没有
//	//转而使用偏移地址代替，然而对于静态的成员变量，它们拥有绝对的地址）。这里有三种解决方法：1.类成员变量（而不是函数）使用virtual 2.类成员函数使用virtual  3.禁止多继承
//	//显然g++使用的是virtual函数。
//
//	//上面的总结有错误
//	//实际上数据总是virtual的，总能正确引用。这是因为无论多继承中继承顺序如何，它总是几个类的集合，每一个类都有自己的分区。而强制指针转换时，
//	//g++会在指针前面处理确保向上转型正确（即将指针加减使其对齐到强制转换的分区）
//	//同理，向下转型则会把继承关系中的偏移还原回去，如果仔细观察c++生成的汇编代码，还会发现如果指针是NULL就什么不操作偏移。
//
//	//以上过程说明了强制转换是一个函数过程，只不过该函数使用宏实现。
//	//如果是简单指针到类指针的转换，就是直接赋值
//	//如果是不相关指针之间的转换，其结果也是直接赋值。
//
//
//
//	//This had been done
//
//	//start build the free space LinkedList
//	LinearSourceDescriptor *lsbarr=(LinearSourceDescriptor*)free_section;
//	printf("in building free space \n");
//	printf("[0]: %x ~ %x \n",lsbarr[0].getStart(),lsbarr[0].getLimit());
//	MallocToSimple<ListNode<LinearSourceDescriptor> > lsdsmm;
//	LinearSourceManager<LinearSourceDescriptor,MallocToSimple> fillAllocs(&lsdsmm,lsbarr[0].getStart(),lsbarr[0].getLimit());
//	auto lsdspace=fillAllocs.getSpace();
//	printf("constructured fileAllocation as : %x ~ %x \n",lsdspace.getStart(),lsdspace.getLimit());
//	if(lsbarr[1].getLimit()!=0 && lsbarr[1].getStart() > lsbarr[0].getStart() && lsbarr[0].getStart()-lsbarr[1].getStart()>=lsbarr[1].getLimit()-lsbarr[0].getLimit())
//	{
//		printf("preparing new %x ~ %x from fileAllocation\n",lsbarr[0].getStart(),lsbarr[1].getStart()-lsbarr[0].getStart());
//		fillAllocs.mnew(lsbarr[0].getStart(),lsbarr[1].getStart()-lsbarr[0].getStart());
//		printf("newed %x ~ %x from fileAllocation\n",lsbarr[0].getStart(),lsbarr[1].getStart()-lsbarr[0].getStart());
//	}
//	if(lsbarr[1].getLimit()!=0)
//	{
//		printf("finding free spaces...\n");
//		for(int i=2;i*sizeof(ListNode<LinearSourceDescriptor>) < X2fsUtil::FreeSpaceSectionLen && lsbarr[i].getLimit()>0;i++)
//		{
//			fillAllocs.mnew(lsbarr[i-1].getStart()+lsbarr[i-1].getLimit(),lsbarr[i].getStart()-lsbarr[i-1].getStart()-lsbarr[i-1].getLimit());
//		}
//	}
//	ListNode<LinearSourceDescriptor> *plstnd=fillAllocs.getHead();
//	printf("dump LinearSourceManager for freespace\n");
//	while(plstnd)
//	{
//		printf("(%x,%x) ",plstnd->getData().getStart(),plstnd->getData().getLimit());
//		plstnd=plstnd->getNext();
//	}
//	printf("\n");
//	/*
//	fillAllocs.mnew(0x3700,1024);
//	fillAllocs.mnew(0x3600,0x100);
//	fillAllocs.mnew(4096);
//	plstnd=fillAllocs.getHead();
//	printf("dump LinearSourceManager for freespace\n");
//	while(plstnd)
//	{
//		printf("(%x,%x) ",plstnd->getData().getStart(),plstnd->getData().getLimit());
//		plstnd=plstnd->getNext();
//	}
//	printf("\n");
//	*///Tested
//
//	printf("ALL init done\n");
//	//***********ALL DONE*********//
//
//	//create a file under root
//	const char *fname="first.first.second";
//	char *fdst=(char*)filenamemm.mnew(strlen(fname));
//	printf("filename base : %x\n",(size_t)filenamemm.getHead()->getData().getStart());
//	printf("allocated for \"%s\" is %d\n",fname,(size_t)fdst);
//	*(unsigned char*)((size_t)filename_section+(size_t)fdst)=strlen(fname);
//	printf("write length is %d\n",*(unsigned char*)((size_t)filename_section+(size_t)fdst));
//	strncpy((char*)((size_t)filename_section+(size_t)fdst+1),fname,strlen(fname));
//	printf("verify if \"%s\" is written\n",fname);
//	for(int i=0;i!=strlen(fname);i++)
//	{
//		putchar(*(unsigned char*)((size_t)filename_section+(size_t)fdst+1+i));
//	}
//	printf("\n");
//	size_t fspan=2;//2 sectors
//
//	size_t fsecStart=(size_t)fillAllocs.mnew(fspan*X2fsUtil::SecSize);
//	printf("requested fileAllocation : %x\n",fsecStart);
//	printf("dump SMM: start=%x,limit=%x,curSize=%d,\n",dirsmm.getStart(),dirsmm.getLimit(),dirsmm.getCurSize());
//	SimpleMemoryManager<TreeNode<FileDescriptor> >::Node *fnode=(SimpleMemoryManager<TreeNode<FileDescriptor> >::Node *)dirsmm.getNew();
//	fnode->setData(
//			FileDescriptor(
//					FileDescriptor::TYPE_FILE,
//					fsecStart,fspan,fsecStart,0,
//					(size_t)fdst,
//					0,0
//			)
//	);
//	printf("sizeof(filenode)=%d\n",sizeof(SimpleMemoryManager<TreeNode<FileDescriptor> >::Node));
//	printf("dump SMM: start=%x,limit=%x,curSize=%d,\n",dirsmm.getStart(),dirsmm.getLimit(),dirsmm.getCurSize());
//	printf("requested filenode offset(relative to dirbase) : %x,%x\n",(size_t)fnode,(size_t)fnode - (size_t)dir_section);
//	printf("fileTree head & root offset(relative to dirbase) : %x , %x \n", (size_t)fileTree.getHead()- (size_t)dir_section,
//			(size_t)fileTree.getHead()->getDirectFather()- (size_t)dir_section);
//	fileTree.getHead()->setSon(fnode);
//	fnode->setFather(fileTree.getHead());
//
//
//
//
//
//	//list all directories
//	TreeNode<FileDescriptor>* rootfs=fileTree.getHead()->getSon();
//	if(rootfs)
//	{
//		FileDescriptor fdroot=rootfs->getData();
//		char *p=(char*)(fdroot.getNameOffset()+filename_section);
//		char saver[20];
//		int n=*p;
//		for(int i=0;i!=n;i++)
//		{
//			putchar(*(p+i+1));
//		}
//		printf("\ttype=%d\tsectionStart=%x\tsectionSpan=%x\tfileStart=%x\tfileLen=%x\n",fdroot.getType(),fdroot.getSectionStart(),
//					fdroot.getSectionSpan(),fdroot.getFileStart(),fdroot.getFileLen());
//		putchar('\n');
//	}
//
//
//
//
//	for(int i=0;i*sizeof(TreeNode<FileDescriptor>) <X2fsUtil::DirSectionLen ; i++ )
//	{
//		nodebuffer[i].setFather(
//				(FileNode*)
//				((nodebuffer[i].getDirectFather())!=NULL?(FileNode*)((size_t)nodebuffer[i].getDirectFather() - (size_t)dir_section ):(FileNode*)NULL) );
//		nodebuffer[i].setNext((FileNode*)(nodebuffer[i].getNext()!=NULL?(FileNode*)((size_t)nodebuffer[i].getNext() - (size_t)dir_section):(FileNode*)NULL) );
//		nodebuffer[i].setPrevious((FileNode*)
//				(nodebuffer[i].getPrevious()!=NULL?(FileNode*)((size_t)nodebuffer[i].getPrevious() - (size_t)dir_section):(FileNode*)NULL ));
//		nodebuffer[i].setSon(
//				(FileNode*)
//				(nodebuffer[i].getSon()!=NULL?(FileNode*)((size_t)nodebuffer[i].getSon() - (size_t)dir_section):(FileNode*)NULL ) );
//	}
//
//	//write the buffer back to the image
//
//	fwrite(allbuf,IMG_SIZE,sizeof(char),img);
//	//or below
////	fseek(img,X2fsUtil::FileNameSection,SEEK_SET);
////	fwrite(filename_section,X2fsUtil::FileNameSectionLen,sizeof(char),img);
////	fwrite(dir_section,X2fsUtil::DirSectionLen,sizeof(char),img);
////	fwrite(free_section,X2fsUtil::FreeSpaceSectionLen,sizeof(char),img);
//
//	//exit program
//	fclose(img);
//	free(allbuf);
//	return 0;
//
//
//}
//
