

#ifndef File_h__
#define File_h__


#include <loki/Int2Type.h>
#include <64/MallocToSimple.h>
#include <def.h>
#include <MemoryManager.h>
#include <List.h>
#include <EnvInterface.h>
//#if defined(CODE64)
//#include <EnvInterface64Impl.h>  //impl for dumpInfo
//#endif
#include <conceptual/Serialize.h>
//#include <initializer_list>
//using std::initializer_list;


//==class FileDescriptor

/**
* 支持序列化
*/
class FileDescriptor:public SerializationInterface
{
public:
	enum{ TYPE_FILE=0,TYPE_DIR=1,TYPE_EAP=2};

	/**
	 * 仅仅是size_t的别名
	 */
	using size_t = HostEnv::size_t;
	using __TimeType = size_t;
public:
	AS_MACRO FileDescriptor()=default;
	AS_MACRO FileDescriptor(u8_t type,size_t sectionList,
			size_t fileLen,size_t nameStart,__TimeType createdTime,__TimeType lastModefiedTime);

	AS_MACRO u8_t getType()const;
	AS_MACRO void setType(u8_t type);

	AS_MACRO size_t getNameOffset()const;
	AS_MACRO void	setNameOffset(size_t off);
	AS_MACRO __TimeType getCreatedTime() const;
	AS_MACRO void setCreatedTime(__TimeType createdTime);
	AS_MACRO size_t getFileLen() const;
	AS_MACRO void setFileLen(size_t fileLen);
	AS_MACRO DEPRECATED size_t getFileStart() const;//file will always starts from the beginning
	AS_MACRO DEPRECATED void setFileStart(size_t fileStart);
	AS_MACRO __TimeType getLastModefiedTime() const;
	AS_MACRO void setLastModefiedTime(__TimeType lastModefiedTime);
	AS_MACRO DEPRECATED size_t getSectionSpan() const;
	AS_MACRO DEPRECATED void setSectionSpan(size_t sectionSpan);
	AS_MACRO DEPRECATED size_t getSectionStart() const;
	AS_MACRO DEPRECATED void setSectionStart(size_t sectionStart);


	AS_MACRO size_t getSectionListIndex() const ;
	AS_MACRO void setSectionListIndex(size_t	sectionListIndex);


	template <class __EnvTransfer>
		SerializerPtr<__EnvTransfer>& serialize(SerializerPtr<__EnvTransfer> &ptr)const;
	template <class __EnvTransfer>
		SerializerPtr<__EnvTransfer>& deserialize(SerializerPtr<__EnvTransfer> &ptr);
	template <class __EnvTransfer>
		constexpr size_t getSerializitionSize();
private:
	/**
	 * 类型，文件，文件夹，或者扩展区域（废弃）
	 */
	u8_t type=TYPE_FILE;

	/**
	 * 文件占据的分区链表的下标
	 */
	size_t /* DEPRECATED sectionStart,sectionSpan,*//*DEPRECATED fileStart */sectionListIndex=0;
	/**
	 * 文件长度
	 */
	size_t fileLen=0;

	/**
	 * 文件名在 name分区中的开始下标
	 */
	size_t nameStart=0;

	/**
	 * 创建时间
	 */
	__TimeType createdTime=0;

	/**
	 * 最后修改时间
	 */
	__TimeType lastModefiedTime=0;

};



//==class X2fsMetaInfo
/**
 * 从一个扇区初始化
 *
 * 注意，该结构必须在所有架构上一致，因此采用uXX_t来定义各个域
 *
 * 实现：序列化接口
 */
class X2fsMetaInfo:public SerializationInterface
{
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

		BASIC_SIZE_TYPE =  sizeof(size_t),


		INDEX_OPTIONAL_SECD=0
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

	X2fsMetaInfo()=default;



public:
	/**
	 *  记录文件系统的size_t的基本长度
	 *  注意：该域必须放在开始，以便一个位置系统读取之后能够根据第一个字节判断出该文件系统的尺寸基本类型
	 *  取值：1,2,4,...
	 */
	u8_t	basicSizeType = BASIC_SIZE_TYPE;

	// mutable因为可能通过反序列化设置
	size_t reservedSec=SECNUM_RESERVED_CONST;//2
	size_t metaSec=SECNUM_META_CONST;

