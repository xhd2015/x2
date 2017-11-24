
#ifndef Filesystem_h
#define Filesystem_h

#include <def.h>

/**
*using policy designate
*
*	The common part of NTFS,FAT,ext... filesystems:
*		
*/
class FileSystem{
public:
	//functions that must be implemented



protected:



};

/**
*	implement the ext4-linux file system
*/
class Ext4FileSystem{
public:


protected:	



};

/**
*	implement the FAT file system
*/
class FATFileSystem{


};


/**
*	implement SimpleFileSystem
*		as it is simple filesystem,most kernel can use it with as few modifications as possible
*/


#pragma pack(push,1)
class MBRPartitionEntry{
public:
	char	activeFlag;
	char	chsStart[3];
	char	chsEnd[3];
	char	paritionType;
	u32_t	lbaStart;
	u32_t	sectorNum;
};

class MBRTable{
public:
	MBRTable()=default;
	~MBRTable();
public:

	MBRPartitionEntry	table[4];

	int		findFirstActive();


};

#pragma pack(pop)




#endif //Filesystem_h
