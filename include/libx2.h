
#ifndef libx2_h__
#define libx2_h__
#include <def.h>



#if defined(CODE16)
#pragma pack(push,1)
/**
 *  int 0x13扩展中断 0x42h等需要用到的数据结构
 */
class ExtendedInt0x13Info{
public:
	AS_MACRO ExtendedInt0x13Info(u16_t dstSeg,u16_t dstOff,u32_t lbaAddrLow,u16_t sectorNum,u32_t lbaAddrHigh=0);
	~ExtendedInt0x13Info()=default;

	enum{
		FUNC_42_READ_LBA=0x42,
		FUNC_43_WRITE_LBA=0x43
	};
public:
	const u8_t thisStructSize;//16
	const u8_t reserved;//0
	u16_t		sectorNum;
	u16_t		dstOff;
	u16_t		dstSeg;
	u32_t		lbaAddrLow;
	u32_t		lbaAddrHigh;
};
#pragma pack(pop)
#endif

//静态工具类
class Util{


public:
	static int printf(const char *fmt,...);
    Util();
    ~Util();

#if defined(CODE16) || defined(CODE32) || defined(CODE32USER)
    //*****兼容：16位，32位*******
    static int x,y;
#endif
    //ON用 |
    //OFF用 &
    enum {	MODE_FL_ON=0x80,
            MODE_FL_OFF=0x7f,
            MODE_BG_RED=0b0100000,
            MODE_BG_GREEN=0b0010000,
            MODE_BG_BLUE=0b0001000,
            MODE_BG_WHITE=0b0111000,
            MODE_BG_RG=0b0110000,
            MODE_BG_RB=0b0101000,
            MODE_BG_BG=0b0011000,
            MODE_BG_BLACK=0b0000000,
            MODE_FG_RED=0b0000100,
            MODE_FG_GREEN=0b0000010,
            MODE_FG_BLUE=0b0000001,
            MODE_FG_WHITE=0b0000111,
            MODE_FG_RG=0b0000110,
            MODE_FG_RB=0b0000101,
            MODE_FG_BG=0b0000011,
            MODE_FG_BLACK=0b0000000,
            MODE_COMMON=(MODE_FL_OFF & MODE_BG_BLACK) | MODE_FG_WHITE
    };
#if defined(CODE16)||defined(CODE32) || defined(CODE32USER)
//    const static int SCREEN_X,SCREEN_Y;
    enum{
    	SCREEN_X = 25,
		SCREEN_Y = 80
    };
#endif

    enum{SEG_CURRENT = 0x10000};
#if defined(CODE16) || defined(CODE32) //只有实模式，保护模式内核态才有全局选择子
    	enum{
			videoSelector=
#if defined(CODE16)
						0xb800
#elif defined(CODE32)
						0x8 //指向videoSelector
#endif
		//,END_ENUM
};
#endif
#if defined(CODE16)||defined(CODE32)
    // 指向选择子
    static int strSel;
    AS_MACRO static void	setStrSel(int sel);
    AS_MACRO static int  getStrSel();
#endif

    static void printStr(const char* str_addr,int mode=MODE_COMMON);
    static void printChar(char ch,int mode=MODE_COMMON);//0x7:White_Black_NoFlash
    static void setCursor(int x,int y); //25 * 80
    static void newLine();
    AS_MACRO static void insertMark(int marker=0x1234);//插入一个语句 mov $,%eax
 
    static int get(int seg,int off);//seg=0x10000指向当前ds
    static void setb(int seg,int off,int byte);

    /**
     *  set 2 bytes
     */
    static void setw(int seg,int off,int halfWord);
    /**
     *   set 4 bytes
     */
    static void setl(int seg,int off,int word);
    static void clr();
    AS_MACRO static void jmpDie();
    AS_MACRO static void jmp(int addr);
    /**
    *使0x92端口的位0从0变化成1从而重启计算机
    */
    AS_MACRO static void reboot();
    void test();
    /**
     * copy by byte
     *
     * from srcSeg:srcOff --> dstSeg:dstOff
     */
    static void memcopy(int srcSeg,int srcOff,int dstSeg,int dstOff,int len);
    /**
     * memcopy的inline版本
     */
    AS_MACRO static void memcopyInlineable(int srcSeg,int srcOff,int dstSeg,int dstOff,int len);

    //==========macros
    AS_MACRO static void cli();
    AS_MACRO static void sti();
    AS_MACRO static void enterDs(int seg,int& temp);
    AS_MACRO static void leaveDs(int seg,int temp);
    AS_MACRO static void enterEs(int seg,int& temp);
    AS_MACRO static void leaveEs(int temp);
    AS_MACRO static void outb(short port,char data);
    AS_MACRO static void outw(short port,short data);
    AS_MACRO static char inb(short port);
    AS_MACRO static short inw(short port);
    AS_MACRO static void ltr(int sel);
    AS_MACRO static void lldt(int sel);
    AS_MACRO static int	getCurrentDs();
    AS_MACRO static void setCurrentDs(int ds);
    AS_MACRO static int	getCurrentSs();
    AS_MACRO static void setCurrentSs(int ss);
    AS_MACRO static void ljmp(int newcs,int neweip);
    /**
     *  使用ljmp来跳转，eip照常增加
     *  只是相当于改变cs的内容，但是cs指向的地址不变
     *  用在32位模式下的虚拟内存映射
     *  也可用于16位模式下，将代码复制后，进行跳转的操作，必须以宏的形式实现
     *
     *  相当于:
     *  		ljmp %cs:$HERE
     *  		HERE:
     */
    AS_MACRO static void replaceCs(int newcs);

