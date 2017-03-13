
#include <cstring>
#include <new>
#include <List.h>
#include <Memory.h>
#include "File.h"
#include <cstdlib>
#include <cassert>
#include <exception>
#include <cstdio>
//extern template class TreeNode<FileDescriptor>;
//extern template class SimpleMemoryManager<TreeNode<FileDescriptor> >;


typedef SimpleMemoryManager<TreeNode<FileDescriptor> >::Node Node;
/**tested**/


X2fsUtil::X2fsUtil(const char* file):
imgFile(file),reservedLen(2*This::SecSize),dirbufLen(This::DirSectionLen),namebufLen(This::FileNameSectionLen),linkbufLen(This::LinkedInfoSectionLen),
freebufLen(This::FreeSpaceSectionLen),
mmnodesmm(TMSmm()),
filenamemm(FileNameMM(&mmnodesmm,0,namebufLen,false)),
listnodesmm(LLSmm()),
dirbuf(NULL),namebuf(NULL),freebuf(NULL),filebufLen(0),filebuf(NULL),linkbuf(NULL),linkarrLen(linkbufLen/sizeof(this->linkarr[0])),
errno(This::ERROR_NOERR)
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
	this->retriveLinkedInfoSection();


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
	fwrite(this->namebuf,sizeof(char),this->namebufLen,this->fpimg);
	fwrite(this->dirbuf,sizeof(char),this->dirbufLen,this->fpimg);
	fwrite(this->freebuf,sizeof(char),this->freebufLen,this->fpimg);
	fwrite(this->linkbuf,sizeof(char),this->linkbufLen,this->fpimg);
	fflush(this->fpimg);
	this->retriveDirSection();
}

void X2fsUtil::retriveFileNameSection() {
	const char *p=this->namebuf;
//	printf("p[0] p[1] p[2]= %d %d %d\n",p[0],p[1],p[2]);
	const char *lastp=NULL;//unset,should point to the first non-zero
	while(*p==0 && p - this->namebuf < this->namebufLen)p++;
	if(p - this->namebuf == this->namebufLen)//all are zeros,no allocated
	{
		return;//then just return
	}else{//find the first non-zero of p
		lastp=p;
	}
//	printf("dump the raw of filename section \n");
//	char last=0;
//	char sum=0;
//	for(int i=0;i!=this->namebufLen;i++)
//	{
//		if(*(this->namebuf+i)!=0)
//		{
//			printf("%x ",(size_t)*(this->namebuf+i));
//		}
//		else
//		{
//			printf("_ ");
//		}
//		last=*(this->namebuf+i);
//	}
//	printf("\n");
	while(p-this->namebuf < this->namebufLen)
	{
		if(*p==0)
		{
			this->filenamemm.mnew(lastp - this->namebuf,(size_t)(p-lastp));
//			printf("filename MM new : %x %x\n",lastp - this->namebuf,(size_t)(p-lastp));
			while(*p==0 && p - this->namebuf < this->namebufLen )p++;
			lastp = p;
		}else{
			p+=*p+1;
		}
//		printf("lastp = %x\n",(size_t)(lastp-this->namebuf));
	}
//	printf("new for 40 len is %x\n",filenamemm.mnew(40));
//	printf("dump filename MM(using MemoryManager<MemoryDescriptor>)\n");
//	TreeNode<MemoryDescriptor> *ptnode=filenamemm.getHead();
//	printf("head : %x : %x : %d\n",ptnode->getData().getStart(),ptnode->getData().getLimit(),ptnode->getData().isAllocable());
//	ptnode=(TreeNode<MemoryDescriptor> *)ptnode->getSon();
//	while(ptnode)
//	{
//		printf("%x : %x : %d\n",ptnode->getData().getStart(),ptnode->getData().getLimit(),ptnode->getData().isAllocable());
//		ptnode=(TreeNode<MemoryDescriptor> *)ptnode->getNext();
//	}
}

/**
 * 所有的空间必须和扇区对齐，否则可能导致writeFIle出错
 */
void X2fsUtil::retriveFreeSpaceSection() {
	LinearSourceDescriptor *lsbarr=(LinearSourceDescriptor*)freebuf;
	new (&this->freemm) FreeSpaceMM(&this->listnodesmm,lsbarr[0].getStart(),lsbarr[0].getLimit());
	auto lsdspace=this->freemm.getSpace();
	if(lsbarr[1].getLimit()!=0 && lsbarr[1].getStart() > lsbarr[0].getStart() && lsbarr[0].getStart()-lsbarr[1].getStart()>=lsbarr[1].getLimit()-lsbarr[0].getLimit())
	{
//		printf("freemm new in 1, newed %x,%x\n",lsbarr[0].getStart(),lsbarr[1].getStart()-lsbarr[0].getStart());
		this->freemm.mnew(lsbarr[0].getStart(),lsbarr[1].getStart()-lsbarr[0].getStart());
	}
	if(lsbarr[1].getLimit()!=0)
	{
		for(int i=2;i*sizeof(ListNode<LinearSourceDescriptor>) < this->freebufLen && lsbarr[i].getLimit()>0;i++)
		{
			this->freemm.mnew(lsbarr[i-1].getStart()+lsbarr[i-1].getLimit(),lsbarr[i].getStart()-lsbarr[i-1].getStart()-lsbarr[i-1].getLimit());
		}
	}
//	this->freemm.mnew(0x3700,40);
//	printf("dump FreeSpace(LinearSourceManager)\n");
//	printf("space is (%x,%x)\n",(size_t)this->freemm.getSpace().getStart(),(size_t)this->freemm.getSpace().getLimit());
//	ListNode<LinearSourceDescriptor> *plnode=this->freemm.getHead();
//	while(plnode)
//	{
//		printf("%x %x\n",(size_t)plnode->getData().getStart(),plnode->getData().getLimit());
//		plnode=plnode->getNext();
//	}
}


