

#ifndef File_h__
#define File_h__

#include <64/MallocToSimple.h>
#include <def.h>
#include <cstdio>
#include <MemoryManager.h>
#include <List.h>
#include <string>


/**
* 
*/
class FileDescriptor
{
public:
	enum{ TYPE_FILE=0,TYPE_DIR=1,TYPE_EAP=2};
	friend class X2fsUtil;
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
class X2fsUtil{
public:
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
	typedef MallocToSimple<TreeNode<MemoryDescriptor> > TMSmm;
	typedef MallocToSimple<ListNode<LinearSourceDescriptor> > LLSmm;
	typedef MemoryManager<MallocToSimple> FileNameMM;
	typedef SimpleMemoryManager<TreeNode<FileDescriptor> > FileNodeMM;

	//FileNode 真实类型是  SimpleMemoryManager<TreeNode<FileDescriptor> >::Node
	//即 TreeNode<FileDescriptor>,SimpleMemoryNode的组合
	// getHead()只返回TreeNode<FileDescriptor>,即数据部分
	//	typedef FileNodeMM::Node FileNode;
	typedef FileNodeMM::DataPart FileNode;


	typedef Tree<FileDescriptor,SimpleMemoryManager> FileTree;
	typedef LinearSourceManager<LinearSourceDescriptor,MallocToSimple> FreeSpaceMM;
	typedef LinearSourceManager<LinearSourceDescriptor,MallocToSimple> LinkedInfoMM;

	enum{
		FileNodeSize=sizeof(FileNode)
	};
public:
	X2fsUtil()=delete;
	X2fsUtil(const char *file);//create a handler to the image file.
	~X2fsUtil();
	/**
	 * 在root根目录下创建一个文件
	 * @name   文件名
	 * @secNum 文件占据的扇区大小
	 */
	bool createFileInRoot(const char *name,size_t secNum);//reserved number of sectors
	DEPRECATED bool hasFilename(const char *name)const;
	bool hasFilename(int argc,const char *argv[],const char *name)const;
	bool hasFilename(FileNode * node,const std::string& name)const;
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
	void flush();//write the buffered content back to file
	AS_MACRO int geterrno()const;

public:
	char *getFileNameCstr(const FileDescriptor &fd,size_t &nlen)const;
	std::string getFileName(const FileNode *p)const;

	UNTESTED void printNode(const FileNode *p)const;
	UNTESTED void listOnNode(const FileNode *p,int maxdeepth=1)const;

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

	INCOMPLETE size_t writeToFile(const char *buf,size_t objsize, size_t nobj,FileNode *fnode,size_t foff=0);
	INCOMPLETE size_t readFromFile(char *buf,size_t objsize, size_t nobj,FileNode *fnode,size_t foff=0);
	AS_MACRO void seterrno(int processErrno)const;
	AS_MACRO void seterrno(int processErrno);
	AS_MACRO FileNode * getRootBase()const;
	AS_MACRO FileNode * getRootBase();
	AS_MACRO static bool isDirectory(const FileNode *p);
	AS_MACRO static bool isFile(const FileNode *p);


	static void mockMkfsX2fs(void *base,size_t secNum);

	template <template <class>class _Allocator>
	INCOMPLETE static void getLinkedList(LinearSourceDescriptor *buffer,size_t i,LinkedList<LinearSourceDescriptor,_Allocator> &list,size_t maxlen);

	DEPRECATED static void createFile_old(void *base,const char* name,size_t secNum);//default length=0,start=0,span=secNum

	AS_MACRO FileTree getFileTree();
protected:
		void initBuffers();

		/**
		 * 这真是一个bug， 因为指针偏移在64位系统下不能仅仅使用int存放，所以导致出错。
		 * 调试了半天。。。
		 */
		// old version ---> void adjustDirbufOffset(int off);//positive or negative
		void adjustDirbufOffset(ptrdiff_t off);


		void retriveFileNameSection();
		/**
		 * This is not necessary for filename section,cause all changes had been made as direct and immediate
		 */
		DEPRECATED void saveFileNameSection();

		void retriveFreeSpaceSection();
		void saveFreeSpaceSection();


		UNTESTED void retriveLinkedInfoSection();
		DEPRECATED void saveLinkedInfoSection();/*The modifies are at-place*/

		void retriveDirSection();
		void saveDirSection();


protected:
	char *namebuf,*dirbuf,*freebuf,*filebuf;
	union{
		char *linkbuf;
		LinearSourceDescriptor *linkarr;
	};
	size_t namebufLen,dirbufLen,freebufLen,filebufLen,linkbufLen,reservedLen;
	size_t linkarrLen;
	const char *imgFile;
	FILE *fpimg;
	TMSmm mmnodesmm;
	FileNameMM filenamemm;
	LLSmm listnodesmm;

	FileNodeMM dirsmm;
	FileTree fileTree;
	FreeSpaceMM freemm;
	LinkedInfoMM linkmm;

	mutable int processErrno;/*can be used in both const & non-const method*/

};

class PathUtil{
public:
	PathUtil();
	~PathUtil();

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
int X2fsUtil::geterrno()const
{
	return this->processErrno;
}
void X2fsUtil::seterrno(int processErrno)const
{
	this->processErrno=processErrno;
}
void X2fsUtil::seterrno(int processErrno)
{
	this->processErrno=processErrno;
}
X2fsUtil::FileNode * X2fsUtil::getRootBase()const
{
		return (FileNode *)this->fileTree.getHead();
}
X2fsUtil::FileNode * X2fsUtil::getRootBase()
{
		return (FileNode *)this->fileTree.getHead();
}
bool X2fsUtil::isDirectory(const FileNode *p)
{
	return p && p->getData().getType()==FileDescriptor::TYPE_DIR;
}
bool X2fsUtil::isFile(const FileNode *p)
{
	return p && p->getData().getType()==FileDescriptor::TYPE_FILE;
}
X2fsUtil::FileTree X2fsUtil::getFileTree()
{
	return fileTree;
}

//template<template<class > class _Allocator>
//void X2fsUtil::getLinkedList(LinearSourceDescriptor* buffer,
//		LinkedList<LinearSourceDescriptor, _Allocator>& list, size_t maxlen) {
//}

#endif //File_h__
