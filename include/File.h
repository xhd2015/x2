

#ifndef File_h__
#define File_h__

#include <64/MallocToSimple.h>
#include <def.h>
#include <MemoryManager.h>
#include <List.h>
#include <EnvInterface.h>
#if defined(CODE64)
#include <EnvInterface64Impl.h>  //impl for dumpInfo
#endif


/**
* 
*/
template <typename __SizeType>
class FileDescriptor
{
public:
	enum{ TYPE_FILE=0,TYPE_DIR=1,TYPE_EAP=2};

	/**
	 * 仅仅是__SizeType的别名
	 */
	typedef __SizeType __TimeType;
public:
	AS_MACRO FileDescriptor(u8_t type,__SizeType sectionList,
			__SizeType fileLen,__SizeType nameStart,__TimeType createdTime,__TimeType lastModefiedTime);

	AS_MACRO u8_t getType()const;
	AS_MACRO void setType(u8_t type);

	AS_MACRO __SizeType getNameOffset()const;
	AS_MACRO void	setNameOffset(__SizeType off);
	AS_MACRO __TimeType getCreatedTime() const;
	AS_MACRO void setCreatedTime(__TimeType createdTime);
	AS_MACRO __SizeType getFileLen() const;
	AS_MACRO void setFileLen(__SizeType fileLen);
	AS_MACRO DEPRECATED __SizeType getFileStart() const;//file will always starts from the beginning
	AS_MACRO DEPRECATED void setFileStart(__SizeType fileStart);
	AS_MACRO __TimeType getLastModefiedTime() const;
	AS_MACRO void setLastModefiedTime(__TimeType lastModefiedTime);
	AS_MACRO DEPRECATED __SizeType getSectionSpan() const;
	AS_MACRO DEPRECATED void setSectionSpan(__SizeType sectionSpan);
	AS_MACRO DEPRECATED __SizeType getSectionStart() const;
	AS_MACRO DEPRECATED void setSectionStart(__SizeType sectionStart);


	AS_MACRO __SizeType getSectionListIndex() const ;
	AS_MACRO void setSectionListIndex(__SizeType	sectionListIndex);

protected:
	/**
	 * 类型，文件，文件夹，或者扩展区域（废弃）
	 */
	u8_t type;

	/**
	 * 文件占据的分区链表的下标
	 */
	__SizeType /* DEPRECATED sectionStart,sectionSpan,*//*DEPRECATED fileStart */sectionListIndex;
	/**
	 * 文件长度
	 */
	__SizeType fileLen;

	/**
	 * 文件名在 name分区中的开始下标
	 */
	__SizeType nameStart;

	/**
	 * 创建时间
	 */
	__TimeType createdTime;

	/**
	 * 最后修改时间
	 */
	__TimeType lastModefiedTime;

};

#pragma pack(push,1)


/**
 * 从一个扇区初始化
 *
 * 注意，该结构必须在所有架构上一致，因此采用uXX_t来定义各个域
 */
template <typename __SizeType>
class X2fsMetaInfo{
public:
	enum __ENUMS{
		SECNUM_RESERVED_CONST=2,
		SECNUM_META_CONST=1,
		SECNUM_SECD = 20,
		VALID_FLAG=0xaa55,


		INDEX_NAME=0,
		INDEX_DIR=1,
		INDEX_FREE=2,
		INDEX_LINK=3,//当你修改该区时，必须修改PARTS_REQUIRED

		PARTS_REQUIRED=4,
		PARTS_OPTIONAL=1,


		INDEX_OPTIONAL_SECD=0
	};
	X2fsMetaInfo()=default;

public:
	const __SizeType reservedSec=SECNUM_RESERVED_CONST;//2
	const __SizeType metaSec=SECNUM_META_CONST;
	/**
	 * 	name dir free file link secd
	 *
	 * 	=0表示该分区不分配。通常用于一些可选分区
	 */
	__SizeType secnums[PARTS_REQUIRED];
	const u8_t len=PARTS_REQUIRED;//上面数组的长度

	__SizeType optional[PARTS_OPTIONAL];
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
	__SizeType wholeSecnums;

