/*
 * CMDUtil_gtest.cpp
 *
 *  Created on: Dec 16, 2017
 *      Author: 13774
 */

#include <cstdio>
#include "gtest/gtest.h"
#include <def.h>
#include <conceptual/Serialize.h>
#include <conceptual/ExtFunctional.h>
//==from gtest
#include "../include/gtest/gtest-all.cc"

namespace {
namespace Data{
	using __Env = EnvTransfer<64>;
	using __SerializerPtr = SerializerPtr<__Env>;

	decltype(makeSharedArray<char>(0)) buf = makeSharedArray<char>(10*1024);
	__SerializerPtr ptr {*buf};
}
}

void prepareData()
{

}

void clearData()
{

}

TEST(TestSerializationInt,unknown){
	using namespace Data;

	ptr << 4;

	int d;
	(ptr = *buf) >> d;
	EXPECT_EQ(d,4);
}

GTEST_API_ int main(int argc,char * argv[])
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
