#include <def.h>
#include <cstring>
#include <new>
#include <List.h>
#include <Memory.h>
#include <EnvInterface64Impl.h>
#include <File.h>
#include <cstdlib>
#include <cassert>
#include <exception>
#include <cstdio>



#include <macros/all.h>
//extern template class TreeNode<FileDescriptor>;
//extern template class SimpleMemoryManager<TreeNode<FileDescriptor> >;

#if defined(CODE64)
	template class X2fsUtil<EnvInterface64Impl>;
#endif

bool X2fsMetaInfo::checkMetainfo(const X2fsMetaInfo* info)
{
	bool checkRes = (info->reservedSec == SECNUM_RESERVED_CONST) &&
					(info->metaSec == SECNUM_META_CONST ) &&
					(info->len == PARTS_REQUIRED) &&
					(info->validFlag == VALID_FLAG);

	return checkRes;
}

#if defined(CODE64)
void X2fsMetaInfo::dumpInfo(EnvInterface64Impl *env)
{
	//每次最多打印3个，这是printf_simple的实现限制
	env->printf_simple("X2fsMetaInfo{"
			"reserved:%d, "
			"metainfo:%d, "
			"sec_filename:%d, ",reservedSec,metaSec,secnums[INDEX_NAME]);
	env->printf_simple(
			"sec_dir:%d, "
			"sec_freespace:%d, "
			"sec_filealloc:%d, ",secnums[INDEX_DIR],secnums[INDEX_FREE],secnums[INDEX_FILE]);
	env->printf_simple(
			"sec_link:%d, "
			"sec_optional_secd:%d, "
			"lba_low:%d, ",secnums[INDEX_LINK],optional[INDEX_OPTIONAL_SECD],lbaStartLow);
	env->printf_simple(
			"lba_high:%d, "
			"total_secs:%d, "
			"valid_flag:%d "
			"}",lbaStartHigh,wholeSecnums,(u32_t)validFlag);
}
#endif


#if defined(CODE64)
typedef SimpleMemoryManager<TreeNode<FileDescriptor> >::FullNode FullNode;

// DEBUG
template <class __EnvInterface>
X2fsUtil<__EnvInterface>::X2fsUtil(_EnvInterface *env,u8_t driver,u32_t lbaBase):
			env(env),driver(driver),lbaBaseAddress(lbaBase),
			mmnodesmm(env),
			listnodesmm(env),
			processErrno(This::ERROR_NOERR)
	{

		env->printf_simple("reading meta info...\n");
		// 先读取元信息区域
		metabuf=env->malloc(CONST_SECSIZE);

		env->readSectors(EnvInterface::CUR_SEG, metabuf, driver,
				lbaBase + X2fsMetaInfo::SECNUM_RESERVED_CONST,X2fsMetaInfo::SECNUM_META_CONST,  0);

		if(metainfo==NULL || !X2fsMetaInfo::checkMetainfo(metainfo))
			env->systemAbort("cannot valid metainfo sector", -2);

		size_t wholeSecs=0;
		for(size_t i=0;i<metainfo->len ;i++)
		{
			wholeSecs+=metainfo->secnums[i];
		}

		// 分配空间
		buffers[0]= env->malloc(wholeSecs * CONST_SECSIZE);


		// NOTICE 如果你改变了X2fsMetaInfo的设计，必须保证所有的可选分区在必选分区之后
		// 此处仅读入必选分区
		env->readSectors(EnvInterface::CUR_SEG, buffers[0], driver,
				lbaBase + X2fsMetaInfo::SECNUM_RESERVED_CONST+X2fsMetaInfo::SECNUM_META_CONST,wholeSecs,0);

		// 依次分配每个分区的buffer地址
		for(size_t i=1;i<metainfo->len ; i++)
		{
			buffers[i]=buffers[i-1]+metainfo->secnums[i-1]*CONST_SECSIZE;
		}
		linkarr = (LinearSourceDescriptor*)buffers[X2fsMetaInfo::INDEX_LINK];
		linkarrLen = metainfo->secnums[X2fsMetaInfo::INDEX_LINK]*CONST_SECSIZE/x2sizeof(linkarr[0]);


		new (&filenamemm) FileNameMM(&mmnodesmm,0,metainfo->secnums[INDEX_NAME]*CONST_SECSIZE,false);

		initWithBuffersAlloced();

	}
template <class __EnvInterface>
X2fsUtil<__EnvInterface>::X2fsUtil(_EnvInterface *env,u8_t driver,u32_t lbaBase,X2fsMetaInfo *metainfo,u8_t *buffers[]):
				env(env),driver(driver),lbaBaseAddress(lbaBase),
				metainfo(metainfo),
				mmnodesmm(env),
				filenamemm(&mmnodesmm,0,metainfo->secnums[INDEX_NAME]*CONST_SECSIZE,false),
				listnodesmm(env),
				processErrno(This::ERROR_NOERR)

		{
			if(metainfo==NULL || !X2fsMetaInfo::checkMetainfo(metainfo))
				env->systemAbort("cannot valid metainfo sector", -2);
			for(size_t i=0;i<metainfo->len;++i)
				this->buffers[i]=buffers[i];
			linkarr =(LinearSourceDescriptor*) buffers[X2fsMetaInfo::INDEX_LINK];
			linkarrLen = metainfo->secnums[X2fsMetaInfo::INDEX_LINK]*CONST_SECSIZE/x2sizeof(linkarr[0]);

			initWithBuffersAlloced();
		}