void X2fsUtil::saveFreeSpaceSection()
{
	LinearSourceDescriptor* lsdarr=(LinearSourceDescriptor*)freebuf;
	lsdarr[0]=this->freemm.getSpace();
	ListNode<LinearSourceDescriptor> *pfreenode=this->freemm.getHead();
//	printf("head of freemm is %x\n",(int)(size_t)pfreenode);
	int i=1;
	while(pfreenode)
	{
		lsdarr[i++]=pfreenode->getData();
//		printf("this node is %x,save free space %x,%x\n",pfreenode,(int)pfreenode->getData().getStart(),(int)pfreenode->getData().getLimit());
		pfreenode=pfreenode->getNext();
	}
	new (&lsdarr[i]) LinearSourceDescriptor(0,0);
}



void X2fsUtil::retriveLinkedInfoSection() {
	new (&this->linkmm) LinkedInfoMM(&this->listnodesmm,0,this->linkarrLen);//manage by number

	//====build the free space of the linked section
//	printf("linkarr off is %x(sec nums,relative to dirbase) \n",((size_t)this->linkarr - (size_t)this->dirbuf)/This::SecSize);
//	printf("sizeof(node) = %d,maxi = %d ,linkarr[0].start = %x,linkarr[1].start=%x \n",sizeof(this->linkarr[0]),this->linkarrLen,
//			this->linkarr[0].getStart(),this->linkarr[1].getStart());
	int i=0;
	while(i < this->linkarrLen && this->linkarr[i].getLimit()==0)i++;
	int lastNonZero=i;
	i+=1;
//	printf("i = %d,lastNonZero = %d \n",i,lastNonZero);
	while(i < this->linkarrLen )
	{
		if(this->linkarr[i].getLimit()==0)
		{
//			printf("in linkmm new %x,%x\n",lastNonZero,i - lastNonZero+1);
			this->linkmm.mnew(lastNonZero,i - lastNonZero + 1);//one more for the trailing 0
			while(i < this->linkarrLen && this->linkarr[i].getLimit()==0)i++;
			lastNonZero=i;
		}else{
			i++;
		}
//		printf("i = %d \n",i);
	}
//	printf("dump link mm\n");
//	printf("space is %x,%x\n",this->linkmm.getSpace().getStart(),this->linkmm.getSpace().getLimit());
//	ListNode<LinearSourceDescriptor> *p=this->linkmm.getHead();
//	while(p)
//	{
//		printf("(%x,%x)\n",p->getData().getStart(),p->getData().getLimit());
//		p = p->getNext();
//	}
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
//	printf("after adjusted back , save\n");
//	FileNode *nodebuffer=(FileNode*)this->dirbuf;
//	char *p;
//	size_t plen;
//	p=this->getFileName(nodebuffer[3].getData(), plen);
//	printf("dump Node[1].next = %x , Node[2].father= %x Node[3].filename=%.*s\n",nodebuffer[1].getSon(),
//			nodebuffer[2].getDirectFather(),
//			plen,
//			p);
}

char* X2fsUtil::getFileName(const FileDescriptor& fd, size_t& nlen)const
{
	if(fd.getNameOffset()==0)return NULL;
	char *p=(char*)((size_t)namebuf+(size_t)fd.getNameOffset());
	nlen = (size_t)*(unsigned char*)p;
	return p+1;
}

void X2fsUtil::listNode(const FileNode* p)const {
	size_t nlen=0;
	char *pname;
	if(p)
	{
		pname=this->getFileName(p->getData(), nlen);
		if(This::isDirectory(p))
		{
			printf("Dir:%.*s\n",nlen,pname);
		}else if(This::isFile(p))
		{
//			printf("File:%.*s %x  %x\n",nlen,pname,p->getData().getSectionStart(),p->getData().getSectionSpan());
			printf("File:%.*s %x  %x\n",nlen,pname,p->getData().getSectionList(),p->getData().getFileLen());
		}
	}
}
void X2fsUtil::listOnNode(const FileNode* p,int maxdeepth)const
{
	if(maxdeepth<=0)return;
	this->listNode(p);
	if(p  && This::isDirectory(p))
	{
		const FileNode * pfn=(FileNode*)p->getSon();
		while(pfn)
		{
			printf("\t");
			this->listNode(pfn);
			pfn=(FileNode *)pfn->getNext();
		}
		pfn=(FileNode*)p->getSon();
		while(pfn)
		{
			if(This::isDirectory(pfn))
			{
//				printf("calling list sub dir,deepth is %d\n",maxdeepth);
				this->listOnNode(pfn, maxdeepth-1);
			}
			pfn=(FileNode*)pfn->getNext();
		}
	}

}
bool X2fsUtil::hasFilename(FileNode * fnode,const char *name)const
{
	return this->locatePath(fnode, name)!=NULL;
}
/**
 * default
 *
 */
