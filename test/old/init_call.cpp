#include <iostream>
#include <new>

using namespace std;

struct T{
	T(){
		cout<<"T()"<<endl;
	}
	int a()=delete;
};
int T::a()
{
	cout<<"T::a()"<<endl;
}

struct V{
	V()=default;
	V(int a)
	{	
		cout<<"V(int)"<<endl;
	}
};

struct N{
	N()=default;
	N(int a){
	//new (&this->v) V(0);
	//this->v=V();
	}

	T t;
	V v;


};

int main()
{

	N n;
	n.t.a();
}







































