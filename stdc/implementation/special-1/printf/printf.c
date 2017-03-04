
#include <stdio.h>
#include <stdarg.h>
#include <Kernel.h>
#include <libx2.h> //for printer
#include <def.h>	//AS_MACRO


//NOTE:these code is from linux-src
#define ZEROPAD	1		/* pad with zero */
#define SIGN	2		/* unsigned/signed long */
#define PLUS	4		/* show plus */
#define SPACE	8		/* space if plus */
#define LEFT	16		/* left justified */
#define SPECIAL	32		/* 0x */
#define LARGE	64		/* use 'ABCDEF' instead of 'abcdef' */

FILE *stdout=NULL,
		*stderr=NULL,
		*stdin=NULL;

static int skip_atoi(const char **s)
{
	int i, c;

	for (i = 0; '0' <= (c = **s) && c <= '9'; ++*s)
		i = i*10 + c - '0';
	return i;
}


AS_MACRO static Printer *getPrinter()
{
	return Kernel::getTheKernel()->getPrinter();
}

int fputc(int c,FILE *stream)
{
	getPrinter()->putc(c);
}
int fputs(const char *s,FILE *stream)
{
	getPrinter()->putsz(s);
}

//stolen from gcc
int vfprintf(FILE *stream,const char *fmt,va_list args)
{
	int len;
	unsigned long long num;
	int i, base;
	char buffer[20],*temp;
	char * str;
	const char *s;
	size_t counts=0;

	int flags;		/* flags to number() */

	int field_width;	/* width of output field */
	int precision;		/* min. # of digits for integers; max
				   number of chars for from string */
	int qualifier;		/* 'h', 'l', or 'L' for integer fields */
	                        /* 'z' support added 23/7/1999 S.H.    */
				/* 'z' changed to 'Z' --davidm 1/25/99 */

	
	for ( ; *fmt ; ++fmt) {
		if (*fmt != '%') {
			//*str++ = *fmt;
			fputc(*fmt,stream);
			counts++;
			continue;
		}
			
		/* process flags */
		flags = 0;
		repeat:
			++fmt;		/* this also skips first '%' */
			switch (*fmt) {
				case '-': flags |= LEFT; goto repeat;
				case '+': flags |= PLUS; goto repeat;
				case ' ': flags |= SPACE; goto repeat;
				case '#': flags |= SPECIAL; goto repeat;
				case '0': flags |= ZEROPAD; goto repeat;
				}
		
		/* get field width */
		field_width = -1;
		if ('0' <= *fmt && *fmt <= '9')
			field_width = skip_atoi(&fmt);
		else if (*fmt == '*') {
			++fmt;
			/* it's the next argument */
			field_width = va_arg(args, int);
			if (field_width < 0) {
				field_width = -field_width;
				flags |= LEFT;
			}
		}

		/* get the precision */
		precision = -1;
		if (*fmt == '.') {
			++fmt;	
			if ('0' <= *fmt && *fmt <= '9')
				precision = skip_atoi(&fmt);
			else if (*fmt == '*') {
				++fmt;
				/* it's the next argument */
				precision = va_arg(args, int);
			}
			if (precision < 0)
				precision = 0;
		}

		/* get the conversion qualifier */
		qualifier = -1;
		if (*fmt == 'l' && *(fmt + 1) == 'l') {
			qualifier = 'q';
			fmt += 2;
		} else if (*fmt == 'h' || *fmt == 'l' || *fmt == 'L'
			|| *fmt == 'Z') {
			qualifier = *fmt;
			++fmt;
		}

		/* default base */
		base = 10;

		switch (*fmt) {
		case 'c':
			if (!(flags & LEFT))
				while (--field_width > 0){
					fputc(' ',stream);//*str++ = ' ';
					counts++;
				}
			fputc((unsigned char) va_arg(args,int),stream);//*str++ = (unsigned char) va_arg(args, int);
			counts++;
			while (--field_width > 0){
				fputc(' ',stream);//*str++ = ' ';
				counts++;
			}
			continue;

		case 's':
			s = va_arg(args, char *);
			if (!s)
				s = "<NULL>";

			len = strnlen(s, precision);

			if (!(flags & LEFT))
				while (len < field_width--){
					fputc(' ',stream);//*str++ = ' ';
					counts++;
				}
			for (i = 0; i < len; ++i){
				fputc(*s++,stream);//*str++ = *s++;
				counts++;
			}
			while (len < field_width--){
				fputc(' ',stream);//*str++ = ' ';
				counts++;
			}
			continue;

		case 'p':
			if (field_width == -1) {
				field_width = 2*sizeof(void *);
				flags |= ZEROPAD;
			}
			temp=number(buffer,
				(unsigned long) va_arg(args, void *), 16,
				field_width, precision, flags);
			*temp=0;
			counts+=fputs(str,stream);
			continue;


		case 'n':
			if (qualifier == 'l') {
				long * ip = va_arg(args, long *);
				*ip = (str - buf);
			} else if (qualifier == 'Z') {
				size_t * ip = va_arg(args, size_t *);
				*ip = (str - buf);
			} else {
				int * ip = va_arg(args, int *);
				*ip = (str - buf);
			}
			continue;

		case '%':
			fputc('%',stream);//*str++ = '%';
			counts++;
			continue;

		/* integer number formats - set up the flags and "break" */
		case 'o':
			base = 8;
			break;

		case 'X':
			flags |= LARGE;
		case 'x':
			base = 16;
			break;

		case 'd':
		case 'i':
			flags |= SIGN;
		case 'u':
			break;

		default:
			fputc('%',stream);//*str++ = '%';
			counts++;
			if (*fmt){
				fputc(*fmt,stream);//*str++ = *fmt;
				counts++;
			}
			else
				--fmt;
			continue;
		}
		if (qualifier == 'l') {
			num = va_arg(args, unsigned long);
			if (flags & SIGN)
				num = (signed long) num;
		} else if (qualifier == 'q') {
			num = va_arg(args, unsigned long long);
			if (flags & SIGN)
				num = (signed long long) num;
		} else if (qualifier == 'Z') {
			num = va_arg(args, size_t);
		} else if (qualifier == 'h') {
			num = (unsigned short) va_arg(args, int);
			if (flags & SIGN)
				num = (signed short) num;
		} else {
			num = va_arg(args, unsigned int);
			if (flags & SIGN)
				num = (signed int) num;
		}
		temp = number(buffer, num, base, field_width, precision, flags);
		*temp=0;
		counts+=fputs(buffer,stream);
	}
	//*str = '\0';
	return counts;//return str-buf;
}


int fprintf(FILE *stream,const char *fmt,...)
{
	va_list ap;
	va_start(ap,fmt);
	vfprintf(stream,fmt,ap);
	va_end(ap);
}

int printf(const char *fmt,...)
{
	va_list ap;
	va_start(ap,fmt);
	vfprintf(stdout,fmt,ap);
	va_end(ap);
}