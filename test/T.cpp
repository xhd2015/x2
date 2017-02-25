
class T{
public:
	union{	char I0[4],PreviousTaskLink[2],PTL[2];};
	union{	char I1[4],ESP0[4];};
	union{	char I2[4],SS0[2];};
	union{	char I3[4],ESP1[4];};
	union{	char I4[4],SS1[4];};
	union{	char I5[4],ESP2[4];};
	union{	char I6[4],SS2[4];};
	union{	char I7[4],CR3[4],PDBR[4];};
	union{	char I8[4],EIP[4];};
	union{	char I9[4],EFLAGS[4];};
	union{	char I10[4],EAX[4];};
	union{	char I11[4],ECX[4];};
	union{	char I12[4],EDX[4];};
	union{	char I13[4],EBX[4];};
	union{	char I14[4],ESP[4];};
	union{	char I15[4],EBP[4];};
	union{	char I16[4],ESI[4];};
	union{	char I17[4],EDI[4];};
	union{	char I18[4],ES[2];};
	union{	char I19[4],CS[2];};
	union{	char I20[4],SS[2];};
	union{	char I21[4],DS[2];};
	union{	char I22[4],FS[2];};
	union{	char I23[4],GS[2];};
	union{	char I24[4],LDTSELECTOR[2],LDTSEL[2];};
	union{	char I25[4],IOBASEADDR[4],IOADDR[4],TRAP;};
	

};

#include<iostream>
using namespace std;
int main()
{
	T t;
	cout << sizeof(t)<<endl;
}