bool X2fsUtil::create(FileNode *p,char type,const char *name,size_t secSpan,int ctime)
{
	if(!p)return false;
	if(this->locatePath(p, name)!=NULL)//check existence of name
	{
		this->seterrno(This::ERROR_FILE_ALREDY_EXIST);
		return false;
	}
	size_t fsecStart=0;
	size_t linkInode=0;
	size_t namelen;
	char *fnamedst;
//	size_t plen;
//	printf("during created[1], node is : %.*s \n",plen,this->getFileName(p->getData(), plen));

	FileNode *fnode=(FileNode*)this->dirsmm.getNew();//request for new FileNode
//	printf("fnode is %x(relative to dirbase) \n",(size_t)fnode-(size_t)this->dirbuf);
	if(fnode==NULL){
		this->seterrno(This::ERROR_DIRTREESPACE);
		goto error;
	}
	if(type==FileDescriptor::TYPE_FILE)
	{
		if(secSpan<2)
		{
			secSpan=2;
		}
		fsecStart=(size_t)this->freemm.mnew(secSpan);//request for new space
	//	printf("fsecStart is %x\n",(int)fsecStart);
		if(fsecStart==0)//no enough space
		{
			this->seterrno(This::ERROR_FILEALLOCSPACE);
			goto error;
		}
		printf("dump link mm\n");
		printf("space is %x,%x\n",this->linkmm.getSpace().getStart(),this->linkmm.getSpace().getLimit());
		ListNode<LinearSourceDescriptor> *p=this->linkmm.getHead();
		while(p)
		{
			printf("(%x,%x)\n",p->getData().getStart(),p->getData().getLimit());
			p = p->getNext();
		}
		linkInode=(size_t)this->linkmm.mnew(2);
		if(linkInode==0)
		{
			this->seterrno(This::ERROR_LINKINFO_SPACE_NOT_ENOUGH);
			printf("error linkInode\n");
			goto error;
		}
	}else if(type==FileDescriptor::TYPE_DIR){
//		printf("creating dir %s\n",name);
		secSpan=0;
		fsecStart=0;
		linkInode=0;
	}

	namelen=strlen(name);
	fnamedst=(char*)this->filenamemm.mnew(namelen+1); //request for name space,the first byte is for length
//	printf("fdst is %x \n",(size_t)fdst);
	if(fnamedst==NULL)
	{
			this->seterrno(This::ERROR_FILENAMESPACE);
			goto error;
	}

	//===OK,all spaces are enough

//
//	printf("during created[2], node is : %.*s \n",plen,this->getFileName(p->getData(), plen));
//	printf("fdst is %x\n",fdst);
//	printf("node name fdst is %x\n",p->getData().getNameOffset());
	//==================Set filename
	*(unsigned char*)((size_t)this->namebuf+(size_t)fnamedst)=namelen;
	strncpy((char*)((size_t)this->namebuf+(size_t)fnamedst+1),name,namelen);

	//===================Set section link info
	if(linkInode!=0)
	{
		this->linkarr[linkInode] = LinearSourceDescriptor(fsecStart,secSpan);
		this->linkarr[linkInode + 1] = LinearSourceDescriptor(0,0);
	}
//	printf("during created[3], node is : %.*s \n",plen,this->getFileName(p->getData(), plen));
	//==================Set file node
	new ((TreeNode<FileDescriptor>*)fnode) TreeNode<FileDescriptor>(FileDescriptor(
					type,
					linkInode,0,
					(size_t)fnamedst,
					ctime,ctime
			)
	);

	this->insertNode(p, fnode);
	return true;
	error:
		if(fnode!=NULL)
			this->dirsmm.withdraw(fnode);
		if(fsecStart!=0)
			this->freemm.mdelete((char*)fsecStart,secSpan);
		if(linkInode!=0)
			this->linkmm.mdelete((char*)linkInode,2);
		if(fnamedst!=NULL)
			this->filenamemm.mdelete(fnamedst,namelen+1);
	return false;
}
/**
 * 如果任何一步出错，都应当把申请的空间换回去
 */
