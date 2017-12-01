
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

CommandOptions<StdEnv64Impl> opts{
			{"-s","--basic-size",true,"文件系统的基本尺寸,默认为系统的sizeof(size_t)"},
			{"","--16",false,"等价于-s 2"},
			{"","--32",false,"等价于-s 4"},
			{"","--64",false,"等价于-s 8"},
			{"-l","--lbalow",true,"lba低32位地址,必须指定"},
			{"-g","--lbahigh",true,"lba高32位地址，默认为0"},
			{"-n","--secnum",true,"扇区总数,必须指定"},
			{"-m","--namesecs",true,"name区总数,0或者默认则为"},
			{"-d","--dirsecs",true,"dir区总数，0或者默认则为"},
			{"-f","--freesecs",true,"free区总数,0或者默认则为"},
			{"-k","--linksecs",true,"link区总数,0或者默认则为"},
			{"-2","--secdsecs",true,"二级加载器预留扇区数目,默认为0"},
			{"-h","--help",false,"显示此帮助信息"},
			{"-v","--version",false,"打印版本号"},
	};
string helpMsg = opts.makeHelpMessage("格式化分区为x2文件系统",
		"CMDUtil_mkfs.x2fs [选项]  镜像文件", "");

class MyPorcessor:public CommandProcessor<StdEnv64Impl,ParamMkfs>
{
public:
	MyPorcessor(StdEnv64Impl &env):CommandProcessor(env){}
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
			pack.wholeSecNumSet=true;
		}else if(itopt->equals("-m")){
			pack.secSpaces[X2fsMetaInfo<size_t>::INDEX_NAME]=atoi((itarg+1)->c_str());
		}else if(itopt->equals("-d")){
			pack.secSpaces[X2fsMetaInfo<size_t>::INDEX_DIR]=atoi((itarg+1)->c_str());
		}else if(itopt->equals("-f")){
			pack.secSpaces[X2fsMetaInfo<size_t>::INDEX_FREE]=atoi((itarg+1)->c_str());
		}else if(itopt->equals("-k")){
			pack.secSpaces[X2fsMetaInfo<size_t>::INDEX_LINK]=atoi((itarg+1)->c_str());
		}else if(itopt->equals("-2")){
			pack.optional[X2fsMetaInfo<size_t>::INDEX_OPTIONAL_SECD]=atoi((itarg+1)->c_str());
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


template <class __StdEnv,class __SizeType>
void process(__StdEnv &env,const ParamMkfs & param);

/**
 * 开辟一个内存块，格式化，然后将其保存到文件中作为磁盘。
 */
int main(int argc,char *argv[])
{
	vector<string> args(argv+1,argv+argc);
	ParamMkfs param;
	StdEnv64Impl env;
	MyPorcessor prep(env);
	int status=prep.processOptions(opts, args.begin(),args.end(), param);

	if(status==MyPorcessor::RETURN_CONTINUE)
	{
		EnvInterface64Impl env(param.imgFile.c_str());
		if(param.basicSize==2)
		{
//			process<EnvInterface64Impl,u16_t>(env,param);
			status = MyPorcessor::RETURN_DONE;
		}else if(param.basicSize==4){
//			process<EnvInterface64Impl,u32_t>(env,param);
			status = MyPorcessor::RETURN_DONE;
		}else if(param.basicSize==8){
			process<EnvInterface64Impl,size_t>(env, param);
			status = MyPorcessor::RETURN_DONE;
		}else{
			cerr << "Unsupported basic size type:"<<param.basicSize<<endl;
			status = MyPorcessor::RETURN_ERROR;
		}
	}

	return (status!=MyPorcessor::RETURN_ERROR?EXIT_SUCCESS : EXIT_FAILURE);

}

template <class __StdEnv,class __SizeType>
void process(__StdEnv &env,const ParamMkfs & param)
{
	X2fsMetaInfo<__SizeType> metainfo;
	metainfo.lbaStartLow = param.lbaLow;
	metainfo.lbaStartHigh = param.lbaHigh;
	metainfo.wholeSecnums =param.wholeSecNum;
	for(size_t i=0;i<metainfo.PARTS_REQUIRED;++i)
		metainfo.secnums[i]=param.secSpaces[i];
	for(size_t i=0;i<metainfo.PARTS_OPTIONAL;++i)
			metainfo.optional[i]=param.optional[i];


	std::cout << "information about metainfo"<<std::endl;
	metainfo.dumpInfo(&env);
	std::cout << std::endl;

	if(!X2fsMetaInfo<__SizeType>::checkMetainfo(&metainfo))
		printf("cannot validate metainfo\n");
	else
		X2fsUtil<__StdEnv,__SizeType>::mkfs(&env, 0x80, &metainfo);

	printf("re-reading the information to validate....");
//	X2fsMetaInfo *buf=(X2fsMetaInfo*)env->malloc(sizeof(X2fsMetaInfo));
//	X2fsMetaInfo *buf = new X2fsMetaInfo;
	u8_t *buf = env.malloc(metainfo.metaSec * CONST_SECSIZE);
	X2fsMetaInfo<size_t> *readMetainfo=(X2fsMetaInfo<size_t>*)buf;
	env.readSectors(EnvInterface::CUR_SEG, buf,0x80,0x3000+2, 1, 0);
	if(!X2fsMetaInfo<size_t>::checkMetainfo(readMetainfo))
	{
		printf("validating failed!\n");
	}else{
		printf("validating succeed!\n");
	}
	env.flushOutputs();


	env.free(buf);

	printf("end.\n");
	env.flushOutputs();
}

#endif
