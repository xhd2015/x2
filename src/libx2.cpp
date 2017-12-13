



#include <libx2.h>
#include <def.h>
#include <Kernel.h>



#ifdef CODE16
    __asm__(".code16gcc \n\t");
#elif defined(CODE32) || defined(CODE32USER)
    __asm__(".code32 \n\t");
#endif

#if defined(CODE64) //模板实例化
#include <cstdio>
#include <cstdarg>

#endif
//==============模板实例化
//===在此声明实例化
#if defined(CODE32)
    template class Queue<unsigned char>;
    template class Queue<u16_t>;
#endif

int Util::printf(const char *fmt,...)
{
#if defined(CODE64)
	va_list ap;
	va_start(ap,fmt);
	int n=vprintf(fmt,ap);
	va_end(ap);
	return n;
#elif defined(CODE32) || defined(CODE16) || defined(CODE32USER)
	//I don't know what todo
	Util::printStr(fmt);
	return 0;
#endif
}

#if defined(CODE32)||defined(CODE16) || defined(CODE32USER)

int Util::x=0;
int Util::y=0;
//const int Util::SCREEN_X=25,Util::SCREEN_Y=80;

#if defined(CODE32)||defined(CODE16)
int		Util::strSel=0;
#endif

//const int Util::SEG_CURRENT =    0x10000;//运行期常数，有时我需要一个编译期常数,那就在g++的命令行中定义之-D
//int Util::videoSelector=
//#if defined(CODE16)
//    0xb800;
//#elif defined(CODE32)
//    0x8; //指向videoSelector
//#endif


Util::Util()
{
    Util::printStr(">>>Init");
    Util::newLine();    
}

Util::~Util()
{
    Util::printStr(">>>Destroy");
    Util::newLine();
}


void Util::test()
{
    Util::printStr(">>>test");
    Util::newLine();
}

void Util::printStr(const char* str_addr,int mode)
{
#if defined(CODE32)
//	 __asm__(
//	"mov $0x8,%ax \n\t"
//	"mov %ax,%ds\n\t"
//	"movb $120,0\n\t" //print 'x' in the screen
//	 );
//	Util::jmpDie(); //Very OK
#endif
#if defined(CODE32) || defined(CODE16)
	if(str_addr==nullptr)return;
	char ch;
//    while( (ch=(char)Util::get(Util::strSel,(int)str_addr++))!=0 )
	while( (ch=*str_addr++) != '\0')
    {
        Util::printChar(ch,mode);
    }
#endif
}
void Util::printChar(char ch,int mode)
{
#if defined(CODE32)
//	 __asm__ __volatile__(
//	""
////	"mov $0x8,%%ax \n\t"
////	"mov %%ax,%%ds\n\t"  //error
////	"movb $'h',0\n\t" //print 'x' in the screen
//	 :
////	 :"b"('x') //w is wroong,try x
//	 :);
//	Util::jmpDie(); //vbox OK
#endif
    if(ch == '\n')
    {
        Util::newLine();
        return;
    }else if(ch == '\r')
    {
        Util::y = 0;
        return;
    }else if(ch=='\b')
    {
        if(Util::y>0)
            Util::y--;
        return;
    }
    
    if(Util::y==80) //为了防止某些情况下两次newLine，比如打印完最后一个字符时。所以把这个移动到这里
    {
        Util::newLine();
    }
#if defined(CODE16)||defined(CODE32)
    int Lpos = Util::x * 80*2 + Util::y*2;//25 * 80
    Util::insertMark(0x21342134);
    __asm__ __volatile__(
		"push %%es\n\t"
		"mov %%dx,%%es\n\t" //视频缓冲区
		"movb %%al,%%es:(%%bx) \n\t"
		"inc %%ebx \n\t"
		"movb %%cl,%%es:(%%bx) \n\t"
		"pop %%es \n\t"
		:
		:"a"(ch),"b"(Lpos),"c"(mode),"d"(Util::videoSelector)
		:"memory"
    );

    Util::y ++;
#elif defined(CODE32USER)

#endif
    
}
void Util::newLine()
{
   
    Util::y = 0;
    Util::x = (Util::x+1)%25;
}

 int Util::get(int seg,int off)
 {
#if defined(CODE32)||defined(CODE16)
     ENTER_DS(seg,s);
     int rt;
     __asm__ __volatile__(
        "movl %%ds:(%%ebx),%%eax \n\t"
       :"=a"(rt)
       :"b"(off),"a"(seg)
       :
     );
    LEAVE_DS(seg,s);
     return rt;
#elif defined(CODE32USER)
     return 0;
#endif
 }
