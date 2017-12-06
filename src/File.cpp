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
//===class FileDescriptor
#define __DEF_Template_FileDescriptor
#define __DEF_FileDescriptor FileDescriptor

__DEF_Template_FileDescriptor
template <class __FsEnvTransfer>
	SerializerPtr<__FsEnvTransfer>& __DEF_FileDescriptor::serialize(SerializerPtr<__FsEnvTransfer> &ptr)const
{
	return ptr	<< type
				<< sectionListIndex
				<< fileLen
				<< nameStart
				<< createdTime
			 	<< lastModefiedTime;
}
__DEF_Template_FileDescriptor
template <class __FsEnvTransfer>
	SerializerPtr<__FsEnvTransfer>& __DEF_FileDescriptor::deserialize(SerializerPtr<__FsEnvTransfer> &ptr)
{
	return ptr	>> type
				>> sectionListIndex
				>> fileLen
				>> nameStart
				>> createdTime
				>> lastModefiedTime;
}

#undef __DEF_Template_FileDescriptor
#undef __DEF_FileDescriptor



//==class X2fsMetaInfo
#define __DEF_Template_X2fsMetaInfo
#define __DEF_X2fsMetaInfo X2fsMetaInfo

__DEF_Template_X2fsMetaInfo
bool __DEF_X2fsMetaInfo::checkMetainfo(const X2fsMetaInfo& info)
{
	bool checkRes = (info.reservedSec == SECNUM_RESERVED_CONST) &&
					(info.metaSec == SECNUM_META_CONST ) &&
					(info.len == PARTS_REQUIRED) &&
					(info.validFlag == VALID_FLAG);

	return checkRes;
}
//序列化接口
__DEF_Template_X2fsMetaInfo
template <class __FsEnvTransfer>
	SerializerPtr<__FsEnvTransfer>& __DEF_X2fsMetaInfo::serialize(SerializerPtr<__FsEnvTransfer> &ptr)const
{
	ptr			<<basicSizeType
				<<reservedSec
				<<metaSec
				<<len;
	ptr.serializeBasicType(secnums, len);
	ptr 		<< optionalLen;
	ptr.serializeBasicType(optional,optionalLen);
	ptr 		<< lbaStartLow
				<< lbaStartHigh
				<< wholeSecnums
				<< validFlag;
	return ptr;
}

//序列化接口
__DEF_Template_X2fsMetaInfo
template <class __FsEnvTransfer>
	SerializerPtr<__FsEnvTransfer>& __DEF_X2fsMetaInfo::deserialize(SerializerPtr<__FsEnvTransfer> &ptr)
{
	ptr			>>basicSizeType
				>>reservedSec
				>>metaSec
				>>len;
	ptr.deserializeBasicType(secnums, len);
	ptr 		>> optionalLen;
	ptr.deserializeBasicType(optional,optionalLen);
	ptr 		>> lbaStartLow
				>> lbaStartHigh
				>> wholeSecnums
				>> validFlag;
	return ptr;
}
__DEF_Template_X2fsMetaInfo
template <class __FsEnvTransfer>
	size_t __DEF_X2fsMetaInfo::getSerializitionSize()
{
#define SZOF(prop) __FsEnvTransfer::template sizeofHostType<decltype(this->prop)>()
	return SZOF(basicSizeType)+
			SZOF(reservedSec)+
			SZOF(metaSec)+
			SZOF(len)+
			SZOF(secnums[0]) * len +
			SZOF(optionalLen) +
			SZOF(optional[0]) * optionalLen +
			SZOF(lbaStartLow) +
			SZOF(lbaStartHigh) +
			SZOF(wholeSecnums) +
			SZOF(validFlag);
#undef SZOF
}

__DEF_Template_X2fsMetaInfo
void  __DEF_X2fsMetaInfo::dumpInfo()
{
	//每次最多打印3个，这是printf_simple的实现限制
	HostEnv::printf_simple("X2fsMetaInfo{"
			"basic_sizetype:%d, "
			"reserved:%d, "
			"metainfo:%d, "
			,static_cast<u32_t>(basicSizeType),reservedSec,metaSec);

	HostEnv::printf_simple(
			"sec_filename:%d, "
			"sec_dir:%d, "
			"sec_freespace:%d, "
			,secnums[INDEX_NAME],secnums[INDEX_DIR],secnums[INDEX_FREE]);
	HostEnv::printf_simple(
			"sec_link:%d, "
			"sec_optional_secd:%d, "
			"lba_low:%d, ",secnums[INDEX_LINK],optional[INDEX_OPTIONAL_SECD],lbaStartLow);
	HostEnv::printf_simple(
			"lba_high:%d, "
			"total_secs:%d, "
			"valid_flag:%d "
			"}",lbaStartHigh,wholeSecnums,static_cast<u32_t>(validFlag));
}



#undef __DEF_Template_X2fsMetaInfo
#undef __DEF_X2fsMetaInfo
//**************X2fsMetaInfo结束

#if defined(CODE64)

//typedef SimpleMemoryManager<TreeNode<FileDescriptor<__SizeType><>> >::FileNode FileNode;

//===class X2fsUtil
// DEBUG
#define __DEF_X2fsUtil_Template template <class __FsEnv>
#define __DEF_X2fsUtil X2fsUtil<__FsEnv>
__DEF_X2fsUtil_Template
__DEF_X2fsUtil::X2fsUtil(u8_t driver,u32_t lbaBase):
			driver(driver),
			mmnodesmm(),
			filenamemm(mmnodesmm),
			listnodesmm(),
			fileTree(dirsmm),
			freemm(listnodesmm),
			linkmm(listnodesmm),
			processErrno(This::ERROR_NOERR)
	{

		HostEnv::printf_simple("reading meta info...\n");
		// 先读取元信息区域
		metainfoRAW=static_cast<u8_t*>(HostEnv::malloc(CONST_SECSIZE));

		// 读取之后进行反序列化
		HostEnv::readSectors(HostEnv::CUR_SEG, metainfoRAW, driver,
				lbaBase + __X2fsMetaInfo::SECNUM_RESERVED_CONST,__X2fsMetaInfo::SECNUM_META_CONST,  0);

		__SerializerPtr ptr{metainfoRAW};

		ptr >> metainfo;

		if( !__X2fsMetaInfo::checkMetainfo(metainfo))
			HostEnv::systemAbort("cannot valid metainfo sector", -2);

		__SizeType wholeSecs=0;
		for(__SizeType i=0;i<metainfo.len ;i++)
		{
			wholeSecs+=metainfo.secnums[i];
		}

		// 分配总的空间
		buffersRAW[0]= static_cast<u8_t*>(HostEnv::malloc(wholeSecs * CONST_SECSIZE));


		// NOTICE 如果你改变了X2fsMetaInfo的设计，必须保证所有的可选分区在必选分区之后
		// 此处仅读入必选分区
		HostEnv::readSectors(HostEnv::CUR_SEG, buffersRAW[0], driver,
				lbaBase + __X2fsMetaInfo::SECNUM_RESERVED_CONST+__X2fsMetaInfo::SECNUM_META_CONST,wholeSecs,0);

		// 依次分配每个分区的buffer地址
		for(__SizeType i=1;i<metainfo.len ; i++)
		{
			buffersRAW[i]=buffersRAW[i-1]+metainfo.secnums[i-1]*CONST_SECSIZE;
		}
		// LINK区存放的信息第一个就是长度，以便进行分配
		ptr = buffersRAW[__X2fsMetaInfo::INDEX_LINK];
		ptr >> linkarr;
//		linkarr
//
//		linkarr = static_cast<__LinearSourceDescriptor*>(buffers[__X2fsMetaInfo::INDEX_LINK]);
//		linkarr.size() = metainfo.secnums[__X2fsMetaInfo::INDEX_LINK]*CONST_SECSIZE/x2sizeof(linkarr[0]);



		initWithBuffersAlloced();

	}
// TODO 最好的方式不是传递metainfo的副本，而是先申请
// 不过这有待讨论，到底传副本好还是传指针好。因为X2fsUtil实际上不允许外部改变其状态
__DEF_X2fsUtil_Template
__DEF_X2fsUtil::X2fsUtil(u8_t driver,const __X2fsMetaInfo &metainfo,u8_t *buffers[]):
				driver(driver),
				metainfo(metainfo),
				mmnodesmm(),
				filenamemm(&mmnodesmm,0,metainfo.secnums[INDEX_NAME]*CONST_SECSIZE,false),
				listnodesmm(),
				processErrno(This::ERROR_NOERR)

		{
			if(!__X2fsMetaInfo::checkMetainfo(metainfo))
				HostEnv::systemAbort("cannot valid metainfo sector", -2);
			for(__SizeType i=0;i<metainfo.len;++i)
				this->buffersRAW[i]=buffers[i];
			__SerializerPtr ptr{buffers[__X2fsMetaInfo::INDEX_LINK]};
			ptr >> linkarr;

			initWithBuffersAlloced();
		}
