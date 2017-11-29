
#include <def.h>

#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include <exception>
#include <EnvInterface64Impl.h>
#include <File.h>

#include <macros/all.h>



#if defined(CODE64)

using namespace std;

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
	string cmd;
	string imgFile;
	if(argc<2)
	{
		cout << "You must specify an image file,please input a file:";
		cin >> imgFile;
	}else{
		imgFile=argv[1];
	}


//	cout << "DEBUG argv[1] is "<<argv[1]<<endl;

	// 注意，由于采用单例模式，所以该类只有一个文件指针

	StdEnv64Impl *envInstance = StdEnv64Impl::getInstance(imgFile.c_str());
	FileOperation<StdEnv64Impl,size_t> op(envInstance,0x80,0x3000);


	// DEBUG
//	op.touch("file",4,0);
//	string content("dddddddddddddddddddddddddddddddd");
//	op.write("file", 5,content.c_str(), content.length());
//	op.read("file", 5, 512);
//	op.ls();
//	return 0;

//	string content2("eeeeeeeeeeee");
//	op.write("file",1,content2.c_str(),content2.length());
//	op.ls();

//	envInstance->spaceSplit("mkdir yes");

	while(
			prompt(op.curDir()) &&
			prompt(">") &&
			getline(cin,cmd))
	{
		//parse all args
		//将其用正则表达式分解成数组格式
		vector<string> args=envInstance->spaceSplit(cmd);
		if(args.size()==0)continue;
		if(args[0].compare("help")==0)
		{
			op.help();
		}else if(args[0].compare("ls")==0){
			op.ls();
		}else if(args[0].compare("pwd")==0){
			op.pwd();
		}else if(args[0].compare("mkdir")==0){
			op.mkdir(args[1]);
		}else if(args[0].compare("cd")==0){
			if(args.size() < 2)
				continue;
			else
				op.cd(args[1]);
		}else if(args[0].compare("rm")==0){
			op.rm(args[1]);
		}else if(args[0].compare("touch")==0){
			if(args.size() < 4)
			{
				cerr << "see help for touch"<<endl;
			}else{
				op.touch(args[1], atoi(args[2].c_str()),atoi(args[3].c_str()));
			}
		}else if(args[0].compare("write")==0){
			if(args.size() < 4)// write file StartSec dddddddddddddd...
			{
				cerr << "see help for write" << endl;
			}else{
				op.write(args[1], atoi(args[2].c_str()),args[3].c_str(), args[3].length());
			}
		}else if(args[0].compare("read")==0){
			//read file StartSec ByteNum
			if(args.size() < 4)
				cerr << "see help for read"<<endl;
			else
			{
				op.read(args[1],atoi(args[2].c_str()), atoi(args[3].c_str()));
			}

		}else if(args[0].compare("quit")==0 || args[0].compare("exit")==0){
			break;
		}else{
			cout << "Unrecognized command '" << args[0] << "'." << endl;
		}
		fflush(stdout);
	}

	return 0;
}

#endif
