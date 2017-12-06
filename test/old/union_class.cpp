#include <cstdio>
#include <new>
#pragma pack(1)

struct T{
T()
{
	printf("T\n");
}
int a;
};

struct P{
P(){
	b=5;
	c=6;
	printf("P\n");
}
int b;
char c;
};
#define MAKE_EXCEPION_DEC(type1,type2,type3) \
	union{ char ____##type1[sizeof(type1)]; char ____##type2[sizeof(type2)]; char ____##type3[sizeof(type3)];};union { type1* __##type1;type2* __##type2;type3* __##type3;};__##type1=(type1*)____##type1; new (__##type3) type3
#define EXCEP(TYPE)	((TYPE*)__##TYPE)
#define EX(TYPE)	EXCEP(TYPE)
int main()
{
	/*
	union{
		char __T[sizeof(T)];
		char __P[sizeof(P)];//KBENoException
	};*/
	MAKE_EXCEPION_DEC(T,int,P);
	//new (__P) P;
	printf("t.a = %d,p.b=%d,p.c=%d\n",__T->a,__P->b,__P->c);
	
}
