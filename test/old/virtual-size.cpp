#include <cstdio>
#pragma pack(1)
struct A{
	int a;
	char b;

};
struct D{

};
struct C{
	void printc(){}
};
struct B{
	virtual void printb(){
		printf("B:printb \n");
	}
};
struct Bson:public B{

};
struct Bson2:public B{
	void printb(){
		printf("Bson2:printb \n");
	}
};

int main()
{
	B b;
	printf("sizeof(A) is %d,sizeof(D) is %d,sizeof(C) is %d,sizeof(B) is %d,sizeof(Bson) is %d,sizeof(Bson2) is %d\n",sizeof(A),sizeof(D),sizeof(C),sizeof(B),sizeof(Bson),sizeof(Bson2)) ;
	B *pb;
	pb=new B;
	pb->printb();
	pb=new Bson;
	pb->printb();
	pb=new Bson2;
	pb->printb();
}
