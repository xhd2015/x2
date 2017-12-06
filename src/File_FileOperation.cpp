/*
 * File_FileOperation.cpp
 *
 *  Created on: Nov 29, 2017
 *      Author: 13774
 */

// 对FileOperation的实现

#include <def.h>
#include <File.h>

#if defined(CODE64)
#include <EnvInterface64Impl.h>
//	template class FileOperation<StdEnv64Impl,FsEnv16>;
//	template class FileOperation<StdEnv64Impl,FsEnv32>;
//	template class FileOperation<StdEnv64Impl,FsEnv64>;
#endif


//==class FileOperation
#define __DEF_Template_FileOperation template <class __FsEnv>
#define __DEF_FileOperation FileOperation<__FsEnv>

__DEF_Template_FileOperation
__DEF_FileOperation::FileOperation(u8_t driver,u32_t lbaAddress):
	util(driver, lbaAddress),
	curNode(nullptr),
	lastNode(nullptr)
{
	curPath.push_back("");
	curNode =util.getFileTree()->getHead();//当前目录为根目录
}
__DEF_Template_FileOperation
__DEF_FileOperation::~FileOperation()
{
	this->curNode=nullptr;
	this->lastNode=nullptr;
	this->curPath.clear();
}
__DEF_Template_FileOperation
void __DEF_FileOperation::help()
{
	HostEnv::printf_simple(R"+*( 
       help
       ls
       pwd
       mkdir dirName
       cd pathName
       rm fname
       touch  fname secNum ctime
       exit
       quit
       read file StartSec ByteNum   #读取并打印文件Start起,共ByteNum个字节的内容
       write file StartSec dddddddddddddd...   #写一串字符串到file，startSec参数后面的所有内容被视为要写的字符串,长度至少为1个扇区
            注:pathName可以含有任意组合的路径,但是fname,dirName不被视为路径而是普通文件名
       randread file startByte  byteNum   #按字节位置随机读取文件内容
       randwrite file startByte dddddddddddddddd...  #按字节位置写文件内容
       truncate file newlen       #增加或截断文件的长度
)+*" );
}



__DEF_Template_FileOperation
void __DEF_FileOperation::ls()
{
	util.listNode(curNode);
}

__DEF_Template_FileOperation
bool __DEF_FileOperation::cd(const __String& strPath)
{
	__Vector_String paths=HostEnv::pathSplit(strPath);
	if(paths.size()==0) // no argument
	{
		//do nothing or cd home
		return true;
	}else if(paths.size()==1 && paths[0].compare("-")==0) // cd last
	{
		return cdLast();
	}else{
		//处理是，遇到.,直接移除
		//			遇到..,移除它和它的上一个
		// 首部的"" 表示切换到 根， 其他的""表示不变

		auto it=paths.cbegin();
		if(paths[0].size()==0) // cd root firstly
		{
			cdRoot();
			++it;
		}

		return cdFromCur(it,paths.cend());
	}

}

