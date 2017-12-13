/*
 * Filesystem.cpp
 *
 *  Created on: Dec 8, 2017
 *      Author: 13774
 */

#include <Filesystem.h>

int		MBRTable::findFirstActiveInline()
{
	for(int i=0;i<4;i++)
	{
		if(table[i].activeFlag == MBRPartitionEntry::FLAG_ACTIVE)return i;
	}
	return -1;
}

