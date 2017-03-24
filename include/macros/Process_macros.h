/*
 * Process.h
 *
 *  Created on: 2017年3月24日
 *      Author: 13774
 */

#ifndef INCLUDE_MACROS_PROCESS_MACROS_H_
#define INCLUDE_MACROS_PROCESS_MACROS_H_


#include <Process.h>

//==========function macros
#if defined(CODE32)||defined(CODE64)

//=====class:Process
int	Process::getTSSSel()const
{
	return this->tssSel;
}
unsigned int	Process::getPid()const
{
	return this->pid;
}
void Process::setStack0(size_t stack0)
{
	ptss->ESP0 = stack0;
}

void Process::setStack3(size_t stack3)
{
	ptss->ESP = stack3;
}

void Process::setSSSel0(int sel)
{
	ptss->SS0 = sel;
}

void Process::setSSSel3(int sel)
{
	ptss->SS = sel;
}

void Process::setCSSel(int sel)
{
	ptss->CS = sel;
}

void Process::setCodeStart(size_t start)
{
	ptss->EIP = start;
}
size_t	Process::getCodeStart()const
{
	return this->ptss->EIP;
}

int	Process::getLDTSsel()const
{
	return this->ldtSel;
}
int Process::getSatus() const
{
	return this->status;
}

void Process::setStatus(
	int status)
{
	this->status=status;
}
int	Process::getStatus()const
{
	return this->status;
}
size_t Process::getProcessBase()const
{
	return this->processBase;
}

#endif




#endif /* INCLUDE_MACROS_PROCESS_MACROS_H_ */