__DEF_Template_FileOperation
bool __DEF_FileOperation::cdFromCur(__Vector_String_cit begin,__Vector_String_cit end)
{
	FileNode *tempCur=curNode;
	FileNode *temp=nullptr;
	int npushed=0;//记录已经加入path的长度,负数表示需要移除,0表示不变
	__Vector_String appendPaths;


	bool isError=false;
	auto p=begin;
	for(;p!=end;++p)
	{
//		如果..超过了根目录，报错
		if(p->compare(".")==0)
			continue;
		else if(p->compare("..")==0)
		{
			if(npushed+curPath.size()<=1)
			{
				HostEnv::printf_simple("there is some error in your path,check it again\n");
				HostEnv::flushOutputs();
				isError = true;
				break;
			}else{
				if(npushed>0)
					appendPaths.pop_back();
				--npushed;
				tempCur= reinterpret_cast<FileNode*>(tempCur->getDirectFather());
			}
		}else{ //normal locating

			temp=util.locatePath(tempCur, p->c_str());
			if(temp==nullptr)
			{
				HostEnv::printf_simple("directory \"");
				HostEnv::printf_simple(p->c_str());
				HostEnv::printf_simple("\" does not exist\n");
				HostEnv::flushOutputs();
				isError=true;
				break;
			}else if(!util.isDirectory(temp)){
				HostEnv::printf_simple("\"");
				HostEnv::printf_simple(p->c_str());
				HostEnv::printf_simple("\" is not a directory");
				HostEnv::flushOutputs();
				isError=true;
				break;
			}else{
				tempCur=temp;
				if(npushed>=0)
					appendPaths.push_back(*p);
				++npushed;
			}
		}
	}
	if(!isError)
	{
		lastNode=curNode;
		curNode=tempCur;
		while(npushed>0)
		{
			curPath.push_back(appendPaths[appendPaths.size() - npushed]);
			--npushed;
		}
		while(npushed<0)
		{
			curPath.pop_back();
			++npushed;
		}
	}

	return (!isError);
}
__DEF_Template_FileOperation
bool __DEF_FileOperation::cdLast()
{
	if(lastNode!=nullptr)
	{
		FileNode *temp=curNode;
		curNode = lastNode;
		lastNode = temp;
		refreshCurrentPath();
	}else{
		lastNode = curNode;
	}
	return true;
}
__DEF_Template_FileOperation
void __DEF_FileOperation::cdRoot()
{
	lastNode=curNode;
	curPath.clear();
	curPath.push_back("");
}
__DEF_Template_FileOperation
void __DEF_FileOperation::rm(const __String & fname)
{
	util.seterrno(__X2fsUtil::ERROR_NOERR);
	FileNode *fnode;
	if(checkExits(fname, fnode))
	{
		util.deleteFile(fnode);
	}
}
__DEF_Template_FileOperation
void __DEF_FileOperation::mkdir(const __String& dir)
{

	util.seterrno(__X2fsUtil::ERROR_NOERR);
	util.create(curNode, FileDescriptor::TYPE_DIR, dir.c_str(), 0,0);
	if(util.geterrno() == __X2fsUtil::ERROR_FILE_ALREDY_EXIST)
	{
		HostEnv::printf_simple("file/directory");
		HostEnv::printf_simple(dir.c_str());
		HostEnv::printf_simple("\" already exists\n");
		HostEnv::flushOutputs();
	}
}
__DEF_Template_FileOperation
void __DEF_FileOperation::touch(const __String & fname,__SizeType secNum,__FsTimeType ctime)
{
	util.seterrno(__X2fsUtil::ERROR_NOERR);
	util.create(curNode, FileDescriptor::TYPE_FILE, fname.c_str(), secNum,ctime);
	if(util.geterrno()!=__X2fsUtil::ERROR_NOERR)
	{
		HostEnv::printf_simple("error code is %d\n",util.geterrno());
		HostEnv::flushOutputs();
	}
	if(util.geterrno() == __X2fsUtil::ERROR_FILE_ALREDY_EXIST)
	{
		HostEnv::printf_simple("file/directory");
		HostEnv::printf_simple(fname.c_str());
		HostEnv::printf_simple("\" already exists\n");
		HostEnv::flushOutputs();
	}
}
__DEF_Template_FileOperation
void __DEF_FileOperation::cat()
{
	HostEnv::printf_simple("method unsupported\n");
	HostEnv::flushOutputs();
}
__DEF_Template_FileOperation
void __DEF_FileOperation::pwd()
{
	for(__String& s:curPath)
	{
		HostEnv::printf_simple(s.c_str());
		HostEnv::printf_simple("/");
	}
	HostEnv::printf_simple("\n");
	HostEnv::flushOutputs();
}
__DEF_Template_FileOperation
void __DEF_FileOperation::changeImage(const __String& img)
{
	HostEnv::printf_simple("method unsupported\n");
	HostEnv::flushOutputs();
}
__DEF_Template_FileOperation
const typename __DEF_FileOperation::__String& __DEF_FileOperation::curDir()
{
	return curPath[curPath.size()-1];
}
__DEF_Template_FileOperation
void __DEF_FileOperation::read(const __String& fname,__SizeType secStart,__SizeType byteLen)
{
	size_t secnum = (byteLen/CONST_SECSIZE)+(byteLen%CONST_SECSIZE!=0);
	char *buffer=new char[secnum * CONST_SECSIZE];

	size_t readNum = util._readFromFile(buffer,secnum,util.locatePath(curNode, fname.c_str()), secStart);
	HostEnv::printf_simple( "read num is %d\n",readNum );
	HostEnv::printf_sn(buffer,byteLen);
	HostEnv::flushOutputs();
	delete [] buffer;
}
__DEF_Template_FileOperation
void __DEF_FileOperation::write(const __String& fname,__SizeType start,const char* content,__SizeType len)
{
	size_t secnum= (len/CONST_SECSIZE)+(len%CONST_SECSIZE!=0);
	char *buffer=new char[secnum * CONST_SECSIZE]();
	for(size_t i=0;i<len;i++)
		buffer[i]=content[i];
	size_t writeNum = util._writeToFile(buffer, secnum, util.locatePath(curNode, fname.c_str()), start);
	HostEnv::printf_simple( "write sec num is %d\n",writeNum );
	HostEnv::flushOutputs();
	delete []buffer;
}

