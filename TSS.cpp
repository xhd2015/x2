#include "TSS.h"
#include "libx2.h"
#include "def.h"
TSS::TSS():IOADDR((char*)((&__IOBASEADDR)+2)),TRAP( (char*)(&__IOBASEADDR))
{


}

TSS::~TSS()
{

}


void TSS::writeToMemory(int seg,int off)
{   
    Util::memcopy(SEG_CURRENT,this->I0,seg,off,TSS_MIN_SIZE);
}
void TSS::ensureReservedZero()
{
        //确保RESERVED的地方为0
    char* reserve_arr[] = {this->I0+2,this->I2+2,this->I4+2,this->I6+2,this->I18+2,this->I19+2,this->I20+2,this->I21+2,this->I22+2,this->I23+2,this->I24+2};
    int len = sizeof(reserve_arr)/sizeof(char*);
    for(int i=0;i!=len;i++)
    {
        *(short*)reserve_arr[i]=0;
    }
    //对TRAP标志单独处理
    *(short*)this->I25 &= 0x1;
    
}
void TSS::fromMemory(TSS &self,int seg,int off)
{
    Util::memcopy(seg,off,SEG_CURRENT,self.I0,TSS_MIN_SIZE);
    self.ensureReservedZero();//保证所有的reserved都为0
}