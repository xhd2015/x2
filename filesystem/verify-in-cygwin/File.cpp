
#include <cstring>
#include <new>
#include <List.h>
#include <Memory.h>
#include "File.h"
#include <cstdlib>
#include <cassert>
#include <cstdio>
//extern template class TreeNode<FileDescriptor>;
//extern template class SimpleMemoryManager<TreeNode<FileDescriptor> >;


typedef SimpleMemoryManager<TreeNode<FileDescriptor> >::Node Node;
/**tested**/


X2fsUtil::X2fsUtil(const char* file):
imgFile(file),reservedLen(2*This::SecSize),dirbufLen(This::DirSectionLen),namebufLen(This::FileNameSectionLen),
freebufLen(This::FreeSpaceSectionLen),
mmnodesmm(TMSmm()),
filenamemm(FileNameMM(&mmnodesmm,0,namebufLen,false)),
listnodesmm(LLSmm()),
dirbuf(NULL),namebuf(NULL),freebuf(NULL),filebufLen(0),filebuf(NULL)
{
//	printf("in init\n");
	this->fpimg=fopen(this->imgFile,"r+");
	this->initBuffers();
//	printf("end init buffers\n");
	this->retriveDirSection();
//	printf("end init dir section\n");
	this->retriveFileNameSection();
//	printf("end init file name section\n");
	this->retriveFreeSpaceSection();//here done
//	printf("end init free space section\n");


}

X2fsUtil::~X2fsUtil()
{

	if(this->fpimg)
	{
//		printf("destruct \n");
		this->flush();  //自行调用flush
		fclose(fpimg);
		fpimg=NULL;
	}
}



void X2fsUtil::flush() {
	this->saveFreeSpaceSection();
	this->saveDirSection();
//	printf("flush\n");
	fseek(this->fpimg,this->reservedLen,SEEK_SET);
	fwrite(this->namebuf,this->namebufLen,sizeof(char),this->fpimg);
	fwrite(this->dirbuf,this->dirbufLen,sizeof(char),this->fpimg);
	fwrite(this->freebuf,this->freebufLen,sizeof(char),this->fpimg);
	fflush(this->fpimg);
	this->retriveDirSection();
}

void X2fsUtil::retriveFileNameSection() {
	const char *p=this->namebuf;
	int lastStart=0;
	const char *lastp=p;

	while(p-this->namebuf < this->namebufLen)
	{
		if(*p==0)
		{
			while(*(++p)==0);
			this->filenamemm.mnew(lastStart,(size_t)(p-lastp));
		}else{
			p+=*p;
		}
		lastStart=(size_t)p-(size_t)this->namebuf;
		lastp=p;
	}
}


void X2fsUtil::retriveFreeSpaceSection() {
	LinearSourceDescriptor *lsbarr=(LinearSourceDescriptor*)freebuf;
	new (&this->freemm) FreeSpaceMM(&this->listnodesmm,lsbarr[0].getStart(),lsbarr[0].getLimit());
	auto lsdspace=this->freemm.getSpace();
	if(lsbarr[1].getLimit()!=0 && lsbarr[1].getStart() > lsbarr[0].getStart() && lsbarr[0].getStart()-lsbarr[1].getStart()>=lsbarr[1].getLimit()-lsbarr[0].getLimit())
	{
		this->freemm.mnew(lsbarr[0].getStart(),lsbarr[1].getStart()-lsbarr[0].getStart());
	}
	if(lsbarr[1].getLimit()!=0)
	{
		for(int i=2;i*sizeof(ListNode<LinearSourceDescriptor>) < this->freebufLen && lsbarr[i].getLimit()>0;i++)
		{
			this->freemm.mnew(lsbarr[i-1].getStart()+lsbarr[i-1].getLimit(),lsbarr[i].getStart()-lsbarr[i-1].getStart()-lsbarr[i-1].getLimit());
		}
	}
}

void X2fsUtil::saveFreeSpaceSection()
{
	LinearSourceDescriptor* lsdarr=(LinearSourceDescriptor*)freebuf;
	lsdarr[0]=this->freemm.getSpace();
	ListNode<LinearSourceDescriptor> *pfreenode=this->freemm.getHead();
	int i=1;
	while(pfreenode)
	{
		lsdarr[i++]=pfreenode->getData();
		pfreenode=pfreenode->getNext();
	}
	new (&lsdarr[i]) LinearSourceDescriptor(0,0);
}

