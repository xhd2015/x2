/*
 * EnvInterfaceX2Impl.h
 *
 *  Created on: Nov 25, 2017
 *      Author: 13774
 */

#ifndef ENVINTERFACEX2IMPL_H_
#define ENVINTERFACEX2IMPL_H_

#include <EnvInterface.h>

class EnvInterfaceX2Impl
#if defined(IDE_MODE)
		:public EnvInterface
#endif
{

public:
	int writeSectors(u32_t srcSeg,u32_t srcOff,u8_t driver,u32_t LBAlow,u32_t num,u32_t LBAhigh);
	int readSectors(u32_t dstSeg,u32_t dstOff,u8_t driver,u32_t LBAlow,u32_t num,u32_t LBAhigh);
	int printf_simple(const char *fmt,...);
	u8_t* malloc(size_t size);



};




#endif /* ENVINTERFACEX2IMPL_H_ */
