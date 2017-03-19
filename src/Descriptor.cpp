#ifdef CODE16
    __asm__(".code16gcc \n\t");//此处开始为保护模式写代码
#elif defined(CODE32)
    __asm__(".code32 \n\t");
#endif


#include <Descriptor.h>
#include <libx2.h>

//指针类型
//#define __MXp(type,pointer,andNum,shiftNum,direction) ((*((type*)this->pointer) & (andNum) ) direction (shiftNum))
////直接量
//#define __MXd(pointer,andNum,shiftNum,direction) ((this->pointer & (andNum) ) direction (shiftNum))
//#define __MLd(pointer,andNum,shiftNum) __MXd(pointer,andNum,shiftNum,<<)
//#define __MRd(pointer,andNum,shiftNum) __MXd(pointer,andNum,shiftNum,>>)
Descriptor::Descriptor()
{

}

Descriptor::~Descriptor()
{

}
//==========For SegmentDescriptor===========
const int       SegmentDescriptor::TYPE_U_STACK = 0b0010,
                SegmentDescriptor::TYPE_U_EXPANEDDOWN=0b0110,
                SegmentDescriptor::TYPE_U_DATA = 0b0010,
                SegmentDescriptor::TYPE_U_CODE_NONCONFORMING = 0b1010,
                SegmentDescriptor::TYPE_U_CODE_CONFORMING = 0b1110,
                SegmentDescriptor::TYPE_S_UNUSED_1=0b0000,
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
SegmentDescriptor::SegmentDescriptor(char* baseaddr,int limit,char type,char dpl,char s,char b,char p):AVL(0),G(0),D(b),P(p),S(s),L(0),DPL(dpl),type(type)
{
	this->setBaseAddr((int)(size_t)baseaddr);
	this->setLimit(limit);
}
bool SegmentDescriptor::equals(SegmentDescriptor &sd2)
{
		return (*(int*)this == *(int*)&sd2) &&  ((*(int*)this+1)==*((int*)&sd2+1));
//    if(
//        (*(int*)this->BaseAddr == *(int*)sd2.BaseAddr) &&
//        ((*(int*)this->Limit & 0xfffff )== (*(short*)sd2.Limit & 0xfffff)) &&
//        (this->P == sd2.P) &&(this->L == sd2.L) && (this->B == sd2.B) &&  (this->S == sd2.S) &&
//        (this->Type == sd2.Type) && (this->G==sd2.G) && (this->AVL==sd2.AVL) && (this->DPL==sd2.DPL)
//        )
//        {
//            return 1;
//        }
//        return 0;
}
#if defined(CODE32)||defined(CODE16)
void SegmentDescriptor::writeToMemory(int seg,char* addr)
{
		Util::memcopy(Util::SEG_CURRENT, (int)(size_t)this,seg, (int)(size_t)addr, sizeof(*this));

//====DEPRECATED
//    char *dst;
//    dst = addr;
//    //*(short*)dst = __MXp(short,Limit,0xffff,0,>>);
//    Util::setw(seg,(int)dst,__MXp(short,Limit,0xffff,0,>>));
//    dst+=2;
//
//    //*(short*)dst = __MXp(int,BaseAddr,0xffff,0,>>);
//    Util::setw(seg,(int)dst,__MXp(int,BaseAddr,0xffff,0,>>));
//    dst+=2;
//
//    //*dst = __MXp(int,BaseAddr,0xff0000,16,>>);
//    Util::setb(seg,(int)dst,__MXp(int,BaseAddr,0xff0000,16,>>));
//    dst++;
//
//    //*dst = __MLd(P,0x1,7) | __MLd(DPL,0x3,5) | __MLd(S,0x1,4) | __MLd(Type,0x0f,0);
//    Util::setb(seg,(int)dst,__MLd(P,0x1,7) | __MLd(DPL,0x3,5) | __MLd(S,0x1,4) | __MLd(Type,0x0f,0));
//    dst++;
//
//    //*dst = __MLd(G,0x1,7) | __MLd(D,0x1,6) | __MLd(L,0x1,5) | __MLd(AVL,1,4) | __MXp(int,Limit,0x0f0000,16,>>);
//    Util::setb(seg,(int)dst,__MLd(G,0x1,7) | __MLd(D,0x1,6) | __MLd(L,0x1,5) | __MLd(AVL,1,4) | __MXp(int,Limit,0x0f0000,16,>>));
//    dst++;
//
//    //*dst = __MXp(int,BaseAddr,0xff000000,24,>>);
//    Util::setb(seg,(int)dst,__MXp(int,BaseAddr,0xff000000,24,>>));
//    dst++;//point to the end
    
}
//void SegmentDescriptor::writeToMemory(int seg,char* addr)
//{
//    char *dst;
//    dst = addr;
//    //*(short*)dst = __MXp(short,Limit,0xffff,0,>>);
//    Util::setw(seg,(int)dst,__MXp(short,Limit,0xffff,0,>>));
//    dst+=2;
//
//    //*(short*)dst = __MXp(int,BaseAddr,0xffff,0,>>);
//    Util::setw(seg,(int)dst,__MXp(int,BaseAddr,0xffff,0,>>));
//    dst+=2;
//
//    //*dst = __MXp(int,BaseAddr,0xff0000,16,>>);
//    Util::setb(seg,(int)dst,__MXp(int,BaseAddr,0xff0000,16,>>));
//    dst++;
//
//    //*dst = __MLd(P,0x1,7) | __MLd(DPL,0x3,5) | __MLd(S,0x1,4) | __MLd(Type,0x0f,0);
//    Util::setb(seg,(int)dst,__MLd(P,0x1,7) | __MLd(DPL,0x3,5) | __MLd(S,0x1,4) | __MLd(Type,0x0f,0));
//    dst++;
//
//    //*dst = __MLd(G,0x1,7) | __MLd(D,0x1,6) | __MLd(L,0x1,5) | __MLd(AVL,1,4) | __MXp(int,Limit,0x0f0000,16,>>);
//    Util::setb(seg,(int)dst,__MLd(G,0x1,7) | __MLd(D,0x1,6) | __MLd(L,0x1,5) | __MLd(AVL,1,4) | __MXp(int,Limit,0x0f0000,16,>>));
//    dst++;
//
//    //*dst = __MXp(int,BaseAddr,0xff000000,24,>>);
//    Util::setb(seg,(int)dst,__MXp(int,BaseAddr,0xff000000,24,>>));
//    dst++;//point to the end
//
//}
void SegmentDescriptor::fromMemory(SegmentDescriptor *sd,int seg,char* addr)
{
	  Util::memcopy(seg,(int)(size_t)addr, Util::SEG_CURRENT, (int)(size_t)sd, sizeof(*sd));
//=======DEPRECATED
//    char *dst=(char*)sd->Limit;
//    char *src=addr;
//    *(short*)dst = Util::get((int)seg,(int)src);
//    src+=2;dst = (char*)sd->BaseAddr;
//
//    *(short*)dst = Util::get((int)seg,(int)src);
//    src+=2;dst = (char*)sd->BaseAddr+2;
//
//    *dst = Util::get((int)seg,(int)src);
//    src++;dst = (char*)sd->Type;
//
//    *dst = Util::get((int)seg,(int)src) & 0x0f;
//    dst=(char*)sd->S;
//
//    *dst = (Util::get((int)seg,(int)src) & 0x10) >> 4;
//    dst=(char*)sd->DPL;
//
//    *dst = (Util::get((int)seg,(int)src) & 0x60) >> 5;
//    dst=(char*)sd->P;
//
//    *dst = (Util::get((int)seg,(int)src) & 0x80) >> 7;
//    src++;dst=(char*)sd->Limit+2;
//
//    *dst = (Util::get((int)seg,(int)src) & 0x0f);
//    dst=(char*)sd->AVL;
//
//    *dst = ((Util::get((int)seg,(int)src)) & 0x10) >> 4;
//    dst=(char*)sd->L;
//
//
//    *dst = (Util::get((int)seg,(int)src)& 0x20) >> 5;
//    dst=(char*)sd->D;
//
//
//    *dst = (Util::get((int)seg,(int)src) & 0x40) >> 6;
//    dst=(char*)sd->G;
//
//    *dst = (Util::get((int)seg,(int)src) & 0x80) >> 7;
//    src++;dst=(char*)sd->BaseAddr+3;
//
//    *dst = Util::get((int)seg,(int)src);
//    src++;dst++;//指向末位
}
#endif //CODE16&& CODE32
void SegmentDescriptor::init(char* baseaddr,int limit,char type,char dpl,char s,char b,char p,char g,char l,char avl)
{
	this->setBaseAddr((int)(size_t)baseaddr);
	this->setLimit(limit);
	this->type = type;
	this->DPL = dpl;
    this->DPL = dpl;
    this->S = s;
    this->D = b;
    this->P = p;
    this->G = g;
    this->L = l;
    this->AVL = avl;
}
/**
*门描述符 ，仅32位
*/
//===============For SelectorDescriptor==============
#ifdef CODE32
//const int SelectorDescriptor::TYPE_INT= 0x0600,//0b0000 0110 0000 0000,
//            SelectorDescriptor::TYPE_TASK=0x0500,//0b0000 0101 0000 0000
//            SelectorDescriptor::TYPE_TRAP=0x0700;
//const int SelectorDescriptor::SIZE_16=0,
//        SelectorDescriptor::SIZE_32=1;
SelectorDescriptor::SelectorDescriptor():
		__D(0),__DPL(0),__P(0)
{

}

