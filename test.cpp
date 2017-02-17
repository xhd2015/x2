
#ifdef CODE32

#include "def.h"
#include "libx2.h"
#include "test.h"
#include "List.h"
#include "PMLoader.h"       //使用常数

Test::Test():
dbg(Printer(5,0,5,30))
{
    
    
}
Test::~Test()
{
    
    
}
void Test::testList()
{
    char save[10];
    dbg.putsz("Testing: List. \n");
    SimpleMemoryManager<ListNode<int> > smm(PMLoader::FREE_HEAP_START,sizeof(ListNode<int>)*100);
    
    ListNode<int>* node;
    

    LinkedList<int> list;
    node=smm.getNew();
    node->setData(5);  
     Util::digitToStr(save,sizeof(save),node->getData());
     dbg.putsz(save);
     dbg.putsz("\n");
    list.append(node);
    node=smm.getNew();
    node->setData(7);
    
    
    list.append(node);
    node=smm.getNew();
    node->setData(6);
    list.append(node);// 5 7 6
    
    dbg.putsz("size is:");
    
    Util::digitToStr(save,sizeof(save),list.getSize());
    dbg.putsz(save);
    dbg.putsz("\n");
    
    
    node=list.remove();
    Util::digitToStr(save,sizeof(save),node->getData());
    dbg.putsz(save);
    
    node=list.remove();
    Util::digitToStr(save,sizeof(save),node->getData());
    dbg.putsz(save);
    
    node=list.remove();
    Util::digitToStr(save,sizeof(save),node->getData());
    dbg.putsz(save);
    
    
    
    dbg.putsz("\nEnd.\n");
    
    
    
}
void Test::testQueue()
{
     dbg.putsz("Testing: Queue. \n");
    
    char save[10];
    unsigned char buf[100];
    Queue<unsigned char> q(buf,sizeof(buf));
    unsigned char p='a';
    q.add(p);
    q.add('b');
    q.add('v');
    Util::digitToStr(save,sizeof(save),q.size());
    dbg.putsz("Current size:");dbg.putsz(save);dbg.putc('\n');
    p=q.remove();
    dbg.putsz("Get : ");
    dbg.putc(p);
    p=q.remove();
    dbg.putc(p);
    p=q.remove();
    dbg.putc(p);
}
void Test::run()
{
    //testQueue();
    testList();
}

#endif