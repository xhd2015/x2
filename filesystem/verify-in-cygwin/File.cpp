
#include "File.h"
#include <cstdio>
#include <cstring>

#include <List.h>
void X2fsFileUtil::mockMkfsX2fs(void* p,size_t secNum) {
	/**
	 * clear data
	 */
	memset((void*) ((size_t)p+X2fsFileUtil::FileNameSection),0,X2fsFileUtil::FileNameSectionLen);
	SimpleMemoryManager<TreeNode<FileDescriptor> > smm(X2fsFileUtil::DirSection,X2fsFileUtil::DirSectionLen,true);
	memset((void*) ((size_t)p+X2fsFileUtil::FreeSpaceSection),0,X2fsFileUtil::FreeSpaceSectionLen);

	/**
	 * set dir root
	 */
	TreeNode<FileDescriptor> *proot=new ( (void*) ((size_t)p+X2fsFileUtil::DirSection)) TreeNode<FileDescriptor>(FileDescriptor(
			FileDescriptor::TYPE_DIR,
			0,0,0,0,0,
			0,0
	));

	LinearSourceDescriptor *lsdarr=(LinearSourceDescriptor*)((size_t)p+X2fsFileUtil::FreeSpaceSection);
	new (lsdarr) LinearSourceDescriptor(X2fsFileUtil::FreeSpaceSection+X2fsFileUtil::FreeSpaceSectionLen  ,  secNum*X2fsFileUtil::SecSize);
	new (lsdarr+1) LinearSourceDescriptor(0,0);
}

void X2fsFileUtil::createFile(void *base,const char* name,size_t secNum)
{

}
