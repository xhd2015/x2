
#include <IOProgramer.h>
#include <libx2.h>
#include <def.h>

#ifdef CODE32
__asm__(".code32 \n\t");
#elif defined(CODE16)
__asm__(".code16gcc \n\t");
#endif

#if defined(CODE32)
#ifdef __I_REALLY_NEED_THIS
const unsigned int IO_8259A::ICW1_EDGE_MODE_OFF=0b0,
                   IO_8259A::ICW1_ELEC_MODE_ON=0b1000,
                    IO_8259A::ICW1_SINGLE_CHIP_ON=0b10,
                    IO_8259A::ICW1_MULTI_CHIPS_OFF=0b0,
                    IO_8259A::ICW1_REQUIRE_ICW4_ON=0b1,
                    IO_8259A::ICW1_NO_ICW4_OFF=0b0,
                    IO_8259A::ICW1_BASE_ON = 0b0001000,
                    IO_8259A::ICW1_BASE_OFF = 0b00011011;
                    
const unsigned int 	IO_8259A::ICW4_SPECIAL_COMPLETE_NEST_ON=0b00010000,
                    IO_8259A::ICW4_COMMON_COMPLETE_NEST_OFF=0b0,
                    IO_8259A::ICW4_BUFFER_ON=0b00001000,
                    IO_8259A::ICW4_NONBUFFER_OFF=0b0,
                    IO_8259A::ICW4_AUTO_END_ON=0b00000010,
                    IO_8259A::ICW4_EOI_OFF=0b0,
                    IO_8259A::ICW4_FOR_80x86_ON=0b00000001,
                    IO_8259A::ICW4_FOR_MCS_OFF=0b0
                    IO_8259A::ICW4_BASE_ON=0b0,
                    IO_8259A::ICW4_BASE_OFF=0b00011111;

const unsigned int 	IO_8259A::OCW2_EOI_COMPLETE_NEST=0x20,
                    IO_8259A::OCW2_BASE_ON=0b0,
                    IO_8259A::OCW2_BASE_OFF=0b11100111;
#endif

const int IO_8259A::PORTS[4]={0x20,0xA0,0x21,0xA1};


IO_8259A::IO_8259A()
{

}

IO_8259A::~IO_8259A()
{

}
void IO_8259A::sendICW1(int chip,int electTriggerMode,int singleChip,int requireICW4)
{
    
    __asm__ __volatile__(
    "outb %%al,%%dx \n\t"
    :
    :"a"(0x10 | 
        ((electTriggerMode & 0x1) << 3) |
        ((singleChip & 0x1) << 1) |
        ((requireICW4 & 0x1))),
     "d"(IO_8259A::PORTS[chip])
    :
    );
}
void IO_8259A::sendICW2(int chip,int base)
{
    
        __asm__ __volatile__(
    "outb %%al,%%dx \n\t"
    :
    :"a"(base),
     "d"(IO_8259A::PORTS[chip+2])
    :
    );
}
void IO_8259A::sendICW3(int chip,int linkage)
{
    
    __asm__ __volatile__(
    "outb %%al,%%dx \n\t"
    :
    :"a"(linkage),
     "d"(IO_8259A::PORTS[chip+2])
    :
    );    
}
void IO_8259A::sendICW4(int chip,int specCompNest,int buf,int autoEndEOI,int useFor80x86)
{
    
    __asm__ __volatile__(
    "outb %%al,%%dx \n\t"
    :
    :"a"(((specCompNest & 0x1) << 4) |
        ((buf & 0x1) << 3) |
        ((autoEndEOI & 0x1) << 1)|
        ((useFor80x86 & 0x1))),
     "d"(IO_8259A::PORTS[chip+2])
    :
    );   
}
void IO_8259A::sendOCW1(int chip,int mask)
{
    __asm__ __volatile__(
    "outb %%al,%%dx \n\t"
    :
    :"a"(mask),
     "d"(IO_8259A::PORTS[chip+2])
    :
    );    
}
void IO_8259A::sendOCW2(int chip,int eoi)
{
    __asm__ __volatile__(
    "outb %%al,%%dx \n\t"
    :
    :"a"(eoi & 0b11100111),//D3,D4恒为0
     "d"(IO_8259A::PORTS[chip])
    :
    );    
}
const int IO_8253::PORTS[4]={0x40,0x41,0x42,0x43};
const unsigned int IO_8253::MAXNUM=1193180; 
const unsigned int IO_8253::MAX_MICRO=3599;
IO_8253::IO_8253()
{
    
    
}
IO_8253::~IO_8253()
{
    
    
}    
void IO_8253::setTimeMill(int tunel,unsigned int millsecs)
{
    int count = IO_8253::MAXNUM/1000 * millsecs;
    //int count=11930;-->10ms
    this->sendControlByte(0,0b11,0x3,0);
    Util::outb(IO_8253::PORTS[tunel],count);
    Util::outb(IO_8253::PORTS[tunel],count >> 8);
}
void IO_8253::setTimeMicro(int tunel,unsigned int microsecs)
{
    if(microsecs > IO_8253::MAX_MICRO)
    {
        microsecs = IO_8253::MAX_MICRO;
    }
    unsigned int count = IO_8253::MAXNUM * microsecs / 1000000;
    this->sendControlByte(0,0b11,0x3,0);
    Util::outb(IO_8253::PORTS[tunel],count);
    Util::outb(IO_8253::PORTS[tunel],count >> 8);
 }