	//长度必须放在上面，以便进行序列化
	u8_t len=PARTS_REQUIRED;//上面数组的长度
	/**
	 * 	name dir free file link secd
	 *
	 * 	=0表示该分区不分配。通常用于一些可选分区
	 */
	size_t secnums[PARTS_REQUIRED];

	u8_t optionalLen=PARTS_OPTIONAL;
	size_t optional[PARTS_OPTIONAL];


	/**
	 * 记录该分区的lba起始地址
	 * 与mbr中的信息重复
	 */
	u32_t lbaStartLow=0;
	u32_t lbaStartHigh=0;

	/**
	 * 记录该分区的总的扇区数
	 * 与mbr中的信息重复
	 */
	size_t wholeSecnums=0;

	u16_t	validFlag=VALID_FLAG;

public:
	/**
	 *  校验metainfo是否符合结构
	 */
	static bool checkMetainfo(const X2fsMetaInfo& info);

	//序列化接口
	template <class __EnvTransfer>
		SerializerPtr<__EnvTransfer>& serialize(SerializerPtr<__EnvTransfer> &ptr)const;
	template <class __EnvTransfer>
		SerializerPtr<__EnvTransfer>& deserialize(SerializerPtr<__EnvTransfer> &ptr);
	template <class __EnvTransfer>
		size_t getSerializitionSize();
	void dumpInfo();
//	size_t getDataAllocation
};



//************X2fsMetaInfo 定义结束

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
 *	@param __FsEnv 参见EnvTransfer
 *
 */
template <class __FsEnv>
class X2fsUtil{
public:
	using __SizeType = HostEnv::size_t;
	// DEPRECATED  对齐因为序列化技术提出，已经过时
//	enum{ __FsAlignment =  __FsEnv::Alignment};
	using __X2fsMetaInfo = X2fsMetaInfo;
	using __SerializerPtr = SerializerPtr<__FsEnv>;

public:
	enum{
		// 顺序一致
		INDEX_NAME=__X2fsMetaInfo::INDEX_NAME,
		INDEX_DIR=__X2fsMetaInfo::INDEX_DIR,
		INDEX_FREE=__X2fsMetaInfo::INDEX_FREE,
		INDEX_LINK=__X2fsMetaInfo::INDEX_LINK,
		INDEX_OPTIONAL_SECD=__X2fsMetaInfo::INDEX_OPTIONAL_SECD,
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


	using This = X2fsUtil<__FsEnv>;
	using __X2fsUtil = This;

	using __TreeNode_MemoryDescriptor = TreeNode<MemoryDescriptor>;
	using __LinearSourceDescriptor = LinearSourceDescriptor;
	using __ListNode_LinearSourceDescriptor = ListNode<__LinearSourceDescriptor>;
	using __FileDescriptor = FileDescriptor;
	using __TimeType = typename __FileDescriptor::__TimeType;
	using __TreeNode_FileDescriptor = TreeNode<__FileDescriptor>;
	/**
	 * 依赖这些类型作为分配器
	 */
	using TMSmm = MallocToSimple<__TreeNode_MemoryDescriptor>;
	using LLSmm = MallocToSimple<__ListNode_LinearSourceDescriptor>;

	template <class T>
			using __SimpleAssociated = AssociatedMemoryManager<T,1>;
	// DEPRECATED 启用SimpleMemoryManager
//	using FileNodeMM = SimpleMemoryManager<__FsTreeNode_FileDescriptor>;
	using FileNodeMM = __SimpleAssociated<__TreeNode_FileDescriptor>;
	using FileNameMM = MemoryManager<MallocToSimple>;
	using FileNode = typename FileNodeMM::TargetType;

	using FileTree = Tree<__FileDescriptor,__SimpleAssociated>;
	using FreeSpaceMM = LinearSourceManager<__LinearSourceDescriptor,
			MallocToSimple>;
	using LinkedInfoMM = LinearSourceManager<__LinearSourceDescriptor,
			MallocToSimple>;

