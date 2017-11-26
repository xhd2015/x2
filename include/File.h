

#ifndef File_h__
#define File_h__

#include <64/MallocToSimple.h>
#include <def.h>
#include <MemoryManager.h>
#include <List.h>
#include <EnvInterface.h>


/**
* 
*/
class FileDescriptor
{
public:
	enum{ TYPE_FILE=0,TYPE_DIR=1,TYPE_EAP=2};

	typedef unsigned int TimeType;
	typedef size_t SizeType;
public:
	AS_MACRO FileDescriptor(char type,size_t sectionList,
			size_t fileLen,size_t nameStart,unsigned int createdTime,unsigned int lastModefiedTime);

	AS_MACRO char getType()const;
	AS_MACRO void setType(char type);

	AS_MACRO size_t getNameOffset()const;
	AS_MACRO void	setNameOffset(size_t off);
	AS_MACRO unsigned int getCreatedTime() const;
	AS_MACRO void setCreatedTime(unsigned int createdTime);
	AS_MACRO size_t getFileLen() const;
	AS_MACRO void setFileLen(size_t fileLen);
	AS_MACRO DEPRECATED size_t getFileStart() const;//file will always starts from the beginning
	AS_MACRO DEPRECATED void setFileStart(size_t fileStart);
	AS_MACRO unsigned int getLastModefiedTime() const;
	AS_MACRO void setLastModefiedTime(unsigned int lastModefiedTime);
	AS_MACRO DEPRECATED size_t getSectionSpan() const;
	AS_MACRO DEPRECATED void setSectionSpan(size_t sectionSpan);
	AS_MACRO DEPRECATED size_t getSectionStart() const;
	AS_MACRO DEPRECATED void setSectionStart(size_t sectionStart);


	AS_MACRO size_t getSectionList() const ;
	AS_MACRO void setSectionList(size_t	sectionList);

protected:
	char type;
	size_t /* DEPRECATED sectionStart,sectionSpan,*//*DEPRECATED fileStart */sectionList,fileLen,nameStart;
	unsigned int createdTime,lastModefiedTime;

};

#pragma pack(push,1)


#if defined(CODE64)
#include <EnvInterface64Impl.h>  //impl for dumpInfo
#endif

/**
 * 从一个扇区初始化
 *
 * 注意，该结构必须在所有架构上一致，因此采用uXX_t来定义各个域
 */
class X2fsMetaInfo{
public:
	enum __ENUMS{
		SECNUM_RESERVED_CONST=2,
		SECNUM_META_CONST=1,
		SECNUM_SECD = 20,
		VALID_FLAG=0xaa55,

		PARTS_REQUIRED=5,
		PARTS_OPTIONAL=1,

		INDEX_NAME=0,
		INDEX_DIR=1,
		INDEX_FREE=2,
		INDEX_FILE=3,
		INDEX_LINK=4,


		INDEX_OPTIONAL_SECD=0
	};
	X2fsMetaInfo()=default;

public:
	const u32_t reservedSec=SECNUM_RESERVED_CONST;//2
	const u32_t metaSec=SECNUM_META_CONST;
	/**
	 * 	name dir free file link secd
	 *
	 * 	=0表示该分区不分配。通常用于一些可选分区
	 */
	u32_t secnums[PARTS_REQUIRED];
	const u8_t len=PARTS_REQUIRED;//上面数组的长度

	u32_t optional[PARTS_OPTIONAL];
	const u8_t optionalLen=PARTS_OPTIONAL;

	/**
	 * 记录该分区的lba起始地址
	 * 与mbr中的信息重复
	 */
	u32_t lbaStartLow;
	u32_t lbaStartHigh;

	/**
	 * 记录该分区的总的扇区数
	 * 与mbr中的信息重复
	 */
	u32_t wholeSecnums;

	const u16_t	validFlag=VALID_FLAG;


public:
	/**
	 *  校验metainfo是否符合结构
	 */
	static bool checkMetainfo(const X2fsMetaInfo* info);
	void dumpInfo(EnvInterface64Impl *env);
};

#pragma pack(pop)

