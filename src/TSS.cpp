#ifdef CODE32
__asm__(".code32 \n\t");
#endif

#include <TSS.h>
#include <libx2.h>
#include <def.h>
#include <PMLoader.h>
#include <MemoryManager.h> //for new

#if defined(CODE32)
TSS::TSS()
{
	//清零
	size_t i;
	for(i=0;i * sizeof(int) < sizeof(*this);i++)//fast
	{
		*((int*)this + i)=0;
	}
	while(i < sizeof(*this))//slower
	{
		*((char*)this + i)=0;
		i++;
	}

}

TSS::~TSS()
{

}


void TSS::writeToMemory(int seg,int off)
{   
    Util::memcopy(Util::SEG_CURRENT,(int)this->I0,seg,off,PMLoader::TSS_MIN_SIZE);
}
//void TSS::ensureReservedZero()
//{
//        //确保RESERVED的地方为0
//    char* reserve_arr[] = {this->I0+2,this->I2+2,this->I4+2,this->I6+2,this->I18+2,this->I19+2,this->I20+2,this->I21+2,this->I22+2,this->I23+2,this->I24+2};
//    int len = sizeof(reserve_arr)/sizeof(char*);
//    for(int i=0;i!=len;i++)
//    {
//        *(short*)reserve_arr[i]=0;
//    }
//    //对TRAP标志单独处理
//    *(short*)this->I25 &= 0x1;
//
//}
void TSS::fromMemory(TSS &self,int seg,int off)
{
	new (&self) TSS;
    Util::memcopy(seg,off,Util::SEG_CURRENT,(int)self.I0,PMLoader::TSS_MIN_SIZE);
}
void TSS::dumpInfo(Printer *p)
{
	if(p!=nullptr)
	{
		p->putsz("TSS{");
		p->putx("LDTSEL:",this->LDTSEL,",");
		p->putx("CR3:",this->CR3,",");
		p->putx("CS:",this->CS,",");
		p->putx("EIP:",this->EIP,",");
		p->putx("DS:",this->DS,",");
		p->putx("SS0:",this->SS0,",");
		p->putx("ESP0:",this->ESP0,",");
		p->putx("SS(3):",this->SS,",");
		p->putx("ESP(3):",this->ESP,",");
		p->putsz("}");
	}
}

#endif //CODE32
