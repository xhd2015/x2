#ifdef CODE32
__asm__(".code32 \n\t");

#include <interrupts.h>
#include <libx2.h>
#include <IOProgramer.h>
#include <def.h>
#include <Kernel.h>

#include <macros/all.h>

void (*__intAddresses[])() ={
     int0x0,
     int0x1,
     int0x2,
     int0x3,
     int0x4,
     int0x5,
     int0x6,
     int0x7,
     int0x8,
     int0x9, //---- 10
    
     int0xa,
     int0xb,
     int0xc,
     int0xd,
     int0xe,
     int0xf,
     int0x10,
     int0x11,
     int0x12,
     int0x13,//---- 20
    
    
     int0x14,
     int0x15,
     int0x16,
     int0x17,
     int0x18,
     int0x19,
     int0x1a,
     int0x1b,
     int0x1c,
     int0x1d,//---- 30
    
     int0x1e,
     int0x1f,//---- 32
    
    
     0,//单独设置
     0,
     intDefault,
     intDefault,
     int0x24,
     int0x25,
	 intDefault,
	 int0x27, // 0x27 --- 40

	 intDefault,
	 intDefault,
	 intDefault,
	 intDefault,
	 intDefault,
	 intDefault,
	 intDefault,
	 intDefault,  // 0x2f

	 0 /*GPUI*/

 };
int *intAddresses=(int*)__intAddresses;
int intLen=sizeof(__intAddresses)/sizeof(int);
//===============中断处理程序：0============
/**
*不需要参数
*/
void int0x0()
{
    __asm__("leave \n\t");
    JMP_DIE();
    int sel=Util::makeSel(3);
    ENTER_DS(sel,s);
    Util::printStr("int 0x0:#DE\n");
    LEAVE_DS(sel,s);
    __asm__("leave \n\t");
    JMP_DIE();
    INTRETURN();
}
//============================================
//===============中断处理程序：1============
/**
*不需要参数
*/
void int0x1()
{
    __asm__("leave \n\t");
    JMP_DIE();
    int sel=Util::makeSel(3);
    ENTER_DS(sel,s);
    Util::printStr("int 0x1:Trap exception\n");
    LEAVE_DS(sel,s);
    INTRETURN();
}
//============================================
//===============中断处理程序：2============
/**
*不需要参数
*/
void int0x2()
{
    __asm__("leave \n\t");
    JMP_DIE();
    int sel=Util::makeSel(3);
    ENTER_DS(sel,s);
    Util::printStr("int 0x2.\n");
    LEAVE_DS(sel,s);
    INTRETURN();
}
//============================================
//===============中断处理程序：3============
/**
*不需要参数
*/
void int0x3()
{
    __asm__("leave \n\t");
    JMP_DIE();
    int sel=Util::makeSel(3);
    ENTER_DS(sel,s);
    Util::printStr("int 0x3.\n");
    LEAVE_DS(sel,s);
    INTRETURN();
}
//============================================
//===============中断处理程序：4============
/**
*不需要参数
*/
void int0x4()
{
    __asm__("leave \n\t");
    JMP_DIE();
    int sel=Util::makeSel(3);
    ENTER_DS(sel,s);
    Util::printStr("int 0x4.\n");
    LEAVE_DS(sel,s);
    INTRETURN();
}
//============================================
//===============中断处理程序：5============
/**
*不需要参数
*/
void int0x5()
{
    __asm__("leave \n\t");
    JMP_DIE();
    int sel=Util::makeSel(3);
    ENTER_DS(sel,s);
    Util::printStr("int 0x5.\n");
    LEAVE_DS(sel,s);
    INTRETURN();
}
//============================================
//===============中断处理程序：6============
/**
*不需要参数
*/
void int0x6()
{
    __asm__("leave \n\t");
    JMP_DIE();
    int sel=Util::makeSel(3);
    ENTER_DS(sel,s);
    Util::printStr("int 0x6.\n");
    LEAVE_DS(sel,s);
    INTRETURN();
}
//============================================