	const u16_t	validFlag=VALID_FLAG;


public:
	/**
	 *  校验metainfo是否符合结构
	 */
	static bool checkMetainfo(const X2fsMetaInfo<__SizeType>* info);
	void dumpInfo(EnvInterface64Impl *env);
//	__SizeType getDataAllocation
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
template <class __EnvInterface,typename __SizeType>
class X2fsUtil{
public:
	typedef
#if defined(IDE_MODE)
			EnvInterface
#else
			__EnvInterface
#endif
		_EnvInterface;

	using __FileDescriptor = FileDescriptor<__SizeType>;
	using __TimeType = typename __FileDescriptor::__TimeType;

public:
	enum{
		// 顺序一致
		INDEX_NAME=X2fsMetaInfo<__SizeType>::INDEX_NAME,
		INDEX_DIR= X2fsMetaInfo<__SizeType>::INDEX_DIR,
		INDEX_FREE=X2fsMetaInfo<__SizeType>::INDEX_FREE,
		INDEX_LINK=X2fsMetaInfo<__SizeType>::INDEX_LINK,
		INDEX_OPTIONAL_SECD=X2fsMetaInfo<__SizeType>::INDEX_OPTIONAL_SECD,
	};





	enum{SecSize=512,KiB=2*SecSize,MiB=1024*KiB,GiB=1024*MiB};
	enum{
		 ReservedSection=0,ReservedSectionLen=2*SecSize,
		 FileNameSection=2*SecSize,FileNameSectionLen=5*SecSize,
		 DirSection=FileNameSection+FileNameSectionLen,DirSectionLen=15*SecSize,
		 FreeSpaceSection=DirSection+DirSectionLen,FreeSpaceSectionLen=5*SecSize,
		 /*NEW @ 2017-03-12 16:19:43*/LinkedInfoSection=FreeSpaceSection + FreeSpaceSectionLen, LinkedInfoSectionLen=5*SecSize,
		 	 	 	 	 	 	 	 FileAllocSection=LinkedInfoSection+LinkedInfoSectionLen
		// DEPRECATED,use sizeof(SECTION_TRAIL) SectoinPointerSize = sizeof(__SizeType),SectionLengthSize = sizeof(__SizeType)/*the end of the section has the two trailing numbers*/
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
	typedef MallocToSimple<TreeNode<MemoryDescriptor<__SizeType>>,_EnvInterface> TMSmm;
	typedef MallocToSimple<ListNode<LinearSourceDescriptor<__SizeType>>,_EnvInterface> LLSmm;

	// TODO 检查下面的做法是否合法
//	template <class T>
//	class PartialMallocToSimple:public MallocToSimple<T,_EnvInterface>{
//		using MallocToSimple<T,_EnvInterface>::MallocToSimple;
//	};
	template <class T>
	using PartialMallocToSimple=MallocToSimple<T,_EnvInterface>;

	typedef MemoryManager<PartialMallocToSimple,__SizeType> FileNameMM;
	typedef SimpleMemoryManager<TreeNode<FileDescriptor<__SizeType> > > FileNodeMM;

	//FileNode 真实类型是  SimpleMemoryManager<TreeNode<FileDescriptor> >::Node
	//即 TreeNode<FileDescriptor>,SimpleMemoryNode的组合
	// getHead()只返回TreeNode<FileDescriptor>,即数据部分
	//	typedef FileNodeMM::Node FileNode;
	typedef typename FileNodeMM::DataPart FileNode;
	typedef typename FileNodeMM::FullNode FullNode;
//	using FullNode = typename FileNodeMM::FullNode;
//	using FileNode = TreeNode<FileDescriptor<__SizeType> >;
//	using FileNode = int;

	typedef Tree<FileDescriptor<__SizeType>,SimpleMemoryManager> FileTree;

	typedef LinearSourceManager<LinearSourceDescriptor<__SizeType>,PartialMallocToSimple,__SizeType> FreeSpaceMM;
	typedef LinearSourceManager<LinearSourceDescriptor<__SizeType>,PartialMallocToSimple,__SizeType> LinkedInfoMM;

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
	X2fsUtil(_EnvInterface *env,u8_t driver,X2fsMetaInfo<__SizeType> *metainfo,u8_t *buffers[]);
private:
	void initWithBuffersAlloced();
public:
	~X2fsUtil();
	/**
	 * 在root根目录下创建一个文件
	 * @name   文件名
	 * @secNum 文件占据的扇区大小
	 */
	bool createFileInRoot(const char *name,__SizeType secNum);//reserved number of sectors
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

