/*
 * Getopt.cpp
 *
 *  Created on: Nov 30, 2017
 *      Author: 13774
 */




#include <common/Getopt.h>


#if defined(CODE64) //模板实例化
#include <string>
#include <vector>
#include <EnvInterface64Impl.h>
#include <64/CMDUtil.h>
#endif



//===class CommandOption
#define __DEF_Template_CommandOption
#define __DEF_CommandOption CommandOption
// 几个常见选项
__DEF_Template_CommandOption
const __DEF_CommandOption __DEF_CommandOption::helpOption={"-h","--help",false,"显示此帮助信息"};
__DEF_Template_CommandOption
const __DEF_CommandOption __DEF_CommandOption::versionOption={"-v","--version",false,"显示版本信息"};
__DEF_Template_CommandOption
const __DEF_CommandOption __DEF_CommandOption::stopOption={"--","--",false,"停止"};



__DEF_Template_CommandOption
__DEF_CommandOption::CommandOption(
		const __String& shortOpt,
		const __String& longOpt,
		bool needsParam,
		const __String &helpMsg
		):
		shortOpt(shortOpt),longOpt(longOpt),needsParam(needsParam),
		helpMsg(helpMsg)
{

}

__DEF_Template_CommandOption
bool __DEF_CommandOption::equals(const __String& opt)const
{
	return shortOpt.compare(opt)==0 ||
			longOpt.compare(opt)==0;
}

__DEF_Template_CommandOption
bool __DEF_CommandOption::equals(const __CommandOption& opt)const
{
	return (this->shortOpt.compare(opt.shortOpt)==0 && this->longOpt.compare(opt.longOpt)==0);
}
__DEF_Template_CommandOption
void __DEF_CommandOption::dump()const
{

	HostEnv::printf_simple(shortOpt.c_str());
	HostEnv::printf_simple("/");
	HostEnv::printf_simple(longOpt.c_str());
}

#undef __DEF_Template_CommandOption
#undef __DEF_CommandOption


//==class CommandOptions
#define __DEF_Template_CommandOptions
#define __DEF_CommandOptions CommandOptions

__DEF_Template_CommandOptions
__DEF_CommandOptions::CommandOptions(const std::initializer_list<__CommandOption> &il):
Super(il)
{

}
__DEF_Template_CommandOptions
typename __DEF_CommandOptions::__PosIterator
__DEF_CommandOptions::find(const __String &option)const
{
	// this->必须加上
	__PosIterator itopt=this->cbegin();
	for(;itopt!=this->cend();++itopt)
	{
		if(itopt->equals(option)) // 通用
			break;
	}
	return itopt;
}
__DEF_Template_CommandOptions
typename __DEF_CommandOptions::__String
__DEF_CommandOptions::makeHelpMessage(const __String &heading,
							const __String &usage,
							const __String &foot)const
{
	__String s;
	s+="\t"+heading + "\n";
	s+="\t用法:\n\t\t";
	s+=usage;
	s+="\n\t选项:\n";
	for(const __CommandOption & option:*this)
	{
		s+="\t\t";
		if(!option.shortOpt.empty())
			s+=option.shortOpt+",";
		s+="\t";
		if(!option.longOpt.empty())
				s+=option.longOpt;
		s+="\t\t"+option.helpMsg+"\n";
	}
	s+=foot+"\n";

	return (std::move(s));
}
#undef __DEF_Template_CommandOptions
#undef __DEF_CommandOptions


