
#ifndef __PMLoder__
#define __PMLoder__
//实模式下的 “保护模式加载器”
//  设置 gdtr,idtr
// 启用A20
//  进入保护模式
class PMLoader{
public:
    int Driver,Head,Cylinder,SecStart,SecNum,CodeSeg,CodeOff;
public:
    PMLoader(int driver=0,int head=0,int cylinder=0,int secStart=1,int secNum=0,int codeSeg=0,int codeOff=0);//指定保护模式的代码区域： 1.磁盘区域:驱动器，c，h，s，数目  2.内存区域 段：偏移
    //一般而言，如果代码在同一个磁盘上，为保护模式预留12~20个扇区是足够测试用的。因此取值可以认为保护模式代码在第16个扇区
    ~PMLoader();
    /**
    *一般而言，计算机的A20是随开机自动启用的，这里仅仅是确保其被开启
    */
    void enableA20();
    
    /**
    *lidt paddr
    *at paddr: .word(length) .long(baseaddr).  baseaddr在高地址
    *相对于栈来说，较后面的参数在栈高地址
    */
    void setidtr(short len,int address);
    void setgdtr(short len,int address);
    
    //=======仅16位=======
#ifdef CODE16
    /**
    * 必须提供PROTECTED_SEL,PROTECTED_ENTRY的值
    * 或者必须将保护模式代码置于 0b10000:0 处开始
    */
    void enterProtected();
    void ajustProtectedCode();
    void mainProcess();
#endif
    
};
#endif