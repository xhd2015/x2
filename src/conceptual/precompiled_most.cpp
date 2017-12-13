/*
 * precompiled_most.h
 *
 *  Created on: Dec 4, 2017
 *      Author: 13774
 */

#ifndef INCLUDE_CONCEPTUAL_PRECOMPILED_MOST_H_D_
#define INCLUDE_CONCEPTUAL_PRECOMPILED_MOST_H_D_


#if defined(CODE64)
//标准库
#include <iostream>

//==from def.h
#include <def.h>

//==from loki
#include <conceptual/loki/Int2Type.h>

//==from 64/
#include <64/MallocToSimple.h>
//#include <64/CMDUtil.h>

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
#include <EnvInterfaceX2Impl.h>  // 经常改变
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

//===========cpp====================
//==from 64/
//#include "../64/CMDUtil_main.cpp"
//#include "../64/CMDUtil_mkfs.x2fs.cpp"
//#include "../64/CMDUtil_rwfile.cpp"
//#include "../64/CMDUtil_test.cpp"
#include "../src/64/MallocToSimple.cpp"

//==from common/
#include "../src/common/Getopt.cpp"

//==from conceptual
#include "../src/conceptual/Serialize.cpp"

//==from $ROOT
#include "../src/AssociatedMemoryManager.cpp"
//#include "../src/Cache.cpp"
#include "../src/Descriptor.cpp"
#include "../src/EnvInterface64Impl.cpp"
#include "../src/File.cpp"
//#include "../src/File_FileOperation.cpp" //不应当include，是一个子文件
//#include "../src/idleProcess.cpp"
//#include "../src/interrupts.cpp"
#include "../src/IOProgramer.cpp"
#include "../src/Kernel.cpp"
#include "../src/KernelMemoryConfig.cpp"
#include "../src/libx2.cpp"
#include "../src/List.cpp"
#include "../src/Locator.cpp"
//#include "../src/MBRmain.cpp"
#include "../src/MemoryManager.cpp"
#include "../src/PMLoader.cpp"
#include "../src/Process.cpp"
//#include "../src/protected_main.cpp"
#include "../src/SecondaryLoader.cpp"
//#include "../src/test.cpp"
#include "../src/TSS.cpp"
#include "../src/UserProcess.cpp"
//#include "../src/VBRmain.cpp"    //无需引入
#include "../src/VirtualMemory.cpp"


#elif defined(CODE32)

#elif defined(CODE32USER)

#elif defined(CODE16)


#else // do nothing
#warning "You do not defined any code compile patter."
#endif





#endif /* INCLUDE_CONCEPTUAL_PRECOMPILED_MOST_H_D_ */