	enum{
		FileNodeSize=sizeof(FileNode) + sizeof(SimpleMemoryNode)
	};
public:
	X2fsUtil()=default;
	X2fsUtil(const __X2fsUtil &)=delete;
	__X2fsUtil& operator=(const __X2fsUtil &)=delete;
	/**
	 * 两种初始化情况：
	 * 	1.需要从驱动器上读取数据，分配缓冲区，然后初始化
	 * 	2.已经准备完备所有缓冲区，数据已经读入，初始化
	 *
	 * 	metainfo 初始化完毕就可以开始读取了
	 */
	X2fsUtil(u8_t driver,u32_t lbaBase);
	X2fsUtil(u8_t driver,const __X2fsMetaInfo &metainfo,u8_t *buffers[]);
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
	bool move(int argcSrc,const char *argvSrc[],int argcDst,const char *argvDst[],const char *newname=nullptr);
	void dumpFileInfo(int argc,const char *argv[]);
	/**
	 * if exist return PATH_XXX,else return ERROR_XXX
	 */
	int	 tellType(int argc,const char * argv[])const;
	void listNode(int argc,const char * argv[],int maxdeepth=1)const;

	DEPRECATED __SizeType writeToFile(const char *buf,__SizeType objsize,__SizeType nobj,int argc,const char *argv[],__SizeType foff=0);
	DEPRECATED __SizeType rsize_tmFile(char *buf,__SizeType objsize, __SizeType nobj,int argc,const char *argv[],FileNode *fnode,__SizeType foff=0);

	void listRoot()const;
	void listNode(const FileNode* p)const;
	/**
	 * 先将散布在内存中的信息写入缓冲区
	 * 再将缓冲区中的内容写入到磁盘
	 */
	void flush();//write the buffered content back to file
	AS_MACRO int geterrno()const;

public:
	char *getFileNameCstr(const __FileDescriptor &fd,__SizeType &nlen)const;
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

	// UNTESTED
	void removeNode(FileNode *node);//remove is necessary only at the connected node(with this tree)

	// UNTESTED
	bool deleteFile(FileNode* fnode);
	bool rename(FileNode *node,const char *newname);
	bool move(FileNode *p,FileNode* dstDir,const char *newname=nullptr);
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
	 * @return nullptr to indicate failure
	 */
	FileNode * locatePath(FileNode *base,const char *name)const;
	FileNode * getPathParentNode(int argc,const char * argv[])const;
	FileNode * getPathNode(int argc,const char * argv[])const;
//	INCOMPLETE FileNode * locatePath(FileNode *base,int argc,const char *argv[],int &errorLevel);
//	INCOMPLETE FileNode * locatePath(FileNode *base,const char *name);

	/**
	 *  DEPRECATED 已经弃用，使用_writeToFile替代
	 * @param buf 源数据区
	 * @param objsize 源数据区中每个数据的大小
	 * @param nobj   要写的数据个数，nobj*objsize就是要写的总字节数
	 * @param fnode		文件节点
	 * @param	foff	写到文件的偏移位置
	 */
//	INCOMPLETE
	DEPRECATED __SizeType writeToFile(const char *buf,__SizeType objsize, __SizeType nobj,FileNode *fnode,__SizeType foff=0);

	// UNTESTED
	/**
	 * 从startILink处开始查找off的ilink位置
	 * 前置条件：startILink指向一个有效的ilink位置，它的末端必须有(0,0)结尾，startILink增加不会到达linkarrLen
	 *
	 * @param secPos  相对于startILink需要定位的偏移量,这个待定位的位置是可以访问的
	 * @param retOff   如果找到这个ilink，则同时设置这个值表明距离此ilink区间的开始处偏移;
	 * 				如果没有找到，则retOff存放最后一个非0 ilink的剩余的secPos偏移量
	 * 				如果retOff=0,表示恰好能够定位到第一个不可到达的字节
	 * @return
	 * 		  最后一个查找的ilink; 如果此ilink 长度(limit)为0，则表明空间不足以定位到该处；此时ilink就是最后一个起始分区
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
	 * 扩展文件实际占用的扇区数目
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

	// TODO 添加完整文档注释
	/**
	 * 实现相对于文件的随机位置扇区的读写
	 * @param updateFileLen 当文件长度不足时，是否更新文件的长度
	 */
	__SizeType _writeToFile(const char *buf, __SizeType nsec,FileNode *fnode,__SizeType secPos=0,
			bool updateFileLen=true);
	__SizeType _readFromFile(char *buf,__SizeType nsec,FileNode *fnode,__SizeType secPos=0);
	/** UNTESTED
	 * 对文件进行按字节随机写
	 * 前置条件：buf是扇区的整数倍, byteStart%CONST_SIZE是相对于buf的开始
	 * 后置条件：如果所写的长度超过文件原始长度，则更新文件长度
	 * @param buf 数据源，长度至少为 byteStart % CONST_SIZE + nbyte; 注意，由于可能修改buf数据源，所以不能传递const
	 * @param nbyte 要写的长度
	 * @param fnode  要写的文件节点
	 * @param byteStart 偏移地址
	 *
	 * @return 实际写入的字节数目
	 */
	__SizeType _randomWriteFile(char *buf, __SizeType nbyte,FileNode *fnode,__SizeType byteStart=0);
	/** UNTESTED
	 * 条件同上
	 * 此函数的实现不需要补齐，返回值的buf+(byteStart%CONST_SECSIZE)为有效数据
	 */
	__SizeType _randomReadFile(char *buf, __SizeType nbyte,FileNode *fnode,__SizeType byteStart=0);


