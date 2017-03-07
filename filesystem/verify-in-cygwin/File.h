
#ifndef File_h__
#define File_h__

#include <Memory.h>

/**
* 
*/
class FileDescriptor
{
public:
	const static char TYPE_FILE,TYPE_DIR,TYPE_EAP;
public:
	FileDescriptor(char type);

protected:
	char type;
	size_t sectionStart,sectionSpan,fileStart,fileLen,nameStart;
	unsigned int createdTime,lastModefiedTime;

}



#endif //File_h__