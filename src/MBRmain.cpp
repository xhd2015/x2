//extern int READSEG[];//use _READSEG in other file

#include <libx2.h>
#include <PMLoader.h>
#include <Descriptor.h>
#include <def.h>
#include <Filesystem.h>

#include <macros/all.h>

#if defined(CODE16)
__asm__(
		".code16gcc \n\t"
);
#endif

#if defined(CODE16)
//开始引导
__asm__(
		".section textmbr,\"x\" \n\t"
		".global STACKSIZE\n\t"
		"STARTSEG = 0x7c0 \n\t"
"ljmp $STARTSEG,$1f \n\t"
"1: \n\t"
"cli \n\t"
"mov $STARTSEG,%ax \n\t"
"mov %ax,%ds \n\t"
"mov %ax,%ss \n\t"
"mov %ax,%es \n\t"
"mov $CONFIG_REAL_INIT_STACK_SIZE - 1,%sp \n\t"  //设置段寄存器和esp
"call _readLaterSectors \n\t" //读取剩余的所有扇区
"call _realModeTest \n\t"
);

extern "C" MBRTable* mbrtable;

__attribute__((section("textmbr"))) int readSectorsCHSInline(int dstSeg,int dstOff,int driver,int cylinder,int head,int startSec,int numSecs)
{
	   int isCarried;
	    __asm__ __volatile__(
	    "push %%es\n\t"
	    "movw %%ax,%%es\n\t"
	    "movb %[head],%%dh \n\t"
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

// 使用该段代码来判断启动扇区，然后读入该扇区
// 注意使用优化：如果一个函数宏被调用超过两次，请使用额外的函数定义
extern "C" __attribute__((section("textmbr"))) void readLaterSectors()
{
	//通过让编译器自己计算这些值来减少代码量，因为我们没有启用优化选项
	enum{
		LBAStart=CONFIG_REAL_INIT_STACK_SIZE/CONST_SECSIZE,
		Cylinder=LBAStart/36,
		Head = (LBAStart - LBAStart/36*36)/18,
		StartSec=(LBAStart%18) + 1,
		NumSec =  CONFIG_REAL_SECNUMS - CONFIG_REAL_INIT_STACK_SIZE/CONST_SECSIZE,
	};
	readSectorsCHSInline(0x7c0, CONFIG_REAL_INIT_STACK_SIZE, 0x80, Cylinder, Head, StartSec, NumSec);

	// 这些是原来的代码，生成的代码量很大，不适合在mbr区中使用
//	Util::readSectors(
//			0x7c0,CONFIG_REAL_INIT_STACK_SIZE,0x80,
//			/36, CONFIG_REAL_SECNUMS - CONFIG_REAL_INIT_STACK_SIZE/CONST_SECSIZE);
	//return readSectorsCHSInline(dstSeg,dstOff,driver,
//	LBAStart/36,(LBAStart - LBAStart/36*36)/18,(LBAStart%18) + 1,numSecs);

//    __asm__(
//        "READLEN =  CONFIG_REAL_SECNUMS - CONFIG_REAL_INIT_STACK_SIZE/512  \n\t"
//        "push %es\n\t"
//        "movw $STARTSEG,%ax \n\t"  //这些来自PMLoader的参数尚未加载
//        "mov %ax,%es\n\t"
//        "mov $CONFIG_REAL_INIT_STACK_SIZE,%bx\n\t" //cx=start-sector -->es:bx+READLEN
//        "xor %dx,%dx \n\t"		//dl=0,1(floppy) 80 81(hard disk)
//    	"mov $0x80,%dl \n\t"	//read from hard disk
//        "mov $0x0003,%cx \n\t"
//        "mov $0x200+READLEN,%ax \n\t"
//        "int $0x13 \n\t"
//        "pop %es \n\t"
//    );

	// 找到开始扇区的位置，将其加载到相应位置

}


__asm__(
		".section textmbr,\"x\" \n\t"
		".org CONFIG_MBR_PARTITION_START \n\t" // 保证代码不会覆盖分区表,463?
		"_mbrtable: \n\t" //定义扇区位置
 		".org 512 - 2 \n\t"
		".byte 0x55\n\t"
		".byte 0xaa\n\t"
		".org CONFIG_REAL_INIT_STACK_SIZE \n\t"
);//make sure it has no more that this
//align is 4
//MBR starts from 0x1BE to 0x1FD,   (0x1FE,0x1FF)=0xaa55,  the last_section should start @0x1bc,and then org 2

/*
__asm__(
".section .last_section \n\t"
".org 2 \n\t" //0x1BC
		"PART1: \n\t"
		".byte 0x80 \n\t"   //boot flag
		".byte 0,0,0 \n\t" //chs start
		".byte 0x0b \n\t"  //sys_ind,type of table
		".byte 0,0,0 \n\t"  //chs end
		".int 0 \n\t"    //start sector(from 0,counting the whole disk)
		".int 0\n\t"    //spanned sectors

		"PART2: \n\t"
		".byte 0x80 \n\t"   //boot flag
		".byte 0,0,0 \n\t" //chs start
		".byte 0x0b \n\t"  //sys_ind,type of table
		".byte 0,0,0 \n\t"  //chs end
		".int 0 \n\t"    //start sector(from 0,counting the whole disk)
		".int 0\n\t"    //spanned sectors

		"PART2: \n\t"
		".byte 0x80 \n\t"   //boot flag
		".byte 0,0,0 \n\t" //chs start
		".byte 0x0b \n\t"  //sys_ind,type of table
		".byte 0,0,0 \n\t"  //chs end
		".int 0 \n\t"    //start sector(from 0,counting the whole disk)
		".int 0\n\t"    //spanned sectors

		"PART2: \n\t"
		".byte 0x80 \n\t"   //boot flag
		".byte 0,0,0 \n\t" //chs start
		".byte 0x0b \n\t"  //sys_ind,type of table
		".byte 0,0,0 \n\t"  //chs end
		".int 0 \n\t"    //start sector(from 0,counting the whole disk)
		".int 0\n\t"    //spanned sectors
".word 0xaa55 \n\t"
);
*/ // This part now is moved as a partition table out side(created by other disk tools)

#endif
