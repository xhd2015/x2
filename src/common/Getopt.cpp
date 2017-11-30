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
	template class CommandOption<std::string>;
	template class CommandOptions<std::string, partial_vec>;
#endif

// TODO 说明下面设计目的
// 用于。。。
#if defined(IDE_MODE)
#define _String _String
#define _Vector _Vector
#else
#define _String __String
#define _Vector __Vector
#endif


template<class _String>
CommandOption<_String >::CommandOption(
		const __String& shortOpt,
		const __String& longOpt,
		bool needsParam,
		const __String &helpMsg
		):
		shortOpt(shortOpt),longOpt(longOpt),needsParam(needsParam),
		helpMsg(helpMsg)
{

}





template <class _String>
bool CommandOption<_String>::equals(const __String& opt)const
{
	return shortOpt.compare(opt)==0 ||
			longOpt.compare(opt)==0;
}


//========= class CommandOptions

template <class _String,template <class>class _Vector>
CommandOptions<_String,_Vector>::CommandOptions(const std::initializer_list<__CommandOption> &il):
_Vector<CommandOption<_String>>(il)
{

}

template <class _String,template <class>class _Vector>
typename CommandOptions<_String,_Vector>::__PosIterator
		CommandOptions<_String,_Vector>::find(const __String &option)const
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
template <class _String,template <class>class _Vector>
//typename CommandOptions<_String,_Vector>::
__String CommandOptions<_String,_Vector>::makeHelpMessage(const __String &heading,
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
		s+="\t\t"+option.shortOpt+",\t"+option.longOpt+"\t\t"+option.helpMsg+"\n";
	}
	s+=foot+"\n";

	return std::move(s);
}
