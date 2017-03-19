
#ifndef MallocToSimple_h__
#define MallocToSimple_h__
#include <List.h>


/**
*T does not have to be SimpleMemoryNode
*
*/
template<class T>
class MallocToSimple
{
public:
	MallocToSimple();
	~MallocToSimple();
	T *getNew();
	void withdraw(T *t);

protected:


};



#endif //MallocToSimple_h__