//===============中断处理程序：7============
/**
*不需要参数
*/
void int0x7()
{
    __asm__("leave \n\t");
    JMP_DIE();
    int sel=Util::makeSel(3);
    ENTER_DS(sel,s);
    Util::printStr("int 0x7.\n");
    LEAVE_DS(sel,s);
    INTRETURN();
}
//============================================
//===============中断处理程序：8============
/**
*不需要参数
*/
void int0x8()
{
    __asm__("leave \n\t");
    JMP_DIE();
    int sel=Util::makeSel(3);
    ENTER_DS(sel,s);
    Util::printStr("int 0x9.\n");
    LEAVE_DS(sel,s);
    INTRETURN();
}
//============================================
//===============中断处理程序：9============
/**
*不需要参数
*/
void int0x9()
{
    __asm__("leave \n\t");
    JMP_DIE();
    int sel=Util::makeSel(3);
    ENTER_DS(sel,s);
    Util::printStr("int 0x9.\n");
    LEAVE_DS(sel,s);
    INTRETURN();
}
//============================================
//===============中断处理程序：10============
/**
*不需要参数
*/
void int0xa()
{
    __asm__("leave \n\t");
    JMP_DIE();
	__asm__("leave \n\t");
	Util::jmpDie();
    int sel=Util::makeSel(3);
    ENTER_DS(sel,s);
    Util::printStr("int 0xa.\n");
    LEAVE_DS(sel,s);
    INTRETURN();
}
//============================================
//===============中断处理程序：11============
/**
*不需要参数
*/
void int0xb()
{
    __asm__("leave \n\t");
    JMP_DIE();
    int sel=Util::makeSel(3);
    ENTER_DS(sel,s);
    Util::printStr("int 0xb.\n");
    LEAVE_DS(sel,s);
    INTRETURN();
}
//============================================
//===============中断处理程序：12============
/**
*不需要参数
*/
void int0xc()
{
    __asm__("leave \n\t");
    JMP_DIE();
    int sel=Util::makeSel(3);
    ENTER_DS(sel,s);
    Util::printStr("int 0xc.\n");
    LEAVE_DS(sel,s);
    INTRETURN();
}
//============================================
//===============中断处理程序：13============
/**
*不需要参数
*
*Segment Error
*/
void int0xd()
{
    __asm__("leave \n\t");
    Util::jmpDie();
    int eax,ebx,ecx,esp;
    __asm__ __volatile__(
    "mov %%esp,%%edx \n\t"
    :"=a"(eax),"=b"(ebx),"=c"(ecx),"=d"(esp)
    :
    :
    );
    int sel=Util::makeSel(3);
    ENTER_DS(sel,s);
    Util::printStr("int 0xd:#GP\n");
    LEAVE_DS(sel,s);
    JMP_DIE();
    __asm__("iret \n\t");
}
//============================================
//===============中断处理程序：14============
/**
*不需要参数
*/
void int0xe()
{
    __asm__("leave \n\t");
    JMP_DIE();
    int sel=Util::makeSel(3);
    ENTER_DS(sel,s);
    Util::printStr("int 0xe.\n");
    LEAVE_DS(sel,s);
    INTRETURN();
}
//============================================
//===============中断处理程序：15============
/**
*不需要参数
*/
void int0xf()
{
    __asm__("leave \n\t");
    JMP_DIE();
    int sel=Util::makeSel(3);
    ENTER_DS(sel,s);
    Util::printStr("int 0xf.\n");
    LEAVE_DS(sel,s);
    INTRETURN();
}
//============================================
//===============中断处理程序：16============
/**
*不需要参数
*/
void int0x10()
{
    __asm__("leave \n\t");
    JMP_DIE();
    int sel=Util::makeSel(3);
    ENTER_DS(sel,s);
    Util::printStr("int 0x10.\n");
    LEAVE_DS(sel,s);
    INTRETURN();
}
//============================================
//===============中断处理程序：17============
/**
*不需要参数
*/
void int0x11()
{
    __asm__("leave \n\t");
    JMP_DIE();
    int sel=Util::makeSel(3);
    ENTER_DS(sel,s);
    Util::printStr("int 0x11.\n");
    LEAVE_DS(sel,s);
    INTRETURN();
}
//============================================
//===============中断处理程序：18============
/**
*不需要参数
*/
void int0x12()
{
    __asm__("leave \n\t");
    JMP_DIE();
    int sel=Util::makeSel(3);
    ENTER_DS(sel,s);
    Util::printStr("int 0x12.\n");
    LEAVE_DS(sel,s);
    INTRETURN();
}
//============================================
//===============中断处理程序：19============
/**
*不需要参数
*/
void int0x13()
{
    __asm__("leave \n\t");
    JMP_DIE();
    int sel=Util::makeSel(3);
    ENTER_DS(sel,s);
    Util::printStr("int 0x13.\n");
    LEAVE_DS(sel,s);
    INTRETURN();
}
//============================================
//===============中断处理程序：20============
/**
*不需要参数
*/
void int0x14()
{
    __asm__("leave \n\t");
    JMP_DIE();
    int sel=Util::makeSel(3);
    ENTER_DS(sel,s);
    Util::printStr("int 0x14.\n");
    LEAVE_DS(sel,s);
    INTRETURN();
}
//============================================
//===============中断处理程序：21============
/**
*不需要参数
*/
void int0x15()
{
    __asm__("leave \n\t");
    JMP_DIE();
    int sel=Util::makeSel(3);
    ENTER_DS(sel,s);
    Util::printStr("int 0x15.\n");
    LEAVE_DS(sel,s);
    INTRETURN();
}
//============================================
//===============中断处理程序：22============
/**
*不需要参数
*/
void int0x16()
{
    __asm__("leave \n\t");
    JMP_DIE();
    int sel=Util::makeSel(3);
    ENTER_DS(sel,s);
    Util::printStr("int 0x16.\n");
    LEAVE_DS(sel,s);
    INTRETURN();
}
//============================================
//===============中断处理程序：23============
/**
*不需要参数
*/
void int0x17()
{
    __asm__("leave \n\t");
    JMP_DIE();
    int sel=Util::makeSel(3);
    ENTER_DS(sel,s);
    Util::printStr("int 0x17.\n");
    LEAVE_DS(sel,s);
    INTRETURN();
}
//============================================
//===============中断处理程序：24============
/**
*不需要参数
*/
void int0x18()
{
    __asm__("leave \n\t");
    JMP_DIE();
    int sel=Util::makeSel(3);
    ENTER_DS(sel,s);
    Util::printStr("int 0x18.\n");
    LEAVE_DS(sel,s);
    INTRETURN();
}
//============================================
//===============中断处理程序：25============
/**
*不需要参数
*/
void int0x19()
{
    __asm__("leave \n\t");
    JMP_DIE();
    int sel=Util::makeSel(3);
    ENTER_DS(sel,s);
    Util::printStr("int 0x19.\n");
    LEAVE_DS(sel,s);
    INTRETURN();
}
//============================================
//===============中断处理程序：26============
/**
*不需要参数
*/
void int0x1a()
{
    __asm__("leave \n\t");
    JMP_DIE();
    int sel=Util::makeSel(3);
    ENTER_DS(sel,s);
    Util::printStr("int 0x1a.\n");
    LEAVE_DS(sel,s);
    INTRETURN();
}
//============================================
//===============中断处理程序：27=============
/**
*不需要参数
*/
void int0x1b()
{
    __asm__("leave \n\t");
    JMP_DIE();
    int sel=Util::makeSel(3);
    ENTER_DS(sel,s);
    Util::printStr("int 0x1b.\n");
    LEAVE_DS(sel,s);
    INTRETURN();
}
//=============================================
//===============中断处理程序：28=============
/**
*不需要参数
*/
void int0x1c()
{
    __asm__("leave \n\t");
    JMP_DIE();
    int sel=Util::makeSel(3);
    ENTER_DS(sel,s);
    Util::printStr("int 0x1c.\n");
    LEAVE_DS(sel,s);
    INTRETURN();
}
//=============================================
//===============中断处理程序：29=============
/**
*不需要参数
*/
void int0x1d()
{
    __asm__("leave \n\t");
    JMP_DIE();
    int sel=Util::makeSel(3);
    ENTER_DS(sel,s);
    Util::printStr("int 0x1d.\n");
    LEAVE_DS(sel,s);
    INTRETURN();
}
//=============================================
//===============中断处理程序：30=============
/**
*不需要参数
*/
void int0x1e()
{
    __asm__("leave \n\t");
    JMP_DIE();
    int sel=Util::makeSel(3);
    ENTER_DS(sel,s);
    Util::printStr("int 0x1e.\n");
    LEAVE_DS(sel,s);
    INTRETURN();
}
//=============================================
//===============中断处理程序：31=============
/**
*不需要参数
*/
void int0x1f()
{
    __asm__("leave \n\t");
    JMP_DIE();
    int sel=Util::makeSel(3);
    ENTER_DS(sel,s);
    Util::printStr("int 0x1f.\n");
    LEAVE_DS(sel,s);
    INTRETURN();
}
//=============================================

