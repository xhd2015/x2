
#ifndef stdarg_h__
#define stdarg_h__
#include <stddef.h> //for NULL

#define va_list char*
//ap==va_list
#define va_start(ap,lastNamedArg) ((ap)=(va_list)(&lastNamedArg))
//va_arg(ap,type)
#define va_arg(ap,type)	({ (ap)+=sizeof(type)/sizeof(*ap); *(type*)(ap); })
#define va_end(ap)		(ap)=NULL


//done

#endif //stdarg_h__