	__SizeType writeToFile(const char *buf,__SizeType objsize,__SizeType nobj,int argc,const char *argv[],__SizeType foff=0);
	__SizeType r__SizeTypemFile(char *buf,__SizeType objsize, __SizeType nobj,int argc,const char *argv[],FileNode *fnode,__SizeType foff=0);

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
	char *getFileNameCstr(const FileDescriptor<__SizeType> &fd,__SizeType &nlen)const;
//	std::string getFileName(const FileNode *p)const;

//	UNTESTED
	void printNode(const FileNode *p)const;
//	UNTESTED
	void listOnNode(const FileNode *p,int maxdeepth=1)const;

	bool hasFilename(FileNode * fnode,const char *name)const;
	bool create(FileNode *p,u8_t type,const char *name,__SizeType secSpan=2,__TimeType ctime=0);
	bool createFile(FileNode *p,const char *name,__SizeType secNum);
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

	/**
	 * @param buf 源数据区
	 * @param objsize 源数据区中每个数据的大小
	 * @param nobj   要写的数据个数，nobj*objsize就是要写的总字节数
	 * @param fnode		文件节点
	 * @param	foff	写到文件的偏移位置
	 */
//	INCOMPLETE
	__SizeType writeToFile(const char *buf,__SizeType objsize, __SizeType nobj,FileNode *fnode,__SizeType foff=0);

	// UNTESTED
	/**
	 * 从startILink处开始查找off的ilink位置
	 * @param secPos  相对于startILink需要定位的偏移量,这个待定位的位置是可以访问的
	 * @param refOff   如果找到这个ilink，则同时设置这个值表明距离此ilink区间的开始处偏移; 如果没有找到，则retOff存放最后一个非0ilink的剩余的secPos偏移量
	 * @return 0 未找到，空间不足以定位到该处
	 * 		   其他，则一定保证retOff小于该区的limit，也就是说refOff一定在该区的范围内。
	 */
	__SizeType locateILink(__SizeType startILink,__SizeType secPos,__SizeType & retOff);

	/**
	 * 按扇区写数据到ilink所指示的区间中，从secPos开始写，写secLen个
	 * @param   secLen 要写的扇区数目，如果len=0，则表示写到最后一个分区结束
	 * @return  如果ilink无效，或者所写的数据范围超过该ilink，则不执行写操作，并且返回0；
	 * 			写成功则返回实际写入的分区长度(secLen=0时返回实际长度)
	 */
	__SizeType		writeToILink(__SizeType ilink,const char *src,__SizeType secPos,__SizeType secLen);

	/**
	 * 扩展文件的大小
	 * @param fileNode  要增加大小的文件
	 * @param extraSec  要增加的扇区数目
	 * @param addFileLength  是否也将文件内容长度更新
	 *
	 * @return 如果extraSec = 0则无影响； 如果不能增加，则返回false，源文件节点状态不变；否则，可能改变ilink的位置
	 */
	bool			extendFileSecNum(FileNode * fileNode,__SizeType extraSec,bool addFileLength=false);

	/**
	 * 返回最后一个ILink的位置，即(0,0)处
	 * @return 0 失败，其他成功
	 */
	__SizeType		getEndILink(FileNode *fileNode)const;

	//INCOMPLETE
	__SizeType _writeToFile(const char *buf, __SizeType nsec,FileNode *fnode,__SizeType secPos=0);
	__SizeType _readFromFile(char *buf,__SizeType nsec,FileNode *fnode,__SizeType secPos=0);

//	INCOMPLETE
	__SizeType readFromFile(char *buf,__SizeType objsize, __SizeType nobj,FileNode *fnode,__SizeType foff=0);
	AS_MACRO void seterrno(int processErrno)const;
	AS_MACRO void seterrno(int processErrno);
	AS_MACRO FileNode * getRootBase()const;
	AS_MACRO FileNode * getRootBase();
	AS_MACRO static bool isDirectory(const FileNode *p);
	AS_MACRO static bool isFile(const FileNode *p);

