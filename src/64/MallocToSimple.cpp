
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
#define __DEF_Template_MallocToSimple template<class T>
#define __DEF_MallocToSimple MallocToSimple<T>

__DEF_Template_MallocToSimple
T * __DEF_MallocToSimple::getNew()
{
//	printf("in getNew of MallocToSimple\n");
//	printf("sizeof(T)=%d,sizeof(mynode)=%d\n",sizeof(T),sizeof(TreeNode<MemoryDescriptor>));
	return static_cast<T*>(HostEnv::malloc(sizeof(T)));
//	return (T*) (new char[sizeof(T)]);
//	TreeNode<MemoryDescriptor> *p=(TreeNode<MemoryDescriptor>*)malloc(sizeof(T));
//	new (p) TreeNode<MemoryDescriptor>(MemoryDescriptor(0,0));
//	p->setSon(nullptr);
//	printf("go down end\n");
}


__DEF_Template_MallocToSimple
void  __DEF_MallocToSimple::withdraw(T *t)
{
	HostEnv::free(reinterpret_cast<u8_t*>(t));
}
#undef __DEF_Template_MallocToSimple
#undef __DEF_MallocToSimple
