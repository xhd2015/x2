
#include <def.h>
#include <Filesystem.h>

#define CODE16

#if defined(CODE16)
	__asm__(".code16gcc \n\t");
#endif

//ld 文件布局：textvbr .data textmain
	// 由于.text会默认生成一些静态初始化代码，一起其他的东西，所以将其丢弃


//这两句生成对as内部标号的引用
extern "C" size_t bootCodeInfo[2]; //定义成数组类型就可以了
extern "C" char		kernelPath[];

// 第一个扇区用于加载和存储信息， 第一个区叫做secmbr, 第二个区是.data
__asm__(
		".section textvbr \n\t"
		"ljmp $0x7c0,$HERE \n\t"
		"HERE: \n\t"
		"mov $0x7c0,%eax \n\t"
		"mov %eax,%ds \n\t"
		"//move \n\t" //启动区域
		"call _readBootSectors \n\t"
		"jmp _vbrMain \n\t"
);

//读取后序扇区的代码
extern "C" __attribute__((section("textvbr"))) void readBootSectors()
{
	size_t start=bootCodeInfo[0];
	size_t size=bootCodeInfo[1];
	*(char*)start=0;
}

//__attribute__((section("textvbr"))) size_t bootCodeInfo[2]={0,0}; // 存放bootcode所在的扇区号以及数目
//__attribute__((section("textvbr"))) char kernelPath[]=""; //.rdata区

__asm__(
		".section textvbr \n\t"
		"_bootCodeInfo: \n\t"
		".int 0,0 \n\t" //定义bootcode所在的扇区
		"_kernelPath: \n\t"
		".asciz \"/boot/kernel.img\" \n\t" //定义内核镜像的路径

		".org 512-2 \n\t"
		".byte 0x55 \n\t"
		".byte 0xaa \n\t" // 0x55 0xaa启动标识
);
__attribute__((section(".data"))) MBRTable mbrTable; //必须放到.data区,不能放到.bss区

__asm__(".align 512 \n\t");//对齐到扇区整数倍
extern "C" __attribute__((section("textmain"))) void vbrMain()
{
	// 设置IDT，GDT，IDTR，GDTR

	// 启用32位包含模式，以0x7c0作为段基址

	// 加载x2文件系统

}



