
extern int a;
extern "C" void x();
extern int &e;
extern int* &o;
extern int z[];
extern int *y;
void test()
{
	int b,c,d;
	//b=&(int)a; //impossible
	c=x;
	c=&x;
	c=e;
	c=&e;
	c=o;
	c=&o;
	c=a;
	c=&a;
	c=z;
	c=&z;
	c=y;
	c=&y;
}
