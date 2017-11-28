#ifndef __MemoryManager__
#define __MemoryManager__
/**
*类的实现：
*   大量使用链表这种结构
*   也使用树这种结构
*       资源的分配很适合使用树来描述
*       
*/
class MemoryManager{
public:
    MemoryManager(int start,int len);//以典型的内存描述建立管理器
    ~MemoryManager(); //当其撤销的时候，必须将子类移动到父类的子类中
    
    MemoryManager allocFree(,int start,int len); //从父级管理器衍生
    int withDrawToParent();                    //回收到父级管理器
    int getBase();
    int getFirstAVL();
    /*
        MemoryManager mm(34*512,0xffff);
        MemoryManager mmIDT,mmGDT;
        mm.allocFree(mmIDT,0,50*8); //base作为零基址
        mm.allocFree(mmGDT,50*8,100*8);
        
        
    */
protected:

private:

};
#endif