	/**
	 * 根据metainfo和磁盘信息，建立一个有效的空分区
	 */
	static void mkfs(_EnvInterface *env,u8_t driver,const X2fsMetaInfo<__SizeType> *metainfo);

	template <template <class>class _Allocator>
	INCOMPLETE static void getLinkedList(LinearSourceDescriptor<__SizeType> *buffer,__SizeType i,LinkedList<LinearSourceDescriptor<__SizeType>,_Allocator> &list,__SizeType maxlen);

	DEPRECATED static void createFile_old(void *base,const char* name,__SizeType secNum);//default length=0,start=0,span=secNum

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
		 * 文件名的存储方式不是以'\0'为分隔的链表形式，而是[N]...的 存储形式
		 * 比如存储 foo,则内存布局如下：[4][f][o][o],首个字节表示字符串长度
		 * 因此，文件名最长不能超过128
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

		/**
		 * 从dir内存缓冲区恢复处正常的链接信息
		 */
		void retriveDirSection();

		/**
		 *  这里需要对dir区指针进行偏移调整，调整基于dir区的开始
		 */
		void saveDirSection();


protected:
	/**
	 * 要求操作系统实现提供的功能集
	 */
	_EnvInterface *env;
	/**
	 * 驱动器号，在有的操作系统上，可能将驱动器号映射成文件
	 */
	u8_t	driver;

	/**
	 * 元信息区域
	 */
	union{
		u8_t 		 *metabuf;
		X2fsMetaInfo<__SizeType> *metainfo;
	};

	/**
	 *	buffers[INDEX_FREE]  该区的开始位置存放两个节点，节点0描述了总体的信息(数据区开始，长度），节点1是(0,0)
	 * 						其中数据区开始是相对于该文件分区的起点，如果文件有10个用于元信息的区域，则开始就是10，以扇区为单位
	 * 						所有的数据以(0,0)结尾
	 * 	buffers[INDEX_LINK]
	 * 	buffers[INDEX_FREE]  该分区是一个供管理使用的分区，其上的数据并不
	 */
	u8_t *buffers[X2fsMetaInfo<__SizeType>::PARTS_REQUIRED];

	/** DEPRECATED
	 * 将link分区看成是一个LineaerSourceDescriptor数组
	 * 每一个元素描述了文件的分配情况，文件占据多个不连续的扇区，这些扇区由下面链表描述
	 */

	/**
	 * 描述文件的占用的扇区信息，文件中的保存起始下标
	 * 文件占用的扇区不连续，可能如下： (2,3)-->(7,2)-->(0,0) 表示文件占用2扇区开始的3个扇区，7扇区开始的2个扇区
	 * 该数组实际上是freespace分区的别名，也就是说linkarr的首地址指向了内存中freespace分区的开始
	 *
	 */
	LinearSourceDescriptor<__SizeType> *linkarr;
	__SizeType linkarrLen;


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

	/**
	 * 为linkmm，分配管理节点
	 */
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
	 * 一个数值区间管理器，初始数值区间是  [数据区开始，数据区开始+数据区长度)
	 * 对于这种管理器，我们只应当将其认为是标记一系列的数值
	 * 当我们从中分配了一段字区间后，相应的认为磁盘上这些区间已经分配了。
	 * 对文件的分配使得这段被分配的区间被加入到该文件linkarr的数组中
	 *
	 * 管理freespace空闲空间的信息，链表实现
	 * 当分配空间后，该段空间就从链表中取消
	 */
	FreeSpaceMM freemm;


