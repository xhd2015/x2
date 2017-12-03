/*
 * all.h
 *
 *  Created on: Dec 2, 2017
 *      Author: 13774
 */

#ifndef INCLUDE_CONCEPTUAL_ALL_H_
#define INCLUDE_CONCEPTUAL_ALL_H_


#if defined(CODE64)

//==from def.h
#include <def.h>

//==from loki
#include <loki/Int2Type.h>

//==from 64/
#include <64/CMDUtil.h>
#include <64/MallocToSimple.h>

//==from common
#include <common/Getopt.h>
#include <common/NoArch.h>

//==from conceptual
#include <conceptual/Serialize.h>

//==from $root
#include <AssociatedMemoryManager.h>
#include <Cache.h>
#include <Descriptor.h>
#include <EnvInterface.h>
#include <EnvInterface64Impl.h>
#include <EnvInterfaceX2Impl.h>
#include <File.h>
#include <Filesystem.h>
#include <Functools.h>
#include <interrupts.h>
#include <IOProgramer.h>
#include <Kernel.h>
#include <KernelMemoryConfig.h>
#include <libx2.h>
#include <List.h>
#include <Locator.h>
#include <MemoryManager.h>
#include <PMLoader.h>
#include <test.h>
#include <TSS.h>
#include <VirtualMemory.h>


//==lastly,from macros
#include <macros/all.h>

#elif defined(CODE32)

#elif defined(CODE32USER)

#elif defined(CODE16)


#else // do nothing
#warning "You do not defined any code compile patter."
#endif


#endif /* INCLUDE_CONCEPTUAL_ALL_H_ */
