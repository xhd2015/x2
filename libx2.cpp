#ifdef CODE16
    __asm__(".code16gcc \n\t");
#elseif defined CODE32
    __asm__(".code32 \n\t");
#endif


#include "libx2.h"


int Util::x=0;
int Util::y=0;

const int Util::SEG_CURRENT =    0x10000;//运行期常数，有时我需要一个编译期常数
int Util::videoSelector=
#ifdef CODE16
    0xb800;
#elseif defined CODE32
    0b10000; //第一项
#endif


Util::Util()
{
    Util::printStr(">>>Init");
    Util::newLine();    
}

Util::~Util()
{
    Util::printStr(">>>Destroy");
    Util::newLine();
}
void Util::test()
{
    Util::printStr(">>>test");
    Util::newLine();
}

void Util::printStr(const char* str_addr,int mode)
{
    while(*str_addr)
    {
        Util::printChar(*str_addr++,mode);
    }
}
void Util::printChar(char ch,int mode)
{
    if(ch == '\n')
    {
        Util::newLine();
        return;
    }else if(ch == '\r')
    {
        Util::y = 0;
        return;
    }
    
    if(Util::y==80*2) //为了防止某些情况下两次newLine，比如打印完最后一个字符时。所以把这个移动到这里
    {
        Util::newLine();
    }
    int Lpos = Util::x * 80*2 + Util::y;//25 * 80
    __asm__ __volatile__(
    "push %%es\n\t"
    "mov %%dx,%%es\n\t" //视频缓冲区
    "movb %%al,%%es:(%%bx) \n\t"
    "inc %%ebx \n\t"
    "movb %%cl,%%es:(%%bx) \n\t"
    "pop %%es \n\t"
    :
    :"a"(ch),"b"(Lpos),"c"(mode),"d"(Util::videoSelector)
    :"memory"
    );
    Util::y += 2;
    
}
void Util::newLine()
{
   
    Util::y = 0;
    Util::x = (Util::x+1)%25;
}
void Util::insertMark(int marker)
{
    __asm__(
     "nop \n\t"
    );
}
 int Util::get(int seg,int off)
 {
     if(seg==0x10000)
     {
         __asm__ __volatile__(
            "xor %%eax,%%eax \n\t"
           "movw %%ds,%%ax \n\t"
         :"=a"(seg)
         :
         :
         );
     }
     int rt;
     __asm__ __volatile__(
        "push %%es \n\t"
        "movw %%ax,%%es \n\t"
        "movl %%es:(%%ebx),%%eax \n\t"
       "pop %%es\n\t" 
       :"=a"(rt)
       :"b"(off),"a"(seg)
       :
     );
     return rt;
 }
void Util::setb(int seg,int off,int byte)
{
     if(seg==0x10000)
     {
         __asm__ __volatile__(
            "xor %%eax,%%eax \n\t"
            "movw %%ds,%%ax \n\t"
         :"=a"(seg)
         :
         :
         );
     }
    __asm__ __volatile__(
        "push %%es \n\t"
        "movl 4+4*1(%%ebp),%%eax \n\t"
        "movw %%ax,%%es \n\t"
        "movl 4+4*2(%%ebp),%%ebx \n\t"
        "movb 4+4*3(%%ebp),%%al \n\t"
        "movb %%al,%%es:(%%ebx) \n\t"
        "pop %%es \n\t"
                :
        :
        :"ebx","eax","memory"
    );
}
void Util::setw(int seg,int off,int halfWorld)
{
     if(seg==0x10000)
     {
         __asm__ __volatile__(
            "xor %%eax,%%eax \n\t"
            "movw %%ds,%%ax \n\t"
         :"=a"(seg)
         :
         :
         );
     }
    __asm__ __volatile__(
        "push %%es \n\t"
        "movl 4+4*1(%%ebp),%%eax \n\t"
        "movw %%ax,%%es \n\t"
        "movl 4+4*2(%%ebp),%%ebx \n\t"
        "movw 4+4*3(%%ebp),%%ax \n\t"
        "movw %%ax,%%es:(%%ebx) \n\t"
        "pop %%es \n\t"
        :
        :
        :"ebx","eax","memory"
    );
}
void Util::setl(int seg,int off,int word)
{
     if(seg==0x10000)
     {
         __asm__ __volatile__(
            "xor %%eax,%%eax \n\t"
            "movw %%ds,%%ax \n\t"
         :"=a"(seg)
         :
         :
         );
     }
    __asm__ __volatile__(
        "push %%es \n\t"
        "movl 4+4*1(%%ebp),%%eax \n\t"
        "movw %%ax,%%es \n\t"
        "movl 4+4*2(%%ebp),%%ebx \n\t"
        "mov 4+4*3(%%ebp),%%eax \n\t"
        "mov %%eax,%%es:(%%ebx) \n\t"
        "pop %%es \n\t"
        :
        :
        :"ebx","eax","memory"
    );
}

void Util::memcopy(int srcSeg,int srcOff,int dstSeg,int dstOff,int len)
{
    __asm__(
    "push %es \n\t"
    "push %ds \n\t" //ds:si es:di
    "push %esi \n\t"
    "push %edi \n\t"
    "mov 4+4*1(%ebp),%eax \n\t"
    "movw %ax,%ds\n\t"
    "mov 4+4*2(%ebp),%esi \n\t"
    "mov 4+4*3(%ebp),%eax \n\t"
    "movw %ax,%es \n\t"
    "mov 4+4*4(%ebp),%edi \n\t"
    "mov 4+4*5(%ebp),%ecx \n\t"
    "cld \n\t"
    "rep movsb \n\t"
    "pop %edi \n\t"
    "pop %esi \n\t"
    "pop %ds \n\t"
    "pop %es \n\t"
    );
    
}

#ifdef CODE16
//============仅16位===========
//ebp + 4 = 返回地址
//ebp + 4*n : n>0,第n个参数
int Util::readSectors(int dstSeg,int dstOff,int driver,int head,int cylinder,int startSec,int numSecs)
{
    int isCarried;
    __asm__ __volatile__(
    "push %%es\n\t"
    "mov 4+4*1(%%ebp),%%eax \n\t"
    "movw %%ax,%%es\n\t"
    "movw 4+4*2(%%ebp),%%bx\n\t"
    "movb 4+4*3(%%ebp),%%dl \n\t"
    "movb 4+4*4(%%ebp),%%dh \n\t"
    "movw 4+4*5(%%ebp),%%cx \n\t"
    "shl   $6,%%cx \n\t"
    "addb 4+4*6(%%ebp),%%cl \n\t"
    "movb $0x02,%%ah \n\t"
    "movb 4+4*7(%%ebp),%%al \n\t"
    "int $0x13 \n\t"
    "pop %%es \n\t"
    "xor %%eax,%%eax \n\t"
    "jc error \n\t"
    "mov $1,%%eax \n\t"
    "error:\n\t"
    :"=a"(isCarried)
    :
    :"memory","cc"
    );
    return isCarried;
}
#endif