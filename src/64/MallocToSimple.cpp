
#include <64/MallocToSimple.h>
#include <cstdlib>
#include <cstddef>
//============template instantiate
#if defined(CODE64)
#include <cstdio>
#include <List.h>
#include <MemoryManager.h>
#include <EnvInterface64Impl.h>
//===代码遗产，古时代的手动编写实例化
//	template class MallocToSimple<TreeNode<MemoryDescriptor<size_t>,sizeof(size_t)>,EnvInterface64Impl>;
//	template class MallocToSimple<ListNode<LinearSourceDescriptor<size_t,sizeof(size_t)> ,sizeof(size_t)>,EnvInterface64Impl>;
//	template class MallocToSimple<ListNode<LinearSourceDescriptor<size_t,sizeof(size_t)> ,sizeof(size_t)>, StdEnv64Impl>;
//	template class MallocToSimple<TreeNode<MemoryDescriptor<size_t> ,sizeof(size_t)>, StdEnv64Impl>;
#endif

//============class functions definition
template<class T,class __EnvInterface>
MallocToSimple<T,__EnvInterface>::MallocToSimple(_EnvInterface &env):env(env)
{

}
template<class T,class __EnvInterface>
MallocToSimple<T,__EnvInterface>::~MallocToSimple()
{

}

template<class T,class __EnvInterface>
T * MallocToSimple<T,__EnvInterface>::getNew()
{
//	printf("in getNew of MallocToSimple\n");
//	printf("sizeof(T)=%d,sizeof(mynode)=%d\n",sizeof(T),sizeof(TreeNode<MemoryDescriptor>));
	return (T*)env.malloc(sizeof(T));
//	return (T*) (new char[sizeof(T)]);
//	TreeNode<MemoryDescriptor> *p=(TreeNode<MemoryDescriptor>*)malloc(sizeof(T));
//	new (p) TreeNode<MemoryDescriptor>(MemoryDescriptor(0,0));
//	p->setSon(NULL);
//	printf("go down end\n");
}


template<class T,class __EnvInterface>
void  MallocToSimple<T,__EnvInterface>::withdraw(T *t)
{
	env.free((u8_t*)t);
}
