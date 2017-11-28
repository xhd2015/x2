/**
 * Test a template that is partial,when defined with only extra functions,will it have the basic functions?
 * If the answer is no,how to make it come true.
 * 	Result:
 * 		The answer is NO
 * 		The solution is extension,like write a subclass template<class V> class IntBase<V>：public Base<int,V>
 */

#include<cstdio>
template <class X,class V>
class Base{
public:
	void baseCall()
	{
		printf("baseCall \n");
	}
};

template <class V>
class Base<int,V>
{
public:
	void baseCall()
	{
		printf("baseCall from int \n");
	}
	void intCall()
	{
		printf("intCall \n");
	}
};
template class Base<int*,int>;
template class Base<int,int>;
int main()
{
		Base<int*,int> b1;
		b1.baseCall();
	//	b1.intCall();//impossible
		Base<int,int> b2;
	//	b2.baseCall(); // also impossible if b2 does not define this function
		b2.intCall();
}


