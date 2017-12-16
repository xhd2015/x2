

#ifndef File_h__
#define File_h__


#include <conceptual/loki/Int2Type.h>
#include <64/MallocToSimple.h>
#include <def.h>
#include <MemoryManager.h>
#include <List.h>
#include <EnvInterface.h>
#include <cassert>
//#if defined(CODE64)
//#include <EnvInterface64Impl.h>  //impl for dumpInfo
//#endif
#include <conceptual/Serialize.h>
//#include <initializer_list>
//using std::initializer_list;


//==class FileDescriptorBase
/**
 * 可默认初始化
 * 实现：序列化接口
 */
template <class __FsEnv = EnvTransfer<HOST_BIT>>
class BaseDescriptor:public SerializationInterface{
	public:
		using This = BaseDescriptor<__FsEnv>;
		using __BaseDescriptor = This;
		using Super = void ; //kidding? no, I do not have a super,but an interface
	public:
		/**
		 * 用于记录动态类型的域
		 */
		using ClassSerializeType = u8_t;
		enum FileType{ TYPE_FILE=0,TYPE_DIR=1,TYPE_EAP=2};

		using __TimeType = size_t;
		using __SizeType = size_t;
	protected:// 不允许构造一个不完整的Descriptor
		AS_MACRO BaseDescriptor()=default;
		AS_MACRO BaseDescriptor(const HostEnv::String& name,__TimeType createdTime,__TimeType lastModefiedTime):
						name(name),createdTime(createdTime),lastModefiedTime(lastModefiedTime) {}
		AS_MACRO BaseDescriptor(HostEnv::String&& name,__TimeType createdTime,__TimeType lastModefiedTime):
								name(std::move(name)),createdTime(createdTime),lastModefiedTime(lastModefiedTime) {}
		BaseDescriptor(const __BaseDescriptor &bd)=default;
		__BaseDescriptor &operator=(const __BaseDescriptor &bd)=default;
		BaseDescriptor(BaseDescriptor &&)=default;
		__BaseDescriptor &operator=(__BaseDescriptor &&)=default;

		explicit BaseDescriptor(SerializerPtr<__FsEnv> & ptr)
		{
			this->This::deserialize(ptr);//在构造函数中，只有this只有基类类型
		}
	public:

		virtual ~BaseDescriptor()=default;


		virtual FileType getType()const = 0;

		AS_MACRO const HostEnv::String& getName()const { return  name;}
		AS_MACRO void				setName(const HostEnv::String& name) { this->name=name;}
		AS_MACRO void				setName(HostEnv::String && name){this->name = std::move(name);}
		AS_MACRO __TimeType getCreatedTime() const{return createdTime;}
		AS_MACRO void setCreatedTime(__TimeType createdTime) { this->createdTime = createdTime;}
		AS_MACRO __TimeType getLastModefiedTime() const{return lastModefiedTime;}
		AS_MACRO void setLastModefiedTime(__TimeType lastModefiedTime){this->lastModefiedTime = lastModefiedTime;}
public:
		//FsEnv只与序列化这一部分有关
		/**
		 * 序列化方案：此处仅仅是序列化的子过程调用dynamic_cast进行转换
		 *
		 */
		virtual SerializerPtr<__FsEnv>& serialize(SerializerPtr<__FsEnv> &ptr)const
			{
				return ptr << name << createdTime << lastModefiedTime;
			}
		virtual SerializerPtr<__FsEnv>& deserialize(SerializerPtr<__FsEnv> &ptr)
			{
				return ptr >> name >> createdTime >> lastModefiedTime;
			}
		virtual size_t getSerializitionSize()const
		{
			return ::getSerializitionSize<__FsEnv>(name) +
					::getSerializitionSize<__FsEnv,decltype(createdTime)>()+
					::getSerializitionSize<__FsEnv,decltype(lastModefiedTime)>();
		}
		/**
		 * 全局operator<<会根据此方法的返回进行选择
		 */
		static constexpr GlobalCallPolicy callPolicy(){
			return CALL_GLOBAL_HELPER;
		}
	private:
		HostEnv::String name{};//name 其实必须初始化