__DEF_Template_FileOperation
void __DEF_FileOperation::randwrite(const __String& fname,__SizeType byteStart,
		const char* content,__SizeType byteLen)
{
	ManagedObject<char*> mbuf;
	__SizeType bufSize,startOff,endOff;
	bufSize=__X2fsUtil::calculateRandomBufferSize(byteStart, byteLen, &startOff, &endOff, CONST_SECSIZE);

	char *contentBuf = mbuf.getOnlyBuffer(bufSize);
	HostEnv::memcpy(contentBuf + startOff, content,byteLen);

	__SizeType writeNum = util._randomWriteFile(contentBuf, byteLen,
			util.locatePath(curNode, fname.c_str()), byteStart);
	HostEnv::printf_simple( "write byte num is %d\n",writeNum );
	HostEnv::flushOutputs();
}
__DEF_Template_FileOperation
void __DEF_FileOperation::randread(const __String& fname,__SizeType byteStart,__SizeType byteLen)
{
	ManagedObject<char*> mbuf;
	__SizeType bufSize,startOff,endOff;
	bufSize=__X2fsUtil::calculateRandomBufferSize(byteStart, byteLen, &startOff, &endOff, CONST_SECSIZE);

	char *contentBuf = mbuf.getOnlyBuffer(bufSize);
	size_t readNum = util._randomReadFile(contentBuf, byteLen,
			util.locatePath(curNode, fname.c_str()), byteStart);
	HostEnv::printf_simple( "read byte num is %d\n",readNum );
	if(readNum!=0)
		HostEnv::printf_sn(contentBuf+startOff,readNum);
	HostEnv::flushOutputs();
}