void Util::setb(int seg,int off,int byte)
{
#if defined(CODE32)||defined(CODE16)
    ENTER_DS(seg,s);
    __asm__ __volatile__(
        "movl 4+4*2(%%ebp),%%ebx \n\t"
        "movb 4+4*3(%%ebp),%%al \n\t"
        "movb %%al,%%ds:(%%ebx) \n\t"
        :
        :
        :"ebx","eax","memory"
    );
    LEAVE_DS(seg,s);
#elif defined(CODE32USER)
#endif
}
void Util::setw(int seg,int off,int halfWorld)
{
#if defined(CODE32)||defined(CODE16)
    ENTER_DS(seg,s);
    __asm__ __volatile__(
        "movl 4+4*2(%%ebp),%%ebx \n\t"
        "movw 4+4*3(%%ebp),%%ax \n\t"
        "movw %%ax,%%ds:(%%ebx) \n\t"
        :
        :
        :"ebx","eax","memory"
    );
    LEAVE_DS(seg,s);
#elif defined(CODE32USER)

#endif
}
void Util::setl(int seg,int off,int word)
{
    __asm__ __volatile__(
        "push %%ds \n\t"
    	"mov %%eax,%%ds \n\t"
        "mov %%ecx,%%ds:(%%ebx) \n\t"
    	"pop %%ds \n\t"
        :
        :"a"(seg),"b"(off),"c"(word)
        :"memory"
    );
}

void Util::memcopy(int srcSeg,int srcOff,int dstSeg,int dstOff,int len)
{   
	Util::memcopyInlineable(srcSeg, srcOff, dstSeg, dstOff, len);
}

void Util::clr()
{
#if defined(CODE32)
//	Util::jmpDie(); //vbox wrong
#endif
    Util::setCursor(0,0);
    for(int i=0;i!=Util::SCREEN_X;i++)
        for(int j=0;j!=Util::SCREEN_Y;j++)
            Util::printChar(' ');
    Util::setCursor(0,0);
}
void Util::setCursor(int x,int y)
{
    Util::x =x % Util::SCREEN_X;
    Util::y =y % Util::SCREEN_Y;
}
//======================仅32位=============
#if defined(CODE32)
short Util::makeSel(int index,int dpl,int from)
{
    return (short)(
        ((index & 0x1fff) << 3) | 
        ((from & 0x1) << 2) | 
        (dpl & 0b11)
        );
}
void Util::lidt(short len,int address)
{
        __asm__(
        "movw 4+4*1(%ebp),%ax \n\t"
        "movw %ax,4+4*1+2(%ebp) \n\t"
        "lidt 4+4*1+2(%ebp) \n\t"
    );
}
void Util::lgdt(short len,int address)
{
        __asm__(
        "movw 4+4*1(%ebp),%ax \n\t"
        "movw %ax,4+4*1+2(%ebp) \n\t"
        "lgdt 4+4*1+2(%ebp) \n\t"
    );
}
char Util::getCPL()
{
	char save;
   __asm__ __volatile__(
    "mov %%cs,%%ax \n\t"
    "and $0b11,%%al \n\t"
	:"=a"(save)
   );
   return save;
}
char Util::getDPL(int sel)
{
	return 0b11 & sel;
}
void Util::changeCPL(int eip,int cs,int eflags,int esp,int ss)
{
    __asm__(
      "add $4*2,%esp \n\t" //skip return addr & ebp
     "iret \n\t"
    );
}
int Util::getEflags()
{
	int save;
    __asm__ __volatile__(
     "pushfl \n\t"
     "popl %%eax \n\t"
    		:"=a"(save)
    );
    return save;
}

#endif //CODE32
#endif //CODE32 || CODE16