		/**
		 * 创建时间
		 */
		__TimeType createdTime=0;

		/**
		 * 最后修改时间
		 */
		__TimeType lastModefiedTime=0;
	};


template <class __FsEnv>
class DirDescriptor:public BaseDescriptor<__FsEnv>{ //无需改写任何东西
private:
	using This = DirDescriptor;
	using Super = BaseDescriptor<__FsEnv>;
public:
	using FileType = typename Super::FileType;
	using __TimeType = typename Super::__TimeType;
	using __SizeType = typename Super::__SizeType;

	AS_MACRO DirDescriptor(const HostEnv::String& name,__TimeType createdTime,__TimeType lastModefiedTime):
						Super(name,createdTime,lastModefiedTime) {}
	AS_MACRO DirDescriptor(HostEnv::String&& name,__TimeType createdTime,__TimeType lastModefiedTime):
		Super(std::move(name),createdTime,lastModefiedTime){}
	AS_MACRO DirDescriptor()=default;
	explicit DirDescriptor(SerializerPtr<__FsEnv> & ptr)
	{
		this->This::deserialize(ptr);//在构造函数中，只有this只有基类类型
	}

	virtual ~DirDescriptor()=default;
	virtual FileType getType()const
	{
		return FileType::TYPE_DIR;
	}
};
template <class __FsEnv>
class FileDescriptor:public BaseDescriptor<__FsEnv>{
private:
	using This = FileDescriptor;
	using Super = BaseDescriptor<__FsEnv>;
public:
	using FileType = typename Super::FileType;
	using __TimeType = typename Super::__TimeType;
	using __SizeType = typename Super::__SizeType;
	AS_MACRO FileDescriptor()=default;
	virtual ~FileDescriptor()=default;
	FileDescriptor(const HostEnv::String& name,__TimeType createdTime,__TimeType lastModefiedTime,__SizeType fileLen):Super(name,createdTime,lastModefiedTime),fileLen(fileLen){}
	explicit FileDescriptor(SerializerPtr<__FsEnv> & ptr)
	{
		this->This::deserialize(ptr);
	}

	virtual FileType getType()const
	{
		return FileType::TYPE_FILE;
	}
	AS_MACRO size_t getFileLen() const { return fileLen;}
	AS_MACRO void setFileLen(size_t fileLen) { this->fileLen = fileLen;}
	void addSpace(const LinearSourceDescriptor &lsd)
	{
		this->spaces.push_back(lsd);
	}
	void popSpace()
	{
		this->spaces.pop_back();
	}

	const LinearSourceDescriptor & getSpace(size_t i)const
	{
		return this->spaces[i];
	}
	size_t getSpaceListSize()const
	{
		return this->spaces.size();
	}
	const HostEnv::Vector<LinearSourceDescriptor> & getSpaces()const
	{
		return spaces;
	}

	virtual SerializerPtr<__FsEnv>& serialize(SerializerPtr<__FsEnv> &ptr)const
	{
		return this->Super::serialize(ptr) << fileLen << spaces;
	}

	virtual SerializerPtr<__FsEnv>& deserialize(SerializerPtr<__FsEnv> &ptr)
	{
		return this->Super::deserialize(ptr) >>  fileLen >> spaces;
	}

	virtual size_t getSerializitionSize()const
	{
		return this->Super::getSerializitionSize() +
				::getSerializitionSize<__FsEnv,decltype(fileLen)>() +
				::getSerializitionSize<__FsEnv>(spaces);
	}

private:
	/**
	 * 文件长度，字节为单位
	 */
	size_t fileLen = 0;
	/**
	 * 占据的空间分区信息，可以不连续
	 */
	HostEnv::Vector<LinearSourceDescriptor> spaces {};
};



/**
 * 使用全局静态函数，这种情况下，原来的operator<<,operator>>需要进行一定程度的改写，指针版本。
 * 只有指针情况下需要使用policy
 * 如果有此静态方法，应当优先调用
 */
