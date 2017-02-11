
#ifndef __libx2__
#define __libx2__

//静态工具类
class Util{
    
    
public:
    Util();
    ~Util();
    //*****兼容：16位，32位*******
    const static int SEG_CURRENT;//SEG_CURRENT = 0x10000指向当前ds
    static int x,y;
    static int videoSelector;
    static void printStr(const char* str_addr,int mode=0x7);
    static void printChar(char ch,int mode=0x7);//0x7:White_Black_NoFlash
    static void setCursor(int x,int y); //25 * 80
    static void newLine();
    static void insertMark(int marker=0x1234);//插入一个语句 mov $,%eax
 
    static int get(int seg,int off);//seg=0x10000指向当前ds
    static void setb(int seg,int off,int byte);
    static void setw(int seg,int off,int halfWord);
    static void setl(int seg,int off,int word);
        
    /**
     * copy by byte
     */
    static void memcopy(int srcSeg,int srcOff,int dstSeg,int dstOff,int len);
    
    //===========仅16位=============
    /**
     *if error,return 0
     *else return 1
    */
    static int readSectors(int dstSeg,int dstOff,int driver,int head,int cylinder,int startSec,int numSecs);
    
    
    void test();
    
};
#endif