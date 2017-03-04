#include <malloc.h>
#include <Kernel.h>
	//for os x2,calls for kernel to provide the heap

void *malloc(size_t size)
{
	return Kernel::getTheKernel()->mnew(size);
}

void free(void *p)
{
	Kernel::getTheKernel()->mdelete(p);

}