void IO_8253::sendControlByte(int tunel,int writeOrder,int workingMode,int BCDMode)
{
    Util::outb(IO_8253::PORTS[3],
                    ((tunel & 0b11) << 6) |
                    ((writeOrder & 0b11) << 4) |
                    ((workingMode & 0b111) << 1) |
                    (BCDMode & 0b1));
}

//=========class: Keyboard

//规则： 1个字符的为可切换的字符，shift可以施加作用
//			即 s[1]=0 则为单字符
//		2个字符以上为控制字符
// 长度至少为1
const char* Keyboard::KEY_MAP_STD[]={
    "UNUSED","ESC",
	"1",		"2",			"3",      "4",   "5",  "6",  "7",       "8",    "9",   "0",
	"-",		"=",			"BS",     "TAB", "q",  "w",  "e",       "r",    "t",    "y",
	"u",		"i",			"o",      "p",  "[",  "]",  "Enter",   "CTRL", "a",    "s",
	"d",		"f",			"g",       "h",  "j",  "k",  "l",       ";",    "'",    "`",
	"LSHFT",	"\\",			"z",  	  "x",  "c",  "v",  "b",       "n",    "m",    ",",
	".",      "/",  "RSHFT","*","ALT"," ","CAP","F1","F2","F3","F4","F5","F6",
    "F7","F8","F9","F10","NUML","CtrlBreak","Home","Up","PgUp","-","Left","Center","Right","+","End","Down","PgDn",
	"Ins","Del","Unknown","Unknown","Unknown","F11","F12","Unkown","Unknown","Windows","Unknown","Menu",
	"RESERVED","RESERVED", "RESERVED","RESERVED","RESERVED",
	"RESERVED","RESERVED","RESERVED","RESERVED","RESERVED" ,//10RESERVED
	"RightALT","RigthCTRL"
};
const char  Keyboard::KEY_MAP_SHIFT[]={
	    '\0','\0',
		'!',		'@',			'#',      '$',   '%', '^','&','*','(',')',
		'_',		'+',			'0',     '0', 'Q',  'W',  'E',       'R',    'T',    'Y',
		'U',		'I',			'O',      'P',  '{',  '}',  '\0',   '\0', 'A', 'S',
		'D',		'F',			'G',     'H',  'J',  'K',  'L',       ':',    '"',    '~',
		'\0',	'|',			'Z',  'X', 'C',  'V',  'B',       'N',    'M',    '<',
		'>',      '?',  '\0','\0'/* 为*，但是找不到 */,'\0',' ','\0','\0','\0','\0','\0','\0','\0',
	    '\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0',
		'\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0',
		'\0','\0', '\0','\0','\0',
		'\0','\0','\0','\0','\0' ,//10RESERVED
		'\0','\0'
};



/**
 *   for(int i=0;i<KEY_MAP_STD_LEN;++i)
 *      cout << i << ":"<< KEY_MAP_STD[i] << endl;
 *   打印查看每个元素的下标
 */
//e0 x e0 x -- up down left right  _  表示需要接受两个e0
//长按无用
const int Keyboard::KEY_MAP_STD_LEN=sizeof(Keyboard::KEY_MAP_STD)/sizeof(char*);
const int		Keyboard::RIGHT_CTRL_INDEX = KEY_MAP_STD_LEN - 1,
				Keyboard::RIGHT_ALT_INDEX = KEY_MAP_STD_LEN - 2
				;

Keyboard::Keyboard()
{
    
    
}

Keyboard::~Keyboard(){
    
}
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
void Keyboard::waitToWrite()
{
    while(this->isBusy());
}
const char* Keyboard::getAsciiChar(unsigned char code)
{
    if(code<=Keyboard::KEY_MAP_STD_LEN)
        return Keyboard::KEY_MAP_STD[code];
    else
        return "Exceed.";
}
/**
 * 你看到一个非常Lisp的表达式，
 */