bool X2fsUtil::createFile(FileNode *p,const char *name,size_t secNum)
{
	return this->create(p,FileDescriptor::TYPE_FILE,name,secNum,0);
}
bool X2fsUtil::mkdir(FileNode * fatherDir,const char *dirname)
{
	return this->create(fatherDir,FileDescriptor::TYPE_DIR,dirname,0,0);
}
void X2fsUtil::freeNode(FileNode * node)
{
	if(node && node != this->fileTree.getHead())//You cannot free the root!!!
	{

		size_t plen;
		char *pname2;
		pname2=this->getFileName(node->getData(), plen);
		printf("in free node : %.*s\n",plen,pname2);
//
//		printf("type is %d \n",node->getData().getType());
		if(This::isDirectory(node))
		{
			FileNode * eachSon=(FileNode*)node->getSon();
			while(eachSon)
			{
				this->freeNode(eachSon);
				eachSon = (FileNode*)eachSon->getNext();
			}
		}
		int off=node->getData().getNameOffset();
		char *pname=this->namebuf + off;

//		printf("before memset , len is %d,str is %.*s\n",*pname,*pname,pname + 1);//dirs are not deleted
//		printf("after , len = %d ,str is \"%.*s\"(may not appear)\n",*pname,*pname,pname + 1);
		this->filenamemm.mdelete((char*)off, *pname + 1);
		memset(pname,0,*pname + 1);
//		printf("dump filename MM(using MemoryManager<MemoryDescriptor>)\n");
//		TreeNode<MemoryDescriptor> *ptnode=filenamemm.getHead();
//		printf("head : %x : %x : %d\n",ptnode->getData().getStart(),ptnode->getData().getLimit(),ptnode->getData().isAllocable());
//		ptnode=(TreeNode<MemoryDescriptor> *)ptnode->getSon();
//		while(ptnode)
//		{
//			printf("%x : %x : %d\n",ptnode->getData().getStart(),ptnode->getData().getLimit(),ptnode->getData().isAllocable());
//			ptnode=(TreeNode<MemoryDescriptor> *)ptnode->getNext();
//		}
		//============name cleared

		if(This::isFile(node))
		{
			int i=node->getData().getSectionList();
			size_t linkstart=i;
			printf("link i is %d\n",i);
			for(;i<this->linkarrLen && this->linkarr[i].getLimit()!=0;i++)
			{
				this->freemm.mdelete((char*)this->linkarr[i].getStart(),this->linkarr[i].getLimit());
				this->linkarr[i]=LinearSourceDescriptor(0,0);//reset as unused
			}
			size_t linklen = i - linkstart + 1;//including the trailing 0.
			//============free space returned(linked sections)
			printf("linkmm delete %d,%d\n",linkstart,linklen);
			this->linkmm.mdelete((char*)linkstart, linklen);
		}
		//==============linked info returned

		//here is a question : if one section is shared by many files,should we delete it too ? woo ~ ~
		//we'll use reference count to do that later.
		this->fileTree.free(node);
		//==============file tree withdrawn

	}
}
void  X2fsUtil::insertNode(FileNode *dst,FileNode *fnode)
{
	if(dst && fnode)
	{
		if(!dst->hasSon())
		{
			dst->insertSon(fnode);
		}else{
			dst->getSon()->insertNext(fnode);
		}
	}
}
void X2fsUtil::removeNode(FileNode * node)
{
	if(node && node != this->fileTree.getHead())//You cannot remove the root!!!
	{
		FileNode * prev=(FileNode*)node->getPrevious(),*father=NULL,*next=NULL;
		if(prev!=NULL)
		{
			prev->removeNext();
		}else{
			father=(FileNode*)node->getDirectFather();
			next = (FileNode*)node->getNext();
			father->setSon((FileNode*)next);
			if(next)
			{
				next->setFather(father);
				next->setPrevious(NULL);
			}
		}
	}
}

bool  X2fsUtil::rename(FileNode *node,const char *newname)
{
	printf("test getNew \n");
	this->linkmm.getMemoryManager()->getNew();
	printf("test after getNew\n");
	size_t newlen=strlen(newname);
	size_t orilen;
	char *pori;
	pori=this->getFileName(node->getData(),orilen);
	if(strncmp(newname,pori,newlen)==0)
	{
		return true;//the names have been the same
	}
	//alloc new space
	printf("before extend\n");
	size_t newoff=(size_t)this->filenamemm.extend(node->getData().getNameOffset(),orilen+1, newlen - orilen, this->namebuf,false);
	char *pnew=this->namebuf + newoff;
	printf("after extend\n");
//	printf("orginal off is %x,new off is %x\n",node->getData().getNameOffset(),newoff);
	if(pnew)
	{
		*pnew = newlen;
		strncpy(pnew + 1,newname,newlen);
		node->getData().setNameOffset(newoff);
		return true;
	}else{
		return false;
	}
}