__DEF_Template_FileOperation
void __DEF_FileOperation::truncate(const __String & fname,__SizeType newlen)
{
	FileNode *fnode;
	if(checkIsFile(fname, fnode))
	{
		__SizeType oldLen = fnode->getData().getFileLen();
		if(util.truncateFile(fnode, newlen))
		{
			HostEnv::printf_simple("len:%d --> %d\n",oldLen,fnode->getData().getFileLen());
		}else{
			HostEnv::printf_simple("cannot truncate file.\n");
		}
	}
}
__DEF_Template_FileOperation
bool __DEF_FileOperation::eval(const __String &cmd)
{
		//parse all args
		//将其用正则表达式分解成数组格式
		vector<string> args=HostEnv::spaceSplit(cmd);
		if(args.size()==0)return true;
		if(args[0].compare("help")==0)
		{
			help();
		}else if(args[0].compare("ls")==0){
			ls();
		}else if(args[0].compare("pwd")==0){
			pwd();
		}else if(args[0].compare("mkdir")==0){
			mkdir(args[1]);
		}else if(args[0].compare("cd")==0){
			if(args.size() < 2)
				return true;
			else
				cd(args[1]);
		}else if(args[0].compare("rm")==0){
			rm(args[1]);
		}else if(args[0].compare("touch")==0){
			if(args.size() < 4)
			{
				HostEnv::printf_simple("see help for touch\n");
			}else{
				touch(args[1], HostEnv::atoi(args[2]),HostEnv::atoi(args[3]));
			}
		}else if(args[0].compare("write")==0 || args[0].compare("randwrite")==0){
			if(args.size() < 4)
			{
				HostEnv::printf_simple("see help for ");
				HostEnv::printf_simple(args[0].c_str());
				HostEnv::printf_simple("\n");
			}else{
				if(args[0].compare("write")==0)
					write(args[1], HostEnv::atoi(args[2]),args[3].c_str(), args[3].length());
				else
					randwrite(args[1], HostEnv::atoi(args[2]),args[3].c_str(), args[3].length());
			}
		}else if(args[0].compare("read")==0 || args[0].compare("randread")==0){
			//read file StartSec ByteNum
			if(args.size() < 4)
			{
				HostEnv::printf_simple("see help for ");
				HostEnv::printf_simple(args[0].c_str());
				HostEnv::printf_simple("\n");
			}
			else
			{
				if(args[0].compare("read")==0)
					read(args[1],HostEnv::atoi(args[2]), HostEnv::atoi(args[3]));
				else
					randread(args[1],HostEnv::atoi(args[2]), HostEnv::atoi(args[3]));
			}
		}else if(args[0].compare("truncate")==0){
			if(args.size() < 3)
			{
				HostEnv::printf_simple("see help for ");
				HostEnv::printf_simple(args[0].c_str());
				HostEnv::printf_simple("\n");
			}
			else{
				truncate(args[1], HostEnv::atoi(args[2]));
			}

		}else if(args[0].compare("quit")==0 || args[0].compare("exit")==0){
			return false;
		}else{
			HostEnv::printf_simple("Unrecognized command '");
				HostEnv::printf_simple(args[0].c_str());
				HostEnv::printf_simple("'.\n");
		}
		HostEnv::flushOutputs();
		return true;

}
#if defined(CODE64)
#include <fstream>
__DEF_Template_FileOperation
typename __DEF_FileOperation::__SizeType __DEF_FileOperation::readSysFileToX2File(const __String &sysFile,__SizeType sysStart,
							const __String &x2File,__SizeType x2Start,
							__SizeType maxLen)
{
	FileNode *fnode=util.locatePath(curNode, x2File.c_str());
	if(fnode==nullptr)
	{
		// TODO 如果文件不存在就创建
		HostEnv::printf_simple("error,file in x2 not exists,please create it first\n");
		return 0;
	}

	std::fstream fs(sysFile,std::fstream::in|std::fstream::out|std::fstream::binary);
	if(!fs.is_open())//如果文件不存在，直接返回
		return 0;

	fs.seekg(0,std::fstream::end);
	__SizeType fcount = fs.tellg();
	HostEnv::printf_simple("file gcount = %d\n",fcount);
	HostEnv::flushOutputs();
	if(sysStart >= fcount)
	{
		fs.close();
		//文件容量不足
		HostEnv::printf_simple("error,file not exists or no a single byte is"
				" available at given position\n");
		return 0;
	}


	// 申请 4KB的buffer，然后循环读取
	const __SizeType headingByte = (x2Start%CONST_SECSIZE);
	const __SizeType bufsize=4*2*CONST_SECSIZE;

	ManagedObject<char*> mbuf;

	char *buf=mbuf.getOnlyBuffer(headingByte + bufsize);//为了兼容
	if(buf==nullptr)
		return 0;

	fs.seekg(sysStart);
	if(maxLen==0)
		maxLen = fcount - sysStart;

	__SizeType leftLen=maxLen;
	__SizeType sysFileLeft = fcount - sysStart;
	__SizeType start=x2Start;
	while(leftLen>0 && sysFileLeft>0)
	{
		__SizeType thisAvl =Util::min(bufsize, Util::min( sysFileLeft,leftLen));
				//取leftLen,sysFileLeft,bufSize中的最小者
		fs.read(buf + headingByte, thisAvl);
		util._randomWriteFile(buf, thisAvl,fnode, start);
		sysFileLeft-=thisAvl;
		leftLen-=thisAvl;
		start+=thisAvl;
	}


	fs.close();
	return (maxLen - leftLen);

}
__DEF_Template_FileOperation
typename __DEF_FileOperation::__SizeType __DEF_FileOperation::
		writeSysFileFromX2File(const __String &sysFile,__SizeType sysStart,
							const __String &x2File,__SizeType x2Start,
							__SizeType maxLen)
{
	FileNode *fnode=util.locatePath(curNode, x2File.c_str());
	__SizeType flen;
	if(fnode==nullptr || (flen=fnode->getData().getFileLen()) <= x2Start)
	{
		HostEnv::printf_simple("error,file in x2 not exists or no a single byte is"
				" available at given position\n");
		return 0;
	}

	std::fstream fs(sysFile,std::fstream::in|std::fstream::out|std::fstream::binary);//如果文件不存在，打开空的
	if(!fs.is_open()) // 文件不存在
		fs.open(sysFile, std::fstream::out);

	// 申请 4KB的buffer，然后循环读取
	const __SizeType headingByte = (x2Start%CONST_SECSIZE);
	const __SizeType bufsize=4*2*CONST_SECSIZE;

	ManagedObject<char*> mbuf;

	char *buf=mbuf.getOnlyBuffer(headingByte + bufsize);//为了兼容x2随机写的需求
	if(buf==nullptr)
		return 0;

	fs.seekp(sysStart);
	if(maxLen==0)
		maxLen = flen - x2Start;

	__SizeType leftLen = maxLen;
	__SizeType x2FileLeft = flen - x2Start;
	__SizeType start = x2Start;
	while(leftLen>0 && x2FileLeft>0)
	{
		__SizeType thisAvl =Util::min(bufsize, Util::min( x2FileLeft,leftLen));
		util._randomReadFile(buf, thisAvl,
					fnode, start);
		fs.write(buf+headingByte,thisAvl);
		x2FileLeft-=thisAvl;
		leftLen-=thisAvl;
		start += thisAvl;
	}
	fs.close();
	return (maxLen - leftLen);
}
#endif