void X2fsUtil::retriveDirSection() {

//	FileNode *nodebuffer=(FileNode*)this->dirbuf;
	this->adjustDirbufOffset((int)(size_t)this->dirbuf);
	new (&this->dirsmm) FileNodeMM((size_t)this->dirbuf,this->dirbufLen,false,3);
	new (&this->fileTree) FileTree(&this->dirsmm,(FileNode*)(dirbuf+sizeof(FileNode) ));
//	printf("after init call get direct\n");
//	nodebuffer[2].getDirectFather();
//	nodebuffer[2].getDirectFather();
//	printf("nodebffer[2]==%x,head=%x\n",nodebuffer+2,this->fileTree.getHead());
//	FileNode * head= (FileNode*)this->fileTree.getHead();
//	new ((SimpleMemoryNode*)head) SimpleMemoryNode;
//	new ((TreeNode<FileDescriptor>*)head) TreeNode<FileDescriptor>(FileDescriptor(0,0,0,0,0,0,0,0));
//	printf("this head = %x \n",head);
//	printf("call this->getDirectFather()\n");
//
//	head->getDirectFather();
//	for(int i=FileNodeSize*1;i!=FileNodeSize*3;i++)
//	{
//		printf("%x ",*(dirbuf+i));
//	}
//	printf("\n");
//	printf("dirbuf + 2*sizeof(filenode) = %x,head = %x\n",(size_t)this->dirbuf+FileNodeSize*2,this->fileTree.getHead());
//	printf("dumpFileTree , head & root is %x ,%x\n",(size_t)this->fileTree.getHead() - (size_t)this->dirbuf,
//			(size_t)this->fileTree.getHead()->getDirectFather() - (size_t)this->dirbuf);
}

void X2fsUtil::saveDirSection() {
	this->adjustDirbufOffset(0 - (int)(size_t)this->dirbuf);
	printf("after adjusted back , save\n");
	FileNode *nodebuffer=(FileNode*)this->dirbuf;
	char *p;
	size_t plen;
	p=this->getFileName(nodebuffer[3].getData(), plen);
	printf("dump Node[1].next = %x , Node[2].father= %x Node[3].filename=%.*s\n",nodebuffer[1].getSon(),
			nodebuffer[2].getDirectFather(),
			plen,
			p);
}

char* X2fsUtil::getFileName(const FileDescriptor& fd, size_t& nlen)
{
	char *p=(char*)((size_t)namebuf+(size_t)fd.getNameOffset());
	nlen = (size_t)*(unsigned char*)p;
	return p+1;
}


bool X2fsUtil::createFileInRoot(const char* name, size_t secNum)
{
	size_t namelen=strlen(name);
	char *fdst=(char*)this->filenamemm.mnew(namelen);
//	printf("new fdst is %x \n",fdst);
	*(unsigned char*)((size_t)this->namebuf+(size_t)fdst)=namelen;
//	printf("namelen is %d,namebuf is %x \n",namelen,this->namebuf);
	strncpy((char*)((size_t)this->namebuf+(size_t)fdst+1),name,namelen);
//	printf("\t\twritten is %.*s\n",namelen,(size_t)this->namebuf+(size_t)fdst+1);
	size_t fsecStart=(size_t)this->freemm.mnew(secNum*X2fsUtil::SecSize);
//	printf("new fsecStart is %x\n",fsecStart);


//	printf("dump SMM: start=%x(relative to dirbuf),limit=%x,curSize=%d,\n",(size_t)dirsmm.getStart() - (size_t)dirbuf,dirsmm.getLimit(),dirsmm.getCurSize());
	FileNode *fnode=(FileNode*)this->dirsmm.getNew();

//	printf("new fnode is %x(relative to dirbuf)\n",(size_t)fnode - (size_t)this->dirbuf);
	fnode->setData(
			FileDescriptor(
					FileDescriptor::TYPE_FILE,
					fsecStart,secNum,fsecStart,0,
					(size_t)fdst,
					0,0
			)
	);
//	printf("dump fileTree , head & root : %x  %x\n",(size_t)this->fileTree.getHead() - (size_t)this->dirbuf
//			,(size_t)this->fileTree.getHead()->getDirectFather() - (size_t)this->dirbuf);
	this->fileTree.getHead()->insertSon(fnode);

//		printf("get son of head : %x , ->getDirectFather=%x , head is %x\n",this->fileTree.getHead()->getSon(),
//			this->fileTree.getHead()->getSon()->getDirectFather(),
//			this->fileTree.getHead());
//	size_t plen;
//	char *p=this->getFileName(fnode->getData(),plen);
//	printf("file name offset is %x,content is %.*s\n",fnode->getData().getNameOffset(),plen,p);

	return true;
}

