
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
	enum{
		FLAG_ACTIVE=0x80u,
		FLAG_NON_ACTIVE=0x0u
	};
	u8_t	activeFlag;
	u8_t	chsStart[3];
	u8_t	chsEnd[3];
	u8_t	paritionType;
	u32_t	lbaStart;
	u32_t	sectorNum;
};

class MBRTable{
public:
	MBRTable()=default;
	~MBRTable();
public:

	MBRPartitionEntry	table[4];

	AS_MACRO int		findFirstActiveInline();


};

#pragma pack(pop)




#endif //Filesystem_h