#if defined(CODE32)||defined(CODE64)||defined(CODE16)
int Util::digitToStr(char* save,unsigned int space,int n)
{
    int sign=1;
    unsigned int index=0;
    if(index==space)return 0;
    save[index]=0;//结束字符串
    index++;
    
    if(n<0)
    {
       n= -n;
       sign = -1;
    }
    if(n==0)
    {
        if(index==space)return 0;
        save[index]='0';
        index++;
    }else{
        while(n>0)
        {
            if(index==space)return 0;
            save[index]=n%10+'0';
            n/=10;
            index++;
        }
    }
    if(sign==-1)
    {
        if(index==space)return 0;
        save[index]='-';
        index++;
    }
    char temp;
    unsigned int i=0,j=index-1;
    while(i<j)
    {
        temp=save[i];
        save[i]=save[j];
        save[j]=temp;
        i++;
        j--;
    }
    return index;
}
int Util::digitToHex(char* save,unsigned int space,unsigned int n)
{
    unsigned int index=0;
    if(index==space)return 0;
    save[index]=0;//结束字符串
    index++;
    if(n==0)
    {
        if(index==space)return 0;
        save[index]='0';
        index++;
    }else{
        while(n>0)
        {
            if(index==space)return 0;
            int temp=n%16;
            if(temp<10)
            {
                save[index]=temp+'0';
            }else{
                save[index]=temp-10+'a';
            }
            n/=16;
            index++;
        }
        
    }
    char temp;
    int i=0,j=index-1;
    while(i<j)
    {
        temp=save[i];
        save[i]=save[j];
        save[j]=temp;
        i++;
        j--;
    }
    return index;
    
}
int Util::strcmp(const char* a,const char *b)
{
   int i=0;
   while( *(a+i) && *(b+i) && *(a+i)==*(b+i))i++;
   return *(a+i) - *(b+i);
}
int Util::strlen(const char *a)
{
    int i=0;
    while(*(a+i))i++;
    return i;
}
int Util::strcopy(const char *src,char *dst,int len)
{
    int i=0;
    while(i!=len - 1 && *(src+i))
    {
        *(dst+i)=*(src+i);
        i++;
    }
    *(dst+i)=0;
    return i;
}
int Util::sign(int n)
{
    if(n<0)return -1;
    if(n==0)return 0;
    return 1;
}

#endif //CODE32 || CODE64

#if defined(CODE32)
//=================class : SimpleCharRotator
const char SimpleCharRotator::rotateShapes[12]={'_','\b',0,'\\','\b',0,'|','\b',0,'/','\b',0};
SimpleCharRotator::SimpleCharRotator(int x,int y,int attr,int direction):
X(x),Y(y),Attr(attr),Status(0),Direction(direction)
{
    
}
SimpleCharRotator::~SimpleCharRotator()
{
    
}
void SimpleCharRotator::setPosition(int x,int y)
{
    this->X = x;
    this->Y = y;
}
void SimpleCharRotator::setAttr(int mode)
{
    this->Attr=mode;
}
void SimpleCharRotator::run()
{
    while(1)
    {
        Util::setCursor(this->X,this->Y);
        //调用0x24中断打印字符
        CALL_INT_3(0x24,c,Util::getCurrentDs(),b,&SimpleCharRotator::rotateShapes[this->Status],d,this->Attr);
        this->Status = (this->Status*this->Direction + 3) % (sizeof(SimpleCharRotator::rotateShapes)/sizeof(char));
    }
}

//=================class:Printer
const int Printer::SCREEN_MAX_X=25,
        Printer::SCREEN_MAX_Y=80; //起始const static 也算是编译期常数，
//This warning can be ignored because no need to assign these value
Printer::Printer(unsigned int x0,
		unsigned int y0,
		unsigned int rows,
		unsigned int cols,
		int mode):
rows(rows>Printer::SCREEN_MAX_X?Printer::SCREEN_MAX_X:rows),
cols(cols>Printer::SCREEN_MAX_Y?Printer::SCREEN_MAX_Y:cols),
x0(x0+this->rows>=Printer::SCREEN_MAX_X?0:x0),
y0(y0+this->cols>=Printer::SCREEN_MAX_Y?0:y0),
x(0),y(0),
mode(mode),
father(nullptr),sonSize(0)
{
     
}
Printer::~Printer()
{
    
}

