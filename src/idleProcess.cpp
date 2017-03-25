/*
 * idleProcess.cpp
 *
 *  Created on: 2017年3月20日
 *      Author: 13774
 */

#include <libx2.h>
#include <macros/all.h>

#if defined(CODE32)
	__asm__(".code32 \n\t");
#endif

extern "C" void idle()
{
	Util::printStr("I am idle\n");
	Util::jmpDie();
}



