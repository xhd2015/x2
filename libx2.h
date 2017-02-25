
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
    const static int SEG_CURRENT;
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
    /**
    *使0x92端口的位0从0变化成1从而重启计算机
    */
    AS_MACRO static void reboot();
    void test();
    /**
     * copy by byte
     */
    static void memcopy(int srcSeg,int srcOff,int dstSeg,int dstOff,int len);

    //==================仅32位
#ifdef CODE32
public:
    

    AS_MACRO static void cli();
    AS_MACRO static void sti();
    AS_MACRO static void enterDs(int seg,int& temp);
    AS_MACRO static void leaveDs(int seg,int temp);
    AS_MACRO static void enterEs(int seg,int& temp);
    AS_MACRO static void leaveEs(int temp);
    AS_MACRO static void jmpDie();
    AS_MACRO static void outb(int port,int data);
    AS_MACRO static int inb(int port);
    AS_MACRO static void ltr(int sel);
    static void lidt(short len,int address);
    static void lgdt(short len,int address);
    
    //=============DEPRECATED===========
    DEPRECATED AS_MACRO static void pusha();//这些宏通常用于中断处理，但是由于在堆栈框架之内的任何栈操作都是错误的，因此将它们标记为过时的
    DEPRECATED AS_MACRO static void popa();
    
    
    static short makeSel(int index,int dpl=0b00,int from=0);
    
    static void changeCPL(int eip,int cs,int eflags,int esp,int ss);
    static int getEflags();
    static char getCPL();
    static char getDPL(int sel);
    
    //如果某些功能暂时不能由某个类实现，就在这里实现它们。
    
    /**
    *将数字转换成10进制/16进制的字符串
    *如果空间不足以存储，就返回0
    *否则返回实际用的空间
    */
    static int digitToStr(char* save,unsigned int space,int n);
    static int digitToHex(char* save,unsigned int space,unsigned int n);
    static int strcmp(const char* a,const char *b);
    static int strlen(const char *a);
    static int strcopy(const char *src,char *dst,int len);
    
    
    
    //========与调用相关的宏
    /**
    *获取一个返回class类型的成员函数的返回对象的参数
    *如果不明确返回所声明的类型，g++是允许编译通过的。但是这样做可能是错误的（即什么都不返回）
    * DO NOT USE IT
    */
    DEPRECATED AS_MACRO static void initTarget(void** target);

    AS_MACRO static void intReturn();
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
/**
*标准屏幕打印管理器
*   通过限制一个矩形区域让打印个性化！！！
*/
class Printer{
public:
    const static int SCREEN_MAX_X,SCREEN_MAX_Y;
public:
    Printer(unsigned int x0=0,unsigned int y0=0,unsigned int rows=Printer::SCREEN_MAX_X,unsigned int cols=Printer::SCREEN_MAX_Y,int mode=Util::MODE_COMMON);
    ~Printer();
    
    void putc(int chr);
    void putsz(char* str);
    void putsn(char *str,int n);
    void setPos(int x,int y);
    void move(int n);
    void setMode(int mode);
    void clr();
    /**
    *direction=-1 即向前
    */
    INCOMPLETE int isInside(int x,int y);
    
    AS_MACRO int getX();
    AS_MACRO int getY();
    
    //相对于申请屏幕的偏移和大小
    // can't be outside the screen
    INCOMPLETE Printer  getSubPrinter(unsigned int x0,unsigned int y0,unsigned int rows,unsigned int cols,int mode);
    
protected:
    int getPos();
    
    
    unsigned int rows,cols,x0,y0;
    int x,y;
    int mode;
    
    
    Printer *father;
    Printer *sons[5]; //need to check if a position is possessed by this printer or its sons.
                        //currently the biggest size is 5
                        //注意排序
    unsigned int sonSize;
    
private:
    /**
    *处理特殊字符
    *   1 --    已经处理
    *   -1 --   是NULL字符
    *   0   --  正常打印
    *
    */
    int specailCharProcessor(int chr);
    /**
    *提供核心部分代码，不包括设置es和显示模式
    *dl提供显示属性
    */
    void __putc(int chr);
};

//===============class :String
class String{
public:
    String(const char* str);
    ~String();
    
    int size();
    char get(int index);
    void set(int index,int ch);
    
    static String valueOf(int n);
protected:
    char *str;
    
};
//==============class :Queue
template <typename T>
class Queue{
public:
    Queue(T p[],unsigned int len);//掌管指针
    ~Queue();
    
    T remove();
    int add(T t);
    AS_MACRO unsigned int size();
    AS_MACRO int empty();
    AS_MACRO int full();
protected:
    T *p;
    unsigned int len;
    unsigned int curLen;
    int indexAdd,indexRemove;
};

#endif

//================函数宏区：使用 __attribute__((always_inline))===============
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

#ifdef CODE32
int Printer::getX()
{
    return this->x;
}

int Printer::getY()
{
    return this->y;
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
/**this originally works
void Util::initTarget(void *&target)
{
    __asm__ __volatile__("":"=c"(target)::);
}
*/
void Util::initTarget(void **target)
{
__asm__ __volatile__("":"=c"(*(char**)target)::);
}

void Util::outb(int port,int data)
{
    __asm__(
    "outb %%al,%%dx \n\t"
    :
    :"d"(port),"a"(data)
    :
    );
}
int Util::inb(int port)
{
    int temp;
    __asm__(
    "inb %%dx,%%al \n\t"
    :"=a"(temp)
    :"d"(port)
    :
    );
    return temp;
}
void Util::pusha()
{
    __asm__("pusha \n\t");
}
void Util::popa()
{
    __asm__("popa \n\t");
}

//=======class : Queue 宏
template <typename T>
int Queue<T>::empty()
{
    return curLen==0;
}
template <typename T>
int Queue<T>::full()
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


#endif
