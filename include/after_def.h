#ifndef AFTER_DEF_H_
#define AFTER_DEF_H_

//====为了解决环形依赖而设置的typedef区域
#if defined(CODE32)||defined(CODE64)
#include <AssociatedMemoryManager.h>
#include <VirtualMemory.h>
	typedef AssociatedMemoryManager<SegmentDescriptor,1> SegManager;
	typedef AssociatedMemoryManager<PTE,1>	PTEManager;
#endif

#endif //AFTER_DEF_H_
