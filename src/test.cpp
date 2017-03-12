
#ifdef CODE32
__asm__(".code32\n\t");
#endif

#include <def.h>
#include <libx2.h>
#include <test.h>
#include <List.h>
#include <PMLoader.h>       //使用常数
#include <Memory.h>
#include <IOProgramer.h>

Test::Test():
dbg(Printer(5,40,15,30))
{
    
    
}
Test::~Test()
{
    
    
}
//void Test::dumpMemoryData(const MemoryDescriptor & data)
//{
//    static int count=0;
//    char buf[10];
//    Util::digitToStr(buf,10,count++);
//    Util::printStr(buf);
//    Util::printStr("-->");
//    Util::digitToStr(buf,10,data.getStart());
//    Util::printStr(buf);
//    Util::printStr(":");
//    Util::digitToStr(buf,10,data.getLimit());
//    Util::printStr(buf);
//    Util::printStr(":");
//    Util::digitToStr(buf,10,data.isAllocable());
//    Util::printStr(buf);
//    Util::printStr("\n");
//}
//void Test::dumpMemoryData(const int & data)
//{
//
//}
//void Test::dumpSMM( SimpleMemoryManager<TreeNode<MemoryDescriptor> > *smm)
//{
//    char buf[10];
//    Util::printStr("DUMP SMM: ");
//    Util::digitToStr(buf,10,smm->getLen());
//    Util::printStr(buf);Util::printStr(":");
//    Util::digitToStr(buf,10,smm->getCurSize());
//    Util::printStr(buf);Util::printStr(":");
//    Util::digitToStr(buf,10,smm->getLimit());
//    Util::printStr(buf);Util::printStr("\n");
//}
//void Test::dumpMM( MemoryManager<SimpleMemoryManager> &mm)
//{
//    char buf[10];
//    Util::printStr("Head: ");
//    if(mm.getHead())
//    {
//        Test::dumpMemoryData(mm.getHead()->getData());
//        int n=0;
//        TreeNode<MemoryDescriptor> *p=mm.getHead()->getSon();
//        while(p)
//        {
//            Util::digitToStr(buf,10,n++);
//            Util::printStr("NO_");
//            Util::printStr(buf);
//            Util::printStr(":");
//            Test::dumpMemoryData(p->getData());
//            p=(TreeNode<MemoryDescriptor>*)p->getNext();
//        }
//    }else{
//        Util::printStr("NULL \n");
//    }
//
//}
//DEVEL_AUTHOR(Doug)
//DEVEL_AUTHOR(TESTED)
//void Test::testMemory()
//{
//    dbg.putsz("Testing: Memory. \n");
//
//    SimpleMemoryManager<TreeNode<MemoryDescriptor> > smm(PMLoader::FREE_HEAP_START,sizeof(TreeNode<MemoryDescriptor>) * 40 ); //has bug,but to let it smaller makes things works
//    //***********test smm
//    // Test::dumpSMM(&smm);
//    // TreeNode<MemoryDescriptor> * p = smm.getNew();
//    // Test::dumpSMM(&smm);
//    // TreeNode<MemoryDescriptor> * x = smm.getNew();
//    // Test::dumpSMM(&smm);
//    // smm.withdraw(p);
//
//    //==============
//
//    Test::dumpSMM(&smm);
//    MemoryManager<SimpleMemoryManager> mm(&smm,0,0xfffff,0);//0~1MB,用于自身分配,模拟空间分配完毕的情况
//    Test::dumpSMM(&smm);
//   // Test::dumpMM(mm);
//
////    dbg.putsz("done init.\n");
//  // dumpMemoryData(mm.getHead()->getData());//OK
//
//    MemoryManager<SimpleMemoryManager> reserved=mm.allocFreeStart(0,PMLoader::CODE_START); //this is for preserved area
//        dbg.putsz("done init 1.\n");
//       // Test::dumpMM(mm);
//    MemoryManager<SimpleMemoryManager> code_area=mm.allocFreeStart(PMLoader::CODE_START,PMLoader::CODE_LIMIT/100);//for code
//    //now it's free to use all the left area
//    dbg.putsz("done allocFreeStart.\n");
//    //Test::dumpMM(mm);
//    int *a=(int*)mm.mnew(sizeof(int));
//   // Test::dumpMM(mm);
//     *a = 9;
//    Util::digitToStr(buf,sizeof(buf),(size_t)a);//addr
//    dbg.putsz(buf);dbg.putsz(":");
//
//    Util::digitToStr(buf,sizeof(buf),*a);
//    dbg.putsz(buf);dbg.putsz("\n");
//
//    int *b=(int*)mm.mnew(sizeof(int));
//    //Test::dumpMM(mm);
//     *b=20;
//    Util::digitToStr(buf,sizeof(buf),(size_t)b);//addr
//    dbg.putsz(buf);dbg.putsz(":");
//
//    Util::digitToStr(buf,sizeof(buf),*b);
//    dbg.putsz(buf);
//
//  Test::dumpMM(mm);
//
//    mm.mdelete(a,sizeof(*a));
//    mm.mdelete(b,sizeof(*b));
//
//   Test::dumpMM(mm);
//    reserved.withdrawToParent();
//    //Test::dumpMM(mm);
////    Test::dumpSMM(&smm);
//    code_area.withdrawToParent();
//    //last:
//    Test::dumpMM(mm);
//    mm.withdrawToParent();//撤销顶级管理器
//    Test::dumpMM(mm);
// //   Test::dumpSMM(&smm);
//    dbg.putsz("\n");
//
//    dbg.putsz("End .\n");
//
//}
//
void Test::testIO_HDD()
{
	dbg.putsz("in testing IO_HDD\n");
//	Util::jmpDie();
	size_t buflen=512;
	char *buf=(char*)PMLoader::FREE_HEAP_START;
	buf[0]='x';
	buf[1]='h';
	buf[2]='d';
	buf[3]=0;
	char *buf2=(char*)((size_t)buf+buflen);
	IO_HDD hdd(0,2,1,Util::SEG_CURRENT,(size_t)buf);
	hdd.write();

//	hdd.setSecStart(2);
//	hdd.setDstOff((size_t)buf2);
//	hdd.read();
//	dbg.putsz("original is :");
//	dbg.putsz(buf);
//	dbg.putsz("\n read after wirte is : ");
//	dbg.putsz(buf2);
//	dbg.putsz("\n");
	Util::jmpDie();

}
//void Test::testList()
//{
//    char save[10];
//    dbg.putsz("Testing: List. \n");
//    SimpleMemoryManager<ListNode<int> > smm(PMLoader::FREE_HEAP_START,sizeof(ListNode<int>)*100);
//
//    ListNode<int>* node;
//
//
//    LinkedList<int,SimpleMemoryManager> list(&smm);
//    node=list.append(5);
//     Util::digitToStr(save,sizeof(save),node->getData());
//     dbg.putsz(save);
//     dbg.putsz("\n");
//
//
//    list.append(7);
//    list.append(6);
//
//    dbg.putsz("size is:");
//
//    Util::digitToStr(save,sizeof(save),list.getSize());
//    dbg.putsz(save);
//    dbg.putsz("\n");
//
//
//    node=list.remove();
//    Util::digitToStr(save,sizeof(save),node->getData());
//    smm.withdraw(node);
//    dbg.putsz(save);
//
//    node=list.remove();
//    Util::digitToStr(save,sizeof(save),node->getData());
//    smm.withdraw(node);
//    dbg.putsz(save);
//
//    node=list.remove();
//    Util::digitToStr(save,sizeof(save),node->getData());
//    smm.withdraw(node);
//    dbg.putsz(save);
//
//
//    list.free();
//    Util::digitToStr(save,sizeof(save),smm.getCurSize());
//    dbg.putsz("\nFree:");
//    dbg.putsz(save);
//
//    dbg.putsz("\nEnd.\n");
//
//
//
//}
//void Test::testQueue()
//{
//     dbg.putsz("Testing: Queue. \n");
//
//    char save[10];
//    unsigned char buf[100];
//    Queue<unsigned char> q(buf,sizeof(buf));
//    unsigned char p='a';
//    q.add(p);
//    q.add('b');
//    q.add('v');
//    Util::digitToStr(save,sizeof(save),q.size());
//    dbg.putsz("Current size:");dbg.putsz(save);dbg.putc('\n');
//    p=q.remove();
//    dbg.putsz("Get : ");
//    dbg.putc(p);
//    p=q.remove();
//    dbg.putc(p);
//    p=q.remove();
//    dbg.putc(p);
//}
void Test::run()
{
    //testQueue();
    //testList();
    dbg.putsz("Test hook started.\n");
   // testMemory();
    this->testIO_HDD();
    dbg.putsz("Test hook ended\n");
}
