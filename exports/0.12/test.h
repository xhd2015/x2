
#ifndef test_h__
#define test_h__
#include "libx2.h"

class Test{
public:
    Test();
    ~Test();
    
    
    
    void testQueue();
    void testList();
    void run();
    
protected:
    Printer dbg;
    
    
};


#endif