bool X2fsUtil::move(FileNode *p,FileNode* dstDir,const char *newname)
{
	if(!p || !dstDir|| p==dstDir)
	{
		this->seterrno(This::ERROR_GENERAL_ERROR);
		return false;
	}
	if(!This::isDirectory(dstDir))
	{
		this->seterrno(This::ERROR_DST_IS_NOT_DIRECTORY);
		return false;
	}
	if(this->hasFilename(dstDir,newname))
	{
		this->seterrno(This::ERROR_FILE_ALREDY_EXIST);
		return false;
	}
	this->removeNode(p);
	this->insertNode(dstDir,p);
	if(newname)
		this->rename(p, newname);
	return true;


}
void X2fsUtil::dumpFileInfo(FileNode * fnode)
{
	const FileDescriptor & fd=fnode->getData();
	size_t nlen;char *p;
	p=this->getFileName(fd, nlen);
	printf("file name : %.*s \n",nlen,p);
	printf("linked section list start : %d\nsections are : \n",fd.getSectionList());
	int i=fd.getSectionList();
	while(i<this->linkarrLen && this->linkarr[i].getLimit()!=0)
	{
		printf("(%x,%x)   ",this->linkarr[i].getStart(),this->linkarr[i].getLimit());
		i++;
	}
	printf("\n");
	printf("type : %d\n",fd.getType());
	printf("length : %d \n",fd.getFileLen());
	printf("created time : %d\n",fd.getCreatedTime());
	printf("last modified time : %d\n",fd.getLastModefiedTime());
}


bool X2fsUtil::createFileInRoot(const char* name, size_t secNum)
{
	return this->createFile((FileNode*)this->fileTree.getHead(), name, secNum);
//	size_t namelen=strlen(name);
//	char *fdst=(char*)this->filenamemm.mnew(namelen);
////	printf("new fdst is %x \n",fdst);
//	*(unsigned char*)((size_t)this->namebuf+(size_t)fdst)=namelen;
////	printf("namelen is %d,namebuf is %x \n",namelen,this->namebuf);
//	strncpy((char*)((size_t)this->namebuf+(size_t)fdst+1),name,namelen);
////	printf("\t\twritten is %.*s\n",namelen,(size_t)this->namebuf+(size_t)fdst+1);
//	size_t fsecStart=(size_t)this->freemm.mnew(secNum*X2fsUtil::SecSize);
////	printf("new fsecStart is %x\n",fsecStart);
//
//
////	printf("dump SMM: start=%x(relative to dirbuf),limit=%x,curSize=%d,\n",(size_t)dirsmm.getStart() - (size_t)dirbuf,dirsmm.getLimit(),dirsmm.getCurSize());
//	FileNode *fnode=(FileNode*)this->dirsmm.getNew();
//
////	printf("new fnode is %x(relative to dirbuf)\n",(size_t)fnode - (size_t)this->dirbuf);
//	fnode->setData(
//			FileDescriptor(
//					FileDescriptor::TYPE_FILE,
//					fsecStart,secNum,fsecStart,0,
//					(size_t)fdst,
//					0,0
//			)
//	);
////	printf("dump fileTree , head & root : %x  %x\n",(size_t)this->fileTree.getHead() - (size_t)this->dirbuf
////			,(size_t)this->fileTree.getHead()->getDirectFather() - (size_t)this->dirbuf);
//
//	if(this->fileTree.getHead()->getSon()==NULL)
//	{
//		this->fileTree.getHead()->insertSon(fnode);
//	}else{
//		this->fileTree.getHead()->getSon()->getLast()->insertNext(fnode);
//	}
//
////		printf("get son of head : %x , ->getDirectFather=%x , head is %x\n",this->fileTree.getHead()->getSon(),
////			this->fileTree.getHead()->getSon()->getDirectFather(),
////			this->fileTree.getHead());
////	size_t plen;
////	char *p=this->getFileName(fnode->getData(),plen);
////	printf("file name offset is %x,content is %.*s\n",fnode->getData().getNameOffset(),plen,p);
//
//	return true;
}

bool X2fsUtil::hasFilename(int argc,const char *argv[],const char *name)const
{
	return this->hasFilename(this->getPathNode(argc, argv), name);
}

bool  X2fsUtil::createFile(int argc,const char* argv[],int secSpan)
{
	int errlv;
	FileNode *p=this->locatePath(this->getRootBase(),argc-1,argv,errlv);
	if(p==NULL)
	{
		this->seterrno(This::ERROR_PATH_PARENT_NOT_EXIST);
//		printf("not found parent\n");
		return false;
	}else{
		FileNode *pson=this->locatePath(p, argv[argc-1]);
		if(pson!=NULL)
		{
			this->seterrno(This::ERROR_FILE_ALREDY_EXIST);
//			printf("exist already\n");
			return false;
		}else{
			size_t plen;
			printf("on node : %.*s \t",plen,this->getFileName(p->getData(), plen));
			printf("create file %s\n",argv[argc-1]);
			bool flag=this->createFile(p, argv[argc-1], secSpan);

			printf("after created, node is : %.*s ,succeed?%d, errno is %d\n",plen,this->getFileName(p->getData(), plen),flag,
					this->geterrno());

			return flag;
		}
	}
}
bool  X2fsUtil::createDir(int argc,const char* argv[])
{
	int errlv;
	FileNode *p=this->locatePath(this->getRootBase(),argc-1,argv,errlv);
	if(p==NULL)
	{
		this->seterrno(This::ERROR_PATH_PARENT_NOT_EXIST);
//		printf("not found parent\n");
		return false;
	}else{
		FileNode *pson=this->locatePath(p, argv[argc-1]);
		if(pson!=NULL)
		{
			this->seterrno(This::ERROR_FILE_ALREDY_EXIST);
//			printf("exist already\n");
			return false;
		}else{
			printf("mkdir %s\n",argv[argc-1]);
			return this->mkdir(p, argv[argc-1]);
		}
	}
}

