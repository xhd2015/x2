
#ifndef math_h__
#define math_h__

#define HUGE_VAL

double sin(double x);
double cos(double x);
double tan(double x);
double asin(double x);
double acos(double x);
double atan(double x);
double atan2(double y,double x);
double sinh(double x);
double cosh(double x);
double tanh(double x);
double exp(double x);
double log(double x);
double log10(double x);
double pow(double x,double y);
double sqrt(double x);
double ceil(double x);
double floor(double x);
double fabs(double x);
double ldexp(double x,int n);//return x*2^n
double frexp(double x,int *exp);//x=rt*2^exp
double modf(int x,double *ip);
double fmod(double x,double y);

#endif //math_h__