/*
 * Filesystem_macros.h
 *
 *  Created on: Nov 24, 2017
 *      Author: 13774
 */

#ifndef INCLUDE_MACROS_FILESYSTEM_MACROS_H_
#define INCLUDE_MACROS_FILESYSTEM_MACROS_H_

#include <Filesystem.h>

int		MBRTable::findFirstActiveInline()
{
	for(int i=0;i<4;i++)
	{
		if(table[i].activeFlag == MBRPartitionEntry::FLAG_ACTIVE)return i;
	}
	return -1;
}


#endif /* INCLUDE_MACROS_FILESYSTEM_MACROS_H_ */
