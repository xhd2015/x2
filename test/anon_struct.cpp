
#include "test.h"

int main()
{
#pragma pack(push,1)
	union{
	int c;
	struct{
		int a;
		int b;
		struct {
			int d;
		};
	};
	}K;
#pragma pack(pop)
	cout <<"sizeof(K)="<<sizeof(K)<<","<< K.d<<","<<K.b<<endl;	


}