/**
 *  about offset: relative to the beginning of that partition
 *		zero(0~3,an integer size) address in   filename should not be used,pointing to them means no name.Only root directory can do that
 *
 *	FreeSpaceSection:
 *		The recorded data is relative the 0.This is because these files do not exist in the memory,so they do not use buffer
 *		0:  record the whole start & limit
 *		....
 *
 *	RAW Section:
 *
 *
 *	性能分析：因为解析路径名需要从根遍历树，很耗费时间。
 *
 */
template <class __EnvInterface>
class X2fsUtil{
public:
	typedef
#if defined(IDE_MODE)
			EnvInterface
#else
			__EnvInterface
#endif
		_EnvInterface;
public:
	enum{
		// 顺序一致
		INDEX_NAME=X2fsMetaInfo::INDEX_NAME,
		INDEX_DIR= X2fsMetaInfo::INDEX_DIR,
		INDEX_FREE=X2fsMetaInfo::INDEX_FREE,
		INDEX_FILE=X2fsMetaInfo::INDEX_FILE,
		INDEX_LINK=X2fsMetaInfo::INDEX_LINK,
		INDEX_OPTIONAL_SECD=X2fsMetaInfo::INDEX_OPTIONAL_SECD,
	};





	enum{SecSize=512,KiB=2*SecSize,MiB=1024*KiB,GiB=1024*MiB};
	enum{
		 ReservedSection=0,ReservedSectionLen=2*SecSize,
		 FileNameSection=2*SecSize,FileNameSectionLen=5*SecSize,
		 DirSection=FileNameSection+FileNameSectionLen,DirSectionLen=15*SecSize,
		 FreeSpaceSection=DirSection+DirSectionLen,FreeSpaceSectionLen=5*SecSize,
		 /*NEW @ 2017-03-12 16:19:43*/LinkedInfoSection=FreeSpaceSection + FreeSpaceSectionLen, LinkedInfoSectionLen=5*SecSize,
		 	 	 	 	 	 	 	 FileAllocSection=LinkedInfoSection+LinkedInfoSectionLen
		// DEPRECATED,use sizeof(SECTION_TRAIL) SectoinPointerSize = sizeof(size_t),SectionLengthSize = sizeof(size_t)/*the end of the section has the two trailing numbers*/
		//DEPRECATED SectionTrailSize = sizeof(LinearSourceDescriptor)

	};
	enum{
		ERROR_FILENAMESPACE,
		ERROR_DIRTREESPACE,
		ERROR_FREESPACE,
		ERROR_LINKINFO_SPACE_NOT_ENOUGH,

		//
		ERROR_FILEALLOCSPACE,
		ERROR_FILE_ALREDY_EXIST,
		/*ERROR_CANNOT_FIND_PARENT_DIRECTORY,*/
		ERROR_PATH_PARENT_NOT_EXIST,
		ERROR_PATH_FILE_NOT_EXIST,
		ERROR_INVALID_FILENAME,
		ERROR_DST_IS_NOT_DIRECTORY,
		ERROR_GENERAL_ERROR,
		ERROR_NOERR,


		PATH_TYPE_DIR,
		PATH_TYPE_FILE,
		PATH_TYPE_UNKNOWN

	};
	typedef X2fsUtil This;
	/**
	 * 依赖这些类型作为分配器
	 */
	typedef MallocToSimple<TreeNode<MemoryDescriptor>,_EnvInterface> TMSmm;
	typedef MallocToSimple<ListNode<LinearSourceDescriptor>,_EnvInterface> LLSmm;

	// TODO 检查下面的做法是否合法
//	template <class T>
//	class PartialMallocToSimple:public MallocToSimple<T,_EnvInterface>{
//		using MallocToSimple<T,_EnvInterface>::MallocToSimple;
//	};
	template <class T>
	using PartialMallocToSimple=MallocToSimple<T,_EnvInterface>;

	typedef MemoryManager<PartialMallocToSimple> FileNameMM;
	typedef SimpleMemoryManager<TreeNode<FileDescriptor> > FileNodeMM;

	//FileNode 真实类型是  SimpleMemoryManager<TreeNode<FileDescriptor> >::Node
	//即 TreeNode<FileDescriptor>,SimpleMemoryNode的组合
	// getHead()只返回TreeNode<FileDescriptor>,即数据部分
	//	typedef FileNodeMM::Node FileNode;
	typedef FileNodeMM::DataPart FileNode;
	typedef typename FileNodeMM::FullNode FullNode;


