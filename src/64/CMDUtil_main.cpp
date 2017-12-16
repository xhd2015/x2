
#include <def.h>

#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include <exception>
#include <EnvInterface64Impl.h>
#include <File.h>
#include <64/CMDUtil.h>
#include <common/Getopt.h>


#if defined(CODE64)

using namespace std;



CommandOptions opts{
			{"-s","--basic-size",true,"文件系统的基本尺寸,默认为系统的sizeof(size_t)"},
			{"","--16",false,"等价于-s 2"},
			{"","--32",false,"等价于-s 4"},
			{"","--64",false,"等价于-s 8"},
			{"-l","--lbalow",true,"镜像文件的lba低32位地址"},
			{"-e","--cmd",true,"以;分隔,执行一系列命令,然后退出"},
			{"-c","--cd",true,"在进行操作之前，x2文件系统先切换到目录下"},
			{"-h","--help",false,"显示此帮助信息"},
			{"-v","--version",false,"打印版本号"},
	};
string helpMsg = opts.makeHelpMessage("指定镜像文件为x2文件系统,然后打开",
		"CMDUtil_main [选项]  x2文件系统文件", "");

class MyPorcessor:public CommandProcessor<ParamMain>
{
public:
	MyPorcessor()=default;
	virtual int onProcessArgOpt(ParamMain &pack,__OptPosIterator itopt,__VS_cit itarg) override{
		if(itopt->equals("-e")){
			pack.cmds+=pack.spiltor+ *(itarg+1);
		}else if(itopt->equals("-c")){
			pack.cdpath = *(itarg+1);
		}else	if(itopt->equals("-s")){
			pack.basicSize = atoi((itarg+1)->c_str());
		}else if(itopt->equals("--16")){
			pack.basicSize=2;
		}else if(itopt->equals("--32")){
			pack.basicSize=4;
		}else if(itopt->equals("--64")){
			pack.basicSize=8;
		}else if(itopt->equals("-l")){
			pack.lbalow = atoi( (itarg+1)->c_str());
		}
		return ERROR_NO_ERROR;
	}

	virtual int onProcessArgTarget(ParamMain &pack,__VS_cit itarg)override
	{
		pack.imgFile = *itarg;
		return ERROR_NO_ERROR;
	}

	virtual int onProcessPost(ParamMain &pack)override
	{
		if(pack.imgFile.empty())
		{
			return ERROR_ARG_NOT_ENOUGH;
		}else{
			return ERROR_NO_ERROR;
		}
	}


	virtual int onProcessHelp(ParamMain &pack)override
	{
		cout << helpMsg << endl;
		return ERROR_NORMAL_EXIT;
	}
	virtual int onProcessVersion(ParamMain &pack)override
	{
		cout << "Version 1.0"<<endl;
		return ERROR_NORMAL_EXIT;
	}
};


template <class __FsEnv>
void process(ParamMain &p,int& status);

bool prompt(const string &p)
{
	cout << p;
	return true;
}
/**
 *  read input & execute commands
 *
 *  流程：用户提供一个参数打开某个文件作为磁盘
 *
 *  进入后停留在根目录,等待用户输入
 *  用户键入help获取帮助命令，显示帮助信息
 *  用户键入cd，mkdir,rm等进行交互
 *  exit/quit退出
 *
 *  读取一行输入后(std::getline)，
 */
int main(int argc,char *argv[])
{
	vector<string> args(argv+1,argv+argc);
	// 打印参数
	for(int i=0;i<argc;++i)
			cout << argv[i]<< " ";
		cout << endl;

	MyPorcessor prep;
	ParamMain p;
	int status=prep.processOptions(opts, args.cbegin(),args.cend(), p);
	if(status==MyPorcessor::RETURN_CONTINUE)
	{
		if(p.basicSize==2)
		{
			process<EnvTransfer<16>>(p,status);
		}else if(p.basicSize==4){
			process<EnvTransfer<32>>(p,status);
		}else if(p.basicSize==8){
			process<EnvTransfer<64>>( p,status);
		}else{
			cerr << "Unsupported basic size type:"<<p.basicSize<<endl;
			status = MyPorcessor::RETURN_ERROR;
		}
	}

	return (status!=MyPorcessor::RETURN_ERROR?EXIT_SUCCESS:EXIT_FAILURE);
}

template <class __FsEnv>
void process(ParamMain &p,int& status)
{
	u8_t driver=HostEnv::addFile(p.imgFile,p.lbalow);
	FileOperation<__FsEnv> op(driver,p.lbalow);

	op.touch("file", 4, 0);
	op.randwrite("file",0,"yesyes");


	if(p.cdpath.size()>0)
		op.cd(p.cdpath);

	if(p.cmds.size()>0)
	{
		std::vector<string> cmds=HostEnv::cmdSplit(p.cmds);
		for(const std::string &cmd:cmds)
		{
			if(!op.eval(cmd))break;
		}
		status=MyPorcessor::RETURN_DONE;
	}else{
		string cmd;
		while(
				prompt(op.curDir()) &&
				prompt(">") &&
				getline(std::cin,cmd))
			if(!op.eval(cmd))break;
	}
}

#endif