	/** INCOMPLETE
	 * 减小或增加文件长度,取决于给定长度与原始文件长度的关系
	 * 前置条件：
	 * 后置条件：newlen如果小于2*CONST_SECSIZE，则返回false，不可完成
	 * @param newlen 新长度
	 *
	 * @return 成功返回true，其他错误返回false
	 */
	bool truncateFile(FileNode *fnode,__SizeType newlen);

	// EFF 使用自动管理的数组效果更佳
	/**
	 * 基于字节的随机位置读写
	 * 长度会扩展
	 */
	DEPRECATED __SizeType randomWriteFile(const char *buf, __SizeType nbyte,FileNode *fnode,__SizeType byteStart=0);
	/**
	 * 长度可能不足以读取，返回实际读取的长度
	 */
	DEPRECATED __SizeType randomReadFile(char *buf,__SizeType nbyte,FileNode *fnode,__SizeType byteStart=0);

	/**
	 * 实现连续多个扇区的随机读写
	 * TODO:应当使用vector来替代char，这样就无需手动管理内存了
	 *
	 */
	DEPRECATED __SizeType randomReadSector(char *buf,__SizeType nbyte,__SizeType bytePos);
	DEPRECATED __SizeType randomWriteSector(const char *buf,__SizeType nbyte,__SizeType bytePos);
	/**
	 * 随机读写一个扇区
	 * 前置条件： 0<=byteStart<byteEnd<=CONST_SECSIZE;
	 * @param buf  数据源,至少有CONST_SECSIZE - bytePos的大小
	 * @param secPos  要写的扇区
	 * @param byteStart 起始位置
	 * @param byteEnd    结束位置,注意：使用的是闭区间形式，[byteStart,byteEnd)
	 * @param optBuffer 一个用于暂存数据的buffer，如果为nullptr，函数会自己申请一个；其中的数据会改变
	 *
	 * @return 成功返回true，失败返回false
	 */
	DEPRECATED bool randomWriteOneUnit(const char *buf,__SizeType secPos,__SizeType byteStart,
			__SizeType byteEnd,char *optBuffer=nullptr);
	DEPRECATED bool randomReadOneUnit(char *buf,__SizeType secPos,__SizeType byteStart,
			__SizeType byteEnd,char *optBuffer=nullptr);

	/**
	 *
	 */
	DEPRECATED bool randomWriteFileOneUnit(const char *buf,
			FileNode *fnode,
			__SizeType secPos,
			__SizeType byteStart,
			__SizeType byteEnd,char *optBuffer=nullptr);


	DEPRECATED __SizeType readFromFile(char *buf,__SizeType objsize, __SizeType nobj,FileNode *fnode,__SizeType foff=0);
	AS_MACRO void seterrno(int processErrno)const;
	AS_MACRO void seterrno(int processErrno);
	AS_MACRO FileNode * getRootBase()const;
	AS_MACRO FileNode * getRootBase();
	AS_MACRO static bool isDirectory(const FileNode *p);
	AS_MACRO static bool isFile(const FileNode *p);

	/**
	 * 根据metainfo和磁盘信息，建立一个有效的空分区
	 * @param env				主机环境
	 * @param driver			主机上的磁盘
	 * @param metainfo			目标区域的metainfo
	 */
	static void mkfs(u8_t driver,const __X2fsMetaInfo  &metainfo);

//	template <template <class>class _Allocator>
//	INCOMPLETE static void getLinkedList(__LinearSourceDescriptor *buffer,
//			__SizeType i,LinkedList<LinearSourceDescriptor<__SizeType>,_Allocator> &list,__SizeType maxlen);

	DEPRECATED static void createFile_old(void *base,const char* name,__SizeType secNum);//default length=0,start=0,span=secNum