	typedef Tree<FileDescriptor,SimpleMemoryManager> FileTree;

	typedef LinearSourceManager<LinearSourceDescriptor,PartialMallocToSimple> FreeSpaceMM;
	typedef LinearSourceManager<LinearSourceDescriptor,PartialMallocToSimple> LinkedInfoMM;

	enum{
		FileNodeSize=sizeof(FileNode)
	};
public:
	X2fsUtil()=default;
	/**
	 * 两种初始化情况：
	 * 	1.需要从驱动器上读取数据，分配缓冲区，然后初始化
	 * 	2.已经准备完备所有缓冲区，数据已经读入，初始化
	 *
	 * 	metainfo 初始化完毕就可以开始读取了
	 */
	X2fsUtil(_EnvInterface *env,u8_t driver,u32_t lbaBase);
	X2fsUtil(_EnvInterface *env,u8_t driver,u32_t lbaBase,X2fsMetaInfo *metainfo,u8_t *buffers[]);
private:
	void initWithBuffersAlloced();
public:
	~X2fsUtil();
	/**
	 * 在root根目录下创建一个文件
	 * @name   文件名
	 * @secNum 文件占据的扇区大小
	 */
	bool createFileInRoot(const char *name,size_t secNum);//reserved number of sectors
	DEPRECATED bool hasFilename(const char *name)const;
	bool hasFilename(int argc,const char *argv[],const char *name)const;


//	bool hasFilename(FileNode * node,const std::string& name)const;


	DEPRECATED bool mkdir(const char* name);
	bool createFile(int argc,const char* argv[],int secSpan);
	bool createDir(int argc,const char* argv[]);
	bool deleteFile(int argc,const char * argv[]);
	bool rename(int argc,const char *argv[],const char *newname);
	bool move(int argcSrc,const char *argvSrc[],int argcDst,const char *argvDst[],const char *newname=NULL);
	void dumpFileInfo(int argc,const char *argv[]);
	/**
	 * if exist return PATH_XXX,else return ERROR_XXX
	 */
	int	 tellType(int argc,const char * argv[])const;
	void listNode(int argc,const char * argv[],int maxdeepth=1)const;

	size_t writeToFile(const char *buf,size_t objsize, size_t nobj,int argc,const char *argv[],size_t foff=0);
	size_t readFromFile(char *buf,size_t objsize, size_t nobj,int argc,const char *argv[],FileNode *fnode,size_t foff=0);

	void listRoot()const;
	void listNode(const FileNode* p)const;
	/**
	 * 先将散布在内存中的信息写入缓冲区
	 * 再将缓冲区中的内容写入到磁盘
	 */
	void flush();//write the buffered content back to file
	AS_MACRO int geterrno()const;
	AS_MACRO void setEnvInterface(_EnvInterface *env);

public:
	char *getFileNameCstr(const FileDescriptor &fd,size_t &nlen)const;
//	std::string getFileName(const FileNode *p)const;

//	UNTESTED
	void printNode(const FileNode *p)const;
//	UNTESTED
	void listOnNode(const FileNode *p,int maxdeepth=1)const;

