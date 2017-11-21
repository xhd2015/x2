/*
 * IOProgramer_macros.h
 *
 *  Created on: 2017年3月24日
 *      Author: 13774
 */

#ifndef INCLUDE_MACROS_IOPROGRAMER_MACROS_H_
#define INCLUDE_MACROS_IOPROGRAMER_MACROS_H_

#include <IOProgramer.h>
//================Function Macros
#if defined(CODE32)
//=========class : Keyboard
int Keyboard::isBusy()
{
    return Util::inb(Keyboard::PORT_CONTROL) & 0x2;
}
int Keyboard::hasData()
{
    return Util::inb(Keyboard::PORT_CONTROL) & 0x1;
}
int Keyboard::readScanCode()
{
    return Util::inb(Keyboard::PORT_DATA);
}
void Keyboard::enable()
{
    int a=Util::inb(Keyboard::PORT_PPI);
    Util::outb(Keyboard::PORT_PPI,a & 0x7f);
}
void Keyboard::disable()
{
    int a=Util::inb(Keyboard::PORT_PPI);
    Util::outb(Keyboard::PORT_PPI,a | 0x80);
}

#endif //CODE32


#if defined(CODE32)||defined(CODE16)
//========class :IO_HDD
bool  IO_HDD::isBusy(char status)
{
	return (status & 0x80);
}

bool IO_HDD::isReady(char status)
{
	return (status & 0x8);
}

bool IO_HDD::isError(char status)
{
	return (status & 0x1);
}

char IO_HDD::readStatus()
{
	return Util::inb(This::PORT_STATUS);
}

void  IO_HDD::writeSecNum()
{
	Util::outb(This::PORT_SECNUM,this->secNumber);
}

void IO_HDD::writeSecStart() {
	Util::outb(This::PORT_SECSTART_0, (char)this->secStart);
	Util::outb(This::PORT_SECSTART_1, (char)(this->secStart >> 8));
	Util::outb(This::PORT_SECSTART_2, (char)(this->secStart >> 16));
	Util::outb(This::PORT_SECSTART_3, ((char)(this->secStart >> 24) & (0xf) )|
				(( this->LBAMode & 0x1) <<6)|
				((this->hddNo & 0x1) << 4) |
				0xa0
	);
}
void IO_HDD::requestRead()
{
	Util::outb(This::PORT_READ_COMMAND, 0x20);
}
void IO_HDD::requestWrite()
{
	Util::outb(This::PORT_WRITE_COMMAND, 0x30);
}
void IO_HDD::waitUntilReady()
{
	char status;//=This::readStatus();
	while(true)
	{
		status=This::readStatus();
		if(!This::isBusy(status) && This::isReady(status))break;
	}
}
size_t IO_HDD::getDstOff() const {
	return dstOff;
}

void IO_HDD::setDstOff(size_t dstOff) {
	this->dstOff = dstOff;
}

int IO_HDD::getDstSeg() const {
	return dstSeg;
}

void IO_HDD::setDstSeg(int dstSeg) {
	this->dstSeg = dstSeg;
}

int IO_HDD::getHddNo() const {
	return hddNo;
}

void IO_HDD::setHddNo(int hddNo) {
	this->hddNo = hddNo;
}

bool IO_HDD::isLbaMode() const {
	return LBAMode;
}

unsigned char IO_HDD::getSecNumber() const {
	return secNumber;
}

void IO_HDD::setSecNumber(unsigned char secNumber) {
	this->secNumber = secNumber;
}

size_t IO_HDD::getSecStart() const {
	return secStart;
}

void IO_HDD::setSecStart(size_t secStart) {
	this->secStart = secStart;
}
#endif //CODE32 || CODE16



#endif /* INCLUDE_MACROS_IOPROGRAMER_MACROS_H_ */
