
#ifndef MallocToSimple_h__
#define MallocToSimple_h__

#include <List.h>
#include <EnvInterface.h>


/**
*   T does not have to be SimpleMemoryNode
*  能够将任何环境提供的malloc函数转换成simple new
*
*/
template<class T,class __EnvInterface>
class MallocToSimple
{
public:
	typedef
#if defined(IDE_MODE)
			EnvInterface
#else
			__EnvInterface
#endif
		_EnvInterface;
public:
	MallocToSimple(_EnvInterface *env);
	~MallocToSimple();
	T *getNew();
	void withdraw(T *t);

protected:
	_EnvInterface *env;

};



#endif //MallocToSimple_h__
