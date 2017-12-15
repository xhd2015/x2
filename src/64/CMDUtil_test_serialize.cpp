/*
 * CMDUtil_test_serialize.cpp
 *
 *  Created on: Dec 3, 2017
 *      Author: 13774
 */



#include <def.h>
#include <conceptual/Serialize.h>
#include <File.h>
#include <iostream>
#include <List.h>
#include <utility>

using namespace std;
enum {Bit = HOST_BIT };
using __Env = EnvTransfer<Bit>;

size_t depths=0;
void consum(BaseDescriptor<__Env>* const & i)
{
	std::cout << i->getName();
}
void beforeSon()
{
	++depths;
	std::cout << "\n";
	for(size_t i=0;i<depths;++i)
		std::cout << "\t";
	std::cout << "|";//son节点打印
}
void afterSon()
{
	--depths;
}
void beforeNext()
{
	++depths;
	std::cout << "\n";
	for(size_t i=0;i<depths;++i)
		std::cout << "\t";
	std::cout <<">";
}
void afterNext()
{
	--depths;
//	cout << "}";
}


void testPointerSerialize();
void testABunch();
void testTree();
void testX2fsUtil();
int main()
{
	testX2fsUtil();
//	testTree();
//	testPointerSerialize();
//	testABunch();
	return 0;
}
void testX2fsUtil()
{
	auto buf = makeSharedArray<char>(1024*50);

	SerializerPtr<__Env> ptr { *buf };

	X2fsMetaInfo metainfo{0,0};
	u8_t driver = 0;
	X2fsUtil<__Env> util(driver, metainfo);

	if(!util.mkdir(util.getFileTree()->getHead(),"myFoo"))
	{
		cerr << "cannot mkdir" << endl;
		return;
	}

	util.mkdir(util.getFileTree()->getHead()->getSon(),"myBar");

	util.listOnNode(util.getFileTree()->getHead(),5);
	cout << endl;

	ptr << util;

	X2fsUtil<__Env> util2 { driver, ptr=*buf};

	util2.listOnNode(util.getFileTree()->getHead(),5);
	cout << endl;

}
// tested good.
void testTree()
{
	auto buf = makeSharedArray<char>(1024*50);

	SerializerPtr<__Env> ptr { *buf };
	using __Tree = Tree<BaseDescriptor<__Env>*,MallocToSimple>;
	__Tree tree(make_shared<__Tree::__Allocator>());
	tree.setHead(new DirDescriptor<__Env>("root",0,0));
	tree.startWalk().insertSon(new FileDescriptor<__Env>("file",0,0,3)).endWalk();

	depths=0;
	tree.dumpInfo(consum, beforeSon, afterSon, beforeNext, afterNext);

	__Tree tree2=tree.makeSmmSharedTree();

	ptr << tree;


	ptr = *buf;
	ptr >> tree2;

	std::cout << std::endl;

	tree2.dumpInfo(consum, beforeSon, afterSon, beforeNext, afterNext);

	// 测试从序列化指针构造对象
	ptr = *buf;
	ptr << FileDescriptor<__Env>("back_file",0,0,2);
	FileDescriptor<__Env> fd(ptr = *buf); //从ptr构造
	std::cout <<fd.getName() << std::endl;

}
void testABunch()
{
	auto buf = makeSharedArray<char>(1024*50);
	enum {Bit = HOST_BIT };
	using __Env = EnvTransfer<Bit>;
	SerializerPtr<__Env> ptr { *buf };

	ptr << "hello world";

	SerializerPtr<__Env> {*buf} << "hello";
	HostEnv::String s;
	ptr = *buf;
	ptr >> s;
	cout << s << endl;
}
/**
 * 对于virtual的类来说，如果使用对象，就是直接调用其序列化方法
 * 如果是使用指针，就是自定义的方法。
 */
void testPointerSerialize()
{
//	auto buf = makeSharedArray<char>(1024*50);
//	enum {Bit = HOST_BIT };
//	using __Env = EnvTransfer<Bit>;
//	SerializerPtr<__Env> ptr { *buf };
//
//	FileDescriptor<__Env> f;
//	f.setName("haha");
//
//	BaseDescriptor<__Env> *pf1 = &f;
//
//	ptr << pf1; // const char &
//	ptr << f;
//
//	ptr = *buf;
//	BaseDescriptor<__Env> *pf2;
//	ptr >> pf2;
//	cout << pf2->getName() <<endl;
//	ptr >> *pf2;
//	cout << pf2->getName() << endl;//使用virtual函数

}

//======= 测试修改过后使用指针的情况
void testStringSerialize()
{
//	auto buf = makeSharedArray<char>(1024*50); // char[]
//	enum {Bit = HOST_BIT };
//	using __Env = EnvTransfer<Bit>;
//	SerializerPtr<__Env> ptr { *buf };//stack:[buf:char0]   heap:[char0][char1]...[charN]
//
////	FileDescriptor<__Env> f;
////	f.setName("haha");
//
//
//
////	ptr << f;
//	HostEnv::String oriStr("char");
//	ptr <<  oriStr << "www.baidu.com";
//
//	cout << getSerializitionSize<__Env>(oriStr) << endl;
//
//	HostEnv::String s;
//	ptr = *buf;
//	ptr >> s;
//	cout << s << endl;
//	ptr >> s;
//	cout << s << endl;
////
////
////	ptr = *buf;
////	FileDescriptor<__Env> f2;
////	ptr >> f2;
////	cout << f2.getName() <<endl;
////	cout << &f << endl;

}