	AS_MACRO FileTree* getFileTree();

	/**
	 * 根据此磁盘一次读写的单位来计算随机读写所需的buffer大小，该大小是unit的整数倍
	 * 通过该函数，可以将对磁盘字节的随机读写变换成按磁盘单位（扇区）的读写
	 * @param startByte  开始位置
	 * @param numbyte    字节数量
	 * @param startDiff  返回值，设置start的距离开始的偏移，范围[0,unit); nullptr不设置
	 * @param endDiff    返回值,设置end的距离末尾的偏移，范围[0,unit); nullptr不设置
	 * @param unit		单元大小
	 *
	 * @return 返回所需的buffer数量，是unit的整数倍，以byte为单位
	 */
	static __SizeType calculateRandomBufferSize(__SizeType startByte,__SizeType numebyte,
			__SizeType *startDiff=nullptr,
			__SizeType *endDiff=nullptr,
			__SizeType unit=CONST_SECSIZE);



protected:
		DEPRECATED void initBuffers();

		/**
		 * 这真是一个bug， 因为指针偏移在64位系统下不能仅仅使用int存放，所以导致出错。
		 * 调试了半天。。。
		 */
		// old version ---> void adjustDirbufOffset(int off);//positive or negative
		DEPRECATED void adjustDirbufOffset(ptrdiff_t off);


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

private:
	/**
	 *  DEPRECATED  现在统一使用命名空间HostEnv
	 * 要求操作系统实现提供的功能集
	 */
//	__EnvInterface &env;
	/**
	 * 驱动器号，在有的操作系统上，可能将驱动器号映射成文件
	 */
	u8_t	driver{};

	/**
	 * 元信息区域
	 */
	u8_t * metainfoRAW{};
	__X2fsMetaInfo metainfo{};

	/**
	 *  buffers[INDEX_NAME]  文件名区域。直接操纵
	 *	buffers[INDEX_FREE]  该区的开始位置存放两个节点，节点0描述了总体的信息(数据区开始，长度），节点1是(0,0)
	 * 						其中数据区开始是相对于该文件分区的起点，如果文件有10个用于元信息的区域，则开始就是10，以扇区为单位
	 * 						所有的数据以(0,0)结尾
	 * 	buffers[INDEX_LINK]  间接操纵，布局：
	 * 	buffers[INDEX_DIR]   间接操纵，布局：dirsmm  FileNode*N  SMMNode*N,  需要序列化
	 */
	u8_t *buffersRAW[__X2fsMetaInfo::PARTS_REQUIRED];
	/**
	 * 存放buffers[INDEX_DIR]的反序列化对象，用于内存直接操作。
	 */
	u8_t *buffersDir{};

	/** DEPRECATED
	 * 将link分区看成是一个LineaerSourceDescriptor数组
	 * 每一个元素描述了文件的分配情况，文件占据多个不连续的扇区，这些扇区由下面链表描述
	 */

	/**
	 * 描述文件的占用的扇区信息，文件中的保存起始下标
	 * 文件占用的扇区不连续，可能如下： (2,3)-->(7,2)-->(0,0) 表示文件占用2扇区开始的3个扇区，7扇区开始的2个扇区
	 * 该数组实际上是freespace分区的别名，也就是说linkarr的首地址指向了内存中freespace分区的开始
	 *
	 *  UPDATE:使用Vector自动内存管理
	 *
	 */
	HostEnv::Vector<__LinearSourceDescriptor> linkarr{};



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


	TMSmm mmnodesmm{};
	/**
	 * 管理文件名的MemoryManager
	 *
	 * 可以根据文件名区重建，不需要序列化
	 */
	FileNameMM filenamemm;

	/**
	 * 为linkmm，分配管理节点
	 */
	LLSmm listnodesmm{};


	/**
	 * 管理节点区域的SMM，管理类型为TreeNode<FileDescriptor>
	 * 用于分配树节点
	 * 此管理器管理的区域是buffers[INDEX_DIR]
	 */
	FileNodeMM dirsmm{};

	/**
	 * 一棵树，其全部分配的节点在dirsmm中
	 */
	FileTree fileTree{};

