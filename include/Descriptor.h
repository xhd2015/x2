#ifndef Descriptor_h__
#define Descriptor_h__
#include <def.h>
/**
*提供了对intel x86的8字节描述符的结构化描述
*
*/
class Descriptor{
public:
    Descriptor();
    ~Descriptor();
protected:

private:

};
//多于一个字节的用数组类型，其他用直接量
//10个属性 = 8直接属性 + 2指针属性
/**
 * Limit指的是
 */
#pragma pack(push,1)
class SegmentDescriptor:public Descriptor{
public:
//conforming can let low privilage keeps
	enum{
						TYPE_U_STACK = 0b0010,
		                TYPE_U_EXPANEDDOWN=0b0110,
		                TYPE_U_DATA = 0b0010,
		                TYPE_U_CODE_NONCONFORMING = 0b1010,
		                TYPE_U_CODE_CONFORMING = 0b1110,
		                TYPE_S_UNUSED_1=0b0000,
						TYPE_S_LDT 		=0b0010,
		                TYPE_S_UNUSED_2=0b1000,
		                TYPE_S_UNUSED_3=0b1010,
		                TYPE_S_UNUSED_4=0b1101,
		                TYPE_S_TSS_16_AVL=0b0001,
		                TYPE_S_TSS_16_BUSY=0b0011,
		                TYPE_S_TSS_32_AVL=0b1001,
		                TYPE_S_TSS_32_BUSY=0b1011,
		                TYPE_S_CALLGATE_16=0b0100,
		                TYPE_S_CALLGATE_32=0b1100,
		                TYPE_S_TASKGATE=0b0101,
		                TYPE_S_INTGATE_16=0b0110,
		                TYPE_S_TRAPGATE_16=0b0111,
		                TYPE_S_INTGATE_32=0b1110,
		                TYPE_S_TRAPGATE_32=0b1111,
						DPL_0=0x0,
		                DPL_1=0x1,
		                DPL_2=0x2,
		                DPL_3=0x3,
						S_SYSTEM=0x0,
						S_USER=0x1,
						L_LONG_SEGMENT=0x1, //L: 64bit  only for IA-32e
						L_LEGACY_SEGMENT=0x0 ,//L: 32bit
						P_PRESENT=0x1,
						P_NON_PRESENT=0x0,
						G_4KB=0x1,
						G_1B = 0x0,
						G_4KB_SCALE=4*1024,
						D_OPSIZE32=0x1,
						D_OPSIZE16=0x0,
						B_UPPER_BOUND32=0x1,
						B_UPPER_BOUND16=0x0,
						RESERVED=0,

	};
//    const static int TYPE_U_EXPANEDDOWN,TYPE_U_STACK,TYPE_U_DATA,TYPE_U_CODE_NONCONFORMING,TYPE_U_CODE_CONFORMING;
//    const static int TYPE_S_UNUSED_1,TYPE_S_UNUSED_2,TYPE_S_UNUSED_3,TYPE_S_UNUSED_4,TYPE_S_TSS_16_AVL,TYPE_S_TSS_16_BUSY,TYPE_S_TSS_32_AVL,TYPE_S_TSS_32_BUSY,TYPE_S_CALLGATE_16,TYPE_S_CALLGATE_32,TYPE_S_TASKGATE,TYPE_S_INTGATE_16,TYPE_S_TRAPGATE_16,TYPE_S_INTGATE_32,TYPE_S_TRAPGATE_32;
//    const static int DPL_0,DPL_1,DPL_2,DPL_3;
protected:
    short		limitLow_16:16;
    int			baseAddrLow_24:24;

public:
    char type:4;
    char S:1;
    char DPL:2;
    char P:1;

//    union	{char tpye:4;char CCRA:4;char DEWA:4;};
//    union	{char system:1;char S:1;};
//    int DPL:2;
//    union	{int present:1;int P:1;};

protected:
    char	limitHigh_4:4;
public:
    char AVL:1;
    char L:1;
    char D:1;
    char G:1;
//    union	{char available:1;char	AVL:1;};
//    union	{char is64Segment:1;char longSegment:1;char L:1;};
//    union	{char defaultOpSize:1;char D:1;char littleUpperBound:1;char B:1;};
//    union	{char Granularity:1; char G:1;  };
protected:
	char	baseAddrHigh_8:8;

public:
    AS_MACRO void setBaseAddr(int baseAddr);
    AS_MACRO int	getBaseAddr()const;
    AS_MACRO int		getLimit()const;
    AS_MACRO void	setLimit(int limit);


    SegmentDescriptor(char* baseaddr=0,int limit=0,char g=G_1B,char type=TYPE_U_DATA,
    		char dpl=DPL_0,char s=S_USER,char b=B_UPPER_BOUND32,char p=P_PRESENT);
    ~SegmentDescriptor();

    /**
    *相同返回1，不同返回0
    */
    bool equals(SegmentDescriptor &sd2);
    void init(char* baseaddr=0,int limit=0,char type=TYPE_U_DATA,char dpl=DPL_0,char s=1,char b=1,char p=1,char g=0,char l=0,char avl=0);
#if defined(CODE32)||defined(CODE16)
    void writeToMemory(int seg,char* addr);//0x10000 means use current seg
    static void fromMemory(SegmentDescriptor *sd,int seg,char* addr);
#endif
    
};
#pragma pack(pop)

//====================仅32位===============
#if defined(CODE32)||defined(CODE64)
#pragma pack(push,1)
/**
*IDT中的描述符
*采用新的方式，必须用选项 -fpack-struct=1什么来支持
*兼容三种类型:
* 主size：4byte
*/
class SelectorDescriptor:public Descriptor{
public:
	enum{TYPE_INT=0x0600,
		TYPE_TASK=0x0500,
		TYPE_TRAP=0x0700,
		SIZE_16=0,
		SIZE_32=1
	};
public:

    union{char I0[2];char __Offset_low[2]; char __reservedI0[2]; };
    union{char I1[2]; char __SegmentSelectorInGDTorLDT[2];/*int 和 trap*/  char __TSSSelector[2];/*Task Gate*/ char __Selector[2];  char __Sel[2];  };
    union{char I2[2];};
    union{char I3[2];char __reservedI3[2];char __Offset_high[2];};
    SelectorDescriptor();
    ~SelectorDescriptor();
    void init(int sel,int offset,int type,int dpl=0,int p=1,int segSize=1);
    void DPL(int dpl);
    void P(int p);
    void D(int d);
    void Offset(int offset);
    void Selector(int selector);
    void Type(int index);//0 task gate,1 int gate,2 trap gate
#if defined(CODE32)||defined(CODE16)
    void writeToMemory(int seg,int off);
    static void fromMemory(SelectorDescriptor &self,int seg,int off);
#elif defined(CODE64)
    void writeToMemory(char *base);
    static void fromMemory(SelectorDescriptor &self,const char *base);
#endif

    
 private:
        
    char __P,__DPL,__D;
        //D:0 16-bit  :1 32-bit
    
};
#pragma pack(pop)
#endif //==CODE32 && CODE64==



#endif//Descriptor_h__
