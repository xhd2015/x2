
class Father{
public:

	Father(int a,int b){}
	Father(int a){}
	void t(){}
	virtual void v(){}
public:
	int a;
	int b;

};

template<class T>
class Son:public Father{
public:
	Son(int a):Father(5){this->a=a;}	
	~Son(){}
	void t(){}
	void v(){}

public:
	int a;
	int c;


};


void test()
{
	Son<int> s1(9);
	Son<int> s2(7);
	s2.a=0;
	s2.Father::a=1;
	s2.b=2;
	s2.c=3;
	s2.t();
	s2.v();
	s2.Father::t();
	s2.Father::v();
	Father *x;
	__asm__("#nothing \n\t");
	x->v();
}