	/**
	 * 一个数值管理器，标记linkarr中可用的下标
	 * 该管理器管理一个数组linkarr，管理范围是[0,0+linarrLen)
	 * 使用listnodesmm作为节点分配器，在retriveLinkeInfoSection()方法中初始化
	 *
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
template <typename __SizeType>
FileDescriptor<__SizeType>::FileDescriptor(u8_t type,__SizeType sectionList,__SizeType fileLen,__SizeType nameStart,
		__TimeType createdTime,__TimeType lastModefiedTime):
type(type),sectionListIndex(sectionList),fileLen(fileLen),
nameStart(nameStart),createdTime(createdTime),lastModefiedTime(lastModefiedTime)
{
}

template <typename __SizeType>
typename FileDescriptor<__SizeType>::__TimeType FileDescriptor<__SizeType>::getCreatedTime() const
{
	return createdTime;
}

template <typename __SizeType>
void FileDescriptor<__SizeType>::setCreatedTime(__TimeType createdTime) {
	this->createdTime = createdTime;
}

template <typename __SizeType>
__SizeType FileDescriptor<__SizeType>::getFileLen() const {
	return fileLen;
}

template <typename __SizeType>
void FileDescriptor<__SizeType>::setFileLen(__SizeType fileLen) {
	this->fileLen = fileLen;
}

template <typename __SizeType>
typename FileDescriptor<__SizeType>::__TimeType FileDescriptor<__SizeType>::getLastModefiedTime() const {
	return lastModefiedTime;
}
template <typename __SizeType>
void FileDescriptor<__SizeType>::setLastModefiedTime(__TimeType lastModefiedTime) {
	this->lastModefiedTime = lastModefiedTime;
}
template <typename __SizeType>
__SizeType FileDescriptor<__SizeType>::getSectionListIndex() const
{
	return this->sectionListIndex;
}

template <typename __SizeType>
void FileDescriptor<__SizeType>::setSectionListIndex(__SizeType	sectionListIndex)
{
	this->sectionListIndex = sectionListIndex;
}

template <typename __SizeType>
u8_t FileDescriptor<__SizeType>::getType() const {
	return type;
}
template <typename __SizeType>
void FileDescriptor<__SizeType>::setType(u8_t type) {
	this->type = type;
}

template <typename __SizeType>
__SizeType FileDescriptor<__SizeType>::getNameOffset()const
{
	return this->nameStart;
}
template <typename __SizeType>
void FileDescriptor<__SizeType>::setNameOffset(__SizeType off)
{
	this->nameStart=off;
}

//=========class X2fsUtil
template <class __EnvInterface,typename __SizeType>
int X2fsUtil<__EnvInterface,__SizeType>::geterrno()const
{
	return this->processErrno;
}
template <class __EnvInterface,typename __SizeType>
void X2fsUtil<__EnvInterface,__SizeType>::setEnvInterface(_EnvInterface *env)
{
	this->env=env;
}
template <class __EnvInterface,typename __SizeType>
void X2fsUtil<__EnvInterface,__SizeType>::seterrno(int processErrno)const
{
	this->processErrno=processErrno;
}
template <class __EnvInterface,typename __SizeType>
void X2fsUtil<__EnvInterface,__SizeType>::seterrno(int processErrno)
{
	this->processErrno=processErrno;
}

template <class __EnvInterface,typename __SizeType>
typename X2fsUtil<__EnvInterface,__SizeType>::FileNode *X2fsUtil<__EnvInterface,__SizeType>::getRootBase()const
{
		return (FileNode *)this->fileTree.getHead();
}
template <class __EnvInterface,typename __SizeType>
typename X2fsUtil<__EnvInterface,__SizeType>::FileNode *X2fsUtil<__EnvInterface,__SizeType>::getRootBase()
{
		return (FileNode *)this->fileTree.getHead();
}
template <class __EnvInterface,typename __SizeType>
bool X2fsUtil<__EnvInterface,__SizeType>::isDirectory(const FileNode *p)
{
	return p && p->getData().getType()==FileDescriptor<__SizeType>::TYPE_DIR;
}
template <class __EnvInterface,typename __SizeType>
bool X2fsUtil<__EnvInterface,__SizeType>::isFile(const FileNode *p)
{
	return p && p->getData().getType()==FileDescriptor<__SizeType>::TYPE_FILE;
}
template <class __EnvInterface,typename __SizeType>
typename X2fsUtil<__EnvInterface,__SizeType>::FileTree X2fsUtil<__EnvInterface,__SizeType>::getFileTree()
{
	return fileTree;
}

//template<template<class > class _Allocator>
//void X2fsUtil::getLinkedList(LinearSourceDescriptor* buffer,
//		LinkedList<LinearSourceDescriptor, _Allocator>& list, __SizeType maxlen) {
//}

#endif //File_h__