__DEF_Template_FileOperation
bool __DEF_FileOperation::checkIsFile(const __String & fname,FileNode *&fnode)const
{
	bool exist=checkExits(fname, fnode) ;
	if(exist && fnode->getData().getType()!=__FileDescriptor::TYPE_FILE){
		errorNotAFile(fname);
		return false;
	}
	return exist;
}
__DEF_Template_FileOperation
bool __DEF_FileOperation::checkIsDir(const __String & fname,FileNode *&fnode)const
{
	bool exist=checkExits(fname, fnode) ;
	if(exist && fnode->getData().getType()!=__FileDescriptor::TYPE_DIR){
		errorNotADir(fname);
		return false;
	}
	return exist;
}

__DEF_Template_FileOperation
bool __DEF_FileOperation::checkExits(const __String & fname,FileNode *&fnode)const
{
	fnode = util.locatePath(curNode, fname.c_str());
	if(fnode==nullptr)
	{
		errorFileNotExits(fname);
		return false;
	}
	return true;
}
__DEF_Template_FileOperation
void __DEF_FileOperation::errorFileNotExits(const __String & fname)const
{
	HostEnv::printf_simple("file/dir \"");
	HostEnv::printf_simple(fname.c_str());
	HostEnv::printf_simple("\" not exists.\n");
	HostEnv::flushOutputs();
}
__DEF_Template_FileOperation
void __DEF_FileOperation::errorNotAFile(const __String & fname)const
{
	HostEnv::printf_simple("name \"");
	HostEnv::printf_simple(fname.c_str());
	HostEnv::printf_simple("\" not a file.\n");
	HostEnv::flushOutputs();
}

__DEF_Template_FileOperation
void __DEF_FileOperation::errorNotADir(const __String &fname)const
{
	HostEnv::printf_simple("file \"");
	HostEnv::printf_simple(fname.c_str());
	HostEnv::printf_simple("\" not a dir.\n");
	HostEnv::flushOutputs();
}

__DEF_Template_FileOperation
void __DEF_FileOperation::refreshCurrentPath()
{
	curPath.clear();
	FileNode *head= reinterpret_cast<FileNode*>(util.getFileTree()->getHead());

//	TreeNode<FileDescriptor> *ip=tree.getHead();

	FileNode *p=curNode;
//	vector<string>::size_type i=1;
	while(p!=head)
	{
		__SizeType nlen;
		char* str=util.getFileNameCstr(p->getData(), nlen);
		curPath.insert(curPath.begin(),__String(str));
		p = reinterpret_cast<FileNode*>(p->getDirectFather());
	}
}

#undef __DEF_Template_FileOperation
#undef __DEF_FileOperation