//=================中断处理程序: 32=========
namespace Int_0x20{
    int current=0;
    //GDT[5] -- task0
    //GDT[9] -- task1
}
__asm__(
".text \n\t"  //如果是第一个函数，就要将其汇编进入.text中
".global _int0x20 \n\t"
"_int0x20:\n\t "
"pusha \n\t"
"push  %ds\n\t"
"mov $0x18,%eax\n\t"
"mov %eax,%ds\n\t"
);
/**
 * I may propose some questions:
 * 		1.during switch process, a timer interrupt happens
 *
 *
 */
void _int0x20()  //保护现场只能发生在堆栈框架之前，所以编写中断有所不同
{
    //CALL_INT_3(0x24,c,SEG_CURRENT,b,"int 0x20.\n",d,Util::MODE_COMMON);
//	Util::printStr("int 0x20 start\n");
    IO_8259A p1;
    p1.sendOCW2(0,0x20);
    Kernel::getTheKernel()->switchNextProcess();
//    Util::printStr("int 0x20 end \n");
//    if(Int_0x20::current==0)
//    {
//        Int_0x20::current=1;
//        __asm__("ljmp $0b1001000,$0 \n\t");
//    }else{
//        Int_0x20::current=0;
//        __asm__("ljmp $0b101000,$0 \n\t");
//    }

    __asm__(
    "leave \n\t"
    "pop %ds \n\t"
    "popa \n\t"
    "iret \n\t"
    );
}
//==========================================

