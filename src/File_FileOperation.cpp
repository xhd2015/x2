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
	template class FileOperation<StdEnv64Impl, size_t>;
#endif


template <class __StdEnv,class __SizeType>
FileOperation<__StdEnv,__SizeType>::FileOperation(__StdEnv * env,u8_t driver,u32_t lbaAddress):
	stdEnv(env),
	util(env, driver, lbaAddress),
	curNode(NULL),
	lastNode(NULL)
{
	curPath.push_back("");
	curNode = (FileNode*) util.getFileTree()->getHead();//当前目录为根目录
}
template <class __StdEnv,class __SizeType>
void FileOperation<__StdEnv,__SizeType>::help()
{
	stdEnv->printf_simple(R"+*( 
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



template <class __StdEnv,class __SizeType>
void FileOperation<__StdEnv,__SizeType>::ls()
{
	util.listNode(curNode);
}

template <class __StdEnv,class __SizeType>
bool FileOperation<__StdEnv,__SizeType>::cd(const __String& strPath)
{
	__Vector_String paths=stdEnv->pathSplit(strPath);
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

template <class __StdEnv,class __SizeType>
bool FileOperation<__StdEnv,__SizeType>::cdFromCur(__Vector_String_cit begin,__Vector_String_cit end)
{
	FileNode *tempCur=curNode;
	FileNode *temp=NULL;
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
				stdEnv->printf_simple("there is some error in your path,check it again\n");
				stdEnv->flushOutputs();
				isError = true;
				break;
			}else{
				if(npushed>0)
					appendPaths.pop_back();
				--npushed;
				tempCur=(FileNode*)tempCur->getDirectFather();
			}
		}else{ //normal locating

			temp=util.locatePath(tempCur, p->c_str());
			if(temp==NULL)
			{
				stdEnv->printf_simple("directory \"");
				stdEnv->printf_simple(p->c_str());
				stdEnv->printf_simple("\" does not exist\n");
				stdEnv->flushOutputs();
				isError=true;
				break;
			}else if(!util.isDirectory(temp)){
				stdEnv->printf_simple("\"");
				stdEnv->printf_simple(p->c_str());
				stdEnv->printf_simple("\" is not a directory");
				stdEnv->flushOutputs();
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
template <class __StdEnv,class __SizeType>
bool FileOperation<__StdEnv,__SizeType>::cdLast()
{
	if(lastNode!=NULL)
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
template <class __StdEnv,class __SizeType>
void FileOperation<__StdEnv,__SizeType>::cdRoot()
{
	lastNode=curNode;
	curPath.clear();
	curPath.push_back("");
}
template <class __StdEnv,class __SizeType>
void FileOperation<__StdEnv,__SizeType>::rm(const __String & fname)
{
	util.seterrno(X2fsUtil<EnvInterface64Impl,size_t>::ERROR_NOERR);
	FileNode *fnode;
	if(checkExits(fname, fnode))
	{
		util.deleteFile(fnode);
	}
}
template <class __StdEnv,class __SizeType>
void FileOperation<__StdEnv,__SizeType>::mkdir(const __String& dir)
{
	util.seterrno(X2fsUtil<EnvInterface64Impl,size_t>::ERROR_NOERR);
	util.create(curNode, FileDescriptor<size_t>::TYPE_DIR, dir.c_str(), 0,0);
	if(util.geterrno() == X2fsUtil<EnvInterface64Impl,size_t>::ERROR_FILE_ALREDY_EXIST)
	{
		stdEnv->printf_simple("file/directory");
		stdEnv->printf_simple(dir.c_str());
		stdEnv->printf_simple("\" already exists\n");
		stdEnv->flushOutputs();
	}
}
template <class __StdEnv,class __SizeType>
void FileOperation<__StdEnv,__SizeType>::touch(const __String & fname,__SizeType secNum,__TimeType ctime)
{
	util.seterrno(X2fsUtil<EnvInterface64Impl,size_t>::ERROR_NOERR);
	util.create(curNode, FileDescriptor<size_t>::TYPE_FILE, fname.c_str(), secNum,ctime);
	if(util.geterrno()!=X2fsUtil<EnvInterface64Impl,size_t>::ERROR_NOERR)
	{
		stdEnv->printf_simple("error code is %d\n",util.geterrno());
		stdEnv->flushOutputs();
	}
	if(util.geterrno() == X2fsUtil<EnvInterface64Impl,size_t>::ERROR_FILE_ALREDY_EXIST)
	{
		stdEnv->printf_simple("file/directory");
		stdEnv->printf_simple(fname.c_str());
		stdEnv->printf_simple("\" already exists\n");
		stdEnv->flushOutputs();
	}
}
template <class __StdEnv,class __SizeType>
void FileOperation<__StdEnv,__SizeType>::cat()
{
	stdEnv->printf_simple("method unsupported\n");
	stdEnv->flushOutputs();
}
template <class __StdEnv,class __SizeType>
void FileOperation<__StdEnv,__SizeType>::pwd()
{
	for(__String& s:curPath)
	{
		stdEnv->printf_simple(s.c_str());
		stdEnv->printf_simple("/");
	}
	stdEnv->printf_simple("\n");
	stdEnv->flushOutputs();
}
template <class __StdEnv,class __SizeType>
void FileOperation<__StdEnv,__SizeType>::changeImage(const __String& img)
{
	stdEnv->printf_simple("method unsupported\n");
	stdEnv->flushOutputs();
}
template <class __StdEnv,class __SizeType>
const typename FileOperation<__StdEnv,__SizeType>::__String& FileOperation<__StdEnv,__SizeType>::curDir()
{
	return curPath[curPath.size()-1];
}
template <class __StdEnv,class __SizeType>
void FileOperation<__StdEnv,__SizeType>::read(const __String& fname,__SizeType secStart,__SizeType byteLen)
{
	size_t secnum = (byteLen/CONST_SECSIZE)+(byteLen%CONST_SECSIZE!=0);
	char *buffer=new char[secnum * CONST_SECSIZE];

	size_t readNum = util._readFromFile(buffer,secnum,util.locatePath(curNode, fname.c_str()), secStart);
	stdEnv->printf_simple( "read num is %d\n",readNum );
	stdEnv->printf_sn(buffer,byteLen);
	stdEnv->flushOutputs();
	delete [] buffer;
}
template <class __StdEnv,class __SizeType>
void FileOperation<__StdEnv,__SizeType>::write(const __String& fname,__SizeType start,const char* content,__SizeType len)
{
	size_t secnum= (len/CONST_SECSIZE)+(len%CONST_SECSIZE!=0);
	char *buffer=new char[secnum * CONST_SECSIZE]();
	for(size_t i=0;i<len;i++)
		buffer[i]=content[i];
	size_t writeNum = util._writeToFile(buffer, secnum, util.locatePath(curNode, fname.c_str()), start);
	stdEnv->printf_simple( "write sec num is %d\n",writeNum );
	stdEnv->flushOutputs();
	delete []buffer;
}

template <class __StdEnv,class __SizeType>
void FileOperation<__StdEnv,__SizeType>::randwrite(const __String& fname,__SizeType byteStart,
		const char* content,__SizeType byteLen)
{
	ManagedObject<char*,__StdEnv,__SizeType> mbuf(stdEnv);
	__SizeType bufSize,startOff,endOff;
	bufSize=__X2fsUtil::calculateRandomBufferSize(byteStart, byteLen, &startOff, &endOff, CONST_SECSIZE);

	char *contentBuf = mbuf.getOnlyBuffer(bufSize);
	stdEnv->memcpy(contentBuf + startOff, content,byteLen);

	__SizeType writeNum = util._randomWriteFile(contentBuf, byteLen,
			util.locatePath(curNode, fname.c_str()), byteStart);
	stdEnv->printf_simple( "write byte num is %d\n",writeNum );
	stdEnv->flushOutputs();
}
template <class __StdEnv,class __SizeType>
void FileOperation<__StdEnv,__SizeType>::randread(const __String& fname,__SizeType byteStart,__SizeType byteLen)
{
	ManagedObject<char*,__StdEnv,__SizeType> mbuf(stdEnv);
	__SizeType bufSize,startOff,endOff;
	bufSize=__X2fsUtil::calculateRandomBufferSize(byteStart, byteLen, &startOff, &endOff, CONST_SECSIZE);

	char *contentBuf = mbuf.getOnlyBuffer(bufSize);
	size_t readNum = util._randomReadFile(contentBuf, byteLen,
			util.locatePath(curNode, fname.c_str()), byteStart);
	stdEnv->printf_simple( "read byte num is %d\n",readNum );
	if(readNum!=0)
		stdEnv->printf_sn(contentBuf+startOff,readNum);
	stdEnv->flushOutputs();
}

template <class __StdEnv,class __SizeType>
void FileOperation<__StdEnv,__SizeType>::truncate(const __String & fname,__SizeType newlen)
{
	FileNode *fnode;
	if(checkIsFile(fname, fnode))
	{
		__SizeType oldLen = fnode->getData().getFileLen();
		if(util.truncateFile(fnode, newlen))
		{
			stdEnv->printf_simple("len:%d --> %d\n",oldLen,fnode->getData().getFileLen());
		}else{
			stdEnv->printf_simple("cannot truncate file.\n");
		}
	}
}
#if defined(CODE64)
#include <fstream>
template <class __StdEnv,class __SizeType>
__SizeType FileOperation<__StdEnv,__SizeType>::readSysFileToX2File(const __String &sysFile,__SizeType sysStart,
							const __String &x2File,__SizeType x2Start,
							__SizeType maxLen)
{
	FileNode *fnode=util.locatePath(curNode, x2File.c_str());
	if(fnode==NULL)
	{
		// TODO 如果文件不存在就创建
		stdEnv->printf_simple("error,file in x2 not exists,please create it first\n");
		return 0;
	}

	std::fstream fs(sysFile,std::fstream::in|std::fstream::out|std::fstream::binary);
	if(!fs.is_open())//如果文件不存在，直接返回
		return 0;

	fs.seekg(0,std::fstream::end);
	__SizeType fcount = fs.tellg();
	stdEnv->printf_simple("file gcount = %d\n",fcount);
	stdEnv->flushOutputs();
	if(sysStart >= fcount)
	{
		fs.close();
		//文件容量不足
		stdEnv->printf_simple("error,file not exists or no a single byte is"
				" available at given position\n");
		return 0;
	}


	// 申请 4KB的buffer，然后循环读取
	const __SizeType headingByte = (x2Start%CONST_SECSIZE);
	const __SizeType bufsize=4*2*CONST_SECSIZE;

	ManagedObject<char*,EnvInterface64Impl,__SizeType> mbuf(stdEnv);

	char *buf=mbuf.getOnlyBuffer(headingByte + bufsize);//为了兼容
	if(buf==NULL)
		return 0;

	fs.seekg(sysStart);
	if(maxLen==0)
		maxLen = fcount - sysStart;

	__SizeType leftLen=maxLen;
	__SizeType sysFileLeft = fcount - sysStart;
	__SizeType start=x2Start;
	while(leftLen>0 && sysFileLeft>0)
	{
		__SizeType thisAvl = (bufsize > sysFileLeft? sysFileLeft:bufsize);
		fs.read(buf + headingByte, thisAvl);
		util._randomWriteFile(buf, thisAvl,fnode, start);
		sysFileLeft-=thisAvl;
		leftLen-=thisAvl;
		start+=thisAvl;
	}


	fs.close();
	return (maxLen - leftLen);

}
template <class __StdEnv,class __SizeType>
__SizeType FileOperation<__StdEnv,__SizeType>::writeSysFileFromX2File(const __String &sysFile,__SizeType sysStart,
							const __String &x2File,__SizeType x2Start,
							__SizeType maxLen)
{
	FileNode *fnode=util.locatePath(curNode, x2File.c_str());
	__SizeType flen;
	if(fnode==NULL || (flen=fnode->getData().getFileLen()) <= x2Start)
	{
		stdEnv->printf_simple("error,file in x2 not exists or no a single byte is"
				" available at given position\n");
		return 0;
	}

	std::fstream fs(sysFile,std::fstream::in|std::fstream::out|std::fstream::binary);//如果文件不存在，打开空的
	if(!fs.is_open()) // 文件不存在
		fs.open(sysFile, std::fstream::out);

	// 申请 4KB的buffer，然后循环读取
	const __SizeType headingByte = (x2Start%CONST_SECSIZE);
	const __SizeType bufsize=4*2*CONST_SECSIZE;

	ManagedObject<char*,EnvInterface64Impl,__SizeType> mbuf(stdEnv);

	char *buf=mbuf.getOnlyBuffer(headingByte + bufsize);//为了兼容x2随机写的需求
	if(buf==NULL)
		return 0;

	fs.seekp(sysStart);
	if(maxLen==0)
		maxLen = flen - x2Start;

	__SizeType leftLen = maxLen;
	__SizeType x2FileLeft = flen - x2Start;
	__SizeType start = x2Start;
	while(leftLen>0 && x2FileLeft>0)
	{
		__SizeType thisAvl = (bufsize > x2FileLeft? x2FileLeft:bufsize);
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

template <class __StdEnv,class __SizeType>
bool FileOperation<__StdEnv,__SizeType>::checkIsFile(const __String & fname,FileNode *&fnode)const
{
	bool exist=checkExits(fname, fnode) ;
	if(exist && fnode->getData().getType()!=__FileDescriptor::TYPE_FILE){
		errorNotAFile(fname);
		return false;
	}
	return exist;
}
template <class __StdEnv,class __SizeType>
bool FileOperation<__StdEnv,__SizeType>::checkIsDir(const __String & fname,FileNode *&fnode)const
{
	bool exist=checkExits(fname, fnode) ;
	if(exist && fnode->getData().getType()!=__FileDescriptor::TYPE_DIR){
		errorNotADir(fname);
		return false;
	}
	return exist;
}

template <class __StdEnv,class __SizeType>
bool FileOperation<__StdEnv,__SizeType>::checkExits(const __String & fname,FileNode *&fnode)const
{
	fnode = util.locatePath(curNode, fname.c_str());
	if(fnode==NULL)
	{
		errorFileNotExits(fname);
		return false;
	}
	return true;
}
template <class __StdEnv,class __SizeType>
void FileOperation<__StdEnv,__SizeType>::errorFileNotExits(const __String & fname)const
{
	stdEnv->printf_simple("file/dir \"");
	stdEnv->printf_simple(fname.c_str());
	stdEnv->printf_simple("\" not exists.\n");
	stdEnv->flushOutputs();
}
template <class __StdEnv,class __SizeType>
void FileOperation<__StdEnv,__SizeType>::errorNotAFile(const __String & fname)const
{
	stdEnv->printf_simple("name \"");
	stdEnv->printf_simple(fname.c_str());
	stdEnv->printf_simple("\" not a file.\n");
	stdEnv->flushOutputs();
}

template <class __StdEnv,class __SizeType>
void FileOperation<__StdEnv,__SizeType>::errorNotADir(const __String &fname)const
{
	stdEnv->printf_simple("file \"");
	stdEnv->printf_simple(fname.c_str());
	stdEnv->printf_simple("\" not a dir.\n");
	stdEnv->flushOutputs();
}

template <class __StdEnv,class __SizeType>
void FileOperation<__StdEnv,__SizeType>::refreshCurrentPath()
{
	curPath.clear();
	FileNode *head=(FileNode*)util.getFileTree()->getHead();

//	TreeNode<FileDescriptor> *ip=tree.getHead();

	FileNode *p=curNode;
//	vector<string>::size_type i=1;
	while(p!=head)
	{
		size_t nlen;
		char* str=util.getFileNameCstr(p->getData(), nlen);
		curPath.insert(curPath.begin(),__String(str));
		p = (FileNode*)p->getDirectFather();
	}
}