template <class __EnvTransfer>
SerializerPtr<__EnvTransfer>& serialize(SerializerPtr<__EnvTransfer> &ptr,
			const BaseDescriptor<__EnvTransfer> * pfile)
{
	ptr << static_cast<typename BaseDescriptor<__EnvTransfer>::ClassSerializeType>(pfile->getType()); //先写 type类型，然后调用其自身的序列化函数
	return pfile->serialize(ptr);
}
/**
 * 前置条件： pfile==nullptr，否则，pfile原来的对象被重置
 * @return pfile指向已经反序列化的对象
 * 如果类型未知,或者分配空间失败，抛出异常
 */
template <class __EnvTransfer>
SerializerPtr<__EnvTransfer>&  deserialize(SerializerPtr<__EnvTransfer> &ptr,
		BaseDescriptor<__EnvTransfer> * &pfile)
{
	typename BaseDescriptor<__EnvTransfer>::ClassSerializeType type;
	ptr >> type; //读取type
	if(type == BaseDescriptor<__EnvTransfer>::TYPE_FILE) //file
	{
		pfile = new FileDescriptor<__EnvTransfer>();

//				static_cast<>(HostEnv::mallocThrows(sizeof(FileDescriptor<__EnvTransfer>)));
		//注意：只能使用static,reinterpret可能导致指针没有正常转换。
		// 并未初始化，vtable表不正确
	}else if(type == BaseDescriptor<__EnvTransfer>::TYPE_DIR){
		pfile = new DirDescriptor<__EnvTransfer>();
//		pfile = static_cast<DirDescriptor<__EnvTransfer>*>(HostEnv::mallocThrows(sizeof(DirDescriptor<__EnvTransfer>))); //
	}else{ //未知类型，抛出异常
		HostEnv::systemAbort("deserialize unknow type", -2);
	}
	return pfile->deserialize(ptr);
}
template <class __EnvTransfer>
size_t getSerializitionSize(BaseDescriptor<__EnvTransfer> * const &pfile)
{
	return ::getSerializitionSize<__EnvTransfer,typename BaseDescriptor<__EnvTransfer>::ClassSerializeType>() +
			pfile->getSerializitionSize();
}
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

	enum {
		SECNUM_RESERVED_CONST=25,
		SECNUM_META_CONST=40, // 200个节点的规模，每个节点100b，大约是40个扇区
		VALID_FLAG=0xaa55,

		BASIC_SIZE_TYPE =  sizeof(size_t),
	};
	enum{SecSize=512,KiB=2*SecSize,MiB=1024*KiB,GiB=1024*MiB};
	X2fsMetaInfo()=default;

    X2fsMetaInfo(u32_t lbaBaseLow, u32_t lbaBaseHigh,
    				size_t wholeSecnums = 10 + SECNUM_META_CONST +  SECNUM_META_CONST,
    				u8_t basicSizeType = BASIC_SIZE_TYPE,
                 size_t reservedSec = SECNUM_RESERVED_CONST,
                 size_t metaSec = SECNUM_META_CONST,
                  u16_t validFlag = VALID_FLAG) :
            basicSizeType(basicSizeType), reservedSec(reservedSec),
                                                         metaSec(metaSec), lbaBaseLow(lbaBaseLow),
                                                         lbaBaseHigh(lbaBaseHigh), wholeSecnums(wholeSecnums),
                                                         validFlag(validFlag) {}

public:
	/**
	 *  校验metainfo是否有效
	 */
	static bool checkMetainfo(const X2fsMetaInfo& info)=delete;

	bool isValid()const
	{
		return validFlag == VALID_FLAG;
	}
	//序列化接口
	template <class __EnvTransfer>
		SerializerPtr<__EnvTransfer>& serialize(SerializerPtr<__EnvTransfer> &ptr)const;
	template <class __EnvTransfer>
		SerializerPtr<__EnvTransfer>& deserialize(SerializerPtr<__EnvTransfer> &ptr);
	template <class __EnvTransfer>
		static constexpr size_t getSerializitionSize();
	void dumpInfo();

    // auto generated setters & getters
    u8_t getBasicSizeType() const;

    void setBasicSizeType(u8_t basicSizeType);

    size_t getReservedSec() const;

    void setReservedSec(size_t reservedSec);

    size_t getMetaSec() const;

    void setMetaSec(size_t metaSec);

    size_t getFreeSpaceStart()const
    {
    	return getMetaSec() + getReservedSec();
    }
    /**
     * 必须足够长
     */
    size_t getFreeSpaceLength()const
    {
//    	std::assert( (this->getWholeSecnums() > this->getFreeSpaceStart()) );
    	return getWholeSecnums() - getFreeSpaceStart();
    }

    u32_t getLbaBaseLow() const;

    void setLbaBaseLow(u32_t lbaBaseLow);

    u32_t getLbaBaseHigh() const;

    void setLbaBaseHigh(u32_t lbaBaseHigh);

    size_t getWholeSecnums() const;

    void setWholeSecnums(size_t wholeSecnums);

