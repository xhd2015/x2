/*
 * ResourceProtocal.h
 *
 *  Created on: Dec 9, 2017
 *      Author: 13774
 */

#ifndef INCLUDE_CONCEPTUAL_RESOURCEPROTOCAL_H_
#define INCLUDE_CONCEPTUAL_RESOURCEPROTOCAL_H_
#include <def.h>
#include <memory>

// 资源初始化协议
template <class __Node>
AS_MACRO __Node * initToNull(__Node *n) noexcept
{
	if(n)
		n->initToNull();
	return n;
}

//template <class __Node>
//__Node *initToNullThrows(__Node *node)
//{
//	if(node)
//		node->initToNull();
//	else
//		HostEnv::systemAbort("initToNullThrows throws at nullptr", -2);
//}
template <template <class>class __SMM,class __Node,class ...Args>
__Node* getNew(__SMM<__Node> &smm,Args&& ...args)
{
	__Node *node=smm.getNew();
	if(node)
		std::_Construct(node, std::forward<Args>(args)...);
	return node;
}
template <template <class>class __SMM,class __Node,class ...Args>
__Node* getNewThrows(__SMM<__Node> &smm,Args&& ...args)
{
	__Node *node=smm.getNew();
	if(node)
		std::_Construct(node, std::forward<Args>(args)...);
	else
		HostEnv::systemAbort("getNewThrows throws with nullptr",-2);
	return node;
}




#endif /* INCLUDE_CONCEPTUAL_RESOURCEPROTOCAL_H_ */
