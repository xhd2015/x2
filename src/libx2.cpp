



#include <libx2.h>
#include <def.h>
#include <Kernel.h>

#include <macros/libx2_macros.h>

#ifdef CODE16
    __asm__(".code16gcc \n\t");
#elif defined(CODE32) || defined(CODE32USER)
    __asm__(".code32 \n\t");
#endif

#if defined(CODE64)
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
	if(str_addr==NULL)return;
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
#if defined(CODE32)||defined(CODE16)
    ENTER_ES(dstSeg,s2);
    ENTER_DS(srcSeg,s1);

    __asm__( //ds:si --> es:di
    "push %esi \n\t"
    "push %edi \n\t"
    "mov 4+4*2(%ebp),%esi \n\t"
    "mov 4+4*4(%ebp),%edi \n\t"
    "mov 4+4*5(%ebp),%ecx \n\t"
    "cld \n\t"
    "rep movsb \n\t"
    "pop %edi \n\t"
    "pop %esi \n\t"
    );
    
    LEAVE_DS(srcSeg,s1);
    LEAVE_ES(dstSeg,s2);
#elif defined(CODE32USER)

#endif
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
sonSize(0),father(NULL)
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
    while(this->y >= this->cols)
    {
        this->y -= this->cols;
        this->x++;
        if(this->x==this->rows)
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
	puti(str,(int)i,strAfter);
}
void Printer::putx(const char* str,void * i,const char* strAfter)
{
	putx(str,(int)i,strAfter);
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
    for(int i=0;i!=this->rows;i++)
    {
        for(int j=0;j!=this->cols;j++)
        {
            this->putc(' ');
        }
    }
    this->setPos(0,0);
}
Printer  Printer::getSubPrinter(unsigned int x0,unsigned int y0,unsigned int rows,unsigned int cols,int mode)
{
	char spaces[sizeof(Printer)];
    Printer* target=(Printer*)spaces;
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
//	if(Kernel::printer!=NULL)
//		Kernel::printer->putsz(msg);
#endif
}

#endif //SimpleCharRotator,Printer ,ErrorSaverin CODE32

#if defined(CODE32) || defined(CODE64)
//==========class : String
String::String(const char* str):
		str(NULL)
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
    return String(NULL);
}

//============class : Queue<T>
template<typename T>
Queue<T>::Queue(T p[],size_t len):p(p),len(len),curLen(0),indexRemove(0),indexAdd(0)
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
        if(indexRemove==(int)len)indexRemove=0;
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
        if(indexAdd == (int)len)indexAdd=0;
    }
    return 1;
    

}


#endif //class Queue,String in CODE32 && CODE64

//======================================================================
#ifdef CODE16
//======================仅16位===========
//ebp + 4 = 返回地址
//ebp + 4*n : n>0,第n个参数
int Util::readSectorsCHS(int dstSeg,int dstOff,int driver,int cylinder,int head,int startSec,int numSecs)
{
    int isCarried;
    __asm__ __volatile__(
    "push %%es\n\t"
    "mov 4+4*1(%%ebp),%%eax \n\t"
    "movw %%ax,%%es\n\t"
    "movw 4+4*2(%%ebp),%%bx\n\t"
    "movb 4+4*3(%%ebp),%%dl \n\t"
    "movb 4+4*5(%%ebp),%%dh \n\t"
    "movw 4+4*4(%%ebp),%%cx \n\t"
    "shl   $6,%%cx \n\t"
    "addb 4+4*6(%%ebp),%%cl \n\t"
    "movb $0x02,%%ah \n\t"
    "movb 4+4*7(%%ebp),%%al \n\t"
    "int $0x13 \n\t"
    "pop %%es \n\t"
    "xor %%eax,%%eax \n\t"
    "jc error \n\t"
    "mov $1,%%eax \n\t"
    "error:\n\t"
    :"=a"(isCarried)
    :
    :"memory","cc"
    );
    return isCarried;
}
int Util::readSectors(int dstSeg,int dstOff,int driver,int LBAStart,int numSecs)
{
    return Util::readSectorsCHS(dstSeg,dstOff,driver,LBAStart/36,(LBAStart - LBAStart/36*36)/18,(LBAStart%18) + 1,numSecs);
}
#endif
