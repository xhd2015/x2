

class T{
public:
	T(int x,int y=0):x(x+this->y),y(this->x+y)
	{

	}
	~T(){}
	int y,x;

};

void test()
{
	T a(0);
	int t;
	__asm__("":"=a"(t));
}