template <class __EnvInterface>
void X2fsUtil<__EnvInterface>::initWithBuffersAlloced()
		{
			//	printf("in init\n");
		//	std::cout << "in init"<<std::endl;
			env->printf_simple("in init\n");


		//	this->fpimg=fopen(this->imgFile,"r+");

		//	assert(this->fpimg!=NULL);

//			this->initBuffers();
//		//	printf("end init buffers\n");


			this->retriveDirSection();
		//	printf("end init dir section\n");
			this->retriveFileNameSection();
		//	printf("end init file name section\n");
			this->retriveFreeSpaceSection();//here done
		//	printf("end init free space section\n");
			this->retriveLinkedInfoSection();
		}

//X2fsUtil::X2fsUtil(EnvInterface *env,u8_t driver,u32_t lbaBase):
//mmnodesmm(TMSmm()),
//filenamemm(FileNameMM(&mmnodesmm,0,namebufLen,false)),
//listnodesmm(LLSmm()),
//{
//
//
//
//}

template <class __EnvInterface>
X2fsUtil<__EnvInterface>::~X2fsUtil()
{

//	if(this->fpimg)
//	{
//		printf("destruct \n");
		this->flush();  //自行调用flush
//		fclose(fpimg);
//		fpimg=NULL;
//	}
}


