
#ifndef MallocToSimple_h__
#define MallocToSimple_h__

#include <List.h>
#include <EnvInterface.h>


/**
*   T does not have to be SimpleMemoryNode
*  能够将任何环境提供的malloc函数转换成simple new
*
*/
template<class T>
class MallocToSimple
{
public:
	MallocToSimple()=default;
	~MallocToSimple()=default;
	T *getNew();
	template <class ... Args>
	T *constructNew(Args && ... args);
	void withdraw(T *t);
};



#endif //MallocToSimple_h__
