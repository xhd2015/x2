/*
 * CMDUtil_rwfile.cpp
 *
 *  Created on: Nov 30, 2017
 *      Author: 13774
 */

#include <common/Getopt.h>
#include <vector>
#include <string>
#include <iostream>
#include <EnvInterface64Impl.h>
#include <File.h>

using namespace std;

//const char *helpMsg=R"+*(
/////**
//// *  从命令行指定文件，读取或者写入到x2的文件系统
//// *  用法：
//// *   CMDUtil_rwfile [选项]  x2文件系统文件
//// *  选项如下：
//// *  	-r,	--read		从x2文件系统读取到系统文件
//// *  	-w,	--write		从系统文件写到x2文件系统
//// *  	-i,	--x2img		指定选用的x2磁盘镜像
//// *  	-o,	--x2offset	指定x2文件系统的偏移,默认为0
//// *  	-g,	--fsoffset	指定系统文件的偏移，默认为0
//// *  	-l,	--length	指定大小,默认为文件长度
//// *  	-f,	--fsfile	指定系统文件
//// *  	-h,	--help		显示此帮助信息
//// *  	-v,	--version	打印版本号
//// *    -c,	--cd		在进行操作之前，x2文件系统先切换到目录下
//// */
//)+*";


template <class T>
bool checkHasNextArg(const vector<T>& vec,typename vector<T>::const_iterator it,bool &hasError)
{
	if(it+1 >= vec.cend())
	{
		cerr << "arguments not enough"<<endl;
		hasError=true;
	}
	hasError=false;
	return !hasError;
}




// 高度特华的不需要模板
int main(int argc,char *argv[])
{
	// 形成参数
	vector<string> args;
	for(int i=1;i<argc;++i)
		args.push_back(argv[i]);


	// 所有的选项
	enum{
		INDEX_READ,
		INDEX_WRITE,
		INDEX_IMG,
		INDEX_X2OFFSET,INDEX_LENGTH,
		INDEX_FROM,
		INDEX_FSOFFSET,INDEX_HELP,INDEX_VERSION,INDEX_CD
	};

	CommandOptions<string,partial_vec> opts{
				{"-r","--read",false,"从x2文件系统读取到系统文件"},
				{"-w","--write",false,"从系统文件写到x2文件系统"},
				{"-i","--x2img",true,"指定选用的x2磁盘镜像"},
				{"-o","--x2offset",true,"指定x2文件系统的偏移,默认为0"},
				{"-l","--length",true,"指定系统文件的偏移，默认为0"},
				{"-f","--fsfile",true,"指定大小,默认为文件长度"},
				{"-g","--fsoffset",true,"指定系统文件"},
				{"-h","--help",true,"显示此帮助信息"},
				{"-v","--version",true,"打印版本号"},
				{"-c","--cd",true,"在进行操作之前，x2文件系统先切换到目录下"}
		};
	string helpMsg = opts.makeHelpMessage("从命令行指定文件，读取或者写入到x2的文件系统",
			"CMDUtil_rwfile [选项]  x2文件系统文件", "");

	// 所有要设置的变量
	enum{
		READ,WRITE
	};
	int mode=READ;
	string hddfile;
	size_t x2offset=0;
	size_t fsoffset=0;
	size_t length=0;
	string frompath;
	string x2path;
	string cdpath;

	bool hasError=false;

	// 开始处理参数
	auto it=args.cbegin();
	while(it<args.cend())
	{
		auto itopt=opts.find(*it);
		if(itopt!=opts.cend())//found
		{
			int index=itopt - opts.cbegin();  //传递index, itopt,it, opts,args等参数，it可以自由决定
			if(index==INDEX_READ)
				mode=READ;
			else if(index==INDEX_WRITE)
				mode=WRITE;
			else if(index == INDEX_IMG){ //需要参数
				if(!checkHasNextArg(args, it,hasError))break;
				hddfile=*(it+1);
				++it;
			}else if(index == INDEX_LENGTH){
				if(!checkHasNextArg(args, it,hasError))break;
				length=atoi((it+1)->c_str());
				++it;
			}else if(index == INDEX_X2OFFSET){
				if(!checkHasNextArg(args, it,hasError))break;
				x2offset=atoi((it+1)->c_str());
				++it;
			}else if(index == INDEX_FSOFFSET){
				if(!checkHasNextArg(args, it,hasError))break;
				fsoffset=atoi((it+1)->c_str());
				++it;
			}else if(index == INDEX_FROM){
				if(!checkHasNextArg(args, it,hasError))break;
				frompath=*(it+1);
				++it;
			}else if(index == INDEX_HELP){
				cout << helpMsg << endl;
				return EXIT_SUCCESS;
			}else if(index == INDEX_VERSION){
				cout << "Version:1.0"<<endl;
				return EXIT_SUCCESS;
			}else if(index == INDEX_CD){
				if(!checkHasNextArg(args, it,hasError))break;
				cdpath=*(it+1);
				++it;
			}
		}else{ //参数处理错误
			x2path=*it;
		}
		++it;
	}


	for(int i=0;i<argc;++i)
		cout << argv[i]<< " ";
	cout << endl;

	// 参数处理完毕
	cout	<< "mode="<<mode
			<<",imgfile="<<hddfile
			<<",fsfile="<<frompath
			<<", x2path="<<x2path
			<<", cdpath="<<cdpath
			<<", length="<<length
			<<", x2offset="<<x2offset
			<<", fsoffset="<<fsoffset
			<<endl
			<<"hasError="<<hasError
			<<endl;
	// 检查是否所有属性已经设置
	if(hddfile.size()==0 ||
			frompath.size()==0 ||
			x2path.size()==0)
	{
		cerr << "invalid argument"<<endl;
		hasError = true;
	}else{
		StdEnv64Impl *env=StdEnv64Impl::getInstance(hddfile.c_str());
		FileOperation<StdEnv64Impl,size_t> fop(env,0x80,0x3000);
		if(cdpath.size()>0)
		{
			if(!fop.cd(cdpath))
			{
				cerr << "cannot cd to \""<<cdpath<<"\""<<endl;
				hasError=true;
			}
		}
		if(!hasError)
		{
			if(mode==READ)
			{
				fop.writeSysFileFromX2File(frompath, fsoffset, x2path, x2offset, length);
			}else{
				fop.readSysFileToX2File(frompath, fsoffset, x2path, x2offset, length);
			}
		}
	}


	return hasError?EXIT_FAILURE:EXIT_SUCCESS;

}

