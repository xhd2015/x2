
#include <conceptual/all.h>


#if defined(CODE64)

//====处理动态引入
#if defined(IDE_MODE)
#define CMDUTIL main.cpp //样例
#endif
#if !defined(CMDUTIL)
#error "Please define CMDUTIL!"
#endif
#define CONH(A) ../64/CMDUtil_##A

#define INC(A) STR(CONH(A))
#include INC(CMDUTIL)
//******===动态引入结束

//==from 64/
//#include "../64/CMDUtil_main.cpp"
//#include "../64/CMDUtil_mkfs.x2fs.cpp"
//#include "../64/CMDUtil_rwfile.cpp"
//#include "../64/CMDUtil_test.cpp"
#include "../64/MallocToSimple.cpp"

//==from common/
#include "../common/Getopt.cpp"

//==from $ROOT
#include "../AssociatedMemoryManager.cpp"
//#include "../Cache.cpp"
#include "../Descriptor.cpp"
#include "../EnvInterface64Impl.cpp"
#include "../File.cpp"
//#include "../File_FileOperation.cpp" //不应当include，是一个子文件
//#include "../idleProcess.cpp"
//#include "../interrupts.cpp"
#include "../IOProgramer.cpp"
#include "../Kernel.cpp"
#include "../KernelMemoryConfig.cpp"
#include "../libx2.cpp"
#include "../List.cpp"
#include "../Locator.cpp"
//#include "../MBRmain.cpp"
#include "../MemoryManager.cpp"
#include "../PMLoader.cpp"
#include "../Process.cpp"
//#include "../protected_main.cpp"
#include "../SecondaryLoader.cpp"
//#include "../test.cpp"
#include "../TSS.cpp"
#include "../UserProcess.cpp"
//#include "../VBRmain.cpp"    //无需引入
#include "../VirtualMemory.cpp"

#elif defined(CODE32)

#elif defined(CODE32USER)

#elif defined(CODE16)


#else // do nothing
#warning "You do not defined any code compile patter."
#endif
