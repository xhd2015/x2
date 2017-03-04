
#ifndef stdlib_h__
#define stdlib_h__

#define NULL ((void*)0)
#define EXIT_FAILURE
#define EXIT_SUCCESS
#define RAND_MAX
#define MB_CUR_MAX

typedef unsigned int size_t;
typedef int wchar_t;
typedef struct div_t_struct{

}div_t;
typedef	struct ldiv_t_struct{

}ldiv_t;



double atof(const char *s);
int atoi(const char *s);
long atol(const char *s);
double strtod(const char *s,char **endp);//say s=" 45lk",then skip " ",return 45,set *endp="lk",however if endp==NULL,does nothing
long strtol(const char *s,char **endp,int base);
unsigned long strtoul(const char *s,char **endp,int base);
int rand(void);
void srand(unsigned int seed);
void *calloc(size_t nobj,size_t size);
void *malloc(size_t size);
void *realloc(void *p,size_t size);
void free(void *p);
void abort(void);
void exit(int status);
int atexit(void (*fcn)(void));
int system(const char *s);
char *getenv(const char *name);
void *bsearch(const void *key,const void *base,size_t n,size_t size,int (*cmp)(const void *keyval,const void *datum));
void qsort(void *base,size_t n,size_t size,int (*cmp)(const void *,const void *));
int abs(int n);
long labs(long n);
div_t div(int num,int denom);
ldiv_t ldiv(long num,long denom);

#endif //stdlib_h__