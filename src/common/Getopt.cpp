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
	template class CommandOption<StdEnv64Impl>;
	template class CommandOptions<StdEnv64Impl>;
	template class CommandProcessor<StdEnv64Impl,ParamRwfile>;
	template class CommandProcessor<StdEnv64Impl,ParamMkfs>;
#endif



// 几个常见选项
template<class __StdEnvInterface>
const CommandOption<__StdEnvInterface> CommandOption<__StdEnvInterface>::helpOption={"-h","--help",false,"显示此帮助信息"};
template<class __StdEnvInterface>
const CommandOption<__StdEnvInterface> CommandOption<__StdEnvInterface>::versionOption={"-v","--version",false,"显示版本信息"};
template<class __StdEnvInterface>
const CommandOption<__StdEnvInterface> CommandOption<__StdEnvInterface>::stopOption=
		{"--","--",false,"停止"};



template<class __StdEnvInterface>
CommandOption<__StdEnvInterface >::CommandOption(
		const __String& shortOpt,
		const __String& longOpt,
		bool needsParam,
		const __String &helpMsg
		):
		shortOpt(shortOpt),longOpt(longOpt),needsParam(needsParam),
		helpMsg(helpMsg)
{

}





template <class __StdEnvInterface>
bool CommandOption<__StdEnvInterface>::equals(const __String& opt)const
{
	return shortOpt.compare(opt)==0 ||
			longOpt.compare(opt)==0;
}

template <class __StdEnvInterface>
bool CommandOption<__StdEnvInterface>::equals(const __CommandOption& opt)const
{
	return (this->shortOpt.compare(opt.shortOpt)==0 && this->longOpt.compare(opt.longOpt)==0);
}
template <class __StdEnvInterface>
void CommandOption<__StdEnvInterface>::dump(__StdEnvInterface &env)const
{

	env.printf_simple(shortOpt.c_str());
	env.printf_simple("/");
	env.printf_simple(longOpt.c_str());
}


//========= class CommandOptions

template <class __StdEnvInterface>
CommandOptions<__StdEnvInterface>::CommandOptions(const std::initializer_list<__CommandOption> &il):
Super(il)
{

}
template <class __StdEnvInterface>
typename CommandOptions<__StdEnvInterface>::__PosIterator
CommandOptions<__StdEnvInterface>::find(const __String &option)const
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
template <class __StdEnvInterface>
typename CommandOptions<__StdEnvInterface>::__String
CommandOptions<__StdEnvInterface>::makeHelpMessage(const __String &heading,
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


//========= class CommandProcessor

template <class __StdEnvInterface,class __ParamPack>
CommandProcessor<__StdEnvInterface,__ParamPack>::CommandProcessor(__StdEnvInterface &env):
env(env)
{

}
template <class __StdEnvInterface,class __ParamPack>
int CommandProcessor<__StdEnvInterface,__ParamPack>::processOptions(
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

template <class __StdEnvInterface,class __ParamPack>
int CommandProcessor<__StdEnvInterface,__ParamPack>::onProcessPre(__ParamPack &pack)
{
	return ERROR_NO_ERROR;
}



template <class __StdEnvInterface,class __ParamPack>
void CommandProcessor<__StdEnvInterface,__ParamPack>::onErrorExit(int errCode,const __CommandOption *opt)
{
	if(opt!=NULL)
	{
		opt->dump(env);
		env.printf_simple(":");
	}
	switch(errCode)
	{
	case ERROR_UNKNOW_OPTION:
		env.printf_simple(
#if defined(CODE64)
				"未知选项\n"
#else
				"option unknown \n"
#endif

		);
		break;
	case ERROR_ARG_NOT_ENOUGH:
		env.printf_simple(
#if defined(CODE64)
				"参数不足\n"
#else
				"argument not enough\n"
#endif

		);
		break;
	case ERROR_PROCESS_NOT_A_NUMBER:
		env.printf_simple(
#if defined(CODE64)
				"需要一个数字\n"
#else
				"needs a number \n"
#endif
		);
		break;
	case ERROR_PROCESS_POST:
		if(opt!=NULL)
		env.printf_simple(
#if defined(CODE64)
				"参数处理错误\n"
#else
				"argument processed error\n"
#endif
		);
		break;
	case ERROR_PROCESS_PRE:
		env.printf_simple(
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
	env.flushOutputs();
}
