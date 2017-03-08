
#include "MallocToSimple.h"
#include <cstdlib>
#include <cstddef>

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
	return (T*)malloc(sizeof(T));
}


template<class T>
void MallocToSimple<T>::withdraw(T *t)
{
	free(t);
}
