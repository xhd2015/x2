
 //CODE64 ONLY
#include <File.h>

#if !defined(CODE64)
#error "CODE64 ONLY"
#endif

#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <string>
#include <64/CMDUtil.h>
#include <List.h>
#include <common/Getopt.h>

#if defined(CODE64)
#include <string>
using namespace std;

CommandOptions opts{
			{"-s","--basic-size",true,"文件系统的基本尺寸,默认为系统的sizeof(size_t)"},
			{"","--16",false,"等价于-s 2"},
			{"","--32",false,"等价于-s 4"},
			{"","--64",false,"等价于-s 8"},
			{"-l","--lbalow",true,"lba低32位地址,必须指定"},
			{"-g","--lbahigh",true,"lba高32位地址，默认为0"},
			{"-n","--secnum",true,"扇区总数,必须指定"},
			{"-r","--reservednum",true,"保留扇区数目"},
			{"-m","--metanum",true,"元信息区域扇区数目"},
			{"-h","--help",false,"显示此帮助信息"},
			{"-v","--version",false,"打印版本号"},
	};
string helpMsg = opts.makeHelpMessage("格式化分区为x2文件系统",
		"CMDUtil_mkfs.x2fs [选项]  镜像文件", "");

class MyPorcessor:public CommandProcessor<ParamMkfs>
{
public:
	MyPorcessor(){}
	virtual int onProcessArgOpt(ParamMkfs &pack,__OptPosIterator itopt,__VS_cit itarg) override{
		if(itopt->equals("-s"))
		{
			pack.basicSize = atoi((itarg+1)->c_str());
		}else if(itopt->equals("--16")){
			pack.basicSize=2;
		}else if(itopt->equals("--32")){
			pack.basicSize=4;
		}else if(itopt->equals("--64")){
			pack.basicSize=8;
		}else if(itopt->equals("-l")){
			pack.lbaLow=atoi((itarg+1)->c_str());
			pack.lbaLowSet=true;
		}else if(itopt->equals("-g")){
			pack.lbaHigh=atoi((itarg+1)->c_str());
		}else if(itopt->equals("-n")){
			pack.wholeSecNum=atoi((itarg+1)->c_str());
			pack.wholeSecNumSet = true;
		}else if(itopt->equals("-r")){
			pack.reserved=atoi((itarg+1)->c_str());
		}else if(itopt->equals("-m")){
			pack.meta=atoi((itarg+1)->c_str());
		}
		return ERROR_NO_ERROR;
	}

	virtual int onProcessArgTarget(ParamMkfs &pack,__VS_cit itarg)override
	{
		pack.imgFile = *itarg;
		return ERROR_NO_ERROR;
	}

	virtual int onProcessPost(ParamMkfs &pack)override
	{
		if(pack.imgFile.empty() || !pack.wholeSecNumSet
				|| !pack.lbaLowSet)
		{
			return ERROR_ARG_NOT_ENOUGH;
		}else{
			return ERROR_NO_ERROR;
		}
	}


	virtual int onProcessHelp(ParamMkfs &pack)override
	{
		cout << helpMsg << endl;
		return ERROR_NORMAL_EXIT;
	}
	virtual int onProcessVersion(ParamMkfs &pack)override
	{
		cout << "Version 1.0"<<endl;
		return ERROR_NORMAL_EXIT;
	}
};


template <class __FsEnv>
void process(const ParamMkfs & param);

/**
 * 开辟一个内存块，格式化，然后将其保存到文件中作为磁盘。
 */
int main(int argc,char *argv[])
{
 	vector<string> args(argv+1,argv+argc);
	ParamMkfs param;
	MyPorcessor prep;
	int status=prep.processOptions(opts, args.begin(),args.end(), param);

	if(status==MyPorcessor::RETURN_CONTINUE)
	{
		if(param.basicSize==2)
		{
			process<EnvTransfer<32>>(param);
			status = MyPorcessor::RETURN_DONE;
		}else if(param.basicSize==4){
			process<EnvTransfer<32>>(param);
			status = MyPorcessor::RETURN_DONE;
		}else if(param.basicSize==8){
			process<EnvTransfer<64>>( param);
			status = MyPorcessor::RETURN_DONE;
		}else{
			cerr << "Unsupported basic size type:"<<param.basicSize<<endl;
			status = MyPorcessor::RETURN_ERROR;
		}
	}

	return (status!=MyPorcessor::RETURN_ERROR?EXIT_SUCCESS : EXIT_FAILURE);

}

template <class __FsEnv>
void process(const ParamMkfs & param)
{
	using __X2fsUtil = X2fsUtil<__FsEnv>;
	using __X2fsMetaInfo =X2fsMetaInfo;
	__X2fsMetaInfo metainfo{
		param.lbaLow,param.lbaHigh,param.wholeSecNum,
		param.basicSize,param.reserved,param.meta
	};

	std::cout << "information about metainfo"<<std::endl;
	metainfo.dumpInfo();
	std::cout << std::endl;

	u8_t driver=HostEnv::addFile(param.imgFile,param.lbaLow);
	__X2fsUtil::mkfs(driver, metainfo);

	printf("re-reading the information to validate....");
	__X2fsUtil util { driver, metainfo.getLbaBaseLow(), metainfo.getLbaBaseHigh() };
	if(!util.getMetainfo().isValid())
	{
		printf("validating failed!\n");
	}else{
		printf("validating succeed!\n");
	}
	printf("end.\n");
	HostEnv::flushOutputs();
}

#endif
