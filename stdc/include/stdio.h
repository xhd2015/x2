
#ifndef stdio_h__
#define stdio_h__
#include <stdarg.h>

#define L_tmpnam 1
#define NULL ((void*)0)

//can be used as the 3rd argument of setvbuf
#define _IOFBF
#define _IOLBF
#define _IONBF

//for setbuf
#define BUFSIZ

#define EOF -1
#define FOPEN_MAX
#define FILENAME_MAX

//for fseek
#define SEEK_CUR
#define SEEK_SET
#define SEEK_END

//tmpnam
#define TMP_MAX




typedef unsigned int size_t;
typedef struct FILE_struct{


} FILE;//you may use another FILE definition,so modify it here
typedef struct fpost_t_struct{

}fpost_t;

//for std
extern FILE *stderr,*stdin,*stdout;



//File IO
FILE *fopen(const char *filename,const char *mode);
FILE *freopen(const char *filename,const char *mode,FILE* stream);
int fflush(FILE *stream);
int fclose(FILE *stream);
int remove(const char *filename);
int rename(const char *oldname,const char *newname);
FILE *tmpfile(void);
char *tmpnam(char s[L_tmpnam]);
int setvbuf(FILE *stream,char *buf,int mode,size_t size);
void setbuf(FILE *stream,char *buf);

//Print
int fprintf(FILE *stream,const char *fmt,...);
int printf(const char *fmt,...);
int sprintf(char *s,const char *fmt);

int vprintf(const char *fmt,va_list arg);
int vfprintf(FILE *stream,const char *fmt,va_list arg);
int vsprintf(char *s,const char *fmt,va_list arg);

//Input
int fscanf(FILE *stream,const char *fmt,...);
int scanf(const char *format,...);
int sscanf(const char *s,const char * fmt,...);

//Character
int fgetc(FILE *stream);
char *fgets(char *s,int n,FILE *stream);
int fputc(int c,FILE *stream);
int fputs(const char *s,FILE *stream);
int getc(FILE *stream);
int getchar(void);
char *gets(char *s);
int putc(int c,FILE *stream);
int putchar(int c);
int puts(const char *s);
int ugetc(int c,FILE *stream);//向流写入一个字符

//Direct read/write
size_t fread(void *ptr,size_t size,size_t nobj,FILE *stream);
size_t fwrite(const void *ptr,size_t size,size_t nobj,FILE *stream);
int fseek(FILE *stream,long offset,int origin);
long ftell(FILE *stream);
void rewind(FILE *stream);//seek to 0,clear error
int fgetpos(FILE *stream,fpost_t *ptr);
int fsetpos(FILE *stream,const fpost_t *ptr);

//Error condition and handling
void clearerr(FILE *stream);
int feof(FILE *stream);
int ferror(FILE *stream);
void perror(const char *s);//print error



#endif //stdio_h__