    /**
     *  一次性重置ss,ds,es指针
     *  注意：这是一个通常的任务，即ss,ds,es同时设置
     */
    AS_MACRO static void replaceSS_DS_ES(int newseg);

    //==================仅32位
public:
#if defined(CODE32)
    static void lidt(short len,int address);
    static void lgdt(short len,int address);
    
    //=============DEPRECATED===========
    DEPRECATED AS_MACRO static void pusha();//这些宏通常用于中断处理，但是由于在堆栈框架之内的任何栈操作都是错误的，因此将它们标记为过时的
    DEPRECATED AS_MACRO static void popa();
    
    /**
     * 创建一个指向LDT或者GDT的选择子
     *
     * @param index		表项的下标
     * @param dpl		权限
     * @param from		指向的表，0=GDT 1=LDT
     */
    static short makeSel(int index,int dpl=0b00,int from=0);
    
    static void changeCPL(int eip,int cs,int eflags,int esp,int ss);
    static int getEflags();
    static char getCPL();
    static char getDPL(int sel);
#endif //CODE32

#if defined(CODE32)||defined(CODE64)||defined(CODE16)||defined(CODE32USER)
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

    /**
     * 返回最小值
     * @param __SimpleType  必须是基本类型
     * @param t1 操作数
     * @param t2 操作数
     */
    template <typename __SimpleType>
    AS_MACRO static __SimpleType min(__SimpleType t1,__SimpleType t2);
    template <typename __SimpleType>
    AS_MACRO static __SimpleType max(__SimpleType t1,__SimpleType t2);
    
    //math related
    static int sign(int n);
#endif //CODE32 || CODE64 || CODE16 ||CODE32USER

#if defined(CODE32)
    //========与调用相关的宏
    /**
    *获取一个返回class类型的成员函数的返回对象的参数
    *如果不明确返回所声明的类型，g++是允许编译通过的。但是这样做可能是错误的（即什么都不返回）
    * DO NOT USE IT
    */
    DEPRECATED AS_MACRO static void initTarget(void** target);

    AS_MACRO static void intReturn();
#endif//CODE32

    
    
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
//private:
public:
    static int readSectorsCHS(int dstSeg,int dstOff,int driver,int cylinder,int head,int startSec,int numSecs);
    AS_MACRO static int readSectorsCHSInline(int dstSeg,int dstOff,int driver,int cylinder,int head,int startSec,int numSecs);
public:
    static int readSectors(int dstSeg,int dstOff,int driver,int LBAStart,int numSecs);
    /**
     * 调用该函数总是会生成一个宏，代码总会被插入到那里
     * 这主要用于16位模式的加载，调用int 0x13
     * @param dstSeg	目的段
     * @param dstOff	目的偏移
     * @param driver	存储器
     * 			0,1  floppy(0,1)
     * 			0x80,0x81 hard disk(0,1)
     * @param LBAStart  28位LBA其实地址
     * @param numSecs	读取扇区的个数
     *
     * 	注意：这个函数作为宏实现,为了节省空间，你可以使用readSectors()替代
     */
    AS_MACRO static int readSectorsInline(int dstSeg,int dstOff,int driver,int LBAStart,int numSecs);

    /**
     *
     * 使用扩展int13 0x42功能来读写LBA模式的磁盘
     * @return  是否有错误，1无错误 0有错误
     */
    AS_MACRO static int readSectorsExt(int driver,ExtendedInt0x13Info *info);
#endif

    
};


#if defined(CODE32) || defined(CODE32USER)
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
#if defined(CODE32) || defined(CODE32USER)
    void puti(const char* str,int i,const char* strAfter="\n");
    void putx(const char* str,int i,const char* strAfter="\n");
    void puti(const char* str,void * i,const char* strAfter="\n");
    void putx(const char* str,void * i,const char* strAfter="\n");
#endif
    void putsz(const char* str);
    void putsn(const char *str,int n);
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

/**
 * 通用的出错状态实现。
 *
 * 一次执行某种状态改变的函数之后，可能产生某些错误情况，可以从这里获取
 * 子类需要继承ErrorSaver，然后提供enum以ERROR_开头的定义，其中一项是ERROR_NOERR
 */
class ErrorSaver{
public:
	AS_MACRO ErrorSaver(int errno=0);
	AS_MACRO int getErrno()const;
protected:
	AS_MACRO void setErrno(int errno);
	int errno;
};

/**
 *  to insert a print information on class init
 */
class ClassDebug{
public:
	ClassDebug()=default;
	ClassDebug(const char *msg);
};
#endif //CODE32 || CODE32USER



#if defined(CODE32)||defined(CODE64)||defined(CODE32USER)

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
// EFF 考虑Queue存放其他结构时，最好使用const T&,存放简单结构时，使用T
template <typename T>
class Queue{
public:
	Queue()=default;//可能需要使用replacement new来重新初始化
    Queue(T p[],size_t len);//掌管指针
    ~Queue();
    
    T remove();
    int put(T t);

    AS_MACRO unsigned int size();
    AS_MACRO bool isEmpty();
    AS_MACRO bool isFull();
protected:
    T *p;
    unsigned int len;
    unsigned int curLen;
    int indexAdd,indexRemove;
};
#endif //CODE32 || CODE64 || CODE32USER




#endif //libx2_h__