void Printer::move(int n)
{
    this->y+=n;
    while(this->y < 0)
    {
        this->y+=this->cols;
        this->x--;
        if(this->x == -1)
        {
            this->x=this->rows - 1;
        }
    }
    while(this->y >= (int)this->cols)
    {
        this->y -= this->cols;
        this->x++;
        if(this->x==(int)this->rows)
        {
            this->x = 0 ;
        }
    }
    
    
    
}
void Printer::putc(int chr)
{
    int oldes;
    Util::enterEs(Util::videoSelector,oldes);
    switch(this->specailCharProcessor(chr))
    {
        case 0:
            this->__putc(chr);
            this->move(1);
            break;
        case 1:
        case -1:
        default:
            break;
    }
    Util::leaveEs(oldes);
}
void Printer::putsz(const char* str)
{
    int oldes;
    const char *p=str;
    Util::enterEs(Util::videoSelector,oldes);
    int rt;
    while((rt=this->specailCharProcessor(*p))!=-1)
    {
        if(rt==0)
        {
            this->__putc(*p);
            this->move(1);
        }
        p++;
    }
    Util::leaveEs(oldes);
}

#if defined(CODE32) || defined(CODE32USER)
void Printer::puti(const char *str,int i,const char* strAfter)
{
	char buf[10];
	Util::digitToStr(buf, arrsizeof(buf), i);
	putsz(str);
	putsz(buf);
	if(strAfter)
		putsz(strAfter);
}


void Printer::putx(const char* str,int i,const char* strAfter)
{
	char buf[10];
	Util::digitToHex(buf, arrsizeof(buf), i);
	putsz(str);
	putsz(buf);
	if(strAfter)
		putsz(strAfter);
}
void Printer::puti(const char* str,void * i,const char* strAfter)
{
	puti(str,reinterpret_cast<int>(i),strAfter);
}
void Printer::putx(const char* str,void * i,const char* strAfter)
{
	putx(str,reinterpret_cast<int>(i),strAfter);
}
#endif

void Printer::putsn(const char *str,int n)
{
    int oldes;
    const char *p=str;
    Util::enterEs(Util::videoSelector,oldes);
    int rt;
    int i=0;
    while((rt=this->specailCharProcessor(*p))!=-1 && i!=n )
    {
        if(rt==0)
        {
            this->__putc(*p);
            this->move(1);
        }
        p++;
        i++;
    }
    Util::leaveEs(oldes);
}
void Printer::setPos(int x,int y)
{
    this->x=x % this->rows;
    this->y=y % this->cols;
}
void Printer::setMode(int mode)
{
    this->mode=mode;
}
int Printer::specailCharProcessor(int chr)
{
    int rt=1;
    switch(chr)
    {
        case '\n':
        	Util::insertMark(0x624624);
            this->x = (this->x + 1) % this->rows;
            this->y = 0;
            break;
        case '\r':
            this->y = 0;
            break;
        case '\b':
            this->move(-1);
            break;
        case '\t':
            this->move(4);
            break;
        case '\0':
            rt=-1;
            break;
        default://
            rt=0;
            break;
    }
    return rt;
}

int Printer::getPos()
{
    return (this->x0+this->x)*Printer::SCREEN_MAX_Y*2+(this->y0+this->y)*2;
}

void Printer::__putc(int chr)
{
    __asm__ __volatile__(
    "mov %%al,%%es:(%%edi) \n\t"
    "mov %%dl,%%es:1(%%edi) \n\t"
    :
    :"a"(chr),"D"(this->getPos()),"d"(this->mode)
    :
    );
}

void Printer::clr()
{
    this->setPos(0,0);
    for(size_t i=0;i!=this->rows;i++)
    {
        for(size_t j=0;j!=this->cols;j++)
        {
            this->putc(' ');
        }
    }
    this->setPos(0,0);
}
Printer  Printer::getSubPrinter(unsigned int x0,unsigned int y0,unsigned int rows,unsigned int cols,int mode)
{
	char spaces[sizeof(Printer)];
    Printer* target=reinterpret_cast<Printer*>(spaces);
    target->rows = rows > this->rows?this->rows:rows;
    target->cols = cols > this->cols? this->cols: cols;
    target->x0   = this->x0 + ((x0+target->rows) >  this->rows?0:x0);
    target->y0   = this->y0 + ((y0+target->cols) > this->cols?0:y0);
    target->x = 0;
    target->y = 0;
    target->mode = mode;
    target->father = this;
    target->sonSize = 0;
    
    return *target;

    //no return target, avoid copying on return
}

ClassDebug::ClassDebug(const char *msg)
{
#if defined(CODE32)
//	if(Kernel::printer!=nullptr)
//		Kernel::printer->putsz(msg);
#endif
}

#endif //SimpleCharRotator,Printer ,ErrorSaverin CODE32