//========= class CommandProcessor
#define __DEF_Template_CommandProcessor template <class __ParamPack>
#define __DEF_CommandProcessor CommandProcessor<__ParamPack>
__DEF_Template_CommandProcessor
__DEF_CommandProcessor::CommandProcessor()
{

}
__DEF_Template_CommandProcessor
int __DEF_CommandProcessor::processOptions(
		const __CommandOptions &opt,__VS_cit beg,__VS_cit end, __ParamPack &pack)
{
	int errCode=ERROR_NO_ERROR;
	errCode=this->onProcessPre(pack);
	if(errCode!=ERROR_NO_ERROR)
	{
		this->onErrorExit(errCode);
		return (RETURN_ERROR);
	}

	auto it=beg;
	while(it != end)
	{
		if(__CommandOption::stopOption.equals(*it)) // 遇见 --, 后面全部当做目标参数处理
			{ ++it;break;}

		if(it->size()>0 && it->at(0)=='-')//以-开头, 选项
		{
			auto itopt=opt.find(*it);
			if(itopt!=opt.cend())//found
			{
				if(itopt->needsParam && (it+1)==end)
				{
					this->onErrorExit(errCode = ERROR_ARG_NOT_ENOUGH, &(*itopt) );
					return (RETURN_ERROR);
				}

				if(__CommandOption::helpOption.equals(*itopt)) //help
				{
					errCode=this->onProcessHelp(pack);
					if(errCode==ERROR_NORMAL_EXIT)
					{
						this->onErrorExit(ERROR_NORMAL_EXIT);
						return (RETURN_DONE);
					}
				}
				else if(__CommandOption::versionOption.equals(*itopt)) //version
				{
					errCode=this->onProcessVersion(pack);
					if(errCode==ERROR_NORMAL_EXIT)
					{
						this->onErrorExit(ERROR_NORMAL_EXIT);
						return (RETURN_DONE);
					}
				}
				else
					errCode = this->onProcessArgOpt(pack,itopt,it); //others

				if(itopt->needsParam)
					it+=2;
				else
					++it;
			}else{ // 未知选项
				errCode = ERROR_UNKNOW_OPTION;
			}

			if(errCode!= ERROR_NO_ERROR)
			{
				__CommandOption op; //临时构造一个Option，显示其名称
				op.shortOpt=*it;
				this->onErrorExit(errCode, &op);
				return (RETURN_ERROR);
			}
		}else //target参数
		{
			if ( (errCode = this->onProcessArgTarget(pack,it++)) != ERROR_NO_ERROR)
			{
				this->onErrorExit(errCode);
				return (RETURN_ERROR);
			}
		}
	}


	//=== 处理剩余的所有参数, 即 -- 之后的所有输入
	while(it != end && (errCode = this->onProcessArgTarget(pack,it))==ERROR_NO_ERROR)++it;
	if(errCode != ERROR_NO_ERROR)
	{
		this->onErrorExit(errCode);
		return (RETURN_ERROR);
	}

	errCode = this->onProcessPost(pack);
	if(errCode != ERROR_NO_ERROR)
	{
		this->onErrorExit(errCode);
		return (RETURN_ERROR);
	}

	return (RETURN_CONTINUE);
}

__DEF_Template_CommandProcessor
int __DEF_CommandProcessor::onProcessPre(__ParamPack &pack)
{
	return ERROR_NO_ERROR;
}



__DEF_Template_CommandProcessor
void __DEF_CommandProcessor::onErrorExit(int errCode,const __CommandOption *opt)
{
	if(opt!=nullptr)
	{
		opt->dump();
		HostEnv::printf_simple(":");
	}
	switch(errCode)
	{
	case ERROR_UNKNOW_OPTION:
		HostEnv::printf_simple(
#if defined(CODE64)
				"未知选项\n"
#else
				"option unknown \n"
#endif

		);
		break;
	case ERROR_ARG_NOT_ENOUGH:
		HostEnv::printf_simple(
#if defined(CODE64)
				"参数不足\n"
#else
				"argument not enough\n"
#endif

		);
		break;
	case ERROR_PROCESS_NOT_A_NUMBER:
		HostEnv::printf_simple(
#if defined(CODE64)
				"需要一个数字\n"
#else
				"needs a number \n"
#endif
		);
		break;
	case ERROR_PROCESS_POST:
		if(opt!=nullptr)
		HostEnv::printf_simple(
#if defined(CODE64)
				"参数处理错误\n"
#else
				"argument processed error\n"
#endif
		);
		break;
	case ERROR_PROCESS_PRE:
		HostEnv::printf_simple(
#if defined(CODE64)
				"参数预处理错误\n"
#else
				"argument pre-processed error\n"
#endif
		);
		break;

	case ERROR_NO_ERROR:
	case ERROR_NORMAL_EXIT:
	default:
		break;
	}
	HostEnv::flushOutputs();
}
#undef __DEF_Template_CommandProcessor
#undef __DEF_CommandProcessor
