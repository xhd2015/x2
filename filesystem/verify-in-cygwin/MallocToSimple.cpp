
#include "MallocToSimple.h"
#include <cmalloc>

template<class T>
MallocToSimple<T>::MallocToSimple():SimpleMemoryManager<T>()
{

}

template<class T>
MallocToSimple<T>::~MallocToSimple()
{

}

template<class T>
T *MallocToSimple<T>::getNew()
{
	return (T*)malloc(sizeof(T));
}


template<class T>
void MallocToSimple<T>::withdraw(T *t)
{
	free(t);
}