#if defined(CODE32) || defined(CODE64)
//==========class : String
String::String(const char* str):
		str(nullptr)
{
    
}
String::~String()
{
    
}

int String::size()
{
    return 0;
}
char String::get(int index)
{
	return 0;
}
void String::set(int index,int ch)
{
    
}

String String::valueOf(int n)
{
    return String(nullptr);
}

//============class : Queue<T>
template<typename T>
Queue<T>::Queue(T p[],size_t len):
p(p),len(len),curLen(0),indexAdd(0),indexRemove(0)
{
    
}
template<typename T>
Queue<T>::~Queue()
{
    
}
// i--remove
//j--add
//len = 4
//  j=0 OK
//  j=1 OK
//  j=2 OK
//  j=3 OK
//  j=4--j=0 but j=0 full
template<typename T>
T Queue<T>::remove()
{
    T rt;
    if(this->isEmpty())
    {
        return 0;
    }else{
        rt = p[indexRemove];
        indexRemove++;
        curLen--;
        if(indexRemove==reinterpret_cast<int>(len))indexRemove=0;
    }
    return rt;
}
template <typename T>
int Queue<T>::put(T t)
{
    if(this->isFull())
    {
        return 0;
    }else{
        this->p[indexAdd]=t;
        indexAdd++;
        curLen++;
        if(indexAdd == reinterpret_cast<int>(len))indexAdd=0;
    }
    return 1;
    

}


#endif //class Queue,String in CODE32 && CODE64


#if defined(CODE32)||defined(CODE16)|| defined(CODE32USER)
void Util::reboot()
{

    __asm__ __volatile__(
    "inb  $0x92,%%eax \n\t"
    "andb $0xfe,%%eax \n\t"
    "outb %%al,$0x92 \n\t"
    "orb $0x1,%%eax \n\t"
    "outb %%al,$0x92\n\t"
    :
    :
    :"eax"
    );
}
void Util::memcopyInlineable(int srcSeg,int srcOff,int dstSeg,int dstOff,int len)
{
#if defined(CODE32)||defined(CODE16)
    ENTER_ES(dstSeg,s2);
    ENTER_DS(srcSeg,s1);

    __asm__ __volatile__( //ds:si --> es:di
    "cld \n\t"
    "rep movsb \n\t"
    		:
    		:"S"(srcOff),"D"(dstOff),"c"(len)
			:
    );

    LEAVE_DS(srcSeg,s1);
    LEAVE_ES(dstSeg,s2);
#elif defined(CODE32USER)

#endif
}

#endif


#if defined(CODE32) || defined(CODE16)
void	Util::setStrSel(int sel)
{
	Util::strSel=sel;
}
int  Util::getStrSel()
{
	return Util::strSel;
}
#endif

#if defined(CODE32) || defined(CODE16) || defined(CODE32USER)
void Util::insertMark(int marker)
{
    __asm__(
     "nop \n\t"
    );
}
void Util::jmpDie()
{
    __asm__("jmp .\n\t");
}
void Util::jmp(int addr)
{
	__asm__ __volatile__(
#if defined(CODE16)
			"jmp %%ax \n\t"
#elif defined(CODE32)
			"jmp %%eax \n\t"
#else
			""
#endif
			:
			:"a"(addr)
			:
	);
}

void Util::cli()
{
    __asm__("cli \n\t");
}
void Util::sti()
{
    __asm__("sti \n\t");
}
void Util::enterDs(int seg,int& temp)
{
    if(seg!=SEG_CURRENT)
    {
            __asm__ __volatile__(
            "mov %%ds,%%bx \n\t"
            "mov %%ax,%%ds \n\t"
            :"=b"(temp)
            :"a"(seg)
            :);
    }
}
void Util::leaveDs(int seg,int temp)
{
    if(seg!=SEG_CURRENT)
    {
        __asm__ __volatile__("mov %%ax,%%ds \n\t"::"a"(temp):);
    }
}
 void Util::enterEs(int seg,int& temp)
 {
     __asm__ __volatile__("mov %%es,%%ax\n\t":"=a"(temp)::);
    if(seg==SEG_CURRENT)
    {
        __asm__ __volatile__(
            "mov %%ds,%%ax \n\t"
            "mov %%ax,%%es \n\t"
            :
            :
            :"eax"
        );
    }else{
        __asm__ __volatile__(
        "mov %%ax,%%es \n\t"
        :
        :"a"(seg)
        :
        );
    }
 }
