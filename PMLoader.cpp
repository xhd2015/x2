#ifdef CODE16
__asm__(".code16gcc \n\t");
#elseif defined CODE32
__asm__(".code32 \n\t");
#endif


#include "PMLoader.h"
#include "libx2.h"

PMLoader::PMLoader(int driver,int head,int cylinder,int secStart,int secNum,int codeSeg,int codeOff):Driver(driver),Head(head),Cylinder(cylinder),SecStart(secStart),SecNum(secNum),CodeSeg(codeSeg),CodeOff(codeOff)
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
//===============仅16位=============
void PMLoader::enterProtected() //仅16位
{
    __asm__(
    "mov %cr0,%eax \n\t"
    "or $0x1,%eax \n\t"
    "mov %eax,$cr0 \n\t"
    "ljmp $0b10000,$0 \n\t"
    );
}
void PMLoader::ajustProtectedCode()
{
    Util::readSectors(this->CodeSeg,this->CodeOff,this->Driver,this->Head,this->Cylinder,this->SecStart,this->SecNum);
}
void PMLoader::mainProcess() //仅16位
{
    
}
#endif
