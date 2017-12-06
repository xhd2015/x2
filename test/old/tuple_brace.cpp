#include <tuple>
template <class K,class V>
class M:public std::tuple<K,V,V,V>{
public:
	typedef std::tuple<K,V,V,V>	Father;
	M()=default;
	//M(Father &&f):Father(f){}
	//M(const Father & f):Father(f){}
	template <class V1,class V2,class V3>
	M(K k,V1 v1,V2 v2,V3 v3):Father(k,std::move(v1),std::move(v2),std::move(v3)){}
	//M(K k,V v1,V v2,V v3):Father(k,v1,v2,v3){}

};
void test(M<int,int> m,int a,int b){}
int main()
{
	M<int,int>	m{0,1,2,3};
	test({0,1,2,3},0,4);

}
