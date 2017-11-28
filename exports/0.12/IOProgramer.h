#ifndef __IOProgramer__
#define __IOProgramer__


#include "def.h"
#include "libx2.h"

#ifdef CODE32
class IO_8259A{
public:
    //电平模式=1，边沿触发=0
    //ON是|，OFF是&
#ifdef __I_REALLY_NEED_THIS
    const static unsigned int ICW1_EDGE_MODE_OFF,ICW1_ELEC_MODE_ON,
                 ICW1_SINGLE_CHIP_ON,ICW1_MULTI_CHIPS_OFF,
                 ICW1_REQUIRE_ICW4_ON,ICW1_NO_ICW4_OFF,
                 ICW1_BASE_ON,ICW1_BASE_OFF;
    const static unsigned int  ICW4_SPECIAL_COMPLETE_NEST_ON,ICW4_COMMON_COMPLETE_NEST_OFF,
                ICW4_BUFFER_ON,ICW4_NONBUFFER_OFF,
                ICW4_AUTO_END_ON,ICW4_EOI_OFF,
                ICW4_FOR_80x86_ON,ICW4_FOR_MCS_OFF,
                ICW4_BASE_ON,ICW4_BASE_OFF;
    const static unsigned int OCW2_EOI_COMPLETE_NEST,OCW2_BASE_ON,OCW2_BASE_OFF;
#endif
    
    const static int PORTS[4];
public:
    IO_8259A();
    ~IO_8259A();
    //0--主片  1--从片
    void sendICW1(int chip=0,int electTriggerMode=0,int singleChip=0,int requireICW4=1);
    void sendICW2(int chip=0,int base=0x20);
    void sendICW3(int chip=0,int linkage=0x4);
    void sendICW4(int chip=0,int specCompNest=0,int buf=0,int autoEndEOI=0,int useFor80x86=1);
    void sendOCW1(int chip=0,int mask=0x0);
    void sendOCW2(int chip=0,int eoi=0x20);
    
    
protected:
private:

};

/**
*8254是8253的进化版。它是一个可编程定时器/计数器。
*芯片有3个独立的16位计数通道，每个通道有自己的计数器，但3个通道是完全相同的。
*   A0,A1用来控制要读写的通道
*3个
*/
class IO_8253{//产生IRQ0，0x20号中断
public:
    const static int PORTS[4];
    const static unsigned int MAXNUM;
    const static unsigned int MAX_MICRO;
public:
    IO_8253();
    ~IO_8253();
    
    
    /**
    *由于精确度的原因，在此处设置两个给予不同单位的setTime，基于微秒的允许最大值是3599，这是为了防止溢出
    */
    void setTimeMicro(int tunel,unsigned int microsecs);//微秒，允许最大值 3599
    void setTimeMill(int tunel,unsigned int millsecs);//毫秒,
    void sendControlByte(int tunel=0,int writeOrder=0b11,int workingMode=0x3,int BCDMode=0);
    
    
};

class Keyboard{
public:
    const static int PORT_DATA,PORT_CONTROL,PORT_PPI;
    const static int NO_DATA_ERROR;//0x10000
    const static int KEY_MAP_STD_LEN;
    const static char* KEY_MAP_STD[];
    /**
    *在此处定义标准键盘 把键盘线性化、连续化以便处理.需要标准化的键指那些不必依赖其他键就能产生输出的键
    *那些控制键不包括在内，控制键是 ctrl,shift,alt,caps lock,num lock
    *
    *按键类型：
    *   单键  --  不包括
    *   双键  --  ctrl+单键 shift+单键
    *   三键  --  ctrl+shift+单键
    *
    *接受到一个接通码
    *接受到一个断开码，判断上一个码是否是该码的接通码，是：放入队列， 否：丢弃
    *
    *或者，接受到一个接通码，加入队列
    *接收到一个断开码，丢弃
    *
    */

public:
    Keyboard();
    ~Keyboard();
    
    /**
    *输入端口0x60 0x64有数据就是busy
    */
    AS_MACRO int isBusy();
    /**
    *0x60端口是否有给系统的数据？即数据是否已经准备好
    */
    AS_MACRO int hasData();
    
    /**
    *读取扫描码
    * -1 表示出错
    */
    AS_MACRO int readScanCode();
    
    /**
    *禁止/允许键盘工作
    *通过 0x61位1来设置
    */
    AS_MACRO void enable();
    AS_MACRO void disable();
    
    
    
    void waitToWrite();
   
    const char* getAsciiChar(unsigned char code);
    
    
protected:
    int leds;
    
    
};
int Keyboard::isBusy()
{
    return Util::inb(Keyboard::PORT_CONTROL) & 0x2;
}
int Keyboard::hasData()
{
    return Util::inb(Keyboard::PORT_CONTROL) & 0x1;
}
int Keyboard::readScanCode()
{
    return Util::inb(Keyboard::PORT_DATA);
}
void Keyboard::enable()
{
    int a=Util::inb(Keyboard::PORT_PPI);
    Util::outb(Keyboard::PORT_PPI,a & 0x7f);
}
void Keyboard::disable()
{
    int a=Util::inb(Keyboard::PORT_PPI);
    Util::outb(Keyboard::PORT_PPI,a | 0x80);
}
#endif //CODE32

#endif