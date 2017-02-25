#ifndef __interrupts_h__
#define __interrupts_h_

#include "def.h"

extern int *intAddresses;
extern int intLen;

extern "C" {
    void int0x0();
    void int0x1();
    void int0x2();
    void int0x3();
    void int0x4();
    void int0x5();
    void int0x6();
    void int0x7();
    void int0x8();
    void int0x9(); //---- 10
    
    void int0xa();
    void int0xb();
    void int0xc();
    void int0xd();
    void int0xe();
    void int0xf();
    void int0x10();
    void int0x11();
    void int0x12();
    void int0x13();//---- 20
    
    
    void int0x14();
    void int0x15();
    void int0x16();
    void int0x17();
    void int0x18();
    void int0x19();
    void int0x1a();
    void int0x1b();
    void int0x1c();
    void int0x1d();//---- 30
    
    void int0x1e();
    void int0x1f();//---- 32  ===== 0~31 used by intel
   // int int0x20;//超越堆栈框架的中断处理程序
    void int0x24();
    void int0x25();
    void intDefault();
}
extern int int0x20,int0x21;

class InterruptsManager{
public:
    typedef void (*GENERAL_FUNC)();
public:
    InterruptsManager();
    ~InterruptsManager();
    
    GENERAL_FUNC getIntAddr(unsigned int i);
    void setIntAddr(unsigned int i);
    
    static void callInt(unsigned int i);
    
protected:
    static GENERAL_FUNC intAddresses[];
    static unsigned int intLen;
    
    static GENERAL_FUNC defaultHandler;
    
};

#endif