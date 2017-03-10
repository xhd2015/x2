
#include <cstring>
#include <new>
#include <List.h>
#include <Memory.h>
#include "File.h"
//extern template class TreeNode<FileDescriptor>;
//extern template class SimpleMemoryManager<TreeNode<FileDescriptor> >;


typedef SimpleMemoryManager<TreeNode<FileDescriptor> >::Node Node;
/**tested**/
void X2fsUtil::mockMkfsX2fs(void* base,size_t secNum)
{
	/**
	 * clear data
	 */
	memset((void*) ((size_t)base+X2fsUtil::FileNameSection),0,X2fsUtil::FileNameSectionLen);
	SimpleMemoryManager<TreeNode<FileDescriptor> > smm((size_t)base+X2fsUtil::DirSection,X2fsUtil::DirSectionLen,true);

	/**
	 * set dir root,node[0] node[1] are preserved for use
	 */
	Node *proot = (Node*)((size_t)base+X2fsUtil::DirSection);//zero is preserved
	proot[0].SimpleMemoryNode::unfree();
	proot[1].SimpleMemoryNode::unfree();
	proot[2].SimpleMemoryNode::unfree();
	proot[1].setSon((Node*)(2*sizeof(Node)));//The first one points to the next one,the next one is root

	proot[2].setData(FileDescriptor(
			FileDescriptor::TYPE_DIR,
			0,0,0,0,0,
			0,0
	));
	proot[2].setFather((Node*)sizeof(Node));//the base is the dir_section,zero is preserved

	LinearSourceDescriptor *lsdarr=(LinearSourceDescriptor*)((size_t)base+X2fsUtil::FreeSpaceSection);
	new (lsdarr) LinearSourceDescriptor(X2fsUtil::FreeSpaceSection+X2fsUtil::FreeSpaceSectionLen  ,
			secNum*X2fsUtil::SecSize);
	new (lsdarr+1) LinearSourceDescriptor(0,0);
}

void X2fsUtil::createFile(void *base,const char* name,size_t secNum)
{

}
