
#include "MallocToSimple.h"
#include <cstdlib>
#include <cstddef>
//============template instantiate
#if defined(CODE64)
#include <cstdio>
#include <List.h>
#include <Memory.h>
	template class MallocToSimple<TreeNode<MemoryDescriptor> >;
	template class MallocToSimple<ListNode<LinearSourceDescriptor> >;
#endif

//============class functions definition
template<class T>
MallocToSimple<T>::MallocToSimple()
{

}

template<class T>
MallocToSimple<T>::~MallocToSimple()
{

}

template<class T>
T *MallocToSimple<T>::getNew()
{
	//printf("in getNew of MallocToSimple\n");
//	printf("sizeof(T)=%d,sizeof(mynode)=%d\n",sizeof(T),sizeof(TreeNode<MemoryDescriptor>));
	return (T*)malloc(sizeof(T));
//	TreeNode<MemoryDescriptor> *p=(TreeNode<MemoryDescriptor>*)malloc(sizeof(T));
//	new (p) TreeNode<MemoryDescriptor>(MemoryDescriptor(0,0));
//	p->setSon(NULL);
//	printf("go down end\n");
}


template<class T>
void MallocToSimple<T>::withdraw(T *t)
{
	free(t);
}
