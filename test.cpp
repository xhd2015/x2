
#ifdef CODE32

#include "def.h"
#include "libx2.h"
#include "test.h"

Test::Test()
{
    
    
}
Test::~Test()
{
    
    
}
void Test::testQueue()
{
    Printer prt(5,0,5,30);
    
    char save[10];
    unsigned char buf[100];
    Queue<unsigned char> q(buf,sizeof(buf));
    unsigned char p='a';
    q.add(p);
    q.add('b');
    q.add('v');
    Util::digitToStr(save,sizeof(save),q.size());
    prt.putsz("Current size:");prt.putsz(save);prt.putc('\n');
    p=q.remove();
    prt.putsz("Get : ");
    prt.putc(p);
    p=q.remove();
    prt.putc(p);
    p=q.remove();
    prt.putc(p);
}
void Test::run()
{
    testQueue();
}

#endif