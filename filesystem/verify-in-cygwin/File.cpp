
#include <cstring>
#include <new>
#include <List.h>
#include <Memory.h>
#include "File.h"
//extern template class TreeNode<FileDescriptor>;
//extern template class SimpleMemoryManager<TreeNode<FileDescriptor> >;
/**tested**/
void X2fsUtil::mockMkfsX2fs(void* base,size_t secNum)
{
	/**
	 * clear data
	 */
	memset((void*) ((size_t)base+X2fsUtil::FileNameSection),0,X2fsUtil::FileNameSectionLen);
	SimpleMemoryManager<TreeNode<FileDescriptor> > smm((size_t)base+X2fsUtil::DirSection,X2fsUtil::DirSectionLen,true);

	/**
	 * set dir root
	 */
	TreeNode<FileDescriptor> *proot=new ( (void*) ((size_t)base+X2fsUtil::DirSection)) TreeNode<FileDescriptor>(FileDescriptor(
			FileDescriptor::TYPE_DIR,
			0,0,0,0,0,
			0,0
	));

	LinearSourceDescriptor *lsdarr=(LinearSourceDescriptor*)((size_t)base+X2fsUtil::FreeSpaceSection);
	new (lsdarr) LinearSourceDescriptor(X2fsUtil::FreeSpaceSection+X2fsUtil::FreeSpaceSectionLen  ,
			secNum*X2fsUtil::SecSize);
	new (lsdarr+1) LinearSourceDescriptor(0,0);
}

void X2fsUtil::createFile(void *base,const char* name,size_t secNum)
{

}
