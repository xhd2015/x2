
#ifndef test_h__
#define test_h__
#include <libx2.h>
#include <List.h>
#include <MemoryManager.h>

class Test{
public:
    Test();
    ~Test();
    
//    void testQueue();
//    void testList();
//    void testMemory();
    void testIO_HDD();
    void run();
    void testVM();

//    static void dumpMemoryData(const MemoryDescriptor & data);
//    static void dumpMemoryData(const int& data);
//
//    static void dumpSMM( SimpleMemoryManager<TreeNode<MemoryDescriptor> > *smm);
//	static void dumpMM( MemoryManager<SimpleMemoryManager> &mm);

protected:
#if defined(CODE32)
    Printer dbg;
#endif
    char buf[10];

    
};


#endif