	/**
	 * 一个数值区间管理器，初始数值区间是  [数据区开始，数据区开始+数据区长度)
	 * 对于这种管理器，我们只应当将其认为是标记一系列的数值
	 * 当我们从中分配了一段字区间后，相应的认为磁盘上这些区间已经分配了。
	 * 对文件的分配使得这段被分配的区间被加入到该文件linkarr的数组中
	 *
	 * 管理freespace空闲空间的信息，链表实现
	 * 当分配空间后，该段空间就从链表中取消
	 *
	 * 可以被决定安全地反序列化，只要设置了smm即可
	 */
	FreeSpaceMM freemm{};


	/**
	 * 一个数值管理器，标记linkarr中可用的下标
	 * 该管理器管理一个数组linkarr，管理范围是[0,0+linarrLen)
	 * 使用listnodesmm作为节点分配器，在retriveLinkeInfoSection()方法中初始化
	 *
	 */
	LinkedInfoMM linkmm{};


	/**
	 * 存放错误信息
	 */
	mutable int processErrno{};/*can be used in both const & non-const method*/

//	/** DEPRECATED 不再加载可选分区
//	 * 二级加载器是否载入
//	 */
//	bool secdLoaded;

};



/**
 *  TODO 更新帮助下面的注释
 *  属性：一个表示状态的当前目录，上一个目录
 *  方法：help ls cd rm mkdir touch cat pwd plwd(-last-)
 */
template <class __FsEnv>
class FileOperation{
public:

	//===类型别名
	using This = FileOperation<__FsEnv>;
    using __FileOperation =This;
	using __SizeType = HostEnv::size_t;
	using __X2fsUtil  = X2fsUtil<__FsEnv>;
	using FileNode = typename __X2fsUtil::FileNode;
	using __FileDescriptor = typename __X2fsUtil::__FileDescriptor;
	using __FsTimeType = typename __FileDescriptor::__TimeType;

	//===============接口约束

	template <class T>
		using __Vector = typename  HostEnv::template Vector <T>;
	using __String = HostEnv::String;

	using __Vector_String =__Vector<__String>;
	using __Vector_String_cit = typename __Vector_String::const_iterator;// cit = const_iterator
	// 需要提供名为spaceSplit的函数，原型如下；完成以空格分隔字符串的功能
	using FunType_SpaceSplit = __Vector_String (*)(const __String&); //声明一个函数


public:
	FileOperation()=default;
    FileOperation(const __FileOperation &)= default;
    __FileOperation  &operator=(const __FileOperation&)= default;
	DEPRECATED FileOperation(const __String& img)=delete;
	/**
	 * @param env  标准环境
	 * @param driver 磁盘驱动器号，在64位系统上可能映射为文件
	 * @param lbaAddress  分区的位置
	 */
	FileOperation(u8_t driver,u32_t lbaAddress);
	~FileOperation();

	/**
	 * 显示help内容
	 */
	void help();
	/**
	 * 显示当前目录下的内容
	 */
	void ls();
	/**
	 * 一般cd命令，如果出错则打印错误信息，设置错误代码（如果有）
	 *
	 * 支持多种模式，参数可以是一个，也可以是多个
	 * @return
	 */
	bool cd(const __String& strPath);

	/**
	 * cd XXX, 从当前目录下开始
	 *
	 * 注意，path数组可以含有特殊含义的目录，比如 ., .., 它们不会被当做一般的目录名称处理
	 */
	bool cdFromCur(__Vector_String_cit begin,__Vector_String_cit end);

	/**
	 * cd -的函数
	 */
	bool cdLast();
	/**
	 * cd ..的函数
	 */
	void cdBack();

	/**
	 *  cd /
	 */
	void cdRoot();
	/**
	 * 删除由名称指定的文件或目录
	 */
	void rm(const __String & fname);
	/**
	 *  创建文件夹
	 *  @param dir  a simple,1-level dirname,such as 'foo',but not 'foo/bar'
	 */
	void mkdir(const __String & dir);
	/**
	 * 创建文件，指定大小和时间，内容为空
	 */
	void touch(const __String & fname,__SizeType secNum,__FsTimeType ctime);
	/**
	 * 尚未实现，使用read
	 */
	void cat();
	/**
	 * 打印当前目录
	 */
	void pwd();

	/**
	 * 切换到另一个磁盘上，不再使用
	 */
	DEPRECATED void changeImage(const __String& img);//change to another disk

//	DEPRECATED
	const __String& curDir();

	/**
	 * read并打印出来
	 */
	void read(const __String& fname,__SizeType secStart,__SizeType byteLen);
	/**
	 * TODO 创建文件，不存在的
	 * 如果文件不存在，则创建
	 */
	void write(const __String& fname,__SizeType start,const char* content,__SizeType len);


