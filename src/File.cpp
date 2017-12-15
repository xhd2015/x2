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
#if defined(CODE64)
#endif



////===class __FileDescriptor
//#define __DEF_Template___FileDescriptor
//#define __DEF___FileDescriptor __FileDescriptor
//
//__DEF_Template___FileDescriptor
//template <class __FsEnvTransfer>
//	SerializerPtr<__FsEnvTransfer>& __DEF___FileDescriptor::serialize(SerializerPtr<__FsEnvTransfer> &ptr)const
//{
//	return ptr	<< type
//				<< sectionListIndex
//				<< fileLen
//				<< nameStart
//				<< createdTime
//			 	<< lastModefiedTime;
//}
//__DEF_Template___FileDescriptor
//template <class __FsEnvTransfer>
//	SerializerPtr<__FsEnvTransfer>& __DEF___FileDescriptor::deserialize(SerializerPtr<__FsEnvTransfer> &ptr)
//{
//	return ptr	>> type
//				>> sectionListIndex
//				>> fileLen
//				>> nameStart
//				>> createdTime
//				>> lastModefiedTime;
//}
//
//#undef __DEF_Template___FileDescriptor
//#undef __DEF___FileDescriptor



//==class X2fsMetaInfo
#define __DEF_Template_X2fsMetaInfo
#define __DEF_X2fsMetaInfo X2fsMetaInfo

//__DEF_Template_X2fsMetaInfo
//bool __DEF_X2fsMetaInfo::checkMetainfo(const X2fsMetaInfo& info)
//{
//	bool checkRes = (info.reservedSec == SECNUM_RESERVED_CONST) &&
//					(info.metaSec == SECNUM_META_CONST ) &&
//					(info.len == PARTS_REQUIRED) &&
//					(info.validFlag == VALID_FLAG);
//
//	return checkRes;
//}
//序列化接口
__DEF_Template_X2fsMetaInfo
template <class __FsEnvTransfer>
	SerializerPtr<__FsEnvTransfer>& __DEF_X2fsMetaInfo::serialize(SerializerPtr<__FsEnvTransfer> &ptr)const
{
	return ptr  <<basicSizeType
				<<reservedSec
				<<metaSec
				<< lbaBaseLow
				<< lbaBaseHigh
				<< wholeSecnums
				<< validFlag;
}

//序列化接口
__DEF_Template_X2fsMetaInfo
template <class __FsEnvTransfer>
	SerializerPtr<__FsEnvTransfer>& __DEF_X2fsMetaInfo::deserialize(SerializerPtr<__FsEnvTransfer> &ptr)
{
	return ptr			 >>basicSizeType
						   >>reservedSec
						   >>metaSec
						   >> lbaBaseLow
						   >> lbaBaseHigh
						   >> wholeSecnums
						   >> validFlag;
}
__DEF_Template_X2fsMetaInfo
template <class __FsEnvTransfer>
	constexpr size_t __DEF_X2fsMetaInfo::getSerializitionSize()
{
#define SZOF(prop) __FsEnvTransfer::template sizeofHostType<decltype(\
		reinterpret_cast<X2fsMetaInfo*>(nullptr)->prop)>()
	return SZOF(basicSizeType)+
			SZOF(reservedSec)+
			SZOF(metaSec)+
			SZOF(lbaBaseLow) +
			SZOF(lbaBaseHigh) +
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
			"lba_low:%d, ",lbaBaseLow);
	HostEnv::printf_simple(
			"lba_high:%d, "
			"total_secs:%d, "
			"valid_flag:%d "
			"}",lbaBaseHigh,wholeSecnums,static_cast<u32_t>(validFlag));
}

u8_t X2fsMetaInfo::getBasicSizeType() const {
	return basicSizeType;
}

void X2fsMetaInfo::setBasicSizeType(u8_t basicSizeType) {
	X2fsMetaInfo::basicSizeType = basicSizeType;
}

size_t X2fsMetaInfo::getReservedSec() const {
	return reservedSec;
}

void X2fsMetaInfo::setReservedSec(size_t reservedSec) {
	X2fsMetaInfo::reservedSec = reservedSec;
}

size_t X2fsMetaInfo::getMetaSec() const {
	return metaSec;
}

void X2fsMetaInfo::setMetaSec(size_t metaSec) {
	X2fsMetaInfo::metaSec = metaSec;
}

