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

using namespace std;
	struct MyEnv128:public EnvTransfer<128>{
		template <class __T>
		constexpr static size_t sizeofHostType()
		{
			return 16;//16 more than the pointer length
		}

	};


	int main()
	{

		bool b=true;
		bool c=false;

		char space[20];
		SerializerPtr<EnvTransfer<64>> ptr{space};

		ptr << b;
		ptr << c;

		ptr = space;
		bool d=false,e=true;
		ptr >> d >> e;
		cout << "d="<<d<<",e="<<e<<endl;

		return 0;
	}

// test pointer/basic safe/truncate
int main3()
{

	char space[128];
	SerializerPtr<EnvTransfer<32>> ptr32{space};
	SerializerPtr<MyEnv128> ptr128{space};
	size_t i=0;
//
//	ptr32 << (&i); // should truncate pointer
//	ptr128 << (&i); //should safe pointer
//
//	ptr32 << i ;// should truncate basic
//	ptr128 << i; //should safe basic

	ptr32=space;ptr128=space;


	size_t *p=&i;
	ptr32 >> p;  // should safe pointer.Why? saving it is unsafe,loading it is safe.
	ptr128 >> p; // should truncate pointer

	ptr32 >> i; // basic safe
	ptr128 >> i; // basic truncate, local is 8,env is 16.That means saving it is safe,loading it is unsafe.


	cout << &i;
	return 0;
}

int main2()
{
	FileDescriptor fd;
	fd.setFileLen(4096);
	char space[fd.getSerializitionSize<EnvTransfer<32>>() * 3];
	SerializerPtr<EnvTransfer<32>> ptr(space);

	ptr << fd
			<< fd << fd; // 序列化多个对象

	ptr = space;

	FileDescriptor fd2;

	ptr >> fd2; // 反序列化

	cout << fd2.getFileLen() << endl;

	char space2[sizeof(X2fsMetaInfo)];

	ptr = space2;

	X2fsMetaInfo meta;
	X2fsMetaInfo meta2;
	meta2.basicSizeType = 8;

	meta.basicSizeType = 4;

	cout << "original meta2 basic size:"<<static_cast<size_t>(meta2.basicSizeType) <<endl;
	cout << meta.getSerializitionSize<EnvTransfer<32>>() << endl;

	ptr << meta;

	ptr = space2;
	ptr >> meta2;

	cout << "now meta2 basic size:"<<static_cast<size_t>(meta2.basicSizeType) <<endl;



	cout << "END."<<endl;

	return 0;
}
