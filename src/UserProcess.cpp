

#include <libx2.h>
#include <def.h>
#if defined(CODE32)
	__asm__(".code32 \n\t");
#endif


int which;

extern "C" __attribute__((section(".proc1"))) void process1()
{
	which=1;
	int curds=Util::getCurrentDs();
    while(1)
    	CALL_INT_3(0x24,c,curds,b,"int 0x24 by process1.\n",d,Util::MODE_COMMON);
	__asm__(
			"#.byte 0xcd,0xa\n\t" //not fine = [0x3 0x4 0x5 0x20] causes triple fault
			"#int $3\n\t"
			"jmp .\n\t");
	__asm__("mov  $0x5561,%eax \n\t");
}


extern "C" __attribute__((section(".proc2"))) void process2()
{

	which=2;
    while(1)
    	CALL_INT_3(0x24,c,Util::getCurrentDs(),b,"int 0x24 by process2.\n",d,Util::MODE_COMMON);
	__asm__(
			"jmp .\n\t");
	__asm__("mov  $0x5562,%eax \n\t");//0x556 for user process,2 for number(not pid)
}
