


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
//run like '$thisprog $filename $spanSec
int main(int argc,char *argv[])
{
	X2fsUtil xfu(HDD_FILE);
	assert(argc>=3);
	printf("file = %s, secSpan = %d\n",argv[1],atoi(argv[2]));
	if(xfu.createFileInRoot(argv[1],(size_t) atoi(argv[2])))
	{
		printf("create successful \n");
	}else{
		printf("create failed \n");
	}
//	printf("end create file : %s\n",argv[1]);
	xfu.listRoot();
//	printf("end listRoot \n");
	xfu.flush();
//	printf("end flush \n");
}
