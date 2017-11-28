

#include <utility>
#include <iostream>
using namespace std;

struct T{
	T()=default;
	T(T&&)
	{
		std::cout<<"T&&"<<endl;
	}
	T(const T&)
	{
		std::cout<<"T&"<<endl;
	}
	void operator=(const T&)
	{
		std::cout<<"=T&"<<endl;
	}
	void operator=(T&&)
	{
		std::cout<<"=T&&"<<endl;
	}

};

struct V{
	V(){
		cout<<"V()"<<endl;
	}
	V(const V& v)
	{
		cout<<"V(V&)"<<endl;
		this->t=v.t;
	}
	V(V&& v)
	{
		cout<<"V(V&&)"<<endl;
		this->t=std::move(v.t);
	}
	void operator=(V&& v)
	{
		cout<<"V&&="<<endl;
		this->t=v.t;
	}
	void operator=(V& v)
	{
		cout<<"V&="<<endl;
	}
	
	T t;

};
V getV()
{
	return V();
}

int main()
{
	V v=getV();
	//V v1=v; // = calls to copy
	V v1;
	v1=v;
	//V v2=std::move(v);
	//v1.V::operator=(v2);
	cout<<&v<<endl;

}
