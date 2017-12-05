/*
 * Locator_macros.h
 *
 *  Created on: 2017年3月24日
 *      Author: 13774
 */

#ifndef INCLUDE_MACROS_LOCATOR_MACROS_H_
#define INCLUDE_MACROS_LOCATOR_MACROS_H_

#include <Locator.h>
//============Function Macros
//=====class SourceLocator
template <class _Source,int _HowStart,int _HowLength,int _HowAllocable>
const _Source* SourceLocator<_Source,_HowStart,_HowLength,_HowAllocable>::getComparator()const
{
	return p;
}




#endif /* INCLUDE_MACROS_LOCATOR_MACROS_H_ */