u32_t X2fsMetaInfo::getLbaBaseLow() const {
	return lbaBaseLow;
}

void X2fsMetaInfo::setLbaBaseLow(u32_t lbaBaseLow) {
	X2fsMetaInfo::lbaBaseLow = lbaBaseLow;
}

u32_t X2fsMetaInfo::getLbaBaseHigh() const {
	return lbaBaseHigh;
}

void X2fsMetaInfo::setLbaBaseHigh(u32_t lbaBaseHigh) {
	X2fsMetaInfo::lbaBaseHigh = lbaBaseHigh;
}

size_t X2fsMetaInfo::getWholeSecnums() const {
	return wholeSecnums;
}

void X2fsMetaInfo::setWholeSecnums(size_t wholeSecnums) {
	X2fsMetaInfo::wholeSecnums = wholeSecnums;
}


#undef __DEF_Template_X2fsMetaInfo
#undef __DEF_X2fsMetaInfo
//**************X2fsMetaInfo结束

#if defined(CODE64)

//typedef SimpleMemoryManager<TreeNode<__FileDescriptor<__SizeType><>> >::FileNode FileNode;

//===class X2fsUtil
// DEBUG
#define __DEF_X2fsUtil_Template template <class __FsEnv>
#define __DEF_X2fsUtil X2fsUtil<__FsEnv>
__DEF_X2fsUtil_Template
__DEF_X2fsUtil::X2fsUtil(u8_t driver,const __X2fsMetaInfo &metainfo):
			driver(driver),
			metainfo(metainfo),//直接复制
			freemm(std::shared_ptr<LLSmm>(new LLSmm()),
					metainfo.getFreeSpaceStart(),metainfo.getFreeSpaceLength()),
			fileTree(std::make_shared<FileTreeSMM>()),
			processErrno(This::ERROR_NOERR)
{
	__BaseDescriptor* rootDir = new __DirDescriptor("",0,0);//root目录
	fileTree.setHead(rootDir);
}
__DEF_X2fsUtil_Template
__DEF_X2fsUtil::X2fsUtil(u8_t driver,u32_t lbaBase,u32_t lbaHigh): // 必然是经过序列化得到
			driver(driver),
			metainfo(),//空
			freemm(std::make_shared<LLSmm>()),
			fileTree(std::make_shared<FileTreeSMM>()),
			processErrno(This::ERROR_NOERR)
	{
		// 读取首扇区的信息，然后确定metainfo的所在
		std::shared_ptr<u8_t[]> buffer{ new u8_t[CONST_SECSIZE], std::default_delete<u8_t[]>() };
		u16_t reservedNum;
		u16_t metaNum;
		readHeaderBufferInfo(*buffer, reservedNum, metaNum);

		auto bufferMeta = makeSharedArray<u8_t>(metaNum * CONST_SECSIZE);
		HostEnv::readSectors(HostEnv::CUR_SEG,
				*bufferMeta, driver, lbaBase, metaNum, lbaHigh);

		// 序列化读到这里
		SerializerPtr<__FsEnv> {*bufferMeta } >>  *this;

		if(!metainfo.isValid() || metainfo.getLbaBaseLow()!=lbaBase ||
				metainfo.getLbaBaseHigh()!=lbaHigh
		)
			HostEnv::systemAbort("incorrect metainfo", -2);
	}
__DEF_X2fsUtil_Template
__DEF_X2fsUtil::X2fsUtil(u8_t driver,SerializerPtr<__FsEnv>& ptr):
driver(driver),
metainfo(),//空
freemm(std::make_shared<LLSmm>()),
fileTree(std::make_shared<FileTreeSMM>()),
processErrno(This::ERROR_NOERR)
{
	this->deserialize(ptr);
}

__DEF_X2fsUtil_Template
__DEF_X2fsUtil::~X2fsUtil()
{
	this->flush();  //自行调用flush
}


__DEF_X2fsUtil_Template
void __DEF_X2fsUtil::flush() {

	auto  bufferMeta = makeSharedArray<u8_t>(CONST_SECSIZE * metainfo.getMetaSec());
	SerializerPtr<__FsEnv> {*bufferMeta } << *this;


	// 回写其他区信息到驱动器
	HostEnv::writeSectors(HostEnv::CUR_SEG, *bufferMeta, driver,
			metainfo.getLbaBaseLow() + metainfo.getReservedSec() ,
			metainfo.getMetaSec(), metainfo.getLbaBaseHigh());
}

