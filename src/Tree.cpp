
#include <List.h>
#include <Memory.h>
#include <test.h>

//=================模板实例化
template class Tree<MemoryDescriptor>;
template class TreeNode<MemoryDescriptor>;

template<class T>
TreeNode<T>::TreeNode(const T& data,TreeNode<T>* father,TreeNode<T>* son,TreeNode<T>* next,TreeNode<T>* previous):
ListNode<T>(data,next,previous),
father(father),
son(son)
{

}
template<class T>
inline TreeNode<T>::~TreeNode() {
}

template<class T>
   TreeNode<T>* TreeNode<T>::init(const T& data,TreeNode<T>* father,TreeNode<T>* son,TreeNode<T>* next,TreeNode<T>* previous)
   {
   	
   	/********
   	Util::printStr("TreeNode init:   ");
   	Test::dumpMemoryData(data);
	*********/

   	this->ListNode<T>::init(data,next,previous);//调用父类的初始化函数
   	this->father=father;
   	this->son = son;

   	/**********
   	Test::dumpMemoryData(this->data);
   	***********/

   	return this;
   }
template<class T>
TreeNode<T>* TreeNode<T>::setFather(TreeNode<T>* father) {
    this->father=father;
}

template<class T>
TreeNode<T>* TreeNode<T>::getSon() {
	return son;
}

template<class T>
TreeNode<T>* TreeNode<T>::getDirectFather() {//direct father
    return father;
}
template<class T>
  TreeNode<T>* TreeNode<T>::setSon(TreeNode<T>* son)
  {
  	this->son=son;
  }
template<class T>
TreeNode<T>* TreeNode<T>::getParent() {//往previous一直遍历，直到是跟，然后返回跟的father
	TreeNode<T> *p=this;
	while(p->hasPrevious())
	{
		p=p->getPrevious();
	}
	return p->getDirectFather();
}

//===============class Tree

template<class T>
Tree<T>::Tree(SimpleMemoryManager<TreeNode<T> >* smm):
smm(smm)
{
	root=smm->getNew();

	
}

template<class T>
Tree<T>::~Tree() {
}

template<class T>
void         Tree<T>::free(TreeNode<T> *root)
{
  if(root)
  {
     TreeNode<T>* p=root->getSon();//先把所有子类free
    while(p)
    {
        this->free(p);
        p = p->getNext();
    }//OK,all the sons are free
    smm->withdraw(root);
  }


}
template<class T>
TreeNode<T>* Tree<T>::getHead() {
	return root->getSon();
}

template<class T>
 Tree<T>* Tree<T>::setHead(TreeNode<T> *head)
 {
 	root->setSon(head);
 	return this;
 }
