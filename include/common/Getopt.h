/*
 * Getopt.h
 *
 *  Created on: Nov 30, 2017
 *      Author: 13774
 */

#ifndef INCLUDE_COMMON_GETOPT_H_
#define INCLUDE_COMMON_GETOPT_H_


/**
 * 兼容unix getopt，实现一个更严格的子集：不允许--long=XX, -oXX, 选项和参数必须分离
 *
 *   getopt解决的主要问题是：识别用户输入的意图，将串字符串看成是参数，还是选项
 */

#include <common/NoArch.h>

struct CommandOption{
public:
	using This = CommandOption;
	using __String = HostEnv::String;
	using __CommandOption = This;

public://几个常见的option
	static const CommandOption helpOption; // -h --help
	static const CommandOption versionOption;// -v --version
	static const CommandOption stopOption;

public:
	CommandOption()=default;
	CommandOption(const __CommandOption &)=default;
	CommandOption& operator=(const __CommandOption&)=default;
	CommandOption(const __String &shortOpt,const __String &longOpt,
			bool needsParam=false,const __String &helpMsg=__String());
	bool equals(const __String& opt)const;
	bool equals(const __CommandOption& opt)const;
	void dump()const;

public:
	__String shortOpt{};
	__String longOpt{};
	bool	  needsParam=false;
	__String helpMsg{};
};

class CommandOptions:public
	HostEnv::Vector<CommandOption>
{
public:
	using This = CommandOptions;
	using Super =HostEnv::Vector<CommandOption>;
	using __String = HostEnv::String;
	template <class T>
		using __Vector =HostEnv::Vector<T>;


	using __CommandOption = CommandOption;
	using __CommandOptions = This;
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
/**
 * @param _String std::string的兼容类型
 * @param _Vector std::vector的兼容类型
 * @param __ParamPack 一个处理参数包，结构自定义
 */
template <class __ParamPack>
class CommandProcessor{
public:
	using This = CommandProcessor<__ParamPack>;
	using __CommandProcessor = This;
	using __String =HostEnv::String;
	template <class T>
	using __Vector = HostEnv::Vector<T>;

	using __CommandOptions=CommandOptions;
	using __CommandOption =typename  __CommandOptions::__CommandOption;
	using __Vector_String = __Vector<__String>;
	using __VS_cit = typename __Vector_String::const_iterator;
	using __OptPosIterator = typename __CommandOptions::__PosIterator;

	enum{
		ERROR_NO_ERROR, //没有错误
		ERROR_NORMAL_EXIT,//提前结束参数处理
		ERROR_ARG_NOT_ENOUGH,
		ERROR_PROCESS_PRE,
		ERROR_PROCESS_NOT_A_NUMBER,
		ERROR_UNKNOW_OPTION,
		ERROR_PROCESS_POST,
		ERROR_OTHER
	};
	enum{
		RETURN_DONE,
		RETURN_CONTINUE,
		RETURN_ERROR
	};

public: // 虚函数还是？
	CommandProcessor();
	CommandProcessor(__CommandProcessor &)=delete;

	/**
	 * @return 参数处理出错，-1; 已经处理完，无需下一步,0; 参数处理完毕，请进行下一步处理,1;
	 */
	int processOptions(const __CommandOptions &opt,__VS_cit beg,__VS_cit end, __ParamPack &pack);



	virtual ~CommandProcessor()=default;

	/**
	 * 用于设定默认值,通常可以省略
	 */
	virtual int onProcessPre(__ParamPack &pack);
	/**
	 * 处理选项
	 */
	virtual int onProcessArgOpt(__ParamPack &pack,__OptPosIterator itopt,__VS_cit itarg)=0;
	/**
	 * 处理目标参数
	 */
	virtual int onProcessArgTarget(__ParamPack &pack,__VS_cit itarg)=0;
	/**
	 * 用于确定某些值
	 */
	virtual int onProcessPost(__ParamPack &pack)=0;

	/**
	 * 默认情况下显示帮助信息并退出
	 */
	virtual int onProcessHelp(__ParamPack &pack)=0;
	/**
	 * 默认情况下显示版本信息并退出
	 */
	virtual int onProcessVersion(__ParamPack &pack)=0;


	/**
	 * @param errCode  退出码
	 * @param opt		上下文选项，可以省略
	 */
	virtual void onErrorExit(int errCode,const __CommandOption *opt=nullptr);


};

#undef _String
#undef _Vector



#endif /* INCLUDE_COMMON_GETOPT_H_ */
