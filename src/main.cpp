//extern int READSEG[];//use _READSEG in other file

#include <libx2.h>
#include <macros/libx2_macros.h>
#include <PMLoader.h>
#include <Descriptor.h>
#include <def.h>

#if defined(CODE16)
__asm__(
		".code16gcc \n\t"
);
#endif

#if defined(CODE16)
//开始引导
__asm__(
		".text \n\t"
		"STARTSEG = 0x7c0 \n\t"
		"STACKSIZE = 512*2 \n\t"
"ljmp $STARTSEG,$HERE \n\t"
"HERE: \n\t"
"cli \n\t"
"mov $STARTSEG,%ax \n\t"
"mov %ax,%ds \n\t"
"mov %ax,%ss \n\t"
"mov %ax,%es \n\t"
"mov $STACKSIZE,%sp \n\t"  //设置段寄存器和esp
"call _readLaterSectors \n\t" //读取剩余的所有扇区
"call _realModeTest \n\t"
);

//突破1扇区的限制先
//将后面的扇区读到起始地址 0xa000处
// NOTE DEPRECATED 不再使用，现在无需跳转
extern "C" void readLaterSectors()
{
    __asm__(
        "READLEN =  25 -2  \n\t"
        "push %es\n\t"
        "movw $STARTSEG,%ax \n\t"  //这些来自PMLoader的参数尚未加载
        "mov %ax,%es\n\t"
        "mov $STACKSIZE,%bx\n\t" //cx=start-sector -->es:bx+READLEN
        "xor %dx,%dx \n\t"		//dl=0,1(floppy) 80 81(hard disk)
    	"mov $0x80,%dl \n\t"	//read from hard disk
        "mov $0x0003,%cx \n\t"
        "mov $0x200+READLEN,%ax \n\t"
        "int $0x13 \n\t"
        "pop %es \n\t"
    );
}


__asm__(
		".text \n\t"
		".org 0x1BC \n\t"
		".word 0xaa55,0xaa55\n\t"
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