private:
	/**
	 *  记录文件系统的size_t的基本长度
	 *  注意：该域必须放在开始，以便一个位置系统读取之后能够根据第一个字节判断出该文件系统的尺寸基本类型
	 *  取值：1,2,4,...
	 */
	u8_t	basicSizeType { BASIC_SIZE_TYPE };

	// mutable因为可能通过反序列化设置
	size_t reservedSec { SECNUM_RESERVED_CONST };//2
	size_t metaSec { SECNUM_META_CONST };

	u32_t	lbaBaseLow { 0 };
	u32_t	lbaBaseHigh	{ 0 };
	/**
	 * 记录该分区的总的扇区数
	 * 与mbr中的信息重复
	 */
	size_t wholeSecnums { 0 };

	u16_t	validFlag { VALID_FLAG };
};



//************X2fsMetaInfo 定义结束


//===class X2fsUtil
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
 *	不变式：
 *
 *
 *	@param __FsEnv 参见EnvTransfer
 *
 */
template <class __FsEnv>
class X2fsUtil : public SerializationInterface{
public:
	using __SizeType = size_t;
	// DEPRECATED  对齐因为序列化技术提出，已经过时
//	enum{ __FsAlignment =  __FsEnv::Alignment};
	using __X2fsMetaInfo = X2fsMetaInfo;
	using __SerializerPtr = SerializerPtr<__FsEnv>;
	using __BaseDescriptor = BaseDescriptor<__FsEnv>;
	using __FileDescriptor = FileDescriptor<__FsEnv>;
	using __DirDescriptor = DirDescriptor<__FsEnv>;

public:
	enum{
		ERROR_FILENAMESPACE,
		ERROR_NEW_NULL,
		ERROR_UNSUPORTED,
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
	using FileType = typename __BaseDescriptor::FileType;

	using This = X2fsUtil<__FsEnv>;
	using __X2fsUtil = This;

	using __TreeNode_MemoryDescriptor = TreeNode<MemoryDescriptor>;
	using __LinearSourceDescriptor = LinearSourceDescriptor;
	using __ListNode_LinearSourceDescriptor = ListNode<__LinearSourceDescriptor>;
	using __TimeType =typename __BaseDescriptor::__TimeType;
	using __TreeNode_BaseDescriptor = TreeNode<__BaseDescriptor*>;

	using LLSmm = MallocToSimple<__ListNode_LinearSourceDescriptor>;
	using FileNode = __TreeNode_BaseDescriptor;

	// 可以有allocator，但是这种情形基本上不多见，一般使用new即可。
	using FileTree = Tree<__BaseDescriptor*,MallocToSimple>; //多态必须使用指针
	using FileTreeSMM = typename FileTree::__Allocator;
	using FreeSpaceMM = LinearSourceManager<__LinearSourceDescriptor,
			MallocToSimple>;
private:
public:
	X2fsUtil(const __X2fsUtil &)=delete;
	__X2fsUtil& operator=(const __X2fsUtil &)=delete;
	/**
	 * @brief 从已有的文件系统初始化
	 * 先读取第一个扇区的506~508字节=保留区长度,508~509字节=元信息区长度，然后读取序列化的x2fsutil结构
	 */
	X2fsUtil(u8_t driver,u32_t lbaBase,u32_t lbaHigh);
	/**
	 * @brief 依据metainfo(格式化分区暗示者)创建一个新的X2fsUtil
	 */
	X2fsUtil(u8_t driver,const __X2fsMetaInfo &metainfo);