	/**
	 * 按字节随机写文件
	 */
	void randwrite(const __String& fname,__SizeType byteStart,const char* content,__SizeType byteLen);
	void randread(const __String& fname,__SizeType byteStart,__SizeType byteLen);

	/**
	 * 截断文件长度
	 */
	void truncate(const __String & fname,__SizeType newlen);
	/**
	 * @return true继续，false退出
	 */
	bool eval(const __String &cmd);

#if defined(CODE64)
	/** UNTESTED
	 *  与系统文件进行交互
	 *
	 *  @param maxLen 最大长度，如果设置成0，则表示读取sysFile的剩余长度
	 */
	__SizeType readSysFileToX2File(const __String &sysFile,__SizeType sysStart,
								const __String &x2File,__SizeType x2Start,
								__SizeType maxLen);
	/** UNTESTED
	 * @param maxLen 最大长度，如果设为0，则表示读取x2File的剩余长度
	 */
	__SizeType writeSysFileFromX2File(const __String &sysFile,__SizeType sysStart,
								const __String &x2File,__SizeType x2Start,
								__SizeType maxLen);
#endif

	bool checkIsFile(const __String & fname,FileNode *&fnode)const;
	bool checkIsDir(const __String & fname,FileNode *&fnode)const;
	bool checkExits(const __String & fname,FileNode *&fnode)const;
	void errorFileNotExits(const __String & fname)const;
	void errorNotAFile(const __String & fname)const;
	void errorNotADir(const __String &fname)const;
private:
	/**
	 * 辅助函数，用于同步curNode和curPath的内容
	 */
	void refreshCurrentPath();

private://成员
	/**
	 * 用于操作文件系统的实用工具类
	 */
	__X2fsUtil util{};

	FileNode *curNode{nullptr};
	/**
	 *  当lastNode为nullptr时，表明没有上一个目录
	 */
	FileNode *lastNode{nullptr};

	/**
	 * 当前的路径数组
	 */
	__Vector_String curPath{};

};

/**
 * 管理一个唯一的已分配对象
 * 如果重复请求，则总是返回第一次分配的对象
 */
template <typename T>
class ManagedObject{ // 在析构函数时自动调用，相当于unique_ptr
public:
	using This = ManagedObject<T>;
	using __ManagedObject = This;
	using __SizeType = HostEnv::size_t;


	explicit ManagedObject();
    ManagedObject(const __ManagedObject &)=default;
    ManagedObject & operator=(const __ManagedObject &)=default;
	~ManagedObject();
	void setBufferIfNone(T buffer);
	T	 getOnlyBuffer()const;
	T    getOnlyBuffer(__SizeType size);
	/**
	 * 返回一个常量引用
	 * 防止对其指向进行修改
	 */
	const T&    getOnlyBufferReference(__SizeType size)const;

    bool operator==(const __ManagedObject &rhs) const;