// UNTESTED
__DEF_X2fsUtil_Template
void __DEF_X2fsUtil::initWithBuffersAlloced()
		{
			//	printf("in init\n");
		//	std::cout << "in init"<<std::endl;
			HostEnv::printf_simple("in init\n");


		//	this->fpimg=fopen(this->imgFile,"r+");

		//	assert(this->fpimg!=nullptr);

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

__DEF_X2fsUtil_Template
__DEF_X2fsUtil::~X2fsUtil()
{

//	if(this->fpimg)
//	{
//		printf("destruct \n");
		this->flush();  //自行调用flush
		this->freemm.~LinearSourceManager();
		this->mmnodesmm.~MallocToSimple();
		this->filenamemm.~MemoryManager();
		this->dirsmm.~AssociatedMemoryManager();

		this->linkmm.~LinearSourceManager();
//		fclose(fpimg);
//		fpimg=nullptr;
//	}
}


__DEF_X2fsUtil_Template
void __DEF_X2fsUtil::flush() {
	saveFreeSpaceSection();

	// 调整偏移到扇区起始
	saveDirSection();

	// linkarr
	__SerializerPtr linkarrPtr{buffersRAW[__X2fsMetaInfo::INDEX_LINK]};
	linkarrPtr << linkarr;


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
	// 回写meta区信息到驱动器
	__SerializerPtr ptrMeta{metainfoRAW} ;
	ptrMeta<< metainfo;
	HostEnv::writeSectors(HostEnv::CUR_SEG, metainfoRAW, driver,
			metainfo.lbaStartLow + metainfo.reservedSec ,
			metainfo.metaSec, metainfo.lbaStartHigh);

	// 回写其他区信息到驱动器
	__SizeType off=metainfo.reservedSec+metainfo.metaSec;
	for(__SizeType i=0;i<__X2fsMetaInfo::PARTS_REQUIRED;++i)
	{
#if defined(CODE64)
		HostEnv::writeSectors(HostEnv::CUR_SEG, buffersRAW[i], driver, metainfo.lbaStartLow + off , metainfo.secnums[i], metainfo.lbaStartHigh);
#else
		HostEnv::writeSectors(HostEnv::CUR_SEG, buffersRAW[i], driver, metainfo.lbaStartLow + off , metainfo.secnums[i], metainfo.lbaStartHigh);
#endif
		off += metainfo.secnums[i];
	}
}
__DEF_X2fsUtil_Template
void __DEF_X2fsUtil::retriveFileNameSection() {
	u8_t *namebuf = buffersRAW[INDEX_NAME];

	__SizeType namebufLen = metainfo.secnums[INDEX_NAME]*CONST_SECSIZE;
	// TODO 将文件名分区修改成能够直接返回原始指针的版本
	new (&filenamemm) FileNameMM(mmnodesmm,0,metainfo.secnums[INDEX_NAME]*CONST_SECSIZE,false);

	u8_t *p=namebuf;


	// 注意：下面的指针相减结果为signed型，需要改变namebufLen类型比较
	u8_t *lastp=nullptr;//unset,should point to the first non-zero
	while(*p==0 && static_cast<__SizeType>(p - namebuf) < namebufLen)p++;
	if(static_cast<__SizeType>(p - namebuf) == namebufLen)//all are zeros,no allocated
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
	while(static_cast<__SizeType>(p - namebuf) < namebufLen)
	{
		if(*p==0)
		{
			filenamemm.mnew(lastp - namebuf,static_cast<__SizeType>(p-lastp));
//			printf("filename MM new : %x %x\n",lastp - this->namebuf,(__SizeType)(p-lastp));
			while(*p==0 && static_cast<__SizeType>(p - namebuf) < namebufLen )p++;
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
__DEF_X2fsUtil_Template
 void __DEF_X2fsUtil::retriveFreeSpaceSection() {
	u8_t *freebuf=buffersRAW[INDEX_FREE];
//	__SizeType freebufLen = metainfo.secnums[INDEX_FREE];

	__SerializerPtr ptr{freebuf};
	ptr >> freemm;

	// DEPRECATED 直接序列化链表
//	__LinearSourceDescriptor *lsbarr=reinterpret_cast<__LinearSourceDescriptor*>(freebuf);
//	new (&freemm) FreeSpaceMM(&listnodesmm,lsbarr[0].getStart(),lsbarr[0].getLimit());
//	auto lsdspace=freemm.getSpace();
//
//	// 如果下标1的长度不为0，且下标1的开始大于下标0的开始，下标1的结束大于下标0的结束
//	// 则预先分配一段从开始到下标1的开始的空间，这段空间被标记为占用状态
//	if(lsbarr[1].getLimit()!=0 && lsbarr[1].getStart() > lsbarr[0].getStart() &&
//			lsbarr[0].getStart()-lsbarr[1].getStart()>=lsbarr[1].getLimit()-lsbarr[0].getLimit())
//	{
////		printf("freemm new in 1, newed %x,%x\n",lsbarr[0].getStart(),lsbarr[1].getStart()-lsbarr[0].getStart());
//		freemm.mnew(lsbarr[0].getStart(),lsbarr[1].getStart()-lsbarr[0].getStart());
//	}
//
//
//	if(lsbarr[1].getLimit()!=0)
//	{
//		for(__SizeType i=2;i*sizeof(lsbarr[0]) < freebufLen && lsbarr[i].getLimit()>0;++i)
//		{
//			freemm.mnew(lsbarr[i-1].getStart()+lsbarr[i-1].getLimit(),
//					lsbarr[i].getStart()-lsbarr[i-1].getStart()-lsbarr[i-1].getLimit());
//		}
//	}
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

// 仅仅将链表序列化然后写入即可
__DEF_X2fsUtil_Template
void __DEF_X2fsUtil::saveFreeSpaceSection()
{
	__SerializerPtr ptr{buffersRAW[INDEX_FREE]} ;
	ptr<< freemm;
//	__LinearSourceDescriptor* lsdarr=reinterpret_cast<__LinearSourceDescriptor*>(buffersRAW[INDEX_FREE]);
//	lsdarr[0]=this->freemm.getSpace();
//	__FsEnvListNode_LinearSourceDescriptor *pfreenode=this->freemm.getHead();
////	printf("head of freemm is %x\n",(int)(__SizeType)pfreenode);
//	int i=1;
//	while(pfreenode)
//	{
//		lsdarr[i++]=pfreenode->getData();
////		printf("this node is %x,save free space %x,%x\n",pfreenode,(int)pfreenode->getData().getStart(),(int)pfreenode->getData().getLimit());
//		pfreenode=pfreenode->getNext();
//	}
//	new (&lsdarr[i]) __LinearSourceDescriptor(0,0);
}


__DEF_X2fsUtil_Template
void __DEF_X2fsUtil::retriveLinkedInfoSection() {
	// 管理0~160错误，第一个不需要管理
	new (&linkmm) LinkedInfoMM(listnodesmm,2,linkarr.size()-2);//manage by number

	//====build the free space of the linked section
//	printf("linkarr off is %x(sec nums,relative to dirbase) \n",((__SizeType)this->linkarr - (__SizeType)this->dirbuf)/This::SecSize);
//	printf("sizeof(node) = %d,maxi = %d ,linkarr[0].start = %x,linkarr[1].start=%x \n",sizeof(this->linkarr[0]),this->linkarr.size(),
//			this->linkarr[0].getStart(),this->linkarr[1].getStart());

	// i定位到第一个有效的节点，有效节点长度不为0
	__SizeType i=2;
	while(i < linkarr.size() && linkarr[i].getLimit()==0)i++;

	__SizeType lastNonZero=i;
	i+=1;
//	printf("i = %d,lastNonZero = %d \n",i,lastNonZero);

	// 下面的循环每次分配[lastNonZero,len)长度的区间,也就是对linkarr进行初始化，(0,0)的节点被跳过，标记为未用状态
	while(i < linkarr.size() )
	{
		if( linkarr[i].getLimit()==0)
		{
//			printf("in linkmm new %x,%x\n",lastNonZero,i - lastNonZero+1);
			u8_t* checkPointerValid=
					static_cast<u8_t*>(
							linkmm.mnew(lastNonZero,i - lastNonZero + 1));//one more for the trailing 0
			if(!checkPointerValid)
			{
				HostEnv::systemAbort("Cannot allocate space for linkmm,so the filesystem cannot be initialized.", -2);
			}
			while(i < linkarr.size() && this->linkarr[i].getLimit()==0)i++;
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


// UNTESTED
__DEF_X2fsUtil_Template
void __DEF_X2fsUtil::retriveDirSection() {
	// NOTE this is not safe under multithreaded
	static ptrdiff_t localPtrBase; // can be changed unconditionally
//	FileNode *nodebuffer=(FileNode*)this->dirbuf;
	u8_t* dirbuf=buffersRAW[INDEX_DIR];
//	__SizeType dirbufLen=metainfo.secnums[INDEX_DIR]*CONST_SECSIZE;
	decltype(dirsmm.getLen())  nodesNum=0;


	struct __MyEnv:public __FsEnv{
			AS_MACRO static ptrdiff_t ptrBase(){
					return localPtrBase;
				}
	};
	SerializerPtr<__MyEnv> ptr{dirbuf};//动态调整基地址
	ptr >> nodesNum; //获取长度
	buffersDir = reinterpret_cast<u8_t*>(HostEnv::malloc(nodesNum * FileNodeMM::getEachSize()));//分配空间
	localPtrBase=reinterpret_cast<ptrdiff_t>(buffersDir); //重新调整基地址

	ptr >> dirsmm;
	FileNode *fileNodes=reinterpret_cast<FileNode*>(buffersDir + sizeof(FileNode));
	SimpleMemoryNode *smmnodes = reinterpret_cast<SimpleMemoryNode*>(
					buffersDir +  sizeof(FileNode)+
					sizeof(FileNode)*nodesNum);
	std::cout << "diff="<<(reinterpret_cast<char*>(smmnodes) - reinterpret_cast<char*>(fileNodes)) << std::endl;
	char *p0=reinterpret_cast<char*>(ptr.getPtr());
	for(size_t i=0;i!=nodesNum;++i)
		ptr >> fileNodes[i];
	char *p1 = reinterpret_cast<char*>(ptr.getPtr());
	for(size_t i=0;i!=nodesNum;++i)
		ptr >> smmnodes[i];

	cout << "p1 - p0 =" << (p1-p0)<<endl;

	new (&fileTree) FileTree(dirsmm,&fileNodes[1]);
}
__DEF_X2fsUtil_Template
void __DEF_X2fsUtil::saveDirSection() {
//	this->adjustDirbufOffset( nullptr - buffersRAW[INDEX_DIR]);
	static ptrdiff_t localPtrBase;
	struct __MyEnv:public __FsEnv{
			AS_MACRO static ptrdiff_t ptrBase(){
					return localPtrBase;
				}
	};
	localPtrBase = reinterpret_cast<ptrdiff_t>(buffersDir); //赋值基地址
	auto  nodesNum=dirsmm.getLen();

	FileNode *fileNodes=reinterpret_cast<FileNode*>(buffersDir + sizeof(FileNode));
	SimpleMemoryNode *smmnodes = reinterpret_cast<SimpleMemoryNode*>(buffersDir + sizeof(FileNode)*(nodesNum+1));

	SerializerPtr<__MyEnv> ptr{buffersDir};
	ptr					<< nodesNum
						<< dirsmm;
	for(size_t i=0;i!=nodesNum;++i)
			ptr << fileNodes[i];
	for(size_t i=0;i!=nodesNum;++i)
			ptr << smmnodes[i];


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
__DEF_X2fsUtil_Template
char *__DEF_X2fsUtil::getFileNameCstr(const __FileDescriptor& fd, __SizeType& nlen)const
{
	if(fd.getNameOffset()==0)return nullptr;
	u8_t *namebuf=buffersRAW[INDEX_NAME];
	char *p=reinterpret_cast<char*>(namebuf+fd.getNameOffset());
	nlen = static_cast<__SizeType>(*reinterpret_cast<unsigned char*>(p));
	return p+1;
}

//__DEF_X2fsUtil_Template
//std::string __DEF_X2fsUtil::getFileName(const FileNode *p)const
//{
//	__SizeType nlen;
//	const FileDescriptor<__SizeType> fd=p->getData();
//	char *ch=getFileNameCstr(fd, nlen);
//	return std::move(std::string(ch));
//}

__DEF_X2fsUtil_Template
void __DEF_X2fsUtil::printNode(const FileNode* p)const {
	__SizeType nlen=0;
	char *pname;
	if(p)
	{
		pname=getFileNameCstr(p->getData(), nlen);
		if(This::isDirectory(p))
		{
			HostEnv::printf_simple("Dir:");
			HostEnv::printf_sn(pname,nlen);
			HostEnv::printf_simple("\n");
//			HostEnv::printf_simple("Dir:%.*s\n",nlen,pname);
		}else if(This::isFile(p))
		{
//			printf("File:%.*s %x  %x\n",nlen,pname,p->getData().getSectionStart(),p->getData().getSectionSpan());
			HostEnv::printf_simple("File:");
			HostEnv::printf_sn(pname,nlen);
			HostEnv::printf_simple(" %d  %d\n",p->getData().getSectionListIndex(),p->getData().getFileLen());
		}
	}
}

__DEF_X2fsUtil_Template
void __DEF_X2fsUtil::listOnNode(const FileNode* p,int maxdeepth)const
{
	if(maxdeepth<=0)return;
	this->printNode(p);
	if(p  && This::isDirectory(p))
	{
		FileNode * pfn=p->getSon();
		while(pfn)
		{
			HostEnv::printf_simple("\t");
			this->printNode(pfn);
			pfn=pfn->getNext();
		}
		pfn=static_cast<FileNode*>(p->getSon());
		while(pfn)
		{
			if(This::isDirectory(pfn))
			{
//				printf("calling list sub dir,deepth is %d\n",maxdeepth);
				this->listOnNode(pfn, maxdeepth-1);
			}
			pfn=static_cast<FileNode*>(pfn->getNext());
		}
	}

}
__DEF_X2fsUtil_Template
bool __DEF_X2fsUtil::hasFilename(FileNode * fnode,const char *name)const
{
	return this->locatePath(fnode, name)!=nullptr;
}
/**
 * default
 *
 */
__DEF_X2fsUtil_Template
bool __DEF_X2fsUtil::create(FileNode *p,u8_t type,const char *name,__SizeType secSpan,__TimeType ctime)
{
	if(!p)return false;

	u8_t *namebuf=buffersRAW[INDEX_NAME];
//	__SizeType namebufLen = metainfo.secnums[INDEX_NAME];

	if(this->locatePath(p, name)!=nullptr)//check existence of name
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

	FileNode *fnode=static_cast<FileNode*>(this->dirsmm.getNew());//request for new FileNode
//	printf("fnode is %x(relative to dirbase) \n",(__SizeType)fnode-(__SizeType)this->dirbuf);
	if(fnode==nullptr){
		this->seterrno(This::ERROR_DIRTREESPACE);
		goto error;
	}
	if(type==__FileDescriptor::TYPE_FILE)
	{
		if(secSpan<2)// ADDDOC 文件类型至少分配2个扇区
		{
			secSpan=2;
		}
		fsecStart=reinterpret_cast<__SizeType>(freemm.mnew(secSpan));//request for new space
	//	printf("fsecStart is %x\n",(int)fsecStart);
		if(fsecStart==0)//no enough space
		{
			this->seterrno(This::ERROR_FILEALLOCSPACE);
			goto error;
		}
		HostEnv::printf_simple("dump link mm\n");
		HostEnv::printf_simple("space is %d,%d\n",this->linkmm.getSpace().getStart(),this->linkmm.getSpace().getLimit());

		// DEBUGINFO
//		ListNode<LinearSourceDescriptor> *p=this->linkmm.getHead();
//		while(p)
//		{
//			HostEnv::printf_simple("(%d,%d)\n",p->getData().getStart(),p->getData().getLimit());
//			p = p->getNext();
//		}


		// NOTE 使用__FsEnvSizeType来保证转换成数字类型，然后再向下转换
		linkInode=reinterpret_cast<__SizeType>(linkmm.mnew(2));
		if(linkInode==0)
		{
			this->seterrno(This::ERROR_LINKINFO_SPACE_NOT_ENOUGH);
			HostEnv::printf_simple("error linkInode\n");
			goto error;
		}
	}else if(type==__FileDescriptor::TYPE_DIR){
//		printf("creating dir %s\n",name);
		secSpan=0;
		fsecStart=0;
		linkInode=0;
	}

	namelen=HostEnv::strlen(name);
	fnamedst=reinterpret_cast<char*>(this->filenamemm.mnew(namelen+1)); //request for name space,the first byte is for length
//	printf("fdst is %x \n",(__SizeType)fdst);
	if(fnamedst==nullptr)
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
	*static_cast<unsigned char*>(namebuf + reinterpret_cast<ptrdiff_t>(fnamedst)) = namelen;
//	*(unsigned char*)((__FsEnvSizeType)namebuf+
//			(__SizeType)(__FsEnvSizeType)fnamedst)=namelen;
	HostEnv::strncpy(  reinterpret_cast<char*>((namebuf+
			reinterpret_cast<ptrdiff_t>(fnamedst)+1)),name,namelen);

	//===================Set section link info
	if(linkInode!=0)
	{
		this->linkarr[linkInode] = __LinearSourceDescriptor(fsecStart,secSpan);
		this->linkarr[linkInode + 1] = __LinearSourceDescriptor(0,0);
	}
//	printf("during created[3], node is : %.*s \n",plen,this->getFileName(p->getData(), plen));
	//==================Set file node
	new (fnode)
			__TreeNode_FileDescriptor(__FileDescriptor(
					type,
					linkInode,secSpan*CONST_SECSIZE,
					reinterpret_cast<__SizeType >(fnamedst),
					ctime,ctime
			)
	);

	this->insertNode(p, fnode);
	return true;
	error:
		if(fnode!=nullptr)
			this->dirsmm.withdraw(fnode);
		if(fsecStart!=0)
			this->freemm.mdelete(reinterpret_cast<char*>(fsecStart),secSpan);
		if(linkInode!=0)
			this->linkmm.mdelete(reinterpret_cast<char*>(linkInode),2);
		if(fnamedst!=nullptr)
			this->filenamemm.mdelete(fnamedst,namelen+1);
	return false;
}
/**
 * 如果任何一步出错，都应当把申请的空间换回去
 */
__DEF_X2fsUtil_Template
bool __DEF_X2fsUtil::createFile(FileNode *p,const char *name,__SizeType secNum)
{
	return this->create(p,__FileDescriptor::TYPE_FILE,name,secNum,0);
}
__DEF_X2fsUtil_Template
bool __DEF_X2fsUtil::mkdir(FileNode * fatherDir,const char *dirname)
{
	return this->create(fatherDir,__FileDescriptor::TYPE_DIR,dirname,0,0);
}
__DEF_X2fsUtil_Template
void __DEF_X2fsUtil::freeNode(FileNode * node)
{
	if(node && node != this->fileTree.getHead())//You cannot free the head!!!
	{
		u8_t *namebuf=buffersRAW[INDEX_NAME];
		__SizeType plen;
		char *pname2;
		pname2=this->getFileNameCstr(node->getData(), plen);
		HostEnv::printf_simple("in free node : ");
		HostEnv::printf_sn(pname2,plen);
		HostEnv::printf_simple("\n");
//
//		printf("type is %d \n",node->getData().getType());
		if(This::isDirectory(node))
		{
			FileNode * eachSon=static_cast<FileNode*>(node->getSon());
			while(eachSon)
			{
				this->freeNode(eachSon);
				eachSon = static_cast<FileNode*>(eachSon->getNext());
			}
		}
		__SizeType off=node->getData().getNameOffset();
		u8_t *pname=namebuf + off;

//		printf("before memset , len is %d,str is %.*s\n",*pname,*pname,pname + 1);//dirs are not deleted
//		printf("after , len = %d ,str is \"%.*s\"(may not appear)\n",*pname,*pname,pname + 1);
		this->filenamemm.mdelete(reinterpret_cast<char*>(off), *pname + 1);
		HostEnv::memset(reinterpret_cast<char*>(pname),0,*pname + 1);
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
			HostEnv::printf_simple("link i is %d\n",i);
			for(;i<this->linkarr.size() && this->linkarr[i].getLimit()!=0;i++)
			{
				this->freemm.mdelete(
						reinterpret_cast<char*>(this->linkarr[i].getStart()),this->linkarr[i].getLimit());
				this->linkarr[i]=__LinearSourceDescriptor(0,0);//reset as unused
			}
			__SizeType linklen = i - linkstart + 1;//including the trailing 0.
			//============free space returned(linked sections)
			HostEnv::printf_simple("linkmm delete %d,%d\n",linkstart,linklen);
			this->linkmm.mdelete(
					reinterpret_cast<char*>(linkstart), linklen);
		}
		//==============linked info returned

		//here is a question : if one section is shared by many files,should we delete it too ? woo ~ ~
		//we'll use reference count to do that later.
		this->fileTree.free(node);
		//==============file tree withdrawn

	}
}
__DEF_X2fsUtil_Template
void __DEF_X2fsUtil::insertNode(FileNode *dst,FileNode *fnode)
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
__DEF_X2fsUtil_Template
void __DEF_X2fsUtil::removeNode(FileNode * node)
{
	if(node && node != this->fileTree.getHead())//You cannot remove the root!!!
	{
		FileNode * prev=reinterpret_cast<FileNode*>(node->getPrevious());
		FileNode *father= nullptr;
		FileNode *next= nullptr;
		if(prev!= nullptr)
		{
			prev->removeNext();
		}else{
			father=static_cast<FileNode*>(node->getDirectFather());
			next =static_cast<FileNode*>(node->getNext());
			father->setSon(static_cast<FileNode*>(next));
			if(next)
			{
				next->setFather(father);
				next->setPrevious(nullptr);
			}
		}
	}
}
__DEF_X2fsUtil_Template
bool __DEF_X2fsUtil::deleteFile(FileNode* fnode)
{
	freeNode(fnode);
	removeNode(fnode);
	return true;

}

__DEF_X2fsUtil_Template
bool __DEF_X2fsUtil::rename(FileNode *node,const char *newname)
{

	u8_t *namebuf=buffersRAW[INDEX_NAME];
//	printf("test getNew \n");
	this->linkmm.getMemoryManager()->getNew();
//	printf("test after getNew\n");
	__SizeType newlen=HostEnv::strlen(newname);
	__SizeType orilen;
	char *pori;
	pori=this->getFileNameCstr(node->getData(),orilen);
	if(HostEnv::strncmp(newname,pori,newlen)==0)
	{
		return true;//the names have been the same
	}
	//alloc new space
	HostEnv::printf_simple("before extend\n");
	__SizeType newoff=reinterpret_cast<__SizeType>(
			this->filenamemm.extend(node->getData().getNameOffset(),orilen+1, newlen - orilen,
					static_cast<char*>(namebuf),false));
	u8_t *pnew=namebuf + newoff;
	HostEnv::printf_simple("after extend\n");
//	printf("orginal off is %x,new off is %x\n",node->getData().getNameOffset(),newoff);
	if(pnew)
	{
		*pnew = newlen;
		HostEnv::strncpy(static_cast<char*>(pnew) + 1,newname,newlen);
		node->getData().setNameOffset(newoff);
		return true;
	}else{
		return false;
	}
}

__DEF_X2fsUtil_Template
bool __DEF_X2fsUtil::move(FileNode *p,FileNode* dstDir,const char *newname)
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
__DEF_X2fsUtil_Template
void __DEF_X2fsUtil::dumpFileInfo(FileNode * fnode)
{
	const __FileDescriptor& fd=fnode->getData();
	__SizeType nlen;char *p;
	p=this->getFileNameCstr(fd, nlen);
	HostEnv::printf_simple("file name : ");
	HostEnv::printf_sn(p,nlen);
	HostEnv::printf_simple("\n");
	HostEnv::printf_simple("linked section list start : %d\nsections are : \n",fd.getSectionListIndex());
	__SizeType i=fd.getSectionListIndex();
	while(i<this->linkarr.size() && this->linkarr[i].getLimit()!=0)
	{
		HostEnv::printf_simple("(%x,%x)   ",this->linkarr[i].getStart(),this->linkarr[i].getLimit());
		i++;
	}
	HostEnv::printf_simple("\n");
	HostEnv::printf_simple("type : %d\n",fd.getType());
	HostEnv::printf_simple("length : %d \n",fd.getFileLen());
	HostEnv::printf_simple("created time : %d\n",fd.getCreatedTime());
	HostEnv::printf_simple("last modified time : %d\n",fd.getLastModefiedTime());
}

/**
 *
 */
__DEF_X2fsUtil_Template
bool __DEF_X2fsUtil::createFileInRoot(const char* name, __SizeType secNum)
{
	return this->createFile(static_cast<FileNode*>(this->fileTree.getHead()), name, secNum);
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
//					__FileDescriptor::TYPE_FILE,
//					fsecStart,secNum,fsecStart,0,
//					(__SizeType)fdst,
//					0,0
//			)
//	);
////	printf("dump fileTree , head & root : %x  %x\n",(__SizeType)this->fileTree.getHead() - (__SizeType)this->dirbuf
////			,(__SizeType)this->fileTree.getHead()->getDirectFather() - (__SizeType)this->dirbuf);
//
//	if(this->fileTree.getHead()->getSon()==nullptr)
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

__DEF_X2fsUtil_Template
bool __DEF_X2fsUtil::hasFilename(int argc,const char *argv[],const char *name)const
{
	return this->hasFilename(this->getPathNode(argc, argv), name);
}

//__DEF_X2fsUtil_Template
//bool __DEF_X2fsUtil::hasFilename(FileNode *fnode,const std::string& name)const
//{
//	return this->hasFilename(fnode, name.c_str());
//}

__DEF_X2fsUtil_Template
bool __DEF_X2fsUtil::createFile(int argc,const char* argv[],int secSpan)
{
	int errlv;
	FileNode *p=this->locatePath(this->getRootBase(),argc-1,argv,errlv);
	if(p==nullptr)
	{
		this->seterrno(This::ERROR_PATH_PARENT_NOT_EXIST);
//		printf("not found parent\n");
		return false;
	}else{
		FileNode *pson=this->locatePath(p, argv[argc-1]);
		if(pson!=nullptr)
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
			HostEnv::printf_simple("on node :");
			char prevLast=filename[plen];
			filename[plen]='\0';
			HostEnv::printf_simple(filename);
			filename[plen]=prevLast;
			HostEnv::printf_simple(" \t");
//			HostEnv::printf_simple("on node : %.*s \t",plen,filename);
			HostEnv::printf_simple("create file ");
			HostEnv::printf_simple(argv[argc-1]);
			HostEnv::printf_simple("\n");
			bool flag=this->createFile(p, argv[argc-1], secSpan);

			HostEnv::printf_simple("after created, node is : ");
			char *filename2=getFileNameCstr(p->getData(), plen);
			prevLast=filename2[plen];
			filename[plen]='\0';
			HostEnv::printf_simple(filename2);
			filename2[plen]=prevLast;
			HostEnv::printf_simple(", scceed?%d, errno is %d\n",flag,geterrno());

			return flag;
		}
	}
}

__DEF_X2fsUtil_Template
bool __DEF_X2fsUtil::createDir(int argc,const char* argv[])
{
	int errlv;
	FileNode *p=this->locatePath(this->getRootBase(),argc-1,argv,errlv);
	if(p==nullptr)
	{
		this->seterrno(This::ERROR_PATH_PARENT_NOT_EXIST);
//		printf("not found parent\n");
		return false;
	}else{
		FileNode *pson=this->locatePath(p, argv[argc-1]);
		if(pson!=nullptr)
		{
			this->seterrno(This::ERROR_FILE_ALREDY_EXIST);
//			printf("exist already\n");
			return false;
		}else{
			HostEnv::printf_simple("mkdir ");
			HostEnv::printf_simple(argv[argc-1]);
			HostEnv::printf_simple("\n");
			return this->mkdir(p, argv[argc-1]);
		}
	}
}
__DEF_X2fsUtil_Template
bool __DEF_X2fsUtil::deleteFile(int argc,const char * argv[])
{
	return deleteFile(getPathNode(argc, argv));
}
__DEF_X2fsUtil_Template
bool __DEF_X2fsUtil::rename(int argc,const char *argv[],const char *newname)
{
	return this->rename(this->getPathNode(argc, argv), newname);
}
__DEF_X2fsUtil_Template
bool __DEF_X2fsUtil::move(int argcSrc,const char *argvSrc[],int argcDst,const char *argvDst[],const char *newname)
{
	return this->move(this->getPathNode(argcSrc, argvSrc),this->getPathNode(argcDst, argvDst), newname);
}

__DEF_X2fsUtil_Template
int __DEF_X2fsUtil::tellType(int argc,const char* argv[])const
{
	auto pnode=this->getPathNode(argc, argv);
	if(pnode==nullptr)
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
__DEF_X2fsUtil_Template
void __DEF_X2fsUtil::dumpFileInfo(int argc,const char *argv[])
{
	this->dumpFileInfo(this->getPathNode(argc, argv));
}
__DEF_X2fsUtil_Template
void __DEF_X2fsUtil::listNode(int argc,const char * argv[],int maxdeepth)const
{
	int errlv;
	FileNode *p=this->locatePath(this->getRootBase(),argc-1,argv,errlv);
//	printf("in p, p==rootBase?%d \n",p == this->getRootBase());
//	this->listOnNode(p);
//	printf("\n");
	if(p==nullptr)
	{
//		printf("No parent path for such file or directory\n");
		return;
	}else{
		FileNode *pson=this->locatePath(p, argv[argc-1]);
//		printf("locate for %s\n",argv[argc-1]);
		if(pson!=nullptr)
		{
			if(This::isFile(pson))
			{
				this->printNode(pson);
			}else{
				this->listOnNode(pson,maxdeepth);
			}
		}else{
			HostEnv::printf_simple("No such file or directory\n");
		}
	}

}
__DEF_X2fsUtil_Template
void __DEF_X2fsUtil::listRoot()const
{
	FileNode *pfn=static_cast<FileNode *>(this->fileTree.getHead());

	HostEnv::printf_simple("/:\n");
	pfn=static_cast<FileNode *>(pfn->getSon());
	__SizeType nlen=0;
	char *pname;
	char savePrev;
	while(pfn)
	{
		pname=this->getFileNameCstr(pfn->getData(), nlen);
		if(nlen!=0)
		{
//			printf("\t%.*s %x  %x\n",nlen,pname,pfn->getData().getSectionStart(),pfn->getData().getSectionSpan());
			HostEnv::printf_simple("\t");
			savePrev=pname[nlen];
			HostEnv::printf_simple(pname);
			pname[nlen]=savePrev;
			HostEnv::printf_simple(" %d  %d\n",pfn->getData().getSectionListIndex(),pfn->getData().getFileLen());
		}
		pfn=static_cast<FileNode *>(pfn->getNext());
	}
}

__DEF_X2fsUtil_Template
void __DEF_X2fsUtil::listNode(const FileNode* p)const
{
//	std::cout << "in listNode"<<std::endl;
	const FileNode *pfn=p;

	pfn=pfn->getSon();
	__SizeType nlen=0;
	char *pname;
	while(pfn)
	{
		pname=this->getFileNameCstr(pfn->getData(), nlen);
		if(nlen!=0)
		{
//			printf("\t%.*s %x  %x\n",nlen,pname,pfn->getData().getSectionStart(),pfn->getData().getSectionSpan());
			HostEnv::printf_simple("\t");
			HostEnv::printf_sn(pname, nlen);
			HostEnv::printf_simple(" sectionList=%d  fileLen=%d\n",pfn->getData().getSectionListIndex(),pfn->getData().getFileLen());
		}
		pfn=static_cast<FileNode *>(pfn->getNext());
	}
}

__DEF_X2fsUtil_Template
typename __DEF_X2fsUtil::__SizeType __DEF_X2fsUtil::calculateRandomBufferSize(
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
__DEF_X2fsUtil_Template
void __DEF_X2fsUtil::initBuffers() {
//	this->namebuf = (char*)malloc(This::namebufLen);
//	this->dirbuf = (char*)malloc(This::dirbufLen);
//	this->freebuf = (char*)malloc(This::freebufLen);
//	this->linkbuf = (char*)malloc(This::linkbufLen);
//	assert(this->namebuf!=nullptr);
//	assert(this->dirbuf!=nullptr);
//	assert(this->freebuf!=nullptr);
//	assert(this->linkbuf!=nullptr);
//	fseek(this->fpimg,this->reservedLen,SEEK_SET);
//	printf("reservedLen = %x , FileNameSection = %x , namebufLen = %x , dirbufLen = %x , freebufLen = %x \n",this->reservedLen,
//			This::FileNameSection,this->namebufLen,this->dirbufLen,this->freebufLen);
//	fread(this->namebuf,sizeof(char),this->namebufLen,this->fpimg);
//	fread(this->dirbuf,sizeof(char),this->dirbufLen,this->fpimg);
//	fread(this->freebuf,sizeof(char),this->freebufLen,this->fpimg);
//	fread(this->linkbuf,sizeof(char),this->linkbufLen,this->fpimg);
}

__DEF_X2fsUtil_Template
void __DEF_X2fsUtil::adjustDirbufOffset(ptrdiff_t off) {
		FileNode *nodebuffer=reinterpret_cast<FileNode*>(buffersRAW[__X2fsMetaInfo::INDEX_DIR]);
//		printf("call before adjust\n");

		__SizeType dirBufLen = metainfo.secnums[__X2fsMetaInfo::INDEX_DIR]*CONST_SECSIZE;
		for(__SizeType i=1;i*x2sizeof(FileNode) <dirBufLen ; i++ )
		{
			// BUG [待修复] 这里，由于32位指针域只有4个字节，而指针域需要容纳64位的地址，因此失败。
			// 解决方法：1.多预留一点  2.不要原址操作，再申请新的buffer。
			// 这里也暴露了一个问题，所有需要在高位系统上存储高位系统指针的域，都是不安全的。
			// 注意，这个bug还没有找到明显的解决方案。
//			if(nodebuffer[i].SimpleMemoryNode::isAlloced()) //已被分配
			if(true)
			{
				// TODO
//				nodebuffer[i].setFather(
//						(nodebuffer[i].getDirectFather()!=nullptr?(FileNode*)((__FsEnvSizeType)nodebuffer[i].getDirectFather() + (__FsEnvSizeType)off ):(FileNode*)nullptr));
//				nodebuffer[i].setNext(
//						(nodebuffer[i].getNext()!=nullptr?(FileNode*)((__FsEnvSizeType)nodebuffer[i].getNext() + (__FsEnvSizeType)off):(FileNode*)nullptr) );
//				nodebuffer[i].setPrevious(
//						(nodebuffer[i].getPrevious()!=nullptr?(FileNode*)((__FsEnvSizeType)nodebuffer[i].getPrevious() + (__FsEnvSizeType)off):(FileNode*)nullptr ) );
//				nodebuffer[i].setSon(
//						(nodebuffer[i].getSon()!=nullptr?(FileNode*)((__FsEnvSizeType)nodebuffer[i].getSon() + (__FsEnvSizeType)off):(FileNode*)nullptr) );
			}
		}
}
//typename
__DEF_X2fsUtil_Template
typename __DEF_X2fsUtil::FileNode * __DEF_X2fsUtil::locatePath(FileNode* base,int argc, const char* argv[], int& errorLevel)const
{
	if(base==nullptr || argc<0)
		{
			errorLevel=-1;
			return nullptr;
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
__DEF_X2fsUtil_Template
typename __DEF_X2fsUtil::FileNode * __DEF_X2fsUtil::locatePath(FileNode* base, const char* name)const
{
	if(!base)return nullptr;
	FileNode *p= reinterpret_cast<FileNode *>(base->getSon());
	__SizeType len;
	const char *pname;
//	printf("finding name %s\n",name);
	while(p)
	{
		pname = this->getFileNameCstr(p->getData(), len);
//		printf("cmp %.*s,n is %d\n",len,pname,len);
		if(len == HostEnv::strlen(name)  && HostEnv::strncmp(pname,name,len)==0)
		{
			break;
		}
		p = reinterpret_cast<FileNode*>(p->getNext());
	}
	return p;
}
__DEF_X2fsUtil_Template
typename __DEF_X2fsUtil::FileNode * __DEF_X2fsUtil::getPathParentNode(int argc,const char * argv[])const
{
	int errlv;
	return this->locatePath(this->getRootBase(),argc-1,argv,errlv);
}
__DEF_X2fsUtil_Template
typename __DEF_X2fsUtil::FileNode * __DEF_X2fsUtil::getPathNode(int argc,const char * argv[])const
{
	if(argc==0)return this->getRootBase();
	int errlv;
	auto p=this->locatePath(this->getRootBase(),argc-1,argv,errlv);
	if(p==nullptr)
	{
		this->seterrno(This::ERROR_PATH_PARENT_NOT_EXIST);
		return nullptr;
	}
	auto pson=this->locatePath(p, argv[argc-1]);
	if(pson==nullptr)
	{
		this->seterrno(This::ERROR_PATH_FILE_NOT_EXIST);
		return nullptr;
	}
	this->seterrno(This::ERROR_NOERR);
//	printf("in getPathNode %s,returned is %x\n",argv[argc-1],(__SizeType)pson-(__SizeType)this->dirbuf);
	return pson;


}

__DEF_X2fsUtil_Template
typename __DEF_X2fsUtil::__SizeType  __DEF_X2fsUtil::writeToFile(const char* buf,__SizeType objsize, __SizeType nobj, int argc, const char* argv[],
		__SizeType foff)
{
	// DEPRECATED
//	return this->writeToFile(buf, objsize, nobj, this->getPathNode(argc, argv), foff);
	return 0;
}
// INCOMPLETE
//__DEF_X2fsUtil_Template
//__SizeType  __DEF_X2fsUtil::readFromFile(
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
__DEF_X2fsUtil_Template
typename __DEF_X2fsUtil::__SizeType  __DEF_X2fsUtil::writeToFile(const char* buf,
		__SizeType objsize, __SizeType nobj, FileNode* fnode, __SizeType foff)
{
////	printf("in write to file\n");
////	printf("fnode is %x(relatively)\n",(__SizeType)fnode - (__SizeType)this->dirbuf);
//	if(fnode || !This::isFile(fnode))
//	{
//		__FileDescriptor &fd=fnode->getData();
////		const __SizeType myobjsize=1;
//		const __SizeType mynobj = nobj * objsize;
//		const __SizeType mynsec = nobj;
//
////		__SizeType newsecLen = foff;
//		__SizeType newlen=foff;
//
////		printf("before ilink got\n");
//		__SizeType ilink=fd.getSectionListIndex();;
////		printf("section list inode is %d,data[0] is %d,%d\n",ilink,this->linkarr[ilink].getStart(),this->linkarr[ilink].getLimit());
//
//		__SizeType thisSectionFileLen = this->linkarr[ilink].getLimit() * CONST_SECSIZE - foff ;
////		__SizeType thisSectionLen = this->linkarr[ilink].getLimit()  - foff ;
//
//		__SizeType thisObjLeft = mynobj;
//		__SizeType thisSecLeft = nobj;
//
//		const char *thisBuf=buf;
//		while(true)
//		{
////			printf("seek at %d,leftSize is %d,this section file len is %d,ilink now is %d\n",thisSectionStart,thisObjLeft,thisSectionFileLen,
////					ilink);
//			// TODO
////			fseek(this->fpimg,thisSectionStart,SEEK_SET);
//
//
//			if(thisSectionFileLen > thisObjLeft)
//			{
//				thisSectionFileLen = thisObjLeft;
//			}
//
//			// TODO
//			__SizeType written =
//					0;
////					fwrite(thisBuf,myobjsize,thisSectionFileLen,this->fpimg);
//
////			HostEnv::writeSectors(HostEnv::CUR_SEG, (const u8_t*)thisBuf, driver,
////					metainfo.lbaStartLow + thisSec, mynsec, metainfo.lbaStartHigh);
//
//			thisBuf += written;
//			thisObjLeft -= written;
//			newlen += written;
//			ilink++;
//			if(thisObjLeft>0)
//			{
//				if(ilink == this->linkarr.size() || this->linkarr[ilink].getLimit()==0)//require for more space
//				{
//					LinkedList<__FsEnvLinearSourceDescriptor,PartialMallocToSimple> list(freemm.getMemoryManager());
////					__SizeType extraSec=(thisObjLeft / CONST_SECSIZE) ;
////					if(thisObjLeft % CONST_SECSIZE> 0)
////					{
////						extraSec++;
////					}
//					__SizeType extraSec = thisSecLeft;
//
////					printf("new linked source,size is %d,extraSec is %d\n",thisObjLeft,extraSec);
//					bool flagnewList=this->freemm.mnewLinked(extraSec, list,0);
//					if(flagnewList)
//					{
//						// TODO nlist
////						__SizeType nlist=list.getSize();
//
////						printf("got list size is %d\n",nlist);
////						printf("ask link for extend : start=%d,size=%d,extsize=%d\n",fd.getSectionList(),ilink - fd.getSectionList() + 1,nlist);
//
//						// TODO 下面这个系统调用
//						__SizeType newilink=
////						(__SizeType)linkmm.extend(fd.getSectionListIndex(), ilink - fd.getSectionListIndex() + 1,nlist,
////								nullptr, false);
//								0;
//						if(newilink==0)
//						{
//							this->seterrno(This::ERROR_LINKINFO_SPACE_NOT_ENOUGH);
////							return (mynobj - thisObjLeft)/objsize;
//							return mynsec - thisSecLeft;
//						}
////						printf("new ilink is %d\n",newilink);
//						if(newilink != fd.getSectionListIndex())//不相等，需要移动
//						{
//							HostEnv::memcpy(reinterpret_cast<char*>(linkarr + newilink),
//									   reinterpret_cast<char*>( (linkarr + fd.getSectionListIndex())),ilink - fd.getSectionListIndex() );
//							HostEnv::memset(reinterpret_cast<char*>((linkarr + fd.getSectionListIndex())),0,ilink - fd.getSectionListIndex());
//						}
//						__FsEnvListNode_LinearSourceDescriptor *pnewnode=list.getHead();
//						ilink = newilink + ilink - fd.getSectionListIndex();
//						while(pnewnode) //copy from list to that memory
//						{
////							printf("copy extra ilink to the space,new(at %d) is %d,%d\n",ilink,pnewnode->getData().getStart(),pnewnode->getData().getLimit());
////							this->linkarr[ilink] = pnewnode->getData();
//							pnewnode = pnewnode->getNext();
//							ilink++ ;
//						}
//						ilink = newilink + ilink - fd.getSectionListIndex() - 1; //reset to the right position
////						printf("reset ilink is %d\n",ilink);
//						fd.setSectionListIndex(newilink); // change fd to the new pointer
//					}else{
//						this->seterrno(This::ERROR_FILEALLOCSPACE);
//						if(fd.getFileLen()<newlen)
//						{
//							fd.setFileLen(newlen);
//						}
////						return (mynobj - thisObjLeft)/objsize;
//						return mynsec - thisSecLeft;
//					}
//				}
//				//here,we continue like nothing happened
////				thisSectionFileLen = this->linkarr[ilink].getLimit() * CONST_SECSIZE ;
////				thisSectionLen = linkarr[ilink].getLimit();
//
//
////				thisSectionStart = this->linkarr[ilink].getStart() * This::SecSize;
//			}else{
//				if(fd.getFileLen()<newlen)
//					{
//						fd.setFileLen(newlen);
//					}
////				return (mynobj - thisObjLeft)/objsize;
//				return mynsec - thisSecLeft;
//			}
//		}//while
//	}//if
	return 0;
}
__DEF_X2fsUtil_Template
typename __DEF_X2fsUtil::__SizeType __DEF_X2fsUtil::locateILink(__SizeType startILink,__SizeType secPos,__SizeType & retOff)
{
	for(; linkarr[startILink].getLimit()!=0 &&
					secPos >= linkarr[startILink].getLimit();++startILink)
							secPos -= linkarr[startILink].getLimit();
	retOff = secPos;
	return startILink;

}
__DEF_X2fsUtil_Template
typename __DEF_X2fsUtil::__SizeType __DEF_X2fsUtil::writeToILink(__SizeType ilink,const char *src,__SizeType secPos,__SizeType secLen)
{
	if(ilink==0 || ilink >= linkarr.size())
		return 0;
	if(secLen==0)
		secLen = linkarr[ilink].getLimit() - secPos;
	else if( linkarr[ilink].getLimit()<secLen || linkarr[ilink].getLimit()-secLen<secPos )
		return 0;

	// UNTESTED lba计算可能溢出到高部分
	HostEnv::writeSectors(HostEnv::CUR_SEG,
					 reinterpret_cast<const u8_t*>(src), driver,metainfo.lbaStartLow + linkarr[ilink].getStart()+secPos, secLen, metainfo.lbaStartHigh);
	return secLen;
}

__DEF_X2fsUtil_Template
bool __DEF_X2fsUtil::extendFileSecNum(FileNode * fileNode,__SizeType extraSec,bool addFileLength)
{
	if(fileNode==nullptr || extraSec==0)return false;

	LinkedList<__LinearSourceDescriptor,MallocToSimple> list(freemm.getMemoryManager());
	bool flagnewList = freemm.mnewLinked(extraSec, list, 0);
	__FileDescriptor& fd=fileNode->getData();
	if(flagnewList)
	{
		__SizeType nlist=list.getSize();
		__SizeType iendLink = getEndILink(fileNode);
		__SizeType oriStartLink = fd.getSectionListIndex();
		__SizeType oriSize = iendLink - oriStartLink+1;
		if(iendLink==0)return false;

		__SizeType newilink = reinterpret_cast<__SizeType>(linkmm.extend(oriStartLink, oriSize ,
				true,nlist,nullptr, false));
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
		__ListNode_LinearSourceDescriptor *p=list.getHead();
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
__DEF_X2fsUtil_Template
typename __DEF_X2fsUtil::__SizeType __DEF_X2fsUtil::getEndILink(FileNode *fileNode)const
{
	if(fileNode==nullptr)return 0;
	__SizeType i=fileNode->getData().getSectionListIndex();
	for( ; i<linkarr.size() && linkarr[i].getLimit()!=0;++i)
		;//空语句
	if(i==linkarr.size())return 0;
	return i;

}
__DEF_X2fsUtil_Template
typename __DEF_X2fsUtil::__SizeType __DEF_X2fsUtil::_writeToFile(const char *buf,
		__SizeType nsec,FileNode *fnode,__SizeType secPos,bool updateFileLen)
{
	if(nsec==0 || fnode==nullptr)return 0;

	__FileDescriptor &fd=fnode->getData();
	if(fd.getType() != __FileDescriptor::TYPE_FILE)return 0;
	__SizeType	ilink = fd.getSectionListIndex();

	__SizeType retOff=0;
	__SizeType ilinkPos = locateILink(ilink, secPos, retOff);
	// TODO 验证下面的计算法则
	__SizeType extraSec = 0;
	if(retOff + nsec > linkarr[ilinkPos].getLimit()) //需要额外的空间
	{
		extraSec = retOff +nsec - linkarr[ilinkPos].getLimit();
		if(!extendFileSecNum(fnode, extraSec, updateFileLen)) // 空间不足以分配
			return 0;
		ilinkPos = locateILink(ilink = fd.getSectionListIndex(), secPos, retOff);//更新数据状态
	}

	__SizeType thisOff = retOff;
	__SizeType thisLen = (nsec > (linkarr[ilinkPos].getLimit()  - thisOff)? (linkarr[ilinkPos].getLimit()  - thisOff): nsec );
	const u8_t *thisBuf= reinterpret_cast<const u8_t*>(buf);
	__SizeType i=ilinkPos;
	__SizeType thisLeftSec = nsec;
	while(true)
	{
		HostEnv::writeSectors(HostEnv::CUR_SEG, thisBuf, driver, metainfo.lbaStartLow + linkarr[i].getStart() + thisOff,
						thisLen, metainfo.lbaStartHigh);
		++i;
		if(i==linkarr.size() || linkarr[i].getLimit()==0)break;
		thisLeftSec-= thisLen;
		if(nsec==0)break;
		thisBuf += thisLen * CONST_SECSIZE;
		thisOff = 0;
		thisLen = (thisLeftSec > linkarr[i].getLimit() ? linkarr[i].getLimit()  : thisLeftSec );
	}

	return nsec;

}
__DEF_X2fsUtil_Template
typename __DEF_X2fsUtil::__SizeType __DEF_X2fsUtil::_readFromFile(char *buf, __SizeType nsec,FileNode *fnode,__SizeType secPos)
{
	if(nsec==0 || fnode==nullptr)return 0;

	__FileDescriptor &fd=fnode->getData();
	if(fd.getType() != __FileDescriptor::TYPE_FILE)return 0;
	__SizeType	ilink = fd.getSectionListIndex();

	__SizeType retOff=0;
	__SizeType ilinkPos = locateILink(ilink, secPos, retOff);

	if(linkarr[ilinkPos].getLimit() == 0) //不可能定位
		return 0;

	__SizeType thisOff = retOff;
	__SizeType thisLen = (nsec > (linkarr[ilinkPos].getLimit()  - thisOff)? (linkarr[ilinkPos].getLimit()  - thisOff): nsec );
	u8_t *thisBuf=reinterpret_cast<u8_t*>(buf);
	__SizeType i=ilinkPos;
	__SizeType thisLeftSec = nsec;
	while(true)
	{
		HostEnv::readSectors(HostEnv::CUR_SEG, thisBuf, driver, metainfo.lbaStartLow + linkarr[i].getStart() + thisOff,
						thisLen, metainfo.lbaStartHigh);

		thisLeftSec-= thisLen;
		++i;
		if(i==linkarr.size() || linkarr[i].getLimit()==0)break;

		if(nsec==0)break;
		thisBuf += thisLen * CONST_SECSIZE;
		thisOff = 0;
		thisLen = (thisLeftSec > linkarr[i].getLimit() ? linkarr[i].getLimit()  : thisLeftSec );
	}

	return nsec - thisLeftSec;
}

__DEF_X2fsUtil_Template
typename __DEF_X2fsUtil::__SizeType __DEF_X2fsUtil::_randomWriteFile(char *buf,
		__SizeType nbyte,FileNode *fnode,__SizeType byteStart)
{
	if(fnode==nullptr || fnode->getData().getType()!=__FileDescriptor::TYPE_FILE
			|| buf==nullptr || nbyte==0)return 0;
	__SizeType bufSize,startOff,endOff;
	bufSize = calculateRandomBufferSize(byteStart, nbyte, &startOff, &endOff, CONST_SECSIZE);
	ManagedObject<u8_t*> mbuf;

	__FileDescriptor& fd=fnode->getData();

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

			if( 1!= HostEnv::readSectors(HostEnv::CUR_SEG,
					oneUnitBuf, driver, metainfo.lbaStartLow + linkarr[ilink].getStart() + retOff,
					1, metainfo.lbaStartHigh))
				return 0;//失败
			HostEnv::memcpy(reinterpret_cast<char*>(buf), reinterpret_cast<const char*>(oneUnitBuf), startOff);//复制前面部分
		}
	}
	// endOff读补齐, 大部分代码同上，但有些许不同
	if(endOff!=0)
	{
		u8_t *oneUnitBuf=nullptr;
		if(nsec==1)// nsec==1 时，扇区已经读入了,直接取用即可
			oneUnitBuf=mbuf.getOnlyBuffer(CONST_SECSIZE);
		else
		{
			__SizeType retOff;
			__SizeType ilink = locateILink(fd.getSectionListIndex(), startSec + nsec - 1, retOff);
			if(linkarr[ilink].getLimit()!=0)//文件足够长
			{

				u8_t *oneUnitBuf=mbuf.getOnlyBuffer(CONST_SECSIZE);
				if( 1!=HostEnv::readSectors(HostEnv::CUR_SEG,
						oneUnitBuf, driver, metainfo.lbaStartLow + linkarr[ilink].getStart()+retOff,
						1, metainfo.lbaStartHigh))
					return 0; // 失败
			}
		}

		// 如果oneUnitBuf不为空，说明已经读入了，需要复制到原来的区域
		if(oneUnitBuf!=nullptr)
		{
			__SizeType offFromBegin = CONST_SECSIZE - endOff;
			HostEnv::memcpy(reinterpret_cast<char*>(buf) + (startSec + nsec - 1)*CONST_SECSIZE + offFromBegin,
					reinterpret_cast<const char*>(oneUnitBuf+offFromBegin), endOff);//定位到最后一个扇区，然后补偿写数据
		}
	}

	// 现在所有的扇区已经补齐了，数据不会覆盖，进行完整的扇区写
	__SizeType written=_writeToFile(buf, nsec, fnode, startSec,false);
	__SizeType realWrittenByte = (
						written==nsec?
								nbyte : //没有写错误
								written*CONST_SECSIZE - startOff);//至少有一个扇区没有写，则已经写的减去偏移部分

	// UNTESTED
	// 更新文件长度
	__SizeType updateLen = realWrittenByte + byteStart;//最后一个不可到达的字节就是长度
	if(updateLen > fd.getFileLen())
		fd.setFileLen(updateLen);
	return (realWrittenByte);
}

__DEF_X2fsUtil_Template
typename __DEF_X2fsUtil::__SizeType __DEF_X2fsUtil::_randomReadFile(char *buf,
		__SizeType nbyte,FileNode *fnode,__SizeType byteStart)
{
	if(fnode==nullptr || fnode->getData().getType()!=__FileDescriptor::TYPE_FILE
			|| buf==nullptr || nbyte==0)return 0;
	__SizeType bufSize,startOff,endOff;
	bufSize = calculateRandomBufferSize(byteStart, nbyte, &startOff, &endOff, CONST_SECSIZE);

	const __SizeType nsec = bufSize/CONST_SECSIZE;
	const __SizeType startSec = byteStart/CONST_SECSIZE;

	__SizeType readin=_readFromFile(buf, nsec, fnode, startSec);
	if(readin==0)//没有成功
		return 0;
	else if(readin==nsec) //没有读错误
		return nbyte;
	else //至少有一个扇区没有读
		return readin*CONST_SECSIZE - startOff; //已读减去偏移部分
}

__DEF_X2fsUtil_Template
bool __DEF_X2fsUtil::truncateFile(FileNode *fnode,__SizeType newlen)
{
	if(fnode == nullptr || newlen < CONST_SECSIZE*2 )return false;//文件至少占用两个扇区
	__FileDescriptor& fd=fnode->getData();
	__SizeType flen = fd.getFileLen();
	if(flen==newlen)return true;

	__SizeType secPos = (newlen/CONST_SECSIZE) + (newlen%CONST_SECSIZE==0?0:1);//需要定位的扇区
	__SizeType retOff;
	__SizeType ilink = locateILink(fd.getSectionListIndex(), secPos, retOff);

	if(linkarr[ilink].getLimit()==0)//超过实际占用的扇区长度，需要分配retOff个扇区
	{
		if(retOff>0) //确实需要多余的空间
		{
			if(!extendFileSecNum(fnode, retOff, false))//不成功
				return false;
		}

	}else{ //需要减少扇区数目
		//将该ilink后面的所有扇区回收
		__SizeType ilinkIt=ilink+1;//迭代
		for(;linkarr[ilinkIt].getLimit()!=0;++ilinkIt)
			freemm.mdelete(reinterpret_cast<u8_t*>(linkarr[ilinkIt].getStart()), linkarr[ilinkIt].getLimit());


		__SizeType ilinkStart= ilink + 1;
		__SizeType ilinkEnd = ilinkIt; //指向最后一个
		if(retOff == 0) // 需要连该ilink一起回收
		{
			ilinkStart = ilink ;
			freemm.mdelete(reinterpret_cast<u8_t*>(linkarr[ilink].getStart()), linkarr[ilink].getLimit());
		}

		// 回收link区
		linkmm.mdelete(reinterpret_cast<u8_t*>(ilinkStart+1), ilinkEnd - ilinkStart);//保留一个作为(0,0)区域
		linkarr[ilinkStart].setStart(0);
		linkarr[ilinkStart].setLimit(0);
	}

	fd.setFileLen(newlen);
	return true;


}

//
//template<class __FsEnvInterface, typename __SizeType>
//__SizeType __DEF_X2fsUtil::randomWriteFile(const char* buf, __SizeType nbyte,
//		FileNode* fnode, __SizeType byteStart)
//{
//	if(buf==nullptr || fnode==nullptr || nbyte==0)return 0;
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
//	ManagedObject<char*,__FsEnvInterface,__SizeType> mbuf(env);//用于自动管理资源
//
//
//
//
//
//	if(startOff!=0) //开始区间需要先读入再写回
//	{
//		if(nsecs==1)//只有一个扇区
//		{
//			randomWriteFileOneUnit(pbase, fnode, startSec, startOff, CONST_SECSIZE - endOff, nullptr);
//			return;
//		}else{ //多个扇区
//			randomWriteFileOneUnit(pbase, fnode, startSec, startOff, CONST_SECSIZE, nullptr);
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
//		if(oneUnitBuf== nullptr)return 0;
//		||
//				1 != _readFromFile(oneUnitBuf,1,fnode,startSec + nsecs -1))
//		++startSec;
//		--nsecs;
//		bufSize-=CONST_SECSIZE;
//	}
//	if(nsecs==0)return nbyte;
//
//	__SizeType realWrite = HostEnv::writeSectors(HostEnv::CUR_SEG,
//			(u8_t*)pbase, driver, metainfo.lbaStartLow + startSec,nsecs, metainfo.lbaStartHigh) ;
//
//	if(realWrite == nsecs)
//		return nbyte;
//	else  //差至少1个扇区没有写
//		return (bufSize/CONST_SECSIZE - nsecs+realWrite)*CONST_SECSIZE
//				- startOff; //原来总的扇区数目，减去未写的扇区数目，减去偏移
//}
//
//template<class __FsEnvInterface, typename __SizeType>
//__SizeType __DEF_X2fsUtil::randomReadFile(char* buf, __SizeType nbyte, FileNode* fnode,
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
//		myBuf=(char*)HostEnv::malloc(bufSize);
//		if(myBuf==nullptr)return 0;
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
//		HostEnv::free((u8_t*)myBuf);
//	}
//
//	return readSec*CONST_SECSIZE - startOff - (CONST_SECSIZE -endOff);
//}


//
//__DEF_X2fsUtil_Template
//__SizeType  __DEF_X2fsUtil::randomReadSector(char *buf,__SizeType nbyte,
//		__SizeType bytePos)
//		{
//			__SizeType bufSize,startOff,endOff;
//			bufSize = calculateRandomBufferSize(bytePos, nbyte, &startOff, &endOff, CONST_SECSIZE);
//			if(bufSize==0)return 0;
//
//			char *myBuf=buf;
//			if(startOff!=0 || endOff!=0)//需要额外的空间
//			{
//				myBuf=(char*)HostEnv::malloc(bufSize);
//				if(myBuf==nullptr)return 0;//内存不足
//			}
//			__SizeType needToRead = bufSize / CONST_SECSIZE;
//
//			__SizeType realRead = HostEnv::readSectors(HostEnv::CUR_SEG,
//					(u8_t*)myBuf, driver, metainfo.lbaStartLow + bytePos/CONST_SECSIZE, needToRead, metainfo.lbaStartHigh) ;
//			if(realRead==0) //读取错误
//			{
//				if(myBuf!=buf)HostEnv::free((u8_t*)myBuf);
//				return 0;
//			}
//
//
//			if(myBuf!=buf)//复制过去
//			{
//				for(__SizeType i=startOff; i + endOff!=bufSize ;++i)//按字节复制
//					buf[i-startOff]=myBuf[i];
//				HostEnv::free((u8_t*)myBuf);
//			}
//			if(realRead == needToRead)
//				return nbyte;
//			else  //差至少1个扇区没有读
//				return realRead*CONST_SECSIZE - startOff;
//		}
//__DEF_X2fsUtil_Template
//__SizeType  __DEF_X2fsUtil::randomWriteSector(const char *buf,__SizeType nbyte,
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
//					if(!randomWriteOneUnit(pbase, startSec,startOff,CONST_SECSIZE,nullptr))
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
//							0,CONST_SECSIZE - endOff, nullptr));
//					++startSec;
//					--nsecs;
//					bufSize-=CONST_SECSIZE;
//				}
//				if(nsecs==0)return nbyte;
//
//				__SizeType realWrite = HostEnv::writeSectors(HostEnv::CUR_SEG,
//						(u8_t*)pbase, driver, metainfo.lbaStartLow + startSec,nsecs, metainfo.lbaStartHigh) ;
//
//				if(realWrite == nsecs)
//					return nbyte;
//				else  //差至少1个扇区没有写
//					return (bufSize/CONST_SECSIZE - nsecs+realWrite)*CONST_SECSIZE
//							- startOff; //原来总的扇区数目，减去未写的扇区数目，减去偏移
//		}

//__DEF_X2fsUtil_Template
//bool  __DEF_X2fsUtil::randomWriteOneUnit(const char *buf,__SizeType secPos,
//		__SizeType byteStart,
//		__SizeType byteEnd,
//		char *optBuffer)
//{
//		if(buf==nullptr || byteStart>=byteEnd || byteEnd > CONST_SECSIZE )return false;
//		if(byteEnd - byteStart == CONST_SECSIZE)//可以直接写入
//		{
//			return 1 == HostEnv::writeSectors(HostEnv::CUR_SEG,
//				(const u8_t*)buf, driver, metainfo.lbaStartLow + secPos, 1, metainfo.lbaStartHigh) ;
//		}
//		// 需要先读入部分，再完整写入
//		char *oneUnitBuffer=(optBuffer==nullptr? (char*)HostEnv::malloc(CONST_SECSIZE):optBuffer);
//		if(oneUnitBuffer==nullptr)return false;//程序空间不足
//
//
//		if( 1 != HostEnv::readSectors(HostEnv::CUR_SEG,
//				(u8_t*)oneUnitBuffer, driver, metainfo.lbaStartLow + secPos, 1, metainfo.lbaStartHigh)  )//没有成功
//			goto ERROR;
//
//		// EFF 按字节复制，低效
//		for(__SizeType i=byteStart;i!=byteEnd;++i) //将原来的数据复制到这个扇区，然后写回
//				oneUnitBuffer[i]=buf[i-byteStart];
//		if( 1!=HostEnv::writeSectors(HostEnv::CUR_SEG,
//					(u8_t*)oneUnitBuffer, driver, metainfo.lbaStartLow+secPos, 1, metainfo.lbaStartHigh))
//			goto ERROR;
//
//		if(oneUnitBuffer!=optBuffer)HostEnv::free((u8_t*)oneUnitBuffer);
//
//		return true;
//		ERROR:
//			if(oneUnitBuffer!=optBuffer)HostEnv::free((u8_t*)oneUnitBuffer);
//				return false;
//}
//__DEF_X2fsUtil_Template
//bool  __DEF_X2fsUtil::randomReadOneUnit(char *buf,__SizeType secPos,__SizeType byteStart,
//		__SizeType byteEnd,char *optBuffer)
//{
//	if(buf==nullptr || byteStart>=byteEnd || byteEnd > CONST_SECSIZE )return false;
//		if(byteEnd - byteStart == CONST_SECSIZE)//可以直接写入
//		{
//			return 1 == HostEnv::readSectors(HostEnv::CUR_SEG,
//				(const u8_t*)buf, driver, metainfo.lbaStartLow + secPos, 1, metainfo.lbaStartHigh) ;
//		}
//		// 需要先读入部分，再完整写入
//		char *oneUnitBuffer=(optBuffer==nullptr? (char*)HostEnv::malloc(CONST_SECSIZE):optBuffer);
//		if(oneUnitBuffer==nullptr)return false;//程序空间不足
//
//
//		if( 1 != HostEnv::readSectors(HostEnv::CUR_SEG,
//				(u8_t*)oneUnitBuffer, driver, metainfo.lbaStartLow + secPos, 1, metainfo.lbaStartHigh)  )//没有成功
//			goto ERROR;
//
//		// EFF 按字节复制，低效
//		for(__SizeType i=byteStart;i!=byteEnd;++i) //将原来的数据复制到这个扇区，然后写回
//			buf[i-byteStart]=oneUnitBuffer[i];
//
//		if(oneUnitBuffer!=optBuffer)HostEnv::free((u8_t*)oneUnitBuffer);//释放空间
//
//		return true;
//		ERROR:
//			if(oneUnitBuffer!=optBuffer)HostEnv::free((u8_t*)oneUnitBuffer);
//				return false;
//}

//__DEF_X2fsUtil_Template
//bool  __DEF_X2fsUtil::randomWriteFileOneUnit(const char *buf,
//			FileNode *fnode,
//			__SizeType secPos,
//			__SizeType byteStart,
//			__SizeType byteEnd,char *optBuffer)
//{
//
//		if(buf==nullptr||fnode==nullptr||byteStart>=byteEnd || byteEnd>=CONST_SECSIZE)return false;
//		ManagedObject<char*,__FsEnvInterface,__SizeType> mbuf(env);//自动管理资源
//
//		char *oneUnitBuf=(optBuffer==nullptr?mbuf.getOnlyBuffer(CONST_SECSIZE):
//				optBuffer);
//
//		if(oneUnitBuf==nullptr)return 0;//空间不足
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

//
//__DEF_X2fsUtil_Template
//__SizeType  __DEF_X2fsUtil::readFromFile(char* buf, __SizeType objsize, __SizeType nobj,FileNode* fnode, __SizeType foff)
//{
////	printf("test getNew at readFromFile \n");
////	this->linkmm.getMemoryManager()->getNew();
////	printf("test after getNew\n");
//	if(fnode || !This::isFile(fnode))
//	{
//		__FileDescriptor &fd=fnode->getData();
////		__SizeType requestLen = nobj * objsize + foff;
////		const __SizeType myobjsize=1;
//		const __SizeType mynobj = nobj * objsize;
//		__SizeType ilink=fd.getSectionListIndex();
//
//		__SizeType thisSectionFileLen;
////		__SizeType thisSectionStart;
//		__SizeType thisObjLeft = mynobj;
//		char *thisBuf=buf;
//		while(thisObjLeft > 0 && ilink <this->linkarr.size() && this->linkarr[ilink].getLimit()!=0)
//		{
//			thisSectionFileLen = this->linkarr[ilink].getLimit() * This::SecSize ;
////			thisSectionStart = this->linkarr[ilink].getStart() * This::SecSize;
//
//			// TODO 下面这行
////			fseek(this->fpimg,thisSectionStart,SEEK_SET);
//
//
//			if(thisSectionFileLen > thisObjLeft)
//			{
//				thisSectionFileLen = thisObjLeft;
//			}
//			// TODO 下面这块
//			__SizeType written =
//					0;
////					fread(thisBuf,myobjsize,thisSectionFileLen,this->fpimg);
//
//			thisBuf += written;
//			thisObjLeft -= written;
//			ilink++;
//		}
//		return (mynobj - thisObjLeft)/objsize;
//	}
//	return 0;
//}

//X2fsUtil::FileNode* X2fsUtil::locatePath(FileNode* base,int argc, const char* argv[], int& errorLevel)
//{
//		return ((const X2fsUtil *)this)->locatePath(base, argc,argv,errorLevel);
//}
//X2fsUtil::FileNode* X2fsUtil::locatePath(FileNode* base, const char* name)
//{
//	return ((const X2fsUtil *)this)->locatePath(base,name);


__DEF_X2fsUtil_Template
void  __DEF_X2fsUtil::mkfs(u8_t driver,const __X2fsMetaInfo &metainfo)
{
//	using __TargetX2fsUtil = X2fsUtil<__FsEnvInterface,__TargetSizeType,__TargetAlignment>;
//	using __TargetX2fsMetaInfo = X2fsMetaInfo<__TargetSizeType>;
//	using __TargetFileDescriptor = typename __TargetX2fsUtil::__FileDescriptor;
//	using __TargetTreeNode_FileDescriptor = TreeNode<__TargetFileDescriptor,__TargetAlignment>;
//	using __TargetFileNode = typename __TargetX2fsUtil::FileNode;
//	using __TargetSimpleMemoryNode = typename __TargetX2fsUtil::SimpleMemoryNode;
//	using __TargetSimpleMemoryManager = SimpleMemoryManager<__TargetTreeNode_FileDescriptor>;
//	using __TargetLinearSourceDescriptor=LinearSourceDescriptor<__TargetSizeType,__TargetAlignment>;


	//debug information
	HostEnv::printf_simple("sizeof(FileNode)=%d\n",sizeof(FileNode));


	HostEnv::printf_simple("sizeof(TreeNode_FileDescriptor)=%d\n",
			sizeof(__TreeNode_FileDescriptor));
	HostEnv::printf_simple("sizeof(SimpleMemoryNode)=%d\n",sizeof(SimpleMemoryNode));

	FileNode *p=reinterpret_cast<FileNode*>(sizeof(FileNode));
	__TreeNode_FileDescriptor *p2=
			reinterpret_cast<__TreeNode_FileDescriptor*>(p);
	SimpleMemoryNode *p3=reinterpret_cast<SimpleMemoryNode*>(p);

	HostEnv::printf_simple("difference is (pfullnode - ptreenode)=%d\n",(reinterpret_cast<char*>(p )- reinterpret_cast<char*>(p2)));
	HostEnv::printf_simple("pfullnode - psimple=%d(should be less than 0)\n",(reinterpret_cast<char*>(p) - reinterpret_cast<char*>(p3)));
	//******=========Test END============**********

	if(!__X2fsMetaInfo::checkMetainfo(metainfo))
	{
		HostEnv::printf_simple("error metainfo format\n");
		return;
	}


	u32_t allSecs=metainfo.metaSec;
	for(__SizeType i=0;i<metainfo.len;i++)
		allSecs+=metainfo.secnums[i];
	u32_t allocedSec=allSecs;//需要分配buffer的sec: meta 以及required
	char *base=static_cast<char*>(HostEnv::malloc(allocedSec*CONST_SECSIZE)); //分配空间
	allSecs+=metainfo.reservedSec;
	for(__SizeType i=0;i<metainfo.optionalLen;++i)
		allSecs+=metainfo.optional[i];
	//==================================init metainfo
	/**
	 *  将metainfo信息序列化到该区域
	 */
	__SerializerPtr ptrMetaInfo{base+0} ;
	ptrMetaInfo << metainfo;


	//==================================init name section
	/**
	 * clear filenames in fileNameSection
	 *         but keep the first two,because when returned nullptr,it will be treated as failure
	 */
	u32_t filenameSecOff = metainfo.metaSec * CONST_SECSIZE; //base + metaSec is filename
	u32_t filenameLen = metainfo.secnums[INDEX_NAME] * CONST_SECSIZE;
	HostEnv::memset(base+filenameSecOff,0,filenameLen);
	char *pbase=base+filenameSecOff;
	pbase[0]=1;
	pbase[1]=' ';//根目录的名称是''


	//===================================init dir section
	u32_t dirsectionOff = filenameSecOff + filenameLen;
	u32_t dirsectionLen = metainfo.secnums[INDEX_DIR] * CONST_SECSIZE;
	//清空该区域
	HostEnv::memset(base+dirsectionOff,0,dirsectionLen);//全部设置为0

	//序列化数组管理器
//	SimpleMemoryManager<__TreeNode_FileDescriptor>
//		smm(base+dirsectionOff,dirsectionLen,true);

	ManagedObject<char*> mdirBuf;
	char *simpleBuf=mdirBuf.getOnlyBuffer(dirsectionLen);

	size_t serialLen  = __FsEnv::template sizeofHostType<size_t>();
	size_t dirMemSerialLen = __SimpleAssociated<FileNode>::getSerializitionSize<__FsEnv>();
	__SizeType simpleNum = (dirsectionLen - serialLen - dirMemSerialLen)/__SimpleAssociated<FileNode>::getEachSize()-1;
	__SizeType fileNodeOffToSimpleBuf = sizeof(FileNode);
	__SizeType smmNodeOffToSimpleBuf = fileNodeOffToSimpleBuf + simpleNum * sizeof(FileNode);
//	__SizeType smmFileNodeDiff = smmNodeOffToSimpleBuf - fileNodeOffToSimpleBuf;
	int usedList[]={0,1,2};// 0 保留  ; 1 root; 2 head; 1+2构成一棵树
	__SimpleAssociated<FileNode> dirMem{
		reinterpret_cast<__SizeType>(simpleBuf + fileNodeOffToSimpleBuf),//避免nullptr
				reinterpret_cast<__SizeType>(simpleBuf + smmNodeOffToSimpleBuf)
				,simpleNum,true,usedList,arrsizeof(usedList)};//初始化0,1,2
	FileNode *fileNode=reinterpret_cast<FileNode*>(simpleBuf + fileNodeOffToSimpleBuf);
	SimpleMemoryNode *smmNodes= reinterpret_cast<SimpleMemoryNode*>(simpleBuf + smmNodeOffToSimpleBuf);//定位到末尾
	std::cout << "diff="<<(reinterpret_cast<char*>(smmNodes) - reinterpret_cast<char*>(fileNode)) << std::endl;
	__SimpleAssociated<FileNode>::NodeType smmAllocedNode{true};
	for(int i:usedList)
		fileNode[i].initToNull();
	fileNode[1].setSon(&fileNode[2]);
	fileNode[2].setFather(&fileNode[1]); // 互相设置引用
	fileNode[2].setData(__FileDescriptor(
			__FileDescriptor::TYPE_DIR,
			0,0,0,
			0,0
	));
	// 开始序列化
	static ptrdiff_t localDiff=0;
	struct DirFsEnv:public __FsEnv{ //设置新的基地址
		AS_MACRO static ptrdiff_t ptrBase(){
				return localDiff;
		}
	};
	localDiff= reinterpret_cast<ptrdiff_t>(simpleBuf);// TARGET + NODE
	SerializerPtr<DirFsEnv> ptrDirFileNodes{base+dirsectionOff};
	ptrDirFileNodes	<< dirMem.getLen() //先长度，再其他，该长度用于决定后面分配的指针基地址
						<< dirMem;
	// DEBUGGING
	char *p0=reinterpret_cast<char*>(ptrDirFileNodes.getPtr());
	ptrDirFileNodes << fileNode[0] << fileNode[1] << fileNode[2];//序列化数组3个
	char spaces[sizeof(FileNode)*3];
	FileNode *fn=reinterpret_cast<FileNode*>(spaces);
	ptrDirFileNodes = p0;
	ptrDirFileNodes >> fn[0] >> fn[1] >>fn[2];
	ptrDirFileNodes += (simpleNum - 3) * (fileNode[0].getSerializitionSize<DirFsEnv>());
	char *p1=reinterpret_cast<char*>(ptrDirFileNodes.getPtr());
	std::cout << "p1 - p0 = "<< (p1 - p0 )<<std::endl;
	ptrDirFileNodes << smmAllocedNode << smmAllocedNode << smmAllocedNode; //连续写alloced=true的node


	//======================================init free space section
	u32_t freesectionOff = dirsectionOff + dirsectionLen;
	u32_t freesectionLen = metainfo.secnums[INDEX_FREE] * CONST_SECSIZE;
	LLSmm listnodesmm;
	FreeSpaceMM  freemm(listnodesmm,allSecs ,metainfo.wholeSecnums - allSecs);
	__SerializerPtr ptrfreemm(base + freesectionOff);
			ptrfreemm << freemm;//from start to the end

	//======================================init linked info section
	u32_t linksectionOff = freesectionOff + freesectionLen;
	u32_t linksectionLen = metainfo.secnums[INDEX_LINK] * CONST_SECSIZE;
	HostEnv::memset(base+linksectionOff,0,linksectionLen);//set all to 0
	// 初始化linkarr的前两项已经分配，这样避免返回0作为下标来标记失败状态, 这两项不会被使用
	__SerializerPtr ptrlinkmm{base + linksectionOff};
	HostEnv::Vector<__LinearSourceDescriptor> lvec;
	lvec.push_back(__LinearSourceDescriptor(0xaa55,1));
	lvec.push_back(__LinearSourceDescriptor(0xaa55,0));
	lvec.resize(linksectionLen/__LinearSourceDescriptor::getSerializitionSize<__FsEnv>() );
	ptrlinkmm << lvec; //0xaa55 is the verifying information,文件第一个扇区不用，所有的都是第一项不用


	//============================flush to storage
	HostEnv::writeSectors(HostEnv::CUR_SEG,
			reinterpret_cast<u8_t*>(base),driver,
			metainfo.lbaStartLow+metainfo.reservedSec,
			allocedSec, metainfo.lbaStartHigh);

	HostEnv::flushOutputs();
	HostEnv::free(base);
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

//===class ManagedObject
#define __DEF_Template_ManagedObject template <typename T>
#define __DEF_ManagedObject ManagedObject<T>

__DEF_Template_ManagedObject
__DEF_ManagedObject::ManagedObject():
buffer(nullptr)
{}

__DEF_Template_ManagedObject
__DEF_ManagedObject::~ManagedObject()
{
	if(buffer!=nullptr)
		HostEnv::free(reinterpret_cast<u8_t*>(buffer));
}
__DEF_Template_ManagedObject
void __DEF_ManagedObject::setBufferIfNone(T buffer)
{
	if(this->buffer==nullptr)
		this->buffer=buffer;
}
__DEF_Template_ManagedObject
T __DEF_ManagedObject::getOnlyBuffer()const
{
	return buffer;
}

__DEF_Template_ManagedObject
T __DEF_ManagedObject::getOnlyBuffer(__SizeType size)
{
	if(buffer==nullptr)
		buffer= static_cast<T>(HostEnv::malloc(size));
	return buffer;
}
__DEF_Template_ManagedObject
const T&    __DEF_ManagedObject::getOnlyBufferReference(__SizeType size)const
{
	if(buffer==nullptr)
		buffer=static_cast<T>(HostEnv::malloc(size));
	return buffer;
}

__DEF_Template_ManagedObject
bool __DEF_ManagedObject::operator==(const __ManagedObject &rhs) const {
    return       buffer == rhs.buffer;
}

__DEF_Template_ManagedObject
bool __DEF_ManagedObject::operator!=(const __ManagedObject &rhs) const {
    return !(rhs == *this);
}

#endif

