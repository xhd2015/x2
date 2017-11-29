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
//extern template class TreeNode<FileDescriptor<__SizeType>>;
//extern template class SimpleMemoryManager<TreeNode<FileDescriptor<__SizeType>> >;

#if defined(CODE64)
	template class X2fsUtil<EnvInterface64Impl,size_t>;
	template class X2fsMetaInfo<size_t>;
#endif
template <typename __SizeType>
bool X2fsMetaInfo<__SizeType>::checkMetainfo(const X2fsMetaInfo* info)
{
	bool checkRes = (info->reservedSec == SECNUM_RESERVED_CONST) &&
					(info->metaSec == SECNUM_META_CONST ) &&
					(info->len == PARTS_REQUIRED) &&
					(info->validFlag == VALID_FLAG);

	return checkRes;
}

#if defined(CODE64)
template <typename __SizeType>
void  X2fsMetaInfo<__SizeType>::dumpInfo(EnvInterface64Impl *env)
{
	//每次最多打印3个，这是printf_simple的实现限制
	env->printf_simple("X2fsMetaInfo{"
			"basic_sizetype:%d, "
			"reserved:%d, "
			"metainfo:%d, "
			,(u32_t)basicSizeType,reservedSec,metaSec);

	env->printf_simple(
			"sec_filename:%d, "
			"sec_dir:%d, "
			"sec_freespace:%d, "
			,secnums[INDEX_NAME],secnums[INDEX_DIR],secnums[INDEX_FREE]);
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

//typedef SimpleMemoryManager<TreeNode<FileDescriptor<__SizeType><>> >::FullNode FullNode;

// DEBUG
template <class __EnvInterface,typename __SizeType>
X2fsUtil<__EnvInterface,__SizeType>::X2fsUtil(_EnvInterface *env,u8_t driver,u32_t lbaBase):
			env(env),driver(driver),
			mmnodesmm(env),
			listnodesmm(env),
			processErrno(This::ERROR_NOERR)
	{

		env->printf_simple("reading meta info...\n");
		// 先读取元信息区域
		metabuf=env->malloc(CONST_SECSIZE);

		env->readSectors(EnvInterface::CUR_SEG, metabuf, driver,
				lbaBase + X2fsMetaInfo<__SizeType>::SECNUM_RESERVED_CONST,X2fsMetaInfo<__SizeType>::SECNUM_META_CONST,  0);

		if(metainfo==NULL || !X2fsMetaInfo<__SizeType>::checkMetainfo(metainfo))
			env->systemAbort("cannot valid metainfo sector", -2);

		__SizeType wholeSecs=0;
		for(__SizeType i=0;i<metainfo->len ;i++)
		{
			wholeSecs+=metainfo->secnums[i];
		}

		// 分配空间
		buffers[0]= env->malloc(wholeSecs * CONST_SECSIZE);


		// NOTICE 如果你改变了X2fsMetaInfo的设计，必须保证所有的可选分区在必选分区之后
		// 此处仅读入必选分区
		env->readSectors(EnvInterface::CUR_SEG, buffers[0], driver,
				lbaBase + X2fsMetaInfo<__SizeType>::SECNUM_RESERVED_CONST+X2fsMetaInfo<__SizeType>::SECNUM_META_CONST,wholeSecs,0);

		// 依次分配每个分区的buffer地址
		for(__SizeType i=1;i<metainfo->len ; i++)
		{
			buffers[i]=buffers[i-1]+metainfo->secnums[i-1]*CONST_SECSIZE;
		}
		linkarr = (LinearSourceDescriptor<__SizeType>*)buffers[X2fsMetaInfo<__SizeType>::INDEX_LINK];
		linkarrLen = metainfo->secnums[X2fsMetaInfo<__SizeType>::INDEX_LINK]*CONST_SECSIZE/x2sizeof(linkarr[0]);


		new (&filenamemm) FileNameMM(&mmnodesmm,0,metainfo->secnums[INDEX_NAME]*CONST_SECSIZE,false);

		initWithBuffersAlloced();

	}
template <class __EnvInterface,typename __SizeType>
X2fsUtil<__EnvInterface,__SizeType>::X2fsUtil(_EnvInterface *env,u8_t driver,X2fsMetaInfo<__SizeType> *metainfo,u8_t *buffers[]):
				env(env),driver(driver),
				metainfo(metainfo),
				mmnodesmm(env),
				filenamemm(&mmnodesmm,0,metainfo->secnums[INDEX_NAME]*CONST_SECSIZE,false),
				listnodesmm(env),
				processErrno(This::ERROR_NOERR)

		{
			if(metainfo==NULL || !X2fsMetaInfo<__SizeType>::checkMetainfo(metainfo))
				env->systemAbort("cannot valid metainfo sector", -2);
			for(__SizeType i=0;i<metainfo->len;++i)
				this->buffers[i]=buffers[i];
			linkarr =(LinearSourceDescriptor<__SizeType>*) buffers[X2fsMetaInfo<__SizeType>::INDEX_LINK];
			linkarrLen = metainfo->secnums[X2fsMetaInfo<__SizeType>::INDEX_LINK]*CONST_SECSIZE/x2sizeof(linkarr[0]);

			initWithBuffersAlloced();
		}
template <class __EnvInterface,typename __SizeType>
void X2fsUtil<__EnvInterface,__SizeType>::initWithBuffersAlloced()
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

template <class __EnvInterface,typename __SizeType>
X2fsUtil<__EnvInterface,__SizeType>::~X2fsUtil()
{

//	if(this->fpimg)
//	{
//		printf("destruct \n");
		this->flush();  //自行调用flush
//		fclose(fpimg);
//		fpimg=NULL;
//	}
}


template <class __EnvInterface,typename __SizeType>
void X2fsUtil<__EnvInterface,__SizeType>::flush() {
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
	__SizeType off=metainfo->reservedSec+metainfo->metaSec;
	for(__SizeType i=0;i<X2fsMetaInfo<__SizeType>::PARTS_REQUIRED;++i)
	{
#if defined(CODE64)
		env->writeSectors(EnvInterface::CUR_SEG, buffers[i], driver, metainfo->lbaStartLow + off , metainfo->secnums[i], metainfo->lbaStartHigh);
#else
		env->writeSectors(EnvInterface::CUR_SEG, buffers[i], driver, metainfo->lbaStartLow + off , metainfo->secnums[i], metainfo->lbaStartHigh);
#endif
		off += metainfo->secnums[i];
	}

	// 恢复偏移到正常位置
	this->retriveDirSection();
}
template <class __EnvInterface,typename __SizeType>
void X2fsUtil<__EnvInterface,__SizeType>::retriveFileNameSection() {
	u8_t *namebuf = buffers[INDEX_NAME];

	__SizeType namebufLen = metainfo->secnums[INDEX_NAME]*CONST_SECSIZE;

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
//			printf("%x ",(__SizeType)*(this->namebuf+i));
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
			filenamemm.mnew(lastp - namebuf,(__SizeType)(p-lastp));
//			printf("filename MM new : %x %x\n",lastp - this->namebuf,(__SizeType)(p-lastp));
			while(*p==0 && p - namebuf < (int)namebufLen )p++;
			lastp = p;
		}else{
			p+=*p+1;
		}
//		printf("lastp = %x\n",(__SizeType)(lastp-this->namebuf));
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
template <class __EnvInterface,typename __SizeType>
 void X2fsUtil<__EnvInterface,__SizeType>::retriveFreeSpaceSection() {
	u8_t *freebuf=buffers[INDEX_FREE];
	__SizeType freebufLen = metainfo->secnums[INDEX_FREE];
	LinearSourceDescriptor<__SizeType> *lsbarr=(LinearSourceDescriptor<__SizeType>*)freebuf;
	new (&freemm) FreeSpaceMM(&listnodesmm,lsbarr[0].getStart(),lsbarr[0].getLimit());
	auto lsdspace=freemm.getSpace();

	// 如果下标1的长度不为0，且下标1的开始大于下标0的开始，下标1的结束大于下标0的结束
	// 则预先分配一段从开始到下标1的开始的空间，这段空间被标记为占用状态
	if(lsbarr[1].getLimit()!=0 && lsbarr[1].getStart() > lsbarr[0].getStart() &&
			lsbarr[0].getStart()-lsbarr[1].getStart()>=lsbarr[1].getLimit()-lsbarr[0].getLimit())
	{
//		printf("freemm new in 1, newed %x,%x\n",lsbarr[0].getStart(),lsbarr[1].getStart()-lsbarr[0].getStart());
		freemm.mnew(lsbarr[0].getStart(),lsbarr[1].getStart()-lsbarr[0].getStart());
	}


	if(lsbarr[1].getLimit()!=0)
	{
		for(int i=2;i*sizeof(ListNode<LinearSourceDescriptor<__SizeType>>) < freebufLen && lsbarr[i].getLimit()>0;i++)
		{
			freemm.mnew(lsbarr[i-1].getStart()+lsbarr[i-1].getLimit(),
					lsbarr[i].getStart()-lsbarr[i-1].getStart()-lsbarr[i-1].getLimit());
		}
	}
//	this->freemm.mnew(0x3700,40);
//	printf("dump FreeSpace(LinearSourceManager)\n");
//	printf("space is (%x,%x)\n",(__SizeType)this->freemm.getSpace().getStart(),(__SizeType)this->freemm.getSpace().getLimit());
//	ListNode<LinearSourceDescriptor> *plnode=this->freemm.getHead();
//	while(plnode)
//	{
//		printf("%x %x\n",(__SizeType)plnode->getData().getStart(),plnode->getData().getLimit());
//		plnode=plnode->getNext();
//	}
}

template <class __EnvInterface,typename __SizeType>
void X2fsUtil<__EnvInterface,__SizeType>::saveFreeSpaceSection()
{
	LinearSourceDescriptor<__SizeType>* lsdarr=(LinearSourceDescriptor<__SizeType>*)buffers[INDEX_FREE];
	lsdarr[0]=this->freemm.getSpace();
	ListNode<LinearSourceDescriptor<__SizeType>> *pfreenode=this->freemm.getHead();
//	printf("head of freemm is %x\n",(int)(__SizeType)pfreenode);
	int i=1;
	while(pfreenode)
	{
		lsdarr[i++]=pfreenode->getData();
//		printf("this node is %x,save free space %x,%x\n",pfreenode,(int)pfreenode->getData().getStart(),(int)pfreenode->getData().getLimit());
		pfreenode=pfreenode->getNext();
	}
	new (&lsdarr[i]) LinearSourceDescriptor<__SizeType>(0,0);
}


template <class __EnvInterface,typename __SizeType>
void X2fsUtil<__EnvInterface,__SizeType>::retriveLinkedInfoSection() {
	// 管理0~160错误，第一个不需要管理
	new (&linkmm) LinkedInfoMM(&listnodesmm,2,linkarrLen);//manage by number

	//====build the free space of the linked section
//	printf("linkarr off is %x(sec nums,relative to dirbase) \n",((__SizeType)this->linkarr - (__SizeType)this->dirbuf)/This::SecSize);
//	printf("sizeof(node) = %d,maxi = %d ,linkarr[0].start = %x,linkarr[1].start=%x \n",sizeof(this->linkarr[0]),this->linkarrLen,
//			this->linkarr[0].getStart(),this->linkarr[1].getStart());

	// i定位到第一个有效的节点，有效节点长度不为0
	__SizeType i=2;
	while(i < linkarrLen && linkarr[i].getLimit()==0)i++;

	__SizeType lastNonZero=i;
	i+=1;
//	printf("i = %d,lastNonZero = %d \n",i,lastNonZero);

	// 下面的循环每次分配[lastNonZero,len)长度的区间,也就是对linkarr进行初始化，(0,0)的节点被跳过，标记为未用状态
	while(i < linkarrLen )
	{
		if( linkarr[i].getLimit()==0)
		{
//			printf("in linkmm new %x,%x\n",lastNonZero,i - lastNonZero+1);
			__SizeType checkPointerValid=(__SizeType)linkmm.mnew(lastNonZero,i - lastNonZero + 1);//one more for the trailing 0
			if(!checkPointerValid)
			{
				env->systemAbort("Cannot allocate space for linkmm,so the filesystem cannot be initialized.", -2);
			}
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


template <class __EnvInterface,typename __SizeType>
void X2fsUtil<__EnvInterface,__SizeType>::retriveDirSection() {

//	FileNode *nodebuffer=(FileNode*)this->dirbuf;
	u8_t* dirbuf=buffers[INDEX_DIR];
	__SizeType dirbufLen=metainfo->secnums[INDEX_DIR]*CONST_SECSIZE;

	this->adjustDirbufOffset((ptrdiff_t)dirbuf);
	new (&dirsmm) FileNodeMM((__SizeType)dirbuf,dirbufLen,false,3);
	new (&fileTree) FileTree(&dirsmm,(FullNode*)(dirbuf+x2sizeof(FullNode) ));
//	printf("after init call get direct\n");
//	nodebuffer[2].getDirectFather();
//	nodebuffer[2].getDirectFather();
//	printf("nodebffer[2]==%x,head=%x\n",nodebuffer+2,this->fileTree.getHead());
//	FileNode * head= (FileNode*)this->fileTree.getHead();
//	new ((SimpleMemoryNode*)head) SimpleMemoryNode;
//	new ((TreeNode<FileDescriptor<__SizeType>>*)head) TreeNode<FileDescriptor<__SizeType>>(FileDescriptor<__SizeType>(0,0,0,0,0,0,0,0));
//	printf("this head = %x \n",head);
//	printf("call this->getDirectFather()\n");
//
//	head->getDirectFather();
//	for(int i=FileNodeSize*1;i!=FileNodeSize*3;i++)
//	{
//		printf("%x ",*(dirbuf+i));
//	}
//	printf("\n");
//	printf("dirbuf + 2*sizeof(filenode) = %x,head = %x\n",(__SizeType)this->dirbuf+FileNodeSize*2,this->fileTree.getHead());
//	printf("dumpFileTree , head & root is %x ,%x\n",(__SizeType)this->fileTree.getHead() - (__SizeType)this->dirbuf,
//			(__SizeType)this->fileTree.getHead()->getDirectFather() - (__SizeType)this->dirbuf);
}
template <class __EnvInterface,typename __SizeType>
void X2fsUtil<__EnvInterface,__SizeType>::saveDirSection() {
	this->adjustDirbufOffset( (u8_t*)NULL - buffers[INDEX_DIR]);

//	printf("after adjusted back , save\n");
//	FileNode *nodebuffer=(FileNode*)this->dirbuf;
//	char *p;
//	__SizeType plen;
//	p=this->getFileName(nodebuffer[3].getData(), plen);
//	printf("dump Node[1].next = %x , Node[2].father= %x Node[3].filename=%.*s\n",nodebuffer[1].getSon(),
//			nodebuffer[2].getDirectFather(),
//			plen,
//			p);
}
template <class __EnvInterface,typename __SizeType>
char *X2fsUtil<__EnvInterface,__SizeType>::getFileNameCstr(const FileDescriptor<__SizeType>& fd, __SizeType& nlen)const
{
	if(fd.getNameOffset()==0)return NULL;
	u8_t *namebuf=buffers[INDEX_NAME];
	char *p=(char*)((__SizeType)namebuf+(__SizeType)fd.getNameOffset());
	nlen = (__SizeType)*(unsigned char*)p;
	return p+1;
}

//template <class __EnvInterface,typename __SizeType>
//std::string X2fsUtil<__EnvInterface,__SizeType>::getFileName(const FileNode *p)const
//{
//	__SizeType nlen;
//	const FileDescriptor<__SizeType> fd=p->getData();
//	char *ch=getFileNameCstr(fd, nlen);
//	return std::move(std::string(ch));
//}

template <class __EnvInterface,typename __SizeType>
void X2fsUtil<__EnvInterface,__SizeType>::printNode(const FileNode* p)const {
	__SizeType nlen=0;
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
			env->printf_simple(" %d  %d\n",p->getData().getSectionListIndex(),p->getData().getFileLen());
		}
	}
}

template <class __EnvInterface,typename __SizeType>
void X2fsUtil<__EnvInterface,__SizeType>::listOnNode(const FileNode* p,int maxdeepth)const
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
template <class __EnvInterface,typename __SizeType>
bool X2fsUtil<__EnvInterface,__SizeType>::hasFilename(FileNode * fnode,const char *name)const
{
	return this->locatePath(fnode, name)!=NULL;
}
/**
 * default
 *
 */
template <class __EnvInterface,typename __SizeType>
bool X2fsUtil<__EnvInterface,__SizeType>::create(FileNode *p,u8_t type,const char *name,__SizeType secSpan,__TimeType ctime)
{
	if(!p)return false;

	u8_t *namebuf=buffers[INDEX_NAME];
//	__SizeType namebufLen = metainfo->secnums[INDEX_NAME];

	if(this->locatePath(p, name)!=NULL)//check existence of name
	{
		this->seterrno(This::ERROR_FILE_ALREDY_EXIST);
		return false;
	}
	__SizeType fsecStart=0;
	__SizeType linkInode=0;
	__SizeType namelen;
	char *fnamedst;
//	__SizeType plen;
//	printf("during created[1], node is : %.*s \n",plen,this->getFileName(p->getData(), plen));

	FileNode *fnode=(FileNode*)this->dirsmm.getNew();//request for new FileNode
//	printf("fnode is %x(relative to dirbase) \n",(__SizeType)fnode-(__SizeType)this->dirbuf);
	if(fnode==NULL){
		this->seterrno(This::ERROR_DIRTREESPACE);
		goto error;
	}
	if(type==FileDescriptor<__SizeType>::TYPE_FILE)
	{
		if(secSpan<2)// ADDDOC 文件类型至少分配2个扇区
		{
			secSpan=2;
		}
		fsecStart=(__SizeType)freemm.mnew(secSpan);//request for new space
	//	printf("fsecStart is %x\n",(int)fsecStart);
		if(fsecStart==0)//no enough space
		{
			this->seterrno(This::ERROR_FILEALLOCSPACE);
			goto error;
		}
		env->printf_simple("dump link mm\n");
		env->printf_simple("space is %d,%d\n",this->linkmm.getSpace().getStart(),this->linkmm.getSpace().getLimit());

		// DEBUGINFO
//		ListNode<LinearSourceDescriptor> *p=this->linkmm.getHead();
//		while(p)
//		{
//			env->printf_simple("(%d,%d)\n",p->getData().getStart(),p->getData().getLimit());
//			p = p->getNext();
//		}

		linkInode=(__SizeType)linkmm.mnew(2);
		if(linkInode==0)
		{
			this->seterrno(This::ERROR_LINKINFO_SPACE_NOT_ENOUGH);
			env->printf_simple("error linkInode\n");
			goto error;
		}
	}else if(type==FileDescriptor<__SizeType>::TYPE_DIR){
//		printf("creating dir %s\n",name);
		secSpan=0;
		fsecStart=0;
		linkInode=0;
	}

	namelen=env->strlen(name);
	fnamedst=(char*)this->filenamemm.mnew(namelen+1); //request for name space,the first byte is for length
//	printf("fdst is %x \n",(__SizeType)fdst);
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
	*(unsigned char*)((__SizeType)namebuf+(__SizeType)fnamedst)=namelen;
	env->strncpy((char*)((__SizeType)namebuf+(__SizeType)fnamedst+1),name,namelen);

	//===================Set section link info
	if(linkInode!=0)
	{
		this->linkarr[linkInode] = LinearSourceDescriptor<__SizeType>(fsecStart,secSpan);
		this->linkarr[linkInode + 1] = LinearSourceDescriptor<__SizeType>(0,0);
	}
//	printf("during created[3], node is : %.*s \n",plen,this->getFileName(p->getData(), plen));
	//==================Set file node
	new ((TreeNode<FileDescriptor<__SizeType>>*)fnode) TreeNode<FileDescriptor<__SizeType>>(FileDescriptor<__SizeType>(
					type,
					linkInode,secSpan*CONST_SECSIZE,
					(__SizeType)fnamedst,
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
template <class __EnvInterface,typename __SizeType>
bool X2fsUtil<__EnvInterface,__SizeType>::createFile(FileNode *p,const char *name,__SizeType secNum)
{
	return this->create(p,FileDescriptor<__SizeType>::TYPE_FILE,name,secNum,0);
}
template <class __EnvInterface,typename __SizeType>
bool X2fsUtil<__EnvInterface,__SizeType>::mkdir(FileNode * fatherDir,const char *dirname)
{
	return this->create(fatherDir,FileDescriptor<__SizeType>::TYPE_DIR,dirname,0,0);
}
template <class __EnvInterface,typename __SizeType>
void X2fsUtil<__EnvInterface,__SizeType>::freeNode(FileNode * node)
{
	if(node && node != this->fileTree.getHead())//You cannot free the root!!!
	{
		u8_t *namebuf=buffers[INDEX_NAME];
		__SizeType plen;
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
		__SizeType off=node->getData().getNameOffset();
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
			__SizeType i=node->getData().getSectionListIndex();
			__SizeType linkstart=i;
			env->printf_simple("link i is %d\n",i);
			for(;i<this->linkarrLen && this->linkarr[i].getLimit()!=0;i++)
			{
				this->freemm.mdelete((char*)this->linkarr[i].getStart(),this->linkarr[i].getLimit());
				this->linkarr[i]=LinearSourceDescriptor<__SizeType>(0,0);//reset as unused
			}
			__SizeType linklen = i - linkstart + 1;//including the trailing 0.
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
template <class __EnvInterface,typename __SizeType>
void X2fsUtil<__EnvInterface,__SizeType>::insertNode(FileNode *dst,FileNode *fnode)
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
template <class __EnvInterface,typename __SizeType>
void X2fsUtil<__EnvInterface,__SizeType>::removeNode(FileNode * node)
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

template <class __EnvInterface,typename __SizeType>
bool X2fsUtil<__EnvInterface,__SizeType>::rename(FileNode *node,const char *newname)
{

	u8_t *namebuf=buffers[INDEX_NAME];
//	printf("test getNew \n");
	this->linkmm.getMemoryManager()->getNew();
//	printf("test after getNew\n");
	__SizeType newlen=env->strlen(newname);
	__SizeType orilen;
	char *pori;
	pori=this->getFileNameCstr(node->getData(),orilen);
	if(env->strncmp(newname,pori,newlen)==0)
	{
		return true;//the names have been the same
	}
	//alloc new space
	env->printf_simple("before extend\n");
	__SizeType newoff=(__SizeType)this->filenamemm.extend(node->getData().getNameOffset(),orilen+1, newlen - orilen, (char*)namebuf,false);
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

template <class __EnvInterface,typename __SizeType>
bool X2fsUtil<__EnvInterface,__SizeType>::move(FileNode *p,FileNode* dstDir,const char *newname)
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
template <class __EnvInterface,typename __SizeType>
void X2fsUtil<__EnvInterface,__SizeType>::dumpFileInfo(FileNode * fnode)
{
	const FileDescriptor<__SizeType> & fd=fnode->getData();
	__SizeType nlen;char *p;
	p=this->getFileNameCstr(fd, nlen);
	env->printf_simple("file name : ");
	env->printf_sn(p,nlen);
	env->printf_simple("\n");
	env->printf_simple("linked section list start : %d\nsections are : \n",fd.getSectionListIndex());
	__SizeType i=fd.getSectionListIndex();
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
template <class __EnvInterface,typename __SizeType>
bool X2fsUtil<__EnvInterface,__SizeType>::createFileInRoot(const char* name, __SizeType secNum)
{
	return this->createFile((FileNode*)this->fileTree.getHead(), name, secNum);
//	__SizeType namelen=strlen(name);
//	char *fdst=(char*)this->filenamemm.mnew(namelen);
////	printf("new fdst is %x \n",fdst);
//	*(unsigned char*)((__SizeType)this->namebuf+(__SizeType)fdst)=namelen;
////	printf("namelen is %d,namebuf is %x \n",namelen,this->namebuf);
//	strncpy((char*)((__SizeType)this->namebuf+(__SizeType)fdst+1),name,namelen);
////	printf("\t\twritten is %.*s\n",namelen,(__SizeType)this->namebuf+(__SizeType)fdst+1);
//	__SizeType fsecStart=(__SizeType)this->freemm.mnew(secNum*X2fsUtil::SecSize);
////	printf("new fsecStart is %x\n",fsecStart);
//
//
////	printf("dump SMM: start=%x(relative to dirbuf),limit=%x,curSize=%d,\n",(__SizeType)dirsmm.getStart() - (__SizeType)dirbuf,dirsmm.getLimit(),dirsmm.getCurSize());
//	FileNode *fnode=(FileNode*)this->dirsmm.getNew();
//
////	printf("new fnode is %x(relative to dirbuf)\n",(__SizeType)fnode - (__SizeType)this->dirbuf);
//	fnode->setData(
//			FileDescriptor<__SizeType>(
//					FileDescriptor<__SizeType>::TYPE_FILE,
//					fsecStart,secNum,fsecStart,0,
//					(__SizeType)fdst,
//					0,0
//			)
//	);
////	printf("dump fileTree , head & root : %x  %x\n",(__SizeType)this->fileTree.getHead() - (__SizeType)this->dirbuf
////			,(__SizeType)this->fileTree.getHead()->getDirectFather() - (__SizeType)this->dirbuf);
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
////	__SizeType plen;
////	char *p=this->getFileName(fnode->getData(),plen);
////	printf("file name offset is %x,content is %.*s\n",fnode->getData().getNameOffset(),plen,p);
//
//	return true;
}

template <class __EnvInterface,typename __SizeType>
bool X2fsUtil<__EnvInterface,__SizeType>::hasFilename(int argc,const char *argv[],const char *name)const
{
	return this->hasFilename(this->getPathNode(argc, argv), name);
}

//template <class __EnvInterface,typename __SizeType>
//bool X2fsUtil<__EnvInterface,__SizeType>::hasFilename(FileNode *fnode,const std::string& name)const
//{
//	return this->hasFilename(fnode, name.c_str());
//}

template <class __EnvInterface,typename __SizeType>
bool X2fsUtil<__EnvInterface,__SizeType>::createFile(int argc,const char* argv[],int secSpan)
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
			__SizeType plen;
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

template <class __EnvInterface,typename __SizeType>
bool X2fsUtil<__EnvInterface,__SizeType>::createDir(int argc,const char* argv[])
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
template <class __EnvInterface,typename __SizeType>
bool X2fsUtil<__EnvInterface,__SizeType>::deleteFile(int argc,const char * argv[])
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
template <class __EnvInterface,typename __SizeType>
bool X2fsUtil<__EnvInterface,__SizeType>::rename(int argc,const char *argv[],const char *newname)
{
	return this->rename(this->getPathNode(argc, argv), newname);
}
template <class __EnvInterface,typename __SizeType>
bool X2fsUtil<__EnvInterface,__SizeType>::move(int argcSrc,const char *argvSrc[],int argcDst,const char *argvDst[],const char *newname)
{
	return this->move(this->getPathNode(argcSrc, argvSrc),this->getPathNode(argcDst, argvDst), newname);
}

template <class __EnvInterface,typename __SizeType>
int X2fsUtil<__EnvInterface,__SizeType>::tellType(int argc,const char* argv[])const
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
template <class __EnvInterface,typename __SizeType>
void X2fsUtil<__EnvInterface,__SizeType>::dumpFileInfo(int argc,const char *argv[])
{
	this->dumpFileInfo(this->getPathNode(argc, argv));
}
template <class __EnvInterface,typename __SizeType>
void X2fsUtil<__EnvInterface,__SizeType>::listNode(int argc,const char * argv[],int maxdeepth)const
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
template <class __EnvInterface,typename __SizeType>
void X2fsUtil<__EnvInterface,__SizeType>::listRoot()const
{
	FileNode *pfn=(FileNode *)this->fileTree.getHead();

	env->printf_simple("/:\n");
	pfn=(FileNode *)pfn->getSon();
	__SizeType nlen=0;
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
			env->printf_simple(" %d  %d\n",pfn->getData().getSectionListIndex(),pfn->getData().getFileLen());
		}
		pfn=(FileNode *)pfn->getNext();
	}
}

template <class __EnvInterface,typename __SizeType>
void X2fsUtil<__EnvInterface,__SizeType>::listNode(const FileNode* p)const
{
//	std::cout << "in listNode"<<std::endl;
	FileNode *pfn=(FileNode *)p;

	pfn=(FileNode *)pfn->getSon();
	__SizeType nlen=0;
	char *pname;
	while(pfn)
	{
		pname=this->getFileNameCstr(pfn->getData(), nlen);
		if(nlen!=0)
		{
//			printf("\t%.*s %x  %x\n",nlen,pname,pfn->getData().getSectionStart(),pfn->getData().getSectionSpan());
			env->printf_simple("\t");
			env->printf_sn(pname, nlen);
			env->printf_simple(" sectionList=%d  fileLen=%d\n",pfn->getData().getSectionListIndex(),pfn->getData().getFileLen());
		}
		pfn=(FileNode *)pfn->getNext();
	}
}

template <class __EnvInterface,typename __SizeType>
__SizeType X2fsUtil<__EnvInterface,__SizeType>::calculateRandomBufferSize(
		__SizeType startByte,__SizeType numbyte,
		__SizeType *startDiff,
		__SizeType *endDiff,
		__SizeType unit)
{
	if(unit==0|| numbyte==0)return 0;
	__SizeType modSize = startByte % unit;
	__SizeType adjustNumByte = numbyte  + modSize;
	__SizeType adjustNumModSize = adjustNumByte % unit;

	if(startDiff)
		*startDiff=modSize;

	if(adjustNumModSize!=0)//需要向后增加补齐
		{
			adjustNumModSize = unit - adjustNumModSize;
			adjustNumByte += adjustNumModSize;
		}
	if(endDiff)
		*endDiff=adjustNumModSize;
	return adjustNumByte;
}
template <class __EnvInterface,typename __SizeType>
void X2fsUtil<__EnvInterface,__SizeType>::initBuffers() {
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

template <class __EnvInterface,typename __SizeType>
void X2fsUtil<__EnvInterface,__SizeType>::adjustDirbufOffset(ptrdiff_t off) {
		FullNode *nodebuffer=(FullNode*)buffers[X2fsMetaInfo<__SizeType>::INDEX_DIR];
//		printf("call before adjust\n");

		__SizeType dirBufLen = metainfo->secnums[X2fsMetaInfo<__SizeType>::INDEX_DIR]*CONST_SECSIZE;
		for(__SizeType i=1;i*x2sizeof(FullNode) <dirBufLen ; i++ )
		{
			if(nodebuffer[i].SimpleMemoryNode::isAlloced()) //已被分配
			{
				nodebuffer[i].setFather(
						(nodebuffer[i].getDirectFather()!=NULL?(FileNode*)((__SizeType)nodebuffer[i].getDirectFather() + (__SizeType)off ):(FileNode*)NULL));
				nodebuffer[i].setNext(
						(nodebuffer[i].getNext()!=NULL?(FileNode*)((__SizeType)nodebuffer[i].getNext() + (__SizeType)off):(FileNode*)NULL) );
				nodebuffer[i].setPrevious(
						(nodebuffer[i].getPrevious()!=NULL?(FileNode*)((__SizeType)nodebuffer[i].getPrevious() + (__SizeType)off):(FileNode*)NULL ) );
				nodebuffer[i].setSon(
						(nodebuffer[i].getSon()!=NULL?(FileNode*)((__SizeType)nodebuffer[i].getSon() + (__SizeType)off):(FileNode*)NULL) );
			}
		}
}
//typename
template <class __EnvInterface,typename __SizeType>
typename X2fsUtil<__EnvInterface,__SizeType>::FileNode * X2fsUtil<__EnvInterface,__SizeType>::locatePath(FileNode* base,int argc, const char* argv[], int& errorLevel)const
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
template <class __EnvInterface,typename __SizeType>
typename X2fsUtil<__EnvInterface,__SizeType>::FileNode * X2fsUtil<__EnvInterface,__SizeType>::locatePath(FileNode* base, const char* name)const
{
	if(!base)return NULL;
	FileNode *p=(FileNode *)base->getSon();
	__SizeType len;
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
template <class __EnvInterface,typename __SizeType>
typename X2fsUtil<__EnvInterface,__SizeType>::FileNode * X2fsUtil<__EnvInterface,__SizeType>::getPathParentNode(int argc,const char * argv[])const
{
	int errlv;
	return this->locatePath(this->getRootBase(),argc-1,argv,errlv);
}
template <class __EnvInterface,typename __SizeType>
typename X2fsUtil<__EnvInterface,__SizeType>::FileNode * X2fsUtil<__EnvInterface,__SizeType>::getPathNode(int argc,const char * argv[])const
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
//	printf("in getPathNode %s,returned is %x\n",argv[argc-1],(__SizeType)pson-(__SizeType)this->dirbuf);
	return pson;


}

template <class __EnvInterface,typename __SizeType>
__SizeType  X2fsUtil<__EnvInterface,__SizeType>::writeToFile(const char* buf,__SizeType objsize, __SizeType nobj, int argc, const char* argv[],
		__SizeType foff)
{
	// DEPRECATED
//	return this->writeToFile(buf, objsize, nobj, this->getPathNode(argc, argv), foff);
	return 0;
}
// INCOMPLETE
//template <class __EnvInterface,typename __SizeType>
//__SizeType  X2fsUtil<__EnvInterface,__SizeType>::readFromFile(
//		char* buf,__SizeType objsize, __SizeType nobj,int argc, const char* argv[], FileNode* fnode,
//		__SizeType foff)
//{
//	return this->readFromFile(buf, objsize,nobj,  this->getPathNode(argc, argv), foff);
//}
/**
 * The most basic problems are
 * 			alignment
 * 			extra size for section
 * 	 There is also one solution: for linked section files,do not link them at the end,but at a specific section
 * 	 And this solution seems more beautiful and nature
 */
// DEBUG
// TODO 修改这个函数，主要是注释为TODO的部分
// 假定objsize=512,foff指的是扇区起始
template <class __EnvInterface,typename __SizeType>
__SizeType  X2fsUtil<__EnvInterface,__SizeType>::writeToFile(const char* buf,
		__SizeType objsize, __SizeType nobj, FileNode* fnode, __SizeType foff)
{
//	printf("in write to file\n");
//	printf("fnode is %x(relatively)\n",(__SizeType)fnode - (__SizeType)this->dirbuf);
	if(fnode || !This::isFile(fnode))
	{
		FileDescriptor<__SizeType> &fd=fnode->getData();
//		const __SizeType myobjsize=1;
		const __SizeType mynobj = nobj * objsize;
		const __SizeType mynsec = nobj;

//		__SizeType newsecLen = foff;
		__SizeType newlen=foff;

//		printf("before ilink got\n");
		__SizeType ilink=fd.getSectionListIndex();;
//		printf("section list inode is %d,data[0] is %d,%d\n",ilink,this->linkarr[ilink].getStart(),this->linkarr[ilink].getLimit());

		__SizeType thisSectionFileLen = this->linkarr[ilink].getLimit() * CONST_SECSIZE - foff ;
//		__SizeType thisSectionLen = this->linkarr[ilink].getLimit()  - foff ;

		__SizeType thisObjLeft = mynobj;
		__SizeType thisSecLeft = nobj;

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
			__SizeType written =
					0;
//					fwrite(thisBuf,myobjsize,thisSectionFileLen,this->fpimg);

//			env->writeSectors(EnvInterface::CUR_SEG, (const u8_t*)thisBuf, driver,
//					metainfo->lbaStartLow + thisSec, mynsec, metainfo->lbaStartHigh);

			thisBuf += written;
			thisObjLeft -= written;
			newlen += written;
			ilink++;
			if(thisObjLeft>0)
			{
				if(ilink == this->linkarrLen || this->linkarr[ilink].getLimit()==0)//require for more space
				{
					LinkedList<LinearSourceDescriptor<__SizeType>,PartialMallocToSimple> list(freemm.getMemoryManager());
//					__SizeType extraSec=(thisObjLeft / CONST_SECSIZE) ;
//					if(thisObjLeft % CONST_SECSIZE> 0)
//					{
//						extraSec++;
//					}
					__SizeType extraSec = thisSecLeft;

//					printf("new linked source,size is %d,extraSec is %d\n",thisObjLeft,extraSec);
					bool flagnewList=this->freemm.mnewLinked(extraSec, list,0);
					if(flagnewList)
					{
						// TODO nlist
//						__SizeType nlist=list.getSize();

//						printf("got list size is %d\n",nlist);
//						printf("ask link for extend : start=%d,size=%d,extsize=%d\n",fd.getSectionList(),ilink - fd.getSectionList() + 1,nlist);

						// TODO 下面这个系统调用
						__SizeType newilink=
//						(__SizeType)linkmm.extend(fd.getSectionListIndex(), ilink - fd.getSectionListIndex() + 1,nlist,
//								NULL, false);
								0;
						if(newilink==0)
						{
							this->seterrno(This::ERROR_LINKINFO_SPACE_NOT_ENOUGH);
//							return (mynobj - thisObjLeft)/objsize;
							return mynsec - thisSecLeft;
						}
//						printf("new ilink is %d\n",newilink);
						if(newilink != fd.getSectionListIndex())//不相等，需要移动
						{
							env->memcpy((char*)(linkarr + newilink),(char*) (linkarr + fd.getSectionListIndex()),ilink - fd.getSectionListIndex() );
							env->memset((char*)(linkarr + fd.getSectionListIndex()),0,ilink - fd.getSectionListIndex());
						}
						ListNode<LinearSourceDescriptor<__SizeType>> *pnewnode=list.getHead();
						ilink = newilink + ilink - fd.getSectionListIndex();
						while(pnewnode) //copy from list to that memory
						{
//							printf("copy extra ilink to the space,new(at %d) is %d,%d\n",ilink,pnewnode->getData().getStart(),pnewnode->getData().getLimit());
							this->linkarr[ilink] = pnewnode->getData();
							pnewnode = pnewnode->getNext();
							ilink++ ;
						}
						ilink = newilink + ilink - fd.getSectionListIndex() - 1; //reset to the right position
//						printf("reset ilink is %d\n",ilink);
						fd.setSectionListIndex(newilink); // change fd to the new pointer
					}else{
						this->seterrno(This::ERROR_FILEALLOCSPACE);
						if(fd.getFileLen()<newlen)
						{
							fd.setFileLen(newlen);
						}
//						return (mynobj - thisObjLeft)/objsize;
						return mynsec - thisSecLeft;
					}
				}
				//here,we continue like nothing happened
//				thisSectionFileLen = this->linkarr[ilink].getLimit() * CONST_SECSIZE ;
//				thisSectionLen = linkarr[ilink].getLimit();


//				thisSectionStart = this->linkarr[ilink].getStart() * This::SecSize;
			}else{
				if(fd.getFileLen()<newlen)
					{
						fd.setFileLen(newlen);
					}
//				return (mynobj - thisObjLeft)/objsize;
				return mynsec - thisSecLeft;
			}
		}//while
	}//if
	return 0;
}
template <class __EnvInterface,typename __SizeType>
__SizeType X2fsUtil<__EnvInterface,__SizeType>::locateILink(__SizeType startILink,__SizeType secPos,__SizeType & retOff)
{
	for(; linkarr[startILink].getLimit()!=0 &&
					secPos >= linkarr[startILink].getLimit();++startILink)
							secPos -= linkarr[startILink].getLimit();
	retOff = secPos;
	return startILink;

}
template <class __EnvInterface,typename __SizeType>
__SizeType X2fsUtil<__EnvInterface,__SizeType>::writeToILink(__SizeType ilink,const char *src,__SizeType secPos,__SizeType secLen)
{
	if(ilink==0 || ilink >= linkarrLen)
		return 0;
	if(secLen==0)
		secLen = linkarr[ilink].getLimit() - secPos;
	else if( linkarr[ilink].getLimit()<secLen || linkarr[ilink].getLimit()-secLen<secPos )
		return 0;

	// UNTESTED lba计算可能溢出到高部分
	env->writeSectors(EnvInterface::CUR_SEG,
			(const u8_t*)src, driver,metainfo->lbaStartLow + linkarr[ilink].getStart()+secPos, secLen, metainfo->lbaStartHigh);
	return secLen;
}

template <class __EnvInterface,typename __SizeType>
bool X2fsUtil<__EnvInterface,__SizeType>::extendFileSecNum(FileNode * fileNode,__SizeType extraSec,bool addFileLength)
{
	if(fileNode==NULL || extraSec==0)return false;

	LinkedList<LinearSourceDescriptor<__SizeType>,PartialMallocToSimple> list(freemm.getMemoryManager());
	bool flagnewList = freemm.mnewLinked(extraSec, list, 0);
	FileDescriptor<__SizeType>& fd=fileNode->getData();
	if(flagnewList)
	{
		__SizeType nlist=list.getSize();
		__SizeType iendLink = getEndILink(fileNode);
		__SizeType oriStartLink = fd.getSectionListIndex();
		__SizeType oriSize = iendLink - oriStartLink+1;
		if(iendLink==0)return false;

		__SizeType newilink = (__SizeType)linkmm.extend(oriStartLink, oriSize ,
				true,nlist,NULL, false);
		if(newilink == 0)  //分配失败，释放list的空间
		{
			freemm.mdeleteLinked(list);
			return false;
		}

		// 分配成功，并且需要移动数据
		if(newilink != oriStartLink)
		{
			for(__SizeType i=0;i!=oriSize-1;++i) //拷贝oriSize个，最后的(0,0)不用拷贝
			{
				linkarr[newilink+i].setStart(linkarr[i+oriStartLink].getStart());
				linkarr[newilink+i].setLimit(linkarr[i+oriStartLink].getLimit());
			}
			fd.setSectionListIndex(newilink);
		}

		// 从list设置新数据
		ListNode<LinearSourceDescriptor<__SizeType>> *p=list.getHead();
		for(__SizeType i=0;i!=nlist;++i)
		{
			linkarr[newilink+oriSize-1+i].setStart(p->getData().getStart());
			linkarr[newilink+oriSize-1+i].setLimit(p->getData().getLimit());
			p=p->getNext();
		}
		linkarr[newilink+oriSize+nlist-1].setStart(0);//设置最后一项
		linkarr[newilink+oriSize+nlist-1].setLimit(0);//设置最后一项


		if(addFileLength)
			fd.setFileLen(fd.getFileLen() + extraSec*CONST_SECSIZE);
		return true;
	}else{
		return false;
	}
}
template <class __EnvInterface,typename __SizeType>
__SizeType X2fsUtil<__EnvInterface,__SizeType>::getEndILink(FileNode *fileNode)const
{
	if(fileNode==NULL)return 0;
	__SizeType i=fileNode->getData().getSectionListIndex();
	for( ; i<linkarrLen && linkarr[i].getLimit()!=0;++i)
		;//空语句
	if(i==linkarrLen)return 0;
	return i;

}
template <class __EnvInterface,typename __SizeType>
__SizeType X2fsUtil<__EnvInterface,__SizeType>::_writeToFile(const char *buf, __SizeType nsec,FileNode *fnode,__SizeType secPos)
{
	if(nsec==0 || fnode==NULL)return 0;

	FileDescriptor<__SizeType> &fd=fnode->getData();
	if(fd.getType() != FileDescriptor<__SizeType>::TYPE_FILE)return 0;
	__SizeType	ilink = fd.getSectionListIndex();

	__SizeType retOff=0;
	__SizeType ilinkPos = locateILink(ilink, secPos, retOff);
	// TODO 验证下面的计算法则
	__SizeType extraSec = 0;
	if(retOff + nsec > linkarr[ilinkPos].getLimit()) //需要额外的空间
	{
		extraSec = retOff +nsec - linkarr[ilinkPos].getLimit();
		if(!extendFileSecNum(fnode, extraSec, true)) // 空间不足以分配
			return 0;
		ilinkPos = locateILink(ilink = fd.getSectionListIndex(), secPos, retOff);//更新数据状态
	}

	__SizeType thisOff = retOff;
	__SizeType thisLen = (nsec > (linkarr[ilinkPos].getLimit()  - thisOff)? (linkarr[ilinkPos].getLimit()  - thisOff): nsec );
	const u8_t *thisBuf=(const u8_t*)buf;
	__SizeType i=ilinkPos;
	__SizeType thisLeftSec = nsec;
	while(true)
	{
		env->writeSectors(EnvInterface::CUR_SEG, thisBuf, driver, metainfo->lbaStartLow + linkarr[i].getStart() + thisOff,
						thisLen, metainfo->lbaStartHigh);
		++i;
		if(i==linkarrLen || linkarr[i].getLimit()==0)break;
		thisLeftSec-= thisLen;
		if(nsec==0)break;
		thisBuf += thisLen * CONST_SECSIZE;
		thisOff = 0;
		thisLen = (thisLeftSec > linkarr[i].getLimit() ? linkarr[i].getLimit()  : thisLeftSec );
	}

	return nsec;

}
template <class __EnvInterface,typename __SizeType>
__SizeType X2fsUtil<__EnvInterface,__SizeType>::_readFromFile(char *buf, __SizeType nsec,FileNode *fnode,__SizeType secPos)
{
	if(nsec==0 || fnode==NULL)return 0;

	FileDescriptor<__SizeType> &fd=fnode->getData();
	if(fd.getType() != FileDescriptor<__SizeType>::TYPE_FILE)return 0;
	__SizeType	ilink = fd.getSectionListIndex();

	__SizeType retOff=0;
	__SizeType ilinkPos = locateILink(ilink, secPos, retOff);

	if(linkarr[ilinkPos].getLimit() == 0) //不可能定位
		return 0;

	__SizeType thisOff = retOff;
	__SizeType thisLen = (nsec > (linkarr[ilinkPos].getLimit()  - thisOff)? (linkarr[ilinkPos].getLimit()  - thisOff): nsec );
	u8_t *thisBuf=(u8_t*)buf;
	__SizeType i=ilinkPos;
	__SizeType thisLeftSec = nsec;
	while(true)
	{
		env->readSectors(EnvInterface::CUR_SEG, thisBuf, driver, metainfo->lbaStartLow + linkarr[i].getStart() + thisOff,
						thisLen, metainfo->lbaStartHigh);

		thisLeftSec-= thisLen;
		++i;
		if(i==linkarrLen || linkarr[i].getLimit()==0)break;

		if(nsec==0)break;
		thisBuf += thisLen * CONST_SECSIZE;
		thisOff = 0;
		thisLen = (thisLeftSec > linkarr[i].getLimit() ? linkarr[i].getLimit()  : thisLeftSec );
	}

	return nsec - thisLeftSec;
}

template<class __EnvInterface, typename __SizeType>
__SizeType X2fsUtil<__EnvInterface,__SizeType>::_randomWriteFile(const char *buf,
		__SizeType nbyte,FileNode *fnode,__SizeType byteStart)
{
	if(fnode==NULL || fnode->getData().getType()!=FileDescriptor<__SizeType>::TYPE_FILE
			|| buf==NULL || nbyte==0)return 0;
	__SizeType bufSize,startOff,endOff;
	bufSize = calculateRandomBufferSize(byteStart, nbyte, &startOff, &endOff, CONST_SECSIZE);
	ManagedObject<u8_t*,_EnvInterface,__SizeType> mbuf(env);

	FileDescriptor<__SizeType> fd=fnode->getData();

	const __SizeType nsec = bufSize/CONST_SECSIZE;
	const __SizeType startSec = byteStart/CONST_SECSIZE;


	// startOff读补齐
	if(startOff!=0)
	{
		__SizeType retOff;
		__SizeType ilink = locateILink(fd.getSectionListIndex(), startSec, retOff);
		if(linkarr[ilink].getLimit()!=0)//文件足够长
		{

			u8_t *oneUnitBuf=mbuf.getOnlyBuffer(CONST_SECSIZE);

			if( 1!= env->readSectors(EnvInterface::CUR_SEG,
					oneUnitBuf, driver, metainfo->lbaStartLow + linkarr[ilink].getStart() + retOff,
					1, metainfo->lbaStartHigh))
				return 0;//失败
			env->memcpy((char*)buf, (const char*)oneUnitBuf, startOff);//复制前面部分
		}
	}
	// endOff读补齐
	if(endOff!=0)
	{
		u8_t *oneUnitBuf=NULL;
		if(nsec==1)// nsec==1 时，扇区已经读入了,直接取用即可
			oneUnitBuf=mbuf.getOnlyBuffer(CONST_SECSIZE);
		else
		{
			__SizeType retOff;
			__SizeType ilink = locateILink(fd.getSectionListIndex(), startSec + nsec - 1, retOff);
			if(linkarr[ilink].getLimit()!=0)//文件足够长
			{

				u8_t *oneUnitBuf=mbuf.getOnlyBuffer(CONST_SECSIZE);
				if( 1!=env->readSectors(EnvInterface::CUR_SEG,
						oneUnitBuf, driver, metainfo->lbaStartLow + linkarr[ilink].getStart()+retOff,
						1, metainfo->lbaStartHigh))
					return 0; // 失败
			}
		}

		// 如果oneUnitBuf不为空，说明已经读入了，需要复制到原来的区域
		__SizeType offFromBegin = CONST_SECSIZE - endOff;
		env->memcpy((char*)buf+offFromBegin, (const char*)oneUnitBuf+offFromBegin, endOff);//复制后面部分
	}

	// 现在所有的扇区已经补齐了，数据不会覆盖，进行完整的扇区写
	__SizeType written=_writeToFile(buf, nsec, fnode, startSec);
	if(written==nsec) //没有写错误
		return nbyte;
	else //至少有一个扇区没有写
		return written*CONST_SECSIZE - startOff; //已经写的减去偏移部分
}

template<class __EnvInterface, typename __SizeType>
__SizeType X2fsUtil<__EnvInterface,__SizeType>::_randomReadFile(char *buf,
		__SizeType nbyte,FileNode *fnode,__SizeType byteStart)
{
	if(fnode==NULL || fnode->getData().getType()!=FileDescriptor<__SizeType>::TYPE_FILE
			|| buf==NULL || nbyte==0)return 0;
	__SizeType bufSize,startOff,endOff;
	bufSize = calculateRandomBufferSize(byteStart, nbyte, &startOff, &endOff, CONST_SECSIZE);

	const __SizeType nsec = bufSize/CONST_SECSIZE;
	const __SizeType startSec = byteStart/CONST_SECSIZE;

	// 现在所有的扇区已经补齐了，数据不会覆盖，进行完整的扇区写
	__SizeType readin=_readFromFile(buf, nsec, fnode, startSec);
	if(readin==nsec) //没有读错误
		return nbyte;
	else //至少有一个扇区没有读
		return readin*CONST_SECSIZE - startOff; //已经写的减去偏移部分
}

//
//template<class __EnvInterface, typename __SizeType>
//__SizeType X2fsUtil<__EnvInterface,__SizeType>::randomWriteFile(const char* buf, __SizeType nbyte,
//		FileNode* fnode, __SizeType byteStart)
//{
//	if(buf==NULL || fnode==NULL || nbyte==0)return 0;
//	__SizeType bufSize,startOff,endOff;
//	bufSize = calculateRandomBufferSize(byteStart, nbyte, &startOff, &endOff, CONST_SECSIZE);
//	if(bufSize==0)return 0;
//	__SizeType nsecs=bufSize/CONST_SECSIZE;
//	__SizeType startIlink = fnode->getData().getSectionListIndex();
//	__SizeType retOff;
//	__SizeType ilink = locateILink(startIlink, byteStart/CONST_SECSIZE, retOff);
//
//	if(linkarr[ilink].getLimit()==0)//长度不够
//	{
//		_writeToFile(buf, nsecs, fnode, linkarr[ilink-1].getStart() + linkarr[ilink-1].getLimit());
//	}else{ //长度足够容纳该位置
//
//	}
//
//
//	const char *pbase=buf;
//
//	ManagedObject<char*,_EnvInterface,__SizeType> mbuf(env);//用于自动管理资源
//
//
//
//
//
//	if(startOff!=0) //开始区间需要先读入再写回
//	{
//		if(nsecs==1)//只有一个扇区
//		{
//			randomWriteFileOneUnit(pbase, fnode, startSec, startOff, CONST_SECSIZE - endOff, NULL);
//			return;
//		}else{ //多个扇区
//			randomWriteFileOneUnit(pbase, fnode, startSec, startOff, CONST_SECSIZE, NULL);
//			//move to next sec,需要对文件的ilink进行遍历, nextSec
//		}
//
//			++startSec;
//			--nsecs;
//			pbase+=CONST_SECSIZE;// 已写指针向前移动
//			bufSize-=CONST_SECSIZE;// 需要普通写的buffer大小减小一个单位
//		}
//		//长度不足以定位到此，则不回写
//	}
//	if(nsecs==0)return nbyte; //已经写完
//
//	if(endOff!=0)//结束区间需要同样处理
//	{
//		char *oneUnitBuf=mbuf.getOnlyBuffer(CONST_SECSIZE);
//		if(oneUnitBuf== NULL)return 0;
//		||
//				1 != _readFromFile(oneUnitBuf,1,fnode,startSec + nsecs -1))
//		++startSec;
//		--nsecs;
//		bufSize-=CONST_SECSIZE;
//	}
//	if(nsecs==0)return nbyte;
//
//	__SizeType realWrite = env->writeSectors(EnvInterface::CUR_SEG,
//			(u8_t*)pbase, driver, metainfo->lbaStartLow + startSec,nsecs, metainfo->lbaStartHigh) ;
//
//	if(realWrite == nsecs)
//		return nbyte;
//	else  //差至少1个扇区没有写
//		return (bufSize/CONST_SECSIZE - nsecs+realWrite)*CONST_SECSIZE
//				- startOff; //原来总的扇区数目，减去未写的扇区数目，减去偏移
//}
//
//template<class __EnvInterface, typename __SizeType>
//__SizeType X2fsUtil<__EnvInterface,__SizeType>::randomReadFile(char* buf, __SizeType nbyte, FileNode* fnode,
//		__SizeType byteStart)
//{
//	__SizeType bufSize,startOff,endOff;
//	bufSize = calculateRandomBufferSize(byteStart, nbyte, &startOff, &endOff, CONST_SECSIZE);
//	if(bufSize==0)return 0;
//	// EFF 可以按照更高的效率处理，但是最好的方式是动态内存，因此这个优化在将来没有意义
//
//	char *myBuf=buf;
//	if(startOff!=0 || endOff!=0)
//	{
//		myBuf=(char*)env->malloc(bufSize);
//		if(myBuf==NULL)return 0;
//	}
//	__SizeType needSec = bufSize/CONST_SECSIZE;
//
//	__SizeType readSec=_readFromFile(myBuf, needSec, fnode,byteStart/CONST_SECSIZE);
//
//	if(myBuf!=buf) //需要复制过来
//	{
//	// EFF 按字节复制低效
//		for(__SizeType i=startOff;i+endOff!=bufSize;++i)
//			buf[i-startOff]=myBuf[i];
//		env->free((u8_t*)myBuf);
//	}
//
//	return readSec*CONST_SECSIZE - startOff - (CONST_SECSIZE -endOff);
//}


//
//template <class __EnvInterface,typename __SizeType>
//__SizeType  X2fsUtil<__EnvInterface,__SizeType>::randomReadSector(char *buf,__SizeType nbyte,
//		__SizeType bytePos)
//		{
//			__SizeType bufSize,startOff,endOff;
//			bufSize = calculateRandomBufferSize(bytePos, nbyte, &startOff, &endOff, CONST_SECSIZE);
//			if(bufSize==0)return 0;
//
//			char *myBuf=buf;
//			if(startOff!=0 || endOff!=0)//需要额外的空间
//			{
//				myBuf=(char*)env->malloc(bufSize);
//				if(myBuf==NULL)return 0;//内存不足
//			}
//			__SizeType needToRead = bufSize / CONST_SECSIZE;
//
//			__SizeType realRead = env->readSectors(EnvInterface::CUR_SEG,
//					(u8_t*)myBuf, driver, metainfo->lbaStartLow + bytePos/CONST_SECSIZE, needToRead, metainfo->lbaStartHigh) ;
//			if(realRead==0) //读取错误
//			{
//				if(myBuf!=buf)env->free((u8_t*)myBuf);
//				return 0;
//			}
//
//
//			if(myBuf!=buf)//复制过去
//			{
//				for(__SizeType i=startOff; i + endOff!=bufSize ;++i)//按字节复制
//					buf[i-startOff]=myBuf[i];
//				env->free((u8_t*)myBuf);
//			}
//			if(realRead == needToRead)
//				return nbyte;
//			else  //差至少1个扇区没有读
//				return realRead*CONST_SECSIZE - startOff;
//		}
//template <class __EnvInterface,typename __SizeType>
//__SizeType  X2fsUtil<__EnvInterface,__SizeType>::randomWriteSector(const char *buf,__SizeType nbyte,
//		__SizeType bytePos)
//		{
//				__SizeType bufSize,startOff,endOff;
//				bufSize = calculateRandomBufferSize(bytePos, nbyte, &startOff, &endOff, CONST_SECSIZE);
//				if(bufSize==0)return 0;
//				__SizeType nsecs=bufSize/CONST_SECSIZE;
//				__SizeType startSec=bytePos / CONST_SECSIZE;
//
//				const char *pbase=buf;
//
//
//				if(startOff!=0) //开始区间需要先读入再写回
//				{
//					if(!randomWriteOneUnit(pbase, startSec,startOff,CONST_SECSIZE,NULL))
//						return 0;
//					++startSec;
//					--nsecs;
//					pbase+=CONST_SECSIZE;// 已写指针向前移动
//					bufSize-=CONST_SECSIZE;// 需要普通写的buffer大小减小一个单位
//				}
//				if(nsecs==0)return nbyte;
//
//				if(endOff!=0)//结束区间需要同样处理
//				{
//					if(!randomWriteOneUnit(pbase + bufSize - CONST_SECSIZE,startSec+nsecs-1 ,
//							0,CONST_SECSIZE - endOff, NULL));
//					++startSec;
//					--nsecs;
//					bufSize-=CONST_SECSIZE;
//				}
//				if(nsecs==0)return nbyte;
//
//				__SizeType realWrite = env->writeSectors(EnvInterface::CUR_SEG,
//						(u8_t*)pbase, driver, metainfo->lbaStartLow + startSec,nsecs, metainfo->lbaStartHigh) ;
//
//				if(realWrite == nsecs)
//					return nbyte;
//				else  //差至少1个扇区没有写
//					return (bufSize/CONST_SECSIZE - nsecs+realWrite)*CONST_SECSIZE
//							- startOff; //原来总的扇区数目，减去未写的扇区数目，减去偏移
//		}

//template <class __EnvInterface,typename __SizeType>
//bool  X2fsUtil<__EnvInterface,__SizeType>::randomWriteOneUnit(const char *buf,__SizeType secPos,
//		__SizeType byteStart,
//		__SizeType byteEnd,
//		char *optBuffer)
//{
//		if(buf==NULL || byteStart>=byteEnd || byteEnd > CONST_SECSIZE )return false;
//		if(byteEnd - byteStart == CONST_SECSIZE)//可以直接写入
//		{
//			return 1 == env->writeSectors(EnvInterface::CUR_SEG,
//				(const u8_t*)buf, driver, metainfo->lbaStartLow + secPos, 1, metainfo->lbaStartHigh) ;
//		}
//		// 需要先读入部分，再完整写入
//		char *oneUnitBuffer=(optBuffer==NULL? (char*)env->malloc(CONST_SECSIZE):optBuffer);
//		if(oneUnitBuffer==NULL)return false;//程序空间不足
//
//
//		if( 1 != env->readSectors(EnvInterface::CUR_SEG,
//				(u8_t*)oneUnitBuffer, driver, metainfo->lbaStartLow + secPos, 1, metainfo->lbaStartHigh)  )//没有成功
//			goto ERROR;
//
//		// EFF 按字节复制，低效
//		for(__SizeType i=byteStart;i!=byteEnd;++i) //将原来的数据复制到这个扇区，然后写回
//				oneUnitBuffer[i]=buf[i-byteStart];
//		if( 1!=env->writeSectors(EnvInterface::CUR_SEG,
//					(u8_t*)oneUnitBuffer, driver, metainfo->lbaStartLow+secPos, 1, metainfo->lbaStartHigh))
//			goto ERROR;
//
//		if(oneUnitBuffer!=optBuffer)env->free((u8_t*)oneUnitBuffer);
//
//		return true;
//		ERROR:
//			if(oneUnitBuffer!=optBuffer)env->free((u8_t*)oneUnitBuffer);
//				return false;
//}
//template <class __EnvInterface,typename __SizeType>
//bool  X2fsUtil<__EnvInterface,__SizeType>::randomReadOneUnit(char *buf,__SizeType secPos,__SizeType byteStart,
//		__SizeType byteEnd,char *optBuffer)
//{
//	if(buf==NULL || byteStart>=byteEnd || byteEnd > CONST_SECSIZE )return false;
//		if(byteEnd - byteStart == CONST_SECSIZE)//可以直接写入
//		{
//			return 1 == env->readSectors(EnvInterface::CUR_SEG,
//				(const u8_t*)buf, driver, metainfo->lbaStartLow + secPos, 1, metainfo->lbaStartHigh) ;
//		}
//		// 需要先读入部分，再完整写入
//		char *oneUnitBuffer=(optBuffer==NULL? (char*)env->malloc(CONST_SECSIZE):optBuffer);
//		if(oneUnitBuffer==NULL)return false;//程序空间不足
//
//
//		if( 1 != env->readSectors(EnvInterface::CUR_SEG,
//				(u8_t*)oneUnitBuffer, driver, metainfo->lbaStartLow + secPos, 1, metainfo->lbaStartHigh)  )//没有成功
//			goto ERROR;
//
//		// EFF 按字节复制，低效
//		for(__SizeType i=byteStart;i!=byteEnd;++i) //将原来的数据复制到这个扇区，然后写回
//			buf[i-byteStart]=oneUnitBuffer[i];
//
//		if(oneUnitBuffer!=optBuffer)env->free((u8_t*)oneUnitBuffer);//释放空间
//
//		return true;
//		ERROR:
//			if(oneUnitBuffer!=optBuffer)env->free((u8_t*)oneUnitBuffer);
//				return false;
//}

//template <class __EnvInterface,typename __SizeType>
//bool  X2fsUtil<__EnvInterface,__SizeType>::randomWriteFileOneUnit(const char *buf,
//			FileNode *fnode,
//			__SizeType secPos,
//			__SizeType byteStart,
//			__SizeType byteEnd,char *optBuffer)
//{
//
//		if(buf==NULL||fnode==NULL||byteStart>=byteEnd || byteEnd>=CONST_SECSIZE)return false;
//		ManagedObject<char*,_EnvInterface,__SizeType> mbuf(env);//自动管理资源
//
//		char *oneUnitBuf=(optBuffer==NULL?mbuf.getOnlyBuffer(CONST_SECSIZE):
//				optBuffer);
//
//		if(oneUnitBuf==NULL)return 0;//空间不足
//
//		if(1==_readFromFile(oneUnitBuf, 1, fnode, secPos)) //长度足够
//		{
//			for(__SizeType i=byteStart;i!=byteEnd;++i) //可能只有一个扇区
//				oneUnitBuf[i]=buf[i-byteStart];
//			//回写
//			return 1==_writeToFile(oneUnitBuf, 1, fnode, secPos);
//		}
//		return false;
//}


template <class __EnvInterface,typename __SizeType>
__SizeType  X2fsUtil<__EnvInterface,__SizeType>::readFromFile(char* buf, __SizeType objsize, __SizeType nobj,FileNode* fnode, __SizeType foff)
{
//	printf("test getNew at readFromFile \n");
//	this->linkmm.getMemoryManager()->getNew();
//	printf("test after getNew\n");
	if(fnode || !This::isFile(fnode))
	{
		FileDescriptor<__SizeType> &fd=fnode->getData();
//		__SizeType requestLen = nobj * objsize + foff;
//		const __SizeType myobjsize=1;
		const __SizeType mynobj = nobj * objsize;
		__SizeType ilink=fd.getSectionListIndex();

		__SizeType thisSectionFileLen;
//		__SizeType thisSectionStart;
		__SizeType thisObjLeft = mynobj;
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
			__SizeType written =
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


template <class __EnvInterface,typename __SizeType>
void  X2fsUtil<__EnvInterface,__SizeType>::mkfs(_EnvInterface *env,u8_t driver,const X2fsMetaInfo<__SizeType>  *metainfo)
{
	if(!X2fsMetaInfo<__SizeType>::checkMetainfo(metainfo))
	{
		env->printf_simple("error metainfo format\n");
		return;
	}

	//debug information
	env->printf_simple("sizeof(FullNode)=%d\n",sizeof(FullNode));


	env->printf_simple("sizeof(TreeNode<FileDescriptor<__SizeType>>)=%d\n",sizeof(TreeNode<FileDescriptor<__SizeType>>));
	env->printf_simple("sizeof(SimpleMemoryNode)=%d\n",sizeof(SimpleMemoryNode));

	FullNode *p=(FullNode *)sizeof(FullNode);
	TreeNode<FileDescriptor<__SizeType>> *p2=(TreeNode<FileDescriptor<__SizeType>>*)p;
	SimpleMemoryNode *p3=(SimpleMemoryNode*)p;

	env->printf_simple("difference is (pfullnode - ptreenode)=%d\n",(signed int)((char*)p - (char*)p2));
	env->printf_simple("pfullnode - psimple=%d(should be less than 0)\n",(signed int)((char*)p - (char*)p3));

	u32_t allSecs=metainfo->metaSec;
	for(__SizeType i=0;i<metainfo->len;i++)
		allSecs+=metainfo->secnums[i];
	u32_t allocedSec=allSecs;
	u8_t *base=env->malloc(allocedSec*CONST_SECSIZE); //分配空间
	allSecs+=metainfo->reservedSec;
	for(__SizeType i=0;i<metainfo->optionalLen;++i)
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
	SimpleMemoryManager<TreeNode<FileDescriptor<__SizeType>> > smm((__SizeType)base+dirsectionOff,dirsectionLen,true);

	/**
	 * set dir root,node[0] node[1] are preserved for use
	 */
	FullNode *proot = (FullNode*)(base+dirsectionOff);//zero is preserved

	proot[0].SimpleMemoryNode::setAlloced(true); //for NULL
	proot[1].SimpleMemoryNode::setAlloced(true); //for Tree Root
	proot[2].SimpleMemoryNode::setAlloced(true); //for Dir Head
	proot[1].setSon((FullNode*)(2*sizeof(FullNode)));//The first one points to the next one,the next one is root

	proot[2].setData(FileDescriptor<__SizeType>(
			FileDescriptor<__SizeType>::TYPE_DIR,
			0,0,0,
			0,0
	));//root dir
	proot[2].setFather((FullNode*)sizeof(FullNode));//the base is the dir_section,zero is preserved

	//======================================init free space section
	u32_t freesectionOff = dirsectionOff + dirsectionLen;
	u32_t freesectionLen = metainfo->secnums[INDEX_FREE] * CONST_SECSIZE;
	LinearSourceDescriptor<__SizeType> *lsdarr=(LinearSourceDescriptor<__SizeType>*)((__SizeType)base+freesectionOff);
	new (lsdarr) LinearSourceDescriptor<__SizeType>(allSecs ,
			metainfo->wholeSecnums - allSecs);//from start to the end
	new (lsdarr+1) LinearSourceDescriptor<__SizeType>(0,0);//This allows it returns NULL,because it is at least a FreeSpaceSectionLen

	//======================================init linked info section
	u32_t linksectionOff = freesectionOff + freesectionLen;
	u32_t linksectionLen = metainfo->secnums[INDEX_LINK] * CONST_SECSIZE;
	LinearSourceDescriptor<__SizeType> *linkarr=(LinearSourceDescriptor<__SizeType>*)((__SizeType)base+linksectionOff);
	env->memset((char*)linkarr,0,linksectionLen);//set all to 0
	// 初始化linkarr的前两项已经分配，这样避免返回0作为下标来标记失败状态
	new (linkarr) LinearSourceDescriptor<__SizeType>(0xaa55,1);//0xaa55 is the verifying information,文件第一个扇区不用，所有的都是第一项不用
	new (linkarr + 1) LinearSourceDescriptor<__SizeType>(0xaa55,0);


	//============================flush to storage
	env->writeSectors(EnvInterface::CUR_SEG, (u8_t*)metainfo,0x80,metainfo->lbaStartLow+metainfo->reservedSec,metainfo->metaSec,metainfo->lbaStartHigh);
	env->writeSectors(EnvInterface::CUR_SEG, base,0x80,metainfo->lbaStartLow+metainfo->reservedSec+metainfo->metaSec, allocedSec, metainfo->lbaStartHigh);

	env->flushOutputs();
	env->free(base);
}
//template <template <class>class _Allocator>
//void X2fsUtil::getLinkedList(LinearSourceDescriptor *buffer,int i,LinkedList<LinearSourceDescriptor,_Allocator> &list,__SizeType maxlen)
//{
//	while(i < maxlen)
//	{
//		list.append(buffer[i]);
//		i++;
//	}
//}

#include "File_FileOperation.cpp"  //包含实现文件

template <typename T,typename __EnvInterface,typename __SizeType>
ManagedObject<T,__EnvInterface,__SizeType>::ManagedObject(__EnvInterface *env):
env(env),
buffer(NULL)
{}

template <typename T,typename __EnvInterface,typename __SizeType>
ManagedObject<T,__EnvInterface,__SizeType>::~ManagedObject()
{
	if(buffer!=NULL && env!=NULL)
		env->free((u8_t*)buffer);
}
template <typename T,typename __EnvInterface,typename __SizeType>
void ManagedObject<T,__EnvInterface,__SizeType>::setBufferIfNone(T buffer)
{
	if(this->buffer==NULL)
		this->buffer=buffer;
}
template <typename T,typename __EnvInterface,typename __SizeType>
T ManagedObject<T,__EnvInterface,__SizeType>::getOnlyBuffer()const
{
	return buffer;
}

template <typename T,typename __EnvInterface,typename __SizeType>
T ManagedObject<T,__EnvInterface,__SizeType>::getOnlyBuffer(__SizeType size)
{
	if(buffer==NULL)
		buffer=(T)env->malloc(size);
	return buffer;
}
#endif

