
#define __STR(x) #x
#define STR(x) __STR(x)
#define M(r,v) :STR(r)(v)

int c=STR("dsaf");
int b=0;
M(r,v)

