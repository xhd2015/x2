/*
 * all.h
 *
 *  Created on: Dec 2, 2017
 *      Author: 13774
 */

#ifndef INCLUDE_CONCEPTUAL_ALL_H_
#define INCLUDE_CONCEPTUAL_ALL_H_

#include <conceptual/precompiled_most.h>

#if defined(CODE64)

//==from 64/
#include <64/CMDUtil.h>

//==from conceptual
#include <conceptual/Serialize.h>

//==from $root
#include <EnvInterface64Impl.h>
#include <EnvInterfaceX2Impl.h>  // 经常改变


//==lastly,from macros
#include <macros/all.h> //this macros can also be precompiled into CODE64

#elif defined(CODE32)

#elif defined(CODE32USER)

#elif defined(CODE16)


#else // do nothing
#warning "You do not defined any code compile patter."
#endif


#endif /* INCLUDE_CONCEPTUAL_ALL_H_ */
