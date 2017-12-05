
int main()
{
	int a;
	__atomic_thread_fence (__ATOMIC_ACQUIRE);
	a=0;
	__atomic_thread_fence (__ATOMIC_RELEASE);
	return a;
}
