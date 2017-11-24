/*
 * libx2_macros.h
 *
 *  Created on: 2017年3月24日
 *      Author: 13774
 */

#ifndef INCLUDE_MACROS_LIBX2_MACROS_H_
#define INCLUDE_MACROS_LIBX2_MACROS_H_

#include <libx2.h>
//================函数宏区：使用 __attribute__((always_inline))===============
#if defined(CODE32)||defined(CODE16)||CODE32USER
void Util::reboot()
{

    __asm__ __volatile__(
    "inb  $0x92,%%eax \n\t"
    "andb $0xfe,%%eax \n\t"
    "outb %%al,$0x92 \n\t"
    "orb $0x1,%%eax \n\t"
    "outb %%al,$0x92\n\t"
    :
    :
    :"eax"
    );
}
#endif


#if defined(CODE32) || defined(CODE16)
void	Util::setStrSel(int sel)
{
	Util::strSel=sel;
}
int  Util::getStrSel()
{
	return Util::strSel;
}
#endif

#if defined(CODE32) || defined(CODE16) || defined(CODE32USER)
void Util::insertMark(int marker)
{
    __asm__(
     "nop \n\t"
    );
}
void Util::jmpDie()
{
    __asm__("jmp .\n\t");
}

void Util::cli()
{
    __asm__("cli \n\t");
}
void Util::sti()
{
    __asm__("sti \n\t");
}
void Util::enterDs(int seg,int& temp)
{
    if(seg!=SEG_CURRENT)
    {
            __asm__ __volatile__(
            "mov %%ds,%%bx \n\t"
            "mov %%ax,%%ds \n\t"
            :"=b"(temp)
            :"a"(seg)
            :);
    }
}
void Util::leaveDs(int seg,int temp)
{
    if(seg!=SEG_CURRENT)
    {
        __asm__ __volatile__("mov %%ax,%%ds \n\t"::"a"(temp):);
    }
}
 void Util::enterEs(int seg,int& temp)
 {
     __asm__ __volatile__("mov %%es,%%ax\n\t":"=a"(temp)::);
    if(seg==SEG_CURRENT)
    {
        __asm__ __volatile__(
            "mov %%ds,%%ax \n\t"
            "mov %%ax,%%es \n\t"
            :
            :
            :"eax"
        );
    }else{
        __asm__ __volatile__(
        "mov %%ax,%%es \n\t"
        :
        :"a"(seg)
        :
        );
    }
 }
void Util::leaveEs(int temp)
{
    __asm__ __volatile__("mov %%ax,%%es \n\t"::"a"(temp):);
}

void Util::outb(short port,char data)
{
    __asm__(
    "outb %%al,%%dx \n\t"
    :
    :"d"(port),"a"(data)
    :
    );
}
void Util::outw(short port,short data)
{
    __asm__(
    "outw %%ax,%%dx \n\t"
    :
    :"d"(port),"a"(data)
    :
    );
}
char Util::inb(short port)
{
    char temp;
    __asm__(
    "inb %%dx,%%al \n\t"
    :"=a"(temp)
    :"d"(port)
    :
    );
    return temp;
}
short Util::inw(short port)
{
    short temp;
    __asm__(
    "inw %%dx,%%ax \n\t"
    :"=a"(temp)
    :"d"(port)
    :
    );
    return temp;
}

void Util::ljmp(int newcs,int neweip)
{
	__asm__ __volatile__(
			"pushw %%cx \n\t"
#if defined(CODE16)
			"pushw %%bx \n\t"
#elif defined(CODE32) || defined(CODE32USER)
			"push %%ebx \n\t"
#endif
			"ljmp *(%esp) \n\t"
			:
			:"c"(newcs),"b"(neweip)
			:"memory"
	);
}

void Util::replaceCs(int newcs)
{
	__asm__ __volatile__(
			"pushw  %%cx\n\t"
			"push  	$1f \n\t"
			"ljmp *(%esp) \n\t"
			"1:\n\t"
			:
			:"c"(newcs)
			:"memory"
	);
}

