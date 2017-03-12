#ifndef IOProgramer_h__
#define IOProgramer_h__


#include <def.h>
#include <libx2.h>

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

/**
 * CMOS中包含基本的磁盘信息,时间信息
 *
 * 应当全部是静态函数
 *
 */
class IO_CMOS{
protected:
	IO_CMOS();
	~IO_CMOS();
public:


};

/**
 * Very simple,just a demo of how hard disk is accessed
 */
class IO_HDD{
protected:
public:
	typedef IO_HDD This;
	//If use LBA28,then this is used
	enum{
		PORT_DATA=0x1f0,/*16 bit,data is read from/write to here*/
		PORT_ERROR_CODE=0x1f1,
		PORT_SECNUM=0x1f2,
		PORT_SECSTART_0=0x1f3,
		PORT_SECSTART_1=0x1f4,
		PORT_SECSTART_2=0x1f5,
		PORT_SECSTART_3=0x1f6/*the ending 4 bits of LBA28*/,
		PORT_READ_COMMAND=0x1f7,PORT_WRITE_COMMAND=0x1f7,
		PORT_STATUS = PORT_READ_COMMAND

	};

	IO_HDD(int hddNo,size_t secStart,unsigned char secNumber,int dstSeg,size_t dstOff);
	IO_HDD();
	~IO_HDD();
	/**
	 * hddNumber  = 0 ,master
	 * 			  = 1 ,slave
	 *  secStart must contains a valid LBA28
	 */
	void read();
	INCOMPLETE void write();
	AS_MACRO static bool	isBusy(char status);
	AS_MACRO static bool	isReady(char status);
	AS_MACRO static bool	isError(char status);
	AS_MACRO static char readStatus();
	AS_MACRO size_t getDstOff() const;
	AS_MACRO void setDstOff(size_t dstOff);
	AS_MACRO int getDstSeg() const;
	AS_MACRO void setDstSeg(int dstSeg);
	AS_MACRO int getHddNo() const;
	AS_MACRO void setHddNo(int hddNo);
	AS_MACRO bool isLbaMode() const;
	AS_MACRO unsigned char getSecNumber() const;
	AS_MACRO void setSecNumber(unsigned char secNumber);
	AS_MACRO size_t getSecStart() const;
	AS_MACRO void setSecStart(size_t secStart);

protected:
	AS_MACRO void writeSecNum();
	AS_MACRO void writeSecStart();
	AS_MACRO void requestRead();
	AS_MACRO void requestWrite();
	void readData();
	AS_MACRO void waitUntilReady();
	void writeData();

	int hddNo;
	bool LBAMode;
	size_t secStart;
	unsigned char secNumber;
	int dstSeg;
	size_t dstOff;

};

class IO_Floppy{

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

//================Function Macros
//=========class : Keyboard
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


//========class :IO_HDD
bool  IO_HDD::isBusy(char status)
{
	return (status & 0x80);
}

bool IO_HDD::isReady(char status)
{
	return (status & 0x8);
}

bool IO_HDD::isError(char status)
{
	return (status & 0x1);
}

char IO_HDD::readStatus()
{
	return Util::inb(This::PORT_STATUS);
}

void  IO_HDD::writeSecNum()
{
	Util::outb(This::PORT_SECNUM,this->secNumber);
}

void IO_HDD::writeSecStart() {
	Util::outb(This::PORT_SECSTART_0, (char)this->secStart);
	Util::outb(This::PORT_SECSTART_1, (char)(this->secStart >> 8));
	Util::outb(This::PORT_SECSTART_2, (char)(this->secStart >> 16));
	Util::outb(This::PORT_SECSTART_3, ((char)(this->secStart >> 24) & (0xf) )|
				(( this->LBAMode & 0x1) <<6)|
				((this->hddNo & 0x1) << 4) |
				0xa0
	);
}
void IO_HDD::requestRead()
{
	Util::outb(This::PORT_READ_COMMAND, 0x20);
}
void IO_HDD::requestWrite()
{
	Util::outb(This::PORT_WRITE_COMMAND, 0x30);
}
void IO_HDD::waitUntilReady()
{
	char status;//=This::readStatus();
	while(true)
	{
		status=This::readStatus();
		if(!This::isBusy(status) && This::isReady(status))break;
	}
}
size_t IO_HDD::getDstOff() const {
	return dstOff;
}

void IO_HDD::setDstOff(size_t dstOff) {
	this->dstOff = dstOff;
}

int IO_HDD::getDstSeg() const {
	return dstSeg;
}

void IO_HDD::setDstSeg(int dstSeg) {
	this->dstSeg = dstSeg;
}

int IO_HDD::getHddNo() const {
	return hddNo;
}

void IO_HDD::setHddNo(int hddNo) {
	this->hddNo = hddNo;
}

bool IO_HDD::isLbaMode() const {
	return LBAMode;
}

unsigned char IO_HDD::getSecNumber() const {
	return secNumber;
}

void IO_HDD::setSecNumber(unsigned char secNumber) {
	this->secNumber = secNumber;
}

size_t IO_HDD::getSecStart() const {
	return secStart;
}

void IO_HDD::setSecStart(size_t secStart) {
	this->secStart = secStart;
}
#endif //CODE32

#endif
