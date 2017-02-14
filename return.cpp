
class T{
public:
	T(char v1){
	x[0]=v1;
}
	~T(){}
	T h(int a)
	{
		T t(0x2);
		T t2(0x22);
	}
	T& k()
	{
		T t(0x1);
		return t;
	}
public:
	char x[10];
};

void test()
{
	T t(0x3);
	__asm__ __volatile__("mov $0x6,%%ecx \n\t":::"ecx");
	t.h(0x4);
	//x 
	//T& y= t.k();
	//T z=y.h(0x5);
	T& x=t.k();

}
