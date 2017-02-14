
class T{
public:
	T();
	~T();
	const int x;
	int y;

};

int m()
{
	T t;
	__asm__("nop \n\t");
	//t.x=0;
	t.y=T::x;

}
