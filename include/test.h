
#ifndef test_h__
#define test_h__
#include <libx2.h>
#include <List.h>
#include <Memory.h>

class Test{
public:
    Test();
    ~Test();
    
    
    
    void testQueue();
    void testList();
    void testMemory();
    void run();

    static void dumpMemoryData(const MemoryDescriptor & data);
    static void dumpMemoryData(const int& data);
    
    static void dumpSMM( SimpleMemoryManager<TreeNode<MemoryDescriptor> > *smm);
	static void dumpMM( MemoryManager<SimpleMemoryManager> &mm);

protected:
    Printer dbg;
    char buf[10];

    
};


#endif
