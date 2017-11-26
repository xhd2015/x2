
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

typedef char *STR_ARR_PTR_TYPE[];

vector<string> spaceSplit(const string& s);
/**
 *  @return the result
 *
 *  some rules: for instance, re='/+',the incoming result should be
 *    'a'  --> ['a']
 *    ''   --> ['']
 *    	上面两个实例表明，如果末尾没有/,应当认为其有一个结尾的/
 *    '/'  --> ['']
 *    'a/b' --> ['a','b']
 *    '/a/b/' --> ['','a','b']
 */
vector<string> regexSplit(const regex& re,const string& s);


/**
 *  属性：一个表示状态的当前目录，上一个目录
 *  方法：help ls cd rm mkdir touch cat pwd plwd(-last-)
 */
class FileOperation{
protected:
	typedef X2fsUtil<EnvInterface64Impl>::FileNode FileNode;
public:
	FileOperation()=delete;
	FileOperation(const string& img);
	void help();
	void ls();
	/**
	 * 一般cd命令，如果出错则打印错误信息，设置错误代码（如果有）
	 *
	 * 支持多种模式，参数可以是一个，也可以是多个
	 */
	void cd(const std::string& strPath);

	/**
	 * cd XXX, 从当前目录下开始
	 *
	 * 注意，path数组可以含有特殊含义的目录，比如 ., .., 它们不会被当做一般的目录名称处理
	 */
	void cdFromCur(vector<string>::const_iterator begin,vector<string>::const_iterator end);

	/**
	 * cd -的函数
	 */
	void cdLast();
	/**
	 * cd ..的函数
	 */
	void cdBack();

	/**
	 *  cd /
	 */
	void cdRoot();
	void rm(const string & fname);
	/**
	 *  @param dir  a simple,1-level dirname,such as 'foo',but not 'foo/bar'
	 */
	void mkdir(const string & dir);
	void touch(const string & fname,FileDescriptor::SizeType secNum,FileDescriptor::TimeType ctime);
	void cat();
	void pwd();
	void changeImage(const string& img);//change to another disk
//	DEPRECATED
	const std::string& curDir();
//	static void splitPaths(const string& path,int maxNum,int &retNum,STR_ARR_PTR_TYPE &retPtr);
protected:
	void refreshCurrentPath();

	string curImage;
	X2fsUtil<EnvInterface64Impl> util;
	/**
	 *  当lastNode为NULL时，表明没有上一个目录
	 */
	FileNode *curNode,*lastNode;
	vector<string> curPath;

};


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
	EnvInterface64Impl::setHDDFile(imgFile.c_str());
	FileOperation op(imgFile);



	while(
			prompt(op.curDir()) &&
			prompt(">") &&
			getline(cin,cmd))
	{
		//parse all args
		//将其用正则表达式分解成数组格式
		vector<string> args=spaceSplit(cmd);
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
		}else if(args[0].compare("quit")==0 || args[0].compare("exit")==0){
			break;
		}else{
			cout << "Unrecognized command '" << args[0] << "'." << endl;
		}
		fflush(stdout);
	}

	return 0;
}

/**
 * 假设全都以空格分隔
 */
vector<string> spaceSplit(const string& s)
		{
			string::size_type start=0;

			vector<string> res;
			while(start<s.size() && start>=0)
			{
				while(s[start]==' ' && start<s.size())start++;//定位到第一个非空
				if(start>=s.size())break;
				auto end=s.find(' ',start);
				res.push_back(s.substr(start,end-start));
				start=end;
			}
			return std::move(res);
		}

vector<string> regexSplit(const regex& re, const string& s) {
	const string::const_iterator begin = s.cbegin();
	auto itBeg = begin;
	vector<string> res;
	smatch allmatch;

	while (itBeg != s.end() && regex_search(itBeg, s.cend(), allmatch, re)) {
		// pos,len 每次迭代时，当还有时,应将beg~pos之间保留，然后beg变换到length之后
		res.push_back(s.substr(itBeg - begin, allmatch.position()));
		auto len = allmatch.length() + allmatch.position();
		if (s.cend() - itBeg <= len) //超出范围
			break;
		itBeg += len;
	}
	if(itBeg!=s.end())
	{
		res.push_back(s.substr(itBeg - begin));
		itBeg = s.end();
	}

	return std::move(res);
}


