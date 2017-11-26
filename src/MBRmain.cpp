//extern int READSEG[];//use _READSEG in other file

/**
 * 该文件是MBR引导区，由于位置比较特殊，其代码的体积有446字节的限制
 * 请谨慎修改该文件，并使用-O1及以下的优化级别
 *
 * 此文件读取分区表，找到其中标记为active的第一项，然后读取该项分区所在的硬盘到0x7c00处并跳转到该处执行
 * 由于这个原因，所以在载入vbr扇区之前，需要将其自身从0x7c00移到一个安全的位置
 *
 */

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

// 汇编代码中定义的MBRTable的,必须使用数组定义，因为需要的是一个地址
extern "C" MBRTable mbrtable[1];


/**
 * 防止该函数被优化
 */
__attribute__((optimize("-fno-crossjumping")))
__attribute__((optimize("-fno-reorder-blocks")))
__attribute__((optimize("-fno-unsafe-loop-optimizations")))
__attribute__((optimize("-fno-aggressive-loop-optimizations")))
__attribute__((optimize("-fno-indirect-inlining")))
__attribute__((optimize("-fno-inline")))
__attribute__((section("textmbr"))) int findFirstActive()
{
	return mbrtable[0].findFirstActiveInline();
}

//#pragma GCC push_options
//#pragma GCC optimize ("Os") //减少代码体积
extern "C"
__attribute__((section("textmbr")))
__attribute__((optimize("O1"))) //请从不要使用O3 O2 Os,最多使用O1,如果可能，使用O0(当然不可能）
__attribute__((optimize("-fno-reorder-blocks")))
__attribute__((optimize("-fno-reorder-blocks-and-partition")))
__attribute__((optimize("-fno-toplevel-reorder")))
__attribute__((optimize("-fno-reorder-functions")))
__attribute__((optimize("-fomit-frame-pointer")))
__attribute__((optimize("-fno-unsafe-loop-optimizations")))
__attribute__((optimize("-fno-aggressive-loop-optimizations")))
__attribute__((optimize("-fno-delayed-branch")))
__attribute__((optimize("-fno-crossjumping")))
__attribute__((optimize("-fno-indirect-inlining")))
__attribute__((optimize("-fno-branch-count-reg")))
__attribute__((optimize("-fno-thread-jumps")))
__attribute__((optimize("-fno-inline")))
__attribute__((optimize("-fno-expensive-optimizations")))
__attribute__((optimize("-fno-loop-parallelize-all")))
__attribute__((optimize("-fno-variable-expansion-in-unroller")))
__attribute__((optimize("-fno-guess-branch-probability")))
__attribute__((optimize("-fno-profile-use")))
//__attribute__((optimize("")))
//__attribute__((optimize("")))
void readLaterSectors()
{
	// 0. 一些调试代码



	// 1.将整体代码和栈复制到0x7c0:栈后
	Util::memcopyInlineable(0x7c0,0,0x7c0, CONFIG_REAL_INIT_STACK_SIZE, CONFIG_REAL_INIT_STACK_SIZE);

	enum{
		NEW_SEG = (0x7c00+CONFIG_REAL_INIT_STACK_SIZE)>>4,
	};
	// 2.跳转到复制后的代码处继续执行
	Util::replaceCs( NEW_SEG );

	// 3.重置ss,ds,es指针
	Util::replaceSS_DS_ES( NEW_SEG );

	// 4.读取活动分区(active)的第一个扇区到0x7c00处
	int activePartition = findFirstActive();
//	int activePartition = 0;
//	if(mbrtable[0].table[activePartition].activeFlag==MBRPartitionEntry::FLAG_ACTIVE)goto found;
//	if(mbrtable[0].table[++activePartition].activeFlag==MBRPartitionEntry::FLAG_ACTIVE)goto found;
//	if(mbrtable[0].table[++activePartition].activeFlag==MBRPartitionEntry::FLAG_ACTIVE)goto found;
//	if(mbrtable[0].table[++activePartition].activeFlag==MBRPartitionEntry::FLAG_ACTIVE)goto found;
//	found:
	if(activePartition != -1)
	{
		*(int*)0=activePartition;
		*(int*)4=mbrtable[0].table[activePartition].lbaStart;
		ExtendedInt0x13Info extInt3Info(0x7c0,0,mbrtable[0].table[activePartition].lbaStart,1);
		Util::readSectorsExt(0x80, &extInt3Info);
	}else{
		Util::jmpDie();
	}

	// 5.重新跳转到 0x7c0:0
	Util::ljmp(0x7c0,0);



	//通过让编译器自己计算这些值来减少代码量，因为我们没有启用优化选项
//	enum{
//		LBAStart=CONFIG_REAL_INIT_STACK_SIZE/CONST_SECSIZE,
//		Cylinder=LBAStart/36,
//		Head = (LBAStart - LBAStart/36*36)/18,
//		StartSec=(LBAStart%18) + 1,
//		NumSec =  CONFIG_REAL_SECNUMS - CONFIG_REAL_INIT_STACK_SIZE/CONST_SECSIZE,
//	};
//	readSectorsCHSInline(0x7c0, CONFIG_REAL_INIT_STACK_SIZE, 0x80, Cylinder, Head, StartSec, NumSec);

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
		".org CONFIG_MBR_PARTITION_START \n\t" // 保证代码不会覆盖分区表,463?//注意：如果这里报错，就是前面代码区尺寸太大，需要优化
		"_mbrtable: \n\t" //定义分区表的位置
 		".org 512 - 2\n\t"
		".byte 0x55\n\t"
		".byte 0xaa\n\t"
		".org CONFIG_REAL_INIT_STACK_SIZE \n\t"
);//make sure it has no more that this

//#pragma GCC pop_options

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