__DEF_X2fsUtil_Template
void __DEF_X2fsUtil::printNode(const FileNode* p)const {
	if(p)
	{
		if(This::isDirectory(p))
		{
			HostEnv::cout << "Dir:" << p->getData()->getName() << HostEnv::endl;
		}else if(This::isFile(p))
		{
			HostEnv::cout << "File:" << p->getData()->getName()
							<< "Len = " << static_cast<__FileDescriptor*>(p->getData())->getFileLen()
							<< HostEnv::endl;
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
bool __DEF_X2fsUtil::create(FileNode *p,FileType type,const char *name,__SizeType secSpan,__TimeType ctime)
{
	if(!p)return false;

	if(this->locatePath(p, name)!=nullptr)//check existence of name
	{
		this->seterrno(This::ERROR_FILE_ALREDY_EXIST);
		return false;
	}
	__SizeType fsecStart=0;

	ResourceWatcher wc;
	// 创建一个节点，分配空间
	/**
	 * 如果任何一步出错，都应当把申请的空间换回去
	 */
	FileNode *fnode =fileTree.newOneNode();
	if(wc.fail(fnode!=nullptr)) // if fnode!=nullptr fails, that is, fnode==nullptr
	{
		this->seterrno(This::ERROR_NEW_NULL);
		return false;
	}
	wc.add(fnode);

	__BaseDescriptor *fd=nullptr;

	if(type==FileType::TYPE_FILE)
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
			return false;
		}
		fd =  wc.add(new __FileDescriptor(HostEnv::String(name),0,0,secSpan));
		if(wc.fail(fd!=nullptr))
			return false;
		__FileDescriptor *fileDesc=static_cast<__FileDescriptor*>(fd);
		fileDesc->addSpace({fsecStart,secSpan});

	}else if(type==FileType::TYPE_DIR){
		fd =  wc.add(new __DirDescriptor(HostEnv::String(name),0,0));
		if(wc.fail(fd!=nullptr))
			return false;
	}else{
		// unsupported now
		wc.fail();
		this->seterrno(ERROR_UNSUPORTED);
		return false;
	}
	fnode->setData(fd);
	this->insertNode(p, fnode);
	return true;
}
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
//		printf("type is %d \n",node->getData().getType());
		if(This::isDirectory(node)) // 对于目录，递归释放其每个子节点
		{
			FileNode * eachSon=static_cast<FileNode*>(node->getSon());
			while(eachSon)
			{
				this->freeNode(eachSon);
				eachSon = static_cast<FileNode*>(eachSon->getNext());
			}
		}else if(This::isFile(node)){ // 需要释放占用的所有空间
			__FileDescriptor *fd = static_cast<__FileDescriptor*>(node->getData());
			for(size_t i=0;i!=fd->getSpaceListSize();++i)
				freemm.mdelete(reinterpret_cast<void*>(fd->getSpace(i).getStart()),fd->getSpace(i).getLimit());
			node->setData(nullptr);
			delete fd;
		}
		//=== 回收掉fileTree中的Node，但是注意：如果该Node是个dir，由于之前的调用已经把所有子类free了，所以此处只需free该node本身即可。
		//here is a question : if one section is shared by many files,should we delete it too ? woo ~ ~
		//we'll use reference count to do that later.
		this->fileTree.freeOneNode(node);

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
	if(node && newname)
		node->getData()->setName(newname);
	return true;
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
// TODO 修正
__DEF_X2fsUtil_Template
void __DEF_X2fsUtil::dumpFileInfo(FileNode * fnode)
{
	const __FileDescriptor& fd=fnode->getData();
	__SizeType nlen;char *p;
	p=this->getFileNameCstr(fd, nlen);
	HostEnv::printf_simple("file name : ");
	HostEnv::printf_sn(p,nlen);
	HostEnv::printf_simple("\n");
//	HostEnv::printf_simple("linked section list start : %d\nsections are : \n",fd.getSectionListIndex());
//	__SizeType i=fd.getSectionListIndex();
//	while(i<this->linkarr.size() && this->linkarr[i].getLimit()!=0)
//	{
//		HostEnv::printf_simple("(%x,%x)   ",this->linkarr[i].getStart(),this->linkarr[i].getLimit());
//		i++;
//	}
	HostEnv::printf_simple("\n");
	HostEnv::printf_simple("type : %d\n",fd.getType());
//	HostEnv::printf_simple("length : %d \n",fd.getFileLen());
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
}

__DEF_X2fsUtil_Template
bool __DEF_X2fsUtil::hasFilename(int argc,const char *argv[],const char *name)const
{
	return this->hasFilename(this->getPathNode(argc, argv), name);
}

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
			bool flag=this->createFile(p, argv[argc-1], secSpan);
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
	FileNode *pfn=this->fileTree.getHead();

	HostEnv::printf_simple("/:\n");
	pfn=pfn->getSon();
	while(pfn)
	{
		HostEnv::cout << "\t" << pfn->getData()->getName();
		if(This::isFile(pfn))
		{
			__FileDescriptor *fd = static_cast<__FileDescriptor*>(pfn->getData());
			HostEnv::cout << "  " << fd->getFileLen();
		}
		pfn=pfn->getNext();
	}
}