void Util::leaveEs(int temp)
{
    __asm__ __volatile__("mov %%ax,%%es \n\t"::"a"(temp):);
}

void Util::outb(short port,char data)
{
    __asm__(
    "outb %%al,%%dx \n\t"
    :
    :"d"(port),"a"(data)
    :
    );
}
void Util::outw(short port,short data)
{
    __asm__(
    "outw %%ax,%%dx \n\t"
    :
    :"d"(port),"a"(data)
    :
    );
}
char Util::inb(short port)
{
    char temp;
    __asm__(
    "inb %%dx,%%al \n\t"
    :"=a"(temp)
    :"d"(port)
    :
    );
    return temp;
}
short Util::inw(short port)
{
    short temp;
    __asm__(
    "inw %%dx,%%ax \n\t"
    :"=a"(temp)
    :"d"(port)
    :
    );
    return temp;
}

void Util::ljmp(int newcs,int neweip)
{
	__asm__ __volatile__(
			"pushw %%cx \n\t"
#if defined(CODE16)
			"pushw %%bx \n\t"
#elif defined(CODE32) || defined(CODE32USER)
			"push %%ebx \n\t"
#endif
			"ljmp *(%%esp) \n\t"
			:
			:"c"(newcs),"b"(neweip)
			:"memory"
	);
}

void Util::replaceCs(int newcs)
{
	__asm__ __volatile__(
			"pushw  %%cx\n\t"
#if defined(CODE32)
			"push  	$1f \n\t"
#elif defined(CODE16)
			"pushw  $1f \n\t"
#endif
			"ljmp *(%%esp) \n\t"
			"1:\n\t"
			:
			:"c"(newcs)
			:"memory"
	);
}
void Util::replaceSS_DS_ES(int newseg)
{
	__asm__ __volatile__(
			"mov %%ax,%%ss \n\t"
			"mov %%ax,%%ds \n\t"
			"mov %%ax,%%es \n\t"
			:
			:"a"(newseg)
			:
	);
}

#if defined(CODE16)
int Util::readSectorsCHSInline(int dstSeg,int dstOff,int driver,int cylinder,int head,int startSec,int numSecs)
{
	   int isCarried;
	    __asm__ __volatile__(
	    "push %%es\n\t"
	    "// mov 4+4*1(%%ebp),%%eax \n\t" // ax由输入参数设置
	    "movw %%ax,%%es\n\t"
	    "// movw 4+4*2(%%ebp),%%bx\n\t" // bx 由输入参数设置
	    "// movb 4+4*3(%%ebp),%%dl \n\t"
	    "// movb 4+4*5(%%ebp),%%dh \n\t" // dl由输入参数设置，但是dh只能由head的值来设定
	    "   movb %[head],%%dh \n\t"
	    "// movw 4+4*4(%%ebp),%%cx \n\t" // cx由输入参数设定
	    "shl   $6,%%cx \n\t"
	    "addb %[startSec],%%cl \n\t"
	    "movb $0x02,%%ah \n\t"
	    "movb %[numSecs],%%al \n\t"
	    "int $0x13 \n\t"
	    "pop %%es \n\t"
	    "xor %%eax,%%eax \n\t"
	    "jc 1f \n\t"
	    "mov $1,%%eax \n\t"
	    "1:\n\t"
	    :"=a"(isCarried)
	    :"a"(dstSeg),"b"(dstOff),"d"(driver),"c"(cylinder),
		 	 [head]"m"(head),[startSec]"m"(startSec),[numSecs]"m"(numSecs)
	    :"memory","cc"
	    );
	    return isCarried;
}
int Util::readSectorsInline(int dstSeg,int dstOff,int driver,int LBAStart,int numSecs)
{
	 return Util::readSectorsCHSInline(dstSeg,dstOff,driver,LBAStart/36,(LBAStart - LBAStart/36*36)/18,(LBAStart%18) + 1,numSecs);
}
int Util::readSectorsExt(int driver,ExtendedInt0x13Info *info)
{
	int isError;
	__asm__ __volatile__(
			"movb %[func_ah],%%ah \n\t"
			"movb %[driver_dl],%%dl \n\t"
			"int $0x13 \n\t"
			"mov $1,%%eax \n\t" //成功返回1
			"jnc   1f \n\t"
			"mov $0,%%eax \n\t"  //错误返回0
			"1:"
			:"=a"(isError)
			:[func_ah]"i"(ExtendedInt0x13Info::FUNC_42_READ_LBA),[driver_dl]"m"(driver),"S"(info)
			:
	);
	return isError;
}
#endif
/*
void Util::pusha()
{
    __asm__("pusha \n\t");
}
void Util::popa()
{
    __asm__("popa \n\t");
}
*/
#endif