#if defined(CODE16)
int Util::readSectorsCHSInline(int dstSeg,int dstOff,int driver,int cylinder,int head,int startSec,int numSecs)
{
	   int isCarried;
	    __asm__ __volatile__(
	    "push %%es\n\t"
	    "// mov 4+4*1(%%ebp),%%eax \n\t" // ax由输入参数设置
	    "movw %%ax,%%es\n\t"
	    "// movw 4+4*2(%%ebp),%%bx\n\t" // bx 由输入参数设置
	    "// movb 4+4*3(%%ebp),%%dl \n\t"
	    "// movb 4+4*5(%%ebp),%%dh \n\t" // dl由输入参数设置，但是dh只能由head的值来设定
	    "   movb %[head],%%dh \n\t"
	    "// movw 4+4*4(%%ebp),%%cx \n\t" // cx由输入参数设定
	    "shl   $6,%%cx \n\t"
	    "addb %[startSec],%%cl \n\t"
	    "movb $0x02,%%ah \n\t"
	    "movb %[numSecs],%%al \n\t"
	    "int $0x13 \n\t"
	    "pop %%es \n\t"
	    "xor %%eax,%%eax \n\t"
	    "jc 1f \n\t"
	    "mov $1,%%eax \n\t"
	    "1:\n\t"
	    :"=a"(isCarried)
	    :"a"(dstSeg),"b"(dstOff),"d"(driver),"c"(cylinder),
		 	 [head]"m"(head),[startSec]"m"(startSec),[numSecs]"m"(numSecs)
	    :"memory","cc"
	    );
	    return isCarried;
}
int Util::readSectorsInline(int dstSeg,int dstOff,int driver,int LBAStart,int numSecs)
{
	 return Util::readSectorsCHSInline(dstSeg,dstOff,driver,LBAStart/36,(LBAStart - LBAStart/36*36)/18,(LBAStart%18) + 1,numSecs);
}
#endif
/*
void Util::pusha()
{
    __asm__("pusha \n\t");
}
void Util::popa()
{
    __asm__("popa \n\t");
}
*/
#endif

#if defined(CODE32) || defined(CODE32USER)
int Printer::getX()
{
    return this->x;
}

int Printer::getY()
{
    return this->y;
}

//=======class ErrorSaver
ErrorSaver::ErrorSaver(int errno):errno(errno) {
}

int ErrorSaver::getErrno() const {
	return this->errno;
}

void ErrorSaver::setErrno(int errno) {
	this->errno=errno;
}

void Util::ltr(int sel)
{
    __asm__ __volatile__(
    "ltr %0 \n\t"
    :
    :"m"(sel)
    :
    );
}
void Util::lldt(int sel)
{
    __asm__ __volatile__(
    "lldt %0 \n\t"
    :
    :"m"(sel)
    :
    );
}
int	Util::getCurrentDs()
{
	int temp;
	__asm__ __volatile__(
	"push %%ds \n\t"
	"pop %%eax \n\t"
	:"=a"(temp)
	:
	:
	);
	return temp;
}
void Util::setCurrentDs(int ds)
{
	__asm__ __volatile__(
			"mov %%eax,%%ds \n\t"
			:
			:"a"(ds)
			 :
			 );
}

int	Util::getCurrentSs()
{
	int temp;
	__asm__ __volatile__(
	"push %%ss \n\t"
	"pop %%eax \n\t"
	:"=a"(temp)
	:
	:
	);
	return temp;
}
void Util::setCurrentSs(int ss)
{
	__asm__ __volatile__(
			"mov %%eax,%%ss \n\t"
			:
			:"a"(ss)
			 :
			 );
}

#if defined(CODE32)
void Util::intReturn()
{
    __asm__(
    "leave \n\t"
    "iret \n\t"
    );
}
#endif
/**this originally works
void Util::initTarget(void *&target)
{
    __asm__ __volatile__("":"=c"(target)::);
}
*/
/************Deprecated
void Util::initTarget(void **target)
{
__asm__ __volatile__("":"=c"(*(char**)target)::);
}
*/
#endif


#if defined(CODE32)||defined(CODE64)||defined(CODE32USER)
//=======class : Queue 宏
template <typename T>
bool Queue<T>::isEmpty()
{
    return curLen==0;
}
template <typename T>
bool Queue<T>::isFull()
{
    return curLen==len;
}
template <typename T>
unsigned int Queue<T>::size()
{
    return curLen;
}
#endif

//============================================================================




#endif /* INCLUDE_MACROS_LIBX2_MACROS_H_ */