bool  X2fsUtil::deleteFile(int argc,const char * argv[])
{
	auto pnode=this->getPathNode(argc, argv);
	if(pnode==NULL)
	{
		return false;
	}else{
		this->freeNode(pnode);
		this->removeNode(pnode);
		return true;
	}
}
bool X2fsUtil::rename(int argc,const char *argv[],const char *newname)
{
	return this->rename(this->getPathNode(argc, argv), newname);
}
bool X2fsUtil::move(int argcSrc,const char *argvSrc[],int argcDst,const char *argvDst[],const char *newname)
{
	return this->move(this->getPathNode(argcSrc, argvSrc),this->getPathNode(argcDst, argvDst), newname);
}
int  X2fsUtil::tellType(int argc,const char* argv[])const
{
	auto pnode=this->getPathNode(argc, argv);
	if(pnode==NULL)
	{
		return this->geterrno();
	}
	if(This::isDirectory(pnode))
	{
		return This::PATH_TYPE_DIR;
	}else if(This::isFile(pnode))
	{
		return This::PATH_TYPE_FILE;
	}else{
		return This::PATH_TYPE_UNKNOWN;
	}
}
void X2fsUtil::dumpFileInfo(int argc,const char *argv[])
{
	this->dumpFileInfo(this->getPathNode(argc, argv));
}
void X2fsUtil::listNode(int argc,const char * argv[],int maxdeepth)const
{
	int errlv;
	FileNode *p=this->locatePath(this->getRootBase(),argc-1,argv,errlv);
//	printf("in p, p==rootBase?%d \n",p == this->getRootBase());
//	this->listOnNode(p);
//	printf("\n");
	if(p==NULL)
	{
//		printf("No parent path for such file or directory\n");
		return;
	}else{
		FileNode *pson=this->locatePath(p, argv[argc-1]);
//		printf("locate for %s\n",argv[argc-1]);
		if(pson!=NULL)
		{
			if(This::isFile(pson))
			{
				this->listNode(pson);
			}else{
				this->listOnNode(pson,maxdeepth);
			}
		}else{
			printf("No such file or directory\n");
		}
	}

}
void X2fsUtil::listRoot()const
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
//			printf("\t%.*s %x  %x\n",nlen,pname,pfn->getData().getSectionStart(),pfn->getData().getSectionSpan());
			printf("\t%.*s %x  %x\n",nlen,pname,pfn->getData().getSectionList(),pfn->getData().getFileLen());
		}
		pfn=(FileNode *)pfn->getNext();
	}
}


