#include "implement.h"

template class Pack<int>;
template class Pack<unsigned char>;

template<class T>
Pack<T>::Pack()
{

}
template<class T>
Pack<T>::~Pack()
{

}

template<class T>
T Pack<T>::get()
{
	T a;
	*(int*)(&a)=0;
	return a;
}

