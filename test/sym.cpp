
extern int extern_sym;

__asm__(
 "_extern_sym: \n\t"
);

int test()
{
	int a=extern_sym;
}