	/**
	 * 提供一些参数，然后从序列化指针读取保存的部分
	 */
	X2fsUtil(u8_t driver,SerializerPtr<__FsEnv>& ptr);
public:
	~X2fsUtil();

	/**
	 * 保留区大小的存储位置
	 */
	static constexpr int getReservedNumOff()
	{
		return 506;
	}
	/**
	 * 元信息区大小的存储位置
	 */
	static constexpr int getMetaNumOff()
	{
		return getReservedNumOff() + sizeof(u16_t);
	}
	static void readHeaderBufferInfo(void *buffer,u16_t &reservedNum,u16_t &metaNum)
	{
		reservedNum = *(reinterpret_cast<u16_t*>(reinterpret_cast<u8_t*>(buffer) + This::getReservedNumOff())) ;
		metaNum = *(reinterpret_cast<u16_t*>(reinterpret_cast<u8_t*>(buffer) + This::getMetaNumOff()));
	}
	static void writeHeaderBufferInfo(void *buffer,u16_t reservedNum,u16_t metaNum)
	{
		*(reinterpret_cast<u16_t*>(reinterpret_cast<u8_t*>(buffer) + This::getReservedNumOff())) = reservedNum;
		*(reinterpret_cast<u16_t*>(reinterpret_cast<u8_t*>(buffer) + This::getMetaNumOff())) =metaNum;
	}

	/**
	 * 在root根目录下创建一个文件
	 * @name   文件名
	 * @secNum 文件占据的扇区大小
	 */
	bool createFileInRoot(const char *name,__SizeType secNum);//reserved number of sectors
	DEPRECATED bool hasFilename(const char *name)const;
	bool hasFilename(int argc,const char *argv[],const char *name)const;


//	bool hasFilename(FileNode * node,const std::string& name)const;


//	DEPRECATED bool mkdir(const char* name);
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
	bool create(FileNode *p,FileType type,const char *name,__SizeType secSpan=2,__TimeType ctime=0);
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
	/**
	 * @return nullptr if not a file or non-exists
	 */
	__FileDescriptor * locateFile(FileNode *base,const char *name)const;
	__DirDescriptor * locateDir(FileNode *base,const char *name)const;
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
	DEPRECATED __SizeType
	writeToFile(const char *buf,__SizeType objsize, __SizeType nobj,FileNode *fnode,__SizeType foff=0)=delete;

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
	__SizeType locateILink(__FileDescriptor *fd,__SizeType startILink,__SizeType secPos,__SizeType & retOff);

	/**
	 * 按扇区写数据到ilink所指示的区间中，从secPos开始写，写secLen个
	 * @param   secLen 要写的扇区数目，如果len=0，则表示写到最后一个分区结束
	 * @return  如果ilink无效，或者所写的数据范围超过该ilink，则不执行写操作，并且返回0；
	 * 			写成功则返回实际写入的分区长度(secLen=0时返回实际长度)
	 */
	__SizeType		writeToILink(__SizeType ilink,const char *src,__SizeType secPos,__SizeType secLen)=delete;

	/**
	 * 扩展文件实际占用的扇区数目
	 * @param fileNode  要增加大小的文件
	 * @param extraSec  要增加的扇区数目
	 * @param addFileLength  是否也将文件内容长度更新
	 *
	 * @return 如果extraSec = 0则无影响； 如果不能增加，则返回false，源文件节点状态不变；否则，可能改变ilink的位置
	 */
	bool			extendFileSecNum(__FileDescriptor* fd,__SizeType extraSec,bool addFileLength=false);

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
	__SizeType _writeToFile(const char *buf, __SizeType nsec,__FileDescriptor *fd,__SizeType secPos=0,
			bool updateFileLen=true);
	__SizeType _readFromFile(char *buf,__SizeType nsec,__FileDescriptor *fd,__SizeType secPos=0);
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
	__SizeType _randomWriteFile(char *buf, __SizeType nbyte,__FileDescriptor *fd,__SizeType byteStart=0);
	/** UNTESTED
	 * 条件同上
	 * 此函数的实现不需要补齐，返回值的buf+(byteStart%CONST_SECSIZE)为有效数据
	 */
	__SizeType _randomReadFile(char *buf, __SizeType nbyte,__FileDescriptor *fd,__SizeType byteStart=0);


