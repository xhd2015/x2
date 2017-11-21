#ifndef __TSS__
#define __TSS__
#include <def.h>

class Printer;

#pragma pack(push,1)
class TSS{//size = 104 + others,所有类型均用指针 // This is tested,standard size is 104
public:
        union{ 	char I0[4];	int  PreviousTaskLink:16;int  PTL:16;     };
        union{  char I1[4];int ESP0:32;};
        union{  char I2[4];int SS0:16;};
        union{  char I3[4];int ESP1:32;};
        union{  char I4[4];int SS1:16;};
        union{  char I5[4];int ESP2:32;};
        union{  char I6[4];int SS2:16;};
        union{  char I7[4];int CR3:32;int PDBR:32;};
        union{  char I8[4];int EIP:32;};
        union{  char I9[4];int EFLAGS:32;};
        union{  char I10[4];int EAX:32;};
        union{  char I11[4];int ECX:32;};
        union{  char I12[4];int EDX:32;};
        union{  char I13[4];int EBX:32;};
        union{  char I14[4];int ESP:32;};
        union{  char I15[4];int EBP:32;};
        union{  char I16[4];int ESI:32;};
        union{  char I17[4];int EDI:32;};
        union{  char I18[4];int ES:16;};
        union{  char I19[4];int CS:16;};
        union{  char I20[4];int SS:16;};
        union{  char I21[4];int DS:16;};
        union{  char I22[4];int FS:16;};
        union{  char I23[4];int GS:16;};
        union{  char I24[4];int LDTSELECTOR:16;int LDTSEL:16;int LDT:16;};
        union{  char I25[2];char TRAP:1;};
        union{  char __I25[2];int IOBASE:16;};


    
public:
    TSS();
    ~TSS();
    
    void writeToMemory(int seg,int off);
    DEPRECATED void ensureReservedZero();
    static void fromMemory(TSS &self,int seg,int off);
    
    void dumpInfo(Printer *p);//=Kernel::printer

protected:
    
private:

};
#pragma pack(pop)
#endif
