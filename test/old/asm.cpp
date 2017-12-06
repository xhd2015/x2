extern int LOP;
extern int What;

__asm__(

"_LOP:\n\t"
"_What = _LOP \n\t"
);

int test()
{
	int* a=&LOP;
	int b=What;
	int *c=&What;
	int g=!(0b100);
	
}
