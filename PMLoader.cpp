#ifdef CODE16
__asm__(".code16gcc \n\t");
#elif defined CODE32
__asm__(".code32 \n\t");
#endif


#include "PMLoader.h"
#include "libx2.h"
#include "Descriptor.h"

PMLoader::PMLoader(int driver,int secStart,int secNum,int codeSeg,int codeOff):Driver(driver),SecStart(secStart),SecNum(secNum),CodeSeg(codeSeg),CodeOff(codeOff)
{
}

PMLoader::~PMLoader()
{

}

void PMLoader::enableA20()
{
    __asm__(
       "inb $0x92,%al \n\t" //读取0x92端口，置位1为1，重新写入
       "orb $0b00000010,%al \n\t"
       "outb %al,$0x92 \n\t"
    );
}
void PMLoader::setidtr(short len,int address)
{

    __asm__(
        "movw 4+4*1(%ebp),%ax \n\t"
        "movw %ax,4+4*1+2(%ebp) \n\t"
        "lidt 4+4*1+2(%ebp) \n\t"
    );
}
void PMLoader::setgdtr(short len,int address)
{
    __asm__(
        "movw 4+4*1(%ebp),%ax \n\t"
        "movw %ax,4+4*1+2(%ebp) \n\t"
        "lgdt 4+4*1+2(%ebp) \n\t"
    );
}

#ifdef CODE16
#define SAFESEG 0xa0b
//===============仅16位=============
void PMLoader::enterProtected() //仅16位
{
    __asm__(
    "mov %cr0,%eax \n\t" //100b
    "or $0x1,%eax \n\t"
    "mov %eax,%cr0 \n\t"
    "ljmp $JMPSEG,$JMPOFF \n\t"
    );
}
void PMLoader::adjustProtectedCode()
{
    if(this->CodeSeg < SAFESEG)
    {
          Util::readSectors(SAFESEG,0,this->Driver,this->SecStart,this->SecNum);
          Util::memcopy(SAFESEG,0,this->CodeSeg,this->CodeOff,this->SecNum * 512);
    }else{
        Util::readSectors(this->CodeSeg,this->CodeOff,this->Driver,this->SecStart,this->SecNum);
    }

}
void PMLoader::mainProcess(int idtaddr,short idtlen,int gdtaddr,short gdtlen,int loaderSeg,int loaderLimit,int stackPointer) //仅16位
{
       //===========PMLoader Start==========
    PMLoader &pmldr=*(this);

    SegmentDescriptor nullSeg,
                        loaderSegCode(0,loaderLimit,SegmentDescriptor::TYPE_U_CODE_NONCONFORMING,0),
                        loaderSegData(0,loaderLimit,SegmentDescriptor::TYPE_U_DATA,0),
                        loaderSegStack(0,stackPointer,SegmentDescriptor::TYPE_U_STACK,0),
                        videoSeg(0xb8000,25*80*2,SegmentDescriptor::TYPE_U_DATA,0);
    nullSeg={0};//not really all zeros.
 
    nullSeg.writeToMemory(0,gdtaddr);      
    videoSeg.writeToMemory(0,gdtaddr+1*8);
    loaderSegCode.writeToMemory(0,gdtaddr+2*8); 
    loaderSegData.writeToMemory(0,gdtaddr+3*8);
    loaderSegStack.writeToMemory(0,gdtaddr+4*8);//B set 4GB
    
    pmldr.adjustProtectedCode();
    pmldr.enableA20();
    //===BUG with int 0x13
    pmldr.setidtr(idtlen,idtaddr);
    //===BUG
    pmldr.setgdtr(gdtlen,gdtaddr);
    //===BUG
    pmldr.enterProtected();
    
    //===========PMLoader End==============
}
#undef SAFESEG
#endif
