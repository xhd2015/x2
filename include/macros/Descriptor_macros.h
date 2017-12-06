/*
 * Descriptor_macros.h
 *
 *  Created on: 2017年3月24日
 *      Author: 13774
 */

#ifndef INCLUDE_MACROS_DESCRIPTOR_MACROS_H_
#define INCLUDE_MACROS_DESCRIPTOR_MACROS_H_

#include <Descriptor.h>
//=================function macros
 void SegmentDescriptor::setBaseAddr(int baseAddr)
 {
	 this->baseAddrLow_24 = baseAddr & 0xffffff;
	 this->baseAddrHigh_8 = ((baseAddr & 0xff000000)>>24);
 }
 int	 SegmentDescriptor::getBaseAddr()const
 {
	 return (this->baseAddrLow_24 | (this->baseAddrHigh_8 << 24));
 }
 int		 SegmentDescriptor::getLimit()const
 {
	 return (this->limitLow_16|(this->limitHigh_4 << 16));
 }
 void	 SegmentDescriptor::setLimit(int limit)
 {
	 this->limitLow_16 = limit & 0xffff;
	 this->limitHigh_4 = ((limit & 0xf0000)>>16);
 }



#endif /* INCLUDE_MACROS_DESCRIPTOR_MACROS_H_ */