template <class __EnvInterface>
void X2fsUtil<__EnvInterface>::flush() {
	saveFreeSpaceSection();

	// 调整偏移到扇区起始
	saveDirSection();


	// TODO 检查下面的断言是否正确
	//下面这两个是不需要的，因为所有对它们的修改都是基于缓冲区的
//	saveFileNameSection();
//	saveLinkedInfoSection();

//	printf("flush\n");
//	fseek(this->fpimg,this->reservedLen,SEEK_SET);
//	fwrite(this->namebuf,sizeof(char),this->namebufLen,this->fpimg);
//	fwrite(this->dirbuf,sizeof(char),this->dirbufLen,this->fpimg);
//	fwrite(this->freebuf,sizeof(char),this->freebufLen,this->fpimg);
//	fwrite(this->linkbuf,sizeof(char),this->linkbufLen,this->fpimg);
//	fflush(this->fpimg);

	// TODO 调试下面的代码
	// 回写信息到驱动器,meta区不回写
	size_t off=metainfo->reservedSec+metainfo->metaSec;
	for(size_t i=0;i<X2fsMetaInfo::PARTS_REQUIRED;++i)
	{
#if defined(CODE64)
		env->writeSectors(EnvInterface::CUR_SEG, buffers[i], driver, lbaBaseAddress + off , metainfo->secnums[i], 0);
#else
		env->writeSectors(EnvInterface::CUR_SEG, buffers[i], driver, lbaBaseAddress + off , metainfo->secnums[i], 0);
#endif
		off += metainfo->secnums[i];
	}

	// 恢复偏移到正常位置
	this->retriveDirSection();
}
template <class __EnvInterface>
void X2fsUtil<__EnvInterface>::retriveFileNameSection() {
	u8_t *namebuf = buffers[INDEX_NAME];

	size_t namebufLen = metainfo->secnums[INDEX_NAME]*CONST_SECSIZE;

	u8_t *p=namebuf;


	// 注意：下面的指针相减结果为signed型，需要改变namebufLen类型比较
	u8_t *lastp=NULL;//unset,should point to the first non-zero
	while(*p==0 && p - namebuf < (int)namebufLen)p++;
	if(p - namebuf == (int)namebufLen)//all are zeros,no allocated
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
	while(p-namebuf < (int)namebufLen)
	{
		if(*p==0)
		{
			filenamemm.mnew(lastp - namebuf,(size_t)(p-lastp));
//			printf("filename MM new : %x %x\n",lastp - this->namebuf,(size_t)(p-lastp));
			while(*p==0 && p - namebuf < (int)namebufLen )p++;
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
template <class __EnvInterface>
 void X2fsUtil<__EnvInterface>::retriveFreeSpaceSection() {
	u8_t *freebuf=buffers[INDEX_FREE];
	size_t freebufLen = metainfo->secnums[INDEX_FREE];
	LinearSourceDescriptor *lsbarr=(LinearSourceDescriptor*)freebuf;
	new (&freemm) FreeSpaceMM(&this->listnodesmm,lsbarr[0].getStart(),lsbarr[0].getLimit());
	auto lsdspace=freemm.getSpace();
	if(lsbarr[1].getLimit()!=0 && lsbarr[1].getStart() > lsbarr[0].getStart() &&
			lsbarr[0].getStart()-lsbarr[1].getStart()>=lsbarr[1].getLimit()-lsbarr[0].getLimit())
	{
//		printf("freemm new in 1, newed %x,%x\n",lsbarr[0].getStart(),lsbarr[1].getStart()-lsbarr[0].getStart());
		freemm.mnew(lsbarr[0].getStart(),lsbarr[1].getStart()-lsbarr[0].getStart());
	}
	if(lsbarr[1].getLimit()!=0)
	{
		for(int i=2;i*sizeof(ListNode<LinearSourceDescriptor>) < freebufLen && lsbarr[i].getLimit()>0;i++)
		{
			freemm.mnew(lsbarr[i-1].getStart()+lsbarr[i-1].getLimit(),lsbarr[i].getStart()-lsbarr[i-1].getStart()-lsbarr[i-1].getLimit());
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

template <class __EnvInterface>
void X2fsUtil<__EnvInterface>::saveFreeSpaceSection()
{
	LinearSourceDescriptor* lsdarr=(LinearSourceDescriptor*)buffers[INDEX_FREE];
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


template <class __EnvInterface>
void X2fsUtil<__EnvInterface>::retriveLinkedInfoSection() {
	new (&this->linkmm) LinkedInfoMM(&this->listnodesmm,0,this->linkarrLen);//manage by number

	//====build the free space of the linked section
//	printf("linkarr off is %x(sec nums,relative to dirbase) \n",((size_t)this->linkarr - (size_t)this->dirbuf)/This::SecSize);
//	printf("sizeof(node) = %d,maxi = %d ,linkarr[0].start = %x,linkarr[1].start=%x \n",sizeof(this->linkarr[0]),this->linkarrLen,
//			this->linkarr[0].getStart(),this->linkarr[1].getStart());
	size_t i=0;
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


template <class __EnvInterface>
void X2fsUtil<__EnvInterface>::retriveDirSection() {

//	FileNode *nodebuffer=(FileNode*)this->dirbuf;
	u8_t* dirbuf=buffers[INDEX_DIR];
	size_t dirbufLen=metainfo->secnums[INDEX_DIR]*CONST_SECSIZE;

	this->adjustDirbufOffset((ptrdiff_t)dirbuf);
	new (&dirsmm) FileNodeMM((size_t)dirbuf,dirbufLen,false,3);
	new (&fileTree) FileTree(&dirsmm,(FullNode*)(dirbuf+x2sizeof(FullNode) ));
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
template <class __EnvInterface>
void X2fsUtil<__EnvInterface>::saveDirSection() {
	this->adjustDirbufOffset( (u8_t*)NULL - buffers[INDEX_DIR]);

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
template <class __EnvInterface>
char *X2fsUtil<__EnvInterface>::getFileNameCstr(const FileDescriptor& fd, size_t& nlen)const
{
	if(fd.getNameOffset()==0)return NULL;
	u8_t *namebuf=buffers[INDEX_NAME];
	char *p=(char*)((size_t)namebuf+(size_t)fd.getNameOffset());
	nlen = (size_t)*(unsigned char*)p;
	return p+1;
}

//template <class __EnvInterface>
//std::string X2fsUtil<__EnvInterface>::getFileName(const FileNode *p)const
//{
//	size_t nlen;
//	const FileDescriptor fd=p->getData();
//	char *ch=getFileNameCstr(fd, nlen);
//	return std::move(std::string(ch));
//}

template <class __EnvInterface>
void X2fsUtil<__EnvInterface>::printNode(const FileNode* p)const {
	size_t nlen=0;
	char *pname;
	if(p)
	{
		pname=getFileNameCstr(p->getData(), nlen);
		if(This::isDirectory(p))
		{
			env->printf_simple("Dir:");
			env->printf_sn(pname,nlen);
			env->printf_simple("\n");
//			env->printf_simple("Dir:%.*s\n",nlen,pname);
		}else if(This::isFile(p))
		{
//			printf("File:%.*s %x  %x\n",nlen,pname,p->getData().getSectionStart(),p->getData().getSectionSpan());
			env->printf_simple("File:");
			env->printf_sn(pname,nlen);
			env->printf_simple(" %d  %d\n",p->getData().getSectionList(),p->getData().getFileLen());
		}
	}
}

template <class __EnvInterface>
void X2fsUtil<__EnvInterface>::listOnNode(const FileNode* p,int maxdeepth)const
{
	if(maxdeepth<=0)return;
	this->printNode(p);
	if(p  && This::isDirectory(p))
	{
		FileNode * pfn=p->getSon();
		while(pfn)
		{
			env->printf_simple("\t");
			this->printNode(pfn);
			pfn=pfn->getNext();
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
template <class __EnvInterface>
bool X2fsUtil<__EnvInterface>::hasFilename(FileNode * fnode,const char *name)const
{
	return this->locatePath(fnode, name)!=NULL;
}
/**
 * default
 *
 */
template <class __EnvInterface>
bool X2fsUtil<__EnvInterface>::create(FileNode *p,char type,const char *name,size_t secSpan,int ctime)
{
	if(!p)return false;

	u8_t *namebuf=buffers[INDEX_NAME];
//	size_t namebufLen = metainfo->secnums[INDEX_NAME];

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
		env->printf_simple("dump link mm\n");
		env->printf_simple("space is %d,%d\n",this->linkmm.getSpace().getStart(),this->linkmm.getSpace().getLimit());

		// DEBUG
//		ListNode<LinearSourceDescriptor> *p=this->linkmm.getHead();
//		while(p)
//		{
//			env->printf_simple("(%d,%d)\n",p->getData().getStart(),p->getData().getLimit());
//			p = p->getNext();
//		}

		linkInode=(size_t)this->linkmm.mnew(2);
		if(linkInode==0)
		{
			this->seterrno(This::ERROR_LINKINFO_SPACE_NOT_ENOUGH);
			env->printf_simple("error linkInode\n");
			goto error;
		}
	}else if(type==FileDescriptor::TYPE_DIR){
//		printf("creating dir %s\n",name);
		secSpan=0;
		fsecStart=0;
		linkInode=0;
	}

	namelen=env->strlen(name);
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
	*(unsigned char*)((size_t)namebuf+(size_t)fnamedst)=namelen;
	env->strncpy((char*)((size_t)namebuf+(size_t)fnamedst+1),name,namelen);

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
					linkInode,secSpan,
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
template <class __EnvInterface>
bool X2fsUtil<__EnvInterface>::createFile(FileNode *p,const char *name,size_t secNum)
{
	return this->create(p,FileDescriptor::TYPE_FILE,name,secNum,0);
}
template <class __EnvInterface>
bool X2fsUtil<__EnvInterface>::mkdir(FileNode * fatherDir,const char *dirname)
{
	return this->create(fatherDir,FileDescriptor::TYPE_DIR,dirname,0,0);
}
template <class __EnvInterface>
void X2fsUtil<__EnvInterface>::freeNode(FileNode * node)
{
	if(node && node != this->fileTree.getHead())//You cannot free the root!!!
	{
		u8_t *namebuf=buffers[INDEX_NAME];
		size_t plen;
		char *pname2;
		pname2=this->getFileNameCstr(node->getData(), plen);
		env->printf_simple("in free node : ");
		env->printf_sn(pname2,plen);
		env->printf_simple("\n");
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
		size_t off=node->getData().getNameOffset();
		u8_t *pname=namebuf + off;

//		printf("before memset , len is %d,str is %.*s\n",*pname,*pname,pname + 1);//dirs are not deleted
//		printf("after , len = %d ,str is \"%.*s\"(may not appear)\n",*pname,*pname,pname + 1);
		this->filenamemm.mdelete((char*)off, *pname + 1);
		env->memset((char*)pname,0,*pname + 1);
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
			size_t i=node->getData().getSectionList();
			size_t linkstart=i;
			env->printf_simple("link i is %d\n",i);
			for(;i<this->linkarrLen && this->linkarr[i].getLimit()!=0;i++)
			{
				this->freemm.mdelete((char*)this->linkarr[i].getStart(),this->linkarr[i].getLimit());
				this->linkarr[i]=LinearSourceDescriptor(0,0);//reset as unused
			}
			size_t linklen = i - linkstart + 1;//including the trailing 0.
			//============free space returned(linked sections)
			env->printf_simple("linkmm delete %d,%d\n",linkstart,linklen);
			this->linkmm.mdelete((char*)linkstart, linklen);
		}
		//==============linked info returned

		//here is a question : if one section is shared by many files,should we delete it too ? woo ~ ~
		//we'll use reference count to do that later.
		this->fileTree.free(node);
		//==============file tree withdrawn

	}
}
template <class __EnvInterface>
void X2fsUtil<__EnvInterface>::insertNode(FileNode *dst,FileNode *fnode)
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
template <class __EnvInterface>
void X2fsUtil<__EnvInterface>::removeNode(FileNode * node)
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

template <class __EnvInterface>
bool X2fsUtil<__EnvInterface>::rename(FileNode *node,const char *newname)
{

	u8_t *namebuf=buffers[INDEX_NAME];
//	printf("test getNew \n");
	this->linkmm.getMemoryManager()->getNew();
//	printf("test after getNew\n");
	size_t newlen=env->strlen(newname);
	size_t orilen;
	char *pori;
	pori=this->getFileNameCstr(node->getData(),orilen);
	if(env->strncmp(newname,pori,newlen)==0)
	{
		return true;//the names have been the same
	}
	//alloc new space
	env->printf_simple("before extend\n");
	size_t newoff=(size_t)this->filenamemm.extend(node->getData().getNameOffset(),orilen+1, newlen - orilen, (char*)namebuf,false);
	u8_t *pnew=namebuf + newoff;
	env->printf_simple("after extend\n");
//	printf("orginal off is %x,new off is %x\n",node->getData().getNameOffset(),newoff);
	if(pnew)
	{
		*pnew = newlen;
		env->strncpy((char*)pnew + 1,newname,newlen);
		node->getData().setNameOffset(newoff);
		return true;
	}else{
		return false;
	}
}

template <class __EnvInterface>
bool X2fsUtil<__EnvInterface>::move(FileNode *p,FileNode* dstDir,const char *newname)
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
template <class __EnvInterface>
void X2fsUtil<__EnvInterface>::dumpFileInfo(FileNode * fnode)
{
	const FileDescriptor & fd=fnode->getData();
	size_t nlen;char *p;
	p=this->getFileNameCstr(fd, nlen);
	env->printf_simple("file name : ");
	env->printf_sn(p,nlen);
	env->printf_simple("\n");
	env->printf_simple("linked section list start : %d\nsections are : \n",fd.getSectionList());
	size_t i=fd.getSectionList();
	while(i<this->linkarrLen && this->linkarr[i].getLimit()!=0)
	{
		env->printf_simple("(%x,%x)   ",this->linkarr[i].getStart(),this->linkarr[i].getLimit());
		i++;
	}
	env->printf_simple("\n");
	env->printf_simple("type : %d\n",fd.getType());
	env->printf_simple("length : %d \n",fd.getFileLen());
	env->printf_simple("created time : %d\n",fd.getCreatedTime());
	env->printf_simple("last modified time : %d\n",fd.getLastModefiedTime());
}

/**
 *
 */
template <class __EnvInterface>
bool X2fsUtil<__EnvInterface>::createFileInRoot(const char* name, size_t secNum)
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

template <class __EnvInterface>
bool X2fsUtil<__EnvInterface>::hasFilename(int argc,const char *argv[],const char *name)const
{
	return this->hasFilename(this->getPathNode(argc, argv), name);
}

//template <class __EnvInterface>
//bool X2fsUtil<__EnvInterface>::hasFilename(FileNode *fnode,const std::string& name)const
//{
//	return this->hasFilename(fnode, name.c_str());
//}

template <class __EnvInterface>
bool X2fsUtil<__EnvInterface>::createFile(int argc,const char* argv[],int secSpan)
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
			char *filename=getFileNameCstr(p->getData(), plen);
			/**
			 * 下面先临时性地改变末尾字符为'\0'，打印后改回来
			 */
			env->printf_simple("on node :");
			char prevLast=filename[plen];
			filename[plen]='\0';
			env->printf_simple(filename);
			filename[plen]=prevLast;
			env->printf_simple(" \t");
//			env->printf_simple("on node : %.*s \t",plen,filename);
			env->printf_simple("create file ");
			env->printf_simple(argv[argc-1]);
			env->printf_simple("\n");
			bool flag=this->createFile(p, argv[argc-1], secSpan);

			env->printf_simple("after created, node is : ");
			char *filename2=getFileNameCstr(p->getData(), plen);
			prevLast=filename2[plen];
			filename[plen]='\0';
			env->printf_simple(filename2);
			filename2[plen]=prevLast;
			env->printf_simple(", scceed?%d, errno is %d\n",flag,geterrno());

			return flag;
		}
	}
}

template <class __EnvInterface>
bool X2fsUtil<__EnvInterface>::createDir(int argc,const char* argv[])
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
			env->printf_simple("mkdir ");
			env->printf_simple(argv[argc-1]);
			env->printf_simple("\n");
			return this->mkdir(p, argv[argc-1]);
		}
	}
}
template <class __EnvInterface>
bool X2fsUtil<__EnvInterface>::deleteFile(int argc,const char * argv[])
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
template <class __EnvInterface>
bool X2fsUtil<__EnvInterface>::rename(int argc,const char *argv[],const char *newname)
{
	return this->rename(this->getPathNode(argc, argv), newname);
}
template <class __EnvInterface>
bool X2fsUtil<__EnvInterface>::move(int argcSrc,const char *argvSrc[],int argcDst,const char *argvDst[],const char *newname)
{
	return this->move(this->getPathNode(argcSrc, argvSrc),this->getPathNode(argcDst, argvDst), newname);
}

template <class __EnvInterface>
int X2fsUtil<__EnvInterface>::tellType(int argc,const char* argv[])const
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
template <class __EnvInterface>
void X2fsUtil<__EnvInterface>::dumpFileInfo(int argc,const char *argv[])
{
	this->dumpFileInfo(this->getPathNode(argc, argv));
}
template <class __EnvInterface>
void X2fsUtil<__EnvInterface>::listNode(int argc,const char * argv[],int maxdeepth)const
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
				this->printNode(pson);
			}else{
				this->listOnNode(pson,maxdeepth);
			}
		}else{
			env->printf_simple("No such file or directory\n");
		}
	}

}
template <class __EnvInterface>
void X2fsUtil<__EnvInterface>::listRoot()const
{
	FileNode *pfn=(FileNode *)this->fileTree.getHead();

	env->printf_simple("/:\n");
	pfn=(FileNode *)pfn->getSon();
	size_t nlen=0;
	char *pname;
	char savePrev;
	while(pfn)
	{
		pname=this->getFileNameCstr(pfn->getData(), nlen);
		if(nlen!=0)
		{
//			printf("\t%.*s %x  %x\n",nlen,pname,pfn->getData().getSectionStart(),pfn->getData().getSectionSpan());
			env->printf_simple("\t");
			savePrev=pname[nlen];
			env->printf_simple(pname);
			pname[nlen]=savePrev;
			env->printf_simple(" %d  %d\n",pfn->getData().getSectionList(),pfn->getData().getFileLen());
		}
		pfn=(FileNode *)pfn->getNext();
	}
}

template <class __EnvInterface>
void X2fsUtil<__EnvInterface>::listNode(const FileNode* p)const
{
//	std::cout << "in listNode"<<std::endl;
	FileNode *pfn=(FileNode *)p;

	pfn=(FileNode *)pfn->getSon();
	size_t nlen=0;
	char *pname;
	while(pfn)
	{
		pname=this->getFileNameCstr(pfn->getData(), nlen);
		if(nlen!=0)
		{
//			printf("\t%.*s %x  %x\n",nlen,pname,pfn->getData().getSectionStart(),pfn->getData().getSectionSpan());
			env->printf_simple("\t");
			env->printf_sn(pname, nlen);
			env->printf_simple(" sectionList=%d  fileLen=%d\n",pfn->getData().getSectionList(),pfn->getData().getFileLen());
		}
		pfn=(FileNode *)pfn->getNext();
	}
}


template <class __EnvInterface>
void X2fsUtil<__EnvInterface>::initBuffers() {
//	this->namebuf = (char*)malloc(This::namebufLen);
//	this->dirbuf = (char*)malloc(This::dirbufLen);
//	this->freebuf = (char*)malloc(This::freebufLen);
//	this->linkbuf = (char*)malloc(This::linkbufLen);
//	assert(this->namebuf!=NULL);
//	assert(this->dirbuf!=NULL);
//	assert(this->freebuf!=NULL);
//	assert(this->linkbuf!=NULL);
//	fseek(this->fpimg,this->reservedLen,SEEK_SET);
//	printf("reservedLen = %x , FileNameSection = %x , namebufLen = %x , dirbufLen = %x , freebufLen = %x \n",this->reservedLen,
//			This::FileNameSection,this->namebufLen,this->dirbufLen,this->freebufLen);
//	fread(this->namebuf,sizeof(char),this->namebufLen,this->fpimg);
//	fread(this->dirbuf,sizeof(char),this->dirbufLen,this->fpimg);
//	fread(this->freebuf,sizeof(char),this->freebufLen,this->fpimg);
//	fread(this->linkbuf,sizeof(char),this->linkbufLen,this->fpimg);
}

template <class __EnvInterface>
void X2fsUtil<__EnvInterface>::adjustDirbufOffset(ptrdiff_t off) {
		FileNodeMM::FullNode *nodebuffer=(FileNodeMM::FullNode*)buffers[X2fsMetaInfo::INDEX_DIR];
//		printf("call before adjust\n");
		size_t dirBufLen = metainfo->secnums[X2fsMetaInfo::INDEX_DIR]*CONST_SECSIZE;
		for(size_t i=1;i*x2sizeof(FullNode) <dirBufLen ; i++ )
		{
			if(nodebuffer[i].SimpleMemoryNode::isAlloced()) //已被分配
			{
				nodebuffer[i].setFather(
						(nodebuffer[i].getDirectFather()!=NULL?(FileNode*)((size_t)nodebuffer[i].getDirectFather() + (size_t)off ):(FileNode*)NULL));
				nodebuffer[i].setNext(
						(nodebuffer[i].getNext()!=NULL?(FileNode*)((size_t)nodebuffer[i].getNext() + (size_t)off):(FileNode*)NULL) );
				nodebuffer[i].setPrevious(
						(nodebuffer[i].getPrevious()!=NULL?(FileNode*)((size_t)nodebuffer[i].getPrevious() + (size_t)off):(FileNode*)NULL ) );
				nodebuffer[i].setSon(
						(nodebuffer[i].getSon()!=NULL?(FileNode*)((size_t)nodebuffer[i].getSon() + (size_t)off):(FileNode*)NULL) );
			}
		}
}
//typename
template <class __EnvInterface>
typename X2fsUtil<__EnvInterface>::FileNode * X2fsUtil<__EnvInterface>::locatePath(FileNode* base,int argc, const char* argv[], int& errorLevel)const
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
template <class __EnvInterface>
typename X2fsUtil<__EnvInterface>::FileNode * X2fsUtil<__EnvInterface>::locatePath(FileNode* base, const char* name)const
{
	if(!base)return NULL;
	FileNode *p=(FileNode *)base->getSon();
	size_t len;
	const char *pname;
//	printf("finding name %s\n",name);
	while(p)
	{
		pname = this->getFileNameCstr(p->getData(), len);
//		printf("cmp %.*s,n is %d\n",len,pname,len);
		if(len == env->strlen(name)  && env->strncmp(pname,name,len)==0)
		{
			break;
		}
		p = (FileNode*)p->getNext();
	}
	return p;
}
template <class __EnvInterface>
typename X2fsUtil<__EnvInterface>::FileNode * X2fsUtil<__EnvInterface>::getPathParentNode(int argc,const char * argv[])const
{
	int errlv;
	return this->locatePath(this->getRootBase(),argc-1,argv,errlv);
}
template <class __EnvInterface>
typename X2fsUtil<__EnvInterface>::FileNode * X2fsUtil<__EnvInterface>::getPathNode(int argc,const char * argv[])const
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

template <class __EnvInterface>
size_t  X2fsUtil<__EnvInterface>::writeToFile(const char* buf,size_t objsize, size_t nobj, int argc, const char* argv[],
		size_t foff)
{
	return this->writeToFile(buf, objsize, nobj, this->getPathNode(argc, argv), foff);
}

template <class __EnvInterface>
size_t  X2fsUtil<__EnvInterface>::readFromFile(char* buf,size_t objsize, size_t nobj,int argc, const char* argv[], FileNode* fnode,
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
// DEBUG
// TODO 修改这个函数，主要是注释为TODO的部分
template <class __EnvInterface>
size_t  X2fsUtil<__EnvInterface>::writeToFile(const char* buf,
		size_t objsize, size_t nobj, FileNode* fnode, size_t foff)
{
//	printf("in write to file\n");
//	printf("fnode is %x(relatively)\n",(size_t)fnode - (size_t)this->dirbuf);
	if(fnode || !This::isFile(fnode))
	{
		FileDescriptor &fd=fnode->getData();
//		const size_t myobjsize=1;
		const size_t mynobj = nobj * objsize;
		size_t newlen=foff;

//		printf("before ilink got\n");
		size_t ilink=fd.getSectionList();;
//		printf("section list inode is %d,data[0] is %d,%d\n",ilink,this->linkarr[ilink].getStart(),this->linkarr[ilink].getLimit());

		size_t thisSectionFileLen = this->linkarr[ilink].getLimit() * This::SecSize - foff ;
//		size_t thisSectionStart = this->linkarr[ilink].getStart() * This::SecSize + foff;
		size_t thisObjLeft = mynobj;
		const char *thisBuf=buf;
		while(true)
		{
//			printf("seek at %d,leftSize is %d,this section file len is %d,ilink now is %d\n",thisSectionStart,thisObjLeft,thisSectionFileLen,
//					ilink);
			// TODO
//			fseek(this->fpimg,thisSectionStart,SEEK_SET);

			if(thisSectionFileLen > thisObjLeft)
			{
				thisSectionFileLen = thisObjLeft;
			}

			// TODO
			size_t written =
					0;
//					fwrite(thisBuf,myobjsize,thisSectionFileLen,this->fpimg);

			thisBuf += written;
			thisObjLeft -= written;
			newlen += written;
			ilink++;
			if(thisObjLeft>0)
			{
				if(ilink == this->linkarrLen || this->linkarr[ilink].getLimit()==0)//require for more space
				{
					LinkedList<LinearSourceDescriptor,PartialMallocToSimple> list(this->freemm.getMemoryManager());
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
						size_t newilink=(size_t)this->linkmm.extend(fd.getSectionList(), ilink - fd.getSectionList() + 1,nlist,
								NULL, false);
						if(newilink==0)
						{
							this->seterrno(This::ERROR_LINKINFO_SPACE_NOT_ENOUGH);
							return (mynobj - thisObjLeft)/objsize;
						}
//						printf("new ilink is %d\n",newilink);
						if(newilink != fd.getSectionList())
						{
							env->memcpy((char*)this->linkarr + newilink,(char*)this->linkarr + fd.getSectionList(),ilink - fd.getSectionList() );
							env->memset((char*)this->linkarr + fd.getSectionList(),0,ilink - fd.getSectionList());
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
//				thisSectionStart = this->linkarr[ilink].getStart() * This::SecSize;
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

template <class __EnvInterface>
size_t  X2fsUtil<__EnvInterface>::readFromFile(char* buf, size_t objsize, size_t nobj,FileNode* fnode, size_t foff)
{
//	printf("test getNew at readFromFile \n");
//	this->linkmm.getMemoryManager()->getNew();
//	printf("test after getNew\n");
	if(fnode || !This::isFile(fnode))
	{
		FileDescriptor &fd=fnode->getData();
//		size_t requestLen = nobj * objsize + foff;
//		const size_t myobjsize=1;
		const size_t mynobj = nobj * objsize;
		size_t ilink=fd.getSectionList();

		size_t thisSectionFileLen;
//		size_t thisSectionStart;
		size_t thisObjLeft = mynobj;
		char *thisBuf=buf;
		while(thisObjLeft > 0 && ilink <this->linkarrLen && this->linkarr[ilink].getLimit()!=0)
		{
			thisSectionFileLen = this->linkarr[ilink].getLimit() * This::SecSize ;
//			thisSectionStart = this->linkarr[ilink].getStart() * This::SecSize;

			// TODO 下面这行
//			fseek(this->fpimg,thisSectionStart,SEEK_SET);


			if(thisSectionFileLen > thisObjLeft)
			{
				thisSectionFileLen = thisObjLeft;
			}
			// TODO 下面这块
			size_t written =
					0;
//					fread(thisBuf,myobjsize,thisSectionFileLen,this->fpimg);

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


template <class __EnvInterface>
void  X2fsUtil<__EnvInterface>::mkfs(_EnvInterface *env,u8_t driver,const X2fsMetaInfo *metainfo)
{
	if(!X2fsMetaInfo::checkMetainfo(metainfo))
	{
		env->printf_simple("error metainfo format\n");
		return;
	}

	//debug information
	env->printf_simple("sizeof(FullNode)=%d\n",sizeof(FullNode));


	env->printf_simple("sizeof(TreeNode<FileDescriptor>)=%d\n",sizeof(TreeNode<FileDescriptor>));
	env->printf_simple("sizeof(SimpleMemoryNode)=%d\n",sizeof(SimpleMemoryNode));

	FullNode *p=(FullNode *)sizeof(FullNode);
	TreeNode<FileDescriptor> *p2=(TreeNode<FileDescriptor>*)p;
	SimpleMemoryNode *p3=(SimpleMemoryNode*)p;

	env->printf_simple("difference is (pfullnode - ptreenode)=%d\n",(signed int)((char*)p - (char*)p2));
	env->printf_simple("pfullnode - psimple=%d(should be less than 0)\n",(signed int)((char*)p - (char*)p3));

	u32_t allSecs=metainfo->metaSec;
	for(size_t i=0;i<metainfo->len;i++)
		allSecs+=metainfo->secnums[i];
	u32_t allocedSec=allSecs;
	u8_t *base=env->malloc(allocedSec*CONST_SECSIZE); //分配空间
	allSecs+=metainfo->reservedSec;
	for(size_t i=0;i<metainfo->optionalLen;++i)
		allSecs+=metainfo->optional[i];
	//==================================init name section
	/**
	 * clear filenames in fileNameSection
	 *         but keep the first two,because when returned NULL,it will be treated as failure
	 */
	u32_t filenameSecOff = 0;//base is filename
	u32_t filenameLen = metainfo->secnums[INDEX_NAME] * CONST_SECSIZE;
	env->memset((char*)base+filenameSecOff,0,filenameLen);
	char *pbase=(char*)base+filenameSecOff;
	pbase[0]=1;
	pbase[1]=' ';//根目录的名称是''


	//===================================init dir section
	u32_t dirsectionOff = filenameSecOff + filenameLen;
	u32_t dirsectionLen = metainfo->secnums[INDEX_DIR] * CONST_SECSIZE;
	SimpleMemoryManager<TreeNode<FileDescriptor> > smm((size_t)base+dirsectionOff,dirsectionLen,true);

	/**
	 * set dir root,node[0] node[1] are preserved for use
	 */
	FullNode *proot = (FullNode*)(base+dirsectionOff);//zero is preserved

	proot[0].SimpleMemoryNode::setAlloced(true); //for NULL
	proot[1].SimpleMemoryNode::setAlloced(true); //for Tree Root
	proot[2].SimpleMemoryNode::setAlloced(true); //for Dir Head
	proot[1].setSon((FullNode*)(2*sizeof(FullNode)));//The first one points to the next one,the next one is root

	proot[2].setData(FileDescriptor(
			FileDescriptor::TYPE_DIR,
			0,0,0,
			0,0
	));//root dir
	proot[2].setFather((FullNode*)sizeof(FullNode));//the base is the dir_section,zero is preserved

	//======================================init free space section
	//Now the managed source has changed to sec number,not sec numer multiply with secsize
	u32_t freesectionOff = dirsectionOff + dirsectionLen;
	u32_t freesectionLen = metainfo->secnums[INDEX_FREE] * CONST_SECSIZE;
	u32_t filesectionOff = freesectionOff + freesectionLen;
	u32_t filesectionLen = metainfo->secnums[INDEX_FILE] * CONST_SECSIZE;
	LinearSourceDescriptor *lsdarr=(LinearSourceDescriptor*)((size_t)base+freesectionOff);
	new (lsdarr) LinearSourceDescriptor(allSecs ,
			metainfo->wholeSecnums - allSecs);//from start to the end
	new (lsdarr+1) LinearSourceDescriptor(0,0);//This allows it returns NULL,because it is at least a FreeSpaceSectionLen

	//======================================init linked info section
	u32_t linksectionOff = filesectionOff + filesectionLen;
	u32_t linksectionLen = metainfo->secnums[INDEX_LINK] * CONST_SECSIZE;
	LinearSourceDescriptor *lkinfarr=(LinearSourceDescriptor*)((size_t)base+linksectionOff);
	env->memset((char*)lkinfarr,0,linksectionLen);//set all to 0
	new (lkinfarr) LinearSourceDescriptor(0xaa55,1);//0xaa55 is the verifying information,文件第一个扇区不用，所有的都是第一项不用
	new (lkinfarr + 1) LinearSourceDescriptor(0xaa55,0);


	//============================flush to storage
	env->writeSectors(EnvInterface::CUR_SEG, (u8_t*)metainfo,0x80,metainfo->lbaStartLow+metainfo->reservedSec,metainfo->metaSec,metainfo->lbaStartHigh);
	env->writeSectors(EnvInterface::CUR_SEG, base,0x80,metainfo->lbaStartLow+metainfo->reservedSec+metainfo->metaSec, allocedSec, metainfo->lbaStartHigh);

	env->flushOutputs();
	env->free(base);
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

#endif