    bool operator!=(const __ManagedObject &rhs) const;

private:
	mutable T buffer;
};



//=============Function Macros
//=====class : FileDescriptor
#define __DEF_Template_FileDescriptor
#define __DEF_FileDescriptor FileDescriptor

__DEF_Template_FileDescriptor
__DEF_FileDescriptor::FileDescriptor(u8_t type,size_t sectionList,size_t fileLen,size_t nameStart,
		__TimeType createdTime,__TimeType lastModefiedTime):
type(type),sectionListIndex(sectionList),fileLen(fileLen),
nameStart(nameStart),createdTime(createdTime),lastModefiedTime(lastModefiedTime)
{
}

__DEF_Template_FileDescriptor
typename __DEF_FileDescriptor::__TimeType __DEF_FileDescriptor::getCreatedTime() const
{
	return createdTime;
}

__DEF_Template_FileDescriptor
void __DEF_FileDescriptor::setCreatedTime(__TimeType createdTime) {
	this->createdTime = createdTime;
}

__DEF_Template_FileDescriptor
typename __DEF_FileDescriptor::size_t __DEF_FileDescriptor::getFileLen() const {
	return fileLen;
}

__DEF_Template_FileDescriptor
void __DEF_FileDescriptor::setFileLen(size_t fileLen) {
	this->fileLen = fileLen;
}

__DEF_Template_FileDescriptor
typename __DEF_FileDescriptor::__TimeType __DEF_FileDescriptor::getLastModefiedTime() const {
	return lastModefiedTime;
}
__DEF_Template_FileDescriptor
void __DEF_FileDescriptor::setLastModefiedTime(__TimeType lastModefiedTime) {
	this->lastModefiedTime = lastModefiedTime;
}
__DEF_Template_FileDescriptor
typename __DEF_FileDescriptor::size_t __DEF_FileDescriptor::getSectionListIndex() const
{
	return this->sectionListIndex;
}

__DEF_Template_FileDescriptor
void __DEF_FileDescriptor::setSectionListIndex(size_t	sectionListIndex)
{
	this->sectionListIndex = sectionListIndex;
}

__DEF_Template_FileDescriptor
template <class __EnvTransfer>
constexpr size_t __DEF_FileDescriptor::getSerializitionSize()
{
	// DEPRECATED Old code: call through funcion-like class .
//	using u8size=typename __EnvTransfer::template SizeofHostType<u8_t>;
//	using SizeTypeSize = typename __EnvTransfer::template SizeofHostType<size_t>;
//	using TimetypeSize = typename __EnvTransfer::template SizeofHostType<__TimeType>;
//	return u8size::Size + SizeTypeSize::Size*3 + TimetypeSize::Size*2;


	return __EnvTransfer::template sizeofHostType<decltype(this->type)>()+
			__EnvTransfer::template sizeofHostType<decltype(this->sectionListIndex)>()+
			__EnvTransfer::template sizeofHostType<decltype(this->fileLen)>()+
			__EnvTransfer::template sizeofHostType<decltype(this->nameStart)>()+
			__EnvTransfer::template sizeofHostType<decltype(this->createdTime)>()+
			__EnvTransfer::template sizeofHostType<decltype(this->lastModefiedTime)>();
}

__DEF_Template_FileDescriptor
u8_t __DEF_FileDescriptor::getType() const {
	return type;
}
__DEF_Template_FileDescriptor
void __DEF_FileDescriptor::setType(u8_t type) {
	this->type = type;
}

__DEF_Template_FileDescriptor
typename __DEF_FileDescriptor::size_t __DEF_FileDescriptor::getNameOffset()const
{
	return this->nameStart;
}
__DEF_Template_FileDescriptor
void __DEF_FileDescriptor::setNameOffset(size_t off)
{
	this->nameStart=off;
}
#undef __DEF_Template_FileDescriptor
#undef __DEF_FileDescriptor



//=========class X2fsUtil
#define __DEF_X2fsUtil_Template template <class __FsEnv>
#define __DEF_X2fsUtil X2fsUtil<__FsEnv>
__DEF_X2fsUtil_Template
int __DEF_X2fsUtil::geterrno()const
{
	return this->processErrno;
}
__DEF_X2fsUtil_Template
void __DEF_X2fsUtil::seterrno(int processErrno)const
{
	this->processErrno=processErrno;
}
__DEF_X2fsUtil_Template
void __DEF_X2fsUtil::seterrno(int processErrno)
{
	this->processErrno=processErrno;
}

__DEF_X2fsUtil_Template
typename __DEF_X2fsUtil::FileNode *__DEF_X2fsUtil::getRootBase()const
{
		return static_cast<FileNode *>(this->fileTree.getHead());
}
__DEF_X2fsUtil_Template
typename __DEF_X2fsUtil::FileNode *__DEF_X2fsUtil::getRootBase()
{
		return static_cast<FileNode *>(this->fileTree.getHead());
}
__DEF_X2fsUtil_Template
bool __DEF_X2fsUtil::isDirectory(const FileNode *p)
{
	return p && p->getData().getType()==__FileDescriptor::TYPE_DIR;
}
__DEF_X2fsUtil_Template
bool __DEF_X2fsUtil::isFile(const FileNode *p)
{
	return p && p->getData().getType()==__FileDescriptor::TYPE_FILE;
}
__DEF_X2fsUtil_Template
typename __DEF_X2fsUtil::FileTree* __DEF_X2fsUtil::getFileTree()
{
	return &fileTree;
}
#undef __DEF_X2fsUtil_Template
#undef __DEF_X2fsUtil

//template<template<class > class _Allocator>
//void X2fsUtil::getLinkedList(LinearSourceDescriptor* buffer,
//		LinkedList<LinearSourceDescriptor, _Allocator>& list, size_t maxlen) {
//}


#endif //File_h__
