/**
 * There is nothing you can include from kernel,except def.h which does not produce any code
 */
#include <def.h>
#include <libx2.h>
#include <macros/all.h>


#if defined(CODE32USER)
	__asm__(".code32 \n\t");
#endif



#if defined(CODE32USER)

int which;
//_process1

__asm__(".section .proc1\n\t"
		"jmp .\n\t");
extern "C" __attribute__((section(".proc1"))) void process1()
{
	Util::jmpDie();
	Util::insertMark(0xCCCC);
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

#endif
