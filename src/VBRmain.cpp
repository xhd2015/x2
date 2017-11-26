
#include <def.h>
#include <Filesystem.h>
#include <libx2.h>

#define CODE16

#if defined(CODE16)
	__asm__(".code16gcc \n\t");
#endif


#if defined(CODE16)
extern "C" u32_t bootCodeInfo[3]; //定义成数组类型就可以了,[0],[1]为LBA地址的低，高位，[2]为扇区数目

//读取后序扇区的代码
__attribute__((optimize("O0"))) //有必要再开启
__attribute__((optimize("-fomit-frame-pointer")))
__attribute__((section("textvbr"))) void vbrMainProcess()
{

	__asm__(
			"ljmp $0x7c0,$1f\n\t"
			"1: \n\t"
			"mov $0x7c0,%eax \n\t"
			"mov %eax,%ds \n\t"
			"mov %eax,%ss \n\t"
			"mov %eax,%es \n\t"
			"mov $CONFIG_REAL_INIT_STACK_SIZE-1,%esp \n\t"
	);
	ExtendedInt0x13Info exinfo(0x7c00,bootCodeInfo[4],bootCodeInfo[0],bootCodeInfo[2],bootCodeInfo[1]);
	Util::readSectorsExt(0x80, &exinfo);
	Util::jmp(bootCodeInfo[4]);
}
__asm__(
		".section textvbr,\"x\" \n\t"
		"_bootCodeInfo: \n\t"
		".int 0,0 \n\t" 				//定义bootcode所在的LBA绝对地址，分为低32位和高32位
		".int 0 \n\t"					//定义长度
		".int 0 \n\t"					//加载相对于0x7c00的偏移
		".org 512-2 \n\t"
		".byte 0x55 \n\t"
		".byte 0xaa \n\t" // 0x55 0xaa启动标识
);


#endif
