


#include <List.h> //for linear space manager:SimpleMemoryManager, for LocateableLinkedList
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cstdlib>
#include <new>
#include "File.h"

//suppose the disk image is :
//		hdd.img
#define HDD_FILE "hdd.img"

int main()
{
	X2fsUtil xfu(HDD_FILE);
	xfu.createFileInRoot("kill.me", 2);
//	printf("end create file\n");
	xfu.listRoot();
	printf("end listRoot \n");
	xfu.flush();
//	printf("end flush \n");
}
