
#include <cstdio>
#pragma pack(push,1)
class X{
public:
	char x;
	int y;
	int z1:3;
	int z2:5;
	int z3:8;
	int __z4:15;
	int z4:1;
	union{
		int z5:8;
		int z6:22;
	//	int z7;
	};
};

#pragma pack(pop)

int a=sizeof(X);


int main()
{
	printf("sizeof(x) is %d\n",sizeof(X));
	X x1;
	x1.z4=9;
	x1.z5=9;
	//printf("z5 = %d,z6 = %d,z7 = %d\n",x1.z5,x1.z6,x1.z7);

}
