
#include <cstdio>
#pragma pack(push,1)
struct A{
int a:24;
int b:8;
char c:3;
char d:1;
char e:1;
char f:1;
char g:1;
char h:1;
int  i:24;
};
#pragma pack(pop)
int main()
{
	A k;
	k.a=0xff;
	k.b=0xfe;
	k.c=0;
	k.d=1;
	k.e=1;
	k.f=1;
	k.g=1;
	k.h=0;
	k.i=0xea00;
	int y=(k.a | (k.b<<24));
	char z=(k.h<<7)|(k.g<<6)|(k.f<<5)|(k.e<<4)|(k.d<<3)|k.c;
	printf("sizeof(A)=%d,y=%x,k.c=%x,k.d=%x,(char)k.c=%c,z=%c,%x,%d\n",sizeof(A),y,k.c,k.d,*((char*)&k+4),z,z,z);
	printf("k map:%x %x\n",*(int*)(&k),*((int*)&k+1));

}
