
#ifndef __libx2__
#define __libx2__
#include "def.h"
//静态工具类
class Util{
    
    
public:
    Util();
    ~Util();
    //*****兼容：16位，32位*******
    static int x,y;
    //ON用 | 
    //OFF用 &
    const static int MODE_COMMON,MODE_FL_ON,MODE_FL_OFF,MODE_BG_RED,MODE_BG_GREEN,MODE_BG_BLUE,MODE_BG_WHITE,MODE_BG_RG,MODE_BG_RB,MODE_BG_BG,MODE_BG_BLACK,MODE_FG_RED,MODE_FG_GREEN,MODE_FG_BLUE,MODE_FG_WHITE,MODE_FG_RG,MODE_FG_RB,MODE_FG_BG,MODE_FG_BLACK;
    const static int SCREEN_X,SCREEN_Y;
    static int videoSelector;
    static void printStr(const char* str_addr,int mode=MODE_COMMON);
    static void printChar(char ch,int mode=MODE_COMMON);//0x7:White_Black_NoFlash
    static void setCursor(int x,int y); //25 * 80
    static void newLine();
    static void insertMark(int marker=0x1234);//插入一个语句 mov $,%eax
 
    static int get(int seg,int off);//seg=0x10000指向当前ds
    static void setb(int seg,int off,int byte);
    static void setw(int seg,int off,int halfWord);
    static void setl(int seg,int off,int word);
    static void clr();
    void test();
    /**
     * copy by byte
     */
    static void memcopy(int srcSeg,int srcOff,int dstSeg,int dstOff,int len);

    //==================仅32位
#ifdef CODE32
public:
    
    static short makeSel(int index,int dpl=0b00,int from=0);
    static void ltr(int sel);
    AS_MACRO static void cli();
    AS_MACRO static void sti();
    AS_MACRO static void enterDs(int seg,int temp);
    AS_MACRO static void leaveDs(int seg,int temp);
    AS_MACRO static void jmpDie();
    AS_MACRO static void intReturn();
    static void changeCPL(int eip,int cs,int eflags,int esp,int ss);
    static int getEflags();
    static char getCPL();
    static char getDPL(int sel);
    static void outb(int port,int byte);

#endif
    
    
#ifdef CODE16
    //===========仅16位=============
    /**
     *if error,return 0
     *else return 1
     * 使用逻辑扇区编址
     *      扇区： 6位
     *      head:  8位 
     *      cylinder: 10位
     *  共24位
     *      LBA=((C*HPC)+H)*SPT+S-1
     *          C = 80
     *          HPC = 2
     *          SPT = 18
     *          BPS = 512 (Byte per Sector)
     *      65扇区  
     *      64扇区    0b1000000   0,1,1
     *      62扇区    0b0111110   0,0,63
     *      0扇区     0b0000000   0,0,1
     * 1.44 CHS = (80,2,18),0b10001 (LBA/18/2,LBA/18%2 LBA%18 + 1 
     *          (0,1,1) = 1*18+1*2*18+0*80*2*18
     *
     *          LBA = (S-1) + H*18+C*18*2 
     *          C = LBA/18/2
     *          H = LBA/18 - 2*C
     *          S = LBA%18 + 1
     *
     *
    */
private:
    static int readSectorsCHS(int dstSeg,int dstOff,int driver,int cylinder,int head,int startSec,int numSecs);
public:
    static int readSectors(int dstSeg,int dstOff,int driver,int LBAStart,int numSecs);
#endif

    
};

#ifdef CODE32
class SimpleCharRotator{
public:
    const static char rotateShapes[12];
    
    SimpleCharRotator(int x,int y,int attr=Util::MODE_COMMON,int direction=1);
    ~SimpleCharRotator();
    
    void setPosition(int x,int y);
    void setAttr(int mode=Util::MODE_COMMON);
    void run();
private:
    int X,Y,Attr;
    int Status;
    int Direction;
};
#endif

//================函数宏区：使用 __attribute__((always_inline))===============
#ifdef CODE32
void Util::cli()
{
    __asm__("cli \n\t");
}
void Util::sti()
{
    __asm__("sti \n\t");
}
void Util::enterDs(int seg,int temp)
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
void Util::jmpDie()
{
    __asm__("jmp .\n\t");
}
void Util::intReturn()
{
    __asm__(
    "leave \n\t"
    "iret \n\t"
    );
}
#endif


//============================================================================

#endif