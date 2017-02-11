#ifdef CODE16
    __asm__(".code16gcc \n\t");//此处开始为保护模式写代码
#elseif defined CODE32
    __asm__(".code32 \n\t");
#endif


#include "Descriptor.h"
#include "libx2.h"

//指针类型
#define __MXp(type,pointer,andNum,shiftNum,direction) ((*((type*)this->pointer) & (andNum) ) direction (shiftNum))
//直接量
#define __MXd(pointer,andNum,shiftNum,direction) ((this->pointer & (andNum) ) direction (shiftNum))
#define __MLd(pointer,andNum,shiftNum) __MXd(pointer,andNum,shiftNum,<<)
#define __MRd(pointer,andNum,shiftNum) __MXd(pointer,andNum,shiftNum,>>)
Descriptor::Descriptor()
{

}

Descriptor::~Descriptor()
{

}
//==========For SegmentDescriptor===========
const int       SegmentDescriptor::TYPE_U_STACK = 0b0110,
                SegmentDescriptor::TYPE_U_DATA = 0b0010,
                SegmentDescriptor::TYPE_U_CODE_NONCONFORMING = 0b1010,
                SegmentDescriptor::TYPE_U_CODE_CONFORMING = 0b1110;
const int       SegmentDescriptor::TYPE_S_UNUSED_1=0,
                SegmentDescriptor::TYPE_S_UNUSED_2=0b1000,
                SegmentDescriptor::TYPE_S_UNUSED_3=0b1010,
                SegmentDescriptor::TYPE_S_UNUSED_4=0b1101,
                SegmentDescriptor::TYPE_S_TSS_16_AVL=0b0001,
                SegmentDescriptor::TYPE_S_TSS_16_BUSY=0b0011,
                SegmentDescriptor::TYPE_S_TSS_32_AVL=0b1001,
                SegmentDescriptor::TYPE_S_TSS_32_BUSY=0b1011,
                SegmentDescriptor::TYPE_S_CALLGATE_16=0b0100,
                SegmentDescriptor::TYPE_S_CALLGATE_32=0b1100,
                SegmentDescriptor::TYPE_S_TASKGATE=0b0101,
                SegmentDescriptor::TYPE_S_INTGATE_16=0b0110,
                SegmentDescriptor::TYPE_S_TRAPGATE_16=0b0111,
                SegmentDescriptor::TYPE_S_INTGATE_32=0b1110,
                SegmentDescriptor::TYPE_S_TRAPGATE_32=0b1111;
const int       SegmentDescriptor::DPL_0=0x0,
                SegmentDescriptor::DPL_1=0x1,
                SegmentDescriptor::DPL_2=0x2,
                SegmentDescriptor::DPL_3=0x3;
SegmentDescriptor::~SegmentDescriptor()
{

}
SegmentDescriptor::SegmentDescriptor(char* baseaddr,int limit,char type,char dpl):AVL(0),G(0),B(1),P(1),S(1),L(0),DPL(dpl),Type(type)
{
    *(char**)this->BaseAddr = baseaddr;
    *(short*)this->Limit = limit & 0xffff;
    *((char*)this->Limit+2) = (limit & 0xf0000) >> 16;
}
int SegmentDescriptor::equals(SegmentDescriptor &sd2)
{
    if(
        (*(int*)this->BaseAddr == *(int*)sd2.BaseAddr) &&
        ((*(int*)this->Limit & 0xfffff )== (*(short*)sd2.Limit & 0xfffff)) &&
        (this->P == sd2.P) &&(this->L == sd2.L) && (this->B == sd2.B) &&  (this->S == sd2.S) &&
        (this->Type == sd2.Type) && (this->G==sd2.G) && (this->AVL==sd2.AVL) && (this->DPL==sd2.DPL)
        )
        {
            return 1;
        }
        return 0;
}

void SegmentDescriptor::writeToMemory(int seg,char* addr)
{
    char *dst;
    dst = addr;
    //*(short*)dst = __MXp(short,Limit,0xffff,0,>>);
    Util::setw(seg,dst,__MXp(short,Limit,0xffff,0,>>));
    dst+=2;
    
    //*(short*)dst = __MXp(int,BaseAddr,0xffff,0,>>);
    Util::setw(seg,dst,__MXp(int,BaseAddr,0xffff,0,>>));
    dst+=2;
    
    //*dst = __MXp(int,BaseAddr,0xff0000,16,>>);
    Util::setb(seg,dst,__MXp(int,BaseAddr,0xff0000,16,>>));
    dst++;
    
    //*dst = __MLd(P,0x1,7) | __MLd(DPL,0x3,5) | __MLd(S,0x1,4) | __MLd(Type,0x0f,0);
    Util::setb(seg,dst,__MLd(P,0x1,7) | __MLd(DPL,0x3,5) | __MLd(S,0x1,4) | __MLd(Type,0x0f,0)); 
    dst++;
    
    //*dst = __MLd(G,0x1,7) | __MLd(D,0x1,6) | __MLd(L,0x1,5) | __MLd(AVL,1,4) | __MXp(int,Limit,0x0f0000,16,>>);   
    Util::setb(seg,dst,__MLd(G,0x1,7) | __MLd(D,0x1,6) | __MLd(L,0x1,5) | __MLd(AVL,1,4) | __MXp(int,Limit,0x0f0000,16,>>));
    dst++;
    
    //*dst = __MXp(int,BaseAddr,0xff000000,24,>>);
    Util::setb(seg,dst,__MXp(int,BaseAddr,0xff000000,24,>>));
    dst++;//point to the end
    
}

void SegmentDescriptor::fromMemory(SegmentDescriptor *sd,int seg,char* addr)
{
    char *dst=(char*)sd->Limit;
    char *src=addr;
    *(short*)dst = Util::get(seg,src);
    src+=2;dst = (char*)sd->BaseAddr;
    
    *(short*)dst = Util::get(seg,src);
    src+=2;dst = (char*)sd->BaseAddr+2;
    
    *dst = Util::get(seg,src);
    src++;dst = (char*)sd->Type;
    
    *dst = Util::get(seg,src) & 0x0f;
    dst=(char*)sd->S;
    
    *dst = (Util::get(seg,src) & 0x10) >> 4;
    dst=(char*)sd->DPL;
    
    *dst = (Util::get(seg,src) & 0x60) >> 5;
    dst=(char*)sd->P;
    
    *dst = (Util::get(seg,src) & 0x80) >> 7;
    src++;dst=(char*)sd->Limit+2;
    
    *dst = (Util::get(seg,src) & 0x0f);
    dst=(char*)sd->AVL;
    
    *dst = ((Util::get(seg,src)) & 0x10) >> 4;
    dst=(char*)sd->L;
    
    
    *dst = (Util::get(seg,src)& 0x20) >> 5;
    dst=(char*)sd->D;
    
    
    *dst = (Util::get(seg,src) & 0x40) >> 6;
    dst=(char*)sd->G;
    
    *dst = (Util::get(seg,src) & 0x80) >> 7;
    src++;dst=(char*)sd->BaseAddr+3;
    
    *dst = Util::get(seg,src);
    src++;dst++;//指向末位
    
    
}