void X2fsUtil::listRoot()
{
	FileNode *pfn=(FileNode *)this->fileTree.getHead();
	printf("/:\n");
	pfn=(FileNode *)pfn->getSon();
	size_t nlen=0;
	char *pname;
	while(pfn)
	{
		pname=this->getFileName(pfn->getData(), nlen);
		if(nlen!=0)
		{
			printf("\t%.*s %x  %x\n",nlen,pname,pfn->getData().getSectionStart(),pfn->getData().getSectionSpan());
		}
		pfn=(FileNode *)pfn->getNext();
	}
}

void X2fsUtil::initBuffers() {
	this->namebuf = (char*)malloc(This::namebufLen);
	this->dirbuf = (char*)malloc(This::dirbufLen);
	this->freebuf = (char*)malloc(This::freebufLen);
	assert(this->namebuf!=NULL);
	assert(this->dirbuf!=NULL);
	assert(this->freebuf!=NULL);
	fseek(this->fpimg,this->reservedLen,SEEK_SET);
//	printf("reservedLen = %x , FileNameSection = %x , namebufLen = %x , dirbufLen = %x , freebufLen = %x \n",this->reservedLen,
//			This::FileNameSection,this->namebufLen,this->dirbufLen,this->freebufLen);
	fread(this->namebuf,this->namebufLen,sizeof(char),this->fpimg);
	fread(this->dirbuf,this->dirbufLen,sizeof(char),this->fpimg);
	fread(this->freebuf,this->freebufLen,sizeof(char),this->fpimg);
}

void X2fsUtil::adjustDirbufOffset(int off) {
		FileNode *nodebuffer=(FileNode*)this->dirbuf;
//		printf("call before adjust\n");
		//nodebuffer[2].getDirectFather();
		(nodebuffer+2)->getDirectFather();
		for(int i=1;i*sizeof(FileNode) <dirbufLen ; i++ )
		{
			if(!nodebuffer[i].isFree())
			{
				nodebuffer[i].setFather((FileNode*)
						(nodebuffer[i].getDirectFather()!=NULL?(FileNode*)((size_t)nodebuffer[i].getDirectFather() + (size_t)off ):(FileNode*)NULL));
				nodebuffer[i].setNext(
						(FileNode*)
						(nodebuffer[i].getNext()!=NULL?(FileNode*)((size_t)nodebuffer[i].getNext() + (size_t)off):(FileNode*)NULL) );
				nodebuffer[i].setPrevious(
						(FileNode*)
						(nodebuffer[i].getPrevious()!=NULL?(FileNode*)((size_t)nodebuffer[i].getPrevious() + (size_t)off):(FileNode*)NULL ) );
				nodebuffer[i].setSon(
						(FileNode*)
						(nodebuffer[i].getSon()!=NULL?(FileNode*)((size_t)nodebuffer[i].getSon() + (size_t)off):(FileNode*)NULL) );
//			printf("init pointer %d\n",i);
			}
		}
//		printf("call in adjust\n");
		//nodebuffer[2].getDirectFather();
		(nodebuffer+2)->getDirectFather();
}

void X2fsUtil::mockMkfsX2fs(void* base,size_t secNum)
{
	/**
	 * clear data
	 */
	memset((void*) ((size_t)base+X2fsUtil::FileNameSection),0,X2fsUtil::FileNameSectionLen);
	SimpleMemoryManager<TreeNode<FileDescriptor> > smm((size_t)base+X2fsUtil::DirSection,X2fsUtil::DirSectionLen,true);

	/**
	 * set dir root,node[0] node[1] are preserved for use
	 */
	Node *proot = (Node*)((size_t)base+X2fsUtil::DirSection);//zero is preserved
	proot[0].SimpleMemoryNode::unfree();
	proot[1].SimpleMemoryNode::unfree();
	proot[2].SimpleMemoryNode::unfree();
	proot[1].setSon((Node*)(2*sizeof(Node)));//The first one points to the next one,the next one is root

	proot[2].setData(FileDescriptor(
			FileDescriptor::TYPE_DIR,
			0,0,0,0,0,
			0,0
	));
	proot[2].setFather((Node*)sizeof(Node));//the base is the dir_section,zero is preserved

	LinearSourceDescriptor *lsdarr=(LinearSourceDescriptor*)((size_t)base+X2fsUtil::FreeSpaceSection);
	new (lsdarr) LinearSourceDescriptor(X2fsUtil::FreeSpaceSection+X2fsUtil::FreeSpaceSectionLen  ,
			secNum*X2fsUtil::SecSize);
	new (lsdarr+1) LinearSourceDescriptor(0,0);
}
