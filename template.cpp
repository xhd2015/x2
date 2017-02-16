template <typename T,typename K>
class V{
public:
	V();
	~V();
	void get();
	void shit();

};

template<typename T,typename K>
V<T,K>::V()
{

}

template<typename T,typename K>
V<T,K>::~V()
{

}
template<typename T,typename K> 
void V<T,K>::get()
{
	int a=0;
	int b;
	b=a;
}
template <typename T,typename K>
void V<T,K>::shit()
{
	__asm__("#shit\n\t");
}
/*
template <typename K>
void V<V<int> >::get()
{
	__asm__("nop \n\t#haha");
}
*/
/*
void test()
{
	V<int>	a;
	a.get();

}
*/