#if defined(CODE16)
ExtendedInt0x13Info::ExtendedInt0x13Info(u16_t dstSeg,u16_t dstOff,u32_t lbaAddrLow,u16_t sectorNum,u32_t lbaAddrHigh):
		thisStructSize(16),reserved(0),
		sectorNum(sectorNum),
		dstOff(dstOff),
		dstSeg(dstSeg),
		lbaAddrLow(lbaAddrLow),
		lbaAddrHigh(lbaAddrHigh)

{

}

#endif

#if defined(CODE32) || defined(CODE32USER)
int Printer::getX()
{
    return this->x;
}

int Printer::getY()
{
    return this->y;
}

//=======class ErrorSaver
ErrorSaver::ErrorSaver(int errno):errno(errno) {
}

int ErrorSaver::getErrno() const {
	return this->errno;
}

void ErrorSaver::setErrno(int errno) {
	this->errno=errno;
}

void Util::ltr(int sel)
{
    __asm__ __volatile__(
    "ltr %0 \n\t"
    :
    :"m"(sel)
    :
    );
}
void Util::lldt(int sel)
{
    __asm__ __volatile__(
    "lldt %0 \n\t"
    :
    :"m"(sel)
    :
    );
}
int	Util::getCurrentDs()
{
	int temp;
	__asm__ __volatile__(
	"push %%ds \n\t"
	"pop %%eax \n\t"
	:"=a"(temp)
	:
	:
	);
	return temp;
}
void Util::setCurrentDs(int ds)
{
	__asm__ __volatile__(
			"mov %%eax,%%ds \n\t"
			:
			:"a"(ds)
			 :
			 );
}

int	Util::getCurrentSs()
{
	int temp;
	__asm__ __volatile__(
	"push %%ss \n\t"
	"pop %%eax \n\t"
	:"=a"(temp)
	:
	:
	);
	return temp;
}
void Util::setCurrentSs(int ss)
{
	__asm__ __volatile__(
			"mov %%eax,%%ss \n\t"
			:
			:"a"(ss)
			 :
			 );
}

#if defined(CODE32)
void Util::intReturn()
{
    __asm__(
    "leave \n\t"
    "iret \n\t"
    );
}
#endif
/**this originally works
void Util::initTarget(void *&target)
{
    __asm__ __volatile__("":"=c"(target)::);
}
*/
/************Deprecated
void Util::initTarget(void **target)
{
__asm__ __volatile__("":"=c"(*(char**)target)::);
}
*/
#endif

#if defined(CODE32)||defined(CODE64)||defined(CODE16)||defined(CODE32USER) //通用
template <typename __SimpleType>
__SimpleType Util::min(__SimpleType t1,__SimpleType t2)
{
	return (t1>t2?t2:t1);
}
template <typename __SimpleType>
__SimpleType Util::max(__SimpleType t1,__SimpleType t2)
{
	return (t1>t2?t1:t2);
}
#endif


#if defined(CODE32)||defined(CODE64)||defined(CODE32USER)


//=======class : Queue 宏
template <typename T>
bool Queue<T>::isEmpty()
{
    return curLen==0;
}
template <typename T>
bool Queue<T>::isFull()
{
    return curLen==len;
}
template <typename T>
unsigned int Queue<T>::size()
{
    return curLen;
}
#endif


//======================================================================
#ifdef CODE16
//======================仅16位===========
//ebp + 4 = 返回地址
//ebp + 4*n : n>0,第n个参数
int Util::readSectorsCHS(int dstSeg,int dstOff,int driver,int cylinder,int head,int startSec,int numSecs)
{
	return Util::readSectorsCHSInline(dstSeg, dstOff, driver, cylinder, head, startSec, numSecs);
}
int Util::readSectors(int dstSeg,int dstOff,int driver,int LBAStart,int numSecs)
{
   return Util::readSectorsInline(dstSeg, dstOff, driver, LBAStart, numSecs);
}
#endif