//=================中断处理程序: 33=========
/**
*键盘中断,直到发送EOI，键盘中断都不会再响应，在这之前处理是安全的。
*
*/
__asm__(
".text \n\t"  //如果是第一个函数，就要将其汇编进入.text中
".global _int0x21 \n\t"
"_int0x21:\n\t "
"pusha \n\t"
);
void _int0x21()
{
    static int times=0;
    static int lastx=0,lasty=0;
    static char save[10]={0};
    static unsigned char lasts[4];
    static unsigned int index=-1;
    Keyboard k;
    
    
    Printer p(10,0,8,80);
    p.setPos(lastx,lasty);
    /*
    times++;
    p.putsz("int 0x21:");
    Util::digitToStr(save,sizeof(save),times);
    p.putsz(save);
    p.putc('\n');
    */
    
    unsigned char code=k.readScanCode();
    
    //==fordebug
    
    
    Util::digitToStr(save,x2sizeof(save),code);
   
    if((code & 0x80) == 0)
    { 
        p.putsz(save);
        p.putsz("->");
        p.putsz(k.getAsciiChar(code));
        p.putsz("  ");
    }else{
        if(code == 0xe1) //还需要接受两个，然后合成一个
        {
            
        }else if(code==0xe0){ //还需要接受一个
            
        }
        Util::digitToHex(save,x2sizeof(save),code);
        p.putsz(save);
        p.putsz("  ");
    }
    
   
    

    
    lastx=p.getX();
    lasty=p.getY();
    //允许键盘工作
    k.disable();
    k.enable(); //先禁止，再允许
    
    IO_8259A p1;
    p1.sendOCW2(0,0x20);
    __asm__(
    "leave \n\t"
    "popa \n\t"
    "iret \n\t"
    );
}
//==========================================
//============中断处理程序: 36============
/**
*打印字符串
*   dl     指定属性
*   ecx:ebx 指定要打印字符串地址，遇到0结束
*
*/
void int0x24()
{
    int dsSel,off,attr;
    __asm__ __volatile__(
    ""
    :"=c"(dsSel),"=b"(off),"=d"(attr)
    :
    :
    );

	int temp;
	__asm__ __volatile__(
		"mov  %%ds,%%ebx\n\t"
		"mov %%eax,%%ds\n\t"
			:"=b"(temp)
			:"a"(0x18)
			:

	);
    if(dsSel!=Util::SEG_CURRENT)
    	Util::setStrSel(dsSel);
    Util::printStr((const char*)off,attr);

    __asm__ __volatile__(
    		"mov %%eax,%%ds \n\t"
    		:
    		:"a"(temp)
			:
    );
    __asm__(
    "leave \n\t"
    "iret \n\t"
    );
}
//===================================================
//============中断处理程序: 37============
/**
*仅用于低特权级进行sti
*
*/
void int0x25()
{
    //ebp[0] = 原ebp
    //ebp[1] = 返回地址
    //
    //ebp[3] = 原eflags
    __asm__("pusha \n\t");
    __asm__(
        "mov 4*3(%ebp),%eax \n\t"
        "or $0x200,%eax \n\t"
        "mov %eax,4*3(%ebp) \n\t"
    );
    __asm__("popa \n\t");
    INTRETURN();
}
//===================================================



