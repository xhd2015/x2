
#ifndef setjmp_h__
#define setjmp_h__
//non-local jmp

typedef void[] jmp_buf;
//int setjmp(jmp_buf env);
#define setjmp(env) !buf

void longjmp(jmp_buf env,int val);

#endif //setjmp_h__