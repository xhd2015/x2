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


int main()
{
	FileDescriptor fd;
	fd.setFileLen(4096);
	char space[fd.getSerializitionSize<EnvTransfer<32>>() * 3];
	SerializerPtr<EnvTransfer<32>> ptr(space);

	ptr << fd
			<< fd << fd; // 序列化多个对象

	ptr -= sizeof(space)*3; // 指针回退

	FileDescriptor fd2;

	ptr >> fd2; // 反序列化

	cout << fd2.getFileLen() << endl;

	cout << "END."<<endl;
}