__DEF_X2fsUtil_Template
void __DEF_X2fsUtil::listNode(const FileNode* p)const
{
//	std::cout << "in listNode"<<std::endl;
	const FileNode *pfn=p;

	pfn=pfn->getSon();
	while(pfn)
	{
		HostEnv::cout << "\t" << pfn->getData()->getName();
		if(This::isFile(pfn))
		{
			__FileDescriptor *fd=static_cast<__FileDescriptor*>(pfn->getData());
			HostEnv::cout << "  " << fd->getFileLen();
		}
		pfn=pfn->getNext();
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
	FileNode *p= base->getSon();
	while(p)
	{
		if( p->getData()->getName().compare(name)==0)break;
		p = p->getNext();
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
__DEF_X2fsUtil_Template
typename __DEF_X2fsUtil::__SizeType __DEF_X2fsUtil::locateILink(__FileDescriptor *fd,__SizeType startILink,__SizeType secPos,__SizeType & retOff)
{
	auto &linkarr = fd->getSpaces();
	for(;startILink!=linkarr.size()&&
					secPos >= linkarr[startILink].getLimit();++startILink)
							secPos -= linkarr[startILink].getLimit();
	retOff = secPos;
	return startILink;
}
//__DEF_X2fsUtil_Template
//typename __DEF_X2fsUtil::__SizeType
//	__DEF_X2fsUtil::writeToILink(__SizeType ilink,const char *src,__SizeType secPos,__SizeType secLen)
//{
//	if(ilink==0 || ilink >= linkarr.size())
//		return 0;
//	if(secLen==0)
//		secLen = linkarr[ilink].getLimit() - secPos;
//	else if( linkarr[ilink].getLimit()<secLen || linkarr[ilink].getLimit()-secLen<secPos )
//		return 0;
//
//	// UNTESTED lba计算可能溢出到高部分
//	HostEnv::writeSectors(HostEnv::CUR_SEG,
//					 reinterpret_cast<const u8_t*>(src), driver,
//					 metainfo.lbaStartLow + linkarr[ilink].getStart()+secPos, secLen, metainfo.lbaStartHigh);
//	return secLen;
//}

__DEF_X2fsUtil_Template
bool __DEF_X2fsUtil::extendFileSecNum(__FileDescriptor* fd,__SizeType extraSec,bool addFileLength)
{
	if(fd==nullptr || extraSec==0)return false;

	LinkedList<__LinearSourceDescriptor,MallocToSimple> list{ std::shared_ptr<LLSmm>{new LLSmm()}};
	bool flagnewList = freemm.mnewLinked(extraSec, list, 0);
	if(flagnewList)
	{
		for(auto p=list.getHead();p!=nullptr;p=p->getNext())
			fd->addSpace(p->getData());

		if(addFileLength)
			fd->setFileLen(fd->getFileLen() + extraSec*CONST_SECSIZE);
		return true;
	}else{
		return false;
	}
}
__DEF_X2fsUtil_Template
typename __DEF_X2fsUtil::__SizeType __DEF_X2fsUtil::_writeToFile(const char *buf,
		__SizeType nsec,__FileDescriptor* fd,__SizeType secPos,bool updateFileLen)
{
	if(nsec==0 || fd==nullptr || fd->getType() != __FileDescriptor::TYPE_FILE)return 0;

	__SizeType retOff=0;
	__SizeType ilinkPos = locateILink(fd,0, secPos, retOff);
	auto & linkarr = fd->getSpaces();

	__SizeType extraSec = 0;
	if(ilinkPos == linkarr.size())
	{
		extraSec = retOff + nsec;
	}else{
		extraSec = retOff + nsec - linkarr[ilinkPos].getLimit();
	}
	if(extraSec > 0) //需要额外的空间
	{
		if(!extendFileSecNum(fd, extraSec, updateFileLen)) // 空间不足以分配
			return 0;
		ilinkPos = locateILink(fd,0, secPos, retOff);//更新数据状态
	}

	__SizeType thisOff = retOff;
	__SizeType thisLen = (nsec > (linkarr[ilinkPos].getLimit()  - thisOff)?
						(linkarr[ilinkPos].getLimit()  - thisOff):
						nsec );
	const u8_t *thisBuf= reinterpret_cast<const u8_t*>(buf);
	__SizeType i=ilinkPos;
	__SizeType thisLeftSec = nsec;
	while(true)
	{
		HostEnv::writeSectors(HostEnv::CUR_SEG, thisBuf, driver,
						metainfo.getLbaBaseLow() + linkarr[i].getStart() + thisOff,
						thisLen, metainfo.getLbaBaseHigh());
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
typename __DEF_X2fsUtil::__SizeType __DEF_X2fsUtil::_readFromFile(char *buf, __SizeType nsec,
		__FileDescriptor *fd,__SizeType secPos)
{
	if(nsec==0 || fd==nullptr)return 0;

	if(fd->getType() != __FileDescriptor::TYPE_FILE)return 0;

	__SizeType retOff=0;
	__SizeType ilinkPos = locateILink(fd,0, secPos, retOff);
	auto &linkarr = fd->getSpaces();

	if(ilinkPos == linkarr.size())//不可能定位
		return 0;

	__SizeType thisOff = retOff;
	__SizeType thisLen = (nsec > (linkarr[ilinkPos].getLimit()  - thisOff)? (linkarr[ilinkPos].getLimit()  - thisOff): nsec );
	u8_t *thisBuf=reinterpret_cast<u8_t*>(buf);
	__SizeType i=ilinkPos;
	__SizeType thisLeftSec = nsec;
	while(true)
	{
		HostEnv::readSectors(HostEnv::CUR_SEG, thisBuf, driver,
						metainfo.getLbaBaseLow()+ linkarr[i].getStart() + thisOff,
						thisLen, metainfo.getLbaBaseHigh());

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
		__SizeType nbyte,__FileDescriptor *fd,__SizeType byteStart)
{
	if(fd==nullptr ||fd->getType()!=__FileDescriptor::TYPE_FILE
			|| buf==nullptr || nbyte==0)return 0;
	__SizeType bufSize,startOff,endOff;
	bufSize = calculateRandomBufferSize(byteStart, nbyte, &startOff, &endOff, CONST_SECSIZE);
	ManagedObject<u8_t*> mbuf;

	const __SizeType nsec = bufSize/CONST_SECSIZE;
	const __SizeType startSec = byteStart/CONST_SECSIZE;

	auto& linkarr = fd->getSpaces();
	// startOff读补齐
	if(startOff!=0)
	{
		__SizeType retOff;
		__SizeType ilink = locateILink(fd,0,startSec, retOff);
		if(ilink != linkarr.size())//文件足够长
		{

			u8_t *oneUnitBuf=mbuf.getOnlyBuffer(CONST_SECSIZE);

			if( 1!= HostEnv::readSectors(HostEnv::CUR_SEG,
					oneUnitBuf, driver, metainfo.getLbaBaseLow()+ linkarr[ilink].getStart() + retOff,
					1, metainfo.getLbaBaseHigh()))
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
			__SizeType ilink = locateILink(fd,0, startSec + nsec - 1, retOff);
			if(ilink != linkarr.size())//文件足够长
			{

				u8_t *oneUnitBuf=mbuf.getOnlyBuffer(CONST_SECSIZE);
				if( 1!=HostEnv::readSectors(HostEnv::CUR_SEG,
						oneUnitBuf, driver, metainfo.getLbaBaseLow() + linkarr[ilink].getStart()+retOff,
						1, metainfo.getLbaBaseHigh()))
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
	__SizeType written=_writeToFile(buf, nsec, fd, startSec,false);
	__SizeType realWrittenByte = (
						written==nsec?
								nbyte : //没有写错误
								written*CONST_SECSIZE - startOff);//至少有一个扇区没有写，则已经写的减去偏移部分

	// UNTESTED
	// 更新文件长度
	__SizeType updateLen = realWrittenByte + byteStart;//最后一个不可到达的字节就是长度
	if(updateLen > fd->getFileLen())
		fd->setFileLen(updateLen);
	return (realWrittenByte);
}

__DEF_X2fsUtil_Template
typename __DEF_X2fsUtil::__SizeType __DEF_X2fsUtil::_randomReadFile(char *buf,
		__SizeType nbyte,__FileDescriptor *fd,__SizeType byteStart)
{
	if(fd==nullptr || fd->getType()!=__FileDescriptor::TYPE_FILE
			|| buf==nullptr || nbyte==0)return 0;
	__SizeType bufSize,startOff,endOff;
	bufSize = calculateRandomBufferSize(byteStart, nbyte, &startOff, &endOff, CONST_SECSIZE);

	const __SizeType nsec = bufSize/CONST_SECSIZE;
	const __SizeType startSec = byteStart/CONST_SECSIZE;

	__SizeType readin=_readFromFile(buf, nsec, fd, startSec);
	if(readin==0)//没有成功
		return 0;
	else if(readin==nsec) //没有读错误
		return nbyte;
	else //至少有一个扇区没有读
		return readin*CONST_SECSIZE - startOff; //已读减去偏移部分
}

// UNTESTED
__DEF_X2fsUtil_Template
bool __DEF_X2fsUtil::truncateFile(__FileDescriptor *fd,__SizeType newlen)
{
	if(fd == nullptr || newlen < CONST_SECSIZE*2 )return false;//文件至少占用两个扇区
	size_t flen = fd->getFileLen();
	if(flen==newlen)return true;

	__SizeType secPos = (newlen/CONST_SECSIZE) + (newlen%CONST_SECSIZE==0?0:1);//需要定位的扇区
	__SizeType retOff;
	__SizeType ilink = locateILink(fd, 0,secPos, retOff);
	const HostEnv::Vector<LinearSourceDescriptor> &linkarr= fd->getSpaces();

	if(linkarr[ilink].getLimit()==0)//超过实际占用的扇区长度，需要分配retOff个扇区
	{
		if(retOff>0) //确实需要多余的空间
		{
			if(!extendFileSecNum(fd, retOff, false))//不成功
				return false;
		}

	}else{ //需要减少扇区数目
		//将该ilink后面的所有扇区回收
		__SizeType ilinkLast = (retOff==0?ilink:ilink + 1); //从ilinkLast~最后一个应当删除的下标

		while(linkarr.size()!=ilinkLast)
		{
			__SizeType iLinkTail=linkarr.size()-1;
			freemm.mdelete(reinterpret_cast<u8_t*>(linkarr[iLinkTail].getStart()),
												linkarr[iLinkTail].getLimit());
			fd->popSpace();
		}
	}

	fd->setFileLen(newlen);
	return true;
}

// UNTESTED
__DEF_X2fsUtil_Template
void  __DEF_X2fsUtil::mkfs(u8_t driver,const __X2fsMetaInfo &metainfo)
{
	X2fsUtil<__FsEnv> util{ driver, metainfo }; //使用buffered可以进行

	size_t size = util.getSerializitionSize();
	size_t secNum =  size/CONST_SECSIZE + (size%CONST_SECSIZE==0?0:1);
	std::shared_ptr<u8_t[]> buffer{ new u8_t[secNum * CONST_SECSIZE], std::default_delete<u8_t[]>()};
	SerializerPtr<__FsEnv> { *buffer } << util;
	HostEnv::writeSectors(HostEnv::CUR_SEG,*buffer, driver,
			metainfo.getLbaBaseLow() + metainfo.getReservedSec(), secNum, metainfo.getLbaBaseHigh());

	// 先读，后写两个数据到首扇区
	HostEnv::readSectors(HostEnv::CUR_SEG, *buffer,
			driver, metainfo.getLbaBaseLow(), 1, metainfo.getLbaBaseHigh());
	writeHeaderBufferInfo(*buffer,metainfo.getReservedSec(),metainfo.getMetaSec());
	HostEnv::writeSectors(HostEnv::CUR_SEG,*buffer,
			driver, metainfo.getLbaBaseLow(), 1, metainfo.getLbaBaseHigh());
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