	/** INCOMPLETE
	 * 减小或增加文件长度,取决于给定长度与原始文件长度的关系
	 * 前置条件：
	 * 后置条件：newlen如果小于2*CONST_SECSIZE，则返回false，不可完成
	 * @param newlen 新长度
	 *
	 * @return 成功返回true，其他错误返回false
	 */
	bool truncateFile(__FileDescriptor *fd,__SizeType newlen);

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

public:
	SerializerPtr<__FsEnv>& serialize(SerializerPtr<__FsEnv> &ptr)const
	{
		return ptr << metainfo << freemm << fileTree;
	}
	SerializerPtr<__FsEnv>& deserialize(SerializerPtr<__FsEnv> &ptr)
	{
		return ptr >> metainfo >> freemm >> fileTree;
	}
	size_t getSerializitionSize()
	{
		return metainfo.getSerializitionSize<__FsEnv>()+
				freemm.getSerializitionSize<__FsEnv>()+
				fileTree.template getSerializitionSize<__FsEnv>();
	}

	u8_t getDriver() const
	{
		return driver;
	}

	const __X2fsMetaInfo& getMetainfo() const
	{
		return metainfo;
	}

private:
	/**
	 * 驱动器号，在有的操作系统上，可能将驱动器号映射成文件
	 */
	u8_t	driver{}; // 不参与序列化

	/**
	 * 元信息区域
	 */
	__X2fsMetaInfo metainfo{};

	/**
	 * 一个数值区间管理器，初始数值区间是  [数据区开始，数据区开始+数据区长度)
	 * 对于这种管理器，我们只应当将其认为是标记一系列的数值
	 * 当我们从中分配了一段字区间后，相应的认为磁盘上这些区间已经分配了。
	 */
	FreeSpaceMM freemm ;

	/**
	 * 一棵树，其全部分配的节点在dirsmm中
	 */
	FileTree fileTree;

	/**
	 * 存放错误信息
	 */
	mutable int processErrno{};/*can be used in both const & non-const method*/
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
	using __SizeType = size_t;
	using __X2fsUtil  = X2fsUtil<__FsEnv>;
	using FileNode = typename __X2fsUtil::FileNode;
	using __FileDescriptor = typename __X2fsUtil::__FileDescriptor;
	using __FsTimeType = typename __FileDescriptor::__TimeType;
	using FileType = typename __FileDescriptor::FileType;

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
	void randwrite(const __String& fname,__SizeType byteStart,const char* content,__SizeType byteLen=0);
	void randread(const __String& fname,__SizeType byteStart,__SizeType byteLen);

	/**
	 * 截断文件长度
	 */
	void truncate(const __String & fname,__SizeType newlen);
	/**
	 * @return true继续，false退出
	 */
	bool eval(const __String &cmd);

	void flush();

#if defined(CODE64)
	/** UNTESTED
	 *  与系统文件进行交互
	 *
	 *  @param maxLen 最大长度，如果设置成0，则表示读取sysFile的剩余长度
	 */
	__SizeType writeSysFileToX2File(const __String &sysFile,__SizeType sysStart,
								const __String &x2File,__SizeType x2Start,
								__SizeType maxLen);
	/** UNTESTED
	 * @param maxLen 最大长度，如果设为0，则表示读取x2File的剩余长度
	 */
	__SizeType readX2FileToSysFile(const __String &sysFile,__SizeType sysStart,
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
	using __SizeType = size_t;


	explicit ManagedObject();
    ManagedObject(const __ManagedObject &)=default;
    ManagedObject & operator=(const __ManagedObject &)=default;
	~ManagedObject();
	void setBufferIfNone(T buffer);
	AS_MACRO T	 getOnlyBuffer()const;
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
	return p && p->getData()->getType()==__FileDescriptor::TYPE_DIR;
}
__DEF_X2fsUtil_Template
bool __DEF_X2fsUtil::isFile(const FileNode *p)
{
	return p && p->getData()->getType()==FileType::TYPE_FILE;
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
