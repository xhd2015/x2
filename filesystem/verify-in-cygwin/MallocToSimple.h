
#ifndef MallocToSimple_h__
#define MallocToSimple_h__
#include <List.h>


/**
*T does not have to be SimpleMemoryNode
*
*/
template<class T>
class MallocManager:public SimpleMemoryManager<T>
{
public:
	MallocManager();
	~MallocManager();
	virtual T *getNew();
	virtual void withdraw(T *t);

protected:


};



#endif 