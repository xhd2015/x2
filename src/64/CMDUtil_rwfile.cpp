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
#include <64/CMDUtil.h>

using namespace std;

CommandOptions<StdEnv64Impl> opts{
			{"-r","--read",false,"从x2文件系统读取到系统文件"},
			{"-w","--write",false,"从系统文件写到x2文件系统"},
			{"-i","--x2img",true,"指定选用的x2磁盘镜像"},
			{"-o","--x2offset",true,"指定x2文件系统的偏移,默认为0"},
			{"-l","--length",true,"指定系统文件的偏移，默认为0"},
			{"-f","--fsfile",true,"指定大小,默认为文件长度"},
			{"-g","--fsoffset",true,"指定系统文件"},
			{"-h","--help",false,"显示此帮助信息"},
			{"-v","--version",false,"打印版本号"},
			{"-c","--cd",true,"在进行操作之前，x2文件系统先切换到目录下"}
	};
string helpMsg = opts.makeHelpMessage("从命令行指定文件，读取或者写入到x2的文件系统",
		"CMDUtil_rwfile [选项]  x2文件系统文件", "");

class MyPorcessor:public CommandProcessor<StdEnv64Impl,Param>
{
public:
	MyPorcessor(StdEnv64Impl &env):CommandProcessor(env){}
	virtual int onProcessArgOpt(Param &pack,__OptPosIterator itopt,__VS_cit itarg) override{
		if(itopt->equals("-r"))
		{
			pack.mode=pack.READ;
		}else if(itopt->equals("-w")){
			pack.mode=pack.WRITE;
		}else if(itopt->equals("-i")){
			pack.hddfile = *(itarg+1);
		}else if(itopt->equals("-o")){
			pack.x2offset = atoi( (itarg+1)->c_str());
		}else if(itopt->equals("-l")){
			pack.length = atoi( (itarg+1)->c_str());
		}else if(itopt->equals("-f")){
			pack.fsfile = *(itarg+1);
		}else if(itopt->equals("-g")){
			pack.fsoffset= atoi( (itarg+1)->c_str());
		}else if(itopt->equals("-c")){
			pack.cdpath = *(itarg+1);
		}

		return ERROR_NO_ERROR;
	}

	virtual int onProcessArgTarget(Param &pack,__VS_cit itarg)override
	{
		pack.x2file = *itarg;
		return ERROR_NO_ERROR;
	}

	virtual int onProcessPost(Param &pack)override
	{
		if(pack.x2file.empty() || pack.fsfile.empty() || pack.hddfile.empty())
		{
			return ERROR_ARG_NOT_ENOUGH;
		}else{
			return ERROR_NO_ERROR;
		}
	}


	virtual int onProcessHelp(Param &pack)override
	{
		cout << helpMsg << endl;
		return ERROR_NORMAL_EXIT;
	}
	virtual int onProcessVersion(Param &pack)override
	{
		cout << "Version 1.0"<<endl;
		return ERROR_NORMAL_EXIT;
	}
};



// 高度特华的不需要模板
int main(int argc,char *argv[])
{
	// 形成参数
	vector<string> args(argv+1,argv+argc);
	// 打印参数
	for(int i=0;i<argc;++i)
			cout << argv[i]<< " ";
		cout << endl;

	StdEnv64Impl env("");
	MyPorcessor prep(env);
	Param p;
	int status=prep.processOptions(opts, args.cbegin(),args.cend(), p);
	// 参数处理完毕
		cout	<< "mode="<<p.mode
				<<",imgfile="<<p.hddfile
				<<",fsfile="<<p.fsfile
				<<", x2file="<<p.x2file
				<<", cdpath="<<p.cdpath
				<<", length="<<p.length
				<<", x2offset="<<p.x2offset
				<<", fsoffset="<<p.fsoffset
				<<endl;
	if(status==MyPorcessor::RETURN_CONTINUE)
	{
			env.setFile(p.hddfile.c_str());
			FileOperation<StdEnv64Impl,size_t> fop(&env,0x80,0x3000);
			if(p.cdpath.size()==0 || fop.cd(p.cdpath) )
			{
				if(p.mode==p.READ)
				{
					fop.writeSysFileFromX2File(p.fsfile, p.fsoffset, p.x2file,p.x2offset, p.length);
				}else{
					fop.readSysFileToX2File(p.fsfile, p.fsoffset, p.x2file, p.x2offset, p.length);
				}
			}
	}

	return (status!=MyPorcessor::RETURN_ERROR?EXIT_SUCCESS : EXIT_FAILURE);

}

