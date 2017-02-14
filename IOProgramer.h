#ifndef __IOProgramer__
#define __IOProgramer__
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
#endif //CODE32

#endif