//============测试树的序列化
// 测试64位，32位序列化Tree是否正确

//template <class T>
//class MySMM:public MallocToSimple<T>
//{
//public:
//	~MySMM()
//	{
//		cout << "~MySMM"<<endl;
//	}
//};
//template <class T>
//using SMMType =
//		MySMM<T>;
////			MallocToSimple<T>;
//void empty(){
//
//}
//int main()
//{
//
//	SMMType<TreeNode<int>> smm;
//	Tree<int,SMMType> tree{
//		std::shared_ptr<decltype(smm)>(&smm,doNothing<void,decltype(&smm)>) //不可以使用std::_Destroy,不知道为什么
//	};
//	tree.setHead(0);
//	tree.startWalk().insertNext(1).insertSon(2).gotoSon().insertSon(3).insertNext(4).endWalk();
//
//	depths=0;
//	tree.dumpInfo(consum, beforeSon, afterSon, beforeNext, afterNext);
//	constexpr size_t bits=32;
//	unique_ptr<char,std::default_delete<char[]>> ubuf{
//			new char[tree.getSerializitionSize<EnvTransfer<bits>>()]};
//
//	SerializerPtr<EnvTransfer<bits>> {ubuf.get()} << tree;
////	pWrite << tree;
//
////	SMMType<TreeNode<int>> smm2;
//	Tree<int,SMMType> tree2
////			{std::shared_ptr<decltype(smm2)>(&smm2,destruct<decltype(smm2)>)};
//			=tree.makeSmmSharedTree();
////			tree.makeSmmSharedTree();
//	SerializerPtr<EnvTransfer<bits>> {ubuf.get()} >> tree2;
//
//	std::cout << std::endl;
//	depths=0;
//
//	std::cout << "dumping tree2"<<std::endl;
//	tree2.dumpInfo(consum, beforeSon, afterSon, beforeNext, afterNext);
//	depths=0;
//	std::cout << "END."<<std::endl;
//	empty();
//	return 0;
//}

//====最初的序列化过程
//	struct MyEnv128:public EnvTransfer<128>{
//		template <class __T>
//		constexpr static size_t sizeofHostType()
//		{
//			return 16;//16 more than the pointer length
//		}
//
//	};
//
//	int main4()
//	{
//
//		bool b=true;
//		bool c=false;
//
//		char space[20];
//		SerializerPtr<EnvTransfer<64>> ptr{space};
//
//		ptr << b;
//		ptr << c;
//
//		ptr = space;
//		bool d=false,e=true;
//		ptr >> d >> e;
//		cout << "d="<<d<<",e="<<e<<endl;
//
//		return 0;
//	}
//
//// test pointer/basic safe/truncate
//int main3()
//{
//
//	char space[128];
//	SerializerPtr<EnvTransfer<32>> ptr32{space};
//	SerializerPtr<MyEnv128> ptr128{space};
//	size_t i=0;
////
////	ptr32 << (&i); // should truncate pointer
////	ptr128 << (&i); //should safe pointer
////
////	ptr32 << i ;// should truncate basic
////	ptr128 << i; //should safe basic
//
//	ptr32=space;ptr128=space;
//
//
//	size_t *p=&i;
//	ptr32 >> p;  // should safe pointer.Why? saving it is unsafe,loading it is safe.
//	ptr128 >> p; // should truncate pointer
//
//	ptr32 >> i; // basic safe
//	ptr128 >> i; // basic truncate, local is 8,env is 16.That means saving it is safe,loading it is unsafe.
//
//
//	cout << &i;
//	return 0;
//}
//
//int main2()
//{
//	FileDescriptor fd;
//	fd.setFileLen(4096);
//	char space[fd.getSerializitionSize<EnvTransfer<32>>() * 3];
//	SerializerPtr<EnvTransfer<32>> ptr(space);
//
//	ptr << fd
//			<< fd << fd; // 序列化多个对象
//
//	ptr = space;
//
//	FileDescriptor fd2;
//
//	ptr >> fd2; // 反序列化
//
//	cout << fd2.getFileLen() << endl;
//
//	char space2[sizeof(X2fsMetaInfo)];
//
//	ptr = space2;
//
//	X2fsMetaInfo meta;
//	X2fsMetaInfo meta2;
//	meta2.basicSizeType = 8;
//
//	meta.basicSizeType = 4;
//
//	cout << "original meta2 basic size:"<<static_cast<size_t>(meta2.basicSizeType) <<endl;
//	cout << meta.getSerializitionSize<EnvTransfer<32>>() << endl;
//
//	ptr << meta;
//
//	ptr = space2;
//	ptr >> meta2;
//
//	cout << "now meta2 basic size:"<<static_cast<size_t>(meta2.basicSizeType) <<endl;
//
//
//
//	cout << "END."<<endl;
//
//	return 0;
//}