int Keyboard::getCodeTypeBit(u8_t  code)
{
#define selectEqual(which,i,another) ((code)==(which) ? (i):(another))

	return selectEqual(LEFT_SHIFT_INDEX,0,
				selectEqual(LEFT_CTRL_INDEX,1,
					selectEqual(LEFT_ALT_INDEX,2,
							selectEqual(RIGHT_SHITF_INDEX,3,
									selectEqual(RIGHT_CTRL_INDEX,4,
											selectEqual(RIGHT_ALT_INDEX,5,
													selectEqual(CAP_INDEX,6,
															selectEqual(NUM_INDEX,7,-1))))))));
}
int Keyboard::interpretCharData(u16_t data)
{
	bool hasCtrl = data & (CONTROL_LCTRL | CONTROL_RCTRL);
	bool hasShift = data & (CONTROL_LSHIFT | CONTROL_RSHIFT);
	bool hasCap = data & CONTROL_CAP;
	enum{
		TYPE_ALPHA,TYPE_NUM,TYPE_PUNCT,TYPE_POS,TYPE_CANNOT_HANDLE,
	};
	int type = TYPE_CANNOT_HANDLE;
	u8_t code=(u8_t)data;

	const char *chstr=KEY_MAP_STD[code];

	char ch;
	if(*(chstr+1)=='\0')//是单个字符
	{
		ch=chstr[0];
		if(ch >= 'a' && ch <='z')
			type=TYPE_ALPHA;
		else if(ch >= '0' && ch <='9')
			type=TYPE_NUM;
		else
			type=TYPE_PUNCT;
	}else if(code == ENTER_INDEX){
		ch='\n';
		type=TYPE_POS;
	}
	else if(code==BACKSPACE_INDEX){
		ch='\b';
		type=TYPE_POS;
	}
	else if(code == TAB_INDEX){
		ch='\t';
		type=TYPE_POS;
	}
	else
		type=TYPE_CANNOT_HANDLE;
//	int x=Kernel::printer->getX();
//	int y=Kernel::printer->getY();
//	Kernel::printer->putsz("\n");
//	Kernel::printer->puti("hasCap=",hasCap,",");
//	Kernel::printer->puti("hasCtrl=",hasCtrl,",");
//	Kernel::printer->puti("ch=",ch,",");
//	Kernel::printer->puti("type=",type,",");
//	Kernel::printer->putsz("\n");
//	Kernel::printer->setPos(x, y);
	if(type == TYPE_ALPHA)
	{
		if( ((!hasShift) && hasCap)||
				(hasShift && (!hasCap))  )
		{
			ch += 'A'-'a';
		}
		return ch;
	}else if(type==TYPE_NUM || type==TYPE_PUNCT)
	{
		if(!hasShift)return ch;
		else	return KEY_MAP_SHIFT[code];
	}
	else if(type==TYPE_POS)
		return ch;
	else
		return Kernel::EOF;
}

#endif //CODE32

#if defined(CODE32)||defined(CODE16)
IO_HDD::IO_HDD(int hddNo,size_t secStart,unsigned char secNumber,int dstSeg,size_t dstOff) :
hddNo(hddNo),LBAMode(true),secStart(secStart),secNumber(secNumber),dstSeg(dstSeg),dstOff(dstOff)
{
}
IO_HDD::IO_HDD() :
LBAMode(true)
{
}

IO_HDD::~IO_HDD() {
}

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


void  IO_HDD::read()
{
	this->writeSecNum();
	this->writeSecStart();
	this->requestRead();
	this->waitUntilReady();
	this->readData();
}

void IO_HDD::write()
{
	this->writeSecNum();
	this->writeSecStart();
	this->requestWrite();
	this->waitUntilReady();
	this->writeData();
}


void IO_HDD::readData()
{
	int temp;
	Util::enterEs(this->dstSeg, temp);
	__asm__ __volatile__(
			"cld;rep;insw\n\t"
			:
			:"d"(PORT_DATA),"D"(this->dstOff),"c"(this->secNumber * 512/2)
			:
	);
	Util::leaveEs(temp);
}

/**
 * Only when the buffer is full,data will be transfered to disk
 */
void IO_HDD::writeData()
{
//	int temp;
//	Util::printStr("writting2 \n");
//	Util::printStr((char*)this->dstOff);
//	Util::printStr("\n");

	//Utilisation,from Linux 0.11
	if(this->dstSeg!=Util::SEG_CURRENT)
	{
		__asm__ __volatile__(
				"push %%ds \n\t"
				"movw %%ax,%%ds \n\t"
				"cld;rep;outsw\n\t"
				"pop %%ds \n\t"
				:
				:"a"(this->dstSeg),"d"(This::PORT_DATA),"S"(this->dstOff),"c"(this->secNumber * 512/2)
				 :
		);
	}else{
		__asm__ __volatile__(
				"cld;rep;outsw\n\t"
				:
				:"d"(This::PORT_DATA),"S"(this->dstOff),"c"(this->secNumber * 512/2)
				 :
		);
	}

//
//	for(unsigned char i=0;i<this->secNumber;i++)
//	{
//		for(int j=0;j < 512;j+=2)
//		{
//			Util::outw(This::PORT_DATA,*(short*)(this->dstOff + i*512 + j));
//		}
//		this->waitUntilReady();
//	}

}

#endif //CODE32||CODE16