FileOperation::FileOperation(const string& img):
		curImage(img),util(EnvInterface64Impl::getInstance(), 0x80, 0x3000)
{
//	cout << "FileOperation init" <<endl;
	curPath.push_back("");//根目录
//	cout << "getHead before"<<endl;
	auto tree=util.getFileTree();
//	cout << "after get tree"<<endl;
	curNode = (FileNode*)tree.getHead();
	lastNode = NULL;
}
void FileOperation::help()
{
	cout << R"+*( 
       help
       ls
       pwd
       mkdir dirName
       cd pathName
       rm fname
       touch  fname secNum ctime
       exit
       quit
            注:pathName可以含有任意组合的路径,但是fname,dirName不被视为路径而是普通文件名
)+*" ;
}



void FileOperation::ls()
{
	util.listNode(curNode);
}

void FileOperation::cd(const string& strPath)
{
	vector<string> paths=regexSplit(regex("/+"), strPath);
	if(paths.size()==0) // no argument
	{
		//do nothing or cd home
	}else if(paths.size()==1 && paths[0].compare("-")==0) // cd last
	{
		cdLast();
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

		cdFromCur(it,paths.cend());
	}

}

void FileOperation::cdFromCur(vector<string>::const_iterator begin,vector<string>::const_iterator end)
{
	FileNode *tempCur=curNode;
	FileNode *temp=NULL;
	int npushed=0;//记录已经加入path的长度,负数表示需要移除,0表示不变
	vector<string> appendPaths;


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
				cerr << "there is some error in your path,check it again"<<endl;
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
				cerr << "directory \""<<*p<<"\" does not exist"<<endl;
				isError=true;
				break;
			}else if(!util.isDirectory(temp)){
				cerr << "\""<<*p<<"\" is not a directory"<<endl;
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
}
void FileOperation::cdLast()
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
}
void FileOperation::cdRoot()
{
	lastNode=curNode;
	curPath.clear();
	curPath.push_back("");
}
void FileOperation::rm(const string & fname)
{
	util.seterrno(X2fsUtil<EnvInterface64Impl>::ERROR_NOERR);
	FileNode *fnode=util.locatePath(curNode, fname.c_str());
	if(fnode==NULL)
	{
		cerr << "file/directory \""<<fname<<"\" does not exists"<<endl;
	}else{
		util.removeNode(fnode);
	}
}
void FileOperation::mkdir(const string& dir)
{
	util.seterrno(X2fsUtil<EnvInterface64Impl>::ERROR_NOERR);
	util.create(curNode, FileDescriptor::TYPE_DIR, dir.c_str(), 0,0);
	if(util.geterrno() == X2fsUtil<EnvInterface64Impl>::ERROR_FILE_ALREDY_EXIST)
	{
		cerr << "file/directory \""<<dir<<"\" already exists"<<endl;
	}
}
void FileOperation::touch(const string & fname,FileDescriptor::SizeType secNum,FileDescriptor::TimeType ctime)
{
	util.seterrno(X2fsUtil<EnvInterface64Impl>::ERROR_NOERR);
	util.create(curNode, FileDescriptor::TYPE_FILE, fname.c_str(), secNum,ctime);
	if(util.geterrno()!=X2fsUtil<EnvInterface64Impl>::ERROR_NOERR)
	{
		cerr << "error code is "<<util.geterrno()<<endl;
	}
	if(util.geterrno() == X2fsUtil<EnvInterface64Impl>::ERROR_FILE_ALREDY_EXIST)
	{
		cerr << "file/directory \""<<fname<<"\" already exists"<<endl;
	}
}
void FileOperation::cat()
{
	cout << "method unsupported"<<endl;
}
void FileOperation::pwd()
{
	for(string& s:curPath)
	{
		cout << s << "/";
	}
	cout << endl;
}
void FileOperation::changeImage(const string& img)
{
	cout << "method unsupported"<<endl;
}
const string& FileOperation::curDir()
{
	return curPath[curPath.size()-1];
}

void FileOperation::refreshCurrentPath()
{
	curPath.clear();
	FileNode *head=(FileNode*)util.getFileTree().getHead();
	X2fsUtil<EnvInterface64Impl>::FileTree tree=util.getFileTree();
//	TreeNode<FileDescriptor> *ip=tree.getHead();

	FileNode *p=curNode;
//	vector<string>::size_type i=1;
	while(p!=head)
	{
		size_t nlen;
		char* str=util.getFileNameCstr(p->getData(), nlen);
		curPath.insert(curPath.begin(),string(str));
		p = (FileNode*)p->getDirectFather();
	}
}


#endif
