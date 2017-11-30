/*
 * Getopt.h
 *
 *  Created on: Nov 30, 2017
 *      Author: 13774
 */

#ifndef INCLUDE_COMMON_GETOPT_H_
#define INCLUDE_COMMON_GETOPT_H_


/**
 * 兼容unix getopt，实现一个更严格的子集：不允许
 * 接口描述：
 *   addShort(char,bool)
 *   addLong(string,bool)
 *
 *   // 对参数进行整理，形成二元组
 *   bool parseArgs(begin,end);
 *
 *   getopt解决的主要问题是：识别用户输入的意图，将串字符串看成是参数，还是选项
 *
 *
 */

#include <common/NoArch.h>


#if defined(CODE64)
#include <vector>
template <class T>
	using partial_vec=typename std::vector<T>;
#endif

#if defined(IDE_MODE)
#define _String _String
#define _Vector _Vector
#else
#define _String __String
#define _Vector __Vector
#endif


template <class _String>
struct CommandOption{
public:
#if defined(IDE_MODE)
	using __String = std::string;
#endif

public:
	CommandOption(const __String &shortOpt,const __String &longOpt,
			bool needsParam=false,const __String &helpMsg=__String());
	bool equals(const __String& opt)const;

public:
	__String shortOpt;
	__String longOpt;
	bool	  needsParam;
	__String helpMsg;
};

template <class _String,template <class>class _Vector>
class CommandOptions:public _Vector<CommandOption<_String>>
{
public:
#if defined(IDE_MODE)
	using __String = typename std::string;
	template <class T>
		using __Vector =typename  std::vector<T>;
#endif

	using __CommandOption = CommandOption<__String>;
	using __CommandOptions = CommandOptions<__String,__Vector>;
	using __PosIterator = typename __Vector<__CommandOption>::const_iterator;

public:
	// 避免使用模板，从而简化重构过程
	CommandOptions(const std::initializer_list<__CommandOption> &il);
	CommandOptions(const __CommandOptions & rhs)=delete;
	__CommandOptions& operator=(const __CommandOptions & rhs)=delete;

	/**
	 * 无论是长选项，还是短选项，返回它的下标
	 */
	__PosIterator	find(const __String &option)const;

	/**
	 * 帮助信息
	 * 格式如下：
	 *
	 * 	$heading
	 * 	用法：
	 * 		$usage
	 * 	选项：
	 * 		...
	 * 	$foot
	 */
	__String	makeHelpMessage(const __String &heading,
								const __String &usage,
								const __String &foot=__String()
						)const;


private:

};

#undef _String
#undef _Vector



#endif /* INCLUDE_COMMON_GETOPT_H_ */