SelectorDescriptor::~SelectorDescriptor()
{

}
void SelectorDescriptor::DPL(int dpl)
{
    *(this->I2+1) |= (char) ( (dpl & 0x3 ) << 5);
}
void SelectorDescriptor::P(int p)
{
    *(this->I2+1) |= (char) ( (p & 0x1 ) << 7);
}
void SelectorDescriptor::D(int d)
{
    
    *(this->I2+1) |= (char) ( (d & 0x1 ) << 3);
}
void SelectorDescriptor::Offset(int offset){
    *(short*)this->I0=(short)offset;
    *(short*)this->I3=(short)(offset >> 16);
}
void SelectorDescriptor::Selector(int selector)
{
    *(short*)this->I1=(short)selector;
}
void SelectorDescriptor::Type(int type)//0 task gate,1 int gate,2 trap gate
{
    *(short*)this->I2=(short)type;
}
void SelectorDescriptor::init(int sel,int offset,int type,int dpl,int p,int segSize)
{
    this->Offset(offset);
    this->Selector(sel);
    this->Type(type);
    this->D(segSize);
    this->DPL(dpl);
    this->P(p);
}
#if defined(CODE32)||defined(CODE16)
void SelectorDescriptor::writeToMemory(int seg,int off)
{
    Util::memcopy(Util::SEG_CURRENT,(int)this->I0,seg,off,this->I3  - this->I0 + 2);
}
void SelectorDescriptor::fromMemory(SelectorDescriptor &self,int seg,int off)
{
    Util::memcopy(seg,off,Util::SEG_CURRENT,(int)self.I0,self.I3-self.I0+2);
}
#elif defined(CODE64)
#include <cstring>
void SelectorDescriptor::writeToMemory(char *base)
{
	memcpy(base,this->I0,this->I3 - this->I0 +2);
}
void SelectorDescriptor::fromMemory(SelectorDescriptor &self,const char *base)
{
	memcpy(self.I0,base,self.I3 - self.I0 +2);
}
#endif

#endif
