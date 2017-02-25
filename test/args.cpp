void test(void *a,void* args,...)
{
	test(args...);

}

void test(void *a,void *b)
{

}

void mmm()
{
	test(0,1,2,3);
}