	bool hasFilename(FileNode * fnode,const char *name)const;
	bool create(FileNode *p,char type,const char *name,size_t secSpan=2,int ctime=0);
	bool createFile(FileNode *p,const char *name,size_t secNum);
	bool mkdir(FileNode * fatherDir,const char *dirname);
	void freeNode(FileNode * node);//free all,not just a single.This is generally used in dir & file
	void insertNode(FileNode *dst,FileNode *fnode);
	void removeNode(FileNode *node);//remove is necessary only at the connected node(with this tree)
	bool rename(FileNode *node,const char *newname);
	bool move(FileNode *p,FileNode* dstDir,const char *newname=NULL);
	void dumpFileInfo(FileNode * fnode);
	/**
	 * If not found,return the index that fails
	 *
	 * This could be used in
	 * 		create a file/dir,ensure no repeating name
	 *
	 */
	FileNode * locatePath(FileNode *base,int argc,const char *argv[],int &errorLevel)const;
	/**
	 *
	 * @return NULL to indicate failure
	 */
	FileNode * locatePath(FileNode *base,const char *name)const;
	FileNode * getPathParentNode(int argc,const char * argv[])const;
	FileNode * getPathNode(int argc,const char * argv[])const;
//	INCOMPLETE FileNode * locatePath(FileNode *base,int argc,const char *argv[],int &errorLevel);
//	INCOMPLETE FileNode * locatePath(FileNode *base,const char *name);

//	INCOMPLETE
	size_t writeToFile(const char *buf,size_t objsize, size_t nobj,FileNode *fnode,size_t foff=0);
//	INCOMPLETE
	size_t readFromFile(char *buf,size_t objsize, size_t nobj,FileNode *fnode,size_t foff=0);
	AS_MACRO void seterrno(int processErrno)const;
	AS_MACRO void seterrno(int processErrno);
	AS_MACRO FileNode * getRootBase()const;
	AS_MACRO FileNode * getRootBase();
	AS_MACRO static bool isDirectory(const FileNode *p);
	AS_MACRO static bool isFile(const FileNode *p);

	/**
	 * 根据metainfo和磁盘信息，建立一个有效的空分区
	 */
	static void mkfs(_EnvInterface *env,u8_t driver,const X2fsMetaInfo *metainfo);

	template <template <class>class _Allocator>
	INCOMPLETE static void getLinkedList(LinearSourceDescriptor *buffer,size_t i,LinkedList<LinearSourceDescriptor,_Allocator> &list,size_t maxlen);

	DEPRECATED static void createFile_old(void *base,const char* name,size_t secNum);//default length=0,start=0,span=secNum

	AS_MACRO FileTree getFileTree();
protected:
		DEPRECATED void initBuffers();

		/**
		 * 这真是一个bug， 因为指针偏移在64位系统下不能仅仅使用int存放，所以导致出错。
		 * 调试了半天。。。
		 */
		// old version ---> void adjustDirbufOffset(int off);//positive or negative
		void adjustDirbufOffset(ptrdiff_t off);


		/**
		 * 文件名的存储方式是以'\0'为分隔的链表形式
		 */
		void retriveFileNameSection();
		/**
		 * This is not necessary for filename section,cause all changes had been made as direct and immediate
		 * 这个函数是没有必要的，但是仅仅为了兼容性才使用
		 * 所有的改变都是基于该缓冲区的，因此不必刷新缓冲区
		 */
		DEPRECATED void saveFileNameSection();

		void retriveFreeSpaceSection();
		void saveFreeSpaceSection();


//		UNTESTED
		void retriveLinkedInfoSection();
		/**
		 * 同name section，所有的修改都是基于该缓冲区的
		 */
		DEPRECATED void saveLinkedInfoSection();/*The modifies are at-place*/

		void retriveDirSection();
		/**
		 *  这里需要对dir区指针进行偏移调整，调整基于dir区的开始
		 */
		void saveDirSection();


protected:
	_EnvInterface *env;
	u32_t	driver;
	u32_t	lbaBaseAddress;

	union{
		u8_t 		 *metabuf;
		X2fsMetaInfo *metainfo;
	};

	u8_t *buffers[X2fsMetaInfo::PARTS_REQUIRED];

	/**
	 * 将link分区看成是一个LineaerSourceDescriptor数组
	 */
	LinearSourceDescriptor *linkarr;
	size_t linkarrLen;


	// TODO 检查下面的设计是否符合松耦合结构设计
	// 依赖图
	/*
	 * this
	 * filenamemm-->mmnodesmm(节点分配器,该节点可以任意)
	 *				fileTree-->dirsmm-->buffers[INDEX_DIR]
	 *		linkmm,freemm-->listnodesmm(同一种类型的节点分配器）
	 *
	 *
	 *
	 *	注：x2文件系统中，除了dir分区存放的是完整的链接信息
	 *	其他分区存放的是原始信息，根据这些原始信息可以构造一个链表
	 */


	TMSmm mmnodesmm;
	/**
	 * 管理文件名的MemoryManager
	 */
	FileNameMM filenamemm;
	LLSmm listnodesmm;