//============中断处理程序: 39============
/**
*仅用于低特权级进行sti
*
*/
void int0x27()
{
	__asm__("leave \n\t"
			"iret \n\t"
	);
//	int temp;
//	__asm__ __volatile__(
//		"mov  %%ds,%%ebx\n\t"
//		"mov $0x18,%%eax\n\t"
//		"mov %%eax,%%ds\n\t"
//			:"=b"(temp)
//			:
//			:"eax"
//	);
//	IO_8259A p1;
//    p1.sendOCW1(0,0xfc);//屏蔽一些中断,允许定时中断，键盘中断
//    p1.sendOCW1(1,0xff);
//    p1.IO_8259A::~IO_8259A();
////	__asm__("leave \n\t");
////	Util::jmpDie();
//	Util::insertMark(0x55527);
//
//	__asm__ __volatile__(
//			"mov %%eax,%%ds \n\t"
//			:
//			:"a"(temp)
//			:
//			);

}


//============中断处理程序: 42============
/**
* General Purposed User Interrupt
* 	The only interface that user process contact with kernel
*
* 	eax	--	main function index
* 		high 24 bits for main index
* 		low  8  bits for sub index
* 	ecx --	arguments	data segment
* 	ebx --  arguments	data pointer
* 	edx --	...
*
*/
__asm__(
".text \n\t"
".global _int0x30 \n\t"
"_int0x30: \n\t"
"push %edx \n\t"
"push %ds \n\t"

);
void _int0x30()
{
    int dsSel,off,mainIndex,subIndex;
    __asm__ __volatile__(
    "mov %%al,%2 \n\t"
    "shr $8,%%eax \n\t"
    "mov %%eax,%3 \n\t"
    :"=c"(dsSel),"=b"(off),"=m"(subIndex),"=m"(mainIndex)
    :
    :"eax"
    );
	__asm__ __volatile__(
		"mov %%eax,%%ds\n\t"
			:
			:"a"(Kernel::KERNEL_DS)
			:
	);

	if(mainIndex==Kernel::GPUI_MEM)
	{
		/**
		 *   processMM allocate
		 *
		 *   rule 1:
		 *   	if only 1 arg & 1 return
		 *   		ecx is used to store argument
		 *   		ebx is used to return result
		 */
		if(subIndex==Kernel::GPUI_MEM_NEW) // int new(size_t newsize)
		{

		}
	}

    __asm__(
    "leave \n\t"
    "pop %edx \n\t"
    "pop %ds \n\t"
    "iret \n\t"
    );
}
//===================================================


//===================================================

//===============中断处理程序：默认打印信息============
/**
*不需要参数
*/
void intDefault()
{
    int sel=Util::makeSel(3);
    int temp;
    Util::enterDs(sel,temp);
    Util::printStr("Default int process called.\n");
    Util::leaveDs(sel,temp);
    Util::intReturn();
}

//========================================================

//====================class : InterruptsManager
InterruptsManager::GENERAL_FUNC InterruptsManager::intAddresses[]={
    
};
unsigned int InterruptsManager::intLen = sizeof(intAddresses)/sizeof(InterruptsManager::GENERAL_FUNC);
InterruptsManager::InterruptsManager()
{
    
}

InterruptsManager::~InterruptsManager()
{
    
}

InterruptsManager::GENERAL_FUNC InterruptsManager::getIntAddr(unsigned int i)
{
    return NULL;
}
void InterruptsManager::setIntAddr(unsigned int i)
{
    
}

//====================end class:InterruptsManager

#endif