void X2fsUtil::initBuffers() {
	this->namebuf = (char*)malloc(This::namebufLen);
	this->dirbuf = (char*)malloc(This::dirbufLen);
	this->freebuf = (char*)malloc(This::freebufLen);
	this->linkbuf = (char*)malloc(This::linkbufLen);
	assert(this->namebuf!=NULL);
	assert(this->dirbuf!=NULL);
	assert(this->freebuf!=NULL);
	assert(this->linkbuf!=NULL);
	fseek(this->fpimg,this->reservedLen,SEEK_SET);
//	printf("reservedLen = %x , FileNameSection = %x , namebufLen = %x , dirbufLen = %x , freebufLen = %x \n",this->reservedLen,
//			This::FileNameSection,this->namebufLen,this->dirbufLen,this->freebufLen);
	fread(this->namebuf,sizeof(char),this->namebufLen,this->fpimg);
	fread(this->dirbuf,sizeof(char),this->dirbufLen,this->fpimg);
	fread(this->freebuf,sizeof(char),this->freebufLen,this->fpimg);
	fread(this->linkbuf,sizeof(char),this->linkbufLen,this->fpimg);
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
//typename
X2fsUtil::FileNode* X2fsUtil::locatePath(FileNode* base,int argc, const char* argv[], int& errorLevel)const
{
	if(base==NULL || argc<0)
		{
			errorLevel=-1;
			return NULL;
		}
	if(argc==0)return base;
	int i=0;
	FileNode *pcur=base;

	while(i<argc && pcur && This::isDirectory(pcur))
	{
//		printf("i = %d , pcur is dir? %d \n",i,This::isDirectory(pcur));
		pcur=this->locatePath(pcur, argv[i]);
		i++;
	}
	errorLevel = i;
	return pcur;
}
X2fsUtil::FileNode* X2fsUtil::locatePath(FileNode* base, const char* name)const
{
	if(!base)return NULL;
	FileNode *p=(FileNode *)base->getSon();
	size_t len;
	const char *pname;
//	printf("finding name %s\n",name);
	while(p)
	{
		pname = this->getFileName(p->getData(), len);
//		printf("cmp %.*s,n is %d\n",len,pname,len);
		if(len == strlen(name)  && strncmp(pname,name,len)==0)
		{
			break;
		}
		p = (FileNode*)p->getNext();
	}
	return p;
}
X2fsUtil::FileNode * X2fsUtil::getPathParentNode(int argc,const char * argv[])const
{
	int errlv;
	return this->locatePath(this->getRootBase(),argc-1,argv,errlv);
}
X2fsUtil::FileNode * X2fsUtil::getPathNode(int argc,const char * argv[])const
{
	if(argc==0)return this->getRootBase();
	int errlv;
	auto p=this->locatePath(this->getRootBase(),argc-1,argv,errlv);
	if(p==NULL)
	{
		this->seterrno(This::ERROR_PATH_PARENT_NOT_EXIST);
		return NULL;
	}
	auto pson=this->locatePath(p, argv[argc-1]);
	if(pson==NULL)
	{
		this->seterrno(This::ERROR_PATH_FILE_NOT_EXIST);
		return NULL;
	}
	this->seterrno(This::ERROR_NOERR);
//	printf("in getPathNode %s,returned is %x\n",argv[argc-1],(size_t)pson-(size_t)this->dirbuf);
	return pson;


}

size_t  X2fsUtil::writeToFile(const char* buf,size_t objsize, size_t nobj, int argc, const char* argv[],
		size_t foff)
{
	return this->writeToFile(buf, objsize, nobj, this->getPathNode(argc, argv), foff);
}

size_t X2fsUtil::readFromFile(char* buf,size_t objsize, size_t nobj,int argc, const char* argv[], FileNode* fnode,
		size_t foff)
{
	return this->readFromFile(buf, objsize,nobj,  this->getPathNode(argc, argv), foff);
}
/**
 * The most basic problems are
 * 			alignment
 * 			extra size for section
 * 	 There is also one solution: for linked section files,do not link them at the end,but at a specific section
 * 	 And this solution seems more beautiful and nature
 */
size_t X2fsUtil::writeToFile(const char* buf,
		size_t objsize, size_t nobj, FileNode* fnode, size_t foff)
{
//	printf("in write to file\n");
//	printf("fnode is %x(relatively)\n",(size_t)fnode - (size_t)this->dirbuf);
	if(fnode || !This::isFile(fnode))
	{
		FileDescriptor &fd=fnode->getData();
		const size_t myobjsize=1;
		const size_t mynobj = nobj * objsize;
		size_t newlen=foff;

//		printf("before ilink got\n");
		size_t ilink=fd.getSectionList();;
//		printf("section list inode is %d,data[0] is %d,%d\n",ilink,this->linkarr[ilink].getStart(),this->linkarr[ilink].getLimit());

		size_t thisSectionFileLen = this->linkarr[ilink].getLimit() * This::SecSize - foff ;
		size_t thisSectionStart = this->linkarr[ilink].getStart() * This::SecSize + foff;
		size_t thisObjLeft = mynobj;
		const char *thisBuf=buf;
		while(true)
		{
//			printf("seek at %d,leftSize is %d,this section file len is %d,ilink now is %d\n",thisSectionStart,thisObjLeft,thisSectionFileLen,
//					ilink);
			fseek(this->fpimg,thisSectionStart,SEEK_SET);
			if(thisSectionFileLen > thisObjLeft)
			{
				thisSectionFileLen = thisObjLeft;
			}
			size_t written = fwrite(thisBuf,myobjsize,thisSectionFileLen,this->fpimg);
			thisBuf += written;
			thisObjLeft -= written;
			newlen += written;
			ilink++;
			if(thisObjLeft>0)
			{
				if(ilink == this->linkarrLen || this->linkarr[ilink].getLimit()==0)//require for more space
				{
					LinkedList<LinearSourceDescriptor,MallocToSimple> list(this->freemm.getMemoryManager());
					int extraSec=(thisObjLeft / This::SecSize) ;
					if(thisObjLeft % This::SecSize > 0)
					{
						extraSec++;
					}

//					printf("new linked source,size is %d,extraSec is %d\n",thisObjLeft,extraSec);
					bool flagnewList=this->freemm.mnewLinked(extraSec, list,0);
					if(flagnewList)
					{
						size_t nlist=list.getSize();
//						printf("got list size is %d\n",nlist);
//						printf("ask link for extend : start=%d,size=%d,extsize=%d\n",fd.getSectionList(),ilink - fd.getSectionList() + 1,nlist);
						int newilink=(size_t)this->linkmm.extend(fd.getSectionList(), ilink - fd.getSectionList() + 1,nlist,
								NULL, false);
						if(newilink==0)
						{
							this->seterrno(This::ERROR_LINKINFO_SPACE_NOT_ENOUGH);
							return (mynobj - thisObjLeft)/objsize;
						}
//						printf("new ilink is %d\n",newilink);
						if(newilink != fd.getSectionList())
						{
							memcpy(this->linkarr + newilink,this->linkarr + fd.getSectionList(),ilink - fd.getSectionList() );
							memset(this->linkarr + fd.getSectionList(),0,ilink - fd.getSectionList());
						}
						ListNode<LinearSourceDescriptor> *pnewnode=list.getHead();
						ilink = newilink + ilink - fd.getSectionList();
						while(pnewnode) //copy from list to that memory
						{
//							printf("copy extra ilink to the space,new(at %d) is %d,%d\n",ilink,pnewnode->getData().getStart(),pnewnode->getData().getLimit());
							this->linkarr[ilink] = pnewnode->getData();
							pnewnode = pnewnode->getNext();
							ilink++ ;
						}
						ilink = newilink + ilink - fd.getSectionList() - 1; //reset to the right position
//						printf("reset ilink is %d\n",ilink);
						fd.setSectionList(newilink); // change fd to the new pointer
					}else{
						this->seterrno(This::ERROR_FILEALLOCSPACE);
						if(fd.getFileLen()<newlen)
						{
							fd.setFileLen(newlen);
						}
						return (mynobj - thisObjLeft)/objsize;
					}
				}
				//here,we continue like nothing happened
				thisSectionFileLen = this->linkarr[ilink].getLimit() * This::SecSize ;
				thisSectionStart = this->linkarr[ilink].getStart() * This::SecSize;
			}else{
				if(fd.getFileLen()<newlen)
					{
						fd.setFileLen(newlen);
					}
				return (mynobj - thisObjLeft)/objsize;
			}
		}//while
	}//if
	return 0;
}

size_t  X2fsUtil::readFromFile(char* buf, size_t objsize, size_t nobj,FileNode* fnode, size_t foff)
{
//	printf("test getNew at readFromFile \n");
//	this->linkmm.getMemoryManager()->getNew();
//	printf("test after getNew\n");
	if(fnode || !This::isFile(fnode))
	{
		FileDescriptor &fd=fnode->getData();
		size_t requestLen = nobj * objsize + foff;
		const size_t myobjsize=1;
		const size_t mynobj = nobj * objsize;
		int ilink=fd.getSectionList();

		size_t thisSectionFileLen;
		size_t thisSectionStart;
		size_t thisObjLeft = mynobj;
		char *thisBuf=buf;
		while(thisObjLeft > 0 && ilink <this->linkarrLen && this->linkarr[ilink].getLimit()!=0)
		{
			thisSectionFileLen = this->linkarr[ilink].getLimit() * This::SecSize ;
			thisSectionStart = this->linkarr[ilink].getStart() * This::SecSize;
			fseek(this->fpimg,thisSectionStart,SEEK_SET);
			if(thisSectionFileLen > thisObjLeft)
			{
				thisSectionFileLen = thisObjLeft;
			}
			size_t written = fread(thisBuf,myobjsize,thisSectionFileLen,this->fpimg);
			thisBuf += written;
			thisObjLeft -= written;
			ilink++;
		}
		return (mynobj - thisObjLeft)/objsize;
	}
	return 0;
}

//X2fsUtil::FileNode* X2fsUtil::locatePath(FileNode* base,int argc, const char* argv[], int& errorLevel)
//{
//		return ((const X2fsUtil *)this)->locatePath(base, argc,argv,errorLevel);
//}
//X2fsUtil::FileNode* X2fsUtil::locatePath(FileNode* base, const char* name)
//{
//	return ((const X2fsUtil *)this)->locatePath(base,name);


void X2fsUtil::mockMkfsX2fs(void* base,size_t secNum)
{
	//==================================init name section
	/**
	 * clear filenames in fileNameSection
	 *         but keep the first two,because when returned NULL,it will be treated as failure
	 */
	memset((void*) ((size_t)base+X2fsUtil::FileNameSection),0,X2fsUtil::FileNameSectionLen);
	char *pbase=(char*)((size_t)base+X2fsUtil::FileNameSection);
	pbase[0]=1;
	pbase[1]='/';


	//===================================init dir section
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
			0,0,0,
			0,0
	));
	proot[2].setFather((Node*)sizeof(Node));//the base is the dir_section,zero is preserved

	//======================================init free space section
	//Now the managed source has changed to sec number,not sec numer multiply with secsize
	LinearSourceDescriptor *lsdarr=(LinearSourceDescriptor*)((size_t)base+X2fsUtil::FreeSpaceSection);
	new (lsdarr) LinearSourceDescriptor(X2fsUtil::FileAllocSection / X2fsUtil::SecSize ,
			secNum);
	new (lsdarr+1) LinearSourceDescriptor(0,0);//This allows it return NULL,because it is at least a FreeSpaceSectionLen

	//======================================init linked info section
	LinearSourceDescriptor *lkinfarr=(LinearSourceDescriptor*)((size_t)base+X2fsUtil::LinkedInfoSection);
	memset(lkinfarr,0,X2fsUtil::LinkedInfoSectionLen);//set all to 0
	new (lkinfarr) LinearSourceDescriptor(0xaa55,1);//0xaa55 is the verifying information,文件第一个扇区不用，所有的都是第一项不用
	new (lkinfarr + 1) LinearSourceDescriptor(0xaa55,0);
}
//template <template <class>class _Allocator>
//void X2fsUtil::getLinkedList(LinearSourceDescriptor *buffer,int i,LinkedList<LinearSourceDescriptor,_Allocator> &list,size_t maxlen)
//{
//	while(i < maxlen)
//	{
//		list.append(buffer[i]);
//		i++;
//	}
//}