	/**
	 * 管理节点区域的SMM，管理类型为TreeNode<FileDescriptor>
	 * 用于分配树节点
	 * 此管理器管理的区域是buffers[INDEX_DIR]
	 */
	FileNodeMM dirsmm;

	/**
	 * 一棵树，其全部分配的节点在dirsmm中
	 */
	FileTree fileTree;

	/**
	 * 管理空闲空间的信息，链表实现
	 */
	FreeSpaceMM freemm;

	/**
	 * 文件的存放信息，即每个文件占用的链表结构
	 */
	LinkedInfoMM linkmm;


	/**
	 * 存放错误信息
	 */
	mutable int processErrno;/*can be used in both const & non-const method*/

	// 不再加载可选分区
//	/**
//	 * 二级加载器是否载入
//	 */
//	bool secdLoaded;

};

//=============Function Macros
//=====class : FileDescriptor
FileDescriptor::FileDescriptor(char type,size_t sectionList,size_t fileLen,size_t nameStart,unsigned int createdTime,unsigned int lastModefiedTime):
type(type),sectionList(sectionList),fileLen(fileLen),
nameStart(nameStart),createdTime(createdTime),lastModefiedTime(lastModefiedTime)
{
}

 unsigned int FileDescriptor::getCreatedTime() const
{
	return createdTime;
}

 void FileDescriptor::setCreatedTime(unsigned int createdTime) {
	this->createdTime = createdTime;
}

 size_t FileDescriptor::getFileLen() const {
	return fileLen;
}

 void FileDescriptor::setFileLen(size_t fileLen) {
	this->fileLen = fileLen;
}


 unsigned int FileDescriptor::getLastModefiedTime() const {
	return lastModefiedTime;
}

 void FileDescriptor::setLastModefiedTime(unsigned int lastModefiedTime) {
	this->lastModefiedTime = lastModefiedTime;
}

size_t FileDescriptor::getSectionList() const
{
	return this->sectionList;
}

void FileDescriptor::setSectionList(size_t	sectionList)
{
	this->sectionList = sectionList;
}

char FileDescriptor::getType() const {
	return type;
}

 void FileDescriptor::setType(char type) {
	this->type = type;
}

size_t FileDescriptor::getNameOffset()const
{
	return this->nameStart;
}
void	FileDescriptor::setNameOffset(size_t off)
{
	this->nameStart=off;
}

//=========class X2fsUtil
template <class __EnvInterface>
int X2fsUtil<__EnvInterface>::geterrno()const
{
	return this->processErrno;
}
template <class __EnvInterface>
void X2fsUtil<__EnvInterface>::setEnvInterface(_EnvInterface *env)
{
	this->env=env;
}
template <class __EnvInterface>
void X2fsUtil<__EnvInterface>::seterrno(int processErrno)const
{
	this->processErrno=processErrno;
}
template <class __EnvInterface>
void X2fsUtil<__EnvInterface>::seterrno(int processErrno)
{
	this->processErrno=processErrno;
}

template <class __EnvInterface>
typename X2fsUtil<__EnvInterface>::FileNode *X2fsUtil<__EnvInterface>::getRootBase()const
{
		return (FileNode *)this->fileTree.getHead();
}
template <class __EnvInterface>
typename X2fsUtil<__EnvInterface>::FileNode *X2fsUtil<__EnvInterface>::getRootBase()
{
		return (FileNode *)this->fileTree.getHead();
}
template <class __EnvInterface>
bool X2fsUtil<__EnvInterface>::isDirectory(const FileNode *p)
{
	return p && p->getData().getType()==FileDescriptor::TYPE_DIR;
}
template <class __EnvInterface>
bool X2fsUtil<__EnvInterface>::isFile(const FileNode *p)
{
	return p && p->getData().getType()==FileDescriptor::TYPE_FILE;
}
template <class __EnvInterface>
typename X2fsUtil<__EnvInterface>::FileTree X2fsUtil<__EnvInterface>::getFileTree()
{
	return fileTree;
}

//template<template<class > class _Allocator>
//void X2fsUtil::getLinkedList(LinearSourceDescriptor* buffer,
//		LinkedList<LinearSourceDescriptor, _Allocator>& list, size_t maxlen) {
//}

#endif //File_h__
